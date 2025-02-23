/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
/**
* @file DfGetProcessorInfoUt.h
* @brief
*
*/

#include <xPRF-api.h>
#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>
#include <Library/UtSilServicesMockLib.h>
#include <DF/Common/DfCmn2Rev.h>
#include <DF/Common/BaseFabricTopologyCmn.h>


UINT32
GetNumberOfProcessorsPresentUt (
  void
  );

UINT32
GetNumberOfRootBridgesOnSocketUt (
  UINT32               Socket
  );

UINT32
GetNumberOfSystemDiesUt (
  void
  );
 