
/*******************************************************************************
*   Ledger Nano S - Secure firmware
*   (c) 2022 Ledger
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#if !defined(ERRORS_H)
#define ERRORS_H

#include <stdint.h>

/**
 * The OS error codes are encoded on two bytes (0xabcd), with the following
 * structure:
 * 'a': The error code category,
 * 'b': The error code subcategory,
 * 'cd': The error code identifier (depends on the two previous fields).
 * The 'B000' - 'EFFF' range is reserved for applications, if they want to
 * have the same uniqueness mechanism in their error codes.
 */

/**
 * OS-reserved error codes ranges.
 * Applications should avoid using them for their own implementations,
 * except for the SWO_SUCCESS value.
 */
#define ERR_IOL_RANGE                     0x1000
#define ERR_TSK_RANGE                     0x2000
#define ERR_CRY_RANGE                     0x3000
#define ERR_PAR_RANGE                     0x4000
#define ERR_SEC_RANGE                     0x5000
#define ERR_APD_RANGE                     0x6000
#define ERR_MUI_RANGE                     0xA000

/**
 * Applications-reserved error codes ranges.
 * The Operating System do not use any error code within these ranges.
 */
#define ERR_APP_RANGE_01                  0xB000
#define ERR_APP_RANGE_02                  0xC000
#define ERR_APP_RANGE_03                  0xD000
#define ERR_APP_RANGE_04                  0xE000

// Generic subcategories.
#define ERR_GEN_SUB_01                    0x0100
#define ERR_GEN_SUB_02                    0x0200
#define ERR_GEN_SUB_03                    0x0300
#define ERR_GEN_SUB_04                    0x0400
#define ERR_GEN_SUB_05                    0x0500
#define ERR_GEN_SUB_06                    0x0600
#define ERR_GEN_SUB_07                    0x0700
#define ERR_GEN_SUB_08                    0x0800
#define ERR_GEN_SUB_09                    0x0900
#define ERR_GEN_SUB_0D                    0x0D00
#define ERR_GEN_SUB_0E                    0x0E00

// Generic identifiers.
enum generic_identifiers {
  ERR_GEN_ID_01 = 0x01,
  ERR_GEN_ID_02,
  ERR_GEN_ID_03,
  ERR_GEN_ID_04,
  ERR_GEN_ID_05,
  ERR_GEN_ID_06,
  ERR_GEN_ID_07,
  ERR_GEN_ID_08,
  ERR_GEN_ID_09,
  ERR_GEN_ID_0A,
  ERR_GEN_ID_0B,
  ERR_GEN_ID_0C,
  ERR_GEN_ID_0D,
  ERR_GEN_ID_0E,
  ERR_GEN_ID_0F,
  ERR_GEN_ID_10,
  ERR_GEN_ID_11,
  ERR_GEN_ID_12,
  ERR_GEN_ID_13,
  ERR_GEN_ID_14,
  ERR_GEN_ID_15,
  ERR_GEN_ID_16,
  ERR_GEN_ID_17,
  ERR_GEN_ID_18,
  ERR_GEN_ID_19,
  ERR_GEN_ID_1A,
  ERR_GEN_ID_1B,
  ERR_GEN_ID_1C,
  ERR_GEN_ID_1D,
  ERR_GEN_ID_1E,
  ERR_GEN_ID_1F,
  ERR_GEN_ID_20,
  ERR_GEN_ID_21,
  ERR_GEN_ID_22,
  ERR_GEN_ID_23,
  ERR_GEN_ID_24,
  ERR_GEN_ID_25,
  ERR_GEN_ID_26,
  ERR_GEN_ID_27,
  ERR_GEN_ID_28,
  ERR_GEN_ID_29,
  ERR_GEN_ID_2A,
  ERR_GEN_ID_2B,
  ERR_GEN_ID_2C,
  ERR_GEN_ID_2D,
  ERR_GEN_ID_2E,
  ERR_GEN_ID_2F,
  ERR_GEN_ID_30,
  ERR_GEN_ID_31,
  ERR_GEN_ID_32,
  ERR_GEN_ID_33,
  ERR_GEN_ID_34,
  ERR_GEN_ID_35,
  ERR_GEN_ID_36,
  ERR_GEN_ID_37,
  ERR_GEN_ID_38,
  ERR_GEN_ID_39,
  ERR_GEN_ID_3A,
  ERR_GEN_ID_3B,
  ERR_GEN_ID_3C,
  ERR_GEN_ID_3D
};

/**
 * I/O-related issues are categorized into:
 * Overflow issues (OFW),
 * Header issues (HDR),
 * State issues (STA),
 * Reset issues (RST),
 * BLE issues (BLE).
 */
#define ERR_IOL_OFW                       (ERR_IOL_RANGE + ERR_GEN_SUB_01)
#define ERR_IOL_HDR                       (ERR_IOL_RANGE + ERR_GEN_SUB_02)
#define ERR_IOL_STA                       (ERR_IOL_RANGE + ERR_GEN_SUB_03)
#define ERR_IOL_RST                       (ERR_IOL_RANGE + ERR_GEN_SUB_04)

#if defined(HAVE_BLE)
# define ERR_IOL_BLE                      (ERR_IOL_RANGE + ERR_GEN_SUB_05)
#endif // HAVE_BLE

#define SWO_IOL_OFW_01                    (ERR_IOL_OFW + ERR_GEN_ID_01)    // 0x1101
#define SWO_IOL_OFW_02                    (ERR_IOL_OFW + ERR_GEN_ID_02)    // 0x1102
#define SWO_IOL_OFW_03                    (ERR_IOL_OFW + ERR_GEN_ID_03)    // 0x1103
#define SWO_IOL_OFW_04                    (ERR_IOL_OFW + ERR_GEN_ID_04)    // 0x1104
#define SWO_IOL_OFW_05                    (ERR_IOL_OFW + ERR_GEN_ID_05)    // 0x1105

#define SWO_IOL_HDR_01                    (ERR_IOL_HDR + ERR_GEN_ID_01)    // 0x1201
#define SWO_IOL_HDR_02                    (ERR_IOL_HDR + ERR_GEN_ID_02)    // 0x1202
#define SWO_IOL_HDR_03                    (ERR_IOL_HDR + ERR_GEN_ID_03)    // 0x1203
#define SWO_IOL_HDR_04                    (ERR_IOL_HDR + ERR_GEN_ID_04)    // 0x1204
#define SWO_IOL_HDR_05                    (ERR_IOL_HDR + ERR_GEN_ID_05)    // 0x1205
#define SWO_IOL_HDR_06                    (ERR_IOL_HDR + ERR_GEN_ID_06)    // 0x1206
#define SWO_IOL_HDR_07                    (ERR_IOL_HDR + ERR_GEN_ID_07)    // 0x1207
#define SWO_IOL_HDR_08                    (ERR_IOL_HDR + ERR_GEN_ID_08)    // 0x1208

#define SWO_IOL_STA_01                    (ERR_IOL_STA + ERR_GEN_ID_01)    // 0x1301
#define SWO_IOL_STA_02                    (ERR_IOL_STA + ERR_GEN_ID_02)    // 0x1302
#define SWO_IOL_STA_03                    (ERR_IOL_STA + ERR_GEN_ID_03)    // 0x1303
#define SWO_IOL_STA_04                    (ERR_IOL_STA + ERR_GEN_ID_04)    // 0x1304

#define SWO_IOL_RST_01                    (ERR_IOL_RST + ERR_GEN_ID_01)    // 0x1401
#define SWO_IOL_RST_02                    (ERR_IOL_RST + ERR_GEN_ID_02)    // 0x1402
#define SWO_IOL_RST_03                    (ERR_IOL_RST + ERR_GEN_ID_03)    // 0x1403
#define SWO_IOL_RST_05                    (ERR_IOL_RST + ERR_GEN_ID_05)    // 0x1405 - Do not move this value.

#if defined(HAVE_BLE)
# define SWO_IOL_BLE_01                   (ERR_IOL_BLE + ERR_GEN_ID_01)    // 0x1501
# define SWO_IOL_BLE_02                   (ERR_IOL_BLE + ERR_GEN_ID_02)    // 0x1502
# define SWO_IOL_BLE_03                   (ERR_IOL_BLE + ERR_GEN_ID_03)    // 0x1503
# define SWO_IOL_BLE_04                   (ERR_IOL_BLE + ERR_GEN_ID_04)    // 0x1504
# define SWO_IOL_BLE_05                   (ERR_IOL_BLE + ERR_GEN_ID_05)    // 0x1505
# define SWO_IOL_BLE_06                   (ERR_IOL_BLE + ERR_GEN_ID_06)    // 0x1506
# define SWO_IOL_BLE_07                   (ERR_IOL_BLE + ERR_GEN_ID_07)    // 0x1507
# define SWO_IOL_BLE_08                   (ERR_IOL_BLE + ERR_GEN_ID_08)    // 0x1508
# define SWO_IOL_BLE_09                   (ERR_IOL_BLE + ERR_GEN_ID_09)    // 0x1509
# define SWO_IOL_BLE_0A                   (ERR_IOL_BLE + ERR_GEN_ID_0A)    // 0x150A
# define SWO_IOL_BLE_0B                   (ERR_IOL_BLE + ERR_GEN_ID_0B)    // 0x150B
# define SWO_IOL_BLE_0C                   (ERR_IOL_BLE + ERR_GEN_ID_0C)    // 0x150C
#endif // HAVE_BLE

/**
 * Tasks-related issues are categorized into:
 * Stack issues (STC),
 * Task Owner issues (OWN),
 * Overflow issues (OFW).
 */
