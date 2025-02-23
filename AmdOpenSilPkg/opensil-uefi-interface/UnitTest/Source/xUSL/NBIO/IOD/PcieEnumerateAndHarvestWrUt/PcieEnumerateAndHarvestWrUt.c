/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file PcieEnumerateAndHarvestWrUt.c
 * @brief
 *
 */

#include "PcieEnumerateAndHarvestWrUt.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

#define PcieLibGetNextDescriptor(Descriptor) ((Descriptor == NULL) ? NULL : ((Descriptor->Header.DescriptorFlags & DESCRIPTOR_TERMINATE_LIST) != 0) ? NULL : (Descriptor + 1))

const SMN_TABLE NbioPprInitValues[] = {0};
const SMN_TABLE GnbEarlyInitTableCommon[] = {0};
const SMN_TABLE GnbnBifInitTable[] = {0};
const SMN_TABLE GnbOncePerSocketInitMP[] = {0};
const SMN_TABLE GnbSdpMuxInitTableCommon[] = {0};
NBIOCLASS_DATA  mNbioIpBlockData = {0};

// Mock data
static PCIe_COMPLEX_CONFIG mockComplex;
static PCIe_SILICON_CONFIG mockSilicon;
static PCIe_WRAPPER_CONFIG mockWrapper;
static uint32_t mockFuseData;
static bool mockIsSteppingAx = false;

// Mock functions for testing function PcieEnumerateAndHarvestWrappers()
bool 
IsSteppingAx (
  void
  )
{
  return mockIsSteppingAx;
}

// control the mock version of IsSteppingAx 
void 
SetIsSteppingAx (
  IN bool Value
  )
{
  mockIsSteppingAx = Value;
}


PCIe_DESCRIPTOR_HEADER* 
PcieConfigGetChild (
  IN uint32_t Type,
  IN PCIe_DESCRIPTOR_HEADER* Descriptor
  )
{
  if (Type == DESCRIPTOR_COMPLEX) {
    return &mockComplex.Header;
  }
  if (Type == DESCRIPTOR_SILICON) {
    return &mockSilicon.Header;
  }
  if (Type == DESCRIPTOR_ALL_WRAPPERS) {
    return &mockWrapper.Header;
  }
  return NULL;
}

uint32_t 
xUSLSmnRead (
  IN uint32_t Segment,
  IN uint32_t Bus,
  IN uint32_t Address
  )
{
  return mockFuseData;
}

SIL_STATUS 
PcieComplexHidePcieCore (
  IN GNB_HANDLE* GnbHandle,
  IN uint32_t PcieCoreNum
  )
{
  return SilPass;
}

//Stub and nock functions in the same file

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

SIL_STATUS 
GetSocLogicalIdOnCurrentCore (
  SOC_LOGICAL_ID *LogicalId
  )
{
  return SilPass;
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

GNB_HANDLE* GetGnbHandle (void)
{
  static GNB_HANDLE  GnbHandle = {0};
  return &GnbHandle;
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

// Test function
void
EFIAPI
TestBody (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*)UtGetActiveFrameworkHandle();
  const char* TestName = UtGetTestName(Ut);
  const char* IterationName = UtGetTestIteration(Ut);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp(IterationName, "TestAXStepping") == 0) {
    // Arrange
    PCIe_PLATFORM_CONFIG Pcie = {0};
    mockComplex.Header.DescriptorFlags = 0;
    mockSilicon.RBIndex = 0;
    mockWrapper.WrapId = 0;
    mockFuseData = SIL_RESERVED2_964; // Set fuse data for harvesting
    SetIsSteppingAx(true);

    // Act
    PcieEnumerateAndHarvestWrappers(&Pcie);

    // Assert
    // If we reach here without crashes, test passed
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Iteration '%s' test passed", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  }
  else if (strcmp(IterationName, "TestBXStepping") == 0) {
    // Arrange
    PCIe_PLATFORM_CONFIG Pcie = {0};
    mockComplex.Header.DescriptorFlags = 0;
    mockSilicon.RBIndex = 0;
    mockWrapper.WrapId = 0;
    mockFuseData = SIL_RESERVED2_956; // Set fuse data for harvesting
    SetIsSteppingAx(false);

    // Act
    PcieEnumerateAndHarvestWrappers(&Pcie);

    // Assert
    // If we reach here without crashes, test passed
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Iteration '%s' test passed", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  
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
