/*
 *******************************************************************************
 *  dynamixel_address_tables.h - 2012-11-13-1441
 *******************************************************************************
 *  A header file of questionable quality containing the address tables of
 *    several Dynamixel devices.  It should work with the AX-12/18, AX-S1,
 *    AX-S20, HaViMo2, Jon Hylands' FootPressureSensor kit, MX-28, IR Sensor 
 *    array, and CM-730.
 *  
 *******************************************************************************
 *  LEGAL STUFF
 *******************************************************************************
 *  
 *  Just to be safe:
 *   'AVR', 'ATmega' are property of Atmel, Inc.
 *      http://www.atmel.com
 *   'Dynamixel' is property of Robotis, Inc.
 *      http://www.robotis.com
 *  
 *  
 *  Copyright (c) 2011, 2012 Matthew Paulishen. All rights reserved.
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
 
#ifndef _DXL_ADDR_TABLE_H_
#define _DXL_ADDR_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
#ifndef BROADCAST_ID
#define BROADCAST_ID                    254
#endif

#ifndef INST_PING
#define INST_PING                       0x01
#endif
#ifndef INST_READ
#define INST_READ                       0x02
#endif
#ifndef INST_WRITE
#define INST_WRITE                      0x03
#endif
#ifndef INST_REG_WRITE
#define INST_REG_WRITE                  0x04
#endif
#ifndef INST_ACTION
#define INST_ACTION                     0x05
#endif
#ifndef INST_RESET
#define INST_RESET                      0x06
#endif
#ifndef INST_DIGITAL_RESET
#define INST_DIGITAL_RESET              0x07
#endif
#ifndef INST_SYSTEM_READ
#define INST_SYSTEM_READ                0x0C
#endif
#ifndef INST_SYSTEM_WRITE
#define INST_SYSTEM_WRITE               0x0D
#endif
#ifndef INST_SYNC_WRITE
#define INST_SYNC_WRITE                 0x83
#endif
#ifndef INST_SYNC_REG_WRITE
#define INST_SYNC_REG_WRITE             0x84
#endif

#ifndef ERRBIT_VOLTAGE
#define ERRBIT_VOLTAGE                  (1)
#endif
#ifndef ERRBIT_ANGLE
#define ERRBIT_ANGLE                    (2)
#endif
#ifndef ERRBIT_OVERHEAT
#define ERRBIT_OVERHEAT                 (4)
#endif
#ifndef ERRBIT_RANGE
#define ERRBIT_RANGE                    (8)
#endif
#ifndef ERRBIT_CHECKSUM
#define ERRBIT_CHECKSUM                 (16)
#endif
#ifndef ERRBIT_OVERLOAD
#define ERRBIT_OVERLOAD                 (32)
#endif
#ifndef ERRBIT_INSTRUCTION
#define ERRBIT_INSTRUCTION              (64)
#endif

#ifndef MAXNUM_RXPARAM
#define MAXNUM_RXPARAM                  (60)
#endif
#ifndef MAXNUM_TXPARAM
#define MAXNUM_TXPARAM                  (150)
#endif


#ifndef COMM_TXSUCCESS
#define	COMM_TXSUCCESS                  (0)
#endif
#ifndef COMM_RXSUCCESS
#define COMM_RXSUCCESS                  (1)
#endif
#ifndef COMM_TXFAIL
#define COMM_TXFAIL                     (2)
#endif
#ifndef COMM_RXFAIL
#define COMM_RXFAIL                     (3)
#endif
#ifndef COMM_TXERROR
#define COMM_TXERROR                    (4)
#endif
#ifndef COMM_RXWAITING
#define COMM_RXWAITING                  (5)
#endif
#ifndef COMM_RXTIMEOUT
#define COMM_RXTIMEOUT                  (6)
#endif
#ifndef COMM_RXCORRUPT
#define COMM_RXCORRUPT                  (7)
#endif

*/

