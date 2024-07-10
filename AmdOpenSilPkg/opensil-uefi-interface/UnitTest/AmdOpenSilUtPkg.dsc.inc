## @file
# AMD OpenSIL Host Unit Test Package DSC Include File
#
# Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved.
# SPDX-License-Identifier: MIT
#
##

[Defines]
  OPENSIL_UTPATH = AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Library

[LibraryClasses.common.HOST_APPLICATION]
  UtIoFakeLib|$(OPENSIL_UTPATH)/Fakes/UtIoFakeLib/UtIoFakeLib.inf
  UtSilInitLib|$(OPENSIL_UTPATH)/Fakes/UtSilInitLib/UtSilInitLib.inf
  UtMmioFakeLib|$(OPENSIL_UTPATH)/Fakes/UtMmioFakeLib/UtMmioFakeLib.inf

[BuildOptions]
  GCC:*_*_*_CC_FLAGS     = -D UNIT_TEST_RUN
  INTEL:*_*_*_CC_FLAGS   = /D UNIT_TEST_RUN
  MSFT:*_*_*_CC_FLAGS    = /D UNIT_TEST_RUN
