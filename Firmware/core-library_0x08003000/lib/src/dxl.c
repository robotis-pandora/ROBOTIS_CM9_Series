/*
 * dxl.c
 *
 *  Created on: 2013. 4. 18.
 *      Author: in2storm
 */

#include "dxl.h"


uint32 Dummy(uint32 tmp){
	return tmp;
}

void uDelay(uint32 uTime) {
	uint32 cnt, max;
	static uint32 tmp = 0;

	for( max=0; max < uTime; max++)
	{
		for( cnt=0; cnt < 10 ; cnt++ )
		{
			tmp +=Dummy(cnt);
		}
	}
	//tmpdly = tmp;
}
void nDelay(uint32 nTime) { //100ns
	uint32 cnt, max;
	cnt=0;
	static uint32 tmp = 0;

	for( max=0; max < nTime; max++)
	{
		//for( cnt=0; cnt < 10 ; cnt++ )
		//{
			tmp +=Dummy(cnt);
		//}
	}
	//tmpdly = tmp;
}

void clearBuffer256(void){
	gbDXLReadPointer = gbDXLWritePointer = 0;
}
byte checkNewArrive(void){
	if(gbDXLReadPointer != gbDXLWritePointer)
		return 1;
	else
		return 0;
}
/*void TxByteToDXL(byte bTxData){
	USART_SendData(USART1,bTxData);
	while( USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET );
}*/
void TxByteToDXL(byte bTxData){
	//USART_SendData(USART1,bTxData);
	//while( USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET );
	USART1->regs->DR = (bTxData & (u16)0x01FF);
		while( (USART1->regs->SR & ((u16)0x0040)) == RESET );
}
byte RxByteFromDXL(void){
	return gbpDXLDataBuffer[gbDXLReadPointer++];
}


/**
 * @brief communicate with dynamixel bus on CM-9XX series. After transmitting packets to the bus, also it receives status feedback packets.
 * @param bID dynamixel ID
 * @param bInst Instruction number, you can find it from dynamixel.h
 * @param bTxParaLen length of packet
 *
 */

byte txrxPacket(byte bID, byte bInst, byte bTxParaLen){
	#define TRY_NUM 2//;;2

	byte bTxLen, bRxLenEx, bTryCount;

	gbBusUsed = 1;


	for(bTryCount = 0; bTryCount < TRY_NUM; bTryCount++)
	{
		gbDXLReadPointer = gbDXLWritePointer; //BufferClear050728
		bTxLen = txPacket(bID, bInst, bTxParaLen);

		if(bInst == INST_PING)
		{
			if(bID == BROADCAST_ID)
			{
				gbRxLength = bRxLenEx = 255;
			}
			else
			{
				gbRxLength = bRxLenEx = 6;
			}
		}
		else if(bInst == INST_READ)
		{
			gbRxLength = bRxLenEx = 6+gbpParameter[1];
		}
		else if( bID == BROADCAST_ID )
		{
			gbRxLength = bRxLenEx = 0;
			break;
		}
		else
		{
			gbRxLength = bRxLenEx = 6;
		}


		if(bRxLenEx)//(gbpValidServo[bID] > 0x81 || bInst != INST_WRITE)) //ValidServo = 0x80|RETURN_LEVEL
		{
			gbRxLength = rxPacket(bRxLenEx);
			//TxDString("gbRxLength = ");TxD_Dec_U8(gbRxLength);TxDString("\r\n");
			//TxDString("bRxLenEx = ");TxD_Dec_U8(bRxLenEx);TxDString("\r\n");
			//      if(gbRxLength != bRxLenEx) //&& bRxLenEx != 255) before Ver 1.11e
			if((gbRxLength != bRxLenEx) && (bRxLenEx != 255)) // after Ver 1.11f
			{
				unsigned long ulCounter;
				word wTimeoutCount;
				ulCounter = 0;
				wTimeoutCount = 0;
				//TxDString("\r\n TEST POINT 0");//TxDString("\r\n Err ID:0x");
				while(ulCounter++ < RX_TIMEOUT_COUNT2)
				{
					if(gbDXLReadPointer != gbDXLWritePointer) {
						gbDXLReadPointer = gbDXLWritePointer; //BufferClear
						ulCounter = 0;
						if(wTimeoutCount++ > 100 )
						{
							//uDelay(0);// porting ydh added
							break; //porting ydh 100->245 //;;;;;; min max 뒤바뀜 found at Ver 1.11e
						}
						nDelay(NANO_TIME_DELAY);// porting ydh added 20120210.
					}
					//uDelay(0);// porting ydh added
					nDelay(NANO_TIME_DELAY);// porting ydh added

				}
				//TxDString("\r\n TEST POINT 1");//TxDString("\r\n Err ID:0x");
				gbDXLReadPointer = gbDXLWritePointer; //BufferClear
			}
			else
			{
				//TxDString("\r\n TEST POINT 6");//TxDString("\r\n Err ID:0x");
				break;
			}
		}
	}

	//TxDString("\r\n TEST POINT 2");//TxDString("\r\n Err ID:0x");
	gbBusUsed = 0;

	if((gbRxLength != bRxLenEx) && (gbpTxBuffer[2] != BROADCAST_ID))
	{
		//TxDString("\r\n TEST POINT 3");//TxDString("\r\n Err ID:0x");
#ifdef	PRINT_OUT_COMMUNICATION_ERROR_TO_USART2
		//TxDString("\r\n Err ID:0x");
		//TxDHex8(bID);
		//TxDString("\r\n ->[DXL]Err: ");
		PrintBuffer(gbpTxBuffer,bTxLen);
		//TxDString("\r\n <-[DXL]Err: ");
		PrintBuffer(gbpRxBuffer,gbRxLength);
#endif

#ifdef	PRINT_OUT_TRACE_ERROR_PRINT_TO_USART2
		//TxDString("\r\n {[ERROR:");TxD16Hex(0x8100);TxDByte(':');TxD16Hex(bID);TxDByte(':');TxD8Hex(bInst);TxDByte(']');TxDByte('}');
		//TxDByte(bID);TxDByte(' ');
		//TxDByte(bInst);TxDByte(' ');
		//TxDByte(gbpParameter[0]);TxDByte(' ');
		//TxDByte(gbpParameter[1]);TxDByte(' ');
#endif
		return 0;
	}

	//TxDString("\r\n TEST POINT 4");//TxDString("\r\n Err ID:0x");
#ifdef PRINT_OUT_PACKET_TO_USART2
	TxDString("\r\n ->[TX Buffer]: ");
	PrintBuffer(gbpTxBuffer,bTxLen);
	TxDString("\r\n <-[RX Buffer]: ");
	PrintBuffer(gbpRxBuffer,gbRxLength);
#endif

	//gbLengthForPacketMaking =0;
	return 1;
}


