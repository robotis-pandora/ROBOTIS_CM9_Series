/*
 * DynamixelPro.cpp
 *
 *  Created on: 2013. 4. 25.
 *      Author: ROBOTIS,.LTD.
 */

#include "DynamixelPro.h"
#include "dxl_pro.h"
extern uint8 gbIsDynmixelUsed;

DynamixelPro::DynamixelPro() {
	// TODO Auto-generated constructor stub

}

DynamixelPro::~DynamixelPro() {
	// TODO Auto-generated destructor stub
}


void DynamixelPro::begin(int baud) {

	uint32 Baudrate = 0;
	//TxDString("[DXL]start begin\r\n");

	//change GPIO D9(PA9),D10(PA10) -> D20(PB6), D21(PB7) in USART1 using AFIO
	afio_remap(AFIO_REMAP_USART1);
	//must be declare as SWJ_NO_NJRST because dxl bus use PB5 as DXL_DIR in Half Duplex USART and also use SWJ
	afio_cfg_debug_ports(AFIO_DEBUG_FULL_SWJ_NO_NJRST);
#ifdef BOARD_CM900  //Engineering version case

	 gpio_set_mode(PORT_ENABLE_TXD, PIN_ENABLE_TXD, GPIO_OUTPUT_PP);
	 gpio_set_mode(PORT_ENABLE_RXD, PIN_ENABLE_RXD, GPIO_OUTPUT_PP);
	 gpio_write_bit(PORT_ENABLE_TXD, PIN_ENABLE_TXD, 0 );// TX Disable
	 gpio_write_bit(PORT_ENABLE_RXD, PIN_ENABLE_RXD, 1 );// RX Enable
#else
	 gpio_set_mode(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, GPIO_OUTPUT_PP);
	 gpio_write_bit(PORT_TXRX_DIRECTION, PIN_TXRX_DIRECTION, 0 );// RX Enable
#endif

	 // initialize GPIO D20(PB6), D21(PB7) as DXL TX, RX respectively
	 gpio_set_mode(PORT_DXL_TXD, PIN_DXL_TXD, GPIO_AF_OUTPUT_PP);
	 gpio_set_mode(PORT_DXL_RXD, PIN_DXL_RXD, GPIO_INPUT_FLOATING);


	 //Initialize USART 1 device
	 usart_init(USART1);


	 //Calculate baudrate, refer to ROBOTIS support page.
	 //Baudrate = 2000000 / (baud + 1);
	 Baudrate = dxl_get_baudrate(baud);

	usart_set_baud_rate(USART1, STM32_PCLK2, Baudrate);
	nvic_irq_set_priority(USART1->irq_num, 0);//[ROBOTIS][ADD] 2013-04-10 set to priority 0
	usart_attach_interrupt(USART1,dxlProInterrupt);
	usart_enable(USART1);

	gbIsDynmixelUsed = 0;  //[ROBOTIS]2012-12-13 to notify end of using dynamixel classic to uart.c
	clearBuffer256Ex();
	mResult= 0;
}


void DynamixelPro::end(void){

}
/*
 *  [ROBOTIS][ADD][START] 2013-04-09 support read and write on dxl bus
 * */

byte DynamixelPro::readRaw(void){

	/*byte bData=0;
	bData = RxByteFromDXL();
	clearBuffer256();*/
	return RxByteFromDXLEx();
}
void DynamixelPro::writeRaw(uint8 value){

	DXL_TXD

	TxByteToDXLEx(value);

	DXL_RXD

}
/*
 * @brief : if data coming from dxl bus, returns 1, or if not, returns 0.
 *
 */
byte DynamixelPro::available(void){

	return checkNewArriveEx();
}

byte DynamixelPro::readByte(byte bID, int wAddress){
	mResult = 0;
	gbpParameterEx[0]	= (unsigned char)DXL_LOBYTE(wAddress);
	gbpParameterEx[1]	= (unsigned char)DXL_HIBYTE(wAddress);
	gbpParameterEx[2]	= 1; //1byte
	gbpParameterEx[3]	= 0;
	if(txrx_PacketEx(bID, INST_READ_EX, 4)){
		mResult = 1;
		return(gbpRxBufferEx[9]);
	}else{
		mResult = 0;
		return 0xff;
	}


}
byte DynamixelPro::writeByte(uint8 bID, int wAddress, byte bData){
	mResult = 0;
	//insert wAddress to parameter bucket
	gbpParameterEx[0]	= (unsigned char)DXL_LOBYTE(wAddress);
	gbpParameterEx[1]	= (unsigned char)DXL_HIBYTE(wAddress);
	//insert data to parameter bucket
	gbpParameterEx[2]	= bData;
	mResult = txrx_PacketEx(bID, INST_WRITE_EX, 3); //// parameter length 4 = 2(address)+2(data)
	return mResult;

}
word DynamixelPro::readWord(byte bID, int wAddress){

	mResult = 0;
	gbpParameterEx[0]	= (unsigned char)DXL_LOBYTE(wAddress);
	gbpParameterEx[1]	= (unsigned char)DXL_HIBYTE(wAddress);
	gbpParameterEx[2]	= 2; //1byte
	gbpParameterEx[3]	= 0;
	if(txrx_PacketEx(bID, INST_READ_EX, 4)){
		mResult = 1;
		return(DXL_MAKEWORD(gbpRxBufferEx[9], gbpRxBufferEx[10]));
	}else{
		mResult = 0;
		return 0xff;
	}

}
byte DynamixelPro::writeWord(byte bID, int wAddress, word wData){
	mResult = 0;
	//insert wAddress to parameter bucket
	gbpParameterEx[0]	= (unsigned char)DXL_LOBYTE(wAddress);
	gbpParameterEx[1]	= (unsigned char)DXL_HIBYTE(wAddress);
	//insert data to parameter bucket
	gbpParameterEx[2]	= DXL_LOBYTE(wData);
	gbpParameterEx[3]	= DXL_HIBYTE(wData);

	mResult = txrx_PacketEx(bID, INST_WRITE_EX, 4); //// parameter length 4 = 2(address)+2(data)

	return mResult;
}

byte DynamixelPro::writeDword( byte bID, int wAddress, unsigned int value ){
	mResult = 0;
	//insert wAddress to parameter bucket
	gbpParameterEx[0]	= (unsigned char)DXL_LOBYTE(wAddress);
	gbpParameterEx[1]	= (unsigned char)DXL_HIBYTE(wAddress);
	//insert data to parameter bucket
	gbpParameterEx[2]	= DXL_LOBYTE(DXL_LOWORD(value));
	gbpParameterEx[3]	= DXL_HIBYTE(DXL_LOWORD(value));
	gbpParameterEx[4]	= DXL_LOBYTE(DXL_HIWORD(value));
	gbpParameterEx[5]	= DXL_HIBYTE(DXL_HIWORD(value));

	mResult = txrx_PacketEx(bID, INST_WRITE_EX, 6); //// parameter length 4 = 2(address)+2(data)
	return mResult;
}
