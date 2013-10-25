#ifndef _BOOTS_RPM_H_
#define _BOOTS_RPM_H_

#include "Boots_Sequences.h"

sequencer_t Boots_RoboPlusMotion_Array[] __FLASH__ = {
	{0,						0,		29},	// 0 (INVALID) (STOP)

	{Boots_Init, 			0,		0},		// 1

	{Boots_Forward_I_R, 	4,		6},		// 2
	{Boots_Forward_I_L,		5,		7},		// 3
	{Boots_Forward_R_L,		5,		7},		// 4
	{Boots_Forward_L_R,		4,		6},		// 5
	{Boots_Forward_R_I,		0,		0},		// 6
	{Boots_Forward_L_I,		0,		0},		// 7

	{Boots_Backward_I_R,	10,		12},	// 8
	{Boots_Backward_I_L,	11,		13},	// 9
	{Boots_Backward_R_L,	11,		13},	// 10
	{Boots_Backward_L_R,	10,		12},	// 11
	{Boots_Backward_R_I,	0,		0},		// 12
	{Boots_Backward_L_I,	0,		0},		// 13

	{Boots_SpinRight, 		0,		0},		// 14
	{Boots_SpinLeft, 		0,		0},		// 15
	{Boots_StrafeRight,		0,		0},		// 16
	{Boots_StrafeLeft, 		0,		0},		// 17

	{Boots_F_Shoot_R, 		0,		0},		// 18
	{Boots_F_Shoot_L, 		0,		0},		// 19
	{Boots_R_Shoot,			0,		0},		// 20
	{Boots_L_Shoot, 		0,		0},		// 21

	{Boots_Pass_R,			0,		0},		// 22
	{Boots_Pass_L,	 		0,		0},		// 23
	{Boots_B_Shoot_R, 		0,		0},		// 24
	{Boots_B_Shoot_L, 		0,		0},		// 25

	{Boots_D_Ready,			26,		1},		// 26
	{Boots_D_Right,	 		26,		0},		// 27
	{Boots_D_Front, 		26,		0},		// 28
	{Boots_D_Left,	 		26,		0}		// 29

};

#endif
