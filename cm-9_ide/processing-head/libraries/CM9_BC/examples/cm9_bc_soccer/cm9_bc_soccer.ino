#include <CM9_BC.h>
#include "Boots_RPM.h"		// Only legs of Type-A Humanoid

#include <RC100.h>

BioloidController BioCon;
RC100 Boomer;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup()
{
	// Setup Dynamixel bus, USB, and RC-100 interfaces
	Dxl.begin(1);
	SerialUSB.begin();
	Boomer.begin();

	while ( !SerialUSB.available() )
	{
		delay(1000);
		digitalWrite(BOARD_LED_PIN, LOW);
		SerialUSB.print("Send any value to continue...\n");
		delay(1000);
		digitalWrite(BOARD_LED_PIN, HIGH);
		if (!Boomer.available())
		{
			if (Boomer.readData()==RC100_BTN_U)
				break;
		}
	}
	SerialUSB.read();
	SerialUSB.print("Now starting program\n");

//	SerialUSB.print("*** Boots_RoboPlusMotion_Array: ");SerialUSB.print((unsigned int) Boots_RoboPlusMotion_Array);SerialUSB.print(" ***\n\n");
	// Load the RoboPlusMotion_Array from our _RPM header file
	BioCon.RPM_Setup(Boots_RoboPlusMotion_Array);
	//  This gives the motion engine the location of the RPM page file
	// 	Sets up the motion engine (allocates memory and initializes variables)
	//  Loads the servo IDs from the first pose in the first sequence in the array
	SerialUSB.print("Done with motion engine setup.\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop()
{
//	SerialUSB.print("*** Boots_Init: ");SerialUSB.print((unsigned int) Boots_Init);SerialUSB.print(" ***\n");
//	SerialUSB.print("*** Boots_id: ");SerialUSB.print((unsigned int) Boots_Init[0].pose);SerialUSB.print(" ***\n");
//	SerialUSB.print("*** Boots_Init_1: ");SerialUSB.print((unsigned int) Boots_Init[1].pose);SerialUSB.print(" ***\n\n");

//	SerialUSB.print("*** Boots_D_Left: ");SerialUSB.print((unsigned int) Boots_D_Left);SerialUSB.print(" ***\n");
//	SerialUSB.print("*** Boots_id: ");SerialUSB.print((unsigned int) Boots_D_Left[0].pose);SerialUSB.print(" ***\n");
//	SerialUSB.print("*** Boots_D_Left_1: ");SerialUSB.print((unsigned int) Boots_D_Left[1].pose);SerialUSB.print(" ***\n\n");



/// Set bot to an initial/ready position
	SerialUSB.print("loop() started. Going to Ready Position...\n");
	BioCon.MotionPage(1);	// Boots_Init
//	SerialUSB.print("\n*** successfully loaded Boots_Init? ***\n");
	while (BioCon.MotionStatus())
	{
//		SerialUSB.print("\n*** successfully checked MotionStatus() ***\n");
		delay(1);
		BioCon.Play();
	}
	SerialUSB.print(" done.\nStarting main loop for user code.\n");
	while(1);
/// Main loop where all user code occurs
// Do not modify anthing outside this while loop unless you are very, very
//  certain of what you are doing.
// Do not create any infinite loops or >30ms waits within this loop, or the
//  motion engine will fail to update.
	while(1)
	{
		unsigned int rang = 0;
		if (Boomer.available())
		{
			rang = Boomer.readData();
		}
		else if (SerialUSB.available())
		{
			rang = SerialUSB.read();
		}
		
		if (rang == RC100_BTN_U)
		{
			// Go forward
			BioCon.MotionPage(2);	// Boots_Forward_I_R
		}
		else if (rang == RC100_BTN_D)
		{
			// Go Backward
			BioCon.MotionPage(8);	// Boots_Backward_I_R
		}
		else if (rang == RC100_BTN_L)
		{
			// Strafe Left
			BioCon.MotionPage(17);	// Boots_StrafeLeft
		}
		else if (rang == RC100_BTN_R)
		{
			// Strafe Right
			BioCon.MotionPage(16);	// Boots_StrafeRight
		}
		else if (rang == RC100_BTN_6)
		{
			// Spin Left
			BioCon.MotionPage(15);	// Boots_SpinLeft
		}
		else if (rang == RC100_BTN_5)
		{
			// Spin Right
			BioCon.MotionPage(14);	// Boots_SpinRight
		}
		else if (rang == RC100_BTN_1)
		{
			// Go to Init
			BioCon.MotionPage(1);	// Boots_Init
		}
		else if (rang > 0)
		{
			// Stop
			BioCon.MotionPage(0);	// INVALID/STOP
		}
		else
		{
			delay(5);
		}


		
/// DO NOT REMOVE ME!!!
		BioCon.Play();	// TODO: replace with timer interrupt-based update.
	}
}
