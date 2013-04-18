/******************************************************************************
 * The ROBOTIS License
 *
 * Copyright (c) 2012 Sangmin Lee
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

/**
 *  @brief Dynamixel class.
 */

#ifndef _DYNAMIXEL_H_
#define _DYNAMIXEL_H_

#include "dxl_constants.h"

/**
 * @brief Interface of Dynimixel class
 * @Author : Sangmin Lee -> sm6787@robotis.com
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
