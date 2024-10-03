/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtIoMockLib.c
 * @brief IO Access Pure Mock Library
 *
 */

#include <Uefi.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdbool.h>
#include <Io.h>

void
xUSLIoWrite8 (
  uint16_t Port,
  uint8_t Value
  )
{
  check_expected (Port);
  check_expected (Value);
}

/**
 * MockxUSLIoWrite8ManyTimes
 * @brief Mocks xUSLIoWrite8 function multiple times
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLIoWrite8 call
 * @param[in]  Count              Number of times to mock xUSLIoWrite8
 *
 **/
void
MockxUSLIoWrite8ManyTimes (
  uint8_t  ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLIoWrite8, Port, IO_ADDRESS_MIN_MOCK_VAL, IO_ADDRESS_MAX_MOCK_VAL, Count);
  expect_value_count (xUSLIoWrite8, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLIoWrite8Once
 * @brief Mocks xUSLIoWrite8 function once
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLIoWrite8 call
 *
 **/
void
MockxUSLIoWrite8Once (
  uint8_t  ExpectedWriteValue
  )
{
  MockxUSLIoWrite8ManyTimes (ExpectedWriteValue, 1);
}

void
xUSLIoWrite16 (
  uint16_t Port,
  uint16_t Value
  )
{
  check_expected (Port);
  check_expected (Value);
}

/**
 * MockxUSLIoWrite16ManyTimes
 * @brief Mocks xUSLIoWrite16 function multiple times
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLIoWrite16 call
 * @param[in]  Count              Number of times to mock xUSLIoWrite16
 *
 **/
void
MockxUSLIoWrite16ManyTimes (
  uint16_t ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLIoWrite16, Port, IO_ADDRESS_MIN_MOCK_VAL, IO_ADDRESS_MAX_MOCK_VAL, Count);
  expect_value_count (xUSLIoWrite16, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLIoWrite16Once
 * @brief Mocks xUSLIoWrite16 function once
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLIoWrite16 call
 *
 **/
void
MockxUSLIoWrite16Once (
  uint16_t ExpectedWriteValue
  )
{
  MockxUSLIoWrite16ManyTimes (ExpectedWriteValue, 1);
}

void
xUSLIoWrite32 (
  uint16_t Port,
  uint32_t Value
  )
{
  check_expected (Port);
  check_expected (Value);
}

/**
 * MockxUSLIoWrite32ManyTimes
 * @brief Mocks xUSLIoWrite32 function multiple times
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLIoWrite32 call
 * @param[in]  Count              Number of times to mock xUSLIoWrite32
 *
 **/
void
MockxUSLIoWrite32ManyTimes (
  uint32_t ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLIoWrite32, Port, IO_ADDRESS_MIN_MOCK_VAL, IO_ADDRESS_MAX_MOCK_VAL, Count);
  expect_value_count (xUSLIoWrite32, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLIoWrite32Once
 * @brief Mocks xUSLIoWrite32 function once
 *
 * @param[in]  ExpectedWriteValue Expected write value by the next xUSLIoWrite32 call
 *
 **/
void
MockxUSLIoWrite32Once (
  uint32_t ExpectedWriteValue
  )
{
  MockxUSLIoWrite32ManyTimes (ExpectedWriteValue, 1);
}

uint8_t
xUSLIoRead8 (
  uint16_t Port
  )
{
  check_expected (Port);
  return (uint8_t) mock();
}

/**
 * MockxUSLIoRead8ManyTimes
 * @brief Mocks xUSLIoRead8 function multiple times
 *
 * @param[in]  ExpectedReadalue Expected read (i.e., return) value by the next xUSLIoRead8 call
 * @param[in]  Count            Number of times to mock xUSLIoRead8
 *
 **/
void
MockxUSLIoRead8ManyTimes (
  uint8_t  ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLIoRead8, Port, IO_ADDRESS_MIN_MOCK_VAL, IO_ADDRESS_MAX_MOCK_VAL, Count);
  will_return_count (xUSLIoRead8, ExpectedReadValue, Count);
}

/**
 * MockxUSLIoRead8Once
 * @brief Mocks xUSLIoRead8 function once
 *
 * @param[in]  ExpectedReadalue Expected read (i.e., return) value by the next xUSLIoRead8 call
 *
 **/
void
MockxUSLIoRead8Once (
  uint8_t  ExpectedReadValue
  )
{
  MockxUSLIoRead8ManyTimes (ExpectedReadValue, 1);
}

uint16_t
xUSLIoRead16 (
  uint16_t Port
  )
{
  check_expected (Port);
  return (uint16_t) mock();
}

/**
 * MockxUSLIoRead16ManyTimes
 * @brief Mocks xUSLIoRead16 function multiple times
 *
 * @param[in]  ExpectedReadalue Expected read (i.e., return) value by the next xUSLIoRead16 call
 * @param[in]  Count            Number of times to mock xUSLIoRead16
 *
 **/
void
MockxUSLIoRead16ManyTimes (
  uint16_t ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLIoRead16, Port, IO_ADDRESS_MIN_MOCK_VAL, IO_ADDRESS_MAX_MOCK_VAL, Count);
  will_return_count (xUSLIoRead16, ExpectedReadValue, Count);
}

/**
 * MockxUSLIoRead16Once
 * @brief Mocks xUSLIoRead16 function once
 *
 * @param[in]  ExpectedReadalue Expected read (i.e., return) value by the next xUSLIoRead16 call
 *
 **/
void
MockxUSLIoRead16Once (
  uint16_t ExpectedReadValue
  )
{
  MockxUSLIoRead16ManyTimes (ExpectedReadValue, 1);
}

uint32_t
xUSLIoRead32 (
  uint16_t Port
  )
{
  check_expected (Port);
  return (uint32_t) mock();
}

/**
 * MockxUSLIoRead32ManyTimes
 * @brief Mocks xUSLIoRead32 function multiple times
 *
 * @param[in]  ExpectedReadalue Expected read (i.e., return) value by the next xUSLIoRead32 call
 * @param[in]  Count            Number of times to mock xUSLIoRead32
 *
 **/
void
MockxUSLIoRead32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLIoRead32, Port, IO_ADDRESS_MIN_MOCK_VAL, IO_ADDRESS_MAX_MOCK_VAL, Count);
  will_return_count (xUSLIoRead32, ExpectedReadValue, Count);
}

