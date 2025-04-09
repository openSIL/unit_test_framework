#include <stdlib.h>
#include <time.h>

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <xSIM.h>
#include <Io.h>
#include <Mmio.h>
#include <SmnAccess.h>

#include <SilCommon.h>
#include "Zen4.h"
#include <CCX/Zen4/Zen4Reg.h>
#include <CcxCmn2Rev.h>
#include <CcxIp2Ip.h>
#include <CommonLib/CpuLib.h>
#include <CcxClass-api.h>
#include <CCX/Common/Ccx.h>
#include "Zen4DownCoreInit.h"

#include <CcxApic.h>

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