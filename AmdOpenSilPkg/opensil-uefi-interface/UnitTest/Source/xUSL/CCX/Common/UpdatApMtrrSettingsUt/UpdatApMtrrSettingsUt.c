/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file ApupdateMtrrSettingsUt.c
 * @brief
 *
 */

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <SilCommon.h>
#include <Ccx.h>
#include <CcxCmn2Rev.h>
#include <MsrReg.h>
#include <CommonLib/CpuLib.h>
#include <xUslCcxRoles.h>
#include <DF/DfIp2Ip.h>
#include <RAS/Common/Ras.h>

// STUBS
void xUslWrMsr(uint32_t MsrAddress, uint64_t MsrValue)
{
  return;
}

uint64_t xUslRdMsr(uint32_t MsrAddress)
{
  return 0;
}

uint8_t xUslGetThreadsPerCore(void)
{
  return 8;
}

bool xUslIsComputeUnitPrimary(void)
{
  return true;
}
// STUBS END

AMD_UNIT_TEST_STATUS
EFIAPI
TestPrerequisite(
    IN AMD_UNIT_TEST_CONTEXT Context)
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK *)UtGetActiveFrameworkHandle();
  const char *TestName = UtGetTestName(Ut);
  const char *IterationName = UtGetTestIteration(Ut);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) Prerequisite started.", TestName, IterationName);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) Prerequisite ended.", TestName, IterationName);
  return AMD_UNIT_TEST_PASSED;
}

void
    EFIAPI
    TestBody(
        IN AMD_UNIT_TEST_CONTEXT Context)
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK *)UtGetActiveFrameworkHandle();
  const char *TestName = UtGetTestName(Ut);
  const char *IterationName = UtGetTestIteration(Ut);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) Test started.", TestName, IterationName);

  if (strcmp(IterationName, "AMD_AP_MTRR_FIX64k_00000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr250 = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX64k_00000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr250)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr250 not correctly copied to MsrAddr AMD_AP_MTRR_FIX64k_00000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX16k_80000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr258 = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX16k_80000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr258)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr258 not correctly copied to MsrAddr AMD_AP_MTRR_FIX16k_80000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX16k_A0000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr259 = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX16k_A0000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr259)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr259 not correctly copied to MsrAddr AMD_AP_MTRR_FIX16k_A0000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_C0000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr268 = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_C0000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr268)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr268 not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_C0000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_C8000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr269 = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_C8000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr269)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr269 not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_C8000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_D0000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr26A = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_D0000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr26A)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr26A not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_D0000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_D8000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr26B = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_D8000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr26B)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr26B not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_D8000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_E0000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr26C = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_E0000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr26C)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr26C not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_E0000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_E8000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr26D = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_E8000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr26D)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr26D not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_E8000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_F0000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr26E = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_F0000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr26E)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr26E not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_F0000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else if (strcmp(IterationName, "AMD_AP_MTRR_FIX4k_F8000") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr26F = 0x000000000001};
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {AMD_AP_MTRR_FIX4k_F8000, 0}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != CcxInputBlock.AmdFixedMtrr26F)
    {
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "AmdFixedMtrr26F not correctly copied to MsrAddr AMD_AP_MTRR_FIX4k_F8000");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
    else if (strcmp(IterationName, "InvalidAddress") == 0)
  {
    // Arrange
    CCXCLASS_INPUT_BLK CcxInputBlock = {.AmdFixedMtrr26F = 0x000000000001};
    const int initialMsrData = 0;
    const int invalidMsrAddr = 0;
    AP_MTRR_SETTINGS ApMtrrSettingsList[2] = {
        {invalidMsrAddr, initialMsrData}, {CPU_LIST_TERMINAL, 0}};

    // Act
    UpdateApMtrrSettings(ApMtrrSettingsList, &CcxInputBlock);

    // Assert
    if (ApMtrrSettingsList[0].MsrData != initialMsrData) //Invalid address so it shouldn't have changed the MsrData.
    {
      
      Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__, "MsrData value has been changed despite invalid MsrAddr");
      UtSetTestStatus(Ut, AMD_UNIT_TEST_FAILED);
    }
    else
    {
      UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);
    }
  }
  else
  {
    Ut->Log(AMD_UNIT_TEST_LOG_ERROR, __FUNCTION__, __LINE__,
            "Iteration '%s' is not implemented.", IterationName);
    UtSetTestStatus(Ut, AMD_UNIT_TEST_ABORTED);
  }

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test context is: %s.", (char *)Context);
  UtSetTestStatus(Ut, AMD_UNIT_TEST_PASSED);

  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) Test ended.", TestName, IterationName);
}

AMD_UNIT_TEST_STATUS
EFIAPI
TestCleanUp(
    IN AMD_UNIT_TEST_CONTEXT Context)
{
  AMD_UNIT_TEST_FRAMEWORK *Ut = (AMD_UNIT_TEST_FRAMEWORK *)UtGetActiveFrameworkHandle();
  const char *TestName = UtGetTestName(Ut);
  const char *IterationName = UtGetTestIteration(Ut);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) CleanUp started.", TestName, IterationName);
  Ut->Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
          "%s (Iteration: %s) CleanUp ended.", TestName, IterationName);
  return AMD_UNIT_TEST_PASSED;
}

int main(
    int argc,
    char *argv[])
{
  AMD_UNIT_TEST_STATUS Status;
  AMD_UNIT_TEST_FRAMEWORK Ut;

  // Initializing the UnitTest framework
  Status = UtInitFromArgs(
      &Ut,
      argc,
      argv);
  if (Status != AMD_UNIT_TEST_PASSED)
  {
    return Status;
  }

  char *SimpleCharContext = "A simple TestBody context";

  // Logging the start of the test.
  // Note: Test status at this time is set to "NOT_SET".
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__,
         "Test %s started. TestStatus is %s.", UtGetTestName(&Ut), UtGetTestStatusString(&Ut));

  // You can pass into the TestPrerequisite, TestBody, and TestCleanUp context of
  // your desire
  UtSetTestContext(&Ut, (AMD_UNIT_TEST_CONTEXT)SimpleCharContext);

  // Running the test
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Running test.");
  UtRunTest(&Ut);

  // Freeing up all framework related allocated memories
  Ut.Log(AMD_UNIT_TEST_LOG_INFO, __FUNCTION__, __LINE__, "Test %s ended.", UtGetTestName(&Ut));
  UtDeinit(&Ut);

  return AMD_UNIT_TEST_PASSED;
}
