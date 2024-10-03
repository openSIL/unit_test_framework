/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtPciStubLib.c
 * @brief PCI/PCIe Stub Library
 *
 */

#include <stdint.h>
#include <Pci.h>

uint8_t
xUSLPciRead8 (
  uint32_t Address
  )
{
  return 0x00;
}

void
xUSLPciWrite8 (
  uint32_t Address,
  uint8_t Value
  )
{
  return;
}

uint16_t
xUSLPciRead16 (
  uint32_t Address
  )
{
  return 0x00;
}

void
xUSLPciWrite16 (
  uint32_t Address,
  uint16_t Value
  )
{
  return;
}

uint32_t
xUSLPciRead32 (
  uint32_t Address
  )
{
  return 0x00;
}

void
xUSLPciWrite32 (
  uint32_t Address,
  uint32_t Value
  )
{
  return;
}

uint64_t
xUSLPciRead64 (
  uint32_t Address
  )
{
  return 0x00;
}

void
xUSLPciWrite64 (
  uint32_t Address,
  uint64_t Value
  )
{
  return;
}

void
xUSLPciReadModifyWrite8 (
  uint32_t Address,
  uint8_t AndMask,
  uint8_t OrMask
  )
{
  return;
}

void
xUSLPciReadModifyWrite16 (
  uint32_t Address,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  return;
}

void
xUSLPciReadModifyWrite32 (
  uint32_t Address,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  return;
}

void
xUSLIndirectPciRead32 (
  volatile uint32_t PciBase,
  uint32_t IndexAddress,
  uint32_t *Value
  )
{
  return;
}

void
xUSLIndirectPciWrite32 (
  volatile uint32_t PciBase,
  uint32_t IndexAddress,
  uint32_t Value
  )
{
  return;
}

void
xUSLPciRead (
  uint32_t Address,
  ACCESS_WIDTH Width,
  void *Value
  )
{
  return;
}

void
xUSLPciRMW(
  uint32_t Address,
  ACCESS_WIDTH Width,
  uint32_t Mask,
  uint32_t Value
  )
{
  return;
}

void
xUSLPciWrite (
  uint32_t Address,
  ACCESS_WIDTH Width,
  void *Value
  )
{
  return;
}