// Instruction Packet (Command Packet)
// 0xFF -> 0xFF -> ID -> LENGTH -> INSTRUCTION -> PARAM_1 -> PARAM_2 -> PARAM_N -> CHECKSUM
// LENGTH = ( 1 {ID Byte} + 1 {INSTRUCTION Byte} + N {Number of PARAMETER Bytes} )
// CHECKSUM = ( ~(ID + LENGTH + INSTRUCTION + PARAM_1 +...+ PARAM_N) ) & (0x00FF)

// Status Packet (Return Packet)
// 0xFF -> 0xFF -> ID -> LENGTH -> ERROR -> PARAM_1 -> PARAM_2 -> PARAM_N -> CHECKSUM
// LENGTH = ( 1 {ID Byte} + 1 {ERROR Byte} + N {Number of PARAMETER Bytes} )
// CHECKSUM = ( ~(ID + LENGTH + ERROR + PARAM_1 +...+ PARAM_N) ) & (0x00FF)

/*
// Dynamixel Packet byte array offsets
enum{
    DXL_PKT_ID                        = 0x02,
    // Offset to ID byte of packet

    DXL_PKT_LEN                       = 0x03,
    // Offset to Length byte of packet

    DXL_PKT_INST                      = 0x04,
    // Offset to Instruction byte of command packet

    DXL_PKT_ERR                       = 0x04,
    // Offset to Error byte of return packet

    DXL_PKT_PARA                      = 0x05
    // Offset to first Parameter byte of packet
};



// Instruction set
    // PARAMETERS // TASK
enum{
    INST_PING                         = 0x01,
    // 0        Get status packet

    INST_READ_DATA                    = 0x02,
    // 2        Read value from device Control Table

    INST_WRITE_DATA                   = 0x03,
    // 2~       Write value into device Control Table

    INST_REG_WRITE                    = 0x04,
    // 2~       Write value in standby mode (wait for REG_WRITE)

    INST_ACTION                       = 0x05,
    // 0        Execute REG_WRITE

    INST_RESET                        = 0x06,
    // 0        Set all Control Table values to default?

    INST_DIGITAL_RESET                = 0x07,
    // ?        From HaViMo2 - Embedded-C example

    INST_SYSTEM_READ                  = 0x0C,
    // ?        From HaViMo2 - Embedded-C example

    INST_SYSTEM_WRITE                 = 0x0D,
    // ?        From HaViMo2 - Embedded-C example

    INST_CAP_REGION                   = 0x0E,
    // 0        From HaViMo2 datasheet
    //          Initiates new image capture and processing
    //          No return packet generated and non-responsive during processing

    INST_RAW_SAMPLE                   = 0x0F,
    // 0        From HaViMo2 datasheet
    //          Sample the Raw Image (used by GUI)
    //          Response does not follow standard RoboPlust packet

    INST_LUT_MANAGE                   = 0x10,
    // 0        From HaViMo2 datasheet
    //          Enter LUT manage mode (used by GUI) (FOR CALIBRATION ONLY.
    //          NOT RECOMMENDED FOR USE WITH ANY BEHAVIOR/ALGORITHM IMPLEMENTATION)

    INST_RD_FILTHR                    = 0x11,
    // 2        From HaViMo2 datasheet
    //          Read noise threshold value (see datasheet for more detail)

    INST_WR_FILTHR                    = 0x12,
    // 2        From HaViMo2 datasheet
    //          Write noise threshold value (see datasheet for more detail)

    INST_RD_REGTHR                    = 0x13,
    // 2        From HaViMo2 datasheet
    //          Read region threshold value (see datasheet for more detail)

    INST_WR_REGTHR                    = 0x14,
    // 2        From HaViMo2 datasheet
    //          Write region threshold value (see datasheet for more detail)

    INST_CAP_GRID                     = 0x15,
    // 0        From HaViMo2 datasheet
    //          Invokes gridding algorithm (compresses image to 32*24 cells.
    //          Each cell given only one object index with lower indices dominating
    //          higher ['Ball==1' > 'Field==2' > .. > 'Unknown==0'].
    //          Each cell contains the number of pixels of the specified index.

    INST_READ_GRID                    = 0x16,
    // 2        From HaViMo2 datasheet
    //          Retrieve results of the gridded image (address internally
    //          multiplied by 16, so retrieve 16 bytes at a time to recover
    //          the entire image.  bits 0-3 are color index, 4-7 are pixel
    //          [15 is the maximum reported, but may be more]
    //          Why not bits 0-2 [0,7] for index and bits 3-7 [0,32] for pixels?
    //          Don't know, so don't ask.

    INST_SAMPLE_FAST                  = 0x17,
    // 0        From HaViMo2 datasheet
    //          Download an entire image from the module at 1Mbps

    INST_SYNC_WRITE                   = 0x83,
    // 4+       Write value to Control Table of multiple dynamixels

    INST_SYNC_REG_WRITE               = 0x84,
    // ?        Write value to Control Table of multiple dynamixels
    //            in a standby mode?  From HaViMo2 - Embedded-C example?

    INST_BULK_READ                    = 0x92,
    // ?        Added to CM-730 in version v1.2.0 of the Darwin Framework

    INST_SYNC_READ                    = 0xD0
    // 2        Issues an INST_READ_DATA command for each servo in ID
    //            location and length of all reads same
};



// Error bits of Status Packet's ERROR byte
enum{
    ERRBIT_INSTRUCTION                = 0x40,
    // Set to 1 if undefined instruction or register is without REG_WRITE

    ERRBIT_OVERLOAD                   = 0x20,
    // Set to 1 if specified max torque cannot handle load

    ERRBIT_CHECKSUM                   = 0x10,
    // Set to 1 if checksum of packet is incorrect

    ERRBIT_RANGE                      = 0x08,
    // Set to 1 if the instruction sent is out of range

    ERRBIT_OVERHEAT                   = 0x04,
    // Set to 1 if the module temp is above operating temp defined in control table

    ERRBIT_ANGLE                      = 0x02,
    // Set to 1 if the Goal position is set out of range

    ERRBIT_VOLTAGE                    = 0x01
    // Set to 1 if the input voltage is out of range
};



// Expanded Dynamixel SDK TX/RX Error code bits
enum{
    DXL_TXSUCCESS                     = 0x0001,
    DXL_RXSUCCESS                     = 0x0002,
    DXL_TXFAIL                        = 0x0004,
    DXL_RXFAIL                        = 0x0008,
    DXL_TXERROR                       = 0x0010,
    DXL_BAD_INST                      = 0x0020,
    DXL_BAD_ID                        = 0x0040,
    DXL_NULL_DATA                     = 0x0080,
    DXL_NULL_SIZE                     = 0x0100,
    DXL_RXWAITING                     = 0x0200,
    DXL_RXTIMEOUT                     = 0x0400,
    DXL_RXLENGTH                      = 0x0800,
    DXL_RXCHECKSUM                    = 0x1000
};

*/

