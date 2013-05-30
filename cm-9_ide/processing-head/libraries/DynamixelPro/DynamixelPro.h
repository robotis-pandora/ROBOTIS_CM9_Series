/*
 * DynamixelPro.h
 *
 *  Created on: 2013. 4. 25.
 *      Author: ROBOTIS,.LTD.
 */

#ifndef DYNAMIXELPRO_H_
#define DYNAMIXELPRO_H_


#include "libpandora_types.h"




class DynamixelPro {
private:
	byte mResult;
public:
	DynamixelPro();
	virtual ~DynamixelPro();


	/////////// Device control methods /////////////
	void begin(int buad);
	void end(void);  /**will be removed by ROBOTIS,.LTD. there maybe not be used...*/

	//// High communication methods ////////
	byte readByte(byte bID, int wAddress);
	word readWord(byte bID, int wAddress);
	byte writeByte(byte bID, int wAddress, byte bData);
	byte writeWord(byte bID, int bAddress, word wData);

	byte writeDword( byte bID, int wAddress, unsigned int value );

	/*
	     * [ROBOTIS][ADD][START] 2013-04-09 support read and write on dxl bus
	     * */
	void writeRaw(byte value);
	byte readRaw(void);
	byte available(void);
};


#endif /* DYNAMIXELPRO_H_ */
