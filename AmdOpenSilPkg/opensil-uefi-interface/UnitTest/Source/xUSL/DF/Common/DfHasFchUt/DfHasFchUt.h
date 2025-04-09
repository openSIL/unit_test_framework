/**
 * @file  DfHasFchUt.h
 * @brief Common declarations of DfHasFchUt functions
 */
/* Copyright 2023 Advanced Micro Devices, Inc. All rights reserved.    */
// SPDX-License-Identifier: MIT

#ifndef __DFHASFCHUT_H__
#define __DFHASFCHUT_H__

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include <xSIM.h>
#include <UtBaseLib.h>
#include <UtLogLib.h>
#include <UtSilInitLib.h>

#include <Include/MsrReg.h>
#include <Include/Library/UtSilServicesMockLib.h>

#include <DF/Common/DfCmn2Rev.h>
#include <DF/Common/BaseFabricTopologyCmn.h>
#include <DF/Common/SilBaseFabricTopologyLib.h>

HOST_DEBUG_SERVICE mHostDebugService = NULL;

// const 
// AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
// DfFindDeviceTypeEntryInMapUt (
//   FABRIC_DEVICE_TYPE  Type
//   );

// void 
// MockDfFindDeviceTypeEntryInMapOnce (
//   const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *DeviceMap,
//   void  *ExpectedReturn
//   );

// const 
// AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
// DfGetDeviceMapOnDieUt (
//   void
//   );

// void 
// MockDfGetDeviceMapOnDieOnce (
//   const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *DeviceMap
//   );

// const 
// COMPONENT_LOCATION *
// DfFindComponentLocationMapUt (
//   uint32_t *Count, 
//   uint32_t *PhysIos0FabricId
//   );

// void 
// MockDfFindComponentLocationMapOnce (
//   const COMPONENT_LOCATION *Locations, 
//   uint32_t Count, 
//   uint32_t PhysIos0FabricId
//   );


// misc; added here for reference; may not be used
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