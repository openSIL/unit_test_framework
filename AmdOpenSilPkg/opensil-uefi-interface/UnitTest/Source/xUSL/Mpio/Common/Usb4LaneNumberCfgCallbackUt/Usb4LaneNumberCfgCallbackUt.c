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

uint32_t xUslGetPackageType(void)
{
  return 1;
}

void *
SilFindStructure(
    SIL_DATA_BLOCK_ID structureID,
    uint16_t InstanceNum)
{
  return xUslFindStructure(structureID, InstanceNum);
};

GNB_HANDLE *NbioGetHandle(PCIe_PLATFORM_CONFIG *Pcie)
{

  return NULL;
}

void MpioManageTopology(
    MPIO_COMPLEX_DESCRIPTOR *ComplexDescriptor)
{

  return;
}

void PcieConfigRunProcForAllEngines(
    uint32_t DescriptorFlags,
    PCIe_RUN_ON_ENGINE_CALLBACK Callback,
    void *Buffer,
    PCIe_PLATFORM_CONFIG *Pcie)
{
  return;
}

NBIO_IP2IP_API ip2ipMock = {
    .PcieConfigRunProcForAllEngines = PcieConfigRunProcForAllEngines};

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

  if (strcmp(IterationName, "ReturnsSilUnsupported") == 0)
  {
    // Arrange
    SIL_STATUS status;
    uint8_t counter = 0;
    FW_ASK_STRUCT *AskEntry = NULL;
    MPIO_PORT_DESCRIPTOR *TopologyEntry = NULL;

    // Act
    status = Usb4LaneNumberCfgCallback(counter, AskEntry, TopologyEntry);

    // Assert inapplicable, set to pass
    if (status == SilUnsupported)
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
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
