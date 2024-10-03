/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file FchInitResetAbUt.c
 * @brief Unit tests for FchInitResetAb
 *
 * Iterations:
 *
 * -Default: Executes FchInitResetAb ()
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
#include <Common/FchCore/FchAb/FchAbReg.h>
#include <Common/FchCore/FchAb/FchAb.h>

HOST_DEBUG_SERVICE mHostDebugService = NULL;

void
FchInitResetAb (
  void
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

  uint32_t ExpectedReadValue;
  uint32_t AndMask;
  uint32_t OrMask;


  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp (IterationName, "Default") == 0) {
    ExpectedReadValue = ALINK_ACCESS_INDEX;
    AndMask = 0x00000000;
    OrMask = ALINK_ACCESS_INDEX;
    MockxUSLMemReadModifyWrite32Once (ExpectedReadValue, AndMask, OrMask);
    FchInitResetAb ();
  } else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Iteration '%s' is not implemented.", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
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
