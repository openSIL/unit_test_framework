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
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/CcxEnableSmee/CcxEnableSmeeUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/CcxInitializeCpb/CcxInitializeCpbUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/CcxSetCacWeights/CcxSetCacWeightsUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/CcxSyncMiscMsrs/CcxSyncMiscMsrsUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/CcxSetMiscMsrs/CcxSetMiscMsrsUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/TypeEntryInMap/TypeEntryInMapUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/RootBridgeInfo/RootBridgeInfoUt.inf  
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/NumberOfProcessors/NumberOfProcessorsUt.inf  
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/NumberOfSystemDies/NumberOfSystemDiesUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/NumberOfSystemRB/NumberOfSystemRBUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/NumberOfRBOnS/NumberOfRBOnSUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/NumberOfRBOnD/NumberOfRBOnDUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/GetDieSystemOffset/GetDieSystemOffsetUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/GetDeviceMapOnDie/GetDeviceMapOnDieUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/GetHostBridgeBB/GetHostBridgeBBUt.inf