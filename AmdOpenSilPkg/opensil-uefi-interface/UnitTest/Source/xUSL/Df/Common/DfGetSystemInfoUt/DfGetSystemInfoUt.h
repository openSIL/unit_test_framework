/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
/**
* @file DfGetSystemInfoUt.h
* @brief
*
*/
#include <xSIM.h>
#include <DF/Df.h>
#include <stdlib.h>
#include <xPRF-api.h>
#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>
#include <Library/UtSilServicesMockLib.h>
#include <DF/Common/DfCmn2Rev.h>
#include <DF/Common/BaseFabricTopologyCmn.h>
#include <DF/Common/SilBaseFabricTopologyLib.h>
#include <DF\DfX\SilFabricRegistersDfX.h>
#include <DF/DfX/DfXBaseFabricTopology.h>
#include <DF\DfX\FabricAcpiDomain\FabricAcpiDomainInfo.h>

// Stub
UINT32
DfXGetNumberOfProcessorsPresent (
  void
  );

UINT32
DfXGetNumberOfSystemDies (
  void
  );

UINT32 
DfXGetNumberOfSystemRootBridges (
  void
  );


// Fake
const AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP* 
DfXGetDeviceMapOnDie (
  void
  );

const COMPONENT_LOCATION* 
DfXFindComponentLocationMap (
  uint32_t *Count,
  uint32_t *PhysIos0FabricId
  );