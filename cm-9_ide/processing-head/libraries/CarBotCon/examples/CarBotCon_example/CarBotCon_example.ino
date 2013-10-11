/*
 *******************************************************************************
 *  CM-5 Carbot control with a RC-100
 *******************************************************************************
 */

#include <RC100.h>

RC100 Remo;
int RcvData = 0;


#include <CarBotCon.h>
CarBotCon carbo;

void setup()
{
	Dxl.begin(1);
	SerialUSB.begin();
/*
	// Waits 10 seconds for you to open the console (open too quickly after
	//   downloading new code, and you will get errors
    delay(10000);
	SerialUSB.print("Send any value to continue...\n");
	while(!SerialUSB.available())
	{
		delay(1000);
		digitalWrite(BOARD_LED_PIN, LOW);
		SerialUSB.print("Send any value to continue...\n");
		delay(1000);
		digitalWrite(BOARD_LED_PIN, HIGH);
	}
	SerialUSB.print("Now starting program\n");
*/
	Remo.begin();
	int righties[] = {1,3};
	carbo.SetRightServos(2, righties);
	int lefties[] = {2,4};
	carbo.SetLeftServos(2, lefties);
	carbo.SetWheelMode(true);
}

void loop()
{
	while(1)
	{
		if(Remo.available())
		{
			RcvData = Remo.readData();

			if(RcvData & RC100_BTN_U)
			{
				carbo.Forward(100);
				SerialUSB.print("Forward\n");
			}
			else if (RcvData & RC100_BTN_D)
			{
				carbo.Backward(100);
				SerialUSB.print("Backward\n");
			}
			else if (RcvData & RC100_BTN_L)
			{
				carbo.SpinLeft(100);
				SerialUSB.print("SpinLeft\n");
			}
			else if (RcvData & RC100_BTN_R)
			{
				carbo.SpinRight(100);
				SerialUSB.print("SpinRight\n");
			}
		}
		else
		{
			carbo.Stop();
//			SerialUSB.print("Stop\n");
		}
		delay(100);
	}
}