// Default model numbers
#define MODEL_AX12                      12
#define MODEL_AX12W                     300
#define MODEL_AX18                      18
#define MODEL_AXS1                      13
#define MODEL_AXS20                     212
#define MODEL_JHFPS                     17163	// 0x6711
#define MODEL_HaViMo2                   0
//#define MODEL_CM730                     ?
#define MODEL_MX28                      29
#define MODEL_IRSA                      330     // 0x014A



// Universal address table
#define P_MODEL_NUMBER_L                0
#define P_MODEL_NUMBER_H                1
#define P_FIRMWARE_VERSION              2
#define P_ID                            3
#define P_BAUD_RATE                     4
#define P_RETURN_DELAY_TIME             5
#define P_STATUS_RETURN_LEVEL           16
//#define P_LED                           25  // AX-12+, AX-18F, and AX-S20
//#define P_REGISTERED_INSTRUCTION        44



// Robotis' IR Sensor Array
enum{
    IRSA_MODEL_NUMBER_L               = 0,
    IRSA_MODEL_NUMBER_H               = 1,
    IRSA_FIRMWARE_VERSION             = 2,
    IRSA_ID                           = 3,
    IRSA_BAUD_RATE                    = 4,
    IRSA_RETURN_DELAY_TIME            = 5,
    IRSA_ETH_L_1                      = 6,
    IRSA_ETH_H_1                      = 7,
    IRSA_ETH_L_2                      = 8,
    IRSA_ETH_H_2                      = 9,
    IRSA_ETH_L_3                      = 10,
    IRSA_ETH_H_3                      = 11,
    IRSA_ETH_L_4                      = 12,
    IRSA_ETH_H_4                      = 13,
    IRSA_ETH_L_5                      = 14,
    IRSA_ETH_H_5                      = 15,
    IRSA_STATUS_RETURN_LEVEL          = 16,
    IRSA_ETH_L_6                      = 17,
    IRSA_ETH_H_6                      = 18,
    IRSA_ETH_L_7                      = 20,
    IRSA_ETH_H_7                      = 21,
    IRSA_FD_L_1                       = 24,
    IRSA_FD_H_1                       = 25,
    IRSA_FD_L_2                       = 26,
    IRSA_FD_H_2                       = 27,
    IRSA_FD_L_3                       = 28,
    IRSA_FD_H_3                       = 29,
    IRSA_FD_L_4                       = 30,
    IRSA_FD_H_4                       = 31,
    IRSA_FD_L_5                       = 32,
    IRSA_FD_H_5                       = 33,
    IRSA_FD_L_6                       = 34,
    IRSA_FD_H_6                       = 35,
    IRSA_FD_L_7                       = 36,
    IRSA_FD_H_7                       = 37,
    IRSA_BUZZ_NOTE                    = 40,
    IRSA_BUZZ_TIME                    = 41,
    IRSA_AUTO_TH                      = 42,
    IRSA_OBS_DET                      = 43,
    IRSA_REGISTERED_INSTRUCTION       = 44,
    IRSA_LOCK                         = 47,
    IRSA_TH_L_1                       = 48,
    IRSA_TH_H_1                       = 49,
    IRSA_TH_L_2                       = 50,
    IRSA_TH_H_2                       = 51,
    IRSA_TH_L_3                       = 52,
    IRSA_TH_H_3                       = 53,
    IRSA_TH_L_4                       = 54,
    IRSA_TH_H_4                       = 55,
    IRSA_TH_L_5                       = 56,
    IRSA_TH_H_5                       = 57,
    IRSA_TH_L_6                       = 58,
    IRSA_TH_H_6                       = 59,
    IRSA_TH_L_7                       = 60,
    IRSA_TH_H_7                       = 61
};

