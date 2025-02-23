/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file IsSteppingAxUt.c
 * @brief
 *
 */

#include "IsSteppingAxUt.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

// Mock data
#define AMD_REV_F19_GENOA_A0    0x0001u
#define AMD_REV_F19_GENOA_A1    0x0002u
#define AMD_REV_F19_GENOA_AX    (AMD_REV_F19_GENOA_A0 | AMD_REV_F19_GENOA_A1)

const SMN_TABLE NbioPprInitValues[] = {0};
const SMN_TABLE GnbEarlyInitTableCommon[] = {0};
const SMN_TABLE GnbnBifInitTable[] = {0};
const SMN_TABLE GnbOncePerSocketInitMP[] = {0};
const SMN_TABLE GnbSdpMuxInitTableCommon[] = {0};
NBIOCLASS_DATA  mNbioIpBlockData = {0};
NBIO_CONFIG_DATA mNbioConfigDataDflts = {0};

// Mock data
static SIL_STATUS     MockReturnStatus;
static SOC_LOGICAL_ID MockLogicalId;


// Mock
SIL_STATUS 
GetSocLogicalIdOnCurrentCore (
  SOC_LOGICAL_ID *LogicalId
  )
{
  *LogicalId = MockLogicalId;
  return MockReturnStatus;
}

// Stub
void
xUSLSmnReadModifyWrite (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress,
  uint32_t    AndMask,
  uint32_t    OrMask
  )
{
  return;
}

GNB_HANDLE* GetGnbHandle (void)
{
  static GNB_HANDLE  GnbHandle = {0};
  return &GnbHandle;
}

void
xUSLSmnWrite (
  uint32_t SegmentNumber,
  uint32_t IohcBus,
  uint32_t SmnAddress,
  uint32_t Value
)
{
  return;
}

uint32_t
xUSLSmnRead (
  uint32_t SegmentNumber,
  uint32_t IohcBus,
  uint32_t SmnAddress
  )
{
  return 0;
}

SIL_STATUS ProgramNbioSmnTable (
        GNB_HANDLE             *GnbHandle,
        const SMN_TABLE        *Table,
        uint32_t               Modifier,
        uint32_t               Property
  )
{
  return SilPass;
}

void
NonPciBarInit (
         GNB_HANDLE   *GnbHandle,
         uint32_t     MmioBarLow,
         uint32_t     MmioBarHigh,
         uint32_t     MemorySize,
         bool         Enable,
         bool         LockSettings,
         bool         Above4G
  )
{
  return;
}

PCIe_DESCRIPTOR_HEADER* 
PcieConfigGetChild(
  uint32_t Type, 
  PCIe_DESCRIPTOR_HEADER *Descriptor
  )
{
    return Descriptor;
}

SIL_STATUS
PcieComplexHidePcieCore (
        GNB_HANDLE     *GnbHandle,
        uint32_t       PcieCoreNum
  )
{
  return SilPass;
}


AMD_UNIT_TEST_STATUS
EFIAPI
TestPrerequisite (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_STATUS Status = AMD_UNIT_TEST_PASSED;
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName        = UtGetTestName (Ut);
  const char* IterationName   = UtGetTestIteration (Ut);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Prerequisite started.", TestName, IterationName);

  Status = UtSilInit ();
  if (Status != AMD_UNIT_TEST_PASSED) {
    return AMD_UNIT_TEST_ABORTED;
  }
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Prerequisite ended.", TestName, IterationName);
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
  
  if (strcmp (IterationName, "SilPass") == 0) {
    // Arrange
    MockReturnStatus = SilPass;  
    MockLogicalId.Family = 1;
    MockLogicalId.Revision = 1;

    // Action
    bool valid = IsSteppingAx();

    // Assert
    if(valid == true){
      Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
        "Iteration '%s' test passed", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }else{
      Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
        "Iteration '%s' test failed", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }

  } else if (strcmp (IterationName, "SilInvalidParameter") == 0) {
    // Arrange
    MockReturnStatus = SilInvalidParameter;

    // Action
    bool valid = IsSteppingAx();

    // Assert
    if(valid == false){
      Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
        "Iteration '%s' test passed", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }else{
      Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
        "Iteration '%s' test failed", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  }else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Iteration '%s' test failed", IterationName);
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
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName        = UtGetTestName (Ut);
  const char* IterationName   = UtGetTestIteration (Ut);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) CleanUp started.", TestName, IterationName);
  // Free openSIL allocated memory
  UtSilDeinit ();
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) CleanUp ended.", TestName, IterationName);
  return AMD_UNIT_TEST_PASSED;
}

/**
 * main
 * @brief      Stating point for Execution
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

  char *SimpleCharContext = "A simple TestBody context";

  // Logging the start of the test.
  // Note: Test status at this time is set to "NOT_SET".
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // You can pass into the TestPrerequisite, TestBody, and TestCleanUp context of
  // your desire
  UtSetTestContext (&Ut, (AMD_UNIT_TEST_CONTEXT)SimpleCharContext);

  // Running the test
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
