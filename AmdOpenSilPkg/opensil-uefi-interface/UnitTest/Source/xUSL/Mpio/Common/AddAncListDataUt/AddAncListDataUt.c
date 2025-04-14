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
  if (strcmp(IterationName, "PhyHeaderofsIsZero") == 0)
  {
    // Arrange
    uint8_t buffer[sizeof(ANC_LIST_TYPE) + sizeof(ANC_DATA_LIST)] = {0};
    uint8_t *dataEntry = buffer;
    uint16_t phyHeaderofs = 0x1234;
    uint16_t spdHeaderofs = 0x5678;
    uint8_t id = 0xAB;
    uint32_t expectedSize = sizeof(ANC_LIST_TYPE) + sizeof(ANC_DATA_LIST);

    // Act
    uint32_t result = AddAncListData(&dataEntry, phyHeaderofs, spdHeaderofs, id);

    // ASSERT
    if (result == expectedSize &&
        ((ANC_LIST_TYPE *)buffer)->type == ANC_LIST &&
        ((ANC_LIST_TYPE *)buffer)->id == id &&
        ((ANC_LIST_TYPE *)buffer)->length == 2 &&
        ((ANC_DATA_LIST *)(buffer + sizeof(ANC_LIST_TYPE)))->ElementOfs0 == phyHeaderofs &&
        ((ANC_DATA_LIST *)(buffer + sizeof(ANC_LIST_TYPE)))->ElementOfs1 == spdHeaderofs)
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
  }
  else if (strcmp(IterationName, "PhyHeaderofsIsNonZero") == 0)
  {
    // Arrange
    uint8_t buffer[sizeof(ANC_LIST_TYPE) + sizeof(ANC_DATA_LIST)] = {0};
    uint8_t *dataEntry = buffer;
    uint16_t phyHeaderofs = 0;
    uint16_t spdHeaderofs = 0x9ABC;
    uint8_t id = 0xCD;
    uint32_t expectedSize = sizeof(ANC_LIST_TYPE) + sizeof(ANC_DATA_LIST);

    // Act
    uint32_t result = AddAncListData(&dataEntry, phyHeaderofs, spdHeaderofs, id);

    // ASSERT
    if (result == expectedSize &&
        ((ANC_LIST_TYPE *)buffer)->type == ANC_LIST &&
        ((ANC_LIST_TYPE *)buffer)->id == id &&
        ((ANC_LIST_TYPE *)buffer)->length == 2 &&
        ((ANC_DATA_LIST *)(buffer + sizeof(ANC_LIST_TYPE)))->ElementOfs0 == spdHeaderofs)
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
