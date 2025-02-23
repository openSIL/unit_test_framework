/**
 * @file RootBridgeInfoUt.c
 * @brief Unit tests for the DfGetRootBridgeInfo function.
 *
 * @details
 * This file contains unit tests for the following function:
 * 
 * SIL_STATUS DfGetRootBridgeInfo(
 *     uint32_t Socket,
 *     uint32_t Die,
 *     uint32_t Index,
 *     uint32_t *SystemFabricID,
 *     uint32_t *BusNumberBase,
 *     uint32_t *BusNumberLimit,
 *     uint32_t *PhysicalRootBridgeNumber,
 *     bool *HasFchDevice,
 *     bool *HasSystemMgmtUnit
 * );
 *
 * The tests iterate through all possible branches for each argument
 * to validate proper functionality.
 */

#include <stdlib.h>                       

#include <UtBaseLib.h>
#include <UtLogLib.h>

#include <DfCmn2Rev.h>                    
#include <Sil-api.h>
#include <SilBaseFabricTopologyLib.h>
#include <SilCommon.h>
#include <xSIM-api.h>
#include <xSIM.h>

#include <Library/UtSilServicesMockLib.h> 

#include "BaseFabricTopologyCmn.h"        

// Dependency:
// This variable holds the host debug service instance.
HOST_DEBUG_SERVICE mHostDebugService = NULL;

// API Table Functions:
// These functions simulate basic functionality for testing purposes.
uint32_t My_DfGetNumberOfProcessorsPresent(void)
{
    return 10; 
}

uint32_t My_DfGetNumberOfRootBridgesOnDie(uint32_t Socket)
{
    return 10; 
}

uint32_t My_DfGetHostBridgeBusBase(uint32_t Socket, uint32_t Index)
{
    return 0; 
}

uint32_t My_DfGetHostBridgeBusLimit(uint32_t Socket, uint32_t Index)
{
    return 0; 
}

uint32_t My_DfGetPhysRootBridgeNumber(uint32_t Index)
{
    return 0; 
}

// Non-Tested Functions (API Table Functions):
// These functions provide mock implementations for non-tested APIs.
const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP* My_DfGetDeviceMapOnDie(void)
{
    static const DEVICE_IDS myIds[1] = {0}; // Mock device IDs.
    static const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP myMap[1] = {
        {
            Ios,       // Device type.
            0,         // Device count.
            myIds      // Associated device IDs.
        }
    };
    return myMap; // Returns a mock device map for testing.
}

uint32_t My_DfGetDieSystemOffset(uint32_t Socket)
{
    return 0; // Returns a fixed system offset for the specified socket.
}