//갯수에 맞게 받는 이유 : 통신에러가 나오면 Length가 틀릴 가능성이 무척 높기 때문
byte rxPacket(byte bRxLength){
	unsigned long ulCounter, ulTimeLimit;
	byte bCount, bLength, bChecksum;
	byte bTimeout;

	bTimeout = 0;
	if(bRxLength == 255) ulTimeLimit = RX_TIMEOUT_COUNT1;
	else ulTimeLimit = RX_TIMEOUT_COUNT2;
	for(bCount = 0; bCount < bRxLength; bCount++)
	{
		ulCounter = 0;
		while(gbDXLReadPointer == gbDXLWritePointer)
		{
			nDelay(NANO_TIME_DELAY); // porting ydh
			if(ulCounter++ > ulTimeLimit)
			{
				bTimeout = 1;

				break;
			}
			//uDelay(0); //porting ydh added
		}
		if(bTimeout) break;
		gbpRxBuffer[bCount] = gbpDXLDataBuffer[gbDXLReadPointer++];
		//TxDString("gbpRxBuffer = ");TxDHex8(gbpRxBuffer[bCount]);TxDString("\r\n");
	}


	bLength = bCount;
	bChecksum = 0;

	if( gbpTxBuffer[2] != BROADCAST_ID )
	{
		if(bTimeout && bRxLength != 255)
		{
#ifdef PRINT_OUT_COMMUNICATION_ERROR_TO_USART2
			TxDString("Rx Timeout");
			TxDByte(bLength);
#endif
			clearBuffer256();

			//return 0;
		}
		if(bLength > 3) //checking available length.
		{
			if(gbpRxBuffer[0] != 0xff || gbpRxBuffer[1] != 0xff )
			{
#ifdef PRINT_OUT_COMMUNICATION_ERROR_TO_USART2
				TxDString("Wrong Header");//[Wrong Header]
#endif
				clearBuffer256();
				return 0;
			}
			if(gbpRxBuffer[2] != gbpTxBuffer[2] )
			{
#ifdef PRINT_OUT_COMMUNICATION_ERROR_TO_USART2
				TxDString("[Error:TxID != RxID]");
#endif
				clearBuffer256();
				return 0;
			}
			if(gbpRxBuffer[3] != bLength-4)
			{
#ifdef PRINT_OUT_COMMUNICATION_ERROR_TO_USART2
				TxDString("RxLength Error");
#endif
				clearBuffer256();
				return 0;
			}
			for(bCount = 2; bCount < bLength; bCount++) bChecksum += gbpRxBuffer[bCount];
			if(bChecksum != 0xff)
			{
#ifdef PRINT_OUT_COMMUNICATION_ERROR_TO_USART2
				TxDString("[RxChksum Error]");
#endif
				clearBuffer256();
				return 0;
			}
		}
	}

	return bLength;
}


byte txPacket(byte bID, byte bInstruction, byte bParameterLength){
    byte bCount,bCheckSum,bPacketLength;

	gbpTxBuffer[0] = 0xff;
    gbpTxBuffer[1] = 0xff;
    gbpTxBuffer[2] = bID;
    gbpTxBuffer[3] = bParameterLength+2; //Length(Paramter,Instruction,Checksum)

    gbpTxBuffer[4] = bInstruction;

    for(bCount = 0; bCount < bParameterLength; bCount++)
    {
        gbpTxBuffer[bCount+5] = gbpParameter[bCount];
    }
    bCheckSum = 0;
    bPacketLength = bParameterLength+4+2;

    for(bCount = 2; bCount < bPacketLength-1; bCount++) //except 0xff,checksum
    {
        bCheckSum += gbpTxBuffer[bCount];
    }

    gbpTxBuffer[bCount] = ~bCheckSum; //Writing Checksum with Bit Inversion

    DXL_TXD; // this define is declared in dxl.h


    for(bCount = 0; bCount < bPacketLength; bCount++)
    {
        TxByteToDXL(gbpTxBuffer[bCount]);
    }

    DXL_RXD;// this define is declared in dxl.h



    return(bPacketLength);
}


