/* Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved. */
// SPDX-License-Identifier: MIT
/**
 * @file UtSilServicesMockLib.c
 * @brief Stubs for openSIL services provided by xUSL
 *
 */

#include <stdint.h>
#include <SilCommon.h>
#include <Sil-api.h>
#include <xSIM-api.h>
#include <setjmp.h>
#include <cmocka.h>

/**
 * xUslFindStructure
 *
 * @brief This function returns the data block for the specified module (IpId)
 *
 * @param IpId          The SIL_DATA_BLOCK_ID value for the IP block to return.
 * @param InstanceNum   The instance of the IP block data. (0 based)
 *
 * @return void*      The pointer to the IP block data
 *
 */
void *
xUslFindStructure (
  SIL_DATA_BLOCK_ID   IpId,
  uint16_t            InstanceNum
  )
{
    return mock_ptr_type(void *);
}

/**
 * xUslFindStructureOnce
 *
 * @brief Arm expected return value for a single call to xUslFindStructure
 *
 * @param SilDataCommonPtr  The expected return value from xUslFindStructure.
 *
 *                       - In a passing case, this parameter should be a pointer to the SilDataCommonPtr.
 *                       - In a failing case, this parameter should be NULL.
 */
void
MockxUslFindStructureOnce (
  void  *SilDataCommonPtr
  )
{
  will_return (xUslFindStructure, SilDataCommonPtr);
}


/**
 * SilInitIp2IpApi
 *
 * @brief   Register an Ip-2-Ip API for IpId to the API table.
 *
 * @param   IpId         The ID of the IP providing the API.
 * @param   Api          Input of the Ip-2-Ip API table to initialize.
 *
 * @retval  SilPass             The Ip-2-Ip API was initialized for IpId.
 * @retval  SilInvalidParameter The Ip ID was outside the bounds of valid IDs defined by SIL_DATA_BLOCK_ID.
 *
 */
SIL_STATUS
SilInitIp2IpApi (
  SIL_DATA_BLOCK_ID   IpId,
  void                *IpApi
  )
{
  /*
   * The API table is a member of the SIL_BLOCK_VARIABLES struct.
   */
  check_expected (IpId);
  IpApi = mock_ptr_type( void *);

  return (SIL_STATUS) mock ();
}

/**
 * MockSilInitIp2IpApiOnce
 *
 * @brief Arm expected return value for a single call to SilInitIp2IpApi
 *
 * @param ExpectedIpApi  The expected return value from SilInitIp2IpApi.
 *
 *                       - In a passing case, this parameter should be a pointer to the Ip2Ip API table to initialize.
 *                       - In a failing case, this parameter should be NULL.
 *
 * @param ExpectedSilStatus  The expected return Status from SilInitIp2IpApi.
 *
 *                        - In a passing case, this parameter should SilPass.
 *                        - In a failing case, this parameter should an error Status.
 */
void
MockSilInitIp2IpApiOnce (
  void            *ExpectedIpApi,
  SIL_STATUS      ExpectedSilStatus
  )
{
  // Verify IpId is within the range defined by SIL_DATA_BLOCK_ID
  expect_in_range (SilInitIp2IpApi, IpId, (uint32_t)SilId_SocCommon, ((uint32_t)SilId_ListEnd - 1));
  will_return (SilInitIp2IpApi, ExpectedIpApi);
  will_return (SilInitIp2IpApi, ExpectedSilStatus);
}

/**
 * SilGetIp2IpApi
 *
 * @details This function is used by openSIL IPs to find and return a pointer to the Ip-2-Ip API installed for the
 *          specified IP ID.
 *
 * @param   IpId         The ID of the IP block to request the Ip-2-Ip API for.  The list of
 *                       valid Ids is defined in xSIM-api.h.
 * @param   Api          Upon success, this output is a pointer to the Ip-2-Ip API.
 *
 * @returns SIL_STATUS
 * @retval  SilPass     The Api was found and returned in the Api pointer
 * @retval  SilNotFound No API was installed for IP
 *
 */
