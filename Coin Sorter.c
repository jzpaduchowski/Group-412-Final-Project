//############################Start of Coin Sorting Programs##################################

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


//Function to put a new coin into the coin reader
void advanceCoin()
{
	//Turns the coin wheel at 60% power for 45 degrees to flick the coin into the reader
	motor[motorC] = 60;
	while (nMotorEncoder[motorC] < 45)
	{}
	motor[motorC] = 0;

	//Resets the motor at a slower speed than normal
	motor[motorC] = -40;
	while (nMotorEncoder[motorC] > 15)
	{}
	motor[motorC] = -15;
	while (nMotorEncoder[motorC] > 0)
	{}
	motor[motorC] = 0;

	wait1Msec(300);
}

//Initializes the coin sorter with a toonie as a set diameter
void initializeCoinSorter()
{
	const int initializationReverseTo = -1500;
	const int initializationResetTo = -400;

	displayBigTextLine(3, "Insert Toonie");

	//Gets button press to read first toonie
	while (!getButtonPress(buttonAny))
	{}
	while (getButtonPress(buttonAny))
	{}

	eraseDisplay();

	//Gets the first toonie
	advanceCoin();

	//Reads the value of the toonie
	motor[motorD] = 75;
	while(SensorValue[S4] == 0)
	{}

	motor[motorD] = 0;

	//Resets the motor to the position that will allow the toonie into the reader but not dimes
	nMotorEncoder[motorD] = 0;
	motor[motorD] = -75;
	//Drops the toonie first
	while (nMotorEncoder[motorD] > initializationReverseTo)
	{}
	motor[motorD] = 75;
	while (nMotorEncoder[motorD] < initializationResetTo)
	{}

	//Resets the motor for the rest of the coin reading
	motor[motorD] = 0;
	nMotorEncoder[motorD] = 0;
}

//Counts all the coins in the reader until there are no more
float countCoins(float payTotal)
{
	float totalCoin = 0;
	int encoderValue = 0;
	bool moreCoins = true;

	nMotorEncoder[motorC] = 0;

	while (moreCoins)
	{
		//Gets the next coin
		advanceCoin();

		//Squeeze the coin and get a motor encoder reading
		motor[motorD] = 75; //speed up motor speed after testing.
		while(SensorValue[S4] == 0)
		{}

		//Stops the motor
		motor[motorD] = 0;
		encoderValue = nMotorEncoder[motorD];

		//Detects which cup it is and add appropriate coin value to the total count
		int encoderReverse = 0;
		if (TOONIE_MIN < encoderValue && encoderValue < TOONIE_MAX)
		{
			totalCoin += 2;
			encoderReverse = 1100;
		}
		else if (LOONIE_MIN < encoderValue && encoderValue < LOONIE_MAX)
		{
			totalCoin += 1;
			encoderReverse = 975;
		}
		else if (QUARTER_MIN < encoderValue && encoderValue < QUARTER_MAX)
		{
			totalCoin += 0.25;
			encoderReverse = 775;
		}
		else if (NICKEL_MIN < encoderValue && encoderValue < NICKEL_MAX)
		{
			totalCoin += 0.05;
			encoderReverse = 550;
		}

		else if (DIME_MIN < encoderValue && encoderValue < DIME_MAX)
		{
			totalCoin += 0.1;
			encoderReverse = 375;
		}
		//Exits if there are no more coins
		else if (encoderValue > NO_COIN_MAX && totalCoin >= payTotal)
		{
			moreCoins = false;
		}

		//Updates the payment systems
		if (totalCoin < 0)
			displayPayment(payTotal, 0);
		else
			displayPayment(payTotal, totalCoin);

		//Drops coin and reset coin measurement system
		motor[motorD] = -75;
		while(nMotorEncoder[motorD] > -encoderReverse)
		{}
		motor[motorD] = 75;
		while (nMotorEncoder[motorD] < 0)
		{}
		motor[motorD] = 0;
	}
	return totalCoin;
}
//############################End of Coin Sorting Programs##################################
