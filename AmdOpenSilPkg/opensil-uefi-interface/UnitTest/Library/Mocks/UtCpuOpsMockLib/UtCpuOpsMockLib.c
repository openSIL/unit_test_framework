/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtCpuOpsMockLib.c
 * @brief CPU Operation Mock Library
 *
 */

#include <Uefi.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdbool.h>
#include <Io.h>

bool 
xUslIsComputeUnitPrimary (
    void
    ) 
{
  return mock_type(bool);
}

/**
* xUslIsComputeUnitPrimary (Mock)
*
* @brief Mocks xUslIsComputeUnitPrimary function returning ture or false
*
* @param[in] ExpectedValue  Expected value which is return by xUslIsComputeUnitPrimary()
*
*/
void 
MockxUslIsComputeUnitPrimary(
    bool ExpectedValue
    )
{
    will_return(xUslIsComputeUnitPrimary, ExpectedValue);
}



