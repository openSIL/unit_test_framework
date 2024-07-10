## @file
# AMD OpenSIL Host Unit Test Package DSC File
#
# Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
# SPDX-License-Identifier: MIT
#
##

[Defines]
  PLATFORM_NAME           = AmdOpenSilUtPkg
  PLATFORM_GUID           = 9539874f-09ba-433e-900d-d2c9d37af45e
  PLATFORM_VERSION        = 0.1
  DSC_SPECIFICATION       = 0x00010005
  OUTPUT_DIRECTORY        = Build/AmdOpenSilPkg/opensil-uefi-interface/HostTest
  SUPPORTED_ARCHITECTURES = IA32|X64
  BUILD_TARGETS           = NOOPT
  SKUID_IDENTIFIER        = DEFAULT

!include UnitTestFrameworkPkg/UnitTestFrameworkPkgHost.dsc.inc

# This is platform-dependent
!include AmdOpenSilPkg/opensil-uefi-interface/UnitTest/AmdOpenSilUtPkgGn.dsc.inc

[LibraryClasses.common.HOST_APPLICATION]
  UtBaseLib|Platform/AmdCommonPkg/Test/UnitTest/Library/UtBaseLib/UtBaseLib.inf
  UtJsonLib|Platform/AmdCommonPkg/Test/UnitTest/Library/UtJsonLib/UtJsonLib.inf
