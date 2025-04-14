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

#include "MpioAncDataV1.c"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

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
  if (strcmp(IterationName, "Default") == 0)
  {
    // Arrange
    GNB_HANDLE GnbHandleInstance = {0};
    uint8_t ancillaryDataBuffer[1024] = {0};

    // Create AncData overrides with INVALID TYPE to trigger "continue"
    MPIO_ANC_DATA_PARAM ancParams[3] = {
        {.Type = 0xFF},                      // Invalid type (triggers continue)
        {.Type = ANC_PHY_OVRD, .Value = 1},  // Valid PHY override
        {.Type = ANC_SPEED_OVRD, .Value = 2} // Valid SPD override
    };

    // Create PortList with 3 descriptors
    MPIO_PORT_DESCRIPTOR portList[3] = {0};

    // 1st descriptor: Valid engine + overrides + invalid entry
    portList[0].EngineData.EngineType = MpioPcieEngine;
    portList[0].AncData.Ovrd = (uint32_t)ancParams;
    portList[0].AncData.Count = 3; // Includes invalid type
    portList[0].EngineData.StartLane = 0;
    portList[0].EngineData.EndLane = 1;

    // 2nd descriptor: Valid engine but ZERO overrides
    portList[1].EngineData.EngineType = MpioSATAEngine;
    portList[1].AncData.Ovrd = 0; // Tests Ovrd == 0 branch

    // 3rd descriptor: Terminate list
    portList[2].Flags = DESCRIPTOR_TERMINATE_LIST;

    // ACT
    uint32_t result = MpioAddAncDataOverride(&GnbHandleInstance, ancillaryDataBuffer, portList);

    // ASSERT
    if (result > 0)
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
