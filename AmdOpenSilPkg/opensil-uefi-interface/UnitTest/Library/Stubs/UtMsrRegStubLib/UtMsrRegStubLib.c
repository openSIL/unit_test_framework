/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtMsrRegStubLib.c
 * @brief Define Msr registers
 *
 */

#include <SilCommon.h> 
#include <MsrReg.h> 

void xUslWrMsr(
    uint32_t msrAddress, 
    uint64_t msrValue
    ) 
{
    return; 
}

uint64_t xUslRdMsr (
    uint32_t MsrAddress
    )
{
    return 0;
}

void xUslMsrAndThenOr (
    uint32_t Index, 
    uint64_t AndData, 
    uint64_t OrData
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

void xUslMsrAnd (
    uint32_t Index, 
    uint64_t AndData
    )
{
    return;
}
