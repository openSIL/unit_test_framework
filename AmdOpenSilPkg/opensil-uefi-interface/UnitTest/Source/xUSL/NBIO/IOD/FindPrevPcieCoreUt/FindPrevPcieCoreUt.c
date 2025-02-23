/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file FindPrevPcieCoreUt.c
 * @brief
 *
 */

#include "FindPrevPcieCoreUt.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

PCIe_DESCRIPTOR_HEADER* PcieConfigGetPeer(uint32_t Type, PCIe_DESCRIPTOR_HEADER *Descriptor)
{
  // Create a static or dummy PCIe_DESCRIPTOR_HEADER object with minimal values
  static PCIe_DESCRIPTOR_HEADER StubDescriptor = {
      .DescriptorFlags = 1, 
      .Parent = 1,          
      .Peer = 1,            
      .Child = 1            
  };

  // Return a pointer to the static object
  return &StubDescriptor;
}

void
PcieConfigRunProcForAllWrappersInNbio (
  uint32_t                      DescriptorFlags,
  PCIe_RUN_ON_WRAPPER_CALLBACK2 Callback,
  void                          *Buffer,
  GNB_HANDLE                    *GnbHandle
  )
{
  return;
}

void
PcieConfigRunProcForAllEnginesInWrapper (
  uint32_t                      DescriptorFlags,
  PCIe_RUN_ON_ENGINE_CALLBACK2  Callback,
  void                          *Buffer,
  PCIe_WRAPPER_CONFIG           *Wrapper
  )
{
  return;
}

// MOCK CONTROL VARIABLES (static to limit scope)
static PCIe_SILICON_CONFIG *mock_silicon_parent = NULL;
static PCIe_PLATFORM_CONFIG *mock_platform_parent = NULL;
static PCIe_SILICON_CONFIG *mock_silicon_child = NULL;
static PCIe_WRAPPER_CONFIG *mock_first_wrapper = NULL;

// MOCKED FUNCTIONS (static to limit scope)
PCIe_DESCRIPTOR_HEADER* PcieConfigGetParent(uint32_t Type, PCIe_DESCRIPTOR_HEADER *Descriptor) {
  if (Type == DESCRIPTOR_SILICON) {
    return (PCIe_DESCRIPTOR_HEADER*)mock_silicon_parent;
  } else if (Type == DESCRIPTOR_PLATFORM) {
    return (PCIe_DESCRIPTOR_HEADER*)mock_platform_parent;
  }
  return NULL;
}

