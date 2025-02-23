/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  PcieEnumerateAndHarvestWrUt.h
 * @brief
 *
 */

#pragma once

#include <xSIM.h>
#include <CommonLib/SmnAccess.h>
#include <NbioSmnTable.h>
#include "GnbRegisters.h"
#include "NbioData.h"
#include <NBIO/NbioCommon.h>
#include <NBIO/GnbDxio.h>
#include <NBIO/NbioPcieTopologyHelper.h>
#include <NBIO/IOD/include/GlobalRegB0.h>
#include <NBIO/IOD/include/SyshubmmReg.h>
#include <NbioPcie.h>
#include <SilSocLogicalId.h>

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>
#include <NBIO/Nbio.h>
#include "NbioDefaults.h"
#include "NbioIohcTbl.h"
#include "NbioIoapicTbl.h"
#include "NbioNbifTbl.h"
#include "NbioWorkaroundTbl.h"


