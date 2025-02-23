/**
 * @file  FindComponentLM.c
 * @brief Unit tests for DfXFindComponentLocationMap
 *
 * Iterations:
 * - NoConditionBranch: Call DfXFindComponentLocationMap and skip the if branch through a mock call
 *   
 * - ConditionBranch: Call DfXFindComponentLocationMap and enter the if branch through a mock call
 */


#include <UtBaseLib.h>
#include <UtLogLib.h>
#include <stdlib.h>

#include <OpenSIL\xUSL\DF\DfIp2Ip.h> // Can not recognize DfIp2Ip.h without relative path 
#include "DfXBaseFabricTopology.h"

// Mocks:
static int num = 0; 
uint32_t
DfXFabricRegisterAccRead (
  uint32_t Socket,
  uint32_t Function,
  uint32_t Offset,
  uint32_t Instance
  )
{
    if(num == 0)
    {
        return 0x00000303;
    }
    else
         return 0x00000000;
}

// Stubs: 
uint32_t DfGetNumberOfDiesOnSocket (void)
{
  return 0; 
}

uint32_t
DfGetHostBridgeSystemFabricID (
  uint32_t Socket,
  uint32_t Index
  )
{
  return 771;
}

// Fakes: 
const
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
DfFindDeviceTypeEntryInMap (
  FABRIC_DEVICE_TYPE  Type
  )
{
    static const DEVICE_IDS myIds[1] = {0}; // Mock device IDs.
    static const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP myMap[1] = 
    {
        {
            Ios,       // Device type.
            0,         // Device count.
            myIds      // Associated device IDs...
        }
    };
    return myMap; // Returns a mock device map for testing.
}

const COMPONENT_LOCATION  TestGenoaComponentLocation [] = {
  {0, 0, 0x22, PrimaryFch}, // Physical location, Socket 0, Die 0, Ios2
  {1, 0, 0x22, SecondaryFch},   // Physical location, Socket 1, Die 0, Ios2
  {0, 0, 0x22, PrimarySmu}, // Physical location, Socket 0, Die 0, Ios2
  {1, 0, 0x22, SecondarySmu},   // Physical location, Socket 1, Die 0, Ios2
};

AMD_UNIT_TEST_STATUS
EFIAPI
TestPrerequisite (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  return AMD_UNIT_TEST_PASSED;
}

void
EFIAPI
TestBody (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName        = UtGetTestName (Ut);
  const char* IterationName   = UtGetTestIteration (Ut);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);
    
    if(strcmp(IterationName, "Count") == 0)
    {
        // Arrange

        num = 1;
        uint32_t *Count = (uint32_t *)malloc(sizeof(uint32_t));
        uint32_t *PhysIos0FabricId = NULL;
        const COMPONENT_LOCATION* result = &TestGenoaComponentLocation[0];
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call DfXFindComponentLocationMap");
        result = DfXFindComponentLocationMap(Count, PhysIos0FabricId);
        // Assert
        if(result->Socket != 0 || result->Die != 0 ||
           result->IomsFabricId != 0x22 || result->Type != PrimaryFch) 
          UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);

    }
    else if(strcmp(IterationName, "PhysIos0FabricId") == 0)
    {
        // Arrange
        uint32_t *Count = NULL;
        uint32_t *PhysIos0FabricId = (uint32_t *)malloc(sizeof(uint32_t));
        const COMPONENT_LOCATION* result = &TestGenoaComponentLocation[0];
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call DfXFindComponentLocationMap");
        result = DfXFindComponentLocationMap(Count, PhysIos0FabricId);
        // Assert
        if(result->Socket != 0 || result->Die != 0 ||
           result->IomsFabricId != 0x22 || result->Type != PrimaryFch) 
          UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);

    }
    else
    {
        Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Iteration '%s' is not implemented.", IterationName);
        UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }

    // if we run at any issue, The API is going to abort here.
    UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);

    Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
        "%s (Iteration: %s) Test ended.", TestName, IterationName);
}

AMD_UNIT_TEST_STATUS
EFIAPI
TestCleanUp (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  return AMD_UNIT_TEST_PASSED;
}

/**
 * main
 * @brief      Starting point for Execution
 *
 * @details    This routine:
 *              - Handles the command line arguments.
 *              - Declares the unit test framework.
 *              - Run the tests.
 *              - Deallocate the Unit test framework.
 *
 * @param      argc                     Argument count
 * @param      *argv[]                  Argument vector
 *
 * @retval     AMD_UNIT_TEST_PASSED     Function succeeded
 * @retval     NON-ZERO                 Error occurs
 */
int
main (
  int   argc,
  char  *argv[]
  )
{
  AMD_UNIT_TEST_STATUS Status;
  AMD_UNIT_TEST_FRAMEWORK Ut;

  // Initializing the UnitTest framework
  Status = UtInitFromArgs (
    &Ut,
    argc,
    argv
  );
  if (Status != AMD_UNIT_TEST_PASSED) {
    return Status;
  }

  // Logging the start of the test.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // Running test.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
