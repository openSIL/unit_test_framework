/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file FchAbSetInputBlkUt.c
 * @brief Unit tests for FchAbSetInputBlk
 *
 * Iterations:
 *
 * -SilPass:    Executes FchAbSetInputBlk () and successfully returns SilPass
 * -SilAborted: Executes FchAbSetInputBlk () and successfully returns SilAborted
 */

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <xSIM.h>
#include <Io.h>
#include <Mmio.h>
#include <SmnAccess.h>
#include <UtLogLib.h>
#include <stdlib.h>
#include <time.h>
#include <Common/FchCore/FchAb/FchAb.h>
#include <Library/UtxSIMMockLib.h>

HOST_DEBUG_SERVICE mHostDebugService = NULL;

uint8_t  TempBlock[0x1000] = {0};

void
xUSLSmnReadModifyWrite (
  uint32_t SegmentNumber,
  uint32_t IohcBus,
  uint32_t SmnAddress,
  uint32_t AndMask,
  uint32_t OrMask
  );

void
SilFchWritePmio (
  uint8_t Address,
  uint8_t AccessWidth,
  uint8_t *Values
  )
{
  return;
}

uint32_t
ReadAlink (
  uint32_t Index
  )
{
  return 0x0;
}

void
WriteAlink (
  uint32_t Index,
  uint32_t Data
  )
{
  return;
}

void
RwAlink (
  uint32_t Index,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  return;
}

void
FchGetAcpiMmioBase (
  uint32_t *AcpiMmioBase
  )
{
  *AcpiMmioBase = 0xFED80000;
}

void*
SilFindStructure (
  SIL_DATA_BLOCK_ID structureID,
  uint16_t          InstanceNum
  )
{
  return xUslFindStructure (structureID, InstanceNum);
}

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

  SIL_STATUS           SilStatus;

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp (IterationName, "SilPass") == 0) {
    // Arrange
    MockSilCreateInfoBlockOnce ((void *)TempBlock);

    // Act
    SilStatus = FchAbSetInputBlk ();

    // Assert
    if (SilStatus != SilPass) {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Did not receive SilPass", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    } else {
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
  } else if (strcmp (IterationName, "SilAborted") == 0) {
    // Arrange
    MockSilCreateInfoBlockOnce (NULL);

    // Act
    SilStatus = FchAbSetInputBlk ();

    // Assert
    if (SilStatus != SilAborted) {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Did not receive SilAborted", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    } else {
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
  } else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Iteration '%s' is not implemented.", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test ended.", TestName, IterationName);
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
  AMD_UNIT_TEST_STATUS Status;
  AMD_UNIT_TEST_FRAMEWORK Ut;

  // Initializing the UnitTest framework
  Status = UtInitFromArgs (
    &Ut,
    argc,
    argv
  );
  if (Status != AMD_UNIT_TEST_PASSED) {
    return Status;
  }

  // Logging the start of the test.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // Running test.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
