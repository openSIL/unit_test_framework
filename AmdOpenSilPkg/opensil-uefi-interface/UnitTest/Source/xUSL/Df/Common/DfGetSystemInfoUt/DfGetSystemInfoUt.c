/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
/**
* @file DfGetSystemInfoUt.c
* @brief
*
* This function retrieves information about the given die.
*
* 5 iterations
*
*/
#include "DfGetSystemInfoUt.h"

#define FABRIC_REG_ACC_BC    (0xFF) // Data needed for fakes

HOST_DEBUG_SERVICE mHostDebugService = NULL;

// Data needed for fakes
// Data for DfXFindComponentLocationMap()
const DEVICE_IDS   GenoaIosMap [] = {
  {0x00000020, 0x00000024},
  {0x00000021, 0x00000025},
  {0x00000022, 0x00000026},
  {0x00000023, 0x00000027}
};

const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  GenoaDeviceMap[] = {
  {Ios,   sizeof (GenoaIosMap) / sizeof (GenoaIosMap[0]),      &GenoaIosMap[0]    },
  {FabricDeviceTypeMax, 0, NULL}
};

// Data for DfXFindComponentLocationMap()
const uint32_t GenoaPhysIos0FabricId = 0x20;

const COMPONENT_LOCATION  GenoaComponentLocation [] = {
  {0, 0, 0x22, PrimaryFch},     // Physical location, Socket 0, Die 0, Ios2
  {1, 0, 0x22, SecondaryFch},   // Physical location, Socket 1, Die 0, Ios2
  {0, 0, 0x22, PrimarySmu},     // Physical location, Socket 0, Die 0, Ios2
  {1, 0, 0x22, SecondarySmu},   // Physical location, Socket 1, Die 0, Ios2
};


// Stub Functions
UINT32
DfXGetNumberOfProcessorsPresent (
  void
  )
{
  return 1;
}

UINT32
DfXGetNumberOfSystemDies (
  void
  )
{
  return 1;
}

UINT32 
DfXGetNumberOfSystemRootBridges (
  void
  )
{
  return 1;
}

// Fake Functions
const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP * DfXGetDeviceMapOnDie (void)
{
  const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *DeviceMap;

  DeviceMap = &GenoaDeviceMap[0];
  return DeviceMap;
}

const
COMPONENT_LOCATION *
DfXFindComponentLocationMap (
  uint32_t *Count,
  uint32_t *PhysIos0FabricId
  )
{
  const COMPONENT_LOCATION *ComponentLocationMap;

  ComponentLocationMap = &GenoaComponentLocation[0];
  if (Count != NULL) {
    *Count = sizeof (GenoaComponentLocation) / sizeof (GenoaComponentLocation[0]);
  }
  if (PhysIos0FabricId != NULL) {
    *PhysIos0FabricId = GenoaPhysIos0FabricId;
  }
  return ComponentLocationMap;
}

DF_COMMON_2_REV_XFER_BLOCK DfCmn2RevXfer = {
  .DfFabricRegisterAccRead                =         NULL,
  .DfFabricRegisterAccWrite               =         NULL,
  .DfGetNumberOfProcessorsPresent         =         DfXGetNumberOfProcessorsPresent,
  .DfGetNumberOfSystemDies                =         DfXGetNumberOfSystemDies,
  .DfGetNumberOfSystemRootBridges         =         DfXGetNumberOfSystemRootBridges,
  .DfGetNumberOfRootBridgesOnSocket       =         NULL, 
  .DfGetNumberOfRootBridgesOnDie          =         NULL,
  .DfGetDieSystemOffset                   =         NULL,
  .DfGetDeviceMapOnDie                    =         DfXGetDeviceMapOnDie,// called in DfFindDeviceTypeEntryInMap()
  .DfGetHostBridgeBusBase                 =         NULL,
  .DfGetHostBridgeBusLimit                =         NULL,
  .DfGetPhysRootBridgeNumber              =         NULL,
  .DfFindComponentLocationMap             =         DfXFindComponentLocationMap,// called in DfGetSystemComponentRootBridgeLocation()
  .DfBaseFabricTopologyConstructor        =         NULL,
  .DfBuildDomainInfo                      =         NULL
};

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

  SIL_STATUS           SilStatus;
  UINT32 NumberOfInstalledProcessors;
  UINT32 TotalNumberOfDie;
  UINT32 TotalNumberOfRootBridges;
  ROOT_BRIDGE_LOCATION SystemFchRootBridgeLocation = {0};
  ROOT_BRIDGE_LOCATION SystemSmuRootBridgeLocation = {0};

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);


  if (strcmp(IterationName, "SilPass") == 0) {
    // Arrange
    NumberOfInstalledProcessors = 1;
    TotalNumberOfDie = 1;
    TotalNumberOfRootBridges = 1;

    // Action
    // Setting up SilGetCommon2RevXferTable to pass. 
    // Mock 5 times.
    MockSilGetCommon2RevXferTableManyTimes ((void *)&DfCmn2RevXfer, SilPass, 5);

    SilStatus = DfGetSystemInfo(&NumberOfInstalledProcessors, &TotalNumberOfDie, 
                                &TotalNumberOfRootBridges,&SystemFchRootBridgeLocation, 
                                &SystemSmuRootBridgeLocation);

    // Assert
    if (SilStatus != SilAborted) {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Did not receive SilAborted", IterationName);
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    } else {
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
*                example: DfGetSystemInfoUt.exe -o "E:\test" -i
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
 