#define ERR_TSK_STC                       (ERR_TSK_RANGE + ERR_GEN_SUB_01)
#define ERR_TSK_OWN                       (ERR_TSK_RANGE + ERR_GEN_SUB_02)
#define ERR_TSK_OFW                       (ERR_TSK_RANGE + ERR_GEN_SUB_03)

#define SWO_TSK_STC_01                    (ERR_TSK_STC + ERR_GEN_ID_01)    // 0x2101
#define SWO_TSK_STC_02                    (ERR_TSK_STC + ERR_GEN_ID_02)    // 0x2102
#define SWO_TSK_STC_03                    (ERR_TSK_STC + ERR_GEN_ID_03)    // 0x2103
#define SWO_TSK_STC_04                    (ERR_TSK_STC + ERR_GEN_ID_04)    // 0x2104
#define SWO_TSK_STC_05                    (ERR_TSK_STC + ERR_GEN_ID_05)    // 0x2105
#define SWO_TSK_STC_06                    (ERR_TSK_STC + ERR_GEN_ID_06)    // 0x2106
#define SWO_TSK_STC_07                    (ERR_TSK_STC + ERR_GEN_ID_07)    // 0x2107
#define SWO_TSK_STC_08                    (ERR_TSK_STC + ERR_GEN_ID_08)    // 0x2108

#define SWO_TSK_OWN_01                    (ERR_TSK_OWN + ERR_GEN_ID_01)    // 0x2201
#define SWO_TSK_OWN_02                    (ERR_TSK_OWN + ERR_GEN_ID_02)    // 0x2202
#define SWO_TSK_OWN_03                    (ERR_TSK_OWN + ERR_GEN_ID_03)    // 0x2203
#define SWO_TSK_OWN_04                    (ERR_TSK_OWN + ERR_GEN_ID_04)    // 0x2204

#define SWO_TSK_OFW_01                    (ERR_TSK_OFW + ERR_GEN_ID_01)    // 0x2301
#define SWO_TSK_OFW_02                    (ERR_TSK_OFW + ERR_GEN_ID_02)    // 0x2302

/**
 * Cryptography parameter-related issues are categorized into:
 * Lengths mismatch in functions (LEN),
 * Values mismatch in functions (VAL).
 */
#define ERR_CRY_LEN                       (ERR_CRY_RANGE + ERR_GEN_SUB_01)
#define ERR_CRY_VAL                       (ERR_CRY_RANGE + ERR_GEN_SUB_02)

// Not used yet.
#define SWO_CRY_LEN_01                    (ERR_CRY_LEN + ERR_GEN_ID_01)    // 0x3101
#define SWO_CRY_VAL_01                    (ERR_CRY_VAL + ERR_GEN_ID_01)    // 0x3201

/**
 * OS (except cryptography) parameter-related issues are categorized into:
 * Lengths mismatch in functions (LEN),
 * Values mismatch in functions (VAL).
 */
#define ERR_PAR_LEN                       (ERR_PAR_RANGE + ERR_GEN_SUB_01)
#define ERR_PAR_VAL                       (ERR_PAR_RANGE + ERR_GEN_SUB_02)

#define SWO_PAR_LEN_01                    (ERR_PAR_LEN + ERR_GEN_ID_01)    // 0x4101
#define SWO_PAR_LEN_02                    (ERR_PAR_LEN + ERR_GEN_ID_02)    // 0x4102
#define SWO_PAR_LEN_03                    (ERR_PAR_LEN + ERR_GEN_ID_03)    // 0x4103
#define SWO_PAR_LEN_04                    (ERR_PAR_LEN + ERR_GEN_ID_04)    // 0x4104
#define SWO_PAR_LEN_05                    (ERR_PAR_LEN + ERR_GEN_ID_05)    // 0x4105
#define SWO_PAR_LEN_06                    (ERR_PAR_LEN + ERR_GEN_ID_06)    // 0x4106
#define SWO_PAR_LEN_07                    (ERR_PAR_LEN + ERR_GEN_ID_07)    // 0x4107
#define SWO_PAR_LEN_08                    (ERR_PAR_LEN + ERR_GEN_ID_08)    // 0x4108
#define SWO_PAR_LEN_09                    (ERR_PAR_LEN + ERR_GEN_ID_09)    // 0x4109
#define SWO_PAR_LEN_0A                    (ERR_PAR_LEN + ERR_GEN_ID_0A)    // 0x410A
#define SWO_PAR_LEN_0B                    (ERR_PAR_LEN + ERR_GEN_ID_0B)    // 0x410B
#define SWO_PAR_LEN_0C                    (ERR_PAR_LEN + ERR_GEN_ID_0C)    // 0x410C
#define SWO_PAR_LEN_0D                    (ERR_PAR_LEN + ERR_GEN_ID_0D)    // 0x410D
#define SWO_PAR_LEN_0E                    (ERR_PAR_LEN + ERR_GEN_ID_0E)    // 0x410E
#define SWO_PAR_LEN_0F                    (ERR_PAR_LEN + ERR_GEN_ID_0F)    // 0x410F
#define SWO_PAR_LEN_10                    (ERR_PAR_LEN + ERR_GEN_ID_10)    // 0x4110
#define SWO_PAR_LEN_11                    (ERR_PAR_LEN + ERR_GEN_ID_11)    // 0x4111
#define SWO_PAR_LEN_12                    (ERR_PAR_LEN + ERR_GEN_ID_12)    // 0x4112
#define SWO_PAR_LEN_13                    (ERR_PAR_LEN + ERR_GEN_ID_13)    // 0x4113
#define SWO_PAR_LEN_14                    (ERR_PAR_LEN + ERR_GEN_ID_14)    // 0x4114
#define SWO_PAR_LEN_15                    (ERR_PAR_LEN + ERR_GEN_ID_15)    // 0x4115
#define SWO_PAR_LEN_16                    (ERR_PAR_LEN + ERR_GEN_ID_16)    // 0x4116

#define SWO_PAR_VAL_01                    (ERR_PAR_VAL + ERR_GEN_ID_01)    // 0x4201
#define SWO_PAR_VAL_02                    (ERR_PAR_VAL + ERR_GEN_ID_02)    // 0x4202
#define SWO_PAR_VAL_03                    (ERR_PAR_VAL + ERR_GEN_ID_03)    // 0x4203
#define SWO_PAR_VAL_04                    (ERR_PAR_VAL + ERR_GEN_ID_04)    // 0x4204
#define SWO_PAR_VAL_05                    (ERR_PAR_VAL + ERR_GEN_ID_05)    // 0x4205
#define SWO_PAR_VAL_06                    (ERR_PAR_VAL + ERR_GEN_ID_06)    // 0x4206
#define SWO_PAR_VAL_07                    (ERR_PAR_VAL + ERR_GEN_ID_07)    // 0x4207
#define SWO_PAR_VAL_08                    (ERR_PAR_VAL + ERR_GEN_ID_08)    // 0x4208
#define SWO_PAR_VAL_09                    (ERR_PAR_VAL + ERR_GEN_ID_09)    // 0x4209
#define SWO_PAR_VAL_0A                    (ERR_PAR_VAL + ERR_GEN_ID_0A)    // 0x420A
#define SWO_PAR_VAL_0B                    (ERR_PAR_VAL + ERR_GEN_ID_0B)    // 0x420B
#define SWO_PAR_VAL_0C                    (ERR_PAR_VAL + ERR_GEN_ID_0C)    // 0x420C
#define SWO_PAR_VAL_0D                    (ERR_PAR_VAL + ERR_GEN_ID_0D)    // 0x420D
#define SWO_PAR_VAL_0E                    (ERR_PAR_VAL + ERR_GEN_ID_0E)    // 0x420E
#define SWO_PAR_VAL_0F                    (ERR_PAR_VAL + ERR_GEN_ID_0F)    // 0x420F
#define SWO_PAR_VAL_10                    (ERR_PAR_VAL + ERR_GEN_ID_10)    // 0x4210
#define SWO_PAR_VAL_11                    (ERR_PAR_VAL + ERR_GEN_ID_11)    // 0x4211
#define SWO_PAR_VAL_12                    (ERR_PAR_VAL + ERR_GEN_ID_12)    // 0x4212
#define SWO_PAR_VAL_13                    (ERR_PAR_VAL + ERR_GEN_ID_13)    // 0x4213
#define SWO_PAR_VAL_14                    (ERR_PAR_VAL + ERR_GEN_ID_14)    // 0x4214
#define SWO_PAR_VAL_15                    (ERR_PAR_VAL + ERR_GEN_ID_15)    // 0x4215
#define SWO_PAR_VAL_16                    (ERR_PAR_VAL + ERR_GEN_ID_16)    // 0x4216
#define SWO_PAR_VAL_17                    (ERR_PAR_VAL + ERR_GEN_ID_17)    // 0x4217
#define SWO_PAR_VAL_18                    (ERR_PAR_VAL + ERR_GEN_ID_18)    // 0x4218
#define SWO_PAR_VAL_19                    (ERR_PAR_VAL + ERR_GEN_ID_19)    // 0x4219
#define SWO_PAR_VAL_1A                    (ERR_PAR_VAL + ERR_GEN_ID_1A)    // 0x421A
#define SWO_PAR_VAL_1B                    (ERR_PAR_VAL + ERR_GEN_ID_1B)    // 0x421B
#define SWO_PAR_VAL_1C                    (ERR_PAR_VAL + ERR_GEN_ID_1C)    // 0x421C
#define SWO_PAR_VAL_1D                    (ERR_PAR_VAL + ERR_GEN_ID_1D)    // 0x421D
#define SWO_PAR_VAL_1E                    (ERR_PAR_VAL + ERR_GEN_ID_1E)    // 0x421E
#define SWO_PAR_VAL_1F                    (ERR_PAR_VAL + ERR_GEN_ID_1F)    // 0x421F
#define SWO_PAR_VAL_20                    (ERR_PAR_VAL + ERR_GEN_ID_20)    // 0x4220
#define SWO_PAR_VAL_21                    (ERR_PAR_VAL + ERR_GEN_ID_21)    // 0x4221
#define SWO_PAR_VAL_22                    (ERR_PAR_VAL + ERR_GEN_ID_22)    // 0x4222
#define SWO_PAR_VAL_23                    (ERR_PAR_VAL + ERR_GEN_ID_23)    // 0x4223
#define SWO_PAR_VAL_24                    (ERR_PAR_VAL + ERR_GEN_ID_24)    // 0x4224
#define SWO_PAR_VAL_25                    (ERR_PAR_VAL + ERR_GEN_ID_25)    // 0x4225
#define SWO_PAR_VAL_26                    (ERR_PAR_VAL + ERR_GEN_ID_26)    // 0x4226
#define SWO_PAR_VAL_27                    (ERR_PAR_VAL + ERR_GEN_ID_27)    // 0x4227
#define SWO_PAR_VAL_28                    (ERR_PAR_VAL + ERR_GEN_ID_28)    // 0x4228
#define SWO_PAR_VAL_29                    (ERR_PAR_VAL + ERR_GEN_ID_29)    // 0x4229
#define SWO_PAR_VAL_2A                    (ERR_PAR_VAL + ERR_GEN_ID_2A)    // 0x422A

