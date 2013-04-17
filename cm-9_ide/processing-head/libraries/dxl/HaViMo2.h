/*
 *******************************************************************************
 *  HaViMo2.h - 2013-04-17
 *******************************************************************************
 *  A header file of questionable quality for using the HaViMo2
 *  
 *******************************************************************************
 *  LEGAL STUFF
 *******************************************************************************
 *  
 *   'Dynamixel' is property of Robotis, Inc.
 *      http://www.robotis.com
 *  
 *  Copyright (c) 2011, 2012, 2013 Matthew Paulishen. All rights reserved.
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 *******************************************************************************
 */
 
#ifndef _HAVIMO2_H_
#define _HAVIMO2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "Dynamixel.h"

// HaViMo2
#define HaViMo2_ID                      100
typedef enum {
    Unknown                           = 0,
    Black                             = 0,
    Ball                              = 1,
    Teal                              = 1,
    Field                             = 2,
    Red                               = 2,
    MyGoal                            = 3,
    Green                             = 3,
    OppGoal                           = 4,
    Purple                            = 4,
    Robot                             = 5,
    White                             = 5,
    Cyan                              = 6,
    Magenta                           = 7
} HaViMo2_Color_t;

typedef struct {
    uint8_t     Index, Color;
    uint16_t    NumPix;
    uint32_t    SumX, SumY;
    uint8_t     MaxX, MinX, MaxY, MinY;
} HaViMo2_Region_t;

typedef struct {
    uint8_t             valid;
    HaViMo2_Region_t    rb[15];
} HaViMo2_Region_Buffer_t;


/**
 * Wrapper function to begin an image capture with the HaViMo2 camera module.
 * @param id HaViMo2 camera ID (fixed as 100 in HaViMo2 firmware).
 * @see dxl_recover() and havGet()
 */
void havCap(uint8_t id);
/**
 * Wrapper function to retrieve an image buffer from a HaViMo2 camera module.
 * @param id HaViMo2 camera ID (fixed as 100 in HaViMo2 firmware).
 * @param hvm2rb Pointer to a user region buffer data type.
 * @see havCap()
 * @return The number of valid regions found in the image.
 */
uint8_t havGet(uint8_t id, HaViMo2_Region_Buffer_t* hvm2rb);


#ifdef __cplusplus
}
#endif

#endif
