/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtSmnAccessStubLib.c
 * @brief SMN Access Stub Library
 *
 */

#include <stdint.h>
#include <SilCommon.h>

uint32_t
xUSLSmnRead (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress
  )
{
  return 0x00;
}

void
xUSLSmnWrite (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress,
  uint32_t    Value
  )
{
  return;
}

void
xUSLSmnReadModifyWrite (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress,
  uint32_t    AndMask,
  uint32_t    OrMask
  )
{
  return;
}

uint8_t
xUSLSmnRead8 (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress
  )
{
  return 0x00;
}

void
xUSLSmnWrite8 (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress,
  uint8_t     Value8
  )
{
  return;
}

void
xUSLSmnReadModifyWrite8 (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress,
  uint8_t     AndMask,
  uint8_t     OrMask
  )
{
  return;
}
