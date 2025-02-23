/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtxUslCcxRolesMockLib.h
 * @brief This header contains definitions used by UtxUslCcxRolesMockLib
 *
 */
#pragma once

void
MockxUslIsComputeUnitPrimary (
    bool ExpectedComputeStatus
    );

bool
xUslIsComputeUnitPrimary (
    void
    );