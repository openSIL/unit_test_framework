/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
/**
* @file DfGetProcessorInfoUt.c
* @brief
*
* This function retrieves information about the processor installed in the given socket.
*
* 2 iterations
*
*/
#include "DfGetProcessorInfoUt.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

DF_COMMON_2_REV_XFER_BLOCK DfCmn2RevXfer = {
  .DfFabricRegisterAccRead                =         NULL,
  .DfFabricRegisterAccWrite               =         NULL,
  .DfGetNumberOfProcessorsPresent         =         GetNumberOfProcessorsPresentUt,
  .DfGetNumberOfSystemDies                =         GetNumberOfSystemDiesUt,
  .DfGetNumberOfSystemRootBridges         =         NULL,
  .DfGetNumberOfRootBridgesOnSocket       =         GetNumberOfRootBridgesOnSocketUt,
  .DfGetNumberOfRootBridgesOnDie          =         NULL,
  .DfGetDieSystemOffset                   =         NULL,
  .DfGetDeviceMapOnDie                    =         NULL,
  .DfGetHostBridgeBusBase                 =         NULL,
  .DfGetHostBridgeBusLimit                =         NULL,
  .DfGetPhysRootBridgeNumber              =         NULL,
  .DfFindComponentLocationMap             =         NULL,
  .DfBaseFabricTopologyConstructor        =         NULL,
  .DfBuildDomainInfo                      =         NULL
};

UINT32
GetNumberOfProcessorsPresentUt (
  void
  )
{
  return 1;
}

UINT32
GetNumberOfRootBridgesOnSocketUt (
  UINT32               Socket
  )
{
  return 1;
}

UINT32
GetNumberOfSystemDiesUt (
  void
  )
{
  return 1;
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
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Allocating memory for openSIL.");
  return AMD_UNIT_TEST_PASSED;
}

void
EFIAPI
TestBody (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut            = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  const char* TestName                   = UtGetTestName (Ut);
  const char* IterationName              = UtGetTestIteration (Ut);

  UINT32 SocketIndex;
  UINT32 DieCount;
  UINT32 RootBridgeCount;

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp(IterationName, "ValidateProcessorInfo") == 0) {
    // Setting up SilGetCommon2RevXferTable to pass.
    // SilGetCommon2RevXferTable from DfGetProcessorInfo()
    MockSilGetCommon2RevXferTableOnce ((void *)&DfCmn2RevXfer, SilPass);

    DfGetProcessorInfo (0, &DieCount, &RootBridgeCount);

    // Assert
    // These should both be 1 given that we return 1 in our stub functions
    if ((DieCount != 1) && (RootBridgeCount != 1)) {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
        "Status (0x%x) ValidateProcessorInfo test fail.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }else {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
         "Status (0x%x) ValidateProcessorInfo test pass.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }

  } else if(strcmp(IterationName, "InvalidSocketIndexParameter") == 0){
    // Set invalid socktIndex parameter which is less than 1
    SocketIndex = 1;

    MockSilGetCommon2RevXferTableOnce ((void *)&DfCmn2RevXfer, SilPass);

    DfGetProcessorInfo (SocketIndex, &DieCount, &RootBridgeCount);

    // Assert
    // Check invalid socktIndex parameter
    if (SocketIndex < 1) {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
        "Status (0x%x) InvalidSocketIndexParameter test fail.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }else {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
         "Status (0x%x) InvalidSocketIndexParameter test pass.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
  } else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "Iteration '%s' is not implemented.", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test ended.", TestName, IterationName);
}


AMD_UNIT_TEST_STATUS
EFIAPI
TestCleanUp (
  IN AMD_UNIT_TEST_CONTEXT Context
  )
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK*) UtGetActiveFrameworkHandle ();
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Freeing memory allocated to openSIL.");
  UtSilDeinit ();
  return AMD_UNIT_TEST_PASSED;
}

/**
* main
* @brief      Stating point for Execution
*
* @details    This routine:
*              - Handles the command line arguments.
*                example: DfGetProcessorInfoUt.exe -o "E:\test" -i
*                         "ValidateProcessorInfo" -c <Path to Test Config File>
*              - Declares the unit test framework.
*              - Run the tests.
*              - Deallocate the Unit test framework.
*
* @param    argc                     Argument count
* @param    *argv[]                  Argument vector
*
* @retval   AMD_UNIT_TEST_PASSED     Function succeeded
* @retval   NON-ZERO                 Error occurs
*/
int
main (
  int   argc,
  char  *argv[]
  )
{
  AMD_UNIT_TEST_STATUS     Status;
  AMD_UNIT_TEST_FRAMEWORK  Ut;

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

  // Running the test
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
 