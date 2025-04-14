/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file DfGetSystemComponentUt.c
 * @brief
 *
 */

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <stdlib.h>

#include <xSIM.h> // Seems to be needed for UtSilServicesMockLib.h, otherwise the build fails
#include <Library/UtSilServicesMockLib.h>

#include <string.h>
#include <xSIM.h>
#include <SilSocLogicalId.h>
#include <Mpio/Common/Deli.h>
#include <NBIO/NbioIp2Ip.h>
#include <SMU/SmuIp2Ip.h>
#include "MpioInitLib.h"
#include "MpioCmn2Rev.h"
#include "MpioLibLocal.h"
#include "MpioStructs.h"
#include "MpioLib.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;
const int socketId = 2;
MPIOCLASS_INPUT_BLK SilData;

/*
  Mock function for the NbioIp2IpApi.
  PcieConfigRunProcForAllWrappers, PcieConfigRunProcForAllEngines, and NbioGetHandle are also used
  as is by the source file of the function under test.
*/
void PcieConfigDebugDump(
    PCIe_PLATFORM_CONFIG *Pcie)
{
  return;
}

SIL_STATUS PcieConfigRunProcForAllWrappers(
    uint32_t DescriptorFlags,
    PCIe_RUN_ON_WRAPPER_CALLBACK Callback,
    void *Buffer,
    PCIe_PLATFORM_CONFIG *Pcie)
{
  return SilPass;
}

void PcieConfigRunProcForAllEngines(
    uint32_t DescriptorFlags,
    PCIe_RUN_ON_ENGINE_CALLBACK Callback,
    void *Buffer,
    PCIe_PLATFORM_CONFIG *Pcie)
{
  return;
}

GNB_HANDLE *NbioGetHandle(PCIe_PLATFORM_CONFIG *Pcie)
{
  GNB_HANDLE *gnb_handle = malloc(sizeof(GNB_HANDLE));
  gnb_handle[0].SocketId = 2;
  gnb_handle[0].Header.DescriptorFlags = DESCRIPTOR_TERMINATE_TOPOLOGY;
  return gnb_handle;
}

/*
Mock function for the Xfer table
*/
void initBusRangesAndAriUt(
    GNB_HANDLE *GnbHandle,
    PCIe_PLATFORM_CONFIG *Pcie,
    bool CfgPcieAriSupport)
{
  return;
}

/*
Other functions being used by the source file of the function being tested.
*/
uint32_t xUslGetPackageType(void)
{
  return 1;
}

void *SilFindStructure(
    SIL_DATA_BLOCK_ID structureID,
    uint16_t InstanceNum)
{
  return &SilData;
};

void MpioManageTopology(
    MPIO_COMPLEX_DESCRIPTOR *ComplexDescriptor)
{
  return;
}

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

  if (strcmp(IterationName, "Default") == 0)
  {
    // Arrange
    MPIO_COMMON_2_REV_XFER_BLOCK xferTable = {
        .InitBusRangesAndAri = initBusRangesAndAriUt,
        .PcieCommonCoreConfiguration = NULL,
        .PcieCommonEngineGetDeliInfo = NULL,
        .PcieCommonCoreConfiguration = NULL};
    NBIO_IP2IP_API nbioIp2IpApi = {
        .PcieConfigDebugDump = PcieConfigDebugDump,
        .PcieConfigRunProcForAllEngines = PcieConfigRunProcForAllEngines,
        .PcieConfigRunProcForAllWrappers = PcieConfigRunProcForAllWrappers,
        .NbioGetHandle = NbioGetHandle};
    MockSilGetCommon2RevXferTableOnce(&xferTable, SilPass);
    MockSilGetIp2IpApiOnce(&nbioIp2IpApi, SilPass);
    PCIe_PLATFORM_CONFIG Pcie;

    // Act
    MpioCfgAfterDxioInit(&Pcie);

    // Nothing to assert
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  }
  else if (strcmp(IterationName, "NoXferTable") == 0)
  {
    MockSilGetCommon2RevXferTableOnce(NULL, SilNotFound);
    PCIe_PLATFORM_CONFIG Pcie;

    // Act
    MpioCfgAfterDxioInit(&Pcie);

    // Nothing to assert
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  }
  else if (strcmp(IterationName, "NoIp2IpApi") == 0)
  {
    // Arrange
    MPIO_COMMON_2_REV_XFER_BLOCK xferTable = {
        .InitBusRangesAndAri = initBusRangesAndAriUt,
        .PcieCommonCoreConfiguration = NULL,
        .PcieCommonEngineGetDeliInfo = NULL,
        .PcieCommonCoreConfiguration = NULL};
    MockSilGetCommon2RevXferTableOnce(&xferTable, SilPass);
    MockSilGetIp2IpApiOnce(NULL, SilNotFound);
    PCIe_PLATFORM_CONFIG Pcie;

    // Act
    MpioCfgAfterDxioInit(&Pcie);

    // Nothing to assert
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  }
  else
  {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Iteration '%s' is not implemented.", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_ABORTED);
  }

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
