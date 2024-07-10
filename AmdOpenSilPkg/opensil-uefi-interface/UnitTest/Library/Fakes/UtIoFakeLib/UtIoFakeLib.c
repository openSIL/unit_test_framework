/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtIoFakeLib.c
 * @brief IO Access Fake Library
 *
 */

#include <Uefi.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdbool.h>
#include <Io.h>

static uint8_t IO[IO_ADDRESS_MAX_MOCK_VAL-IO_ADDRESS_MIN_MOCK_VAL+1] = {0};

void
xUSLIoWrite8 (
  uint16_t Port,
  uint8_t Value
  )
{
  IO[Port-IO_ADDRESS_MIN_MOCK_VAL] = Value;
}

void
xUSLIoWrite16 (
  uint16_t Port,
  uint16_t Value
  )
{
  *((uint16_t*)&IO[Port-IO_ADDRESS_MIN_MOCK_VAL]) = Value;
}

void
xUSLIoWrite32 (
  uint16_t Port,
  uint32_t Value
  )
{
  *((uint32_t*)&IO[Port-IO_ADDRESS_MIN_MOCK_VAL]) = Value;
}

uint8_t
xUSLIoRead8 (
  uint16_t Port
  )
{
  return IO[Port-IO_ADDRESS_MIN_MOCK_VAL];
}

uint16_t
xUSLIoRead16 (
  uint16_t Port
  )
{
  return *((uint16_t*)&IO[Port-IO_ADDRESS_MIN_MOCK_VAL]);
}

uint32_t
xUSLIoRead32 (
  uint16_t Port
  )
{
  return *((uint32_t*)&IO[Port-IO_ADDRESS_MIN_MOCK_VAL]);
}

void
xUSLIoReadModifyWrite8 (
  uint16_t Port,
  uint8_t  AndMask,
  uint8_t  OrMask
  )
{
  xUSLIoWrite8 (Port, (xUSLIoRead8 (Port) & AndMask) | OrMask );
}

void
xUSLIoReadModifyWrite16 (
  uint16_t Port,
  uint16_t AndMask,
  uint16_t OrMask
  )
{
  xUSLIoWrite16 (Port, (xUSLIoRead16 (Port) & AndMask) | OrMask );
}

void
xUSLIoReadModifyWrite32 (
  uint16_t Port,
  uint32_t AndMask,
  uint32_t OrMask
  )
{
  xUSLIoWrite32 (Port, (xUSLIoRead32 (Port) & AndMask) | OrMask );
}
