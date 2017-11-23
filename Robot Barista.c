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
	setSoundVolume(75);

	setLEDColor(ledOff);


	//initializeCoinSorter();

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


	while (isNotQuit)
	{
		for (int index = 0; index < 5; index++)
		{
			numMilkCoffee[index] = 0;
			numMilkTea[index] = 0;
		}

		numTea = 0;
		numCoffee = 0;

		drinkCost = 0;
		totalCoin = 0;

		if (!getDrinkSelections(numCoffee, numTea))
		{
			getMilkSelections(numCoffee, numTea, numMilkCoffee, numMilkTea);


			total = (numCoffee * COFFEE_PRICE + numTea * TEA_PRICE);

			while(getButtonPress(buttonAny));

			displayPayment(total);

			while(!getButtonPress(buttonAny));
			while(getButtonPress(buttonAny));

			///////////////////////////////////Coin Sorting
			/*


			while (totalCoin < total)
			{
				totalCoin += countCoins(total);
				displayPayment(total, totalCoin);
			}

			displayPayment(ORDER_SUCCESS);

			*/
			//////////////////////////////////////End Coin sorting

			for (int coffeeCount = 0; coffeeCount < numCoffee; coffeeCount++)
			{
				dispProgress(false, COFFEE_TYPE, coffeeCount + 1);
				cartControl(COFFEE_TYPE, numMilkCoffee[coffeeCount]);
				dispProgress(true, COFFEE_TYPE, coffeeCount + 1);
			}

			for (int teaCount = 0; teaCount < numTea; teaCount++)
			{
				dispProgress(false, TEA_TYPE, teaCount + 1);
				cartControl(TEA_TYPE, numMilkTea[teaCount]);
				dispProgress(true, TEA_TYPE, teaCount + 1);
			}

			endCustomer();

		}
		else
		{
			isNotQuit = false;

			endCustomer();

			goTo(0);
		}




	}
}
