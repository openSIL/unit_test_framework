/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  PciExpress.h
 * @brief openSIL PCIe access functions prototype
 *
 */

#pragma once

#define PCIE_MMIO_ADDRESS_MIN_VAL    0xE0000000     // 32 bit PCIe Base
#define PCIE_MMIO_ADDRESS_MAX_VAL    0xEFFFFFFF

#define PCI_READ   0
#define PCI_WRITE  1

#ifdef __cplusplus
extern "C" {
#endif

uint8_t
xUSLPciExpressRead8 (
  void *Addr
  );

uint16_t
xUSLPciExpressRead16 (
  void *Addr
  );

uint32_t
xUSLPciExpressRead32 (
  void *Addr
  );

uint64_t
xUSLPciExpressRead64 (
  void *Addr
  );

void
xUSLPciExpressWrite8 (
  void *Addr,
  uint8_t Value
  );

void
xUSLPciExpressWrite16 (
  void *Addr,
  uint16_t Value
  );

void
xUSLPciExpressWrite32 (
  void *Addr,
  uint32_t Value
  );

void
xUSLPciExpressWrite64 (
  void *Addr,
  uint64_t Value
  );

#ifdef __cplusplus
}
#endif
