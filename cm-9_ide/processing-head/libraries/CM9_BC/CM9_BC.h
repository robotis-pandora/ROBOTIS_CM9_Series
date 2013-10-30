/*
  BioloidController.h - ArbotiX Library for Bioloid Pose Engine
  Copyright (c) 2008-2012 Michael E. Ferguson.  All right reserved.

  Copyright (c) 2012, 2013 Matthew Paulishen. Copypaster: NaN a.k.a. tician

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CM9_BC_h
#define CM9_BC_h

#include <Arduino-compatibles.h>
#include "stdlib.h"
#include <Dynamixel.h>
#include <libpandora_types.h>

/// Pose format (array of integers):
//	unsigned int pose_name[] __FLASH__ = {4,512,512,482,542};
 		// First number is number of servos used by the pose
 		// Subsequent entries are servo positions

/// Sequence format (array of pose pointers and integers):
//	transition_t seq_name[] __FLASH__ = {{NULL,count},{pose_name,1000},...};
		// First "time" entry in array contains number of poses in sequence.
			// The CM-9 IDE may complain if the "pose" component of the first
			//  entry is not an unsigned int pointer.  Can be useful to store
			//  pointer to an array containing the servo IDs used by sequence.
		// Subsequent entries are pointers to pose arrays and timelength of pose.

#ifndef __FLASH__
#define __FLASH__ __attr_flash
#endif

/// Desire some extra resolution, use 16 bits, rather than 10, during interpolation
#define BIOLOID_SHIFT				6

/// BioloidController Pose type
//typedef unsigned int bc_pose_t;
#define bc_pose_t unsigned int

/// BioloidController Sequence
typedef struct
{
	bc_pose_t * pose;					// address of pose
	unsigned int time;					// time interval for transition
} bc_seq_t; 							// BC sequence

/// RoboPlus Motion Page
typedef struct
{
	bc_seq_t * steps;					// pointer to sequence of "steps"/poses
	unsigned int next;					// index of next sequence
	unsigned int stop;					// index of stop sequence
} rpm_page_t;							// RPM sequence

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Bioloid Controller Class for CM9 clients.
class BioloidController
{
public:
/// Constructor and setup
	BioloidController() {};
	void setup(unsigned int servo_count);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Debug/Emergency controls
	void suspend() { pause(true); }	// set bcState_ = PAUSED
	void resume() { pause(false); }	// set bcState_ = RUNNING
	// Pause/Restart motion engine
	bool pause(bool);
	// Emergency Stop (disables servo torque and stops all engine-based servo usage)
	void kill(void);					// set bcState_ = KILLED


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Pose Manipulation functions
	// Load a named pose from FLASH
	void loadPose( bc_pose_t * addr );
	// Read a pose in from the servos
	void readPose();
	// Write a pose out to the servos
	void writePose();

	// Get a servo value in the current pose
	int getCurPose(int id);	
	// Get a servo value in the next pose
	int getNextPose(int id);
	// Set a servo value in the next pose
	void setNextPose(int id, int pos);

	// Set number of servos in current pose
	void setPoseSize(unsigned int num);
	// Get number of servos in current pose
	unsigned int getPoseSize();


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Servo Manipulation functions
	// Set the ID of a particular storage index
	void setId(int index, int id);	
	// Set the ID of a particular storage index
	int getId(int index);
	// Set servo resolution
	unsigned int setResolution(unsigned int id, unsigned int res);

	// Load servo offsets from FLASH
	void loadOffsets( int * addr );


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Pose Interpolation
	// Calculates speeds for smooth transition
	// Calls readPose() to ensure starting pose is actual servo locations
	void interpolateSetup(unsigned int time);
	// Moves forward one step in current interpolation
	void interpolateStep();
	// Currently interpolating?
	bool interpolating(bool);	// Polls current state
	bool interpolating(void);	// Used to control interpolation state

/// Pose Interpolation Usage: Load a pose and interpolate from present servo locations.
/*
	bioloid.loadPose(myPose);
	bioloid.interpolateSetup(67);
	while(bioloid.interpolating())
	{
		bioloid.interpolateStep();
		delay(10);
	}
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Sequence Engine
	// Load a sequence and play it from FLASH
	void playSeq( bc_seq_t * addr );
	// Keep moving forward in time
	void play();
	// Are we playing a sequence?
	bool playing(void);	// Polls current state
	bool playing(bool);	// Used to control playing state
	// What sequence is being played?
	bc_seq_t* checkSeq() {return sequence_;}

/// Sequence Engine Usage: Load a sequence and play it.
/*
	bioloid.playSeq(walk);
	while(bioloid.playing())
	{
		bioloid.play();
		delay(10);
	}
*/


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// RoboPlus Compatibility functions
	// Start a series of motion pages from RoboPlusMotion_Array
	void MotionPage(unsigned int page_index);
	void setMotionPage(unsigned int page_index) { MotionPage(page_index); }
	// Check status of motions
	bool MotionStatus(void);
	// Check currently running motion page from RoboPlusMotion_Array
	unsigned int MotionPage();
	unsigned int getMotionPage() { return MotionPage; }
	// Keep playing a RoboPlusMotion series of sequences
	void Play();
	// Load a RoboPlusMotion_Array
	void RPM_Setup(rpm_page_t* array);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Engine Modifiers
	// Set the temporal multiplier
//	float setTimeModifier(float mult);
	unsigned int setTimeModifier(unsigned int mult);
	// Set the interpolation time length
	unsigned int setFrameLength(unsigned int time);



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	// Servo IDs for this BioloidController object
	unsigned char * id_;
	// Present servo positions
	bc_pose_t * pose_;
	// Goal servo positions
	bc_pose_t * nextpose_;
	// Change in each servo position per interpolation step
	int * deltas_;
	// Calibration offsets for each servo
	int * offsets_;
	// Resolution of each servo
	unsigned int * resolutions_;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Number of servos used by current pose.
	unsigned int poseSize_;
	// Number of servos controllable by this BioloidController object
	unsigned int numServos_;

	// Time {from millis()} when last position change occurred
	unsigned long lastframe_;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Currently running sequence
	bc_seq_t * sequence_;
	// Number of transitions remaining in current interpolation
	unsigned int transitions_;
	unsigned int seqIndex_;

	// MotionEngine control state
	enum
	{
		INTERPOLATING,
		INTERPOLATION_DONE,
		SEQUENCE_DONE
	} seqState_;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// RoboPlusMotion Array pointer
	rpm_page_t * rpmArray_;
	// RoboPlusMotion Array index
	unsigned int rpmIndexNow_;
	unsigned int rpmIndexInput_;

	// RoboPlusMotion control state
	enum
	{
		PLAYING,
		STOPPING,
		STOPPED
	} rpmState_;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Debug/Emergency control state
	enum
	{
		KILLED,
		PAUSED,
		RUNNING
	} bcState_;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Temporal modifier
//	float timeModder_;
	unsigned int timeModder_;
	// Length (in milliseconds) of each step in interpolation
	unsigned int frameLength_;
	
};
#endif
