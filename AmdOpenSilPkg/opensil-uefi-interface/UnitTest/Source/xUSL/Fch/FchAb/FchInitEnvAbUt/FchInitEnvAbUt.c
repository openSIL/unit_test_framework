/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file FchInitEnvAbUt.c
 * @brief Unit tests for FchInitEnvAbUt
 *
 * Iterations:
 *
 * -FchAbInputBlkCleared: Execute FchInitEnvAb () with input block cleared
 * -FchAbInputBlkSet: Execute FchInitEnvAb () with input block set
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

#include <Pci.h>
#include <Common/FchCore/FchAb/FchAb.h>
#include <Library/UtxSIMMockLib.h>
#include <Library/UtSilServicesMockLib.h>
#include <FCH/Common/FchCommonCfg.h>

HOST_DEBUG_SERVICE mHostDebugService = NULL;


void
FchInitEnvAb (
  FCHAB_INPUT_BLK *LclInpFchAbBlk
  );

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
  if (UtSilInit() != SilPass) {
    return AMD_UNIT_TEST_ABORTED;
  }
  return AMD_UNIT_TEST_PASSED;
}

void
EFIAPI
TestBody (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut           = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName                  = UtGetTestName (Ut);
  const char* IterationName             = UtGetTestIteration (Ut);
  FCHAB_INPUT_BLK FchAbInputBlk         = {0};

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp (IterationName, "FchAbInputBlkCleared") == 0) {
    // Arrange

    // Act
    FchInitEnvAb (&FchAbInputBlk);

    // Assert - N/A

  } else if (strcmp (IterationName, "FchAbInputBlkSet") == 0) {
    // Arrange
    FchAbInputBlk.ResetCpuOnSyncFlood = TRUE;
    FchAbInputBlk.AbDmaMemoryWrtie3264B = TRUE;
    FchAbInputBlk.AbMemoryPowerSaving  = TRUE;
    FchAbInputBlk.AbClockGating = TRUE;
    FchAbInputBlk.ALinkClkGateOff = TRUE;
    FchAbInputBlk.BLinkClkGateOff = TRUE;
    FchAbInputBlk.SlowSpeedAbLinkClock = 0x1;
    FchAbInputBlk.SbgMemoryPowerSaving = TRUE;
    FchAbInputBlk.SbgClockGating = TRUE;
    FchAbInputBlk.XdmaDmaWrite16ByteMode = TRUE;
    FchAbInputBlk.XdmaMemoryPowerSaving = TRUE;
    FchAbInputBlk.XdmaPendingNprThreshold = 0x1F;
    FchAbInputBlk.XdmaDncplOrderDis = TRUE;
    FchAbInputBlk.SdphostBypassDataPack = TRUE;
    FchAbInputBlk.SdphostDisNpmwrProtect = TRUE;

    // Act
    FchInitEnvAb (&FchAbInputBlk);

    // Assert - N/A

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
  UtSilDeinit ();
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
