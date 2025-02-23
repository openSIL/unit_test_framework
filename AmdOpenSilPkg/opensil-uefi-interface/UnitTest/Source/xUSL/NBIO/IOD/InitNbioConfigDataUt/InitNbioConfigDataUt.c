/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file InitNbioConfigDataUt.c
 * @brief
 *
 */

#include "InitNbioConfigDataUt.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

NBIOCLASS_DATA mNbioIpBlockData;
NBIO_CONFIG_DATA mNbioConfigData;

// Mock
uint32_t
xUSLSmnRead (
  uint32_t SegmentNumber,
  uint32_t IohcBus,
  uint32_t SmnAddress
  )
{
  return (uint32_t)(0xAA << 24);
}


AMD_UNIT_TEST_STATUS
EFIAPI
TestPrerequisite (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_STATUS Status = AMD_UNIT_TEST_PASSED;
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName        = UtGetTestName (Ut);
  const char* IterationName   = UtGetTestIteration (Ut);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Prerequisite started.", TestName, IterationName);

  Status = UtSilInit ();
  if (Status != AMD_UNIT_TEST_PASSED) {
    return AMD_UNIT_TEST_ABORTED;
  }
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Prerequisite ended.", TestName, IterationName);
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

  if (strcmp (IterationName, "InitDataSuccess") == 0) {
      // Arrange
      mNbioIpBlockData.NbioConfigData = &mNbioConfigData;
      mNbioConfigData.OpnSpare = 0;  // Initialize to known value

      // Action
      InitNbioConfigData();

      // Assert
      if (mNbioConfigData.OpnSpare == 0xAA) {  // Should match the mock xUSLSmnRead return value
        Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "Iteration '%s' test passed", IterationName);
        UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
      } else {
        Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
          "OpnSpare value mismatch. Expected: 0xAA, Got: 0x%x", mNbioConfigData.OpnSpare);
        UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
      }
  }else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Iteration '%s' test failed", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test ended.", TestName, IterationName);
}

AMD_UNIT_TEST_STATUS
EFIAPI
TestCleanUp (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName        = UtGetTestName (Ut);
  const char* IterationName   = UtGetTestIteration (Ut);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) CleanUp started.", TestName, IterationName);
  // Free openSIL allocated memory
  UtSilDeinit ();
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) CleanUp ended.", TestName, IterationName);
  return AMD_UNIT_TEST_PASSED;
}


/**
 * main
 * @brief      Stating point for Execution
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
  // Note: Test status at this time is set to "NOT_SET".
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // Running the test
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
