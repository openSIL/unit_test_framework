#ifndef __CCXGETCACWEIGHTSUT_H__
#define __CCXGETCACWEIGHTSUT_H__

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <UtBaseLib.h>
#include <UtBaseLibTypes.h>
#include <UtLogLib.h>
#include <UtSilInitLib.h>

#include <xSIM.h>
#include <CCX/Common/Ccx.h>
#include <Include/MsrReg.h>
#include <Include/Library/UtSilServicesMockLib.h>

// implements a mock for SmuReadCacWeights
SIL_STATUS
SmuReadCacWeightsUt (
  uint32_t MaxNumWeights,
  uint64_t *ApmWeights
);

uint64_t
xUslRdMsr (
  uint32_t MsrAddress
  )
{
  return 0;
}

void
xUslWrMsr (
  uint32_t MsrAddress,
  uint64_t MsrValue
  )
{
  return;
}

void
xUslMsrAnd (
  uint32_t Index,
  uint64_t AndData
  )
{
  return;
}

void xUslMsrOr (
  uint32_t Index,
  uint64_t OrData
  )
{
  return;
}

void
xUslMsrAndThenOr (
  uint32_t Index,
  uint64_t AndData,
  uint64_t OrData
  )
{
  return;
}

bool xUslIsComputeUnitPrimary (
  void
  )
{
  return TRUE;
}

/*
typedef struct {
  SMU_IP2IP_API_HEADER          Header;
  SMU_SERVICE_INIT_ARGS         SmuServiceInitArguments;
  SMU_SERVICE_REQUEST           SmuServiceRequest;
  SMU_FIRMWARE_TEST             SmuFirmwareTest;
  DXIO_SERVICE_REQUEST          DxioServiceRequest;
  SMU_NOFITY_S3_ENTRY           SmuNotifyS3Entry;
  SMU_GET_GNB_HANDLE            SmuGetGnbHandle;
  SMU_READ_BRAND_STRING         SmuReadBrandString;
  SMU_LAUNCH_THREAD             SmuLaunchThread;
  SMU_READ_BIST_INFO            SmuReadBistInfo;
  SMU_READ_CAC_WEIGHTS          SmuReadCacWeights;
  SMU_REGISTER_READ             SmuRegisterRead;
  SMU_REGISTER_WRITE            SmuRegisterWrite;
  SMU_REGISTER_RMW              SmuRegisterRMW;
  SMU_DISABLE_SMT               SmuDisableSmt;
  SMU_GET_OPN_CORE_PRESENCE     SmuGetOpnCorePresence;
  SMU_GET_OPN_CORE_PRESENCE_EX  SmuGetOpnCorePresenceEx;
} SMU_IP2IP_API;

typedef enum {
  SilId_SocCommon = 0,
  SilId_DfClass,
  SilId_CcxClass,
  SilId_FchClass,
  SilId_MultiFchClass,
  SilId_FchHwAcpiP,
  SilId_FchAb,
  SilId_FchSpi,
  SilId_FchHwAcpi,
  SilId_FchSata,
  SilId_FchEspi,
  SilId_FchUsb,
  SilId_MemClass,
  SilId_MultiFch,
  SilId_NorthBridgePcie,
  SilId_NbioClass,
  SilId_XmpClass,
  SilId_RcManager,
  SilId_SmuClass,
  SilId_MpioClass,
  SilId_SdciClass,
  SilId_CxlClass,
  SilId_RasClass,
                            // Add new elements above this line ^^^
  SilId_ListEnd             ///< Value to bound the list
} SIL_DATA_BLOCK_ID;
*/

#endif