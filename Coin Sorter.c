//############################Start of Coin Sorting Programs##################################



void advanceCoin()
{
	motor[motorC] = 60;

	while (nMotorEncoder[motorC] < 45)
	{}
	motor[motorC] = 0;


	motor[motorC] = -40;
	while (nMotorEncoder[motorC] > 15)
	{}
	motor[motorC] = -15;
	while (nMotorEncoder[motorC] > 0)
	{}
	motor[motorC] = 0;

	wait1Msec(300);
}

void initializeCoinSorter()
{
	const int initializationReverseTo = -1500;
	const int initializationResetTo = -400;

	SensorType[S4] = sensorEV3_Touch;


	displayBigTextLine(3, "Insert Toonie");


	while (!getButtonPress(buttonAny))
	{}
	while (getButtonPress(buttonAny))
	{}

	advanceCoin();

	eraseDisplay();

	motor[motorD] = 75;
	while(SensorValue[S4] == 0)
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




float countCoins(float payTotal)
{
	//Constants for the range of encoder values allowed for each kind of coin
	const int TOONIE_MIN = 350;
	const int TOONIE_MAX = 450;
	const int LOONIE_MIN = 460;
	const int LOONIE_MAX = 590;
	const int QUARTER_MIN = 610;
	const int QUARTER_MAX = 750;
	const int NICKEL_MIN = 800;
	const int NICKEL_MAX = 900;
	const int DIME_MIN = 950;
	const int DIME_MAX = 1150;
	const int NO_COIN_MAX = 1250;

	float totalCoin = 0;
	int encoderValue = 0;
	bool moreCoins = true;

	int motorPosition = 0;


	nMotorEncoder[motorC] = 0;

	while (moreCoins)
	{

		advanceCoin();

		//Squeeze the coin and get a motor encoder reading
		motor[motorD] = 75; //speed up motor speed after testing.
		while(SensorValue[S4] == 0)
		{}

		motor[motorD] = 0;
		encoderValue = nMotorEncoder[motorD];

		//Add appropriate coin value to the total count
		int encoderReverse = 0;
		if (TOONIE_MIN < encoderValue && encoderValue < TOONIE_MAX)
		{
			totalCoin += 2;
			encoderReverse = 1100;
		}
		else if (LOONIE_MIN < encoderValue && encoderValue < LOONIE_MAX)
		{
			totalCoin += 1;
			encoderReverse = 925;
		}
		else if (QUARTER_MIN < encoderValue && encoderValue < QUARTER_MAX)
		{
			totalCoin += 0.25;
			encoderReverse = 750;
		}
		else if (NICKEL_MIN < encoderValue && encoderValue < NICKEL_MAX)
		{
			totalCoin += 0.05;
			encoderReverse = 550;
		}

		else if (DIME_MIN < encoderValue && encoderValue < DIME_MAX)
		{
			totalCoin += 0.1;
			encoderReverse = 350;
		}
		else if (encoderValue > NO_COIN_MAX && totalCoin >= payTotal)
		{
			moreCoins = false;
		}
		else if (encoderValue > NO_COIN_MAX)
		{
			//displayTextLine(6, "No coins yet");
		}
		else
		{
			displayBigTextLine(6, "Coin error");
		}

		if (totalCoin < 0)
			displayPayment(payTotal, 0);
		else
			displayPayment(payTotal, totalCoin);



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
//############################End of Coin Sorting Programs##################################
