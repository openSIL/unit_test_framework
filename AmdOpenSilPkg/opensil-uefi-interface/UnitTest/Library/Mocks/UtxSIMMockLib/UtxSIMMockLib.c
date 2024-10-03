/* Copyright (C) 2022 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtxSIMMockLib.c
 * @brief Defines cpu specific common operations
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <Sil-api.h>
#include <xSIM-api.h>
#include <setjmp.h>
#include <cmocka.h>

/**
 * SilCreateInfoBlock (Mock)
 *
 * @brief Create an Info Block
 *
 * @details This is a Mock implementation of SilCreateInfoBlock from xSIM.c
 *
 * This is a mock function
 * @param BlockTag - IP block unique identifier
 * @param BlockSize - size of the requested block
 * @param Block_Instance - Instance of block using this ID
 * @param Block_MajorRev - Revision of the IP data structure used
 * @param Block_MinorRev  - Revision (minor) of the IP data struct used.
 * @return pointer to the IP data segment of the assigned memory space.
 *
 */
void *
SilCreateInfoBlock (
  uint32_t        BlockTag,
  size_t          BlockSize,
  uint16_t        Block_Instance,
  uint8_t         Block_MajorRev,
  uint8_t         Block_MinorRev
  )
{
  check_expected (BlockTag);
  return mock_ptr_type(void *);
}

// Mock arming functions

/**
 * MockSilCreateInfoBlockOnce
 *
 * @brief Arm expected return value for a single call to SilCreateInfoBlock
 *
 * @param ExpectedReturn  The expected return value from SilCreateInfoBlock.
 *
 *                        - In a passing case, this parameter should be a pointer to a buffer of size BlockSize.
 *                        - In a failing case, this parameter should be NULL.
 *
 */
void
MockSilCreateInfoBlockOnce (
  void            *ExpectedReturn
  )
{
  // Verify BlockTag is within the range defined by SIL_DATA_BLOCK_ID
  expect_in_range (SilCreateInfoBlock, BlockTag, (uint32_t)SilId_SocCommon, ((uint32_t)SilId_ListEnd - 1));
  will_return (SilCreateInfoBlock, ExpectedReturn);
}
