/**
 * @file TypeEntryInMapUt.c
 * @brief Unit tests for DfFindDeviceTypeEntryInMap
 *
 * Iterations:
 *
 *   - TypeMatch:    Executes DfFindDeviceTypeEntryInMap and passes the Type 
 *                   that matches the DeviceMap Type returned from the API table (XferTable).
 *   - TypeMismatch: Executes DfFindDeviceTypeEntryInMap and passes the Type 
 *                   that mismatches the DeviceMap Type returned from the API table (XferTable).
 */


#include <UtBaseLib.h>
#include <UtLogLib.h>

#include <SilBaseFabricTopologyLib.h>
#include <DfCmn2Rev.h>
#include <xSIM.h>
#include <xSIM-api.h>
#include <Sil-api.h>
#include <SilCommon.h>

#include <Library/UtSilServicesMockLib.h>

#include "BaseFabricTopologyCmn.h"

// Dependency:
// This variable holds the host debug service instance.
HOST_DEBUG_SERVICE mHostDebugService = NULL;

// API Table Functions:
// These functions simulate basic functionality for testing purposes.
const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP* My_DfGetDeviceMapOnDie(void)
{
    static const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP myMap[3] = {0}; 
    return myMap; 
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
    
    if(strcmp(IterationName, "TypeMatch") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        FABRIC_DEVICE_TYPE passedType = {0};                        // input - type

        DF_COMMON_2_REV_XFER_BLOCK passedTable = {NULL};            // API table
        passedTable.DfGetDeviceMapOnDie = My_DfGetDeviceMapOnDie;   // called function in the API table

        MockSilGetCommon2RevXferTableOnce(&passedTable, Status);    // mock with proper API table and status
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call DfFindDeviceTypeEntryInMap with the matching Type");
        const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP * returnedMap = DfFindDeviceTypeEntryInMap (passedType);
        // Assert
        if(returnedMap->Type != passedType) 
          UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }
    else if(strcmp(IterationName, "TypeMismatch") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        FABRIC_DEVICE_TYPE passedType = {1};                        // input - type

        DF_COMMON_2_REV_XFER_BLOCK passedTable = {NULL};            // API table
        passedTable.DfGetDeviceMapOnDie = My_DfGetDeviceMapOnDie;   // called function in the API table

        MockSilGetCommon2RevXferTableOnce(&passedTable, Status);    // mock with proper API table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfFindDeviceTypeEntryInMap with the mismsatching Type");
        const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP * returnedMap = DfFindDeviceTypeEntryInMap (passedType);
        // Assert
        if(returnedMap) // should be null 
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
