/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  Io.h
 * @brief
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void
xUSLIoWrite8 (
  uint16_t Port,
  uint8_t Value
  );

void
xUSLIoWrite16 (
  uint16_t Port,
  uint16_t Value
  );

void
xUSLIoWrite32 (
  uint16_t Port,
  uint32_t Value
  );

uint8_t
xUSLIoRead8 (
  uint16_t Port
  );

uint16_t
xUSLIoRead16 (
  uint16_t Port
  );

uint32_t
xUSLIoRead32 (
  uint16_t Port
  );

void
xUSLIoReadModifyWrite8 (
  uint16_t Port,
  uint8_t  AndMask,
  uint8_t  OrMask
  );

void
xUSLIoReadModifyWrite16 (
  uint16_t Port,
  uint16_t AndMask,
  uint16_t OrMask
  );

void
xUSLIoReadModifyWrite32 (
  uint16_t Port,
  uint32_t AndMask,
  uint32_t OrMask
  );

void
MockxUSLIoWrite8ManyTimes (
  uint8_t  ExpectedWriteValue,
  uint32_t Count
  );

void
MockxUSLIoWrite8Once (
  uint8_t  ExpectedWriteValue
  );

void
MockxUSLIoWrite16ManyTimes (
  uint16_t ExpectedWriteValue,
  uint32_t Count
  );

void
MockxUSLIoWrite16Once (
  uint16_t ExpectedWriteValue
  );

void
MockxUSLIoWrite32ManyTimes (
  uint32_t ExpectedWriteValue,
  uint32_t Count
  );

void
MockxUSLIoWrite32Once (
  uint32_t ExpectedWriteValue
  );

void
MockxUSLIoRead8ManyTimes (
  uint8_t  ExpectedReadValue,
  uint32_t Count
  );

void
MockxUSLIoRead8Once (
  uint8_t  ExpectedReadValue
  );

void
MockxUSLIoRead16ManyTimes (
  uint16_t ExpectedReadValue,
  uint32_t Count
  );

void
MockxUSLIoRead16Once (
  uint16_t ExpectedReadValue
  );

void
MockxUSLIoRead32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t Count
  );

void
MockxUSLIoRead32Once (
  uint32_t ExpectedReadValue
  );

void
MockxUSLIoReadModifyWrite8ManyTimes (
  uint8_t  ExpectedReadValue,
  uint8_t  AndMask,
  uint8_t  OrMask,
  uint32_t Count
  );

void
MockxUSLIoReadModifyWrite8Once (
  uint8_t  ExpectedReadValue,
  uint8_t  AndMask,
  uint8_t  OrMask
  );

void
MockxUSLIoReadModifyWrite16ManyTimes (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask,
  uint32_t Count
  );

void
MockxUSLIoReadModifyWrite16Once (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask
  );

void
MockxUSLIoReadModifyWrite32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask,
  uint32_t Count
  );

void
MockxUSLIoReadModifyWrite32Once (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask
  );

#ifdef __cplusplus
}
#endif
