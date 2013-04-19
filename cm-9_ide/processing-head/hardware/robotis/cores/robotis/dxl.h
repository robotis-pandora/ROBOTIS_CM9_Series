
/************************* (C) COPYRIGHT 2010 ROBOTIS *************************
* File Name          : dynamixel.h
* Author             : danceww
* Version            : V0.1
* Date               : 2010/08/26
* Description        : This file contains the dynamixel communication function.
                       for the firmware.
*******************************************************************************/
/* Copyright (C) 2013 ROBOTIS, Co., Ltd.
 *
 * @File: dxl.h ( <- dynamixel.h )
 * @Brief : ported dynamixel SDK from CM-530 firmware for CM-9XX series
 *
 */
#ifndef DXL_H_
#define DXL_H_


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "libpandora_types.h"
#include "gpio.h"
#include "usart.h"
#include "usb_type.h"
#include "dxl_constants.h"

/* Debug defines ------------------------------------------------------------*/
#ifdef CM9_DEBUG
//#define PRINT_OUT_PACKET_TO_USART2
//#define PRINT_OUT_COMMUNICATION_ERROR_TO_USART2
//#define PRINT_OUT_TRACE_ERROR_PRINT_TO_USART2
#endif

/* Exported types ------------------------------------------------------------*/



#define RX_WAIT_TIMEOUT			0xf000
#define RX_TIMEOUT_COUNT2		(1600L) //(1000L) //porting
#define NANO_TIME_DELAY			(12000) //ydh added 20111228 -> 20120210 edited ydh
//#define RX_TIMEOUT_COUNT1  	(RX_TIMEOUT_COUNT2*90L)// -> 110msec  before Ver 1.11e
#define RX_TIMEOUT_COUNT1  		(RX_TIMEOUT_COUNT2*128L)//  -> 156msec for ID 110 safe access after Ver 1.11f //porting ydh
#define DOWNLOAD_TIMEOUT  		(RX_WAIT_TIMEOUT-0x1000)



/*
 * defines for error message
 * */
#define ERRBIT_VOLTAGE		(1)
#define ERRBIT_ANGLE		(2)
#define ERRBIT_OVERHEAT		(4)
#define ERRBIT_RANGE		(8)
#define ERRBIT_CHECKSUM		(16)
#define ERRBIT_OVERLOAD		(32)
#define ERRBIT_INSTRUCTION	(64)

/*Half Duflex UART ENABLE PIN ----------------------------------------------------------------------------------------------*/
#ifdef BOARD_CM900
#define PORT_ENABLE_TXD			GPIOB
#define PORT_ENABLE_RXD			GPIOB

#define PIN_ENABLE_TXD			4
#define PIN_ENABLE_RXD			5


#define PORT_DXL_TXD			GPIOB
#define PORT_DXL_RXD			GPIOB

#define PIN_DXL_TXD				6
#define PIN_DXL_RXD				7
//set to TXD Enable
#define	DXL_TXD	{ gpio_write_bit(PORT_ENABLE_TXD, PIN_ENABLE_TXD, 1 ); gpio_write_bit(PORT_ENABLE_RXD, PIN_ENABLE_RXD, 0 );}
//set to RXD Enable
#define	DXL_RXD	{ gpio_write_bit(PORT_ENABLE_TXD, PIN_ENABLE_TXD, 0 ); gpio_write_bit(PORT_ENABLE_RXD, PIN_ENABLE_RXD, 1 );}


#elif BOARD_CM900_REV10

#define PORT_TXRX_DIRECTION		GPIOB
#define PIN_TXRX_DIRECTION		5

#define PORT_DXL_TXD			GPIOB
#define PORT_DXL_RXD			GPIOB

#define PIN_DXL_TXD				6
#define PIN_DXL_RXD				7

#define	DXL_TXD	{ gpio_write_bit(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, 1); } //set to HIGH
#define	DXL_RXD	{ gpio_write_bit(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, 0); } //set to LOW

#endif



/*Global Variables ----------------------------------------------------------------------------------------------*/
volatile byte  gbDXLWritePointer;
volatile byte  gbDXLReadPointer;
volatile byte  gbpDXLDataBuffer[256];

volatile byte gbpParameter[130+10];
volatile byte gbBusUsed;
uint32 gbRxLength;
byte gbpRxBuffer[255];
byte gbpTxBuffer[255];

uint8 gbIsDynmixelUsed; //[ROBOTIS]2012-12-13

/*
 * Raw methods for basic packet methods
 * */
void clearBuffer256(void);
byte checkNewArrive(void);
void TxByteToDXL( byte bTxData);
byte RxByteFromDXL(void);

/*
 * Basic packet communications methods
 * */
byte txrx_Packet(byte bID, byte bInst, byte bTxParaLen);
byte tx_Packet(byte bID, byte bInstruction, byte bParameterLength);
byte rx_Packet(byte bLength);
/*
 *
 */

#ifdef __cplusplus
}
#endif


#endif /* DXL_H_ */