/**
 * Security-related issues are categorized into:
 * Application registry-related issues (APP),
 * CRC checks issues (CRC),
 * Miscellaneous security checks (CHK),
 * Key-related operations (KEY),
 * User consent-related operations (PIN),
 * SCP-related operations (SCP),
 * Signature-related operations (SIG),
 * Memory Management operation (MEM),
 * Device state issues (STA).
 */
#define ERR_SEC_APP                       (ERR_SEC_RANGE + ERR_GEN_SUB_01)
#define ERR_SEC_CRC                       (ERR_SEC_RANGE + ERR_GEN_SUB_02)
#define ERR_SEC_CHK                       (ERR_SEC_RANGE + ERR_GEN_SUB_03)
#define ERR_SEC_KEY                       (ERR_SEC_RANGE + ERR_GEN_SUB_04)
#define ERR_SEC_PIN                       (ERR_SEC_RANGE + ERR_GEN_SUB_05)
#define ERR_SEC_SCP                       (ERR_SEC_RANGE + ERR_GEN_SUB_06)
#define ERR_SEC_SIG                       (ERR_SEC_RANGE + ERR_GEN_SUB_07)
#define ERR_SEC_MEM                       (ERR_SEC_RANGE + ERR_GEN_SUB_08)
#define ERR_SEC_STA                       (ERR_SEC_RANGE + ERR_GEN_SUB_09)

#define SWO_SEC_APP_01                    (ERR_SEC_APP + ERR_GEN_ID_01)    // 0x5101
#define SWO_SEC_APP_02                    (ERR_SEC_APP + ERR_GEN_ID_02)    // 0x5102
#define SWO_SEC_APP_03                    (ERR_SEC_APP + ERR_GEN_ID_03)    // 0x5103
#define SWO_SEC_APP_04                    (ERR_SEC_APP + ERR_GEN_ID_04)    // 0x5104
#define SWO_SEC_APP_05                    (ERR_SEC_APP + ERR_GEN_ID_05)    // 0x5105
#define SWO_SEC_APP_06                    (ERR_SEC_APP + ERR_GEN_ID_06)    // 0x5106
#define SWO_SEC_APP_07                    (ERR_SEC_APP + ERR_GEN_ID_07)    // 0x5107
#define SWO_SEC_APP_08                    (ERR_SEC_APP + ERR_GEN_ID_08)    // 0x5108
#define SWO_SEC_APP_09                    (ERR_SEC_APP + ERR_GEN_ID_09)    // 0x5109
#define SWO_SEC_APP_0A                    (ERR_SEC_APP + ERR_GEN_ID_0A)    // 0x510A
#define SWO_SEC_APP_0B                    (ERR_SEC_APP + ERR_GEN_ID_0B)    // 0x510B
#define SWO_SEC_APP_0C                    (ERR_SEC_APP + ERR_GEN_ID_0C)    // 0x510C
#define SWO_SEC_APP_0D                    (ERR_SEC_APP + ERR_GEN_ID_0D)    // 0x510D
#define SWO_SEC_APP_0E                    (ERR_SEC_APP + ERR_GEN_ID_0E)    // 0x510E
#define SWO_SEC_APP_0F                    (ERR_SEC_APP + ERR_GEN_ID_0F)    // 0x510F
#define SWO_SEC_APP_10                    (ERR_SEC_APP + ERR_GEN_ID_10)    // 0x5110
#define SWO_SEC_APP_11                    (ERR_SEC_APP + ERR_GEN_ID_11)    // 0x5111
#define SWO_SEC_APP_12                    (ERR_SEC_APP + ERR_GEN_ID_12)    // 0x5112
#define SWO_SEC_APP_13                    (ERR_SEC_APP + ERR_GEN_ID_13)    // 0x5113
#define SWO_SEC_APP_14                    (ERR_SEC_APP + ERR_GEN_ID_14)    // 0x5114
#define SWO_SEC_APP_15                    (ERR_SEC_APP + ERR_GEN_ID_15)    // 0x5115
#define SWO_SEC_APP_16                    (ERR_SEC_APP + ERR_GEN_ID_16)    // 0x5116
#define SWO_SEC_APP_17                    (ERR_SEC_APP + ERR_GEN_ID_17)    // 0x5117
#define SWO_SEC_APP_18                    (ERR_SEC_APP + ERR_GEN_ID_18)    // 0x5118
#define SWO_SEC_APP_19                    (ERR_SEC_APP + ERR_GEN_ID_19)    // 0x5119
#define SWO_SEC_APP_1A                    (ERR_SEC_APP + ERR_GEN_ID_1A)    // 0x511A
#define SWO_SEC_APP_1B                    (ERR_SEC_APP + ERR_GEN_ID_1B)    // 0x511B
#define SWO_SEC_APP_1C                    (ERR_SEC_APP + ERR_GEN_ID_1C)    // 0x511C
#define SWO_SEC_APP_1D                    (ERR_SEC_APP + ERR_GEN_ID_1D)    // 0x511D
#define SWO_SEC_APP_1E                    (ERR_SEC_APP + ERR_GEN_ID_1E)    // 0x511E
#define SWO_SEC_APP_1F                    (ERR_SEC_APP + ERR_GEN_ID_1F)    // 0x511F
#define SWO_SEC_APP_20                    (ERR_SEC_APP + ERR_GEN_ID_20)    // 0x5120
#define SWO_SEC_APP_21                    (ERR_SEC_APP + ERR_GEN_ID_21)    // 0x5121

