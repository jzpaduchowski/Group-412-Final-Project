#include "Menu Selections.c"
#include "Coin Sorter.c"
#include "Drink Mixer.c"

/*
Port Configuration:
A - Cart Belt
B - Valves
C - Coin Wheel
D - Coin Measurement
1 - Cup Colour
4 - Coin touch sensor
*/

//############################Start of Main##################################
task main()
{
	//Initialization for all used variables
	setSoundVolume(75);

	setLEDColor(ledOff);

	SensorType[S1] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1] = modeEV3Color_Color;
	wait1Msec(50);

	SensorType[S2] = sensorEV3_Touch;

	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorD] = 0;

	int numTea = 0;
	int numCoffee = 0;
	float total = 0;

	float drinkCost = 0;
	float totalCoin = 0;

	int numMilkCoffee[5];
	int numMilkTea[5];
	int isNotQuit = true;

	initializeCoinSorter();
	calibrateCart();

	//The robot will always be avaliable for serving drinks as long as the operators choose.
	while (isNotQuit)
	{

		//Resets variables for each new customer
		for (int index = 0; index < 5; index++)
		{
			numMilkCoffee[index] = 0;
			numMilkTea[index] = 0;
		}

		numTea = 0;
		numCoffee = 0;

		drinkCost = 0;
		totalCoin = 0;

		//Gets drink selections selection from the customer
		if (!getDrinkSelections(numCoffee, numTea))
		{
			//Gets milk selections if avaliable
			getMilkSelections(numCoffee, numTea, numMilkCoffee, numMilkTea);

			//Calculates the total to get the cost
			total = (numCoffee * COFFEE_PRICE + numTea * TEA_PRICE);

			while(getButtonPress(buttonAny))
			{}

			//Displays the payment amount for the customer
			displayPayment(total);

			//Counts and calculates the money input by the user
			while (totalCoin < total)
			{
				totalCoin += countCoins(total);

				displayPayment(total, totalCoin);
			}

			//Shows that the order was a success
			displayPayment(ORDER_SUCCESS);
			wait1Msec(2000);

			//Starts making all the coffees while there are still more to make
			for (int coffeeCount = 0; coffeeCount < numCoffee; coffeeCount++)
			{
				//Shows progress on which coffee is being made
				dispProgress(COFFEE_TYPE, coffeeCount + 1);
				//Gets the drink specified
				cartControl(COFFEE_TYPE, numMilkCoffee[coffeeCount]);
			}

			//Makes all teas
			for (int teaCount = 0; teaCount < numTea; teaCount++)
			{
				//Shows progress on which coffee is being made
				dispProgress(TEA_TYPE, teaCount + 1);
				//Gets the drink specified
				cartControl(TEA_TYPE, numMilkTea[teaCount]);
			}

			//Displays thank you message
			endCustomer();

		}
		else
		{
			//Clean exiting protocols
			isNotQuit = false;

			//Ending message
			endCustomer();

			//Sets the cart to proper initializing position
			goTo(20);
		}
	}
}
