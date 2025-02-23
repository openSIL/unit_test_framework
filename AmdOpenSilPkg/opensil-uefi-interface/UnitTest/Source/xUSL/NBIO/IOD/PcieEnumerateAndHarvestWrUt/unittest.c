/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>
#include <NBIO/GnbDxio.h>
#include <NBIO/NbioPcieTopologyHelper.h>
#include <NBIO/Nbio.h>
#include <NBIO/NbioCommon.h>
#include <UnitTest/AmdUnitTest.h>
#include <xSIM.h>
#include <SilSocLogicalId.h>

// Mock data
static PCIe_COMPLEX_CONFIG mockComplex;
static PCIe_SILICON_CONFIG mockSilicon;
static PCIe_WRAPPER_CONFIG mockWrapper;
static uint32_t mockFuseData;
static bool isSteppingAx = false;

// Mock functions
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

PCIe_DESCRIPTOR_HEADER* 
PcieLibGetNextDescriptor (
  IN void* Descriptor
  )
{
  // Return NULL to end the loop after first iteration
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

bool 
IsSteppingAx (void)
{
  return isSteppingAx;
}

SIL_STATUS 
PcieComplexHidePcieCore (
  IN GNB_HANDLE* GnbHandle,
  IN uint32_t PcieCoreNum
  )
{
  return SilPass;
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
    isSteppingAx = true;

    // Act
    PcieEnumerateAndHarvestWrappers(&Pcie);

    // Assert
    // If we reach here without crashes, test passed
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  }
  else if (strcmp(IterationName, "TestBXStepping") == 0) {
    // Arrange
    PCIe_PLATFORM_CONFIG Pcie = {0};
    mockComplex.Header.DescriptorFlags = 0;
    mockSilicon.RBIndex = 0;
    mockWrapper.WrapId = 0;
    mockFuseData = SIL_RESERVED2_956; // Set fuse data for harvesting
    isSteppingAx = false;

    // Act
    PcieEnumerateAndHarvestWrappers(&Pcie);

    // Assert
    // If we reach here without crashes, test passed
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  }
  else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Unknown test iteration '%s'", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_ABORTED);
  }

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test ended.", TestName, IterationName);
}

/**
 * main
 *
 * @brief   Starting point for Execution
 *
 * @param   argc  Argument count
 * @param   argv  Argument vector
 *
 * @return  int   0 in success, other in failure
 */
int
main (
  int   argc,
  char  *argv[]
  )
{
  AMD_UNIT_TEST_FRAMEWORK Ut;
  AMD_UNIT_TEST_STATUS Status;

  // Initialize framework
  Status = UtInitFromArgs(&Ut, argc, argv);
  if (Status != AMD_UNIT_TEST_PASSED) {
    return Status;
  }

  char *SimpleCharContext = "A simple TestBody context";
  UtSetTestContext(&Ut, (AMD_UNIT_TEST_CONTEXT)SimpleCharContext);

  // Run test
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest(&Ut);

  // Cleanup
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName(&Ut));
  UtDeinit(&Ut);

  return AMD_UNIT_TEST_PASSED;
}
