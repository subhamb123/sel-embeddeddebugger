/******************************************************************************
* Copyright (c) 2022 - 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
 * @section EEMI_API_DETAIL XilPM EEMI API Version Detail
 *
 * This section provides details of EEMI API version and it's history for PM APIs of XilPM library.
 *
 * | NAME			| ID	| Platform	| Version| Description								     |
 * |----------------------------|-------|---------------|:------:|---------------------------------------------------------------------------|
 * | PM_GET_API_VERSION		| 0x1   | Both		| 1	 | The API is used to request the version number of the API		     |
 * | PM_SET_CONFIGURATION	| 0x2	| ZynqMP	| 1	 | The API is used to configure the power management framework		     |
 * | ^				| ^	| ^		| ^	 | Note: Deprecated in Versal but supported in ZynqMP			     |
 * | PM_GET_NODE_STATUS		| 0x3	| Both		| 1	 | The API is used to obtain information about current status of a device    |
 * | PM_GET_OP_CHARACTERISTIC	| 0x4	| Both		| 2	 | V1 - The API is used to gets operating characteristics of a device	     |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of bitmask functionality, user can check the supported\n									"type" first before performing the actual functionality			    |
 * | PM_REGISTER_NOTIFIER	| 0x5	| Both		| 2	 | V1 - The API is used to register a subsystem to be notified about the\n									device event								    |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of event management functionality			     |
 * | ^				| ^	| ^		| ^	 | Note: V2 is supported in Versal but for ZynqMP it supports only V1	     |
 * | PM_REQUEST_SUSPEND		| 0x6	| Both		| 1	 | The API is used to send suspend request to another subsystem		     |
 * | PM_SELF_SUSPEND		| 0x7	| Both		| 2	 | V1 - The API is used to suspend a child subsystem			     |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of cpu idle functionality during force powerdown	     |
 * | ^				| ^	| ^		| ^	 | Note: V2 is supported in Versal but for ZynqMP it supports only V1	     |
 * | PM_FORCE_POWERDOWN		| 0x8	| Both		| 2	 | V1 - The API is used to Powerdown other processor or node		     |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of cpu idle functionality	during force powerdown	     |
 * | ^				| ^	| ^		| ^	 | Note: V2 is supported in Versal but for ZynqMP it supports only V1	     |
 * | PM_ABORT_SUSPEND		| 0x9	| Both		| 1	 | The API is used to aborting suspend of a child subsystem		     |
 * | PM_REQUEST_WAKEUP		| 0xA	| Both		| 1	 | The API is used to start-up and wake-up a child subsystem		     |
 * | PM_SET_WAKEUP_SOURCE	| 0xB	| Both		| 1	 | The API is used to set wakeup source					     |
 * | PM_SYSTEM_SHUTDOWN		| 0xC	| Both		| 1	 | The API is used to shutdown or restart the system			     |
 * | PM_REQUEST_NODE		| 0xD	| Both		| 2	 | V1 - The API is used to request the usage of a device		     |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of security policy handling during request device	     |
 * | ^				| ^	| ^		| ^	 | Note: V2 is supported in Versal but for ZynqMP it supports only V1	     |
 * | PM_RELEASE_NODE		| 0xE	| Both		| 2	 | V1 - The API is used to release the usage of a device		     |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of security policy handling during request device      |
 * | ^				| ^	| ^		| ^	 | Note: V2 is supported in Versal but for ZynqMP it supports only V1	     |
 * | PM_SET_REQUIREMENT		| 0xF	| Both		| 1	 | The API is used to announce a change in requirement for a specific slave\n									node which is currently in use						    |
 * | PM_SET_MAX_LATENCY		| 0x10	| Both		| 1	 | The API is used to set maximum allowed latency for the device	     |
 * | PM_RESET_ASSERT		| 0x11	| Both		| 1	 | The API is used to reset or de-reset a device			     |
 * | PM_RESET_GET_STATUS	| 0x12	| Both		| 1	 | The API is used to reads the device reset state			     |
 * | PM_MMIO_WRITE		| 0x13	| ZynqMP	| 1	 | The API is used to writes a value into a register			     |
 * | ^				| ^	| ^		| ^	 | Note: Deprecated in Versal but supported in ZynqMP			     |
 * | PM_MMIO_READ		| 0x14	| ZynqMP	| 1	 | The API is used to reads a value from a register			     |
 * | ^				| ^	| ^		| ^	 | Note: Deprecated in Versal but supported in ZynqMP			     |
 * | PM_INIT_FINALIZE		| 0x15	| Both		| 1	 | The API is used to initializes subsystem and releases unused	devices	     |
 * | PM_GET_CHIPID		| 0x18	| Both		| 1	 | The API is used to request the version and ID code of a chip		     |
 * | PM_PINCTRL_REQUEST		| 0x1C	| Both		| 1	 | The API is used to requests the pin					     |
 * | PM_PINCTRL_RELEASE		| 0x1D	| Both		| 1	 | The API is used to releases the pin					     |
 * | PM_PINCTRL_GET_FUNCTION	| 0x1E	| Both		| 1	 | The API is used to reads the pin function				     |
 * | PM_PINCTRL_SET_FUNCTION	| 0x1F	| Both		| 1	 | The API is used to sets the pin function				     |
 * | PM_PINCTRL_CONFIG_PARAM_GET| 0x20	| Both		| 1	 | The API is used to reads the pin parameter value			     |
 * | PM_PINCTRL_CONFIG_PARAM_SET| 0x21	| Both		| 1	 | The API is used to sets the pin parameter value			     |
 * | PM_IOCTL			| 0x22	| Both		| 2	 | V1 - The API is used to performs driver-like IOCTL functions on shared\n									system devices								    |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of bitmask functionality, user can check the supported\n									ID first before performing the actual functionality			    |
 * | PM_QUERY_DATA		| 0x23	| Both		| 2	 | V1 - The API is used to queries information about the platform resources  |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of bitmask functionality, user can check the supported\n									ID first before performing the actual functionality			    |
 * | PM_CLOCK_ENABLE		| 0x24	| Both		| 1	 | The API is used to enables the clock					     |
 * | PM_CLOCK_DISABLE		| 0x25	| Both		| 1	 | The API is used to disables the clock				     |
 * | PM_CLOCK_GETSTATE		| 0x26	| Both		| 1	 | The API is used to reads the clock state				     |
 * | PM_CLOCK_SETDIVIDER	| 0x27	| Both		| 1	 | The API is used to sets the divider value of the clock		     |
 * | PM_CLOCK_GETDIVIDER	| 0x28	| Both		| 1	 | The API is used to reads the clock divider				     |
 * | PM_CLOCK_SETRATE		| 0x29	| Versal	| 1	 | The API is used to sets the rate of the clock			     |
 * | ^				| ^	| ^		| ^	 | Note: Not supported in ZynqMP but supported in Versal		     |
 * | PM_CLOCK_GETRATE		| 0x2A	| Versal	| 1	 | The API is used to gets the rate of the clock			     |
 * | ^				| ^	| ^		| ^	 | Note: Not supported in ZynqMP but supported in Versal		     |
 * | PM_CLOCK_SETPARENT		| 0x2B	| Both		| 1	 | The API is used to sets the parent of the clock			     |
 * | PM_CLOCK_GETPARENT		| 0x2C	| Both		| 1	 | The API is used to reads the clock parent				     |
 * | PM_PLL_SET_PARAM		| 0x30	| Both		| 1	 | The API is used to sets the parameter of PLL clock			     |
 * | PM_PLL_GET_PARAM		| 0x31	| Both		| 1	 | The API is used to reads the parameter of PLL clock			     |
 * | PM_PLL_SET_MODE		| 0x32	| Both		| 1	 | The API is used to sets the mode of PLL clock			     |
 * | PM_PLL_GET_MODE		| 0x33	| Both		| 1	 | The API is used to reads the mode of PLL clock			     |
 * | PM_REGISTER_ACCESS		| 0x34	| ZynqMP	| 1	 | The API is used for register read/write access data			     |
 * | ^				| ^	| ^		| ^	 | Note: Deprecated in Versal but supported in ZynqMP			     |
 * | PM_EFUSE_ACCESS		| 0x35	| ZynqMP	| 1	 | The API is used to provides access to efuse memory			     |
 * | ^				| ^	| ^		| ^	 | Note: Deprecated in Versal but supported in ZynqMP			     |
 * | PM_FEATURE_CHECK		| 0x3F	| Both		| 2	 | V1 - The API is used to returns supported version of the given API	     |
 * | ^				| ^	| ^		| ^	 | V2 - Added support of bitmask payload functionality			     |
 *
 *****************************************************************************/

