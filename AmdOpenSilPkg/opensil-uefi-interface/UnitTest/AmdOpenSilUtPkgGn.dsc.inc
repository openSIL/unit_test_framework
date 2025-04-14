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
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/Common/DfGetHostBridgeSystemFabricIDUt/DfGetHostBridgeSystemFabricIDUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/Common/DfGetSystemComponentUt/DfGetSystemComponentUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/GetPortAncDataTypeSizeUt/GetPortAncDataTypeSizeUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/MpioAncDataCalcSizeUt/MpioAncDataCalcSizeUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/AddPhyOvrdDataUt/AddPhyOvrdDataUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/AddSpdOvrdDataUt/AddSpdOvrdDataUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/AddAncListDataUt/AddAncListDataUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/MpioAddAncDataOverrideUt/MpioAddAncDataOverrideUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/PcieAriInitUt/PcieAriInitUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/Usb4LaneNumberCfgCallbackUt/Usb4LaneNumberCfgCallbackUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/MpioCfgBeforeDxioInitUt/MpioCfgBeforeDxioInitUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/Mpio/Common/MpioCfgAfterDxioInitUt/MpioCfgAfterDxioInitUt.inf