// John Hyland's FSR FOOT PRESSURE SENSOR BOARD
enum{
    JHFPS_MODEL_NUMBER_L              = 0,
    JHFPS_MODEL_NUMBER_H              = 1,
    JHFPS_FIRMWARE_VERSION            = 2,
    JHFPS_ID                          = 3,
    JHFPS_BAUD_RATE                   = 4,
    JHFPS_RETURN_DELAY_TIME           = 5,
    JHFPS_STATUS_RETURN_LEVEL         = 16,
    JHFPS_LED                         = 25,
    JHFPS_FRONT_INSIDE_L              = 26,
    JHFPS_FRONT_INSIDE_H              = 27,
    JHFPS_FRONT_OUTSIDE_L             = 28,
    JHFPS_FRONT_OUTSIDE_H             = 29,
    JHFPS_REAR_INSIDE_L               = 30,
    JHFPS_REAR_INSIDE_H               = 31,
    JHFPS_REAR_OUTSIDE_L              = 32,
    JHFPS_REAR_OUTSIDE_H              = 33
};

#include <HaViMo2.h>
/*
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
*/

// AX-12+/18F address table
enum{
    AXM_MODEL_NUMBER_L                = 0,
    AXM_MODEL_NUMBER_H                = 1,
    AXM_FIRMWARE_VERSION              = 2,
    AXM_ID                            = 3,
    AXM_BAUD_RATE                     = 4,
    AXM_RETURN_DELAY_TIME             = 5,
    AXM_CW_ANGLE_LIMIT_L              = 6,
    AXM_CW_ANGLE_LIMIT_H              = 7,
    AXM_CCW_ANGLE_LIMIT_L             = 8,
    AXM_CCW_ANGLE_LIMIT_H             = 9,
    AXM_SYSTEM_DATA2                  = 10,
    AXM_HIGHEST_LIMIT_TEMPERATURE     = 11,
    AXM_LOWEST_LIMIT_VOLTAGE          = 12,
    AXM_HIGHEST_LIMIT_VOLTAGE         = 13,
    AXM_MAX_TORQUE_L                  = 14,
    AXM_MAX_TORQUE_H                  = 15,
    AXM_STATUS_RETURN_LEVEL           = 16,
    AXM_ALARM_LED                     = 17,
    AXM_ALARM_SHUTDOWN                = 18,
    AXM_OPERATING_MODE                = 19,
    AXM_DOWN_CALIBRATION_L            = 20,
    AXM_DOWN_CALIBRATION_H            = 21,
    AXM_UP_CALIBRATION_L              = 22,
    AXM_UP_CALIBRATION_H              = 23,
    AXM_TORQUE_ENABLE                 = 24,
    AXM_LED                           = 25,
    AXM_CW_COMPLIANCE_MARGIN          = 26,
    AXM_CCW_COMPLIANCE_MARGIN         = 27,
    AXM_CW_COMPLIANCE_SLOPE           = 28,
    AXM_CCW_COMPLIANCE_SLOPE          = 29,
    AXM_GOAL_POSITION_L               = 30,
    AXM_GOAL_POSITION_H               = 31,
    AXM_MOVING_SPEED_L                = 32,
    AXM_MOVING_SPEED_H                = 33,
    AXM_TORQUE_LIMIT_L                = 34,
    AXM_TORQUE_LIMIT_H                = 35,
    AXM_PRESENT_POSITION_L            = 36,
    AXM_PRESENT_POSITION_H            = 37,
    AXM_PRESENT_SPEED_L               = 38,
    AXM_PRESENT_SPEED_H               = 39,
    AXM_PRESENT_LOAD_L                = 40,
    AXM_PRESENT_LOAD_H                = 41,
    AXM_PRESENT_VOLTAGE               = 42,
    AXM_PRESENT_TEMPERATURE           = 43,
    AXM_REGISTERED_INSTRUCTION        = 44,
    AXM_PAUSE_TIME                    = 45,
    AXM_MOVING                        = 46,
    AXM_LOCK                          = 47,
    AXM_PUNCH_L                       = 48,
    AXM_PUNCH_H                       = 49
};


