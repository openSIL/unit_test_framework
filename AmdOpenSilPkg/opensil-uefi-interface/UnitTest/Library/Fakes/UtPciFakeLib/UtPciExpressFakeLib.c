/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtPcieFakeLib.c
 * @brief PCI/PCIe Fake Library
 *
 */

#include <SilCommon.h>
#include <Pci.h>
#include <PciExpress.h>

static uint8_t PCIEMMIO[PCIE_MMIO_ADDRESS_MAX_VAL-PCIE_MMIO_ADDRESS_MIN_VAL+1] = {0};


uint8_t
xUSLPciExpressRead8 (
  void *Addr
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  return PCIEMMIO[Index];
}

uint16_t
xUSLPciExpressRead16 (
  void *Addr
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  return *((uint16_t*)&PCIEMMIO[Index]);
}

uint32_t
xUSLPciExpressRead32 (
  void *Addr
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  return *((uint32_t*)&PCIEMMIO[Index]);
}

uint64_t
xUSLPciExpressRead64 (
  void *Addr
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  return *((uint64_t*)&PCIEMMIO[Index]);
}

void
xUSLPciExpressWrite8 (
  void *Addr,
  uint8_t Value
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  PCIEMMIO[Index] = Value;
}

void
xUSLPciExpressWrite16 (
  void *Addr,
  uint16_t Value
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  *((uint16_t*)&PCIEMMIO[Index]) = Value;
}

void
xUSLPciExpressWrite32 (
  void *Addr,
  uint32_t Value
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  *((uint32_t*)&PCIEMMIO[Index]) = Value;
}

void
xUSLPciExpressWrite64 (
  void *Addr,
  uint64_t Value
  )
{
  size_t Index;

  Index = (size_t)Addr - PCIE_MMIO_ADDRESS_MIN_VAL;
  *((uint64_t*)&PCIEMMIO[Index]) = Value;
}
