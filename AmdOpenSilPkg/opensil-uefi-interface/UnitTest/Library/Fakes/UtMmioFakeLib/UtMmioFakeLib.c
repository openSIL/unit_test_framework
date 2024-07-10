/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtMmioFakeLib.c
 * @brief MMIO Access Fake Library
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <Mmio.h>

static uint8_t MMIO[MMIO_ADDRESS_SIZE] = {0};

uint8_t
xUSLMemRead8 (
  const volatile void *Addr
  )
{
  return MMIO[(size_t)Addr-MMIO_ADDRESS_MIN_MOCK_VAL];
}

uint16_t
xUSLMemRead16 (
  const volatile void *Addr
  )
{
  return *((uint16_t*)&MMIO[(size_t)Addr-MMIO_ADDRESS_MIN_MOCK_VAL]);
}

uint32_t
xUSLMemRead32 (
  const volatile void *Addr
  )
{
  return *((uint32_t*)&MMIO[(size_t)Addr-MMIO_ADDRESS_MIN_MOCK_VAL]);
}

void
xUSLMemWrite8 (
  volatile void *Addr,
  uint8_t Value
  )
{
  MMIO[(size_t)Addr-MMIO_ADDRESS_MIN_MOCK_VAL] = Value;
}

void
xUSLMemWrite16 (
  volatile void *Addr,
  uint16_t Value
  )
{
  *((uint16_t*)&MMIO[(size_t)Addr-MMIO_ADDRESS_MIN_MOCK_VAL]) = Value;
}

void
xUSLMemWrite32 (
  volatile void *Addr,
  uint32_t Value
  )
{
  *((uint32_t*)&MMIO[(size_t)Addr-MMIO_ADDRESS_MIN_MOCK_VAL])= Value;
}

void
xUSLMemReadModifyWrite8 (
  void *Addr,
  uint8_t AndMask,
  uint8_t OrMask
  )
{
  xUSLMemWrite8 (Addr, (xUSLMemRead8 (Addr) & AndMask) | OrMask);
}

void
xUSLMemReadModifyWrite16 (
  void *Addr,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  xUSLMemWrite16 (Addr, (xUSLMemRead16 (Addr) & AndMask) | OrMask);
}

void
xUSLMemReadModifyWrite32 (
  void *Addr,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  xUSLMemWrite32 (Addr, (xUSLMemRead32 (Addr) & AndMask) | OrMask);
}
