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
