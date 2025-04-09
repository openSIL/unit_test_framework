/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file CcxSetCacWeightsUt.c
 * @brief Unit tests for CcxSetCacWeightsUt
 *
 * Iterations:
 *
 * -CacWeightsNull: This Iteration will take in uint64_t array of nullptr.
 * -CacWeightsSize15: This Iteration will take in uint64_t array of size 15.
 * -CacWeightsSize23: This Iteration will take in uint64_t array of size MAX_CAC_WEIGHT_NUM.
 */

#include "CcxGetCacWeightsUt.h"

SIL_STATUS
SmuReadCacWeightsUt (
  uint32_t MaxNumWeights,
  uint64_t *ApmWeights
)
{
  return SilPass;
};

// prerequisuite begins
AMD_UNIT_TEST_STATUS
EFIAPI
TestPrerequisite (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  return AMD_UNIT_TEST_PASSED;
}

// body begins
void
EFIAPI
TestBody (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName        = UtGetTestName (Ut);
  const char* IterationName   = UtGetTestIteration (Ut);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp(IterationName, "GetCacWeightsAborted") == 0) {

    // Arrange
    // SMU_IP2IP_API *SmuApiVoid = NULL;
    uint64_t CacWeights[MAX_CAC_WEIGHT_NUM] = {0};

    // Act
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Calling CcxGetCacWeights assuming SmuApi vector table is NULL.");
    MockSilGetIp2IpApiOnce(NULL, SilAborted);
    SIL_STATUS rc = CcxGetCacWeights(CacWeights);

    // Assert
    if (rc == SilAborted) {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "%s (Iteration: %s) test ended.", TestName, IterationName);
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    } 
    else {
      Ut->Log(AMD_UNIT_TEST_ABORTED, __FUNCTION__, __LINE__, "Iteration '%s' expects null transfer table, but there are data found within.");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_ABORTED);
    }

  } else if(strcmp(IterationName, "GetCacWeightsPass") == 0) {

    // Arrange
    uint64_t CacWeights[MAX_CAC_WEIGHT_NUM] = {0};

    // instantiates the vector table globally as a null vector
    SMU_IP2IP_API SmuApi = {
      .Header                     = {
        .IpId                     = SilId_SmuClass,
        .IpVersion                = 13,
      },
      .SmuServiceInitArguments    = NULL,
      .SmuServiceRequest          = NULL,
      .SmuFirmwareTest            = NULL,
      .DxioServiceRequest         = NULL,
      .SmuNotifyS3Entry           = NULL,
      .SmuGetGnbHandle            = NULL,
      .SmuReadBrandString         = NULL,
      .SmuLaunchThread            = NULL,
      .SmuReadBistInfo            = NULL,
      .SmuReadCacWeights          = SmuReadCacWeightsUt,
      .SmuRegisterRead            = NULL,
      .SmuRegisterWrite           = NULL,
      .SmuRegisterRMW             = NULL,
      .SmuDisableSmt              = NULL,
      .SmuGetOpnCorePresence      = NULL,
      .SmuGetOpnCorePresenceEx    = NULL
    };

    // Act
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Calling CcxSetCacWeights with weight vector of 23 (MAX_CAC_WEIGHT_NUM) elements.");
    MockSilGetIp2IpApiOnce((void *)&SmuApi, SilPass);
    SIL_STATUS rc = CcxGetCacWeights(CacWeights);
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "\nrc=%d.", rc);

    // Assert
    if (rc == SilPass) {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "%s (Iteration: %s) test ended.", TestName, IterationName);
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
    else {
      Ut->Log(AMD_UNIT_TEST_ABORTED, __FUNCTION__, __LINE__, "Iteration '%s' expects SilPass, but exhibits SilAborted instead.");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_ABORTED);
    }

  } else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "Iteration: %s is not implemented.", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
  }

  Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "%s (Iteration: %s) test ended.", TestName, IterationName);
  UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
}

// cleanup begins
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
