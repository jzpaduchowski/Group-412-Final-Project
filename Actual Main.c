#include "Coin Sorter.c"
#include "Menu Selections.c"
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


	initializeCoinSorter();

	int numTea = 0;
	int numCoffee = 0;
	int selection = MENU_COFFEE;
	int numMilkCoffee[5] = {0, 0, 0, 0, 0};
	int numMilkTea[5] = {0, 0, 0, 0, 0};
	float total = 0;

	getDrinkSelections();


	for (int coffeeCount = 0; coffeeCount < numCoffee; coffeeCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			displayMilks(numMilkCoffee[coffeeCount], MENU_COFFEE, (coffeeCount + 1));
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
			displayMilks(numMilkTea[teaCount], MENU_TEA, (teaCount + 1));
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

	total = (numCoffee * COFFEE_PRICE + numTea * TEA_PRICE);

	displayPayment(total);


	///////////////////////////////////Coin Sorting


	float drinkCost = 0;
	float totalCoin = 0;

	while (totalCoin < total)
	{
		totalCoin += countCoins();
		displayPayment(total, totalCoin);
	}

	displayPayment(ORDER_SUCCESS);

	//////////////////////////////////////End Coin sorting

	//else (payment == orderFailed);
	//displayPayment(orderFailed);

	while (!getButtonPress(buttonAny));
	while (getButtonPress(buttonAny));

}
