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

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Ccx/Common/CcxEnableSmeeUt/CcxEnableSmeeUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Ccx/Common/CcxSetCacWeightsUt/CcxSetCacWeightsUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Ccx/Common/CcxGetCacWeightsUt/CcxGetCacWeightsUt.inf

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Df/Common/DfGetProcessorInfoUt/DfGetProcessorInfoUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Df/Common/DfGetDieInfoUt/DfGetDieInfoUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Df/Common/DfGetSystemInfoUt/DfGetSystemInfoUt.inf

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/FindPcieCoreDescUt/FindPcieCoreDescUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/FindLastPciePortOnPrevPcieCUt/FindLastPciePortOnPrevPcieCUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/FindLastPciePortOfThisPcieCUt/FindLastPciePortOfThisPcieCUt.inf

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/PcieConfigAttachDescriptorsUt/PcieConfigAttachDescriptorsUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/FindPrevPcieCoreUt/FindPrevPcieCoreUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/IsSteppingAxUt/IsSteppingAxUt.inf

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/PcieEnumerateAndHarvestWrUt/PcieEnumerateAndHarvestWrUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/NBIO/IOD/InitNbioConfigDataUt/InitNbioConfigDataUt.inf
