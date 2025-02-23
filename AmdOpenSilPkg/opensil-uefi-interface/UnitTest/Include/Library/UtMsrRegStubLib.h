/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtMsrRegStubLib.h
 * @brief This header contains definitions used by UtMsrRegStubLib
 *
 */

 #pragma once

void xUslWrMsr(
    uint32_t msrAddress, 
    uint64_t msrValue
    );

uint64_t xUslRdMsr (
    uint32_t MsrAddress
    );

void xUslMsrAndThenOr (
    uint32_t Index, 
    uint64_t AndData, 
    uint64_t OrData
    );

void xUslMsrOr (
    uint32_t Index, 
    uint64_t OrData
    );

void xUslMsrAnd (
    uint32_t Index, 
    uint64_t AndData
    );


