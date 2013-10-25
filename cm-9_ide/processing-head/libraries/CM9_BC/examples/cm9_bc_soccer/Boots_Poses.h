#ifndef _BOOTS_POSES_H_
#define _BOOTS_POSES_H_

#include <CM9_BC.h>

/*
	Init		- Ready position
Walking Forward
	Forward_I_R		- Forward Start from Init on Right foot
						-> transitions to Forward_R_L
						-> quits with Forward_R_I
	Forward_I_L		- Forward Start from Init on Left foot
						-> transitions to Forward_L_R
						-> quits with Forward_L_I
	Forward_R_L		- Forward Right to Left step
						-> transitions to Forward_L_R
						-> quits with Forward_L_I
	Forward_L_R		- Forward Left to Right step
						-> transitions to Forward_R_L
						-> quits with Forward_R_I
	Forward_R_I		- Forward End from Right foot to Init
	Forward_L_I		- Forward End from Left foot to Init

Walking Backward
	Backward_I_R	- Backward Start from Init on Right foot
						-> transitions to Backward_R_L
						-> quits with Backward_R_I
	Backward_I_L	- Backward Start from Init on Left foot
						-> transitions to Backward_L_R
						-> quits with Backward_L_I
	Backward_R_L	- Backward Right to Left step
						-> transitions to Backward_L_R
						-> quits with Backward_L_I
	Backward_L_R	- Backward Left to Right step
 	 					-> transitions to Backward_R_L
 	 					-> quits with Backward_R_I
	Backward_R_I	- Backward End from Right foot to Init
	Backward_L_I	- Backward End from Left foot to Init

Maneuvering
	SpinRight		- Turn-in-place Right
	SpinLeft		- Turn-in-place Left
	StrafeRight		- Sidestep Right
	StrafeLeft		- Sidestep Left

Soccer moves
	F_Shoot_R		- Forward Kick with Right foot
	F_Shoot_L		- Forward Kick with Left foot
	R_Shoot			- Side Kick with Right foot
	L_Shoot			- Side Kick with Left foot
	Pass_R			- Pass left with Right foot
	Pass_L			- Pass right with Left foot
	B_Shoot_R		- Backward Kick with Right foot
	B_Shoot_L		- Backward Kick with Left foot
	D_Ready			- Defense Ready position
						-> transitions to D_Ready
						-> quits with Init
	D_Right			- Defend Right
						-> transitions to D_Ready
	D_Front			- Defend Center
						-> transitions to D_Ready
	D_Left			- Defend Left
						-> transitions to D_Ready

Uncertain and Unused
	FRT_R_M			- ForwardRightTurn_Right_Mid?
						-> transitions to FRT_R_M
						-> quits with Forward_L_R -> Forward_R_I
	FRT_L_M			- ForwardLeftTurn_Left_Mid?
						-> transitions to FLT_L_M
						-> quits with Forward_R_L -> Forward_L_I

	RFT				- Right_Forward_Turn?
	LFT				- Left_Forward_Turn?
	RBT				- Right_Backward_Turn?
	LBT				- Left_Backward_Turn?
	Fst_R			- Fast Right Turn?
	Fst_L			- Fast Left Turn?

Incomplete (only part of sequence retained by script because of unnamed page)
	F_PShoot_R		- Forward Step then Shoot with Right foot
	F_PShoot_L		- Forward Step then Shoot with Left foot
	Bravo			- Only useful for bot with arms
	Rap chest		- Again only useful for bot with arms

*/

unsigned int Boots_id[] __FLASH__ = {12,7,8,9,10,11,12,13,14,15,16,17,18};


int Boots_Calibration[] __FLASH__ = {12,0,0,0,0,0,0,0,0,0,0,0,0};


