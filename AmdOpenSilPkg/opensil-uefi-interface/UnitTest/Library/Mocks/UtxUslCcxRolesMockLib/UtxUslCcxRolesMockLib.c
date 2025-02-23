/* Copyright (C) 2022 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtxUslCcxRolesMockLib.c
 * @brief Defines cpu helper function definition.
 *
 */

#include <SilCommon.h> 

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

bool
xUslIsComputeUnitPrimary (
    void
    )
{
     return mock_type(bool);
}

/**
 * MockxUslIsComputeUnitPrimary
 *
 * @brief xUslIsComputeUnitPrimary should return false or true value 
 *
 * @param boll Expected Compute Unit Primary Status  
 */
void
MockxUslIsComputeUnitPrimary (
    bool ExpectedComputeStatus 
    )
{
  will_return(xUslIsComputeUnitPrimary, ExpectedComputeStatus);
}