#define SWO_SEC_CRC_01                    (ERR_SEC_CRC + ERR_GEN_ID_01)    // 0x5201
#define SWO_SEC_CRC_02                    (ERR_SEC_CRC + ERR_GEN_ID_02)    // 0x5202
#define SWO_SEC_CRC_03                    (ERR_SEC_CRC + ERR_GEN_ID_03)    // 0x5203
#define SWO_SEC_CRC_04                    (ERR_SEC_CRC + ERR_GEN_ID_04)    // 0x5204
#define SWO_SEC_CRC_05                    (ERR_SEC_CRC + ERR_GEN_ID_05)    // 0x5205
#define SWO_SEC_CRC_06                    (ERR_SEC_CRC + ERR_GEN_ID_06)    // 0x5206
#define SWO_SEC_CRC_07                    (ERR_SEC_CRC + ERR_GEN_ID_07)    // 0x5207
#define SWO_SEC_CRC_08                    (ERR_SEC_CRC + ERR_GEN_ID_08)    // 0x5208
#define SWO_SEC_CRC_09                    (ERR_SEC_CRC + ERR_GEN_ID_09)    // 0x5209
#define SWO_SEC_CRC_0A                    (ERR_SEC_CRC + ERR_GEN_ID_0A)    // 0x520A
#define SWO_SEC_CRC_0B                    (ERR_SEC_CRC + ERR_GEN_ID_0B)    // 0x520B
#define SWO_SEC_CRC_0C                    (ERR_SEC_CRC + ERR_GEN_ID_0C)    // 0x520C
#define SWO_SEC_CRC_0D                    (ERR_SEC_CRC + ERR_GEN_ID_0D)    // 0x520D
#define SWO_SEC_CRC_0E                    (ERR_SEC_CRC + ERR_GEN_ID_0E)    // 0x520E
#define SWO_SEC_CRC_0F                    (ERR_SEC_CRC + ERR_GEN_ID_0F)    // 0x520F
#define SWO_SEC_CRC_10                    (ERR_SEC_CRC + ERR_GEN_ID_10)    // 0x5210
#define SWO_SEC_CRC_11                    (ERR_SEC_CRC + ERR_GEN_ID_11)    // 0x5211
#define SWO_SEC_CRC_12                    (ERR_SEC_CRC + ERR_GEN_ID_12)    // 0x5212
#define SWO_SEC_CRC_13                    (ERR_SEC_CRC + ERR_GEN_ID_13)    // 0x5213
#define SWO_SEC_CRC_14                    (ERR_SEC_CRC + ERR_GEN_ID_14)    // 0x5214
#define SWO_SEC_CRC_15                    (ERR_SEC_CRC + ERR_GEN_ID_15)    // 0x5215
#define SWO_SEC_CRC_16                    (ERR_SEC_CRC + ERR_GEN_ID_16)    // 0x5216
#define SWO_SEC_CRC_17                    (ERR_SEC_CRC + ERR_GEN_ID_17)    // 0x5217
#define SWO_SEC_CRC_18                    (ERR_SEC_CRC + ERR_GEN_ID_18)    // 0x5218
#define SWO_SEC_CRC_19                    (ERR_SEC_CRC + ERR_GEN_ID_19)    // 0x5219
#define SWO_SEC_CRC_1A                    (ERR_SEC_CRC + ERR_GEN_ID_1A)    // 0x521A
#define SWO_SEC_CRC_1B                    (ERR_SEC_CRC + ERR_GEN_ID_1B)    // 0x521B
#define SWO_SEC_CRC_1C                    (ERR_SEC_CRC + ERR_GEN_ID_1C)    // 0x521C
#define SWO_SEC_CRC_1D                    (ERR_SEC_CRC + ERR_GEN_ID_1D)    // 0x521D
#define SWO_SEC_CRC_1E                    (ERR_SEC_CRC + ERR_GEN_ID_1E)    // 0x521E
#define SWO_SEC_CRC_1F                    (ERR_SEC_CRC + ERR_GEN_ID_1F)    // 0x521F
#define SWO_SEC_CRC_20                    (ERR_SEC_CRC + ERR_GEN_ID_20)    // 0x5220
#define SWO_SEC_CRC_21                    (ERR_SEC_CRC + ERR_GEN_ID_21)    // 0x5221
#define SWO_SEC_CRC_22                    (ERR_SEC_CRC + ERR_GEN_ID_22)    // 0x5222
#define SWO_SEC_CRC_23                    (ERR_SEC_CRC + ERR_GEN_ID_23)    // 0x5223
#define SWO_SEC_CRC_24                    (ERR_SEC_CRC + ERR_GEN_ID_24)    // 0x5224
#define SWO_SEC_CRC_25                    (ERR_SEC_CRC + ERR_GEN_ID_25)    // 0x5225
#define SWO_SEC_CRC_26                    (ERR_SEC_CRC + ERR_GEN_ID_26)    // 0x5226
#define SWO_SEC_CRC_27                    (ERR_SEC_CRC + ERR_GEN_ID_27)    // 0x5227
#define SWO_SEC_CRC_28                    (ERR_SEC_CRC + ERR_GEN_ID_28)    // 0x5228
#define SWO_SEC_CRC_29                    (ERR_SEC_CRC + ERR_GEN_ID_29)    // 0x5229
#define SWO_SEC_CRC_2A                    (ERR_SEC_CRC + ERR_GEN_ID_2A)    // 0x522A
#define SWO_SEC_CRC_2B                    (ERR_SEC_CRC + ERR_GEN_ID_2B)    // 0x522B
#define SWO_SEC_CRC_2C                    (ERR_SEC_CRC + ERR_GEN_ID_2C)    // 0x522C
#define SWO_SEC_CRC_2D                    (ERR_SEC_CRC + ERR_GEN_ID_2D)    // 0x522D

#define SWO_SEC_CHK_01                    (ERR_SEC_CHK + ERR_GEN_ID_01)    // 0x5301
#define SWO_SEC_CHK_02                    (ERR_SEC_CHK + ERR_GEN_ID_02)    // 0x5302
#define SWO_SEC_CHK_03                    (ERR_SEC_CHK + ERR_GEN_ID_03)    // 0x5303
#define SWO_SEC_CHK_04                    (ERR_SEC_CHK + ERR_GEN_ID_04)    // 0x5304
#define SWO_SEC_CHK_05                    (ERR_SEC_CHK + ERR_GEN_ID_05)    // 0x5305
#define SWO_SEC_CHK_06                    (ERR_SEC_CHK + ERR_GEN_ID_06)    // 0x5306
#define SWO_SEC_CHK_07                    (ERR_SEC_CHK + ERR_GEN_ID_07)    // 0x5307
#define SWO_SEC_CHK_08                    (ERR_SEC_CHK + ERR_GEN_ID_08)    // 0x5308
#define SWO_SEC_CHK_09                    (ERR_SEC_CHK + ERR_GEN_ID_09)    // 0x5309
#define SWO_SEC_CHK_0A                    (ERR_SEC_CHK + ERR_GEN_ID_0A)    // 0x530A
#define SWO_SEC_CHK_0B                    (ERR_SEC_CHK + ERR_GEN_ID_0B)    // 0x530B
#define SWO_SEC_CHK_0C                    (ERR_SEC_CHK + ERR_GEN_ID_0C)    // 0x530C
#define SWO_SEC_CHK_0D                    (ERR_SEC_CHK + ERR_GEN_ID_0D)    // 0x530D
#define SWO_SEC_CHK_0E                    (ERR_SEC_CHK + ERR_GEN_ID_0E)    // 0x530E
#define SWO_SEC_CHK_0F                    (ERR_SEC_CHK + ERR_GEN_ID_0F)    // 0x530F
#define SWO_SEC_CHK_10                    (ERR_SEC_CHK + ERR_GEN_ID_10)    // 0x5310
#define SWO_SEC_CHK_11                    (ERR_SEC_CHK + ERR_GEN_ID_11)    // 0x5311
#define SWO_SEC_CHK_12                    (ERR_SEC_CHK + ERR_GEN_ID_12)    // 0x5312
#define SWO_SEC_CHK_13                    (ERR_SEC_CHK + ERR_GEN_ID_13)    // 0x5313
#define SWO_SEC_CHK_14                    (ERR_SEC_CHK + ERR_GEN_ID_14)    // 0x5314
#define SWO_SEC_CHK_15                    (ERR_SEC_CHK + ERR_GEN_ID_15)    // 0x5315
#define SWO_SEC_CHK_16                    (ERR_SEC_CHK + ERR_GEN_ID_16)    // 0x5316
#define SWO_SEC_CHK_17                    (ERR_SEC_CHK + ERR_GEN_ID_17)    // 0x5317
#define SWO_SEC_CHK_18                    (ERR_SEC_CHK + ERR_GEN_ID_18)    // 0x5318
#define SWO_SEC_CHK_19                    (ERR_SEC_CHK + ERR_GEN_ID_19)    // 0x5319
#define SWO_SEC_CHK_1A                    (ERR_SEC_CHK + ERR_GEN_ID_1A)    // 0x531A
#define SWO_SEC_CHK_1B                    (ERR_SEC_CHK + ERR_GEN_ID_1B)    // 0x531B
#define SWO_SEC_CHK_1C                    (ERR_SEC_CHK + ERR_GEN_ID_1C)    // 0x531C
#define SWO_SEC_CHK_1D                    (ERR_SEC_CHK + ERR_GEN_ID_1D)    // 0x531D
#define SWO_SEC_CHK_1E                    (ERR_SEC_CHK + ERR_GEN_ID_1E)    // 0x531E
#define SWO_SEC_CHK_1F                    (ERR_SEC_CHK + ERR_GEN_ID_1F)    // 0x531F
#define SWO_SEC_CHK_20                    (ERR_SEC_CHK + ERR_GEN_ID_20)    // 0x5320
#define SWO_SEC_CHK_21                    (ERR_SEC_CHK + ERR_GEN_ID_21)    // 0x5321
#define SWO_SEC_CHK_22                    (ERR_SEC_CHK + ERR_GEN_ID_22)    // 0x5322
#define SWO_SEC_CHK_23                    (ERR_SEC_CHK + ERR_GEN_ID_23)    // 0x5323
#define SWO_SEC_CHK_24                    (ERR_SEC_CHK + ERR_GEN_ID_24)    // 0x5324
#define SWO_SEC_CHK_25                    (ERR_SEC_CHK + ERR_GEN_ID_25)    // 0x5325
#define SWO_SEC_CHK_26                    (ERR_SEC_CHK + ERR_GEN_ID_26)    // 0x5326

#define SWO_SEC_KEY_01                    (ERR_SEC_KEY + ERR_GEN_ID_01)    // 0x5401
#define SWO_SEC_KEY_02                    (ERR_SEC_KEY + ERR_GEN_ID_02)    // 0x5402
#define SWO_SEC_KEY_03                    (ERR_SEC_KEY + ERR_GEN_ID_03)    // 0x5403
#define SWO_SEC_KEY_04                    (ERR_SEC_KEY + ERR_GEN_ID_04)    // 0x5404
#define SWO_SEC_KEY_05                    (ERR_SEC_KEY + ERR_GEN_ID_05)    // 0x5405
#define SWO_SEC_KEY_06                    (ERR_SEC_KEY + ERR_GEN_ID_06)    // 0x5406
#define SWO_SEC_KEY_07                    (ERR_SEC_KEY + ERR_GEN_ID_07)    // 0x5407

