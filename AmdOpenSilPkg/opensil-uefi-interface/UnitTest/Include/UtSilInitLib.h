/* Copyright (C) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file  UtSilInitLib.h
 * @brief
 */

#pragma once

#include <Sil-api.h>

#ifdef __cplusplus
extern "C" {
#endif

SIL_STATUS
UtSilInit (
  void
  );

SIL_STATUS
UtSilDeinit (
  void
  );

#ifdef __cplusplus
}
#endif
