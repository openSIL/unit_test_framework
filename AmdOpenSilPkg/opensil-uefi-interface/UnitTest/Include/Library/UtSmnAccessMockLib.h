/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtSmnAccessMockLib.h
 * @brief
 *
 */
#pragma once

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <stdint.h>
#include <stdbool.h>
#include <setjmp.h>
#include <cmocka.h>
#include <SilCommon.h>

uint32_t
xUSLSmnRead (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress
  );

void
MockxUSLSmnReadManyTimes (
  uint32_t    ExpectedReadValue,
  uint32_t    Count
  );

void
MockxUSLSmnReadOnce (
  uint32_t    ExpectedReadValue
  );

void
xUSLSmnWrite (
  uint32_t    SegmentNumber,
  uint32_t    IohcBus,
  uint32_t    SmnAddress,
  uint32_t    Value
  );

void
MockxUSLSmnWriteManyTimes (
  uint32_t    ExpectedWriteValue,
  uint32_t    Count
  );

void
MockxUSLSmnWriteOnce (
  uint32_t    ExpectedWriteValue
  );
