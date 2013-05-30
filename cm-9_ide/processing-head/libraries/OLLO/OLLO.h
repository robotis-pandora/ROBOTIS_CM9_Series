/*
 * OLLO.h
 *
 *  Created on: 2013. 5. 30.
 *      Author: ROBOTIS,.LTD.
 */

#ifndef OLLO_H_
#define OLLO_H_
#include "libpandora_types.h"

class OLLO {
public:
	OLLO();
	virtual ~OLLO();
	//General 3PIN sensors
	void begin(int devNum);
	int read(int devNum);
	void write(int devNum, uint8 leftVal, uint8 centerVal, uint8 rightVal);
	//IR Sensor Module
	void beginIR(int devNum);
	//LED Module
	void writeLED(int devNum,uint8 leftVal, uint8 rightVal );
	//Button Module
	void beginButton(int devNum,voidFuncPtr handler);

};

#endif /* OLLO_H_ */
