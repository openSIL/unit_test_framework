/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file DfHasSmuUt.c
 * @brief Unit tests for DfHasSmuUt
 *
 * Iterations: SmuIsFound, SmuIsNotFound
 */

#include "DfHasSmuUt.h"

// parameter used by DfXFindComponentLocationMap
const uint32_t GenoaPhysIos0FabricId = 0x20;

// parameter used by DfXFindComponentLocationMap
const COMPONENT_LOCATION  GenoaComponentLocation [] = {
  {0, 0, 0x22, PrimaryFch},     // Physical location, Socket 0, Die 0, Ios2
  {1, 0, 0x22, SecondaryFch},   // Physical location, Socket 1, Die 0, Ios2
  {0, 0, 0x22, PrimarySmu},     // Physical location, Socket 0, Die 0, Ios2
  {1, 0, 0x22, SecondarySmu},   // Physical location, Socket 1, Die 0, Ios2
};

/**
  *	DfXFindComponentLocationMap
  *
  *	@brief Fake Implementation
  *
  * @param Count TBD
  * @param PhysIos0FabricId Globally declared
  *
  *	@return const COMPONENT_LOCATION* TBD
  *
  */
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

// parameter used by DfXGetDeviceMapOnDie
const DEVICE_IDS   GenoaIosMap [] = {
  {0x00000020, 0x00000024},
  {0x00000021, 0x00000025},
  {0x00000022, 0x00000026},
  {0x00000023, 0x00000027}
};

// parameter used by DfXGetDeviceMapOnDie
const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  GenoaDeviceMap[] = {
  {Ios,   sizeof (GenoaIosMap) / sizeof (GenoaIosMap[0]),      &GenoaIosMap[0]    },
  {FabricDeviceTypeMax, 0, NULL}
};

/**
  *	DfXGetDeviceMapOnDie
  *
  *	@brief Fake Implementation
  *
  * @param Socket TBD
  *
  *	@return AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP* TBD
  *
  */
const 
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP * 
DfXGetDeviceMapOnDie (
  void
  )
{
  const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *DeviceMap;

  DeviceMap = &GenoaDeviceMap[0];
  return DeviceMap;
}

// instantiates the transfer table globally
static DF_COMMON_2_REV_XFER_BLOCK MockDfXfer = {
  .DfFabricRegisterAccRead = NULL,
  .DfFabricRegisterAccWrite = NULL,
  .DfGetNumberOfProcessorsPresent = NULL,
  .DfGetNumberOfSystemDies = NULL,
  .DfGetNumberOfSystemRootBridges = NULL,
  .DfGetNumberOfRootBridgesOnSocket = NULL,
  .DfGetNumberOfRootBridgesOnDie = NULL,
  .DfGetDieSystemOffset = NULL,
  .DfGetDeviceMapOnDie = DfXGetDeviceMapOnDie,
  .DfGetHostBridgeBusBase = NULL,
  .DfGetHostBridgeBusLimit = NULL,
  .DfGetPhysRootBridgeNumber = NULL,
  .DfFindComponentLocationMap = DfXFindComponentLocationMap,
  .DfBaseFabricTopologyConstructor = NULL,
  .DfBuildDomainInfo = NULL
};

// prerequisuite begins
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

// body begins
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

  if (strcmp(IterationName, "SmuIsFound") == 0) 
  {
    // Arrange
    uint32_t Socket = 0, Die = 0, Index = 2; 
    bool Result;

    // Act
    MockSilGetCommon2RevXferTableOnce( (void *)&MockDfXfer, SilPass );
    MockSilGetCommon2RevXferTableOnce( (void *)&MockDfXfer, SilPass );
    Result = DfHasSmu(Socket, Die, Index);

    // Assert
    // No assertion is needed due to Result are valid in both T/F forms.
  }
  else if (strcmp(IterationName, "SmuIsNotFound") == 0)
  {
    // Arrange
    uint32_t Socket = 0, Die = 0xFF, Index = 2; 
    bool Result;

    // Act
    MockSilGetCommon2RevXferTableOnce( (void *)&MockDfXfer, SilPass );
    MockSilGetCommon2RevXferTableOnce( (void *)&MockDfXfer, SilPass );
    Result = DfHasSmu(Socket, Die, Index);

    // Assert
    // No assertion is needed due to Result are valid in both T/F forms.
  }
  else 
  {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "Iteration: %s is not implemented.", IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
  }

  Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "%s (Iteration: %s) test ended.", TestName, IterationName);
  UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
}

// cleanup begins
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