/*****************************************************************************/
/**
 * @section IOCTL_ID_DETAIL XilPM IOCTL IDs Detail
 *
 * This section provides the details of the IOCTL IDs which are supported across the different platforms and their brief descriptions.
 *
 * | Name				| ID	| Platform	| Description				|
 * |------------------------------------|-------|---------------|---------------------------------------|
 * | IOCTL_GET_RPU_OPER_MODE		| 0	| Both		| Get RPU mode				|
 * | IOCTL_SET_RPU_OPER_MODE		| 1	| Both		| Set RPU mode				|
 * | IOCTL_RPU_BOOT_ADDR_CONFIG		| 2	| Both		| RPU boot address config		|
 * | IOCTL_TCM_COMB_CONFIG		| 3	| Both		| TCM config				|
 * | IOCTL_SET_TAPDELAY_BYPASS		| 4	| Both		| TAP delay bypass			|
 * | IOCTL_SET_SGMII_MODE		| 5	| ZynqMP	| SGMII mode				|
 * | IOCTL_SD_DLL_RESET			| 6	| Both		| SD DLL reset				|
 * | IOCTL_SET_SD_TAPDELAY		| 7	| Both		| SD TAP delay				|
 * | IOCTL_SET_PLL_FRAC_MODE		| 8	| Both		| Set PLL frac mode			|
 * | IOCTL_GET_PLL_FRAC_MODE		| 9	| Both		| Get PLL frac mode			|
 * | IOCTL_SET_PLL_FRAC_DATA		| 10	| Both		| Set PLL frac data			|
 * | IOCTL_GET_PLL_FRAC_DATA		| 11	| Both		| Get PLL frac data			|
 * | IOCTL_WRITE_GGS			| 12	| Both		| Write GGS				|
 * | IOCTL_READ_GGS			| 13	| Both		| Read GGS				|
 * | IOCTL_WRITE_PGGS			| 14	| Both		| Write PGGS				|
 * | IOCTL_READ_PGGS			| 15	| Both		| Read PGGS				|
 * | IOCTL_ULPI_RESET			| 16	| ZynqMP	| ULPI reset				|
 * | IOCTL_SET_BOOT_HEALTH_STATUS	| 17	| Both		| Set boot status			|
 * | IOCTL_AFI				| 18	| ZynqMP	| AFI					|
 * | IOCTL_PROBE_COUNTER_READ		| 19	| Versal	| Probe counter read			|
 * | IOCTL_PROBE_COUNTER_WRITE		| 20	| Versal	| Probe counter write			|
 * | IOCTL_OSPI_MUX_SELECT		| 21	| Versal	| OSPI mux select			|
 * | IOCTL_USB_SET_STATE		| 22	| Versal	| USB set state				|
 * | IOCTL_GET_LAST_RESET_REASON	| 23	| Versal	| Get last reset reason			|
 * | IOCTL_AIE_ISR_CLEAR		| 24	| Versal	| AIE ISR clear				|
 * | IOCTL_REGISTER_SGI			| 25	| None		| Register SGI to ATF			|
 * | IOCTL_SET_FEATURE_CONFIG		| 26	| ZynqMP	| Set runtime feature config		|
 * | IOCTL_GET_FEATURE_CONFIG		| 27	| ZynqMP	| Get runtime feature config		|
 * | IOCTL_READ_REG			| 28	| Versal	| Read a 32-bit register		|
 * | IOCTL_MASK_WRITE_REG		| 29	| Versal	| RMW a 32-bit register			|
 * | IOCTL_SET_SD_CONFIG		| 30	| ZynqMP	| Set SD config register value		|
 * | IOCTL_SET_GEM_CONFIG		| 31	| ZynqMP	| Set GEM config register value		|
 * | IOCTL_SET_USB_CONFIG		| 32	| ZynqMP	| Set USB config register value		|
 * | IOCTL_AIE_OPS			| 33	| Versal	| AIE1/AIEML Run Time Operations	|
 * | IOCTL_GET_QOS			| 34	| Versal	| Get Device QoS value			|
 * | IOCTL_GET_APU_OPER_MODE		| 35	| Versal	| Get APU operation mode		|
 * | IOCTL_SET_APU_OPER_MODE		| 36	| Versal	| Set APU operation mode		|
 *
 *****************************************************************************/

