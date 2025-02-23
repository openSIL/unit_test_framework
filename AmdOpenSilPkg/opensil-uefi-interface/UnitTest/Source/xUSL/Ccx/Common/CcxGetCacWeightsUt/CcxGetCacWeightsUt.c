/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file CcxGetCacWeightsUt.c
 * @brief
 *
 */

#include <CcxGetCacWeightsUt.h>

HOST_DEBUG_SERVICE mHostDebugService = NULL;

SMU_IP2IP_API SmuApi = {
  .Header                   =      {
      .IpId         = SilId_SmuClass,
      .IpVersion    = 13,
    },  
  .SmuServiceInitArguments  =     NULL,
  .SmuServiceRequest        =     NULL,
  .SmuFirmwareTest          =     NULL,
  .DxioServiceRequest       =     NULL,
  .SmuNotifyS3Entry         =     NULL,
  .SmuGetGnbHandle          =     NULL,
  .SmuReadBrandString       =     NULL,
  .SmuLaunchThread          =     NULL,
  .SmuReadBistInfo          =     NULL,
  .SmuReadCacWeights        =     SmuReadCacWeightsUt,
  .SmuRegisterRead          =     NULL,
  .SmuRegisterWrite         =     NULL,
  .SmuRegisterRMW           =     NULL,
  .SmuDisableSmt            =     NULL,
  .SmuGetOpnCorePresence    =     NULL,
  .SmuGetOpnCorePresenceEx  =     NULL
};

SIL_STATUS 
SmuReadCacWeightsUt (
  uint32_t  MaxNumWeights,
  uint64_t  *ApmWeights
  )
{
  return SilPass; 
}

void
xUslMsrAndThenOr (
  uint32_t Index,
  uint64_t AndData,
  uint64_t OrData
  )
{
  return;
}

uint64_t 
xUslRdMsr (
  uint32_t MsrAddress
  )
{
  return 0;
}

void 
xUslWrMsr (
  uint32_t MsrAddress, 
  uint64_t MsrValue
  )

{
  return;
}

void 
xUslMsrOr (
  uint32_t Index, 
  uint64_t OrData)
{
  return;
}

void 
xUslMsrAnd (
  uint32_t Index, 
  uint64_t AndData
  )
{
  return;
}

bool 
xUslIsComputeUnitPrimary (
  void
  ) 
{
  return TRUE;
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

  SIL_STATUS           SilStatus;
  uint64_t CacWeightsGet[MAX_CAC_WEIGHT_NUM] = {0};
  
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp (IterationName, "SilPass") == 0) {
    // Arrange 
    MockSilGetIp2IpApiOnce((void *)&SmuApi, SilPass);

    // Act  
    SilStatus = CcxGetCacWeights(CacWeightsGet);

    // Assert
    if (SilStatus != SilPass){
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Did not receive SilPass", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    } else {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Receive SilPass", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }

  } else if (strcmp (IterationName, "SilAborted") == 0) {
    // Arrange 
    MockSilGetIp2IpApiOnce(NULL, SilAborted);

    // Act  
    SilStatus = CcxGetCacWeights(CacWeightsGet);

    // Assert 
    if (SilStatus != SilAborted) {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Did not receive SilAborted", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    } else {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Receive SilAborted", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
  } else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Iteration '%s' is not implemented.", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

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

  // char *SimpleCharContext = "A simple TestBody context";

  // Logging the start of the test.
  // Note: Test status at this time is set to "NOT_SET".
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // You can pass into the TestPrerequisite, TestBody, and TestCleanUp context of
  // your desire
  // UtSetTestContext (&Ut, (AMD_UNIT_TEST_CONTEXT)SimpleCharContext);

  // Running the test
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
