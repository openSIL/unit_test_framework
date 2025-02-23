/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtCpuOpsMockLib.h
 * @brief This header contains definitions used by UtCpuOpsMockLib
 *
 */
#pragma once

#include <Uefi.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdbool.h>
#include <Io.h>

void MockxUslIsComputeUnitPrimary(
    bool ExpectedValue
    );
