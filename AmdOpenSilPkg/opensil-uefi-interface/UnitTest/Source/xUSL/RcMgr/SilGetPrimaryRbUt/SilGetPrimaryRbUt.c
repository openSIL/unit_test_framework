/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file SilGetPrimaryRbUt.c
 * @brief Unit tests for SilGetPrimaryRbUt
 *
 * Iterations:
 *
 */

#include "SilGetPrimaryRbUt.h"

// Stub implementation for DfGetSystemComponentRootBridgeLocation; true case.
bool
DfGetSystemComponentRootBridgeLocationTrue (
  COMPONENT_TYPE Component,
  ROOT_BRIDGE_LOCATION *Location
  )
{
  Location->Die     = 1;
  Location->Index   = 1;
  Location->Socket  = 1;
  return true;
}

// Stub implementation for DfGetSystemComponentRootBridgeLocation; false case.
bool
DfGetSystemComponentRootBridgeLocationFalse (
  COMPONENT_TYPE Component,
  ROOT_BRIDGE_LOCATION *Location
  )
{
  Location->Die     = 0;
  Location->Index   = 0;
  Location->Socket  = 0;
  return false;
}

// Mocks df ip 2 ip API
static DF_IP2IP_API DfIp2IpApi = {
  .DfGetNumberOfProcessorsPresent =             NULL,
  .DfGetNumberOfSystemDies =                    NULL,
  .DfGetNumberOfSystemRootBridges =             NULL,
  .DfGetNumberOfRootBridgesOnSocket =           NULL,
  .DfGetNumberOfRootBridgesOnDie =              NULL,
  .DfGetDieSystemOffset =                       NULL,
  .DfGetDeviceMapOnDie =                        NULL,
  .DfGetHostBridgeBusBase =                     NULL,
  .DfGetHostBridgeBusLimit =                    NULL,
  .DfGetPhysRootBridgeNumber =                  NULL,
  .DfGetNumberOfDiesOnSocket =                  NULL,
  .DfGetHostBridgeSystemFabricID =              NULL,
  .DfGetSystemComponentRootBridgeLocation =     NULL,
  .DfHasFch =                                   NULL,
  .DfHasSmu =                                   NULL,
  .DfFindDeviceTypeEntryInMap =                 NULL,
  .DfFabricRegisterAccRead =                    NULL,
  .DfFabricRegisterAccWrite =                   NULL,
  .DfGetWdtInfo =                               NULL,
  .DfGetRootBridgeInfo =                        NULL,
  .DfGetDieInfo =                               NULL,
  .DfGetProcessorInfo =                         NULL,
  .DfGetSystemInfo =                            NULL,
  .DfDomainXlat =                               NULL,
};

// Stub implementation for FabricReserveMmio
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

// Mocks rcmgr ip2ip API
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
  uint32_t SocketNum     = 0;
  uint32_t RootBridgeNum = 0;
  SIL_STATUS SilStatus;

  if (strcmp(IterationName, "RootBridgeIsFound") == 0) {

    // Arrange
    SilStatus = SilPass;
    DfIp2IpApi.DfGetSystemComponentRootBridgeLocation = DfGetSystemComponentRootBridgeLocationTrue;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    MockSilGetIp2IpApiOnce( (void *)&DfIp2IpApi, SilStatus );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Sil get ip2ip API mocked successfully.");

    SilGetPrimaryRb( &SocketNum, &RootBridgeNum );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if ( SocketNum && RootBridgeNum )
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
  else 
  {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test ended at the 'else' case; this is a faulty behaviour.", TestName, IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
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
