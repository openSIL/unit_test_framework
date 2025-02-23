/**
 * @file PieRasInitUt.c
 * @brief Unit tests for FabricPieRasInit
 *
 * Iterations:
 * -AmdFabricWdtCntSel: Set xSimData's AmdFabricWdtCntSel to 0xFF
 * -HwaStsLowValue:     Enter the DfXGetNumberOfProcessorsPresent and DfGetNumberOfDiesOnSocket loops 
 *                      set HwaStsLow's Value with DfXFabricRegisterAccRead return values.     
 * -CtrlInstance:       Enter the DfGlblCtrlInstanceIds loop 
 */


#include <UtBaseLib.h>
#include <UtLogLib.h>
#include <stdlib.h>
#include "FabricPieRasInit.h"
#include <DF/DfX/SilFabricRegistersDfX.h>

HOST_DEBUG_SERVICE mHostDebugService;
#define FABRIC_REG_ACC_BC    (0xFF)

static bool NumberOfProcessors = true; 
uint32_t DfXGetNumberOfProcessorsPresent (void){
  if(NumberOfProcessors)
    return 1;
  else return 0; 
};
uint32_t DfGetNumberOfDiesOnSocket (void){
  return 1;
};

static bool RegisterAccValue = true; 
static int RegisterAccNum = -1; 
uint32_t DfXFabricRegisterAccRead(
  uint32_t Socket,
  uint32_t Function, 
  uint32_t Offset, 
  uint32_t Instance){
  if (RegisterAccValue && RegisterAccNum >= -1) {
    RegisterAccNum++;   
    return 1 << RegisterAccNum;
  } else {
    return 0x00000000; 
  }
}

void
DfXFabricRegisterAccWrite (
  uint32_t Socket,
  uint32_t Function,
  uint32_t Offset,
  uint32_t Instance,
  uint32_t Value
  ){
    return;
};


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
      
      if(strcmp(IterationName, "AmdFabricWdtCntSel") == 0)
      {
          // Arrange
          DFCLASS_INPUT_BLK* xSimData = (DFCLASS_INPUT_BLK*)malloc(sizeof(DFCLASS_INPUT_BLK));
          memset(xSimData, 0, sizeof(DFCLASS_INPUT_BLK));
          xSimData->AmdFabricWdtCntSel = 0xFF; 
          RegisterAccValue = false;
          NumberOfProcessors = false; 
          // Act 
          FabricPieRasInit(xSimData);
          Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
          "Call FabricPieRasInit");
          // Assert  
      }
      else if(strcmp(IterationName, "HwaStsLowValue") == 0)
      {
          // Arrange
          DFCLASS_INPUT_BLK* xSimData = (DFCLASS_INPUT_BLK*)malloc(sizeof(DFCLASS_INPUT_BLK));
          memset(xSimData, 0, sizeof(DFCLASS_INPUT_BLK));

          uint32_t *ids = (uint32_t *)malloc(2 * sizeof(uint32_t));
          ids[0] = 0xFFFFFFFF;
          xSimData->DfGlblCtrlInstanceIds = ids;

          // Act 
          FabricPieRasInit(xSimData);
          Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
          "Call FabricPieRasInit");
          // Assert  
      }
      else if(strcmp(IterationName, "CtrlInstance") == 0)
      {
          // Arrange
          DFCLASS_INPUT_BLK* xSimData = (DFCLASS_INPUT_BLK*)malloc(sizeof(DFCLASS_INPUT_BLK));
          memset(xSimData, 0, sizeof(DFCLASS_INPUT_BLK));

          uint32_t *ids = (uint32_t *)malloc(2 * sizeof(uint32_t));
          ids[0] = 1;
          ids[1] = 0xFFFFFFFF;
          xSimData->DfGlblCtrlInstanceIds = ids;

          RegisterAccValue = true;
          RegisterAccNum = -10; 

          // Act 
          FabricPieRasInit(xSimData);
          Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, 
          "Call FabricPieRasInit");
          // Assert  
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
 