#define SWO_SEC_PIN_01                    (ERR_SEC_PIN + ERR_GEN_ID_01)    // 0x5501
#define SWO_SEC_PIN_02                    (ERR_SEC_PIN + ERR_GEN_ID_02)    // 0x5502
#define SWO_SEC_PIN_03                    (ERR_SEC_PIN + ERR_GEN_ID_03)    // 0x5503
#define SWO_SEC_PIN_04                    (ERR_SEC_PIN + ERR_GEN_ID_04)    // 0x5504
#define SWO_SEC_PIN_05                    (ERR_SEC_PIN + ERR_GEN_ID_05)    // 0x5505
#define SWO_SEC_PIN_06                    (ERR_SEC_PIN + ERR_GEN_ID_06)    // 0x5506
#define SWO_SEC_PIN_07                    (ERR_SEC_PIN + ERR_GEN_ID_07)    // 0x5507
#define SWO_SEC_PIN_08                    (ERR_SEC_PIN + ERR_GEN_ID_08)    // 0x5508
#define SWO_SEC_PIN_09                    (ERR_SEC_PIN + ERR_GEN_ID_09)    // 0x5509
#define SWO_SEC_PIN_0A                    (ERR_SEC_PIN + ERR_GEN_ID_0A)    // 0x550A
#define SWO_SEC_PIN_0B                    (ERR_SEC_PIN + ERR_GEN_ID_0B)    // 0x550B
#define SWO_SEC_PIN_0C                    (ERR_SEC_PIN + ERR_GEN_ID_0C)    // 0x550C
#define SWO_SEC_PIN_0D                    (ERR_SEC_PIN + ERR_GEN_ID_0D)    // 0x550D
#define SWO_SEC_PIN_0E                    (ERR_SEC_PIN + ERR_GEN_ID_0E)    // 0x550E
#define SWO_SEC_PIN_0F                    (ERR_SEC_PIN + ERR_GEN_ID_0F)    // 0x550F
#define SWO_SEC_PIN_10                    (ERR_SEC_PIN + ERR_GEN_ID_10)    // 0x5510
#define SWO_SEC_PIN_11                    (ERR_SEC_PIN + ERR_GEN_ID_11)    // 0x5511
#define SWO_SEC_PIN_12                    (ERR_SEC_PIN + ERR_GEN_ID_12)    // 0x5512
#define SWO_SEC_PIN_13                    (ERR_SEC_PIN + ERR_GEN_ID_13)    // 0x5513
#define SWO_SEC_PIN_14                    (ERR_SEC_PIN + ERR_GEN_ID_14)    // 0x5514
#define SWO_SEC_PIN_15                    (ERR_SEC_PIN + ERR_GEN_ID_15)    // 0x5515

#define SWO_SEC_SCP_01                    (ERR_SEC_SCP + ERR_GEN_ID_01)    // 0x5601
#define SWO_SEC_SCP_02                    (ERR_SEC_SCP + ERR_GEN_ID_02)    // 0x5602

#define SWO_SEC_SIG_01                    (ERR_SEC_SIG + ERR_GEN_ID_01)    // 0x5701
#define SWO_SEC_SIG_02                    (ERR_SEC_SIG + ERR_GEN_ID_02)    // 0x5702
#define SWO_SEC_SIG_03                    (ERR_SEC_SIG + ERR_GEN_ID_03)    // 0x5703
#define SWO_SEC_SIG_04                    (ERR_SEC_SIG + ERR_GEN_ID_04)    // 0x5704
#define SWO_SEC_SIG_05                    (ERR_SEC_SIG + ERR_GEN_ID_05)    // 0x5705
#define SWO_SEC_SIG_06                    (ERR_SEC_SIG + ERR_GEN_ID_06)    // 0x5706
#define SWO_SEC_SIG_07                    (ERR_SEC_SIG + ERR_GEN_ID_07)    // 0x5707
#define SWO_SEC_SIG_08                    (ERR_SEC_SIG + ERR_GEN_ID_08)    // 0x5708
#define SWO_SEC_SIG_09                    (ERR_SEC_SIG + ERR_GEN_ID_09)    // 0x5709
#define SWO_SEC_SIG_0A                    (ERR_SEC_SIG + ERR_GEN_ID_0A)    // 0x570A
#define SWO_SEC_SIG_0B                    (ERR_SEC_SIG + ERR_GEN_ID_0B)    // 0x570B
#define SWO_SEC_SIG_0C                    (ERR_SEC_SIG + ERR_GEN_ID_0C)    // 0x570C
#define SWO_SEC_SIG_0D                    (ERR_SEC_SIG + ERR_GEN_ID_0D)    // 0x570D
#define SWO_SEC_SIG_0E                    (ERR_SEC_SIG + ERR_GEN_ID_0E)    // 0x570E
#define SWO_SEC_SIG_0F                    (ERR_SEC_SIG + ERR_GEN_ID_0F)    // 0x570F
#define SWO_SEC_SIG_10                    (ERR_SEC_SIG + ERR_GEN_ID_10)    // 0x5710
#define SWO_SEC_SIG_11                    (ERR_SEC_SIG + ERR_GEN_ID_11)    // 0x5711
#define SWO_SEC_SIG_12                    (ERR_SEC_SIG + ERR_GEN_ID_12)    // 0x5712
#define SWO_SEC_SIG_13                    (ERR_SEC_SIG + ERR_GEN_ID_13)    // 0x5713
#define SWO_SEC_SIG_14                    (ERR_SEC_SIG + ERR_GEN_ID_14)    // 0x5714

#define SWO_SEC_MEM_01                    (ERR_SEC_MEM + ERR_GEN_ID_01)    // 0x5801
#define SWO_SEC_MEM_02                    (ERR_SEC_MEM + ERR_GEN_ID_02)    // 0x5802
#define SWO_SEC_MEM_03                    (ERR_SEC_MEM + ERR_GEN_ID_03)    // 0x5803
#define SWO_SEC_MEM_04                    (ERR_SEC_MEM + ERR_GEN_ID_04)    // 0x5804
#define SWO_SEC_MEM_05                    (ERR_SEC_MEM + ERR_GEN_ID_05)    // 0x5805
#define SWO_SEC_MEM_06                    (ERR_SEC_MEM + ERR_GEN_ID_06)    // 0x5806
#define SWO_SEC_MEM_07                    (ERR_SEC_MEM + ERR_GEN_ID_07)    // 0x5807
#define SWO_SEC_MEM_08                    (ERR_SEC_MEM + ERR_GEN_ID_08)    // 0x5808
#define SWO_SEC_MEM_09                    (ERR_SEC_MEM + ERR_GEN_ID_09)    // 0x5809
#define SWO_SEC_MEM_0A                    (ERR_SEC_MEM + ERR_GEN_ID_0A)    // 0x580A
#define SWO_SEC_MEM_0B                    (ERR_SEC_MEM + ERR_GEN_ID_0B)    // 0x580B
#define SWO_SEC_MEM_0C                    (ERR_SEC_MEM + ERR_GEN_ID_0C)    // 0x580C
#define SWO_SEC_MEM_0D                    (ERR_SEC_MEM + ERR_GEN_ID_0D)    // 0x580D
#define SWO_SEC_MEM_0E                    (ERR_SEC_MEM + ERR_GEN_ID_0E)    // 0x580E
#define SWO_SEC_MEM_0F                    (ERR_SEC_MEM + ERR_GEN_ID_0F)    // 0x580F
#define SWO_SEC_MEM_10                    (ERR_SEC_MEM + ERR_GEN_ID_10)    // 0x5810

#define SWO_SEC_STA_01                    (ERR_SEC_STA + ERR_GEN_ID_01)    // 0x5901
#define SWO_SEC_STA_02                    (ERR_SEC_STA + ERR_GEN_ID_02)    // 0x5902
#define SWO_SEC_STA_03                    (ERR_SEC_STA + ERR_GEN_ID_03)    // 0x5903
#define SWO_SEC_STA_04                    (ERR_SEC_STA + ERR_GEN_ID_04)    // 0x5904
#define SWO_SEC_STA_05                    (ERR_SEC_STA + ERR_GEN_ID_05)    // 0x5905
#define SWO_SEC_STA_06                    (ERR_SEC_STA + ERR_GEN_ID_06)    // 0x5906
#define SWO_SEC_STA_07                    (ERR_SEC_STA + ERR_GEN_ID_07)    // 0x5907
#define SWO_SEC_STA_08                    (ERR_SEC_STA + ERR_GEN_ID_08)    // 0x5908
#define SWO_SEC_STA_09                    (ERR_SEC_STA + ERR_GEN_ID_09)    // 0x5909
#define SWO_SEC_STA_0A                    (ERR_SEC_STA + ERR_GEN_ID_0A)    // 0x590A
#define SWO_SEC_STA_0B                    (ERR_SEC_STA + ERR_GEN_ID_0B)    // 0x590B
#define SWO_SEC_STA_0C                    (ERR_SEC_STA + ERR_GEN_ID_0C)    // 0x590C
#define SWO_SEC_STA_0D                    (ERR_SEC_STA + ERR_GEN_ID_0D)    // 0x590D

/**
 * APDU-related issues are categorized into:
 * Class issues (CLA),
 * Instruction issues (INS),
 * Other APDU header checks (HDR),
 * Operating System state (STA),
 * Length issues (LEN),
 * Transmitted data issues (DAT).
 */
#define ERR_APD_CLA                       (ERR_APD_RANGE + ERR_GEN_SUB_0E)
#define ERR_APD_INS                       (ERR_APD_RANGE + ERR_GEN_SUB_0D)
#define ERR_APD_HDR                       (ERR_APD_RANGE + ERR_GEN_SUB_05)
#define ERR_APD_STA                       (ERR_APD_RANGE + ERR_GEN_SUB_06)
#define ERR_APD_LEN                       (ERR_APD_RANGE + ERR_GEN_SUB_07)
#define ERR_APD_DAT                       (ERR_APD_RANGE + ERR_GEN_SUB_08)

#define SWO_APD_CLA_01                    (ERR_APD_CLA + ERR_GEN_ID_01)    // 0x6E01
#define SWO_APD_CLA_02                    (ERR_APD_CLA + ERR_GEN_ID_02)    // 0x6E02