/*****************************************************************************/
/**
 * @section QUERY_ID_DETAIL XilPM QUERY IDs Detail
 *
 * This section provides the details of the QUERY IDs which are supported across the different platforms and their brief descriptions.
 *
 * | Name					| ID	| Platform	| Description				|
 * |--------------------------------------------|-------|---------------|---------------------------------------|
 * | XPM_QID_INVALID				| 0	| Both		| Invalid Query ID			|
 * | XPM_QID_CLOCK_GET_NAME			| 1	| Both		| Get clock name			|
 * | XPM_QID_CLOCK_GET_TOPOLOGY			| 2	| Both		| Get clock topology			|
 * | XPM_QID_CLOCK_GET_FIXEDFACTOR_PARAMS	| 3	| Both		| Get clock fixedfactor parameter	|
 * | XPM_QID_CLOCK_GET_MUXSOURCES		| 4	| Both		| Get clock mux sources			|
 * | XPM_QID_CLOCK_GET_ATTRIBUTES		| 5	| Both		| Get clock attributes			|
 * | XPM_QID_PINCTRL_GET_NUM_PINS		| 6	| Both		| Get total pins			|
 * | XPM_QID_PINCTRL_GET_NUM_FUNCTIONS		| 7	| Both		| Get total pin functions		|
 * | XPM_QID_PINCTRL_GET_NUM_FUNCTION_GROUPS	| 8	| Both		| Get total pin function groups		|
 * | XPM_QID_PINCTRL_GET_FUNCTION_NAME		| 9	| Both		| Get pin function name			|
 * | XPM_QID_PINCTRL_GET_FUNCTION_GROUPS	| 10	| Both		| Get pin function groups		|
 * | XPM_QID_PINCTRL_GET_PIN_GROUPS		| 11	| Both		| Get pin groups			|
 * | XPM_QID_CLOCK_GET_NUM_CLOCKS		| 12	| Both		| Get number of clocks			|
 * | XPM_QID_CLOCK_GET_MAX_DIVISOR		| 13	| Both		| Get max clock divisor			|
 * | XPM_QID_PLD_GET_PARENT			| 14	| Versal	| Get PLD parent			|
 *
 *****************************************************************************/


/*****************************************************************************/
/**
 * @section GET_OP_CHAR_DETAIL XilPM GET_OP_CHAR IDs Detail
 *
 * This section provides the details of the GET_OP_CHAR IDs which are supported across the different platforms and their brief descriptions.
 *
 * | Name				| ID	| Platform	| Description					|
 * |------------------------------------|-------|---------------|-----------------------------------------------|
 * | PM_OPCHAR_TYPE_POWER		| 1	| ZynqMP	| Operating characteristic ID power		|
 * | PM_OPCHAR_TYPE_TEMP		| 2	| Versal	| Operating characteristic ID temperature	|
 * | PM_OPCHAR_TYPE_LATENCY		| 3	| Both		| Operating characteristic ID latency		|
 *
 *****************************************************************************/

 /**
 * @file xpm_api_version.h
 *
 * @addtogroup xpm_versal_apis XilPM APIs
 *****************************************************************************/
