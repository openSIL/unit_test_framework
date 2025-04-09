/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file Zen4DownCoreInit.c
 * @brief Unit tests for Zen4DownCoreInit
 *
 * Iterations:
 *
 */

#include "GetZen4DesiredCcdCountUt.h"

bool 
SocIsOneCcdModeSupported (
  void
  ) 
{
    return mock_type(bool);
}

void 
MockSocIsOneCcdModeSupportedOnce (
  bool ExpectedReturnValue
  ) 
{
    will_return(SocIsOneCcdModeSupported, ExpectedReturnValue);
}

void 
MockSocIsOneCcdModeSupportedManyTimes (
  bool ExpectedReturnValue, 
  uint32_t CallCount
  ) 
{
    will_return_count(SocIsOneCcdModeSupported, ExpectedReturnValue, CallCount);
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

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test started.", TestName, IterationName);

  // Common data structure used by all cases
  CCXCLASS_DATA_BLK LclCcxDataBlk = {0};
  uint32_t CcdDisMask             =  0;
  uint32_t DesiredCcdCount        =  0;

  if (strcmp(IterationName, "Case_CCD_MODE_11_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_11_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 11)         &&
      (CcdDisMask      == 0x00000800)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_10_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_10_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 10)         &&
      (CcdDisMask      == 0x00000C00)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_9_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_9_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 9)         &&
      (CcdDisMask      == 0x00000E00)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_8_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_8_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 8)         &&
      (CcdDisMask      == 0x00000F00)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_7_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_7_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 7)         &&
      (CcdDisMask      == 0x00000F80)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_6_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_6_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 6)         &&
      (CcdDisMask      == 0x00000FC0)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_5_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_5_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 5)         &&
      (CcdDisMask      == 0x00000FE0)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_4_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_4_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 4)         &&
      (CcdDisMask      == 0x00000FF0)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_3_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_3_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 3)         &&
      (CcdDisMask      == 0x00000FF8)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_CCD_MODE_2_CCDS") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_2_CCDS;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 2)         &&
      (CcdDisMask      == 0x00000FFC)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "TrueCase_CCD_MODE_1_CCD") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_1_CCD;
    MockSocIsOneCcdModeSupportedOnce(true);
    // SocIsOneCcdModeSupported = SocIsOneCcdModeSupportedTrue;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 1)         &&
      (CcdDisMask      == 0x00000FFE)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "FalseCase_CCD_MODE_1_CCD") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_1_CCD;
    MockSocIsOneCcdModeSupportedOnce(false);
    // SocIsOneCcdModeSupported = SocIsOneCcdModeSupportedFalse;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 0)         &&
      (CcdDisMask      == 0)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_Default_True") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_AUTO;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 0xFFFFFFFF)  &&
      (CcdDisMask      == 0x0)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 

  else if (strcmp(IterationName, "Case_Default_False") == 0) 
  {
    // Arrange
    LclCcxDataBlk.CcxInputBlock.AmdCcdMode = CCD_MODE_MAX;
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Arrange completed.");

    // Act
    GetZen4DesiredCcdCount( 
      LclCcxDataBlk.CcxInputBlock.AmdCcdMode,
      &CcdDisMask,
      &DesiredCcdCount
    );
    Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Acting completed.");

    // Assert
    if (
      (DesiredCcdCount == 0xFFFFFFFF)  &&
      (CcdDisMask      == 0x0)
    )
    {
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is true.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
    }
    else
    {  
      Ut->Log(AMD_UNIT_TEST_LOG_DEBUG, __FUNCTION__, __LINE__, "Assert is false.");
      UtSetTestStatus (Ut, AMD_UNIT_TEST_FAILED);
    }
  } 
  
  else {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "%s (Iteration: %s) Test ended at the 'else' case; this is a faulty behaviour.", TestName, IterationName);
    UtSetTestStatus (Ut, AMD_UNIT_TEST_ABORTED);
  }

  UtSetTestStatus (Ut, AMD_UNIT_TEST_PASSED);
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
  AMD_UNIT_TEST_STATUS Status;              // conv.
  AMD_UNIT_TEST_FRAMEWORK Ut;               // conv.

  // Initializing the UnitTest framework    // conv.
  Status = UtInitFromArgs (
    &Ut,
    argc,
    argv
  );
  if (Status != AMD_UNIT_TEST_PASSED) {
    return Status;
  }

  // Logging the start of the test.         // conv.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
    "Test %s started. TestStatus is %s.", UtGetTestName (&Ut), UtGetTestStatusString (&Ut));

  // Running test.                          // conv.
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest (&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName (&Ut));
  UtDeinit (&Ut);

  return AMD_UNIT_TEST_PASSED;
}