#define SWO_APD_INS_01                    (ERR_APD_INS + ERR_GEN_ID_01)    // 0x6D01
#define SWO_APD_INS_02                    (ERR_APD_INS + ERR_GEN_ID_02)    // 0x6D02
#define SWO_APD_INS_03                    (ERR_APD_INS + ERR_GEN_ID_03)    // 0x6D03
#define SWO_APD_INS_04                    (ERR_APD_INS + ERR_GEN_ID_04)    // 0x6D04
#define SWO_APD_INS_05                    (ERR_APD_INS + ERR_GEN_ID_05)    // 0x6D05
#define SWO_APD_INS_06                    (ERR_APD_INS + ERR_GEN_ID_06)    // 0x6D06
#define SWO_APD_INS_07                    (ERR_APD_INS + ERR_GEN_ID_07)    // 0x6D07
#define SWO_APD_INS_08                    (ERR_APD_INS + ERR_GEN_ID_08)    // 0x6D08
#define SWO_APD_INS_09                    (ERR_APD_INS + ERR_GEN_ID_09)    // 0x6D09

#define SWO_APD_HDR_01                    (ERR_APD_HDR + ERR_GEN_ID_01)    // 0x6501
#define SWO_APD_HDR_02                    (ERR_APD_HDR + ERR_GEN_ID_02)    // 0x6502
#define SWO_APD_HDR_03                    (ERR_APD_HDR + ERR_GEN_ID_03)    // 0x6503
#define SWO_APD_HDR_04                    (ERR_APD_HDR + ERR_GEN_ID_04)    // 0x6504
#define SWO_APD_HDR_05                    (ERR_APD_HDR + ERR_GEN_ID_05)    // 0x6505
#define SWO_APD_HDR_06                    (ERR_APD_HDR + ERR_GEN_ID_06)    // 0x6506
#define SWO_APD_HDR_07                    (ERR_APD_HDR + ERR_GEN_ID_07)    // 0x6507
#define SWO_APD_HDR_08                    (ERR_APD_HDR + ERR_GEN_ID_08)    // 0x6508
#define SWO_APD_HDR_09                    (ERR_APD_HDR + ERR_GEN_ID_09)    // 0x6509
#define SWO_APD_HDR_0A                    (ERR_APD_HDR + ERR_GEN_ID_0A)    // 0x650A
#define SWO_APD_HDR_0B                    (ERR_APD_HDR + ERR_GEN_ID_0B)    // 0x650B
#define SWO_APD_HDR_0C                    (ERR_APD_HDR + ERR_GEN_ID_0C)    // 0x650C
#define SWO_APD_HDR_0D                    (ERR_APD_HDR + ERR_GEN_ID_0D)    // 0x650D
#define SWO_APD_HDR_0E                    (ERR_APD_HDR + ERR_GEN_ID_0E)    // 0x650E
#define SWO_APD_HDR_0F                    (ERR_APD_HDR + ERR_GEN_ID_0F)    // 0x650F
#define SWO_APD_HDR_10                    (ERR_APD_HDR + ERR_GEN_ID_10)    // 0x6510
#define SWO_APD_HDR_11                    (ERR_APD_HDR + ERR_GEN_ID_11)    // 0x6511
#define SWO_APD_HDR_12                    (ERR_APD_HDR + ERR_GEN_ID_12)    // 0x6512
#define SWO_APD_HDR_13                    (ERR_APD_HDR + ERR_GEN_ID_13)    // 0x6513
#define SWO_APD_HDR_14                    (ERR_APD_HDR + ERR_GEN_ID_14)    // 0x6514
#define SWO_APD_HDR_15                    (ERR_APD_HDR + ERR_GEN_ID_15)    // 0x6515
#define SWO_APD_HDR_16                    (ERR_APD_HDR + ERR_GEN_ID_16)    // 0x6516

#define SWO_APD_LEN_01                    (ERR_APD_LEN + ERR_GEN_ID_01)    // 0x6701
#define SWO_APD_LEN_02                    (ERR_APD_LEN + ERR_GEN_ID_02)    // 0x6702
#define SWO_APD_LEN_03                    (ERR_APD_LEN + ERR_GEN_ID_03)    // 0x6703
#define SWO_APD_LEN_04                    (ERR_APD_LEN + ERR_GEN_ID_04)    // 0x6704
#define SWO_APD_LEN_05                    (ERR_APD_LEN + ERR_GEN_ID_05)    // 0x6705
#define SWO_APD_LEN_06                    (ERR_APD_LEN + ERR_GEN_ID_06)    // 0x6706
#define SWO_APD_LEN_07                    (ERR_APD_LEN + ERR_GEN_ID_07)    // 0x6707
#define SWO_APD_LEN_08                    (ERR_APD_LEN + ERR_GEN_ID_08)    // 0x6708
#define SWO_APD_LEN_09                    (ERR_APD_LEN + ERR_GEN_ID_09)    // 0x6709
#define SWO_APD_LEN_0A                    (ERR_APD_LEN + ERR_GEN_ID_0A)    // 0x670A
#define SWO_APD_LEN_0B                    (ERR_APD_LEN + ERR_GEN_ID_0B)    // 0x670B
#define SWO_APD_LEN_0C                    (ERR_APD_LEN + ERR_GEN_ID_0C)    // 0x670C
#define SWO_APD_LEN_0D                    (ERR_APD_LEN + ERR_GEN_ID_0D)    // 0x670D
#define SWO_APD_LEN_0E                    (ERR_APD_LEN + ERR_GEN_ID_0E)    // 0x670E
#define SWO_APD_LEN_0F                    (ERR_APD_LEN + ERR_GEN_ID_0F)    // 0x670F
#define SWO_APD_LEN_10                    (ERR_APD_LEN + ERR_GEN_ID_10)    // 0x6710
#define SWO_APD_LEN_11                    (ERR_APD_LEN + ERR_GEN_ID_11)    // 0x6711
#define SWO_APD_LEN_12                    (ERR_APD_LEN + ERR_GEN_ID_12)    // 0x6712
#define SWO_APD_LEN_13                    (ERR_APD_LEN + ERR_GEN_ID_13)    // 0x6713
#define SWO_APD_LEN_14                    (ERR_APD_LEN + ERR_GEN_ID_14)    // 0x6714
#define SWO_APD_LEN_15                    (ERR_APD_LEN + ERR_GEN_ID_15)    // 0x6715
#define SWO_APD_LEN_16                    (ERR_APD_LEN + ERR_GEN_ID_16)    // 0x6716
#define SWO_APD_LEN_17                    (ERR_APD_LEN + ERR_GEN_ID_17)    // 0x6717
#define SWO_APD_LEN_18                    (ERR_APD_LEN + ERR_GEN_ID_18)    // 0x6718
#define SWO_APD_LEN_19                    (ERR_APD_LEN + ERR_GEN_ID_19)    // 0x6719
#define SWO_APD_LEN_1A                    (ERR_APD_LEN + ERR_GEN_ID_1A)    // 0x671A
#define SWO_APD_LEN_1B                    (ERR_APD_LEN + ERR_GEN_ID_1B)    // 0x671B
#define SWO_APD_LEN_1C                    (ERR_APD_LEN + ERR_GEN_ID_1C)    // 0x671C
#define SWO_APD_LEN_1D                    (ERR_APD_LEN + ERR_GEN_ID_1D)    // 0x671D
#define SWO_APD_LEN_1E                    (ERR_APD_LEN + ERR_GEN_ID_1E)    // 0x671E
#define SWO_APD_LEN_1F                    (ERR_APD_LEN + ERR_GEN_ID_1F)    // 0x671F
#define SWO_APD_LEN_20                    (ERR_APD_LEN + ERR_GEN_ID_20)    // 0x6720
#define SWO_APD_LEN_21                    (ERR_APD_LEN + ERR_GEN_ID_21)    // 0x6721
#define SWO_APD_LEN_22                    (ERR_APD_LEN + ERR_GEN_ID_22)    // 0x6722
#define SWO_APD_LEN_23                    (ERR_APD_LEN + ERR_GEN_ID_23)    // 0x6723
#define SWO_APD_LEN_24                    (ERR_APD_LEN + ERR_GEN_ID_24)    // 0x6724
#define SWO_APD_LEN_25                    (ERR_APD_LEN + ERR_GEN_ID_25)    // 0x6725
#define SWO_APD_LEN_26                    (ERR_APD_LEN + ERR_GEN_ID_26)    // 0x6726
#define SWO_APD_LEN_27                    (ERR_APD_LEN + ERR_GEN_ID_27)    // 0x6727
#define SWO_APD_LEN_28                    (ERR_APD_LEN + ERR_GEN_ID_28)    // 0x6728
#define SWO_APD_LEN_29                    (ERR_APD_LEN + ERR_GEN_ID_29)    // 0x6729
#define SWO_APD_LEN_2A                    (ERR_APD_LEN + ERR_GEN_ID_2A)    // 0x672A
#define SWO_APD_LEN_2B                    (ERR_APD_LEN + ERR_GEN_ID_2B)    // 0x672B
#define SWO_APD_LEN_2C                    (ERR_APD_LEN + ERR_GEN_ID_2C)    // 0x672C
#define SWO_APD_LEN_2D                    (ERR_APD_LEN + ERR_GEN_ID_2D)    // 0x672D
#define SWO_APD_LEN_2E                    (ERR_APD_LEN + ERR_GEN_ID_2E)    // 0x672E
#define SWO_APD_LEN_2F                    (ERR_APD_LEN + ERR_GEN_ID_2F)    // 0x672F
#define SWO_APD_LEN_30                    (ERR_APD_LEN + ERR_GEN_ID_30)    // 0x6730
#define SWO_APD_LEN_31                    (ERR_APD_LEN + ERR_GEN_ID_31)    // 0x6731
#define SWO_APD_LEN_32                    (ERR_APD_LEN + ERR_GEN_ID_32)    // 0x6732

