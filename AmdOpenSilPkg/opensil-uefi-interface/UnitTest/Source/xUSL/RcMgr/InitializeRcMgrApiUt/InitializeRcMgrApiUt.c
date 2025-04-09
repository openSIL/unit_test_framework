/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file InitializeRcMgrApiUt.c
 * @brief Unit tests for InitializeRcMgrApiUt
 *
 * Iterations:
 *
 */

#include "InitializeRcMgrApiUt.h"

// Stub implementation for FabricReserveMmio.
SIL_STATUS
FabricReserveMmio (
  uint64_t              *BaseAddress,
  uint64_t              *Length,
  uint64_t              Alignment,
  FABRIC_TARGET         Target,
  FABRIC_MMIO_ATTRIBUTE *Attributes
  )
{
  return SilPass;
}

extern RCMGR_IP2IP_API RcMgrApi;

// Mocks rcmgr api.
// RCMGR_IP2IP_API RcMgrApi = {
//     .FabricReserveMmio    = FabricReserveMmio
// };

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

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test started.", TestName, IterationName);

  // Shared variable decalarations for all iterations.
  SIL_STATUS SilStatus;
  SIL_STATUS rc;

  if (strcmp(IterationName, "Ip2ipApiSuccess") == 0) 
  {

    // Arrange
    SilStatus = SilPass;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    MockSilInitIp2IpApiOnce( (void *)&RcMgrApi, SilStatus );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Initialize RcMgr Api is mocked successfully.");
    
    // Act
    rc = InitializeRcMgrApi();
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if ( rc == SilPass )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Asserted successfully.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Asserted unsuccessfully.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 
/*
  else if(strcmp(IterationName, "RootBridgeIsNotFound") == 0) 
  {
    // Arrange
    SilStatus = SilPass;
    DfIp2IpApi.DfGetSystemComponentRootBridgeLocation = DfGetSystemComponentRootBridgeLocationFalse;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    MockSilGetIp2IpApiOnce( (void *)&DfIp2IpApi, SilStatus );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Sil get ip2ip API mocked successfully.");

    SilGetPrimaryRb( &SocketNum, &RootBridgeNum );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if ( !(SocketNum || RootBridgeNum) )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Asserted successfully.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Asserted unsuccessfully.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 
*/
  else 
  {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test ended at the 'else' case; this is a faulty behaviour.", TestName, IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  // UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
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
  AMD_UNIT_TEST_STATUS Status;              // conv.
  AMD_UNIT_TEST_FRAMEWORK Ut;               // conv.

  // Initializing the UnitTest framework    // conv.
  Status = UtInitFromArgs (
    &Ut,
    argc,
    argv
  );
  if (Status != AMD_UNIT_TEST_PASSED) {
    return Status;
  }

  // Logging the start of the test.         // conv.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // Running test.                          // conv.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
