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
  if (strcmp(IterationName, "NoOvrdPresent") == 0)
  {
    // Arrange
    MPIO_PORT_DESCRIPTOR Port = {0};
    Port.AncData.Ovrd = 0;

    // Act
    uint32_t Size = GetPortAncDataTypeSize(0, &Port);

    // ASSERT
    if (Size == 0)
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
  }
  else if (strcmp(IterationName, "PhyOvrdPresent"))
  {
    // Arrange
    MPIO_ANC_DATA_PARAM AncParams[1] = {{ANC_PHY_OVRD, 0}};
    MPIO_PORT_DESCRIPTOR Port = {0};
    Port.AncData.Ovrd = (uint32_t)(uintptr_t)AncParams;
    Port.AncData.Count = 1;

    // Act
    uint32_t Size = GetPortAncDataTypeSize(ANC_PHY_OVRD, &Port);

    // ASSERT
    if (Size == sizeof(ANC_PHY_OVRD_DATA))
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
  }
  else if (strcmp(IterationName, "SpdOvrdPresent"))
  {
    // Arrange
    MPIO_ANC_DATA_PARAM AncParams[1] = {{ANC_SPEED_OVRD, 0}};
    MPIO_PORT_DESCRIPTOR Port = {0};
    Port.AncData.Ovrd = (uint32_t)(uintptr_t)AncParams;
    Port.AncData.Count = 1;

    // Act
    uint32_t Size = GetPortAncDataTypeSize(ANC_SPEED_OVRD, &Port);

    // ASSERT
    if (Size == sizeof(ANC_SPD_OVRD_DATA))
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
