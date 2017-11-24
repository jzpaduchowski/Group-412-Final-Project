const int MENU_EMPTY = 0;
const int MENU_COFFEE = 1;
const int MENU_TEA = 2;
const int MENU_MILKS = 3;
const int ORDER_FAILED = -1;
const int ORDER_SUCCESS = 0;
const float COFFEE_PRICE = 1.5;
const float TEA_PRICE = 1.5;
const int COFFEE_TYPE = 0;
const int TEA_TYPE = 220;


//############################Start of Order Processing Programs##################################
//Displays user's selection on how many coffees or teas
void displayCoffeeTea(int numCoffee, int numTea, int drinkType)
{

	if (drinkType == MENU_COFFEE)
		drawBmpfile(0, 127, "menuCoffee");
	else if (drinkType == MENU_TEA)
		drawBmpfile(0, 127, "menuTea");

	displayBigStringAt(150, 65, "%d", numCoffee);
	displayBigStringAt(150, 28, "%d", numTea);
}

//For displaying the number of milks selected for a particular drink
void displayMilks(int numMilks, int drinkType, int drinkNum)
{

	drawBmpfile(0, 127, "menuGetMilks");

	if (drinkType == MENU_COFFEE)
		displayBigStringAt(5, 33, "Coffee %d", drinkNum);
	else if (drinkType == MENU_TEA)
		displayBigStringAt(5, 33, "Tea %d", drinkNum);

	displayBigStringAt(152, 30, "%d", numMilks);
}


void displayPayment(float orderCost)
{

	drawBmpfile(0, 127, "menuEmpty");

	if (orderCost == ORDER_FAILED)
		displayBigTextLine(7, "You did not put in enough coins!");
	else if (orderCost == ORDER_SUCCESS)
	{
		displayCenteredBigTextLine(6, "Order Success!");
		displayCenteredBigTextLine(9, "Making order...");
	}
	else
	{
		displayCenteredBigTextLine(6,"Order Total: ");
		displayCenteredBigTextLine(9, "$%.2f", orderCost);
		displayCenteredBigTextLine(12, "Please Pay Now.");
	}
}

//Displays the payment and value of coins inserted
void displayPayment(float orderCost, float coinsInserted)
{

	drawBmpfile(0, 127, "menuEmpty");
	displayCenteredBigTextLine(6,"Order Total: ");
	displayCenteredBigTextLine(9, "$%.2f", orderCost);
	displayCenteredBigTextLine(12, "Owing: $%.2f", (orderCost - coinsInserted);

}

void dispProgress(int drink, int drinkNum)
{


		drawBmpfile(0, 127, "menuEmpty");
		displayCenteredBigTextLine(6,"Now Preparing:");
		if (drink == COFFEE_TYPE)
			displayCenteredBigTextLine(9, "Coffee %d", drinkNum);
		else if (drink == TEA_TYPE)
			displayCenteredBigTextLine(9, "Tea %d", drinkNum);

}

void dispIsReady()
{

		displayCenteredBigTextLine(6,"Please take:");
}


void endCustomer()
{

	drawBmpfile(0, 127, "menuEmpty");
	displayCenteredBigTextLine(8,"Thank you!");
	displayCenteredBigTextLine(11, "Goodbye!");

}




bool getDrinkSelections(int & numCoffee, int & numTea)
{
	int selection = MENU_COFFEE;
	bool isQuit = false;

	displayCoffeeTea(numCoffee, numTea, MENU_COFFEE);
	while ((!getButtonPress(buttonEnter) || ((numCoffee + numTea) < 1)) && !isQuit )
	{

		while (getButtonPress(buttonAny) && !(getButtonPress(buttonUp) && getButtonPress(buttonDown)));

		if (getButtonPress(buttonUp) && getButtonPress(buttonDown))
		{
			isQuit = true;
		}
		while (!getButtonPress(buttonAny) && !isQuit);


		if (getButtonPress(buttonUp))
			selection = MENU_COFFEE;
		else if (getButtonPress(buttonDown))
			selection = MENU_TEA;

		if (selection == MENU_COFFEE)
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

			displayCoffeeTea(numCoffee, numTea, MENU_COFFEE);
		}
		else if (selection == MENU_TEA)
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

			displayCoffeeTea(numCoffee, numTea, MENU_TEA);

		}
	}
	while(getButtonPress(buttonAny));

	return isQuit;
}

void getMilkSelections(int numCoffee, int numTea, int* numMilkCoffee, int* numMilkTea)
{

	for (int coffeeCount = 0; coffeeCount < numCoffee; coffeeCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			displayMilks(numMilkCoffee[coffeeCount], MENU_COFFEE, (coffeeCount + 1));
			while (getButtonPress(buttonAny));
			while (!getButtonPress(buttonAny));

			if (getButtonPress(buttonRight) || getButtonPress(buttonUp))
			{
				if (numMilkCoffee[coffeeCount] < 5)
					++numMilkCoffee[coffeeCount];

			}
			else if (getButtonPress(buttonLeft) || getButtonPress(buttonDown))
			{
				if (numMilkCoffee[coffeeCount] > 0)
					--numMilkCoffee[coffeeCount];
			}
		}

		if (numMilkCoffee[coffeeCount] == 5)
		{
			playSoundFile("Okey-dokey");
			sleep(800);
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
		if (numMilkTea[teaCount] == 5)
		{
			playSoundFile("Okey-dokey");
			sleep(800);
		}
		while (getButtonPress(buttonAny));
	}
}

//############################End of Order Processing Programs##################################
