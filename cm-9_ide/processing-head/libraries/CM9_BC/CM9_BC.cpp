/*
  BioloidController.cpp - ArbotiX Library for Bioloid Pose Engine
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

#include "CM9_BC.h"


/// Newer BioloidController setup function
void BioloidController::setup(unsigned int servo_count)
{
	if (servo_count < 1)
		numServos_ = 20;
	else
		numServos_ = servo_count;

	// setup storage
	id_ = (unsigned char *) malloc(numServos_ * sizeof(unsigned char));
	pose_ = (unsigned int *) malloc(numServos_ * sizeof(unsigned int));
	nextpose_ = (unsigned int *) malloc(numServos_ * sizeof(unsigned int));
	deltas_ = (int *) malloc(numServos_ * sizeof(int));
	offsets_ = (int *) malloc(numServos_ * sizeof(int));

	// initialize
	int iter;
	for(iter=0;iter<numServos_;iter++)
	{
		id_[iter] = iter+1;
		pose_[iter] = 512 << BIOLOID_SHIFT;
		nextpose_[iter] = 512 << BIOLOID_SHIFT;
		offsets_[iter] = 0;
	}
	interpolating = false;
	playing = false;
	lastframe_ = millis();

	frameLength_ = 33;	// default is 33[ms] to get ~30[Hz] update rate


	runState_ = WAITING;

	rpmArray_ = 0;
	rpmIndexNow_ = 0;
	rpmIndexNext_ = 0;
	rpmIndexStop_ = 0;
}

/// Manually set a servo ID
void BioloidController::setId(int index, int id)
{
	id_[index] = id;
}
/// Check a servo ID
int BioloidController::getId(int index)
{
	return id_[index];
}

/// Load a named pose from FLASH into nextpose.
void BioloidController::loadPose( unsigned int * addr )
{
	unsigned int servo_count = addr[0];
	if (servo_count > numServos_)
	{
		SerialUSB.print("The pose you attempted to load requires more servos than the object allocated during setup. Doing this leads to bad, bad things...\n");
		return;
	}
	poseSize = servo_count;

//	SerialUSB.print("\nLoading Pose");
	int iter;
	for(iter=0; iter<poseSize; iter++)
	{
		nextpose_[iter] = addr[1+iter] << BIOLOID_SHIFT;
//		SerialUSB.print("\n  Servo ID=");SerialUSB.print(id_[iter]);
//		SerialUSB.print(" to goal=");SerialUSB.print(nextpose_[iter]);
//		SerialUSB.print(".  Current position=");SerialUSB.println(pose_[iter]);
	}
}
/// Read current servo positions and store to the pose.
void BioloidController::readPose()
{
//	SerialUSB.print("\nCurrent Pose");
	int iter;
	for(iter=0; iter<numServos_; iter++)
	{
		int temp = Dxl.readWord(id_[iter], P_PRESENT_POSITION_L);
		if ((temp < 1024) && (temp > 0))
			pose_[iter] = temp << BIOLOID_SHIFT;
		else
			pose_[iter] = 512 << BIOLOID_SHIFT;
//		SerialUSB.print("\n  Servo ID=");SerialUSB.print(id_[iter]);
//		SerialUSB.print(" at present=");SerialUSB.println(pose_[iter]);
//		delay(25);
	}
}
/// Write the next pose out to servos using sync write.
void BioloidController::writePose()
{
	if (runState_ < 2)
		return;

	int temp;
	int numParams = 2 + (poseSize * 3);   // 3 = id + GOAL_L + GOAL_H

	Dxl.setTxPacketId( BROADCAST_ID );
	Dxl.setTxPacketInstruction( INST_SYNC_WRITE );
	Dxl.setTxPacketLength( numParams );
	Dxl.setTxPacketParameter( 0, P_GOAL_POSITION_L );
	Dxl.setTxPacketParameter( 1, 2 );	// writing two bytes
//	SerialUSB.print("\nNext Pose Packet");
	int iter;
	for(iter=0; iter<poseSize; iter++)
	{
		temp = (pose_[iter] >> BIOLOID_SHIFT) + offsets_[iter];
//		SerialUSB.print("\n  Servo ID=");SerialUSB.print(id_[iter]);
//		SerialUSB.print(" to goal=");SerialUSB.println(temp);
		Dxl.setTxPacketParameter( 2 + 3*iter + 0, id_[iter] );
		Dxl.setTxPacketParameter( 2 + 3*iter + 1, (temp)&0xff );
		Dxl.setTxPacketParameter( 2 + 3*iter + 2, (temp>>8)&0xff );
	}
	Dxl.txrxPacket();
}

/// Setup for interpolating from pose to nextpose over TIME milliseconds
void BioloidController::interpolateSetup(int time)
{
	time = (int) (time * timeModder_);
	int frames = (time/frameLength_) + 1;
	lastframe_ = millis();

	// Make sure that pose_ contains accurate position information of servos
		// If we do not check here and user did not call in sketch, then can
		// have large and unexpected jump before starting smooth interpolation
	readPose();

	int iter;
	// Set deltas for each servo...
	for(iter=0; iter<poseSize; iter++)
	{
/*
		if(nextpose_[iter] > pose_[iter])
		{
			deltas_[iter] = (nextpose_[iter] - pose_[iter])/frames + 1;
		}
		else
		{
			deltas_[iter] = (pose_[iter] - nextpose_[iter])/frames + 1;
		}
*/
		deltas_[iter] = (nextpose_[iter] - pose_[iter])/frames + 1;
	}
	interpolating = true;
}
/// Write next intermediate pose of the interpolation
void BioloidController::interpolateStep()
{
	if (runState_ < 2)
		return;

	if (!interpolating)
		return;

	int complete = poseSize;
	while( (millis() - lastframe_) < frameLength_ );
	lastframe_ = millis();
//	readPose();

	int iter;
	// update each servo
	for(iter=0; iter<poseSize; iter++)
	{
		int diff = nextpose_[iter] - pose_[iter];
		if(diff == 0)
		{
			complete--;
		}
		else
		{
/*
			if(diff > 0)
			{
				if(diff < deltas_[iter])
				{
					pose_[iter] = nextpose_[iter];
					complete--;
				}
				else
				{
					pose_[iter] += deltas_[iter];
				}
			}
			else
			{
				if((-diff) < deltas_[iter])
				{
					pose_[iter] = nextpose_[iter];
					complete--;
				}
				else
				{
					pose_[iter] -= deltas_[iter];
				}
			}
*/
			if (abs(diff) > abs(deltas_[iter]))
			{
				pose_[iter] += deltas_[iter];
			}
			else
			{
				pose_[iter] = nextpose_[iter];
				complete--;
			}
		}
	}
	if(complete <= 0)
	{
		interpolating = false;
	}
	writePose();
}

