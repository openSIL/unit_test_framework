/**
 * @file CcxSetMiscMsrsUt.c
 * @brief Unit tests for CcxSetMiscMsrs
 *
 * Iterations:
 *
 * -Default: Executes CcxSetMiscMsrsUt(CCXCLASS_INPUT_BLK)
 */

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <xSIM.h> 
#include <Ccx.h>
#include <MsrReg.h>
#include <CcxCmn2Rev.h>

#include <Library/UtMsrRegStubLib.h>
#include <Library/UtSilServicesMockLib.h>
#include <xSIM-api.h>

// Stubs 
bool xUslIsComputeUnitPrimary (
    void
    )
{
    return true;
}

void
Zen4SetMiscMsrs (
  CCXCLASS_INPUT_BLK *CcxInputBlock
  )
{
    return; 
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
    
    if(strcmp(IterationName, "ZeroInitialized") == 0)
    {
        // Arrange
        CCX_XFER_TABLE CcxXferZen4 = {0};          // table 
        CcxXferZen4.SetMiscMsrs = Zen4SetMiscMsrs; // function is called in CcxSetMiscMsrs. assign stub

        MockSilGetCommon2RevXferTableOnce(&CcxXferZen4, SilPass); // mock with proper table and status

        CCXCLASS_INPUT_BLK CcxInputBlock = {0}; // 0 initialized argument. will skip EnableSvmAVIC branch 
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call CcxSetMiscMsrs and pass zero initialized CcxInputBlock");
        CcxSetMiscMsrs (&CcxInputBlock);
        // Assert
    }
    else if(strcmp(IterationName, "ZeroInitialized_EnableSvmAVIC") == 0)
    {
        // Arrange
        CCX_XFER_TABLE CcxXferZen4 = {0};           // table
        CcxXferZen4.SetMiscMsrs = Zen4SetMiscMsrs;  // function is called in CcxSetMiscMsrs. assign stub

        MockSilGetCommon2RevXferTableOnce(&CcxXferZen4, SilPass);  // mock with proper table and status

        CCXCLASS_INPUT_BLK CcxInputBlock = {0};  // 0 initialized argument 
        CcxInputBlock.EnableSvmAVIC = true;      // set to true to enter EnableSvmAVIC branch 
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call CcxSetMiscMsrs and pass zero initialized CcxInputBlock with EnableSvmAVIC set to true");
        CcxSetMiscMsrs (&CcxInputBlock);
        // Assert
    }
    else if(strcmp(IterationName, "SilAborted") == 0)
    {
        // Arrange
        MockSilGetCommon2RevXferTableOnce(NULL, SilAborted); // mock with null table and error status
        
        CCXCLASS_INPUT_BLK CcxInputBlock = {0};  // 0 initialized argument 
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call CcxSetMiscMsrs. Mock CcxXferZen4 table as invalid");
        CcxSetMiscMsrs (&CcxInputBlock);
        // Assert
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
