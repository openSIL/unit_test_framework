/**
 * @file  FbrRegstrAccReadUt.c
 * @brief Unit tests for DfXFabricRegisterAccRead
 *
 * Iterations:
 * - InstanceEnter: Call DfXFabricRegisterAccRead and enter Instance branch
 *   
 * - InstanceSkip: Call DfXFabricRegisterAccRead and skip Instance branch
 */


#include <UtBaseLib.h>
#include <UtLogLib.h>

#include <OpenSIL\xUSL\DF\DfIp2Ip.h> // Can not recognize DfIp2Ip.h without relative path 
#include "DfXFabricRegisterAcc.h"

// Stubs:
uint32_t xUSLPciRead32 (uint32_t Address)
{
    return 0;
}
void xUSLPciWrite32 (uint32_t Address, uint32_t Value)
{
    return; 
}
uint32_t
DfFabricRegisterAccGetPciDeviceNumberOfDie (
  uint32_t Socket
  )
{
    return 0; 
}

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
    
    if(strcmp(IterationName, "InstanceEnter") == 0)
    {
        // Arrange
        uint32_t Socket = 0;
        uint32_t Function = 0;
        uint32_t Offset = 0;
        uint32_t Instance = FABRIC_REG_ACC_BC;

        uint32_t result; 
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call DfXFabricRegisterAccRead");
        result =  DfXFabricRegisterAccRead(Socket, Function, Offset, Instance);
        // Assert
        if(result != 0) 
          UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);

    }
    else if(strcmp(IterationName, "InstanceSkip") == 0)
    {
        // Arrange
        uint32_t Socket = 0;
        uint32_t Function = 0;
        uint32_t Offset = 0;
        uint32_t Instance = 0;

        uint32_t result; 
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call DfXFabricRegisterAccRead");
        result =  DfXFabricRegisterAccRead(Socket, Function, Offset, Instance);
        // Assert
        if(result != 0) 
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
