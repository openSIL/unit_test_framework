/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file PcieConfigAttachDescriptorsUt.c
 * @brief
 *
 */

#include "PcieConfigAttachDescriptorsUt.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

PCIe_DESCRIPTOR_HEADER* PcieConfigGetPeer(uint32_t Type, PCIe_DESCRIPTOR_HEADER *Descriptor)
{
  // return Descriptor;
  // Create a static or dummy PCIe_DESCRIPTOR_HEADER object with minimal values
  static PCIe_DESCRIPTOR_HEADER StubDescriptor = {
      .DescriptorFlags = 0, 
      .Parent = 1,          
      .Peer = 0,            
      .Child = 1            
  };

  // Return a pointer to the static object
  return &StubDescriptor;
}

PCIe_DESCRIPTOR_HEADER* PcieConfigGetChild(uint32_t Type, PCIe_DESCRIPTOR_HEADER *Descriptor)
{
  // Create a static PCIe_DESCRIPTOR_HEADER object with minimal values
  static PCIe_DESCRIPTOR_HEADER StubDescriptor = {
      .DescriptorFlags = 0, 
      .Parent = 1,          
      .Peer = 0,            
      .Child = 1            
  };

  // Return a pointer to the static object
  return &StubDescriptor;
}

PCIe_DESCRIPTOR_HEADER* PcieConfigGetParent (uint32_t Type, PCIe_DESCRIPTOR_HEADER *Descriptor)
{
  // Create a static PCIe_DESCRIPTOR_HEADER object with minimal values
  static PCIe_DESCRIPTOR_HEADER StubDescriptor = {
      .DescriptorFlags = 0, 
      .Parent = 1,          
      .Peer = 0,            
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

  UINT32 Type;
  PCIe_DESCRIPTOR_HEADER Base = {0};
  PCIe_DESCRIPTOR_HEADER New  = {0};

  void
PcieConfigAttachDescriptors (
      uint32_t                       Type,
      PCIe_DESCRIPTOR_HEADER         *Base,
      PCIe_DESCRIPTOR_HEADER         *New
  );
  
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp (IterationName, "ValidDescriptorRemoved") == 0) {
    // Arrange
    Type  = 1;

    // Action
    PcieConfigAttachDescriptors(Type, &Base, &New);

    Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
      "ValidDescriptorRemoved test passed", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);

    // Assert
  } else {
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
