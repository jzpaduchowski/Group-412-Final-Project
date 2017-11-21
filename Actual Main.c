




const int menuEmpty = 0;
const int menuCoffee = 1;
const int menuTea = 2;
const int menuMilks = 3;
const int orderFailed = -1;
const int orderSuccess = 0;
const float coffeePrice = 1.5;
const float teaPrice = 1.5;





/*
Port Configuration:
A - Cart Belt
B - Valves
C - Coin Wheel
D - Coin Measurement
1 - Cup Colour
2 - Coin touch sensor
*/


//############################Start of Coin Sorting Programs##################################
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



		motor[motorC] = 60;
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
//############################End of Coin Sorting Programs##################################












//############################Start of Order Processing Programs##################################
void displayCoffeeTea(int numCoffee, int numTea, int drinkType)
{

	if (drinkType == menuCoffee)
		drawBmpfile(0, 127, "menuCoffee");
	else if (drinkType == menuTea)
		drawBmpfile(0, 127, "menuTea");

	displayBigStringAt(150, 65, "%d", numCoffee);
	displayBigStringAt(150, 28, "%d", numTea);
}

void displayMilks(int numMilks, int drinkType, int drinkNum)
{

	drawBmpfile(0, 127, "menuGetMilks");

	if (drinkType == menuCoffee)
		displayBigStringAt(5, 33, "Coffee %d", drinkNum);
	else if (drinkType == menuTea)
		displayBigStringAt(5, 33, "Tea %d", drinkNum);

	displayBigStringAt(152, 30, "%d", numMilks);
}


void displayPayment(float orderCost)
{

	drawBmpfile(0, 127, "menuEmpty");

	if (orderCost == orderFailed)
		displayBigTextLine(7, "You did not put in enough coins!");
	else if (orderCost == orderSuccess)
	{
		displayCenteredBigTextLine(6, "Order Success!");
		displayCenteredBigTextLine(9, "Thank you!");
	}
	else
	{
		displayCenteredBigTextLine(6,"Order Total: ");
		displayCenteredBigTextLine(9, "$%.2f", orderCost);
		displayCenteredBigTextLine(12, "Please Pay Now.");
	}
}


void displayPayment(float orderCost, float coinsInserted)
{

	drawBmpfile(0, 127, "menuEmpty");
	displayCenteredBigTextLine(6,"Order Total: ");
	displayCenteredBigTextLine(9, "$%.2f", orderCost);
	displayCenteredBigTextLine(12, "Coins Left: $%.2f", orderCost);

}
//############################End of Order Processing Programs##################################



//############################Start of Main##################################
task main()
{

	SensorType[S2] = sensorEV3_Touch;


	initializeCoinSorter();

	int numTea = 0;
	int numCoffee = 0;
	int selection = menuCoffee;
	int numMilkCoffee[5] = {0, 0, 0, 0, 0};
	int numMilkTea[5] = {0, 0, 0, 0, 0};
	float total = 0;

	displayCoffeeTea(numCoffee, numTea, menuCoffee);
	while (!getButtonPress(buttonEnter))
	{

		while (getButtonPress(buttonAny));
		while (!getButtonPress(buttonAny));

		if (getButtonPress(buttonUp))
			selection = menuCoffee;
		else if (getButtonPress(buttonDown))
			selection = menuTea;

		if (selection == menuCoffee)
		{

			if (getButtonPress(buttonRight))
			{
				if ((numCoffee + numTea) < 5)
					++numCoffee;
			}
			else if (getButtonPress(buttonLeft))
			{
				if (numCoffee > 0)
					--numCoffee;
			}

			displayCoffeeTea(numCoffee, numTea, menuCoffee);
		}
		else if (selection == menuTea)
		{

			if (getButtonPress(buttonRight))
			{
				if ((numCoffee + numTea) < 5)
					++numTea;
			}
			else if (getButtonPress(buttonLeft))
			{
				if (numTea > 0)
					--numTea;
			}

			displayCoffeeTea(numCoffee, numTea, menuTea);

		}
	}

	while(getButtonPress(buttonAny));


	for (int coffeeCount = 0; coffeeCount < numCoffee; coffeeCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			displayMilks(numMilkCoffee[coffeeCount], menuCoffee, (coffeeCount + 1));
			while (getButtonPress(buttonAny));
			while (!getButtonPress(buttonAny));

			if (getButtonPress(buttonRight))
			{
				if (numMilkCoffee[coffeeCount] < 5)
					++numMilkCoffee[coffeeCount];
			}
			else if (getButtonPress(buttonLeft))
			{
				if (numMilkCoffee[coffeeCount] > 0)
					--numMilkCoffee[coffeeCount];
			}
		}
		while (getButtonPress(buttonAny));
	}

	for (int teaCount = 0; teaCount < numTea; teaCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			displayMilks(numMilkTea[teaCount], menuTea, (teaCount + 1));
			while (getButtonPress(buttonAny));
			while (!getButtonPress(buttonAny));

			if (getButtonPress(buttonRight))
			{
				if (numMilkTea[teaCount] < 5)
					++numMilkTea[teaCount];
			}
			else if (getButtonPress(buttonLeft))
			{
				if (numMilkTea[teaCount] > 0)
					--numMilkTea[teaCount];
			}
		}
		while (getButtonPress(buttonAny));
	}

	total = (numCoffee * coffeePrice + numTea * teaPrice);

	displayPayment(total);


	///////////////////////////////////Coin Sorting


	float drinkCost = 0;
	float totalCoin = 0;

	while (totalCoin < total)
	{
		totalCoin += countCoins();
		displayPayment(total, totalCoin);
	}

	displayPayment(orderSuccess);

	//////////////////////////////////////End Coin sorting

	//else (payment == orderFailed);
	//displayPayment(orderFailed);

	while (!getButtonPress(buttonAny));
	while (getButtonPress(buttonAny));

}
