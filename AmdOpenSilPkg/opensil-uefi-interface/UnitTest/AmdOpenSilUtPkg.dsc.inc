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
  UtIoMockLib|$(OPENSIL_UTPATH)/Mocks/UtIoMockLib/UtIoMockLib.inf
  UtIoStubLib|$(OPENSIL_UTPATH)/Stubs/UtIoStubLib/UtIoStubLib.inf
  UtPciFakeLib|$(OPENSIL_UTPATH)/Fakes/UtPciFakeLib/UtPciFakeLib.inf
  UtPciStubLib|$(OPENSIL_UTPATH)/Stubs/UtPciStubLib/UtPciStubLib.inf
  UtSilInitLib|$(OPENSIL_UTPATH)/Fakes/UtSilInitLib/UtSilInitLib.inf
  UtMmioFakeLib|$(OPENSIL_UTPATH)/Fakes/UtMmioFakeLib/UtMmioFakeLib.inf
  UtMmioMockLib|$(OPENSIL_UTPATH)/Mocks/UtMmioMockLib/UtMmioMockLib.inf
  UtMmioStubLib|$(OPENSIL_UTPATH)/Stubs/UtMmioStubLib/UtMmioStubLib.inf
  UtxSIMFakeLib|$(OPENSIL_UTPATH)/Fakes/UtxSIMFakeLib/UtxSIMFakeLib.inf
  UtxSIMMockLib|$(OPENSIL_UTPATH)/Mocks/UtxSIMMockLib/UtxSIMMockLib.inf
  UtSilServicesMockLib|$(OPENSIL_UTPATH)/Mocks/UtSilServicesMockLib/UtSilServicesMockLib.inf
  UtSmnAccessStubLib|$(OPENSIL_UTPATH)/Stubs/UtSmnAccessStubLib/UtSmnAccessStubLib.inf
  UtCpuOpsMockLib|$(OPENSIL_UTPATH)/Mocks/UtCpuOpsMockLib/UtCpuOpsMockLib.inf

[BuildOptions]
  GCC:*_*_*_CC_FLAGS     = -D UNIT_TEST_RUN
  INTEL:*_*_*_CC_FLAGS   = /D UNIT_TEST_RUN
  MSFT:*_*_*_CC_FLAGS    = /D UNIT_TEST_RUN
