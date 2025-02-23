/**
 * @file CcxInitializeCpbUt.c
 * @brief Unit tests for CcxInitializeCpbUt
 *
 * Iterations:
 *
 * -Default: Executes CcxInitializeCpbUt(intuint8_t)
 */

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>
#include <Library/UtMsrRegStubLib.h>

#include <xSIM.h> 
#include <Ccx.h>
#include <MsrReg.h>

// Stubs 
bool xUslIsComputeUnitPrimary (
    void
    )
{
    return true;
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

    uint8_t CpbEnable; 
    // Iterations:
    if(strcmp(IterationName, "CpbEnableTrue") == 0)
    {
        // Arrange
        CpbEnable = 1; 
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__,
            "Call CcxInitializeCpb and pass 1 value");
        CcxInitializeCpb(CpbEnable);
        // Assert
        // The function is void 
    }
    else if(strcmp(IterationName, "CpbEnableFalse") == 0)
    {
        // Arrange
        CpbEnable = 0; 
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call CcxInitializeCpb and pass 0 value");
        CcxInitializeCpb(CpbEnable);
        // Assert
        // The function is void 
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