/// Get a servo value from the current pose
int BioloidController::getCurPose(int id)
{
	int iter;
	for(iter=0; iter<numServos_; iter++)
	{
		if( id_[iter] == id )
			return ((pose_[iter]) >> BIOLOID_SHIFT);
	}
	return -1;
}
/// Get a servo value from the goal pose
int BioloidController::getNextPose(int id)
{
	int iter;
	for(iter=0; iter<numServos_; iter++)
	{
		if( id_[iter] == id )
			return ((nextpose_[iter]) >> BIOLOID_SHIFT);
	}
	return -1;
}
/// Set a servo value in the goal pose
void BioloidController::setNextPose(int id, int pos)
{
	int iter;
	for(iter=0; iter<numServos_; iter++)
	{
		if( id_[iter] == id )
		{
			nextpose_[iter] = (pos << BIOLOID_SHIFT);
			return;
		}
	}
}

/// Load and begin playing a sequence.
void BioloidController::playSeq( transition_t * addr )
{
	sequence_ = (transition_t *) addr;

	// number of transitions left to load
//	transitions_ = ( sequence_->time );
//	sequence_++;

	seqIndex_ = 0;
	transitions_ = sequence_[seqIndex_].time;
	seqIndex_++;

//	SerialUSB.print("Number Transitions: ");SerialUSB.println(transitions_);
	// load a transition
//	loadPose( sequence_->pose );
//	interpolateSetup( sequence_->time );
//	transitions_--;

	loadPose( sequence_[seqIndex_].pose );
//	interpolateSetup( sequence_[seqIndex_].time );
	int time = (int) (sequence_[seqIndex_].time * timeModder_);
	interpolateSetup( time );

	playing = true;
}
/// Keep playing the current sequence.
void BioloidController::play()
{
	if (runState_ < 2)
		return;

	if (!playing)
		return;
	if (interpolating)
	{
		interpolateStep();
	}
	else  // Move on to next pose
	{
//		sequence_++;
//		if (transitions_ > 0)
//		{
//			loadPose( sequence_->pose );
//			interpolateSetup( sequence_->time );
//			transitions_--;
//		}
		seqIndex_++;
		if (seqIndex_ <= transitions_)
		{
			loadPose( sequence_[seqIndex_].pose );
//			interpolateSetup( sequence_[seqIndex_].time );
			int time = (int) (sequence_[seqIndex_].time * timeModder_);
			interpolateSetup( time );
		}
		else
		{
			playing = false;
		}
	}
}

/// Start a series of motion pages from RoboPlusMotion_Array
void BioloidController::MotionPage(unsigned int page)
{
	if ()

	rpmIndexNow_ = page;
	rpmIndexNext_ = rpmArray_[page].next;
	rpmIndexStop_ = rpmArray_[page].next;

	playSeq(rpmArray_[page].seq);
}
/// Check status of motions
bool BioloidController::MotionStatus(void)
{
	return playing;
}
/// Check currently running motion page from RoboPlusMotion_Array
unsigned int BioloidController::MotionPage()
{
	if (MotionStatus())
		return rpmIndexNow_;
	else
		return 0;
}
/// Load a RoboPlusMotion_Array
void BioloidController::LoadMotionArray(sequencer_t* array)
{
	rpmArray_ = array;
}

/// Pause the motion engine
bool BioloidController::pause(bool bolly)
{
	if (bolly)
	{
		runState_ = PAUSED;
	}
	else
	{
		runState_ = RUNNING;
	}
}
/// Emergency Stop
void BioloidController::kill(void)
{
	runState_ = KILLED;
	Dxl.writeByte(BROADCAST_ID, P_TORQUE_ENABLE, 0);
}

/// Set the Temporal modifier
float BioloidController::setTimeModifier(float mult)
{
	if ((mult > 0.01) && (mult < 2.0))
		timeModder_ = mult;
	return timeModder_;
}
/// Set the interpolation time length
unsigned int BioloidController::setFrameLength(unsigned int time)
{
	if (time > 10)
		frameLength_ = time;
	return frameLength_;
}


