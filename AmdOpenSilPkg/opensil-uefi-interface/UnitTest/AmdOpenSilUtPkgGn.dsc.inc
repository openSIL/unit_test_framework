## @file
# AMD OpenSIL PHX Host Unit Test Package DSC Include File
#
# Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved.
# SPDX-License-Identifier: MIT
#
##

!include AmdOpenSilPkg/opensil-uefi-interface/UnitTest/AmdOpenSilUtPkg.dsc.inc

[Defines]
  #

[LibraryClasses.common.HOST_APPLICATION]


[Components.common.HOST_APPLICATION]

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/Xmp/SilHelloWorldUt/SilHelloWorldUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Fch/FchAb/FchInitResetAbUt/FchInitResetAbUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Fch/FchAb/FchAbSetInputBlkUt/FchAbSetInputBlkUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Fch/FchAb/FchInitEnvAbUt/FchInitEnvAbUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/Common/UpdatApMtrrSettingsUt/UpdatApMtrrSettingsUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/Common/CcxEnableSmeeUt/CcxEnableSmeeUt.inf