// AX-S1 Address table
enum{
    AXS1_MODEL_NUMBER_L               = 0,
    AXS1_MODEL_NUMBER_H               = 1,
    AXS1_FIRMWARE_VERSION             = 2,
    AXS1_ID                           = 3,
    AXS1_BAUD_RATE                    = 4,
    AXS1_RETURN_DELAY_TIME            = 5,
    AXS1_STATUS_RETURN_LEVEL          = 16,
    AXS1_IR_LEFT                      = 26,
    AXS1_IR_CENTER                    = 27,
    AXS1_IR_RIGHT                     = 28,
    AXS1_LUMINOSITY_LEFT              = 29,
    AXS1_LUMINOSITY_CENTER            = 30,
    AXS1_LUMINOSITY_RIGHT             = 31,
    AXS1_IR_OBSTACLE_DETECTED         = 32,
    AXS1_LUMINOSITY_DETECTED          = 33,
    AXS1_SOUND_DATA                   = 35,
    AXS1_SOUND_DATA_MAX_HOLD          = 36,
    AXS1_SOUND_DETECT_COUNT           = 37,
    AXS1_SOUND_DETECT_TIME_L          = 38,
    AXS1_SOUND_DETECT_TIME_H          = 39,
    AXS1_BUZZER_INDEX                 = 40,
    AXS1_BUZZER_TIME                  = 41,
    AXS1_IR_REMOCON_ARRIVED           = 46,
    AXS1_IR_REMOCON_RX_DATA_L         = 48,
    AXS1_IR_REMOCON_RX_DATA_H         = 49,
    AXS1_IR_REMOCON_TX_DATA_L         = 50,
    AXS1_IR_REMOCON_TX_DATA_H         = 51,
    AXS1_OBSTACLE_DETECTED_COMPARE    = 52,
    AXS1_LIGHT_DETECTED_COMPARE       = 53
};


