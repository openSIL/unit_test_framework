/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtMmioMockLib.c
 * @brief MMIO Access Pure Mock Library
 *
 */

#include <Uefi.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdbool.h>
#include <Mmio.h>

uint8_t
xUSLMemRead8 (
  const volatile void *Addr
  )
{
  check_expected_ptr (Addr);
  return (uint8_t) mock();
}

/**
 * MockxUSLMemRead8ManyTimes
 * @brief Mocks xUSLMemRead8 function multiple times
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead8 call
 * @param[in]  Count             Number of times to mock xUSLMemRead8
 *
 **/
void
MockxUSLMemRead8ManyTimes (
  uint8_t  ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemRead8, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  will_return_count (xUSLMemRead8, ExpectedReadValue, Count);
}

/**
 * MockxUSLMemRead8Once
 * @brief Mocks xUSLMemRead8 function once
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead8 call
 *
 **/
void
MockxUSLMemRead8Once (
  uint8_t ExpectedReadValue
  )
{
  MockxUSLMemRead8ManyTimes (ExpectedReadValue, 1);
}

uint16_t
xUSLMemRead16 (
  const volatile void *Addr
  )
{
  check_expected_ptr (Addr);
  return (uint16_t) mock();
}

/**
 * MockxUSLMemRead16ManyTimes
 * @brief Mocks xUSLMemRead16 function multiple times
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead16 call
 * @param[in]  Count             Number of times to mock xUSLMemRead16
 *
 **/
void
MockxUSLMemRead16ManyTimes (
  uint16_t ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemRead16, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  will_return_count (xUSLMemRead16, ExpectedReadValue, Count);
}

/**
 * MockxUSLMemRead16Once
 * @brief Mocks xUSLMemRead16 function once
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead16 call
 *
 **/
void
MockxUSLMemRead16Once (
  uint16_t ExpectedReadValue
  )
{
  MockxUSLMemRead16ManyTimes (ExpectedReadValue, 1);
}

uint32_t
xUSLMemRead32 (
  const volatile void *Addr
  )
{
  check_expected_ptr (Addr);
  return (uint32_t) mock();
}

/**
 * MockxUSLMemRead32ManyTimes
 * @brief Mocks xUSLMemRead32 function multiple times
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead32 call
 * @param[in]  Count             Number of times to mock xUSLMemRead32
 *
 **/
void
MockxUSLMemRead32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemRead32, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  will_return_count (xUSLMemRead32, ExpectedReadValue, Count);
}

/**
 * MockxUSLMemRead32Once
 * @brief Mocks xUSLMemRead32 function once
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead32 call
 *
 **/
void
MockxUSLMemRead32Once (
  uint32_t ExpectedReadValue
  )
{
  MockxUSLMemRead32ManyTimes (ExpectedReadValue, 1);
}

uint64_t
xUSLMemRead64 (
  const volatile void *Addr
  )
{
  check_expected_ptr (Addr);
  return (uint64_t) mock();
}

/**
 * MockxUSLMemRead64ManyTimes
 * @brief Mocks xUSLMemRead64 function multiple times
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead64 call
 * @param[in]  Count             Number of times to mock xUSLMemRead64
 *
 **/
void
MockxUSLMemRead64ManyTimes (
  uint64_t ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemRead64, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  will_return_count (xUSLMemRead64, ExpectedReadValue, Count);
}

/**
 * MockxUSLMemRead64Once
 * @brief Mocks xUSLMemRead64 function once
 *
 * @param[in]  ExpectedReadValue Expected read (i.e., return) value by the next xUSLMemRead64 call
 *
 **/
void
MockxUSLMemRead64Once (
  uint64_t ExpectedReadValue
  )
{
  MockxUSLMemRead64ManyTimes (ExpectedReadValue, 1);
}

void
xUSLMemWrite8 (
  volatile void *Addr,
  uint8_t Value
  )
{
  check_expected (Value);
  check_expected_ptr (Addr);
}

/**
 * MockxUSLMemWrite8ManyTimes
 * @brief Mocks xUSLMemWrite8 function multiple times
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite8 call
 * @param[in]  Count              Number of times to mock xUSLMemWrite8
 *
 **/
