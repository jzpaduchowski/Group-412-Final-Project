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

	initializeCoinSorter();

	int numTea = 0;
	int numCoffee = 0;

	int numMilkCoffee[5] = {0, 0, 0, 0, 0};
	int numMilkTea[5] = {0, 0, 0, 0, 0};
	float total = 0;

	getDrinkSelections(numTea, numCoffee);
	getMilkSelections(numTea, numCoffee, numMilkCoffee, numMilkTea);


	total = (numCoffee * COFFEE_PRICE + numTea * TEA_PRICE);

	displayPayment(total);


	///////////////////////////////////Coin Sorting


	float drinkCost = 0;
	float totalCoin = 0;

	while (totalCoin < total)
	{
		totalCoin += countCoins(total);
		displayPayment(total, totalCoin);
	}

	displayPayment(ORDER_SUCCESS);

	//////////////////////////////////////End Coin sorting

	//else (payment == orderFailed);
	//displayPayment(orderFailed);

	while (!getButtonPress(buttonAny));
	while (getButtonPress(buttonAny));

}
