/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtIoStubLib.c
 * @brief IO Access Stub Library
 *
 */

#include <stdint.h>
#include <Io.h>

void
xUSLIoWrite8 (
  uint16_t Port,
  uint8_t Value
  )
{
  return;
}

void
xUSLIoWrite16 (
  uint16_t Port,
  uint16_t Value
  )
{
  return;
}

void
xUSLIoWrite32 (
  uint16_t Port,
  uint32_t Value
  )
{
  return;
}

uint8_t
xUSLIoRead8 (
  uint16_t Port
  )
{
  return 0x00;
}

uint16_t
xUSLIoRead16 (
  uint16_t Port
  )
{
  return 0x00;
}

uint32_t
xUSLIoRead32 (
  uint16_t Port
  )
{
  return 0x00;
}

void
xUSLIoReadModifyWrite8 (
  uint16_t Port,
  uint8_t  AndMask,
  uint8_t  OrMask
  )
{
  return;
}

void
xUSLIoReadModifyWrite16 (
  uint16_t Port,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  return;
}

void
xUSLIoReadModifyWrite32 (
  uint16_t Port,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  return;
}