/**
 * MockxUSLIoRead32Once
 * @brief Mocks xUSLIoRead32 function once
 *
 * @param[in]  ExpectedReadalue Expected read (i.e., return) value by the next xUSLIoRead32 call
 *
 **/
void
MockxUSLIoRead32Once (
  uint32_t ExpectedReadValue
  )
{
  MockxUSLIoRead32ManyTimes (ExpectedReadValue, 1);
}

void
xUSLIoReadModifyWrite8 (
  uint16_t Port,
  uint8_t  AndMask,
  uint8_t  OrMask
  )
{
  uint8_t Value;
  Value = xUSLIoRead8 (Port);
  xUSLIoWrite8 (Port, (Value & AndMask) | OrMask );
}

void
MockxUSLIoReadModifyWrite8ManyTimes (
  uint8_t  ExpectedReadValue,
  uint8_t  AndMask,
  uint8_t  OrMask,
  uint32_t Count
  )
{
  uint8_t ExpectedWriteValue;
  MockxUSLIoRead8ManyTimes (ExpectedReadValue, Count);
  ExpectedWriteValue = (ExpectedReadValue & AndMask) | OrMask;
  MockxUSLIoWrite8ManyTimes (ExpectedWriteValue, Count);
}

void
MockxUSLIoReadModifyWrite8Once (
  uint8_t  ExpectedReadValue,
  uint8_t  AndMask,
  uint8_t  OrMask
  )
{
  MockxUSLIoReadModifyWrite8ManyTimes (ExpectedReadValue, AndMask, OrMask, 1);
}

void
xUSLIoReadModifyWrite16 (
  uint16_t Port,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  uint16_t Value;
  Value = xUSLIoRead16 (Port);
  xUSLIoWrite16 (Port, (Value & AndMask) | OrMask );
}

void
MockxUSLIoReadModifyWrite16ManyTimes (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask,
  uint32_t Count
  )
{
  uint16_t ExpectedWriteValue;
  MockxUSLIoRead16ManyTimes (ExpectedReadValue, Count);
  ExpectedWriteValue = (ExpectedReadValue & AndMask) | OrMask;
  MockxUSLIoWrite16ManyTimes (ExpectedWriteValue, Count);
}

void
MockxUSLIoReadModifyWrite16Once (
  uint16_t ExpectedReadValue,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  MockxUSLIoReadModifyWrite16ManyTimes (ExpectedReadValue, AndMask, OrMask, 1);
}

void
xUSLIoReadModifyWrite32 (
  uint16_t Port,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  uint32_t Value;
  Value = xUSLIoRead32 (Port);
  xUSLIoWrite32 (Port, (Value & AndMask) | OrMask );
}

void
MockxUSLIoReadModifyWrite32ManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask,
  uint32_t Count
  )
{
  uint32_t ExpectedWriteValue;
  MockxUSLIoRead32ManyTimes (ExpectedReadValue, Count);
  ExpectedWriteValue = (ExpectedReadValue & AndMask) | OrMask;
  MockxUSLIoWrite32ManyTimes (ExpectedWriteValue, Count);
}

void
MockxUSLIoReadModifyWrite32Once (
  uint32_t ExpectedReadValue,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  MockxUSLIoReadModifyWrite32ManyTimes (ExpectedReadValue, AndMask, OrMask, 1);
}
