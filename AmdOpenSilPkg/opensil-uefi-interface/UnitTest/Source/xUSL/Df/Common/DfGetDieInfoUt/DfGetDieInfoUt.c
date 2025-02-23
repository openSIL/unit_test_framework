/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
/**
* @file DfGetDieInfoUt.c
* @brief
*
* This function retrieves information about the given die.
*
* 5 iterations
*
*/
#include "DfGetDieInfoUt.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

DF_COMMON_2_REV_XFER_BLOCK DfCmn2RevXfer = {
  .DfFabricRegisterAccRead                =         NULL,
  .DfFabricRegisterAccWrite               =         NULL,
  .DfGetNumberOfProcessorsPresent         =         GetNumberOfProcessorsPresentUt,
  .DfGetNumberOfSystemDies                =         NULL,
  .DfGetNumberOfSystemRootBridges         =         NULL,
  .DfGetNumberOfRootBridgesOnSocket       =         NULL, 
  .DfGetNumberOfRootBridgesOnDie          =         GetNumberOfRootBridgesOnDieUt,
  .DfGetDieSystemOffset                   =         GetDieSystemOffsetUt,
  .DfGetDeviceMapOnDie                    =         GetDeviceMapOnDieUt,
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
GetNumberOfRootBridgesOnDieUt (
  UINT32 Socket
  ) 
{
  return 1;
};

UINT32 
GetDieSystemOffsetUt (
  UINT32 Socket
  )
{
  return 1;
}

CONST 
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP* 
  GetDeviceMapOnDieUt (
  void
  )
{
  return NULL; //or {type = NULL; Count = 0; *IDs = NULL} 
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

  UINT32 NumberOfRootBridges;
  UINT32 SystemIdOffset;
  const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *FabricIdMap;

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp(IterationName, "ValidateDieInfo") == 0) {
    // Setting up SilGetCommon2RevXferTable to pass.
    // SilGetCommon2RevXferTable from DfGetDieInfo()
    MockSilGetCommon2RevXferTableOnce ((void *)&DfCmn2RevXfer, SilPass);

    DfGetDieInfo (0, 0, &NumberOfRootBridges, &SystemIdOffset, &FabricIdMap);

    // Assert
    // These should both be 1 given that we return 1 in our stub functions
    if ((NumberOfRootBridges != 1) && (SystemIdOffset != 1) && (FabricIdMap == NULL)) {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
        "Status (0x%x) ValidateProcessorInfo test fail.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }else {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
         "Status (0x%x) ValidateProcessorInfo test pass.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    
  } else if(strcmp(IterationName, "InvalidSocketParameter") == 0){
    //Arrange an invalid Socket which is more than 1 according to the stub function
    UINT32 Socket = 1;

    MockSilGetCommon2RevXferTableOnce ((void *)&DfCmn2RevXfer, SilPass);

    DfGetDieInfo (Socket, 0, &NumberOfRootBridges, &SystemIdOffset, &FabricIdMap);

    //Assert
    //Socket should be less than 1 because we return 1 in our stub function
    if(Socket >= 1){
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
         "Status (0x%x) InvalidSocketIndexParameter test pass.", IterationName, Socket);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }else{
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
        "Status (0x%x) InvalidSocketIndexParameter test fail.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }

  }else if(strcmp(IterationName, "InvalidDieParameter") == 0){
    //Arrange an invalid Die which is more than 1 according to the stub function
    UINT32  Die = 1;

    MockSilGetCommon2RevXferTableOnce ((void *)&DfCmn2RevXfer, SilPass);

    DfGetDieInfo (0, Die, &NumberOfRootBridges, &SystemIdOffset, &FabricIdMap);

    //Assert
    //Die should be less than 1 because we return 1 in our stub function
    if(Die >= 1){
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
         "Status (0x%x) InvalidSocketIndexParameter test pass.", IterationName, Die);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }else{
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
        "Status (0x%x) InvalidSocketIndexParameter test fail.", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }

  }else {
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
*                example: DfGetDieInfoUt.exe -o "E:\test" -i
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
 