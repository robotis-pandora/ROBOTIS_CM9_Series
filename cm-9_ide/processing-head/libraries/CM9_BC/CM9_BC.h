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

#ifndef __FLASH__
#define __FLASH__ __attr_flash
#endif

/// Desire some extra resolution, use 13 bits, rather than 10, during interpolation
#define BIOLOID_SHIFT				3

/// Transition structure
typedef struct
{
	unsigned int * pose;					// addr of pose to transition to 
	int time;								// time for transition
} transition_t; 

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

/// RoboPlus Motion File Assistance
typedef struct
{
	transition_t* seq;
	unsigned int next;
	unsigned int stop;
} sequencer_t;

/// Bioloid Controller Class for CM9 clients.
class BioloidController
{
public:
/// Constructor and setup
	BioloidController() {};
	void setup(unsigned int servo_count);

/// Pose Manipulation functions
	// Load a named pose from FLASH
	void loadPose( unsigned int * addr );
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

/// Servo ID manipulation
	// Set the ID of a particular storage index
	void setId(int index, int id);	
	// Set the ID of a particular storage index
	int getId(int index);

/// Pose Engine
	// Calculates speeds for smooth transition
	// Calls readPose() to ensure starting pose is actual servo locations
	void interpolateSetup(int time);
	// Moves forward one step in current interpolation
	void interpolateStep();
	// Currently interpolating? (can be used to stop interpolating)
	bool interpolating;
	// Number of servos used by this pose.
	int poseSize;

/// Pose Engine Usage: Load a pose and interpolate from present servo locations.
/*
	bioloid.loadPose(myPose);
	bioloid.interpolateSetup(67);
	while(bioloid.interpolating > 0)
	{
		bioloid.interpolateStep();
		delay(10);
	}
*/

/// Sequence Engine
	// Load a sequence and play it from FLASH
	void playSeq( transition_t * addr );
	// Keep moving forward in time
	void play();
	// Are we playing a sequence? (can be used to stop playing)
	bool playing;
	// What sequence is being played?
	transition_t* checkSeq() {return sequence_;}

/// Sequence Engine Usage: Load a sequence and play it.
/*
	bioloid.playSeq(walk);
	while(bioloid.playing)
	{
		bioloid.play();
		delay(10);
	}
*/


/// RoboPlus Compatibility functions
	// Start a series of motion pages from RoboPlusMotion_Array
	void MotionPage(unsigned int page);
	// Check status of motions
	bool MotionStatus(void);
	// Check currently running motion page from RoboPlusMotion_Array
	unsigned int MotionPage();
	// Load a RoboPlusMotion_Array
	void LoadMotionArray(sequencer_t* array);


/// Debug/Emergency controls
	void suspend() { pause(true); }	// set runState_ = 1
	void resume() { pause(false); }	// set runState_ = 2
	// Pause/Resume motion engine
	bool pause(bool);
	// Emergency Stop
	void kill(void);					// set runState_ = 0

/// Engine Modifiers
	// Set the temporal multiplier
	float setTimeModifier(float mult);
	// Set the interpolation time length
	unsigned int setFrameLength(unsigned int time);

private:
	// Present servo positions
	unsigned int * pose_;
	// Goal servo positions
	unsigned int * nextpose_;
	// Change in each servo position per interpolation step
	int * deltas_;
	
	// Calibration offsets for each servo
	int * offsets_;

	// Servo IDs for this BioloidController object
	unsigned char * id_;
	// Number of servos controlled by this BioloidController object
	unsigned int numServos_;

	// Time {from millis()} when last position change occurred
	unsigned long lastframe_;

	// Currently running sequence
	transition_t * sequence_;
	// Number of transitions remaining in current interpolation
	int transitions_;
	unsigned int seqIndex_;

	// RoboPlusMotion Array pointer
	sequencer_t * rpmArray_;
	// RoboPlusMotion Array index
	unsigned int rpmIndexNow_;
	unsigned int rpmIndexNext_;
	unsigned int rpmIndexStop_;
	

	enum
	{
		KILLED,
		PAUSED,
		RUNNING,
		WAITING,
		TRANSITIONING,
		STOPPING
	};

	// Debug/Emergency control state
	unsigned int runState_;

	// Temporal modifier
	float timeModder_;
	// Length (in milliseconds) of each step in interpolation
	unsigned int frameLength_;
	
};
#endif