// Sequence: Init
unsigned int Boots_Init_1[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:1.000


// Sequence: Forward_I_R
unsigned int Boots_Forward_I_R_1[] __FLASH__ = {12,358,666,507,516,291,732,160,863,687,336,457,486};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_I_R_2[] __FLASH__ = {12,358,666,487,526,271,722,60,843,737,326,477,496};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_I_R_3[] __FLASH__ = {12,358,666,507,516,271,712,160,863,672,306,507,516};	//wait:0.000	//move:0.096


// Sequence: Forward_I_L
unsigned int Boots_Forward_I_L_1[] __FLASH__ = {12,358,666,507,516,301,722,160,863,687,336,537,566};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_I_L_2[] __FLASH__ = {12,357,665,497,536,301,752,160,963,687,286,527,546};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_I_L_3[] __FLASH__ = {12,358,666,507,516,311,752,160,863,717,351,507,516};	//wait:0.000	//move:0.096


// Sequence: Forward_R_L
unsigned int Boots_Forward_R_L_1[] __FLASH__ = {12,357,665,507,516,261,682,160,863,647,296,527,536};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_R_L_2[] __FLASH__ = {12,357,665,497,536,301,802,160,983,687,296,527,536};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_R_L_3[] __FLASH__ = {12,358,666,507,516,331,752,160,863,717,366,507,516};	//wait:0.000	//move:0.072


// Sequence: Forward_L_R
unsigned int Boots_Forward_L_R_1[] __FLASH__ = {12,358,666,507,516,341,762,160,863,727,376,487,496};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_L_R_2[] __FLASH__ = {12,358,666,487,526,241,722,80,863,707,336,487,496};	//wait:0.000	//move:0.072
unsigned int Boots_Forward_L_R_3[] __FLASH__ = {12,358,666,507,516,271,692,160,863,657,306,507,516};	//wait:0.000	//move:0.072


// Sequence: Forward_R_I
unsigned int Boots_Forward_R_I_1[] __FLASH__ = {12,358,666,507,516,271,692,160,863,657,306,547,566};	//wait:0.000	//move:0.096
unsigned int Boots_Forward_R_I_2[] __FLASH__ = {12,357,665,497,536,301,732,160,963,707,286,527,546};	//wait:0.000	//move:0.096
unsigned int Boots_Forward_R_I_3[] __FLASH__ = {12,358,666,507,516,301,722,160,863,687,336,507,516};	//wait:0.000	//move:0.096


// Sequence: Forward_L_I
unsigned int Boots_Forward_L_I_1[] __FLASH__ = {12,358,666,507,516,331,752,160,863,717,366,447,476};	//wait:0.000	//move:0.096
unsigned int Boots_Forward_L_I_2[] __FLASH__ = {12,358,666,487,526,271,722,60,863,737,326,477,496};	//wait:0.000	//move:0.096
unsigned int Boots_Forward_L_I_3[] __FLASH__ = {12,358,666,507,516,301,722,160,863,687,336,507,516};	//wait:0.000	//move:0.096


// Sequence: Backward_I_R
unsigned int Boots_Backward_I_R_1[] __FLASH__ = {12,358,666,507,516,311,712,160,863,687,336,457,486};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_I_R_2[] __FLASH__ = {12,358,666,487,526,281,712,60,863,737,336,477,496};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_I_R_3[] __FLASH__ = {12,358,666,508,515,341,722,160,863,697,366,507,516};	//wait:0.000	//move:0.096


// Sequence: Backward_I_L
unsigned int Boots_Backward_I_L_1[] __FLASH__ = {12,358,666,507,516,331,692,160,863,687,336,537,566};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_I_L_2[] __FLASH__ = {12,357,665,497,536,311,742,160,963,687,286,527,546};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_I_L_3[] __FLASH__ = {12,358,666,507,516,301,682,160,863,667,316,507,516};	//wait:0.000	//move:0.096


// Sequence: Backward_R_L
unsigned int Boots_Backward_R_L_1[] __FLASH__ = {12,358,666,507,516,341,742,170,863,707,376,547,566};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_R_L_2[] __FLASH__ = {12,357,665,497,536,301,742,160,993,687,266,527,546};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_R_L_3[] __FLASH__ = {12,358,666,507,516,281,672,160,863,657,306,507,516};	//wait:0.000	//move:0.096


// Sequence: Backward_L_R
unsigned int Boots_Backward_L_R_1[] __FLASH__ = {12,358,666,507,516,281,682,160,853,657,306,477,486};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_L_R_2[] __FLASH__ = {12,358,666,487,526,271,722,60,863,737,336,477,496};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_L_R_3[] __FLASH__ = {12,358,666,507,516,341,742,160,863,717,366,507,516};	//wait:0.000	//move:0.096


// Sequence: Backward_R_I
unsigned int Boots_Backward_R_I_1[] __FLASH__ = {12,358,666,507,516,341,722,160,863,707,356,537,566};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_R_I_2[] __FLASH__ = {12,357,665,497,536,301,782,160,963,687,286,527,546};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_R_I_3[] __FLASH__ = {12,358,666,507,516,301,722,160,863,687,336,507,516};	//wait:0.000	//move:0.096


// Sequence: Backward_L_I
unsigned int Boots_Backward_L_I_1[] __FLASH__ = {12,358,666,507,516,291,692,160,863,667,316,447,486};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_L_I_2[] __FLASH__ = {12,358,666,487,526,241,722,60,863,737,336,477,496};	//wait:0.000	//move:0.096
unsigned int Boots_Backward_L_I_3[] __FLASH__ = {12,358,666,507,516,301,722,160,863,687,336,507,516};	//wait:0.000	//move:0.096


// Sequence: SpinRight
unsigned int Boots_SpinRight_1[] __FLASH__ = {12,438,566,507,516,271,722,110,853,717,336,507,516};	//wait:0.000	//move:0.096
unsigned int Boots_SpinRight_2[] __FLASH__ = {12,408,616,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.072
unsigned int Boots_SpinRight_3[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.144


// Sequence: SpinLeft
unsigned int Boots_SpinLeft_1[] __FLASH__ = {12,457,585,507,516,301,752,170,913,687,306,507,516};	//wait:0.000	//move:0.096
unsigned int Boots_SpinLeft_2[] __FLASH__ = {12,407,615,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.072
unsigned int Boots_SpinLeft_3[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.144


// Sequence: StrafeRight
unsigned int Boots_StrafeRight_1[] __FLASH__ = {12,358,666,457,566,271,722,120,853,717,336,507,516};	//wait:0.000	//move:0.096
unsigned int Boots_StrafeRight_2[] __FLASH__ = {12,358,666,477,546,301,722,170,853,687,336,487,516};	//wait:0.000	//move:0.072
unsigned int Boots_StrafeRight_3[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.096


// Sequence: StrafeLeft
unsigned int Boots_StrafeLeft_1[] __FLASH__ = {12,357,665,457,566,301,752,170,903,687,306,507,516};	//wait:0.000	//move:0.096
unsigned int Boots_StrafeLeft_2[] __FLASH__ = {12,357,665,477,546,301,722,170,853,687,336,507,536};	//wait:0.000	//move:0.072
unsigned int Boots_StrafeLeft_3[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.096


// Sequence: F_Shoot_R
unsigned int Boots_F_Shoot_R_1[] __FLASH__ = {12,358,666,507,516,321,722,210,853,667,336,477,476};	//wait:0.000	//move:0.072
unsigned int Boots_F_Shoot_R_2[] __FLASH__ = {12,358,666,487,526,271,722,10,853,737,336,477,456};	//wait:0.000	//move:0.096
unsigned int Boots_F_Shoot_R_3[] __FLASH__ = {12,358,666,487,526,221,722,440,853,467,356,477,455};	//wait:0.296	//move:0.096
unsigned int Boots_F_Shoot_R_4[] __FLASH__ = {12,358,666,487,526,221,722,290,853,467,356,477,456};	//wait:0.000	//move:0.096
unsigned int Boots_F_Shoot_R_5[] __FLASH__ = {12,358,666,487,526,271,722,10,853,737,336,477,456};	//wait:0.000	//move:0.400
unsigned int Boots_F_Shoot_R_6[] __FLASH__ = {12,358,666,507,516,321,722,210,853,667,336,477,476};	//wait:0.000	//move:0.096
unsigned int Boots_F_Shoot_R_7[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: F_Shoot_L
unsigned int Boots_F_Shoot_L_1[] __FLASH__ = {12,357,665,507,516,301,702,170,813,687,356,547,546};	//wait:0.000	//move:0.072
unsigned int Boots_F_Shoot_L_2[] __FLASH__ = {12,357,665,497,536,301,752,170,1013,687,286,557,546};	//wait:0.000	//move:0.096
unsigned int Boots_F_Shoot_L_3[] __FLASH__ = {12,357,665,497,536,301,802,170,583,677,556,563,546};	//wait:0.296	//move:0.096
unsigned int Boots_F_Shoot_L_4[] __FLASH__ = {12,357,665,497,536,301,802,170,733,677,556,557,546};	//wait:0.000	//move:0.096
unsigned int Boots_F_Shoot_L_5[] __FLASH__ = {12,357,665,497,536,301,752,170,1013,687,286,557,546};	//wait:0.000	//move:0.400
unsigned int Boots_F_Shoot_L_6[] __FLASH__ = {12,357,665,507,516,301,702,170,813,687,356,547,546};	//wait:0.000	//move:0.096
unsigned int Boots_F_Shoot_L_7[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: R_Shoot
unsigned int Boots_R_Shoot_1[] __FLASH__ = {12,358,666,507,516,321,722,210,853,667,336,477,466};	//wait:0.000	//move:0.072
unsigned int Boots_R_Shoot_2[] __FLASH__ = {12,358,666,487,526,271,722,10,853,737,336,477,456};	//wait:0.000	//move:0.096
unsigned int Boots_R_Shoot_3[] __FLASH__ = {12,358,666,387,556,321,722,210,853,657,336,327,455};	//wait:0.200	//move:0.096
unsigned int Boots_R_Shoot_4[] __FLASH__ = {12,358,666,507,516,321,722,210,853,667,336,477,466};	//wait:0.000	//move:0.096
unsigned int Boots_R_Shoot_5[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: L_Shoot
unsigned int Boots_L_Shoot_1[] __FLASH__ = {12,357,665,507,516,301,702,170,813,687,356,547,546};	//wait:0.000	//move:0.072
unsigned int Boots_L_Shoot_2[] __FLASH__ = {12,357,665,497,536,301,752,170,1013,687,286,557,546};	//wait:0.000	//move:0.096
unsigned int Boots_L_Shoot_3[] __FLASH__ = {12,357,665,467,636,301,702,170,813,697,366,563,696};	//wait:0.200	//move:0.096
unsigned int Boots_L_Shoot_4[] __FLASH__ = {12,357,665,507,516,301,702,170,813,687,356,547,546};	//wait:0.000	//move:0.096
unsigned int Boots_L_Shoot_5[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: Pass_R
unsigned int Boots_Pass_R_1[] __FLASH__ = {12,358,666,507,516,321,722,210,853,667,336,477,466};	//wait:0.000	//move:0.400
unsigned int Boots_Pass_R_2[] __FLASH__ = {12,358,666,487,526,271,722,10,853,737,336,477,456};	//wait:0.000	//move:0.096
unsigned int Boots_Pass_R_3[] __FLASH__ = {12,428,656,437,526,221,722,210,853,577,336,477,456};	//wait:0.096	//move:0.096
unsigned int Boots_Pass_R_4[] __FLASH__ = {12,378,656,584,496,141,722,200,853,557,346,477,446};	//wait:0.000	//move:0.096
unsigned int Boots_Pass_R_5[] __FLASH__ = {12,428,656,437,526,221,722,210,853,577,336,477,456};	//wait:0.000	//move:0.200
unsigned int Boots_Pass_R_6[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: Pass_L
unsigned int Boots_Pass_L_1[] __FLASH__ = {12,357,665,507,516,301,702,170,813,687,356,547,546};	//wait:0.000	//move:0.400
unsigned int Boots_Pass_L_2[] __FLASH__ = {12,357,665,497,536,301,752,170,1013,687,286,557,546};	//wait:0.000	//move:0.096
unsigned int Boots_Pass_L_3[] __FLASH__ = {12,367,595,497,586,301,802,170,813,687,446,567,546};	//wait:0.096	//move:0.096
unsigned int Boots_Pass_L_4[] __FLASH__ = {12,367,645,527,439,301,882,170,823,677,466,577,546};	//wait:0.000	//move:0.096
unsigned int Boots_Pass_L_5[] __FLASH__ = {12,367,595,497,586,301,802,170,813,687,446,567,546};	//wait:0.000	//move:0.200
unsigned int Boots_Pass_L_6[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: B_Shoot_R
unsigned int Boots_B_Shoot_R_1[] __FLASH__ = {12,358,666,507,516,321,722,210,853,667,336,477,476};	//wait:0.000	//move:0.400
unsigned int Boots_B_Shoot_R_2[] __FLASH__ = {12,358,666,487,526,221,722,10,853,737,336,477,466};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_R_3[] __FLASH__ = {12,358,666,487,526,545,772,240,853,866,336,477,460};	//wait:0.200	//move:0.096
unsigned int Boots_B_Shoot_R_4[] __FLASH__ = {12,358,666,487,526,495,722,240,853,766,306,477,460};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_R_5[] __FLASH__ = {12,358,666,487,526,221,722,10,853,737,336,477,466};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_R_6[] __FLASH__ = {12,358,666,507,516,321,722,210,853,667,336,477,476};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_R_7[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: B_Shoot_L
unsigned int Boots_B_Shoot_L_1[] __FLASH__ = {12,357,665,507,516,301,702,170,813,687,356,547,546};	//wait:0.000	//move:0.400
unsigned int Boots_B_Shoot_L_2[] __FLASH__ = {12,357,665,497,536,301,802,170,1013,687,286,557,546};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_L_3[] __FLASH__ = {12,357,665,497,536,251,478,170,783,687,157,560,546};	//wait:0.200	//move:0.096
unsigned int Boots_B_Shoot_L_4[] __FLASH__ = {12,357,665,497,536,301,528,170,783,717,257,553,546};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_L_5[] __FLASH__ = {12,357,665,497,536,301,802,170,1013,697,286,557,546};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_L_6[] __FLASH__ = {12,357,665,507,516,301,702,170,813,707,336,547,546};	//wait:0.000	//move:0.096
unsigned int Boots_B_Shoot_L_7[] __FLASH__ = {12,358,666,507,516,301,722,170,853,687,336,507,516};	//wait:0.000	//move:0.496


// Sequence: D_Ready
unsigned int Boots_D_Ready_1[] __FLASH__ = {12,358,665,437,586,311,712,180,843,677,346,437,586};	//wait:0.000	//move:0.400


// Sequence: D_Right
unsigned int Boots_D_Right_1[] __FLASH__ = {12,358,665,437,586,270,649,28,763,762,379,499,651};	//wait:0.096	//move:0.072
unsigned int Boots_D_Right_2[] __FLASH__ = {12,358,665,437,586,270,649,28,763,762,379,499,651};	//wait:0.200	//move:0.072
unsigned int Boots_D_Right_3[] __FLASH__ = {12,358,665,437,586,270,649,28,763,762,379,499,651};	//wait:0.096	//move:0.072


// Sequence: D_Front
unsigned int Boots_D_Front_1[] __FLASH__ = {12,358,665,437,586,233,771,47,969,746,271,437,586};	//wait:0.096	//move:0.072
unsigned int Boots_D_Front_2[] __FLASH__ = {12,358,665,437,586,233,771,47,969,746,271,437,586};	//wait:0.200	//move:0.072
unsigned int Boots_D_Front_3[] __FLASH__ = {12,358,665,437,586,233,771,47,969,746,271,437,586};	//wait:0.096	//move:0.072


// Sequence: D_Left
unsigned int Boots_D_Left_1[] __FLASH__ = {12,358,665,437,586,374,753,260,995,644,261,372,524};	//wait:0.096	//move:0.072
unsigned int Boots_D_Left_2[] __FLASH__ = {12,358,665,437,586,374,753,260,995,644,261,372,524};	//wait:0.200	//move:0.072
unsigned int Boots_D_Left_3[] __FLASH__ = {12,358,665,437,586,374,753,260,995,644,261,372,524};	//wait:0.096	//move:0.072

#endif
