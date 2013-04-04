/* Copyright (C) 2013 ROBOTIS, Co., Ltd.
 *
 * @File: dxl_hal.c
 * @Brief : Dynamixel SDK platform dependent source
 * 
 */

#include "dxl_hal.h"
#include "usart.h"
#include "timer.h"

/*extern void TxDStringC(char *str);
void TxDHex8C(u16 bSentData);
void TxByteToDXL( byte bTxData);*/

//For Dynamixel
void TIM2_IRQHandler(void)
{
	Interrupt1ms();
}


int dxl_hal_open( int devIndex, int baudrate )
{
	// Opening device
	// devIndex: Device index
	// baudrate: Real baudrate (ex> 115200, 57600, 38400...)
	// Return: 0(Failed), 1(Succeed)

	//USART_Configuration(baudrate);

	gpio_set_mode(PORT_DXL_TXD, PIN_DXL_TXD, GPIO_AF_OUTPUT_PP);
	gpio_set_mode(PORT_DXL_RXD, PIN_DXL_RXD, GPIO_INPUT_FLOATING);


	usart_init(USART1);
	//TxDStringC("USART clock = ");TxDHex32C(STM32_PCLK2);TxDStringC("\r\n");
	usart_set_baud_rate(USART1, STM32_PCLK2, baudrate);
	usart_enable(USART1);



	return 1;
}



void TxByteToDXL( byte bTxData)
{
	USART1->regs->DR = (bTxData & (u16)0x01FF);
	while( (USART1->regs->SR & ((u16)0x0040)) == RESET );
}

void DisableUSART1(void)
{
	usart_disable(USART1);
	//USART_Cmd(USART1, DISABLE);
}
void dxl_hal_close()
{
	// Closing device

	/* Disable the USART1 */
	DisableUSART1();
}

void dxl_hal_clear(void)
{
	// Clear communication buffer

	ClearBuffer256();
}

int dxl_hal_tx( unsigned char *pPacket, int numPacket )
{
	// Transmiting date
	// *pPacket: data array pointer
	// numPacket: number of data array
	// Return: number of data transmitted. -1 is error.

#ifdef BOARD_CM900 //CM900 REV A~C
	gpio_write_bit(PORT_ENABLE_TXD, PIN_ENABLE_TXD, 1 );// TX Enable
	gpio_write_bit(PORT_ENABLE_RXD, PIN_ENABLE_RXD, 0 );// RX Disable
#else
	gpio_write_bit(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, 1 );// TX Enable
#endif
	unsigned char i;
	for(i=0 ; i<numPacket; i++  )
	{

		TxByteToDXL( pPacket[i]);

	}

#ifdef BOARD_CM900
	gpio_write_bit(PORT_ENABLE_TXD, PIN_ENABLE_TXD, 0 );// TX Disable
	gpio_write_bit(PORT_ENABLE_RXD, PIN_ENABLE_RXD, 1 );// RX Enable
#else
	gpio_write_bit(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, 0 );// TX Enable
#endif

	return numPacket;
}

int dxl_hal_rx( unsigned char *pPacket, int numPacket )
{
	// Receiving data
	// *pPacket: data array pointer
	// numPacket: number of data array
	// Return: number of data received. -1 is error.

	unsigned char i;
	for( i=0 ; i<numPacket ; i++ )
	{
		if (CheckNewArrive())
		{
			pPacket[i] =  RxByte();

		}
		else
		{
			return i;
		}

	}
	return numPacket;
}
byte RxByte(void)
{
    byte bTemp = 0;


	bTemp = gbpDXLDataBuffer[gbDXLReadPointer];
	gbDXLReadPointer++;

	return bTemp;
}

void dxl_hal_set_timeout( int NumRcvByte )
{
	// Start stop watch
	// NumRcvByte: number of recieving data(to calculate maximum waiting time)

	//exceed range of int...
	timer_resume(TIMER2);
	StartDiscount(NumRcvByte*100);
}

int dxl_hal_timeout(void)
{
	// Check timeout
	// Return: 0 is false, 1 is true(timeout occurred)

	return CheckTimeOut();
}


void ClearBuffer256(void)
{
	gbDXLReadPointer = gbDXLWritePointer = 0;
}

byte CheckNewArrive(void)
{
	if(gbDXLReadPointer != gbDXLWritePointer)
		return 1;
	else
		return 0;
}



void StartDiscount(s32 StartTime)
{
	gw1msCounter = StartTime;
}

u8 CheckTimeOut(void)
{
	// Check timeout
	// Return: 0 is false, 1 is true(timeout occurred)

	if(gw1msCounter == 0){
		timer_pause(TIMER2);
		return 1;
	}
	else
		return 0;
}

//For Dynamixel
void Interrupt1ms(void)
{
	//gu32TimingCounter1ms++;



	if(gw1msCounter > 0)
		gw1msCounter--;
}