SIL_STATUS
SilGetIp2IpApi (
  SIL_DATA_BLOCK_ID   IpId,
  void                **Api
  )
{
  void *ApiTemp;

  /*
   * The API table is a member of the SIL_BLOCK_VARIABLES struct.
   */
  check_expected (IpId);
  ApiTemp = mock_ptr_type( void *);
  *Api = ApiTemp;

  return (SIL_STATUS) mock ();
}

/**
 * MockSilGetIp2IpApiOnce
 *
 * @brief Arm expected return value for a single call to SilGetIp2IpApi
 *
 * @param ExpectedIpApi  The expected return value from SilGetIp2IpApi.
 *
 *                       - In a passing case, this parameter should be a pointer to the Ip2Ip API table to initialize.
 *                       - In a failing case, this parameter should be NULL.
 *
 * @param ExpectedSilStatus  The expected return Status from SilGetIp2IpApi.
 *
 *                        - In a passing case, this parameter should SilPass.
 *                        - In a failing case, this parameter should an error Status.
 */
void
MockSilGetIp2IpManyTimes (
  void            *ExpectedIpApi,
  SIL_STATUS      ExpectedSilStatus,
  uint32_t        Count
  )
{
  // Verify IpId is within the range defined by SIL_DATA_BLOCK_ID
  expect_in_range_count (SilGetIp2IpApi, IpId, (uint32_t)SilId_SocCommon, ((uint32_t)SilId_ListEnd - 1), Count);
  will_return_count (SilGetIp2IpApi, ExpectedIpApi, Count);
  will_return_count (SilGetIp2IpApi, ExpectedSilStatus, Count);
}

/**
 * MockSilGetIp2IpApiOnce
 *
 * @brief Arm expected return value for a single call to SilGetIp2IpApi
 *
 * @param ExpectedIpApi  The expected return value from SilGetIp2IpApi.
 *
 *                       - In a passing case, this parameter should be a pointer to the Ip2Ip API table to initialize.
 *                       - In a failing case, this parameter should be NULL.
 *
 * @param ExpectedSilStatus  The expected return Status from SilGetIp2IpApi.
 *
 *                        - In a passing case, this parameter should SilPass.
 *                        - In a failing case, this parameter should an error Status.
 */
void
MockSilGetIp2IpApiOnce (
  void            *ExpectedIpApi,
  SIL_STATUS      ExpectedSilStatus
  )
{
  MockSilGetIp2IpManyTimes (ExpectedIpApi, ExpectedSilStatus, 1);
}

/**
 * SilInitCommon2RevXferTable
 *
 * @brief   Register an IP Common to revision specific transfer table.
 *
 * @details The common to revision specific transfer table is an interface from common code to abstracted program
 *          specific code.
 *
 * @param   IpId        The ID of the IP providing the table.
 * @param   XferTable   Input of the transfer table to initialize.
 *
 * @retval  SilPass             The Xfer table was initialized for IpId.
 * @retval  SilInvalidParameter The Ip ID was outside the bounds of valid IDs defined by SIL_DATA_BLOCK_ID.
 *
 */
SIL_STATUS
SilInitCommon2RevXferTable (
  SIL_DATA_BLOCK_ID   IpId,
  void                *XferTable
  )
{
  /*
   * The API table is a member of the SIL_BLOCK_VARIABLES struct.
   */
  check_expected (IpId);
  XferTable= mock_ptr_type( void *);

  return (SIL_STATUS) mock ();
}

/**
 * MockSilInitCommon2RevXferTableOnce
 *
 * @brief Arm expected return value for a single call to SilInitCommon2RevXferTable
 *
 * @param ExpectedXferTable  The expected return value from SilInitCommon2RevXferTable.
 *
 *                        - In a passing case, this parameter should be a pointer to a buffer for the transfer table.
 *                        - In a failing case, this parameter should be NULL.
 *
 * @param ExpectedSilStatus  The expected return Status from SilInitCommon2RevXferTable.
 *
 *                        - In a passing case, this parameter should SilPass.
 *                        - In a failing case, this parameter should an error Status.
 */
