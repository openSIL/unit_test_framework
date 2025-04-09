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

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/Common/CcxEnableSmeeUt/CcxEnableSmeeUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/Common/CcxSetCacWeightsUt/CcxSetCacWeightsUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/Common/CcxGetCacWeightsUt/CcxGetCacWeightsUt.inf

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/Common/DfHasFchUt/DfHasFchUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/DF/Common/DfHasSmuUt/DfHasSmuUt.inf

  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/CCX/Zen4/GetZen4DesiredCcdCountUt/GetZen4DesiredCcdCountUt.inf
  
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/RcMgr/SilGetPrimaryRbUt/SilGetPrimaryRbUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/RcMgr/InitializeRcMgrApiUt/InitializeRcMgrApiUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/RcMgr/DfX/DfXRcMgrSetInputBlkUt/DfXRcMgrSetInputBlkUt.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/RcMgr/DfX/InitializeResourceManagerDfXTp3Ut/InitializeResourceManagerDfXTp3Ut.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/RcMgr/DfX/InitializeResourceManagerDfXTp2Ut/InitializeResourceManagerDfXTp2Ut.inf
  AmdOpenSilPkg/opensil-uefi-interface/UnitTest/Source/xUSL/RcMgr/DfX/InitializeResourceManagerDfXTp1Ut/InitializeResourceManagerDfXTp1Ut.inf