// AX-S20 address table
enum{
    AXS20_MODEL_NUMBER_L              = 0,
    AXS20_MODEL_NUMBER_H              = 1,
    AXS20_FIRMWARE_VERSION            = 2,
    AXS20_ID                          = 3,
    AXS20_BAUD_RATE                   = 4,
    AXS20_RETURN_DELAY_TIME           = 5,
    AXS20_STATUS_RETURN_LEVEL         = 16,
    AXS20_LED                         = 25, // AX-12+, AX-18F, and AX-S20
    AXS20_AZIMUTH_Z_L                 = 26, // 0-360 degrees            +CW from top/-CCW from top
    AXS20_AZIMUTH_Z_H                 = 27,
    AXS20_PITCH_Y_L                   = 28, // -90-90 degrees [word]    +forward/-backward
    AXS20_PITCH_Y_H                   = 29,
    AXS20_ROLL_X_L                    = 30, // -90-90 degrees [word]    +left/-right
    AXS20_ROLL_X_H                    = 31,
    AXS20_MAGNETO_Z_L                 = 32, // raw magneto flux density
    AXS20_MAGNETO_Z_H                 = 33,
    AXS20_MAGNETO_X_L                 = 34, // raw magneto flux density
    AXS20_MAGNETO_X_H                 = 35,
    AXS20_MAGNETO_Y_L                 = 36, // raw magneto flux density
    AXS20_MAGNETO_Y_H                 = 37,
    AXS20_ACCEL_X_L                   = 38, // -2048~2048               +forward/-backward
    AXS20_ACCEL_X_H                   = 39,
    AXS20_ACCEL_Y_L                   = 40, // -2048~2048               +left/-right
    AXS20_ACCEL_Y_H                   = 41,
    AXS20_ACCEL_Z_L                   = 46, // -2048~2048               +up/-down
    AXS20_ACCEL_Z_H                   = 47,
    AXS20_ACCEL_PITCH_Y               = 48, // -90~90 degrees [byte] from accelerometer
    AXS20_ACCEL_ROLL_X                = 49  // -90~90 degrees [byte] from accelerometer

};