void
MockSilInitCommon2RevXferTableOnce (
  void            *ExpectedXferTable,
  SIL_STATUS      ExpectedSilStatus
  )
{
  // Verify IpId is within the range defined by SIL_DATA_BLOCK_ID
  expect_in_range (SilInitCommon2RevXferTable, IpId, (uint32_t)SilId_SocCommon, ((uint32_t)SilId_ListEnd - 1));
  will_return (SilInitCommon2RevXferTable, ExpectedXferTable);
  will_return (SilInitCommon2RevXferTable, ExpectedSilStatus);
}

/**
 * SilGetCommon2RevXferTable
 *
 * @brief   Retrieves an IP Common to revision specific transfer table.
 *
 * @details The common to revision specific transfer table is an interface from common code to abstracted program
 *          specific code.
 *
 * @param   IpId        The ID of the IP providing the table.
 * @param   XferTable   Output pointer to return the transfer table.
 *
 * @retval  SilPass     The transfer table was returned for IpId.
 * @retval  SilNotFound No transfer table was installed for the specified IP.
 *
 */
SIL_STATUS
SilGetCommon2RevXferTable (
  SIL_DATA_BLOCK_ID   IpId,
  void                **XferTable
  )
{
  void *XferTableTemp;

  /*
   * The API table is a member of the SIL_BLOCK_VARIABLES struct.
   */
  check_expected (IpId);
  XferTableTemp= mock_ptr_type( void *);
  *XferTable = XferTableTemp;

  return (SIL_STATUS) mock ();
}

/**
 * MockSilGetCommon2RevXferTableOnce
 *
 * @brief Arm expected return value for a single call to SilGetCommon2RevXferTable
 *
 * @param ExpectedXferTable  The expected return value from SilGetCommon2RevXferTable.
 *
 *                        - In a passing case, this parameter should be a pointer to a buffer for the transfer table.
 *                        - In a failing case, this parameter should be NULL.
 *
 * @param ExpectedSilStatus  The expected return Status from SilGetCommon2RevXferTable.
 *
 *                        - In a passing case, this parameter should SilPass.
 *                        - In a failing case, this parameter should an error Status.
 */
void
MockSilGetCommon2RevXferTableOnce (
  void            *ExpectedXferTable,
  SIL_STATUS      ExpectedSilStatus
  )
{
  // Verify IpId is within the range defined by SIL_DATA_BLOCK_ID
  expect_in_range (SilGetCommon2RevXferTable, IpId, (uint32_t)SilId_SocCommon, ((uint32_t)SilId_ListEnd - 1));
  will_return (SilGetCommon2RevXferTable, ExpectedXferTable);
  will_return (SilGetCommon2RevXferTable, ExpectedSilStatus);
}

/**
 * MockSilGetCommon2RevXferTableManyTimes
 *
 * @brief Arm expected return value for a single call to SilGetCommon2RevXferTable
 *
 * @param ExpectedXferTable  The expected return value from SilGetCommon2RevXferTable.
 *
 *                        - In a passing case, this parameter should be a pointer to a buffer for the transfer table.
 *                        - In a failing case, this parameter should be NULL.
 *
 * @param ExpectedSilStatus  The expected return Status from SilGetCommon2RevXferTable.
 *
 *                        - In a passing case, this parameter should SilPass.
 *                        - In a failing case, this parameter should an error Status.
 */
void
MockSilGetCommon2RevXferTableManyTimes (
  void            *ExpectedXferTable,
  SIL_STATUS      ExpectedSilStatus,
  uint32_t        Count 
  )
{
  for(uint32_t i = 0; i < Count; i++)
  {
    // Verify IpId is within the range defined by SIL_DATA_BLOCK_ID
    expect_in_range (SilGetCommon2RevXferTable, IpId, (uint32_t)SilId_SocCommon, ((uint32_t)SilId_ListEnd - 1));
    will_return (SilGetCommon2RevXferTable, ExpectedXferTable);
    will_return (SilGetCommon2RevXferTable, ExpectedSilStatus);
  }
}