/*
 *******************************************************************************
 *  Dynamixel Bus Scanner (CM-900 version)
 *******************************************************************************
 *  Searches through all valid IDs to find all dynamixel devices currently on
 *    the bus, and uses the Model Number to identify the device by name
 *******************************************************************************
 */

// My gigantic dynamixel header file
#include <dynamixel_address_tables.h>

#define DXL_BAUDRATE_NUMBER 1  // number = 1 is 1000000 bps, 34 is 57600 bps

void setup()
{
	SerialUSB.begin();
	Dxl.begin(DXL_BAUDRATE_NUMBER);

	pinMode(BOARD_LED_PIN, OUTPUT);

	// Waits 10 seconds for you to open the console (open too quickly after
	//   downloading new code, and you will get errors
	delay(10000);
	SerialUSB.print("Send any value to continue...\n");
	while(!SerialUSB.available());
}

void loop()
{
	int model;
	for (int i=1; i<BROADCAST_ID; i++)
	{
		// Print device ID being checked
		SerialUSB.print(i);
		delay(10);
		// Read model number
		model = Dxl.readWord(i, AXM_MODEL_NUMBER_L);
		// If got a response, then device exists
		if (Dxl.getResult()==COMM_RXSUCCESS)
		{
			if (model == MODEL_AX12)
				SerialUSB.println(": AX-12");
			else if (model == MODEL_AX12W)
				SerialUSB.println(": AX-12W");
			else if (model == MODEL_AX18)
				SerialUSB.println(": AX-18");
			else if (model == MODEL_AXS1)
				SerialUSB.println(": AX-S1");
			else if (model == MODEL_AXS20)
				SerialUSB.println(": AX-S20");
			else if (model == MODEL_JHFPS)
				SerialUSB.println(": JH-FPS");
			else if (model == MODEL_HaViMo2)
				SerialUSB.println(": HaViMo2");
			else if (model == MODEL_MX28)
				SerialUSB.println(": MX-28");
			else if (model == MODEL_IRSA)
				SerialUSB.println(": IRSA");
			else
			{
				// Not recognized/supported by my dynamixel device header file
				SerialUSB.print(": Unknown : ");
				SerialUSB.println(model);
			}
		}
		else
			SerialUSB.println(": Not Found");
	}
	// Indicate search is finished by toggling the LED endlessly
	while(1)
	{
		digitalWrite(BOARD_LED_PIN, HIGH);
		delay(100);
		digitalWrite(BOARD_LED_PIN, LOW);
		delay(100);
	}
}