PCIe_DESCRIPTOR_HEADER* PcieConfigGetChild(uint32_t Type, PCIe_DESCRIPTOR_HEADER *Descriptor) {
  if (Type == DESCRIPTOR_SILICON) {
    return (PCIe_DESCRIPTOR_HEADER*)mock_silicon_child;
  } else if (Type == DESCRIPTOR_ALL_WRAPPERS) {
    return (PCIe_DESCRIPTOR_HEADER*)mock_first_wrapper;
  }
  return NULL;
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
  
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);
    
  // Test Case 1: Early return when InstanceID is 0
  if(strcmp (IterationName, "InvalidInstanceID") == 0){

  // Arrange
  HIDE_WRAPPER_INFO HideInfo = {0};
  PCIe_WRAPPER_CONFIG PcieCore;
  PCIe_SILICON_CONFIG Silicon = { .InstanceId = 0 };

  mock_silicon_parent = &Silicon;  // Returned by PcieConfigGetParent(DESCRIPTOR_SILICON)
  mock_platform_parent = NULL;     // Not used in this test case

  // Act
  FindPrevPcieCore(&HideInfo, &PcieCore);

  // Assert: Function should exit early; HideInfo.PrevPcieCore remains NULL
  if (HideInfo.PrevPcieCore == NULL) {
    Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Iteration '%s' test passed", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  } else {
    Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Iteration '%s' test failed", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
  }

  } 
  // Test Case 2: Find previous silicon and its last wrapper
  else if(strcmp (IterationName, "FindPrevSiliconAndLastWrapper") == 0){

  // Arrange
  HIDE_WRAPPER_INFO HideInfo = {0};
  PCIe_WRAPPER_CONFIG PcieCore;
  PCIe_SILICON_CONFIG Silicon = { .InstanceId = 1 };
  PCIe_PLATFORM_CONFIG Pcie;
  PCIe_SILICON_CONFIG PrevSilicon = { 
    .InstanceId = 0,
    .Header = { .Peer = 0 }                 // Terminate topology list
  };
  PCIe_WRAPPER_CONFIG Wrappers[2] = {
    { .Header.DescriptorFlags = 0 },        // First wrapper
    { .Header.DescriptorFlags = DESCRIPTOR_TERMINATE_LIST }  // Last wrapper
  };

  // Link wrappers
  Wrappers[0].Header.Peer = (uint16_t)((uint8_t*)&Wrappers[1] - (uint8_t*)&Wrappers[0]);

  mock_silicon_parent = &Silicon;     // PcieCore's parent silicon
  mock_platform_parent = &Pcie;       // Silicon's parent platform
  mock_silicon_child = &PrevSilicon;  // Platform's child silicon
  mock_first_wrapper = &Wrappers[0];  // PrevSilicon's first wrapper

  // Act
  FindPrevPcieCore(&HideInfo, &PcieCore);

  // Assert: Last wrapper (Wrappers[1]) should be saved in HideInfo
  if (HideInfo.PrevPcieCore == &Wrappers[1]) {
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  } else {
    UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
  }

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Iteration '%s' test passed", IterationName);
  UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);

}
  // Test Case 3: Traverse multiple silicons to find the matching one
  else if(strcmp (IterationName, "TraverseMultipleSilicons") == 0){

  // Arrange
  HIDE_WRAPPER_INFO HideInfo = {0};
  PCIe_WRAPPER_CONFIG PcieCore;
  PCIe_SILICON_CONFIG Silicon = { .InstanceId = 3 };  
  PCIe_PLATFORM_CONFIG Pcie;

  // Create Silicons: InstanceId 0 → 1 → 2 (target)
  PCIe_SILICON_CONFIG Silicons[3] = {
    [0] = {
      .InstanceId = 0,
      .Header = {
        .Peer = sizeof(PCIe_SILICON_CONFIG),           
        .DescriptorFlags = 0                           
      }
    },
    [1] = {
      .InstanceId = 1,
      .Header = {
        .Peer = sizeof(PCIe_SILICON_CONFIG),           
        .DescriptorFlags = 0                           
      }
    },
    [2] = {
      .InstanceId = 2,                                 
      .Header = {
        .Peer = 0,                                     
        .DescriptorFlags = DESCRIPTOR_TERMINATE_TOPOLOGY  
      }
    }
  };

  // Wrapper under Silicon[2]
  PCIe_WRAPPER_CONFIG Wrapper = { 
    .Header.DescriptorFlags = DESCRIPTOR_TERMINATE_LIST 
  };

  // Mock Setup
  mock_silicon_parent = &Silicon;     
  mock_platform_parent = &Pcie;       
  mock_silicon_child = &Silicons[0];  
  mock_first_wrapper = &Wrapper;      

  // Act
  FindPrevPcieCore(&HideInfo, &PcieCore);

  // Assert: Loop calls PcieConfigGetNextTopologyDescriptor twice before breaking
  if (HideInfo.PrevPcieCore == &Wrapper) {
    // Verify the state of mock objects
    assert(mock_silicon_parent == &Silicon);
    assert(mock_platform_parent == &Pcie);
    assert(mock_silicon_child == &Silicons[0]);
    assert(mock_first_wrapper == &Wrapper);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  } else {
    UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
  }

}
  // Test Case 4: Previous silicon not found (no silicon with InstanceID - 1)
  else if(strcmp (IterationName, "PrevSiliconNotFound") == 0){

  // Arrange
  HIDE_WRAPPER_INFO HideInfo = {0};
  PCIe_WRAPPER_CONFIG PcieCore;
  PCIe_SILICON_CONFIG Silicon = { .InstanceId = 1 };  
  PCIe_PLATFORM_CONFIG Pcie;

  // Create Silicons: InstanceId 2 → 3 (no InstanceId = 0)
  PCIe_SILICON_CONFIG Silicons[2] = {
    [0] = {
      .InstanceId = 2,
      .Header = {
        .Peer = sizeof(PCIe_SILICON_CONFIG),           
        .DescriptorFlags = 0                           
      }
    },
    [1] = {
      .InstanceId = 3,
      .Header = {
        .Peer = 0,                                       
        .DescriptorFlags = DESCRIPTOR_TERMINATE_TOPOLOGY 
      }
    }
  };

  // Mock Setup
  mock_silicon_parent = &Silicon;     
  mock_platform_parent = &Pcie;       
  mock_silicon_child = &Silicons[0];  

  // Act
  FindPrevPcieCore(&HideInfo, &PcieCore);

  // Assert: PrevSilicon becomes NULL → Function returns early
  if (HideInfo.PrevPcieCore == NULL) {
    // Verify the state of mock objects
    assert(mock_silicon_parent == &Silicon);
    assert(mock_platform_parent == &Pcie);
    assert(mock_silicon_child == &Silicons[0]);
    assert(mock_first_wrapper == NULL);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
  } else {
    UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
  }

} else {
  Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
      "Unknown test iteration '%s'", IterationName);
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