const COMPONENT_LOCATION* My_DfFindComponentLocationMap(uint32_t *Count, uint32_t *PhysIos0FabricId)
{
    static const COMPONENT_LOCATION myComponents[1] = {
        0, 0, 0, PrimarySmu // Mock component location data.
    };
    return myComponents; // Returns a mock component location map.
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

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "%s (Iteration: %s) Test started.", TestName, IterationName);

    // Input values for DfGetRootBridgeInfo
    uint32_t Socket = 0;
    uint32_t Die = 0;
    uint32_t Index = 0;
    uint32_t *SystemFabricID = NULL;
    uint32_t *BusNumberBase = NULL;
    uint32_t *BusNumberLimit = NULL;
    uint32_t *PhysicalRootBridgeNumber = NULL;
    bool *HasFchDevice = NULL;
    bool *HasSystemMgmtUnit = NULL; 
    // The API table
    DF_COMMON_2_REV_XFER_BLOCK passedTable = {NULL};            
    // Called API table functions in the DfGetRootBridgeInfo
    passedTable.DfGetNumberOfProcessorsPresent = My_DfGetNumberOfProcessorsPresent;  
    passedTable.DfGetNumberOfRootBridgesOnDie = My_DfGetNumberOfRootBridgesOnDie;
    passedTable.DfGetHostBridgeBusBase = My_DfGetHostBridgeBusBase; 
    passedTable.DfGetHostBridgeBusLimit = My_DfGetHostBridgeBusLimit; 
    passedTable.DfGetPhysRootBridgeNumber = My_DfGetPhysRootBridgeNumber;     
    passedTable.DfGetDeviceMapOnDie = My_DfGetDeviceMapOnDie; 
    passedTable.DfGetDieSystemOffset = My_DfGetDieSystemOffset;
    passedTable.DfFindComponentLocationMap = My_DfFindComponentLocationMap;
    if(strcmp(IterationName, "Socket") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        Socket = 100;                                               // input - Socket branch 
        MockSilGetCommon2RevXferTableOnce(&passedTable, Status);    // mock with proper table and status
        // Act 
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
        "Call DfGetRootBridgeInfo and enter Socket branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilInvalidParameter != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }
    else if(strcmp(IterationName, "Die") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        Die = 100;                                                  // input - Die branch 
        MockSilGetCommon2RevXferTableOnce(&passedTable, Status);    // mock with proper table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfGetRootBridgeInfo and enter Die branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilInvalidParameter != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }
    else if(strcmp(IterationName, "Index") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        Index = 100;                                                // input - Die branch 
        MockSilGetCommon2RevXferTableOnce(&passedTable, Status);    // mock with proper table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfGetRootBridgeInfo and enter Index branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilInvalidParameter != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }    
    else if(strcmp(IterationName, "SystemFabricID") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                     // status
        SystemFabricID = malloc(sizeof(uint32_t));                       // input - SystemFabricID branch 
        *SystemFabricID = 1;
        MockSilGetCommon2RevXferTableManyTimes(&passedTable, Status, 3); // mock with proper table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfGetRootBridgeInfo and enter SystemFabricID branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilPass != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }  
    else if(strcmp(IterationName, "BusNumberLimit") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        BusNumberLimit = malloc(sizeof(uint32_t));          // input - SystemFabricID branch 
        *BusNumberLimit = 1;
        MockSilGetCommon2RevXferTableOnce(&passedTable, Status);    // mock with proper table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfGetRootBridgeInfo and enter BusNumberLimit branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilPass != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }   
    else if(strcmp(IterationName, "PhysicalRootBridgeNumber") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        PhysicalRootBridgeNumber = malloc(sizeof(uint32_t));          // input - SystemFabricID branch 
        *PhysicalRootBridgeNumber = 1;
        MockSilGetCommon2RevXferTableOnce(&passedTable, Status);    // mock with proper table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfGetRootBridgeInfo and enter PhysicalRootBridgeNumber branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilPass != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }   
    else if(strcmp(IterationName, "HasFchDevice") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        HasFchDevice = malloc(sizeof(bool));                        // input - SystemFabricID branch 
        *HasFchDevice = true;
        Die = 0; // 
        MockSilGetCommon2RevXferTableManyTimes(&passedTable, Status, 3); // mock with proper table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfGetRootBridgeInfo and enter HasFchDevice branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilPass != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }   
    else if(strcmp(IterationName, "HasSystemMgmtUnit") == 0)
    {
        // Arrange
        SIL_STATUS Status = SilPass;                                // status
        HasSystemMgmtUnit = malloc(sizeof(bool));                        // input - SystemFabricID branch 
        *HasSystemMgmtUnit = true;
        Die = 0; // 
        MockSilGetCommon2RevXferTableManyTimes(&passedTable, Status, 3); // mock with proper table and status
        // Act
        Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
            "Call DfGetRootBridgeInfo and enter HasSystemMgmtUnit branch");
        SIL_STATUS returnedStatus = DfGetRootBridgeInfo (Socket, Die, Index, SystemFabricID, BusNumberBase, 
                                                        BusNumberLimit, PhysicalRootBridgeNumber, HasFchDevice, 
                                                        HasSystemMgmtUnit);
        // Assert
        if(SilPass != returnedStatus)
            UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }        
    else
    {
        Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Iteration '%s' is not implemented.", IterationName);
        UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
    }

    // if we run at any issue, The API is going to abort here.
    UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);

    Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
        "%s (Iteration: %s) Test ended.", TestName, IterationName);
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
