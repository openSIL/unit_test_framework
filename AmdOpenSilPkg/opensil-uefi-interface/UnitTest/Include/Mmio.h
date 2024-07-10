/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  Mmio.h
 * @brief
 *
 */

#pragma once

#define MMIO_ADDRESS_MIN_MOCK_VAL        0xFEC00000ul
#define MMIO_ADDRESS_MAX_MOCK_VAL        0xFED82000ul
#define MMIO_MAX_SLOT_COUNT              0x4
#define MMIO_ADDRESS_SIZE                (MMIO_ADDRESS_MAX_MOCK_VAL-MMIO_ADDRESS_MIN_MOCK_VAL+1)

#ifdef __cplusplus
extern "C" {
#endif

uint8_t
xUSLMemRead8 (
  const volatile void *Addr
  );

uint16_t
xUSLMemRead16 (
  const volatile void *Addr
  );

uint32_t
xUSLMemRead32 (
  const volatile void *Addr
  );

uint64_t
xUSLMemRead64 (
  const volatile void *Addr
  );

void
xUSLMemWrite8 (
  volatile void *Addr,
  uint8_t Value
  );

void
xUSLMemWrite16 (
  volatile void *Addr,
  uint16_t Value
  );

void
xUSLMemWrite32 (
  volatile void *Addr,
  uint32_t Value
  );

void
xUSLMemWrite64 (
  volatile void *Addr,
  uint64_t Value
  );

void
xUSLMemReadModifyWrite8 (
  void *Addr,
  uint8_t AndMask,
  uint8_t OrMask
  );

void
xUSLMemReadModifyWrite16 (
  void *Addr,
  uint16_t AndMask,
  uint16_t OrMask
  );

void
xUSLMemReadModifyWrite32 (
  void *Addr,
  uint32_t AndMask,
  uint32_t OrMask
  );

void
MockxUSLMemRead8ManyTimes (
  uint8_t  ExpectedReadValue,
  uint32_t Count
  );

void
MockxUSLMemRead8Once (
  uint8_t ExpectedReadValue
  );

void
MockxUSLMemRead16ManyTimes (
  uint16_t ExpectedReadValue,
  uint32_t Count
  );

void
MockxUSLMemRead16Once (
  uint16_t ExpectedReadValue
  );

void
MockxUSLMemRead32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t Count
  );

void
MockxUSLMemRead32Once (
  uint32_t ExpectedReadValue
  );

void
MockxUSLMemRead64ManyTimes (
  uint64_t ExpectedReadValue,
  uint32_t Count
  );

void
MockxUSLMemRead64Once (
  uint64_t ExpectedReadValue
  );

void
MockxUSLMemWrite8ManyTimes (
  uint8_t  ExpectedWriteValue,
  uint32_t Count
  );

void
MockxUSLMemWrite8Once (
  uint8_t ExpectedWriteValue
  );

void
MockxUSLMemWrite16ManyTimes (
  uint16_t ExpectedWriteValue,
  uint32_t Count
  );

void
MockxUSLMemWrite16Once (
  uint16_t ExpectedWriteValue
  );

void
MockxUSLMemWrite32ManyTimes (
  uint32_t ExpectedWriteValue,
  uint32_t Count
  );

void
MockxUSLMemWrite32Once (
  uint32_t ExpectedWriteValue
  );

void
MockxUSLMemWrite64ManyTimes (
  uint64_t ExpectedWriteValue,
  uint32_t Count
  );

void
MockxUSLMemWrite64Once (
  uint64_t ExpectedWriteValue
  );

void
MockxUSLMemReadModifyWrite8ManyTimes (
  uint8_t ExpectedReadValue,
  uint8_t AndMask,
  uint8_t OrMask,
  uint32_t Count
  );

void
MockxUSLMemReadModifyWrite8Once (
  uint8_t ExpectedReadValue,
  uint8_t AndMask,
  uint8_t OrMask
  );

void
MockxUSLMemReadModifyWrite16ManyTimes (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask,
  uint32_t Count
  );

void
MockxUSLMemReadModifyWrite16Once (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask
  );

void
MockxUSLMemReadModifyWrite32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask,
  uint32_t Count
  );

void
MockxUSLMemReadModifyWrite32Once (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask
  );

#ifdef __cplusplus
}
#endif
