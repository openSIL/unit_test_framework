/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file InitializeResourceManagerDfXTp3Ut.c
 * @brief Unit tests for InitializeResourceManagerDfXTp3Ut
 *
 * Iterations: ["SilPass"]
 *
 */

#include "InitializeResourceManagerDfXTp3Ut.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

/* Stubs for resolving the unresolved external symbols. */
void*
SilFindStructure (
  SIL_DATA_BLOCK_ID  StructureID,
  uint16_t InstanceNum
  )
{
  void *dummy_ptr = malloc(1);
  return dummy_ptr;
}

void
SilGetPrimaryRb (
  uint32_t *SocketNum,
  uint32_t *RootBridgeNum
  )
{
  return;
}

uint8_t
xUslGetPhysAddrSize (
  void
  )
{
  return 0;
}

uint8_t
xUslGetPhysAddrReduction (
  void
  )
{
  return 0;
}

void
SilSetMmioReg4 (
  uint8_t   TotalSocket,
  uint8_t   MmioPairIndex,
  uint32_t  SktNum,
  uint32_t  RbNum,
  uint64_t  BaseAddress,
  uint64_t  Length
  )
{
  return;
}

void
SilSetIoReg4 (
  uint8_t  TotalSocket,
  uint8_t  RegIndex,
  uint32_t SktNum,
  uint32_t RbNum,
  uint32_t IoBase,
  uint32_t IoSize
  )
{
  return;
}

void
SilAdditionalMmioSetting4 (
  DFX_RCMGR_INPUT_BLK *SilData,
  uint64_t            BottomOfCompat,
  bool                ReservedRegionAlreadySet
  )
{
  return;
}

void
DfXSilGetPhySktRbNum (
  uint32_t  LogSktNum,
  uint32_t  LogRbNum,
  uint32_t  *PhySktNum,
  uint32_t  *PhyRbNum,
  bool *LogToPhyMapInit,
  FABRIC_RB_LOG_TO_PHY_MAP *pLogToPhyMap
  )
{
  return;
}

SIL_STATUS
SilInitPciBusBasedOnNvVariable4 (
  DFX_RCMGR_INPUT_BLK *SilData
  )
{
  return SilPass;
}

SIL_STATUS
SilInitIoBasedOnNvVariable4 (
  DFX_RCMGR_INPUT_BLK     *SilData,
  FABRIC_ADDR_SPACE_SIZE  *SpaceStatus,
  bool                    SetDfRegisters
  )
{
  return SilPass;
}

SIL_STATUS
SilInitMmioBasedOnNvVariable4 (
  DFX_RCMGR_INPUT_BLK     *SilData,
  FABRIC_ADDR_SPACE_SIZE  *SpaceStatus,
  bool                    SetDfRegisters
  )
{
  return SilPass;
}

uint64_t
xUslRdMsr (
  uint32_t MsrAddress
  )
{
  return 0;
}

void
xUslWrMsr (
  uint32_t MsrAddress,
  uint64_t MsrValue
  )
{
  return;
}

void
xUslMsrAnd (
  uint32_t Index,
  uint64_t AndData
  )
{
  return;
}

void xUslMsrOr (
  uint32_t Index,
  uint64_t OrData
  )
{
  return;
}

void
xUslMsrAndThenOr (
  uint32_t Index,
  uint64_t AndData,
  uint64_t OrData
  )
{
  return;
}

bool xUslIsComputeUnitPrimary (
  void
  )
{
  return TRUE;
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

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp(IterationName, "SilPass") == 0) {

    // Arrange
    SIL_STATUS rc;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    rc = InitializeResourceManagerDfXTp3();
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (rc == SilPass)
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    else
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
      
  }
  else 
  {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test ended at the 'else' case; this is a faulty behaviour.", TestName, IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  // UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
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
  AMD_UNIT_TEST_STATUS Status;              // conv.
  AMD_UNIT_TEST_FRAMEWORK Ut;               // conv.

  // Initializing the UnitTest framework    // conv.
  Status = UtInitFromArgs (
    &Ut,
    argc,
    argv
  );
  if (Status != AMD_UNIT_TEST_PASSED) {
    return Status;
  }

  // Logging the start of the test.         // conv.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // Running test.                          // conv.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
