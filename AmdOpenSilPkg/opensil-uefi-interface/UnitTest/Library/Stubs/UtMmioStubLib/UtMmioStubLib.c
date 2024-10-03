/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtMmioStubLib.c
 * @brief MMIO Access Stub Library
 *
 */

#include <stdint.h>
#include <Mmio.h>

uint8_t
xUSLMemRead8 (
  const volatile void *Addr
  )
{
  return 0x00;
}

uint16_t
xUSLMemRead16 (
  const volatile void *Addr
  )
{
  return 0x00;
}

uint32_t
xUSLMemRead32 (
  const volatile void *Addr
  )
{
  return 0x00;
}

void
xUSLMemWrite8 (
  volatile void *Addr,
  uint8_t Value
  )
{
  return;
}

void
xUSLMemWrite16 (
  volatile void *Addr,
  uint16_t Value
  )
{
  return;
}

void
xUSLMemWrite32 (
  volatile void *Addr,
  uint32_t Value
  )
{
  return;
}

void
xUSLMemReadModifyWrite8 (
  void *Addr,
  uint8_t AndMask,
  uint8_t OrMask
  )
{
  return;
}

void
xUSLMemReadModifyWrite16 (
  void *Addr,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  return;
}

void
xUSLMemReadModifyWrite32 (
  void *Addr,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  return;
}
