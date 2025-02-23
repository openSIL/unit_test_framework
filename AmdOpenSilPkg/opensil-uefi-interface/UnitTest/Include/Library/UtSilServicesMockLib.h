/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtSilServicesMockLib.h
 * @brief This header contains definitions used by UtSilServicesMockLib
 *
 */
#pragma once

void
MockSilGetCommon2RevXferTableOnce (
  void            *ExpectedXferTable,
  SIL_STATUS      ExpectedSilStatus
  );

void
MockSilGetCommon2RevXferTableManyTimes (
  void            *ExpectedXferTable,
  SIL_STATUS      ExpectedSilStatus,
  uint32_t        Count 
  );

void
MockSilInitCommon2RevXferTableOnce (
  void            *ExpectedXferTable,
  SIL_STATUS      ExpectedSilStatus
  );

void
MockSilGetIp2IpApiOnce (
  void            *ExpectedIpApi,
  SIL_STATUS      ExpectedSilStatus
  );

void
MockSilGetIp2IpManyTimes (
  void            *ExpectedIpApi,
  SIL_STATUS      ExpectedSilStatus,
  uint32_t        Count
  );

void
MockSilInitIp2IpApiOnce (
  void            *ExpectedIpApi,
  SIL_STATUS      ExpectedSilStatus
  );

void
MockxUslFindStructureOnce (
  void  *SilDataCommonPtr
  );

void *
xUslFindStructure (
  SIL_DATA_BLOCK_ID   IpId,
  uint16_t            InstanceNum
  );

SIL_STATUS
SilInitIp2IpApi (
  SIL_DATA_BLOCK_ID   IpId,
  void                *IpApi
  );

SIL_STATUS
SilGetIp2IpApi (
  SIL_DATA_BLOCK_ID   IpId,
  void                **Api
  );

SIL_STATUS
SilInitCommon2RevXferTable (
  SIL_DATA_BLOCK_ID   IpId,
  void                *XferTable
  );

SIL_STATUS
SilGetCommon2RevXferTable (
  SIL_DATA_BLOCK_ID   IpId,
  void                **XferTable
  );
