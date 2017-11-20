/*
A - Cart Belt
B - Valves
C - Coin Wheel
D - Coin Measurement
1 - Cup Colour
2 - Coin touch sensor
*/

void initializeCoinSorter()
{
	displayBigTextLine(0,"Insert Toonie");
	while (!getButtonPress(buttonAny))
	{}
	while (getButtonPress(buttonAny))
	{}
	eraseDisplay()
	
	motor[motorD] = 75;
	while(SensorValue[S2] == 0)
	{}

	nMotorEncoder[motorD] = 0;
	motor[motorD] = -75;
	while (nMotorEncoder[motorD] > -1500)
	{}

	motor[motorD] = 75;
	while (nMotorEncoder[motorD] < -400)
	{}
	
	motor[motorD] = 0;
	nMotorEncoder[motorD] = 0;
}

double countCoins();
{
	
}

task main()
{
	SensorType[S2] = sensorEV3_Touch;
	initializeCoinSorter();
}