#define SWO_APD_DAT_01                    (ERR_APD_DAT + ERR_GEN_ID_01)    // 0x6801
#define SWO_APD_DAT_02                    (ERR_APD_DAT + ERR_GEN_ID_02)    // 0x6802
#define SWO_APD_DAT_03                    (ERR_APD_DAT + ERR_GEN_ID_03)    // 0x6803
#define SWO_APD_DAT_04                    (ERR_APD_DAT + ERR_GEN_ID_04)    // 0x6804
#define SWO_APD_DAT_05                    (ERR_APD_DAT + ERR_GEN_ID_05)    // 0x6805
#define SWO_APD_DAT_06                    (ERR_APD_DAT + ERR_GEN_ID_06)    // 0x6806
#define SWO_APD_DAT_07                    (ERR_APD_DAT + ERR_GEN_ID_07)    // 0x6807
#define SWO_APD_DAT_08                    (ERR_APD_DAT + ERR_GEN_ID_08)    // 0x6808
#define SWO_APD_DAT_09                    (ERR_APD_DAT + ERR_GEN_ID_09)    // 0x6809
#define SWO_APD_DAT_0A                    (ERR_APD_DAT + ERR_GEN_ID_0A)    // 0x680A
#define SWO_APD_DAT_0B                    (ERR_APD_DAT + ERR_GEN_ID_0B)    // 0x680B
#define SWO_APD_DAT_0C                    (ERR_APD_DAT + ERR_GEN_ID_0C)    // 0x680C
#define SWO_APD_DAT_0D                    (ERR_APD_DAT + ERR_GEN_ID_0D)    // 0x680D
#define SWO_APD_DAT_0E                    (ERR_APD_DAT + ERR_GEN_ID_0E)    // 0x680E
#define SWO_APD_DAT_0F                    (ERR_APD_DAT + ERR_GEN_ID_0F)    // 0x680F
#define SWO_APD_DAT_10                    (ERR_APD_DAT + ERR_GEN_ID_10)    // 0x6810
#define SWO_APD_DAT_11                    (ERR_APD_DAT + ERR_GEN_ID_11)    // 0x6811
#define SWO_APD_DAT_12                    (ERR_APD_DAT + ERR_GEN_ID_12)    // 0x6812
#define SWO_APD_DAT_13                    (ERR_APD_DAT + ERR_GEN_ID_13)    // 0x6813
#define SWO_APD_DAT_14                    (ERR_APD_DAT + ERR_GEN_ID_14)    // 0x6814
#define SWO_APD_DAT_15                    (ERR_APD_DAT + ERR_GEN_ID_15)    // 0x6815
#define SWO_APD_DAT_16                    (ERR_APD_DAT + ERR_GEN_ID_16)    // 0x6816
#define SWO_APD_DAT_17                    (ERR_APD_DAT + ERR_GEN_ID_17)    // 0x6817
#define SWO_APD_DAT_18                    (ERR_APD_DAT + ERR_GEN_ID_18)    // 0x6818
#define SWO_APD_DAT_19                    (ERR_APD_DAT + ERR_GEN_ID_19)    // 0x6819
#define SWO_APD_DAT_1A                    (ERR_APD_DAT + ERR_GEN_ID_1A)    // 0x681A
#define SWO_APD_DAT_1B                    (ERR_APD_DAT + ERR_GEN_ID_1B)    // 0x681B
#define SWO_APD_DAT_1C                    (ERR_APD_DAT + ERR_GEN_ID_1C)    // 0x681C
#define SWO_APD_DAT_1D                    (ERR_APD_DAT + ERR_GEN_ID_1D)    // 0x681D
#define SWO_APD_DAT_1E                    (ERR_APD_DAT + ERR_GEN_ID_1E)    // 0x681E
#define SWO_APD_DAT_1F                    (ERR_APD_DAT + ERR_GEN_ID_1F)    // 0x681F
#define SWO_APD_DAT_20                    (ERR_APD_DAT + ERR_GEN_ID_20)    // 0x6820
#define SWO_APD_DAT_21                    (ERR_APD_DAT + ERR_GEN_ID_21)    // 0x6821
#define SWO_APD_DAT_22                    (ERR_APD_DAT + ERR_GEN_ID_22)    // 0x6822
#define SWO_APD_DAT_23                    (ERR_APD_DAT + ERR_GEN_ID_23)    // 0x6823
#define SWO_APD_DAT_24                    (ERR_APD_DAT + ERR_GEN_ID_24)    // 0x6824
#define SWO_APD_DAT_25                    (ERR_APD_DAT + ERR_GEN_ID_25)    // 0x6825
#define SWO_APD_DAT_26                    (ERR_APD_DAT + ERR_GEN_ID_26)    // 0x6826
#define SWO_APD_DAT_27                    (ERR_APD_DAT + ERR_GEN_ID_27)    // 0x6827
#define SWO_APD_DAT_28                    (ERR_APD_DAT + ERR_GEN_ID_28)    // 0x6828
#define SWO_APD_DAT_29                    (ERR_APD_DAT + ERR_GEN_ID_29)    // 0x6829
#define SWO_APD_DAT_2A                    (ERR_APD_DAT + ERR_GEN_ID_2A)    // 0x682A
#define SWO_APD_DAT_2B                    (ERR_APD_DAT + ERR_GEN_ID_2B)    // 0x682B
#define SWO_APD_DAT_2C                    (ERR_APD_DAT + ERR_GEN_ID_2C)    // 0x682C
#define SWO_APD_DAT_2D                    (ERR_APD_DAT + ERR_GEN_ID_2D)    // 0x682D
#define SWO_APD_DAT_2E                    (ERR_APD_DAT + ERR_GEN_ID_2E)    // 0x682E
#define SWO_APD_DAT_2F                    (ERR_APD_DAT + ERR_GEN_ID_2F)    // 0x682F
#define SWO_APD_DAT_30                    (ERR_APD_DAT + ERR_GEN_ID_30)    // 0x6830
#define SWO_APD_DAT_31                    (ERR_APD_DAT + ERR_GEN_ID_31)    // 0x6831
#define SWO_APD_DAT_32                    (ERR_APD_DAT + ERR_GEN_ID_32)    // 0x6832
#define SWO_APD_DAT_33                    (ERR_APD_DAT + ERR_GEN_ID_33)    // 0x6833

