/**
 * @file  InitializeResourceManagerDfXTp3Ut.h
 * @brief Ut for InitializeResourceManagerDfXTp3Ut
 *
 */
/* Copyright 2021-2023 Advanced Micro Devices, Inc. All rights reserved.    */
// SPDX-License-Identifier: MIT
#ifndef __INITIALIZERESOURCEMANAGERDFXTP3UT_H__
#define __INITIALIZERESOURCEMANAGERDFXTP3UT_H__

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

#include <Utils.h>
#include <DF/Df.h>
#include <DF/Common/SilFabricInfo.h>
#include <MsrReg.h>

#include <xSIM-api.h>
#include <RcMgr/DfX/FabricRcInitDfX.h>

#endif