/**
 * @file  InitializeResourceManagerDfXTp1Ut.h
 * @brief Ut for InitializeResourceManagerDfXTp1Ut
 *
 */
/* Copyright 2021-2023 Advanced Micro Devices, Inc. All rights reserved.    */
// SPDX-License-Identifier: MIT
#ifndef __INITIALIZERESOURCEMANAGERDFXTP1UT_H__
#define __INITIALIZERESOURCEMANAGERDFXTP1UT_H__

#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <xSIM.h>
#include <Io.h>
#include <Mmio.h>
#include <SmnAccess.h>
#include <SilCommon.h>

#include <Include/Library/UtxSIMMockLib.h>
#include <Include/Library/UtSilServicesMockLib.h>

#include <Utils.h>
#include <DF/Df.h>
#include <DF/Common/SilFabricInfo.h>
#include <MsrReg.h>

#include <xSIM-api.h>
#include <RcMgr/DfX/FabricRcInitDfX.h>

HOST_DEBUG_SERVICE mHostDebugService = NULL;

/* Stubs for resolving the unresolved external symbols. */
/*
 * SilFindStructure
 *  This is a host API function, so you can find the
 *  prototype, text description and Doxygen text in xSim-api.h
 */
void*
SilFindStructure (
  SIL_DATA_BLOCK_ID structureID,
  uint16_t          InstanceNum
  )
{
  return xUslFindStructure (structureID, InstanceNum);
};

void
SilGetPrimaryRb (
  uint32_t *SocketNum,
  uint32_t *RootBridgeNum
  )
{
  return;
}

uint8_t
xUslGetPhysAddrSize (
  void
  )
{
  return 0;
}

uint8_t
xUslGetPhysAddrReduction (
  void
  )
{
  return 0;
}

void
SilSetMmioReg4 (
  uint8_t   TotalSocket,
  uint8_t   MmioPairIndex,
  uint32_t  SktNum,
  uint32_t  RbNum,
  uint64_t  BaseAddress,
  uint64_t  Length
  )
{
  return;
}

void
SilSetIoReg4 (
  uint8_t  TotalSocket,
  uint8_t  RegIndex,
  uint32_t SktNum,
  uint32_t RbNum,
  uint32_t IoBase,
  uint32_t IoSize
  )
{
  return;
}

void
SilAdditionalMmioSetting4 (
  DFX_RCMGR_INPUT_BLK *SilData,
  uint64_t            BottomOfCompat,
  bool                ReservedRegionAlreadySet
  )
{
  return;
}

void
DfXSilGetPhySktRbNum (
  uint32_t  LogSktNum,
  uint32_t  LogRbNum,
  uint32_t  *PhySktNum,
  uint32_t  *PhyRbNum,
  bool *LogToPhyMapInit,
  FABRIC_RB_LOG_TO_PHY_MAP *pLogToPhyMap
  )
{
  return;
}

SIL_STATUS
SilInitPciBusBasedOnNvVariable4 (
  DFX_RCMGR_INPUT_BLK *SilData
  )
{
  return SilPass;
}

SIL_STATUS
SilInitIoBasedOnNvVariable4 (
  DFX_RCMGR_INPUT_BLK     *SilData,
  FABRIC_ADDR_SPACE_SIZE  *SpaceStatus,
  bool                    SetDfRegisters
  )
{
  return SilPass;
}

SIL_STATUS
SilInitMmioBasedOnNvVariable4 (
  DFX_RCMGR_INPUT_BLK     *SilData,
  FABRIC_ADDR_SPACE_SIZE  *SpaceStatus,
  bool                    SetDfRegisters
  )
{
  return SilPass;
}

uint64_t
xUslRdMsr (
  uint32_t MsrAddress
  )
{
  return 0;
}

void
xUslWrMsr (
  uint32_t MsrAddress,
  uint64_t MsrValue
  )
{
  return;
}

void
xUslMsrAnd (
  uint32_t Index,
  uint64_t AndData
  )
{
  return;
}

void xUslMsrOr (
  uint32_t Index,
  uint64_t OrData
  )
{
  return;
}

void
xUslMsrAndThenOr (
  uint32_t Index,
  uint64_t AndData,
  uint64_t OrData
  )
{
  return;
}

bool xUslIsComputeUnitPrimary (
  void
  )
{
  return TRUE;
}


#endif