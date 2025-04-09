#include <stdlib.h>
#include <time.h>

#include <UtBaseLib.h>
#include <UtSilInitLib.h>
#include <UtLogLib.h>

#include <stdbool.h>
#include <setjmp.h>
#include <cmocka.h>

// #include <xSIM.h>
// #include <Io.h>
// #include <Mmio.h>
// #include <SmnAccess.h>

#include <SilCommon.h>
#include "Zen4DownCoreInit.h"
#include <CcxDownCoreInit.h>
// #include <SocServices.h>
#include <CcxClass-api.h>
#include "Ccx.h"

HOST_DEBUG_SERVICE mHostDebugService = NULL;

/**
 * Mock SocIsOneCcdModeSupported
 *
 * @brief Mock implementation of SocIsOneCcdModeSupported.
 *
 * @return true if 1 CCD mode is supported, false otherwise.
 */
bool 
SocIsOneCcdModeSupported (
  void
  );

/**
 * MockSocIsOneCcdModeSupportedOnce
 *
 * @brief Sets the expected return value for a single call to SocIsOneCcdModeSupported.
 *
 * @param ExpectedReturnValue The expected return value (true or false).
 */
void 
MockSocIsOneCcdModeSupportedOnce (
  bool ExpectedReturnValue
  );

/**
 * MockSocIsOneCcdModeSupportedManyTimes
 *
 * @brief Sets the expected return value for multiple calls to SocIsOneCcdModeSupported.
 *
 * @param ExpectedReturnValue The expected return value (true or false).
 * @param CallCount Number of times the mock should return the value.
 */
void 
MockSocIsOneCcdModeSupportedManyTimes (
  bool ExpectedReturnValue, 
  uint32_t CallCount
  );