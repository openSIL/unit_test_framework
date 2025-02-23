/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  CcxGetCacWeightsUt.h
 * @brief
 *
 */

#pragma once

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>
#include <stdlib.h>     
#include <time.h>       
#include <stdbool.h>    
#include <xSIM.h>       
#include <CCX/Common/Ccx.h> 
#include <Include/MsrReg.h>
#include <Include/Library/UtSilServicesMockLib.h>

SIL_STATUS SmuReadCacWeightsUt (
  uint32_t  MaxNumWeights,
  uint64_t  *ApmWeights
);