/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file DfGetHostBridgeSystemFabricIDUt.c
 * @brief
 *
 */

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <xSIM.h>
#include <DF/Df.h>
#include <Library/UtSilServicesMockLib.h>
#include <DF/Common/SilBaseFabricTopologyLib.h>
#include "BaseFabricTopologyCmn.h"
#include "DfCmn2Rev.h"

#define FABRIC_ID 4
#define GET_DIE_SYSTEM_OFFSET_UT_RETURN_VALUE 4

const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *GetDeviceMapOnDieUt(
    void)
{
  static const DEVICE_IDS IDs = {.FabricID = FABRIC_ID};
  static AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP deviceMap = {
      .Type = Ios, ///< Type
      .Count = 1,  ///< Count
      .IDs = &IDs, ///< Device IDs
  };
  return &deviceMap;
}

uint32_t GetDieSystemOffsetUt(
    uint32_t Socket)
{
  return GET_DIE_SYSTEM_OFFSET_UT_RETURN_VALUE;
}

HOST_DEBUG_SERVICE mHostDebugService = NULL;

DF_COMMON_2_REV_XFER_BLOCK DfCmn2RevXfer = {
    .DfFabricRegisterAccRead = NULL,
    .DfFabricRegisterAccWrite = NULL,
    .DfGetNumberOfProcessorsPresent = NULL,
    .DfGetNumberOfSystemDies = NULL,
    .DfGetNumberOfSystemRootBridges = NULL,
    .DfGetNumberOfRootBridgesOnSocket = NULL,
    .DfGetNumberOfRootBridgesOnDie = NULL,
    .DfGetDieSystemOffset = GetDieSystemOffsetUt,
    .DfGetDeviceMapOnDie = GetDeviceMapOnDieUt,
    .DfGetHostBridgeBusBase = NULL,
    .DfGetHostBridgeBusLimit = NULL,
    .DfGetPhysRootBridgeNumber = NULL,
    .DfFindComponentLocationMap = NULL,
    .DfBaseFabricTopologyConstructor = NULL,
    .DfBuildDomainInfo = NULL};

AMD_UNIT_TEST_STATUS
EFIAPI
TestPrerequisite(
    IN AMD_UNIT_TEST_CONTEXT Context)
{
  return AMD_UNIT_TEST_PASSED;
}

void
    EFIAPI
    TestBody(
        IN AMD_UNIT_TEST_CONTEXT Context)
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK *)UtGetActiveFrameworkHandle();
  const char *TestName = UtGetTestName(Ut);
  const char *IterationName = UtGetTestIteration(Ut);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) Test started.", TestName, IterationName);

  // Iteration name to be named
  if (strcmp(IterationName, "PositiveTest") == 0)
  {
    // Arrange
    SIL_STATUS Status = SilPass;
    MockSilGetCommon2RevXferTableManyTimes(&DfCmn2RevXfer, Status, 2);

    // Act
    uint32_t result = DfGetHostBridgeSystemFabricID(0, 0);

    // Assert
    if (result != FABRIC_ID + GET_DIE_SYSTEM_OFFSET_UT_RETURN_VALUE)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
              "Incorrect return value.");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
  }
  else
  {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Iteration '%s' is not implemented.", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_ABORTED);
  }
  
  UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) Test ended.", TestName, IterationName);
}

AMD_UNIT_TEST_STATUS
EFIAPI
TestCleanUp(
    IN AMD_UNIT_TEST_CONTEXT Context)
{
  return AMD_UNIT_TEST_PASSED;
}

int main(
    int argc,
    char *argv[])
{
  AMD_UNIT_TEST_STATUS Status;
  AMD_UNIT_TEST_FRAMEWORK Ut;

  // Initializing the UnitTest framework
  Status = UtInitFromArgs(
      &Ut,
      argc,
      argv);
  if (Status != AMD_UNIT_TEST_PASSED)
  {
    return Status;
  }

  // Logging the start of the test.
  // Note: Test status at this time is set to "NOT_SET".
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
         "Test %s started. TestStatus is %s.", UtGetTestName(&Ut), UtGetTestStatusString(&Ut));

  // Running the test
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest(&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName(&Ut));
  UtDeinit(&Ut);

  return AMD_UNIT_TEST_PASSED;
}
