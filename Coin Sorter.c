/*
Port Configuration:
A - Cart Belt
B - Valves
C - Coin Wheel
D - Coin Measurement
1 - Cup Colour
2 - Coin touch sensor
*/

void initializeCoinSorter()
{
	const int initializationReverseTo = -1500;
	const int initializationResetTo = -400;

	displayBigTextLine(0, "Insert Toonie");
	while (!getButtonPress(buttonAny))
	{}
	while (getButtonPress(buttonAny))
	{}
	eraseDisplay();

	motor[motorD] = 75;
	while(SensorValue[S2] == 0)
	{}

	//For resetting initializing toonie
	nMotorEncoder[motorD] = 0;
	motor[motorD] = -75;
	while (nMotorEncoder[motorD] > initializationReverseTo)
	{}

	//Setting to correct position
	motor[motorD] = 75;
	while (nMotorEncoder[motorD] < initializationResetTo)
	{}


	motor[motorD] = 0;
	nMotorEncoder[motorD] = 0;
	eraseDisplay();
}

float countCoins()
{
	//Constants for the range of encoder values allowed for each kind of coin
	const int toonieMin = 350;
	const int toonieMax = 450;
	const int loonieMin = 460;
	const int loonieMax = 590;
	const int quarterMin = 610;
	const int quarterMax = 750;
	const int nickelMin = 800;
	const int nickelMax = 900;
	const int dimeMin = 950;
	const int dimeMax = 1150;
	const int noCoinMax = 1300;

	float totalCoin = 0;
	int encoderValue = 0;
	bool moreCoins = true;

	int motorPosition = 0;


	nMotorEncoder[motorC] = 0;

	while (moreCoins)
	{

	/*
		//Spin the coin wheel to drop a coin into the measurement system
		motor[motorC] = 75;
		while(nMotorEncoder[motorC] % 60 < 2)
		{}
		while(nMotorEncoder[motorC] % 60 > 1)
		{}
		motor[motorC] = 0;
		wait1Msec(1000); //MAKE THIS FASTER AFTER TESTING
		motor[motorC] = 25;
		while(nMotorEncoder[motorC] % 120 < 2)
		{}
		while (nMotorEncoder[motorC] % 120 > 1)
		{}
		motor[motorC] = 0;
*/


		motor[motorC] = 75;
		while (motorPosition + 60 > nMotorEncoder[motorC]);

		motor[motorC] = 0;
		wait1Msec(500); //MAKE THIS FASTER AFTER TESTING
		motor[motorC] = 25;

		while (motorPosition + 120 > nMotorEncoder[motorC]);
		motor[motorC] = 0;



		//Squeeze the coin and get a motor encoder reading
		motor[motorD] = 75; //speed up motor speed after testing.
		while(SensorValue[S2] == 0)
		{}
		motor[motorD] = 0;
		encoderValue = nMotorEncoder[motorD];

		//Add appropriate coin value to the total count
		int encoderReverse = 0;
		if (toonieMin < encoderValue && encoderValue < toonieMax)
		{
			totalCoin += 2;
			encoderReverse = 950;
		}
		else if (loonieMin < encoderValue && encoderValue < loonieMax)
		{
			totalCoin += 1;
			encoderReverse = 875;
		}
		else if (quarterMin < encoderValue && encoderValue < quarterMax)
		{
			totalCoin += 0.25;
			encoderReverse = 600;
		}
		else if (nickelMin < encoderValue && encoderValue < nickelMax)
		{
			totalCoin += 0.05;
			encoderReverse = 400;
		}

		else if (dimeMin < encoderValue && encoderValue < dimeMax)
		{
			totalCoin += 0.1;
			encoderReverse = 200;
		}
		else if (encoderValue > noCoinMax && totalCoin > 0)
		{
			moreCoins = false;
		}
		else if (encoderValue > noCoinMax)
		{
			displayTextLine(6, "No coins yet");
		}
		else
		{
			displayBigTextLine(6, "?????");
		}

		//for testing only
		displayTextLine(4, "current total: %f",totalCoin);

		//Drop coin and reset coin measurement system
		motor[motorD] = -75;
		while(nMotorEncoder[motorD] > -encoderReverse)
		{}
		motor[motorD] = 75;
		while (nMotorEncoder[motorD] < 0)
		{}
		motor[motorD] = 0;

		motorPosition = nMotorEncoder[motorC];

	}



	return totalCoin;
}


task main()
{

	SensorType[S2] = sensorEV3_Touch;
	initializeCoinSorter();

	float drinkCost = 0;
	float totalCoin = 0;


	//temporary, for testing
	drinkCost = 5;

	while (!getButtonPress(buttonAny));
		while (getButtonPress(buttonAny));


	while (totalCoin <= drinkCost)
	{
		totalCoin += countCoins();
		displayTextLine(6, "Money Inserted: %f",totalCoin);
	}
	displayTextLine(7,"drink can be made now");
	wait1Msec(60000);
}
