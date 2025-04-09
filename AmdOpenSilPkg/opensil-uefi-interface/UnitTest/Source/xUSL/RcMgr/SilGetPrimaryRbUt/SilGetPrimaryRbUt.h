#ifndef __SILGETPRIMARYRBUT_H__
#define __SILGETPRIMARYRBUT_H__

#include <stdlib.h>
#include <time.h>

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <xSIM.h>
#include <Io.h>
#include <Mmio.h>

#include <SmnAccess.h>
#include <Include/Library/UtSilServicesMockLib.h>
#include <Include/Library/UtxSIMMockLib.h>

#include "RcMgrIp2Ip.h"
#include <DF/DfIp2Ip.h>
#include <RcMgr/FabricResourceManager.h>

HOST_DEBUG_SERVICE mHostDebugService = NULL;

// Stub prototype for DfGetSystemComponentRootBridgeLocation; true case.
bool
DfGetSystemComponentRootBridgeLocationTrue (
  COMPONENT_TYPE Component,
  ROOT_BRIDGE_LOCATION *Location
  );

// Stub prototype for DfGetSystemComponentRootBridgeLocation; false case.
bool
DfGetSystemComponentRootBridgeLocationFalse (
  COMPONENT_TYPE Component,
  ROOT_BRIDGE_LOCATION *Location
  );

// Stub prototype for FabricReserveMmio.
// SIL_STATUS
// FabricReserveMmio (
//   uint64_t              *BaseAddress,
//   uint64_t              *Length,
//   uint64_t              Alignment,
//   FABRIC_TARGET         Target,
//   FABRIC_MMIO_ATTRIBUTE *Attributes
//   );

/*
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
*/

#endif