/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtPcieStubLib.c
 * @brief PCI/PCIe Stub Library
 *
 */

#include <stdint.h>

uint8_t
xUSLPciExpressRead8 (
  void *Addr
  )
{
  return 0x00;
}

uint16_t
xUSLPciExpressRead16 (
  void *Addr
  )
{
  return 0x00;
}

uint32_t
xUSLPciExpressRead32 (
  void *Addr
  )
{
  return 0x00;
}

uint64_t
xUSLPciExpressRead64 (
  void *Addr
  )
{
  return 0x00;
}

void
xUSLPciExpressWrite8 (
  void *Addr,
  uint8_t Value
  )
{
  return;
}

void
xUSLPciExpressWrite16 (
  void *Addr,
  uint16_t Value
  )
{
  return;
}

void
xUSLPciExpressWrite32 (
  void *Addr,
  uint32_t Value
  )
{
  return;
}

void
xUSLPciExpressWrite64 (
  void *Addr,
  uint64_t Value
  )
{
  return;
}
