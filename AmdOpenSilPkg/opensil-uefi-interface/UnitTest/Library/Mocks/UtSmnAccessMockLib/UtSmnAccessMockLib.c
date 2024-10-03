/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtSmnAccessMockLib.c
 * @brief SMN Access Mock Library
 *
 */

#include <Uefi.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdbool.h>
#include <SilCommon.h>

#define MIN_MOCK_VAL        0x0000
#define MAX_MOCK_VAL        0xFFFFFFFF

uint32_t
xUSLSmnRead (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress
  )
{
  check_expected (SegmentNumber);
  check_expected (IohcBus);
  check_expected (SmnAddress);
  return (uint32_t) mock ();
}

/**
 * MockxUSLSmnReadManyTimes
 * @brief Mocks xUSLSmnRead function multiple times
 *
 * @param[in]  ExpectedReadValue     Expected read (i.e., return) value by the next xUSLSmnRead call
 * @param[in]  Count                 Number of times to mock xUSLSmnRead
*/
void
MockxUSLSmnReadManyTimes (
  uint32_t ExpectedReadValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLSmnRead, SegmentNumber, MIN_MOCK_VAL, MAX_MOCK_VAL, Count);
  expect_in_range_count (xUSLSmnRead, IohcBus, MIN_MOCK_VAL, MAX_MOCK_VAL, Count);
  expect_in_range_count (xUSLSmnRead, SmnAddress, MIN_MOCK_VAL, MAX_MOCK_VAL, Count);

  will_return_count (xUSLSmnRead, ExpectedReadValue, Count);
}

/**
 * MockxUSLSmnReadOnce
 * @brief Mocks xUSLSmnRead function once
 *
 * @param[in]  ExpectedReadValue     Expected read (i.e., return) value by the next xUSLSmnRead call
 *
*/
void
MockxUSLSmnReadOnce (
  uint32_t ExpectedReadValue
  )
{
  MockxUSLSmnReadManyTimes (ExpectedReadValue, 1);
}

void
xUSLSmnWrite (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress,
  uint32_t    Value
  )
{
  check_expected (SegmentNumber);
  check_expected (IohcBus);
  check_expected (SmnAddress);
  check_expected (Value);
}

/**
 * MockxUSLSmnWriteManyTimes
 * @brief Mocks xUSLSmnWrite function multiple times
 *
 * @param[in]  ExpectedWriteValue   Expected write value by the next xUSLSmnWrite call
 * @param[in]  Count                Number of times to mock xUSLSmnWrite
 *
 **/
void
MockxUSLSmnWriteManyTimes (
  uint32_t ExpectedWriteValue,
  uint32_t Count
  )
{
  expect_in_range_count (xUSLSmnWrite, SegmentNumber, MIN_MOCK_VAL, MAX_MOCK_VAL, Count);
  expect_in_range_count (xUSLSmnWrite, IohcBus, MIN_MOCK_VAL, MAX_MOCK_VAL, Count);
  expect_in_range_count (xUSLSmnWrite, SmnAddress, MIN_MOCK_VAL, MAX_MOCK_VAL, Count);

  expect_value_count (xUSLSmnWrite, Value, ExpectedWriteValue, Count);
}

/**
 * MockxUSLSmnWriteOnce
 * @brief Mocks the xUSLSmnWrite function once
 *
 * @param[in]  ExpectedWriteValue   Expected write value by the next xUSLSmnWrite call
 *
 **/
void
MockxUSLSmnWriteOnce (
  uint32_t ExpectedWriteValue
  )
{
  MockxUSLSmnWriteManyTimes (ExpectedWriteValue, 1);
}
