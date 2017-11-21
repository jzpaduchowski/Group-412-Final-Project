const int menuEmpty = 0;
const int menuCoffee = 1;
const int menuTea = 2;
const int menuMilks = 3;
const int orderFailed = -1;
const int orderSuccess = 0;



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


void displayPayment(int orderCost)
{

	drawBmpfile(0, 127, "menuEmpty");

	if (orderCost == orderFailed)
		displayBigTextLine(5, "You did not put in enough coins!");
	else if (orderCost == orderSuccess)
	{
		displayBigTextLine(5, "Order Success!");
		displayBigTextLine(8, "Thank you!");
	}
	else
	{
		drawBmpfile(5, 33, "Order Total: ");
		displayBigTextLine(8, "XXXX");

	}

}


task main()
{
	int numTea = 0;
	int numCoffee = 0;
	int selection = menuCoffee;
	int numMilkCoffee[5] = {0, 0, 0, 0, 0};
	int numMilkTea[5] = {0, 0, 0, 0, 0};

	displayCoffeeTea(numCoffee, numTea, menuCoffee);
	displayBigTextLine(1, "FFFFF");

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
				if (numCoffee < 5)
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
				if (numTea < 5)
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

	displayBigTextLine(4, "FFFFF");


	for (int coffeeCount = 0; coffeeCount < numCoffee; coffeeCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			displayMilks(numMilkCoffee[coffeeCount], menuCoffee, (coffeeCount + 1));
			while (getButtonPress(buttonAny));
			while (!getButtonPress(buttonAny));

			if (getButtonPress(buttonRight))
				if (numMilkCoffee[coffeeCount] < 5)
				++numMilkCoffee[coffeeCount];
			else if (getButtonPress(buttonLeft))
				if (numMilkCoffee[coffeeCount] > 0)
				--numMilkCoffee[coffeeCount];
		}
		while(getButtonPress(buttonAny));
	}

	for (int teaCount = 0; teaCount < numTea; teaCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			displayMilks(numMilkTea[teaCount], menuTea, (teaCount + 1));
			while (getButtonPress(buttonAny));
			while (!getButtonPress(buttonAny));

			if (getButtonPress(buttonRight))
				if (numMilkTea[teaCount] < 5)
				++numMilkTea[teaCount];
			else if (getButtonPress(buttonLeft))
				if (numMilkTea[teaCount] > 0)
				--numMilkTea[teaCount];
		}
		while(getButtonPress(buttonAny));
	}

	displayBigTextLine(6, "GGGGG");

	wait10Msec(1000);



}
