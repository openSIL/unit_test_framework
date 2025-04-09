#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <UtBaseLib.h>
#include <UtLogLib.h>
#include <UtSilInitLib.h>

#include <xSIM.h>
#include <CCX/Common/Ccx.h>
#include <Include/MsrReg.h>

#define UNDER_SIZE 15

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