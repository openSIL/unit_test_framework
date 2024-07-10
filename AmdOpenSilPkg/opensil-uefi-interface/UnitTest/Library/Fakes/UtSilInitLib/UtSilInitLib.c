/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtSilInitLib.c
 * @brief
 */

#include <xSIM.h>
#include <stdlib.h>
#include <string.h>
#include <xSIM-api.h>
#include <SilCommon.h>

#define SIL_SERVICES_MEMORY_SIZE     (256*1024ul)
void *mSilMemoryBase;

/**
 * UtSilInit
 * @brief Allocates the required memory on the host to accommodate
 * for some of openSIL APIs (e.g. SilCreateInfoBlock, xUslFindStructure)
 *
 * @retval SIL_STATUS
 */
SIL_STATUS
UtSilInit (
  void
  )
{
  if (mSilMemoryBase != NULL) {
    // mSilMemoryBase is already allocated.
    return SilPass;
  }
  size_t MemorySize = SIL_SERVICES_MEMORY_SIZE;
  mSilMemoryBase = malloc(MemorySize);
  if (mSilMemoryBase == NULL) {
    return SilAborted;
  }
  ((SIL_BLOCK_VARIABLES*)mSilMemoryBase)->HostBlockSize = MemorySize;
  ((SIL_BLOCK_VARIABLES*)mSilMemoryBase)->FreeSpaceOffset = sizeof(SIL_BLOCK_VARIABLES);
  ((SIL_BLOCK_VARIABLES*)mSilMemoryBase)->FreeSpaceLeft = (uint32_t)(MemorySize-sizeof(SIL_BLOCK_VARIABLES));
  return SilPass;
}

/**
 * UtSilDeinit
 * @brief Deallocates the memory allocation by UtSilInit
 *
 * @retval SIL_STATUS
 */
SIL_STATUS
UtSilDeinit (
  void
  )
{
  if (mSilMemoryBase == NULL) {
    return SilPass;
  }
  free (mSilMemoryBase);
  mSilMemoryBase = NULL;
  return SilPass;
}
