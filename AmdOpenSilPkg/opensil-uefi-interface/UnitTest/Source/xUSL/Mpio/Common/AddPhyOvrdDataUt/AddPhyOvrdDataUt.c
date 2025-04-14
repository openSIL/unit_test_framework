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

  if (strcmp(IterationName, "HeaderAddrIsNotNull"))
  {
    // Arrange
    // Pre-initialize the header (simulate a prior call to AddPhyOvrdData)
    uint8_t buffer[sizeof(ANC_PHY_OVRD_HEADER) + sizeof(ANC_PHY_OVRD_DATA)] = {0};
    ANC_PHY_OVRD_HEADER *existingHeader = (ANC_PHY_OVRD_HEADER *)buffer;
    existingHeader->type = ANC_PHY_OVRD;
    existingHeader->id = 1; // Assume prior ID increment
    existingHeader->phytype = E32;

    uint8_t *dataEntry = buffer + sizeof(ANC_PHY_OVRD_HEADER); // Start after the header
    ANC_PHY_OVRD_HEADER *headerAddr = existingHeader;          // Header already exists
    uint32_t value = 0xAABBCCDD;
    uint8_t id = 1; // ID is not incremented in this path

    // Act
    uint32_t dataSize = AddPhyOvrdData(&dataEntry, &headerAddr, value, &id);

    // Assert
    if (dataSize == sizeof(ANC_PHY_OVRD_DATA) &&
        headerAddr == existingHeader && // Header address remains unchanged
        ((ANC_PHY_OVRD_DATA *)(dataEntry - sizeof(ANC_PHY_OVRD_DATA)))->PhyOverride == value &&
        id == 1)
    { // ID should NOT increment here
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
  }
  else if (strcmp(IterationName, "HeaderAddrIsNull"))
  {
    // Arrange
    uint8_t buffer[sizeof(ANC_PHY_OVRD_HEADER) + sizeof(ANC_PHY_OVRD_DATA)] = {0};
    uint8_t *dataEntry = buffer;
    ANC_PHY_OVRD_HEADER *headerAddr = NULL;
    uint32_t value = 0x12345678;
    uint8_t id = 0;

    // Act
    uint32_t dataSize = AddPhyOvrdData(&dataEntry, &headerAddr, value, &id);

    // Assert
    if (dataSize == sizeof(ANC_PHY_OVRD_HEADER) + sizeof(ANC_PHY_OVRD_DATA) &&
        headerAddr != NULL &&
        headerAddr->type == ANC_PHY_OVRD &&
        headerAddr->id == 0 &&
        headerAddr->phytype == E32 &&
        ((ANC_PHY_OVRD_DATA *)(dataEntry - sizeof(ANC_PHY_OVRD_DATA)))->PhyOverride == value &&
        id == 1)
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
