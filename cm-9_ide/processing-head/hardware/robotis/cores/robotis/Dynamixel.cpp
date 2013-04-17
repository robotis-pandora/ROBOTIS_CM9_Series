/******************************************************************************
 * License
 *
 * Copyright (c) 2012 ROBOTIS,.LTD.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

#include "Dynamixel.h"

#include "dxl_core.h"
#include "dxl_hal.h"
#include "HardwareTimer.h"

#include "gpio.h"
//#include "timer.h"
#include "wirish_math.h"


//extern void TxDString(char *str);

Dynamixel Dxl; //[ROBOTIS] declare dynamixel instance in advance, it is used by sketch code.

HardwareTimer timer(2);//[ROBOTIS][ADD] 2013-04-03 Add to support dynamixel bus for timeout.

Dynamixel::Dynamixel(void) {


}

void Dynamixel::begin(int baud) {
	//TxDString("[DXL]start begin\r\n");

	afio_remap(AFIO_REMAP_USART1);//USART1 -> DXL
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
	/* timer_set_mode(TIMER2, TIMER_CH1, TIMER_OUTPUT_COMPARE);

	 timer_pause(TIMER2);

	 uint16 ovf = timer_get_reload(TIMER2);
	 timer_set_count(TIMER2, min(0, ovf));

	 timer_set_reload(TIMER2, 10000);//set overflow

	 ovf = timer_get_reload(TIMER2);
	 timer_set_compare(TIMER2, TIMER_CH1, min(1000, ovf));

	 timer_attach_interrupt(TIMER2, TIMER_CH1, TIM2_IRQHandler);

	 timer_generate_update(TIMER2);
	 //timer_resume(TIMER2);*/

	/*
	 * Timer Configuation for Dynamixel bus
	 * 2013-04-03 ROBOTIS Changed it as the below codes
	 * Dynamixel bus used timer 2(channel 1) to check timeout for receiving data from the bus.
	 * So, don't use time 2(channel 1) in other parts.
	 * */
	// Pause the timer while we're configuring it
	timer.pause();

	// Set up period
	timer.setPeriod(1); // in microseconds

	// Set up an interrupt on channel 1
	timer.setMode(TIMER_CH1,TIMER_OUTPUT_COMPARE);
	timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
	timer.attachInterrupt(TIMER_CH1,TIM2_IRQHandler);

	// Refresh the timer's count, prescale, and overflow
	timer.refresh();

	// Start the timer counting
	//timer.resume();
	 dxl_initialize(0, baud);
}

void Dynamixel::end(void){

	dxl_terminate();
}

void Dynamixel::ping(int id){
	dxl_ping( id );

}
void Dynamixel::reset(int id){
	dxl_reset( id );

}

void Dynamixel::setTxPacketId(int id){
	dxl_set_txpacket_id( id );
}
void Dynamixel::setTxPacketInstruction(int instruction){
	 dxl_set_txpacket_instruction( instruction );
}

void Dynamixel::writeByte(int id, int address, int value ) {

	dxl_write_byte( id, address, value );
}

void Dynamixel::writeWord(int id, int address, int value) {

	dxl_write_word( id, address, value );
}

int Dynamixel::readByte(int id, int address) {

	 return dxl_read_byte(  id, address );
}

int Dynamixel::readWord(int id, int address ) {
	 return dxl_read_word( id, address );

}
int Dynamixel::getResult(void) {
	 return dxl_get_result();

}
void Dynamixel::setPosition(int ServoID,int Position, int Speed){
	//Made by Martin S. Mason(Professor @Mt. San Antonio College)
	void setPosition(int ServoID, int Position, int Speed);
}
void Dynamixel::setTxPacketParameter( int index, int value ){
	dxl_set_txpacket_parameter( index, value );
}
void Dynamixel::setTxPacketLength( int length ){
	dxl_set_txpacket_length( length );
}

int Dynamixel::getRxPacketParameter( int index ){
	return dxl_get_rxpacket_parameter( index );
}
int Dynamixel::getRxPacketLength(void){
	return dxl_get_rxpacket_length();
}
int Dynamixel::getRxPacketError( int errbit ){
	return dxl_get_rxpacket_error( errbit );
}

////////// utility methods for value ////////////
int Dynamixel::makeWord( int lowbyte, int highbyte ){
	return dxl_makeword( lowbyte, highbyte );
}
int Dynamixel::getLowByte( int word ){
	return dxl_get_lowbyte( word );
}
int Dynamixel::getHighByte( int word ){
	return dxl_get_highbyte( word );
}

////////// packet communication methods ///////////////////////
void Dynamixel::txPacket(void){
	dxl_tx_packet();
}
void Dynamixel::rxPacket(void){
	dxl_rx_packet();
}
void Dynamixel::txrxPacket(void){
	dxl_txrx_packet();
}


