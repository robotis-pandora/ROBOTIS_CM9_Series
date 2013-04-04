/* Copyright (C) 2013 ROBOTIS, Co., Ltd.
 *
 * @File: Dynamixel.h
 * @Brief : Dynamixel class.
 * 
 */

#ifndef _DYNAMIXEL_H_
#define _DYNAMIXEL_H_

#include "dxl_constants.h"


/**
 * @brief Interface of Dynimixel class
 * @Author : ROBOTIS[sm6787@robotis.com]
 */
class Dynamixel {
private:


public:
    /**
     * @brief Construct a new Dynamixel instance.
     * @param -
     */
	Dynamixel(void);

	/////////// Device control methods /////////////
    void begin(int buad);
    void end(void);

    //// High communication methods ////////
    int readByte( int id, int address );
    void writeByte( int id, int address, int value );
    int readWord( int id, int address );
    void writeWord( int id, int address, int value );

    void ping(int id);
    void reset(int id);
    int getResult(void);
    void setPosition(int ServoID, int Position, int Speed);//Made by Martin S. Mason(Professor @Mt. San Antonio College)

    /////// Methods for making a packet ////////
    void setTxPacketId( int id );
    void setTxPacketInstruction( int instruction );
    void setTxPacketParameter( int index, int value );
    void setTxPacketLength( int length );
    int getRxPacketParameter( int index );
    int getRxPacketLength(void);
    int getRxPacketError( int errbit );

    ////////// utility methods for value ////////////
    int makeWord( int lowbyte, int highbyte );
    int getLowByte( int word );
    int getHighByte( int word );

    ////////// packet communication methods ///////////////////////
    void txPacket(void);
    void rxPacket(void);
    void txrxPacket(void);



};


extern Dynamixel Dxl;



#endif