void
MockxUSLMemWrite8ManyTimes (
  uint8_t  ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemWrite8, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  expect_value_count (xUSLMemWrite8, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLMemWrite8Once
 * @brief Mocks xUSLMemWrite8 function once
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite8 call
 *
 **/
void
MockxUSLMemWrite8Once (
  uint8_t ExpectedWriteValue
  )
{
  MockxUSLMemWrite8ManyTimes (ExpectedWriteValue, 1);
}

void
xUSLMemWrite16 (
  volatile void *Addr,
  uint16_t Value
  )
{
  check_expected (Value);
  check_expected_ptr (Addr);
}

/**
 * MockxUSLMemWrite16ManyTimes
 * @brief Mocks xUSLMemWrite16 function multiple times
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite16 call
 * @param[in]  Count              Number of times to mock xUSLMemWrite16
 *
 **/
void
MockxUSLMemWrite16ManyTimes (
  uint16_t ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemWrite16, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  expect_value_count (xUSLMemWrite16, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLMemWrite16Once
 * @brief Mocks xUSLMemWrite16 function once
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite16 call
 *
 **/
void
MockxUSLMemWrite16Once (
  uint16_t ExpectedWriteValue
  )
{
  MockxUSLMemWrite16ManyTimes (ExpectedWriteValue, 1);
}

void
xUSLMemWrite32 (
  volatile void *Addr,
  uint32_t Value
  )
{
  check_expected (Value);
  check_expected_ptr (Addr);
}

/**
 * MockxUSLMemWrite32ManyTimes
 * @brief Mocks xUSLMemWrite32 function multiple times
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite32 call
 * @param[in]  Count              Number of times to mock xUSLMemWrite32
 *
 **/
void
MockxUSLMemWrite32ManyTimes (
  uint32_t ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemWrite32, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  expect_value_count (xUSLMemWrite32, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLMemWrite32Once
 * @brief Mocks xUSLMemWrite32 function once
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite32 call
 *
 **/
void
MockxUSLMemWrite32Once (
  uint32_t ExpectedWriteValue
  )
{
  MockxUSLMemWrite32ManyTimes (ExpectedWriteValue, 1);
}

void
xUSLMemWrite64 (
  volatile void *Addr,
  uint64_t Value
  )
{
  check_expected (Value);
  check_expected_ptr (Addr);
}

/**
 * MockxUSLMemWrite64ManyTimes
 * @brief Mocks xUSLMemWrite64 function multiple times
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite64 call
 * @param[in]  Count              Number of times to mock xUSLMemWrite64
 *
 **/
void
MockxUSLMemWrite64ManyTimes (
  uint64_t ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLMemWrite64, Addr, MMIO_ADDRESS_MIN_MOCK_VAL, MMIO_ADDRESS_MAX_MOCK_VAL, Count);
  expect_value_count (xUSLMemWrite64, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLMemWrite64Once
 * @brief Mocks xUSLMemWrite64 function once
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLMemWrite64 call
 *
 **/
void
MockxUSLMemWrite64Once (
  uint64_t ExpectedWriteValue
  )
{
  MockxUSLMemWrite64ManyTimes (ExpectedWriteValue, 1);
}

void
xUSLMemReadModifyWrite8 (
  void *Addr,
  uint8_t AndMask,
  uint8_t OrMask
  )
{
  uint8_t Value;
  Value = xUSLMemRead8 (Addr);
  xUSLMemWrite8 (Addr, (Value & AndMask) | OrMask);
}

void
MockxUSLMemReadModifyWrite8ManyTimes (
  uint8_t ExpectedReadValue,
  uint8_t AndMask,
  uint8_t OrMask,
  uint32_t Count
  )
{
  uint8_t ExpectedWriteValue;
  MockxUSLMemRead8ManyTimes (ExpectedReadValue, Count);
  ExpectedWriteValue = (ExpectedReadValue & AndMask) | OrMask;
  MockxUSLMemWrite8ManyTimes (ExpectedWriteValue, Count);
}

void
MockxUSLMemReadModifyWrite8Once (
  uint8_t ExpectedReadValue,
  uint8_t AndMask,
  uint8_t OrMask
  )
{
  MockxUSLMemReadModifyWrite8ManyTimes (ExpectedReadValue, AndMask, OrMask, 1);
}

void
xUSLMemReadModifyWrite16 (
  void *Addr,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  uint16_t Value;
  Value = xUSLMemRead16 (Addr);
  xUSLMemWrite16 (Addr, (Value & AndMask) | OrMask);
}

void
MockxUSLMemReadModifyWrite16ManyTimes (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask,
  uint32_t Count
  )
{
  uint16_t ExpectedWriteValue;
  MockxUSLMemRead16ManyTimes (ExpectedReadValue, Count);
  ExpectedWriteValue = (ExpectedReadValue & AndMask) | OrMask;
  MockxUSLMemWrite16ManyTimes (ExpectedWriteValue, Count);
}

void
MockxUSLMemReadModifyWrite16Once (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  MockxUSLMemReadModifyWrite16ManyTimes (ExpectedReadValue, AndMask, OrMask, 1);
}

void
xUSLMemReadModifyWrite32 (
  void *Addr,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  uint32_t Value;
  Value = xUSLMemRead32 (Addr);
  xUSLMemWrite32 (Addr, (Value & AndMask) | OrMask);
}

void
MockxUSLMemReadModifyWrite32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask,
  uint32_t Count
  )
{
  uint32_t ExpectedWriteValue;
  MockxUSLMemRead32ManyTimes (ExpectedReadValue, Count);
  ExpectedWriteValue = (ExpectedReadValue & AndMask) | OrMask;
  MockxUSLMemWrite32ManyTimes (ExpectedWriteValue, Count);
}

void
MockxUSLMemReadModifyWrite32Once (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  MockxUSLMemReadModifyWrite32ManyTimes (ExpectedReadValue, AndMask, OrMask, 1);
}
