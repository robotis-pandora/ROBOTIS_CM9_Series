/*
 * OLLO.cpp
 *
 *  Created on: 2013. 5. 30.
 *      Author: ROBOTIS,.LTD.
 */

#include "OLLO.h"

#include "Arduino-compatibles.h"

OLLO::OLLO() {
	// TODO Auto-generated constructor stub

}

OLLO::~OLLO() {
	// TODO Auto-generated destructor stub
}

void OLLO::begin(int devNum){
	if( devNum == 0 || devNum > 4){
			return;
	}
	switch(devNum){
	case 1:
		pinMode(6, OUTPUT); //RED  (right)
		pinMode(7, OUTPUT); //BLUE (left)
		pinMode(2, INPUT_ANALOG); //ADC input
		break;
	case 2:
		pinMode(8, OUTPUT); //RED  (right)
		pinMode(9, OUTPUT); //BLUE (left)
		pinMode(3, INPUT_ANALOG);//ADC input
		break;
	case 3:
		pinMode(10, OUTPUT); //RED  (right)
		pinMode(11, OUTPUT); //BLUE (left)
		pinMode(0, INPUT_ANALOG);//ADC input
		break;
	case 4:
		pinMode(12, OUTPUT); //RED  (right)
		pinMode(13, OUTPUT); //BLUE (left)
		pinMode(1, INPUT_ANALOG);//ADC input
		break;
	default:
		break;
	}
}

int OLLO::read(int devNum){
	if( devNum == 0 || devNum > 4){
			return 0;
	}
	switch(devNum){
	case 1:
		return (int)analogRead(2);
	case 2:
		return (int)analogRead(3);
	case 3:
		return (int)analogRead(0);
	case 4:
		return (int)analogRead(1);
	default:
		return 0;
	}

}
void OLLO::beginIR(int devNum){
	if( devNum == 0 || devNum > 4){
			return;
	}
	switch(devNum){
	case 1:
		pinMode(2, INPUT_ANALOG); //ADC init
		pinMode(6, OUTPUT); //IR LOW
		pinMode(7, PWM); //IR PWM

		digitalWrite(6,LOW); //set to LOW
		analogWrite(7,40000);
		break;
	case 2:
		pinMode(3, INPUT_ANALOG); //ADC init
		pinMode(8, OUTPUT); //IR LOW
		pinMode(9, PWM); //IR PWM

		digitalWrite(8,LOW); //set to LOW
		analogWrite(9,40000);
		break;
	case 3:
		pinMode(0, INPUT_ANALOG); //ADC init
		pinMode(10, OUTPUT); //IR LOW
		pinMode(11, PWM); //IR PWM

		digitalWrite(10,LOW); //set to LOW
		analogWrite(11,40000);
		break;
	case 4:
		pinMode(1, INPUT_ANALOG); //ADC init
		pinMode(12, OUTPUT); //IR LOW
		pinMode(13, PWM); //IR PWM

		digitalWrite(12,LOW); //set to LOW
		analogWrite(13,40000);
		break;
	default:
		break;
	}

}

void OLLO::writeLED(int devNum,uint8 leftVal, uint8 rightVal ){
	if( leftVal >1 || rightVal >1 || devNum == 0 || devNum > 4){
		return;
	}

	switch(devNum){
		case 1:
			 digitalWrite(6,rightVal);
			 digitalWrite(7,leftVal);
			break;
		case 2:
			digitalWrite(8,rightVal);
			digitalWrite(9,leftVal);
			break;
		case 3:
			digitalWrite(10,rightVal);
			digitalWrite(11,leftVal);
			break;
		case 4:
			digitalWrite(12,rightVal);
			digitalWrite(13,leftVal);
			break;
		default:
			break;
		}

}
void OLLO::beginButton(int devNum, voidFuncPtr handler){
	if( devNum == 0 || devNum > 4){
		return;
	}
	switch(devNum){
		case 1:
			pinMode(2, INPUT_PULLUP);
			attachInterrupt(2,handler, RISING);
			break;
		case 2:
			pinMode(3, INPUT_PULLUP);
			attachInterrupt(3,handler, RISING);
			break;
		case 3:
			pinMode(0, INPUT_PULLUP);
			attachInterrupt(0,handler, RISING);
			break;
		case 4:
			pinMode(1, INPUT_PULLUP);
			attachInterrupt(1,handler, RISING);
			break;
		default:
			break;
		}
}

void OLLO::write(int devNum, uint8 leftVal, uint8 centerVal, uint8 rightVal){

	if( leftVal >1 || rightVal >1 || centerVal > 1 || devNum == 0 || devNum > 4){
		return;
	}

	switch(devNum){
		case 1:
			 digitalWrite(6,rightVal);
			 digitalWrite(2,centerVal);
			 digitalWrite(7,leftVal);
			break;
		case 2:
			digitalWrite(8,rightVal);
			digitalWrite(3,centerVal);
			digitalWrite(9,leftVal);
			break;
		case 3:
			digitalWrite(10,rightVal);
			digitalWrite(0,centerVal);
			digitalWrite(11,leftVal);
			break;
		case 4:
			digitalWrite(12,rightVal);
			digitalWrite(1,centerVal);
			digitalWrite(13,leftVal);
			break;
		default:
			break;
	}

}