#define SWO_APD_STA_01                    (ERR_APD_STA + ERR_GEN_ID_01)    // 0x6601
#define SWO_APD_STA_02                    (ERR_APD_STA + ERR_GEN_ID_02)    // 0x6602
#define SWO_APD_STA_03                    (ERR_APD_STA + ERR_GEN_ID_03)    // 0x6603
#define SWO_APD_STA_04                    (ERR_APD_STA + ERR_GEN_ID_04)    // 0x6604
#define SWO_APD_STA_05                    (ERR_APD_STA + ERR_GEN_ID_05)    // 0x6605
#define SWO_APD_STA_06                    (ERR_APD_STA + ERR_GEN_ID_06)    // 0x6606
#define SWO_APD_STA_07                    (ERR_APD_STA + ERR_GEN_ID_07)    // 0x6607
#define SWO_APD_STA_08                    (ERR_APD_STA + ERR_GEN_ID_08)    // 0x6608
#define SWO_APD_STA_09                    (ERR_APD_STA + ERR_GEN_ID_09)    // 0x6609
#define SWO_APD_STA_0A                    (ERR_APD_STA + ERR_GEN_ID_0A)    // 0x660A
#define SWO_APD_STA_0B                    (ERR_APD_STA + ERR_GEN_ID_0B)    // 0x660B
#define SWO_APD_STA_0C                    (ERR_APD_STA + ERR_GEN_ID_0C)    // 0x660C
#define SWO_APD_STA_0D                    (ERR_APD_STA + ERR_GEN_ID_0D)    // 0x660D
#define SWO_APD_STA_0E                    (ERR_APD_STA + ERR_GEN_ID_0E)    // 0x660E
#define SWO_APD_STA_0F                    (ERR_APD_STA + ERR_GEN_ID_0F)    // 0x660F
#define SWO_APD_STA_10                    (ERR_APD_STA + ERR_GEN_ID_10)    // 0x6610
#define SWO_APD_STA_11                    (ERR_APD_STA + ERR_GEN_ID_11)    // 0x6611
#define SWO_APD_STA_12                    (ERR_APD_STA + ERR_GEN_ID_12)    // 0x6612
#define SWO_APD_STA_13                    (ERR_APD_STA + ERR_GEN_ID_13)    // 0x6613
#define SWO_APD_STA_14                    (ERR_APD_STA + ERR_GEN_ID_14)    // 0x6614
#define SWO_APD_STA_15                    (ERR_APD_STA + ERR_GEN_ID_15)    // 0x6615
#define SWO_APD_STA_16                    (ERR_APD_STA + ERR_GEN_ID_16)    // 0x6616
#define SWO_APD_STA_17                    (ERR_APD_STA + ERR_GEN_ID_17)    // 0x6617
#define SWO_APD_STA_18                    (ERR_APD_STA + ERR_GEN_ID_18)    // 0x6618
#define SWO_APD_STA_19                    (ERR_APD_STA + ERR_GEN_ID_19)    // 0x6619
#define SWO_APD_STA_1A                    (ERR_APD_STA + ERR_GEN_ID_1A)    // 0x661A
#define SWO_APD_STA_1B                    (ERR_APD_STA + ERR_GEN_ID_1B)    // 0x661B
#define SWO_APD_STA_1C                    (ERR_APD_STA + ERR_GEN_ID_1C)    // 0x661C
#define SWO_APD_STA_1D                    (ERR_APD_STA + ERR_GEN_ID_1D)    // 0x661D
#define SWO_APD_STA_1E                    (ERR_APD_STA + ERR_GEN_ID_1E)    // 0x661E
#define SWO_APD_STA_1F                    (ERR_APD_STA + ERR_GEN_ID_1F)    // 0x661F
#define SWO_APD_STA_20                    (ERR_APD_STA + ERR_GEN_ID_20)    // 0x6620
#define SWO_APD_STA_21                    (ERR_APD_STA + ERR_GEN_ID_21)    // 0x6621
#define SWO_APD_STA_22                    (ERR_APD_STA + ERR_GEN_ID_22)    // 0x6622
#define SWO_APD_STA_23                    (ERR_APD_STA + ERR_GEN_ID_23)    // 0x6623
#define SWO_APD_STA_24                    (ERR_APD_STA + ERR_GEN_ID_24)    // 0x6624
#define SWO_APD_STA_25                    (ERR_APD_STA + ERR_GEN_ID_25)    // 0x6625
#define SWO_APD_STA_26                    (ERR_APD_STA + ERR_GEN_ID_26)    // 0x6626
#define SWO_APD_STA_27                    (ERR_APD_STA + ERR_GEN_ID_27)    // 0x6627
#define SWO_APD_STA_28                    (ERR_APD_STA + ERR_GEN_ID_28)    // 0x6628
#define SWO_APD_STA_29                    (ERR_APD_STA + ERR_GEN_ID_29)    // 0x6629
#define SWO_APD_STA_2A                    (ERR_APD_STA + ERR_GEN_ID_2A)    // 0x662A
#define SWO_APD_STA_2B                    (ERR_APD_STA + ERR_GEN_ID_2B)    // 0x662B
#define SWO_APD_STA_2C                    (ERR_APD_STA + ERR_GEN_ID_2C)    // 0x662C
#define SWO_APD_STA_2D                    (ERR_APD_STA + ERR_GEN_ID_2D)    // 0x662D
#define SWO_APD_STA_2E                    (ERR_APD_STA + ERR_GEN_ID_2E)    // 0x662E
#define SWO_APD_STA_2F                    (ERR_APD_STA + ERR_GEN_ID_2F)    // 0x662F
#define SWO_APD_STA_30                    (ERR_APD_STA + ERR_GEN_ID_30)    // 0x6630
#define SWO_APD_STA_31                    (ERR_APD_STA + ERR_GEN_ID_31)    // 0x6631
#define SWO_APD_STA_32                    (ERR_APD_STA + ERR_GEN_ID_32)    // 0x6632
#define SWO_APD_STA_33                    (ERR_APD_STA + ERR_GEN_ID_33)    // 0x6633
#define SWO_APD_STA_34                    (ERR_APD_STA + ERR_GEN_ID_34)    // 0x6634
#define SWO_APD_STA_35                    (ERR_APD_STA + ERR_GEN_ID_35)    // 0x6635
#define SWO_APD_STA_36                    (ERR_APD_STA + ERR_GEN_ID_36)    // 0x6636
#define SWO_APD_STA_37                    (ERR_APD_STA + ERR_GEN_ID_37)    // 0x6637
#define SWO_APD_STA_38                    (ERR_APD_STA + ERR_GEN_ID_38)    // 0x6638
#define SWO_APD_STA_39                    (ERR_APD_STA + ERR_GEN_ID_39)    // 0x6639
#define SWO_APD_STA_3A                    (ERR_APD_STA + ERR_GEN_ID_3A)    // 0x663A
#define SWO_APD_STA_3B                    (ERR_APD_STA + ERR_GEN_ID_3B)    // 0x663B
#define SWO_APD_STA_3C                    (ERR_APD_STA + ERR_GEN_ID_3C)    // 0x663C
#define SWO_APD_STA_3D                    (ERR_APD_STA + ERR_GEN_ID_3D)    // 0x663D

/**
 * The process is successful.
 */
#define SWO_SUCCESS                       0x9000

/**
 * For internal use only, not meant to be returned
 */
#define SWO_OK                            0x0000
#define SWO_KO                            0x0001

/**
 * Miscellaneous Unexplained issues (no categorization, Unknown).
 */
#define SWO_MUI_UNK_01                    (ERR_MUI_RANGE + ERR_GEN_ID_01)    // 0xA001
#define SWO_MUI_UNK_02                    (ERR_MUI_RANGE + ERR_GEN_ID_02)    // 0xA002
#define SWO_MUI_UNK_03                    (ERR_MUI_RANGE + ERR_GEN_ID_03)    // 0xA003
#define SWO_MUI_UNK_04                    (ERR_MUI_RANGE + ERR_GEN_ID_04)    // 0xA004
#define SWO_MUI_UNK_05                    (ERR_MUI_RANGE + ERR_GEN_ID_05)    // 0xA005
#define SWO_MUI_UNK_06                    (ERR_MUI_RANGE + ERR_GEN_ID_06)    // 0xA006
#define SWO_MUI_UNK_07                    (ERR_MUI_RANGE + ERR_GEN_ID_07)    // 0xA007
#define SWO_MUI_UNK_08                    (ERR_MUI_RANGE + ERR_GEN_ID_08)    // 0xA008
#define SWO_MUI_UNK_09                    (ERR_MUI_RANGE + ERR_GEN_ID_09)    // 0xA009
#define SWO_MUI_UNK_0A                    (ERR_MUI_RANGE + ERR_GEN_ID_0A)    // 0xA00A
#define SWO_MUI_UNK_0B                    (ERR_MUI_RANGE + ERR_GEN_ID_0B)    // 0xA00B
#define SWO_MUI_UNK_0C                    (ERR_MUI_RANGE + ERR_GEN_ID_0C)    // 0xA00C
#define SWO_MUI_UNK_0D                    (ERR_MUI_RANGE + ERR_GEN_ID_0D)    // 0xA00D
#define SWO_MUI_UNK_0E                    (ERR_MUI_RANGE + ERR_GEN_ID_0E)    // 0xA00E
#define SWO_MUI_UNK_0F                    (ERR_MUI_RANGE + ERR_GEN_ID_0F)    // 0xA00F
#define SWO_MUI_UNK_10                    (ERR_MUI_RANGE + ERR_GEN_ID_10)    // 0xA010
#define SWO_MUI_UNK_11                    (ERR_MUI_RANGE + ERR_GEN_ID_11)    // 0xA011
#define SWO_MUI_UNK_12                    (ERR_MUI_RANGE + ERR_GEN_ID_12)    // 0xA012
#define SWO_MUI_UNK_13                    (ERR_MUI_RANGE + ERR_GEN_ID_13)    // 0xA013
#define SWO_MUI_UNK_14                    (ERR_MUI_RANGE + ERR_GEN_ID_14)    // 0xA014
#define SWO_MUI_UNK_15                    (ERR_MUI_RANGE + ERR_GEN_ID_15)    // 0xA015
#define SWO_MUI_UNK_16                    (ERR_MUI_RANGE + ERR_GEN_ID_16)    // 0xA016
#define SWO_MUI_UNK_17                    (ERR_MUI_RANGE + ERR_GEN_ID_17)    // 0xA017
#define SWO_MUI_UNK_18                    (ERR_MUI_RANGE + ERR_GEN_ID_18)    // 0xA018

// Legacy
#define EXCEPTION                         0x1  // keep original value // SWO_MUI_UNK_01
#define INVALID_PARAMETER                 0x2  // keep original value // SWO_CRY_LEN_01
#define EXCEPTION_SECURITY                0x3  // keep original value // SWO_MUI_UNK_02
#define INVALID_STATE                     0x4  // keep original value // SWO_CRY_VAL_01
#define EXCEPTION_IO_RESET                0x5  // keep original value // SWO_IOL_RST_01
#define NOT_ENOUGH_SPACE                  0x6  // keep original value // SWO_CRY_VAL_01
#define EXCEPTION_OVERFLOW                0x7  // keep original value // SWO_MUI_UNK_03
#define INVALID_CRC                       0x8  // keep original value // SWO_MUI_UNK_0C
#define INVALID_CHECKSUM                  0x9  // keep original value // SWO_MUI_UNK_0D
#define INVALID_COUNTER                   0xA  // keep original value // SWO_MUI_UNK_0E
#define NOT_SUPPORTED                     0xB  // keep original value // SWO_MUI_UNK_0F
#define TIMEOUT                           0xC  // keep original value // SWO_MUI_UNK_10
#define EXCEPTION_PIC                     0xD  // keep original value // SWO_MUI_UNK_11
#define EXCEPTION_APPEXIT                 0xE  // keep original value // SWO_MUI_UNK_12
#define EXCEPTION_IO_OVERFLOW             0xF  // keep original value // SWO_MUI_UNK_13
#define EXCEPTION_IO_HEADER               0x10 // keep original value // SWO_MUI_UNK_14
#define EXCEPTION_IO_STATE                0x11 // keep original value // SWO_MUI_UNK_15
#define EXCEPTION_CXPORT                  0x12 // keep original value // SWO_MUI_UNK_16
#define EXCEPTION_SYSTEM                  0x13 // keep original value // SWO_MUI_UNK_17

/* Custom error type for all OS errors */
typedef uint32_t bolos_err_t;

#endif // ERRORS_H