// MX-28 address table
#ifdef MX28_1024
enum{
    MX_MODEL_NUMBER_L                 = 0,
    MX28_MODEL_NUMBER_H               = 1,
    MX28_VERSION                      = 2,
    MX28_ID                           = 3,
    MX28_BAUD_RATE                    = 4,
    MX28_RETURN_DELAY_TIME            = 5,
    MX28_CW_ANGLE_LIMIT_L             = 6,
    MX28_CW_ANGLE_LIMIT_H             = 7,
    MX28_CCW_ANGLE_LIMIT_L            = 8,
    MX28_CCW_ANGLE_LIMIT_H            = 9,
    MX28_HIGH_LIMIT_TEMPERATURE       = 11,
    MX28_LOW_LIMIT_VOLTAGE            = 12,
    MX28_HIGH_LIMIT_VOLTAGE           = 13,
    MX28_MAX_TORQUE_L                 = 14,
    MX28_MAX_TORQUE_H                 = 15,
    MX28_RETURN_LEVEL                 = 16,
    MX28_ALARM_LED                    = 17,
    MX28_ALARM_SHUTDOWN               = 18,
    MX28_TORQUE_ENABLE                = 24,
    MX28_LED                          = 25,
    MX28_CW_COMPLIANCE_MARGIN         = 26,
    MX28_CCW_COMPLIANCE_MARGIN        = 27,
    MX28_CW_COMPLIANCE_SLOPE          = 28,
    MX28_CCW_COMPLIANCE_SLOPE         = 29,
    MX28_GOAL_POSITION_L              = 30,
    MX28_GOAL_POSITION_H              = 31,
    MX28_MOVING_SPEED_L               = 32,
    MX28_MOVING_SPEED_H               = 33,
    MX28_TORQUE_LIMIT_L               = 34,
    MX28_TORQUE_LIMIT_H               = 35,
    MX28_PRESENT_POSITION_L           = 36,
    MX28_PRESENT_POSITION_H           = 37,
    MX28_PRESENT_SPEED_L              = 38,
    MX28_PRESENT_SPEED_H              = 39,
    MX28_PRESENT_LOAD_L               = 40,
    MX28_PRESENT_LOAD_H               = 41,
    MX28_PRESENT_VOLTAGE              = 42,
    MX28_PRESENT_TEMPERATURE          = 43,
    MX28_REGISTERED_INSTRUCTION       = 44,
    MX28_MOVING                       = 46,
    MX28_LOCK                         = 47,
    MX28_PUNCH_L                      = 48,
    MX28_PUNCH_H                      = 49
};
#else
enum{
    MX28_MODEL_NUMBER_L               = 0,
    MX28_MODEL_NUMBER_H               = 1,
    MX28_VERSION                      = 2,
    MX28_ID                           = 3,
    MX28_BAUD_RATE                    = 4,
    MX28_RETURN_DELAY_TIME            = 5,
    MX28_CW_ANGLE_LIMIT_L             = 6,
    MX28_CW_ANGLE_LIMIT_H             = 7,
    MX28_CCW_ANGLE_LIMIT_L            = 8,
    MX28_CCW_ANGLE_LIMIT_H            = 9,
    MX28_SYSTEM_DATA2                 = 10,
    MX28_HIGH_LIMIT_TEMPERATURE       = 11,
    MX28_LOW_LIMIT_VOLTAGE            = 12,
    MX28_HIGH_LIMIT_VOLTAGE           = 13,
    MX28_MAX_TORQUE_L                 = 14,
    MX28_MAX_TORQUE_H                 = 15,
    MX28_RETURN_LEVEL                 = 16,
    MX28_ALARM_LED                    = 17,
    MX28_ALARM_SHUTDOWN               = 18,
    MX28_OPERATING_MODE               = 19,
    MX28_LOW_CALIBRATION_L            = 20,
    MX28_LOW_CALIBRATION_H            = 21,
    MX28_HIGH_CALIBRATION_L           = 22,
    MX28_HIGH_CALIBRATION_H           = 23,
    MX28_TORQUE_ENABLE                = 24,
    MX28_LED                          = 25,
    MX28_P_GAIN                       = 26,
    MX28_I_GAIN                       = 27,
    MX28_D_GAIN                       = 28,
    MX28_RESERVED                     = 29,
    MX28_GOAL_POSITION_L              = 30,
    MX28_GOAL_POSITION_H              = 31,
    MX28_MOVING_SPEED_L               = 32,
    MX28_MOVING_SPEED_H               = 33,
    MX28_TORQUE_LIMIT_L               = 34,
    MX28_TORQUE_LIMIT_H               = 35,
    MX28_PRESENT_POSITION_L           = 36,
    MX28_PRESENT_POSITION_H           = 37,
    MX28_PRESENT_SPEED_L              = 38,
    MX28_PRESENT_SPEED_H              = 39,
    MX28_PRESENT_LOAD_L               = 40,
    MX28_PRESENT_LOAD_H               = 41,
    MX28_PRESENT_VOLTAGE              = 42,
    MX28_PRESENT_TEMPERATURE          = 43,
    MX28_REGISTERED_INSTRUCTION       = 44,
    MX28_PAUSE_TIME                   = 45,
    MX28_MOVING                       = 46,
    MX28_LOCK                         = 47,
    MX28_PUNCH_L                      = 48,
    MX28_PUNCH_H                      = 49,
    MX28_RESERVED4                    = 50,
    MX28_RESERVED5                    = 51,
    MX28_POT_L                        = 52,
    MX28_POT_H                        = 53,
    MX28_PWM_OUT_L                    = 54,
    MX28_PWM_OUT_H                    = 55,
    MX28_P_ERROR_L                    = 56,
    MX28_P_ERROR_H                    = 57,
    MX28_I_ERROR_L                    = 58,
    MX28_I_ERROR_H                    = 59,
    MX28_D_ERROR_L                    = 60,
    MX28_D_ERROR_H                    = 61,
    MX28_P_ERROR_OUT_L                = 62,
    MX28_P_ERROR_OUT_H                = 63,
    MX28_I_ERROR_OUT_L                = 64,
    MX28_I_ERROR_OUT_H                = 65,
    MX28_D_ERROR_OUT_L                = 66,
    MX28_D_ERROR_OUT_H                = 67
};
#endif


