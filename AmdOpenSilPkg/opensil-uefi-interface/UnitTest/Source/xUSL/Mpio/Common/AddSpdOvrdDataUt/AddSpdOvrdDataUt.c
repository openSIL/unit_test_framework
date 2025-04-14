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

  if (strcmp(IterationName, "HeaderAddrIsNotNull") == 0)
  {
    // Arrange
    uint8_t buffer[sizeof(ANC_SPD_OVRD_HEADER) + sizeof(ANC_SPD_OVRD_DATA)];
    ANC_SPD_OVRD_HEADER *existingHeader = (ANC_SPD_OVRD_HEADER *)buffer;
    existingHeader->type = ANC_SPEED_OVRD;
    existingHeader->lane = 3;
    existingHeader->ovrdtype = 4;
    uint8_t *dataEntry = buffer + sizeof(ANC_SPD_OVRD_HEADER);
    uint32_t value = 0x87654321;
    uint8_t lane = 5;
    uint8_t ovrdType = 6;

    // ACT
    uint32_t dataSize = AddSpdOvrdData(&dataEntry, &existingHeader, value, lane, ovrdType);

    // ASSERT
    if (existingHeader->type == ANC_SPEED_OVRD &&
        existingHeader->lane == 3 &&
        existingHeader->ovrdtype == 4 &&
        dataEntry == buffer + sizeof(ANC_SPD_OVRD_HEADER) + sizeof(ANC_SPD_OVRD_DATA) &&
        dataSize == sizeof(ANC_SPD_OVRD_DATA) &&
        ((ANC_SPD_OVRD_DATA *)(buffer + sizeof(ANC_SPD_OVRD_HEADER)))->Value == value)
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
  }
  else if (strcmp(IterationName, "HeaderAddrIsNull") == 0)
  {
    // Arrange
    uint8_t buffer[sizeof(ANC_SPD_OVRD_HEADER) + sizeof(ANC_SPD_OVRD_DATA)];
    uint8_t *dataEntry = buffer;
    ANC_SPD_OVRD_HEADER *header = NULL;
    uint32_t value = 0x12345678;
    uint8_t lane = 1;
    uint8_t ovrdType = 2;

    // ACT
    uint32_t dataSize = AddSpdOvrdData(&dataEntry, &header, value, lane, ovrdType);

    // ASSERT
    if (header == (ANC_SPD_OVRD_HEADER *)buffer &&
        header->type == ANC_SPEED_OVRD &&
        header->lane == lane &&
        header->ovrdtype == ovrdType &&
        dataEntry == buffer + sizeof(ANC_SPD_OVRD_HEADER) + sizeof(ANC_SPD_OVRD_DATA) &&
        dataSize == sizeof(ANC_SPD_OVRD_HEADER) + sizeof(ANC_SPD_OVRD_DATA))
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
