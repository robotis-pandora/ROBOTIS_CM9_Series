// Zigbee SDK platform dependent source
#include "zgb_hal.h"
#include "usart.h"


volatile byte                   gbPacketWritePointer = 0; // PC, Wireless
volatile byte                   gbPacketReadPointer = 0;
//volatile byte                   gbPacketPointer = 0;
volatile byte                   gbpPacketDataBuffer[16+1+16];
volatile byte                   gbpPacket[PACKET_LENGTH+2];
volatile byte                   gbNewPacket;
volatile word                   gwZigbeeRxData;


void EnableZigbee(int baud)
{
	//USART_Configuration(USART_ZIGBEE, 57600);
	//GPIO_ResetBits(PORT_ZIGBEE_RESET, PIN_ZIGBEE_RESET);

	usart_init(USART2);
		//TxDStringC("USART clock = ");TxDHex32C(STM32_PCLK2);TxDStringC("\r\n");
	usart_set_baud_rate(USART2, STM32_PCLK1, baud);
	usart_enable(USART2);

}


int zgb_hal_open( int devIndex, int baudrate )
{
	// Opening device
	// devIndex: Device index
	// baudrate: Real baudrate (ex> 115200, 57600, 38400...)
	// Return: 0(Failed), 1(Succeed)
	EnableZigbee(baudrate);

	return 1;
}

void zgb_hal_close()
{
	// Closing device
	DisableZigbee();
}

void TxDByte_Zigbee(byte bTxdData)
{
	/*USART_SendData(USART1,bTxdData);
	while( USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET );
	*/
	USART2->regs->DR = (bTxdData & (u16)0x01FF);
	while( (USART2->regs->SR & ((u16)0x0040)) == RESET );
}

byte RxDByte_Zigbee(void)
{
	byte bTemp;

	while(1)
	{
		if(gbPacketReadPointer != gbPacketWritePointer) break;
	}

	bTemp = gbpPacketDataBuffer[gbPacketReadPointer];
	gbPacketReadPointer++;

	gbPacketReadPointer = gbPacketReadPointer & 0x1F; //added 2012-11-23
	return bTemp;
}


int zgb_hal_tx( unsigned char *pPacket, int numPacket )
{
	// Transmiting date
	// *pPacket: data array pointer
	// numPacket: number of data array
	// Return: number of data transmitted. -1 is error.
	unsigned char i;
	for(i=0 ; i<numPacket; i++  )
		TxDByte_Zigbee(pPacket[i]);

	return numPacket;
}

byte CheckZgbNewArrive(void)
{
	if(gbPacketReadPointer != gbPacketWritePointer)
		return 1;
	else
		return 0;
}

int zgb_hal_rx( unsigned char *pPacket, int numPacket )
{
	// Recieving date
	// *pPacket: data array pointer
	// numPacket: number of data array
	// Return: number of data recieved. -1 is error.
	unsigned char i;
	for( i=0 ; i<numPacket ; i++ )
	{
		if (CheckZgbNewArrive())
			pPacket[i] =  RxDByte_Zigbee();

		else
			return i;
	}

	return numPacket;
}