// CM-730 address table
enum{
    CM730_MODEL_NUMBER_L              = 0,
    CM730_MODEL_NUMBER_H              = 1,
    CM730_FIRMWARE_VERSION            = 2,
    CM730_ID                          = 3,
    CM730_BAUD_RATE                   = 4,
    CM730_RETURN_DELAY_TIME           = 5,
    CM730_STATUS_RETURN_LEVEL         = 16,
    CM730_DXL_POWER                   = 24,
    CM730_LED_PANEL                   = 25,
    CM730_LED_HEAD_L                  = 26,
    CM730_LED_HEAD_H                  = 27,
    CM730_LED_EYE_L                   = 28,
    CM730_LED_EYE_H                   = 29,
    CM730_BUTTON                      = 30,
    CM730_GYRO_Z_L                    = 38,
    CM730_GYRO_Z_H                    = 39,
    CM730_GYRO_Y_L                    = 40,
    CM730_GYRO_Y_H                    = 41,
    CM730_GYRO_X_L                    = 42,
    CM730_GYRO_X_H                    = 43,
    CM730_ACCEL_X_L                   = 44,
    CM730_ACCEL_X_H                   = 45,
    CM730_ACCEL_Y_L                   = 46,
    CM730_ACCEL_Y_H                   = 47,
    CM730_ACCEL_Z_L                   = 48,
    CM730_ACCEL_Z_H                   = 49,
    CM730_VOLTAGE                     = 50,
    CM730_LEFT_MIC_L                  = 51,
    CM730_LEFT_MIC_H                  = 52,
    CM730_ADC2_L                      = 53,
    CM730_ADC2_H                      = 54,
    CM730_ADC3_L                      = 55,
    CM730_ADC3_H                      = 56,
    CM730_ADC4_L                      = 57,
    CM730_ADC4_H                      = 58,
    CM730_ADC5_L                      = 59,
    CM730_ADC5_H                      = 60,
    CM730_ADC6_L                      = 61,
    CM730_ADC6_H                      = 62,
    CM730_ADC7_L                      = 63,
    CM730_ADC7_H                      = 64,
    CM730_ADC8_L                      = 65,
    CM730_ADC8_H                      = 66,
    CM730_RIGHT_MIC_L                 = 67,
    CM730_RIGHT_MIC_H                 = 68,
    CM730_ADC10_L                     = 69,
    CM730_ADC10_H                     = 70,
    CM730_ADC11_L                     = 71,
    CM730_ADC11_H                     = 72,
    CM730_ADC12_L                     = 73,
    CM730_ADC12_H                     = 74,
    CM730_ADC13_L                     = 75,
    CM730_ADC13_H                     = 76,
    CM730_ADC14_L                     = 77,
    CM730_ADC14_H                     = 78,
    CM730_ADC15_L                     = 79,
    CM730_ADC15_H                     = 80
};

#ifdef __cplusplus
}
#endif



#endif
