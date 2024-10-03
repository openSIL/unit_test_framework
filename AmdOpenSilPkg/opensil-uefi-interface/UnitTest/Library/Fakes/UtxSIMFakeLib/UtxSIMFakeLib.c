/* Copyright (C) 2022 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtxSIMFakeLib.c
 * @brief Defines cpu specific common operations
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <Sil-api.h>
#include <Library/UtxSIMFakeLib.h>
#include <xSIM-api.h>
#include <setjmp.h>
#include <cmocka.h>

uint8_t TempInfoBlock[sizeof(SIL_INFO_BLOCK_HEADER) + MAX_INFO_BLOCK_SIZE] = {0};

/**
 * SilCreateInfoBlock (Fake)
 *
 * @brief Create an Info Block
 *
 * @details This is a fake implementation of SilCreateInfoBlock from xSIM.c
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
  size_t                RequestSize;
  SIL_INFO_BLOCK_HEADER *Header = NULL;

  assert_true (BlockSize <= MAX_INFO_BLOCK_SIZE);

  Header = (SIL_INFO_BLOCK_HEADER *)TempInfoBlock;
  RequestSize = BlockSize + sizeof (SIL_INFO_BLOCK_HEADER);

  // Fill the Info Block
  Header->Id        = BlockTag;
  Header->InfoBlockDataSize = (uint32_t)(RequestSize & 0xFFFFFFFF);
  Header->Instance  = Block_Instance;
  Header->RevMajor  = Block_MajorRev;
  Header->RevMinor  = Block_MinorRev;
  return (void *)Header->InfoBlockData;
}
