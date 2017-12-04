const int MENU_COFFEE = 1; //These were used before we knew about enumerators
const int MENU_TEA = 2;
const int ORDER_FAILED = -100;
const int ORDER_SUCCESS = -99;
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

//Shows order progress
void displayPayment(float orderCost)
{
	drawBmpfile(0, 127, "menuEmpty");

	//Checks if the order had failed
	if (orderCost == ORDER_FAILED)
		displayBigTextLine(7, "You did not put in enough coins!");
	//Shows the order success
	else if (orderCost == ORDER_SUCCESS)
	{
		displayCenteredBigTextLine(6, "Order Success!");
		displayCenteredBigTextLine(9, "Making order...");
	}
	//Shows the order cost before getting coins
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
	//Shows order cost
	drawBmpfile(0, 127, "menuEmpty");
	displayCenteredBigTextLine(6,"Order Total: ");
	displayCenteredBigTextLine(9, "$%.2f", orderCost);

	//Shows the amount of money remaining
	if ((orderCost - coinsInserted) < 0)
	{
		displayCenteredBigTextLine(12, "Owing: $%.2f", 0);
	}
	else
	{
		displayCenteredBigTextLine(12, "Owing: $%.2f", (orderCost - coinsInserted));
	}
}

//Shows which drink is being made at the current time
void dispProgress(int drink, int drinkNum)
{
	drawBmpfile(0, 127, "menuEmpty");
	displayCenteredBigTextLine(6,"Now Preparing:");
	if (drink == COFFEE_TYPE)
		displayCenteredBigTextLine(9, "Coffee %d", drinkNum);
	else if (drink == TEA_TYPE)
		displayCenteredBigTextLine(9, "Tea %d", drinkNum);
}

//Alerts the user and shows that their drink is ready.
void dispIsReady()
{
	playSoundFile("Confirm");
	displayCenteredBigTextLine(6,"Please take:");
}

//Showing end protocols to end the user
void endCustomer()
{
	drawBmpfile(0, 127, "menuEmpty");
	displayCenteredBigTextLine(8,"Thank you!");
	displayCenteredBigTextLine(11, "Goodbye!");
}

//Gets the user's drink selections for number of cofee and tea
bool getDrinkSelections(int & numCoffee, int & numTea)
{
	int selection = MENU_COFFEE;
	bool isQuit = false;

	//Displays the selection and the number of drinks
	displayCoffeeTea(numCoffee, numTea, MENU_COFFEE);

	//Stays on selection while the user does not press the enter button to confirm, and the operators do not quit the robot.
	while ((!getButtonPress(buttonEnter) || ((numCoffee + numTea) < 1)) && !isQuit )
	{
		//Stays on a button press and checks for button and button down presses
		while (getButtonPress(buttonAny) && !(getButtonPress(buttonUp) && getButtonPress(buttonDown)))
		{}

		//Sets the quitting flag to true
		if (getButtonPress(buttonUp) && getButtonPress(buttonDown))
		{
			isQuit = true;
		}

		//Waits for the user to click a button
		while (!getButtonPress(buttonAny) && !isQuit)
		{}

		//Checks to see if the button pressed were for changing the selections
		if (getButtonPress(buttonUp))
			selection = MENU_COFFEE;
		else if (getButtonPress(buttonDown))
			selection = MENU_TEA;

		//Increases or decreases the quantity of coffee
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

			//Updates the display
			displayCoffeeTea(numCoffee, numTea, MENU_COFFEE);
		}
		else if (selection == MENU_TEA)
		{
			//Increments or decrements the quantity of tea
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

			//Updates display
			displayCoffeeTea(numCoffee, numTea, MENU_TEA);

		}
	}
	while(getButtonPress(buttonAny))
	{}

	//Returns if the operator wanted to quit or not
	return isQuit;
}

//Gets the amount of milk from the customer for each drink
void getMilkSelections(int numCoffee, int numTea, int* numMilkCoffee, int* numMilkTea)
{

	for (int coffeeCount = 0; coffeeCount < numCoffee; coffeeCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			//Shows amount of milk
			displayMilks(numMilkCoffee[coffeeCount], MENU_COFFEE, (coffeeCount + 1));

			while (getButtonPress(buttonAny))
			{}
			while (!getButtonPress(buttonAny))
			{}

			//Increments the number of milks
			if (getButtonPress(buttonRight) || getButtonPress(buttonUp))
			{
				if (numMilkCoffee[coffeeCount] < 5)
					++numMilkCoffee[coffeeCount];

			}
			//Decrements number of milks
			else if (getButtonPress(buttonLeft) || getButtonPress(buttonDown))
			{
				if (numMilkCoffee[coffeeCount] > 0)
					--numMilkCoffee[coffeeCount];
			}
		}

		//Easter egg
		if (numMilkCoffee[coffeeCount] == 5)
		{
			playSoundFile("Okey-dokey");
			sleep(800);
		}

		while (getButtonPress(buttonAny))
		{}
	}

	//Gets number of tea for each tea
	for (int teaCount = 0; teaCount < numTea; teaCount++)
	{
		while(!getButtonPress(buttonEnter))
		{
			//Displays the number of milks requested
			displayMilks(numMilkTea[teaCount], MENU_TEA, (teaCount + 1));

			while (getButtonPress(buttonAny))
			{}
			while (!getButtonPress(buttonAny))
			{}

			//Increments and decrements the number of milks
			if (getButtonPress(buttonRight) || getButtonPress(buttonUp))
			{
				if (numMilkTea[teaCount] < 5)
					++numMilkTea[teaCount];
			}
			else if (getButtonPress(buttonLeft) || getButtonPress(buttonDown))
			{
				if (numMilkTea[teaCount] > 0)
					--numMilkTea[teaCount];
			}
		}
		if (numMilkTea[teaCount] == 5)
		{
			playSoundFile("Okey-dokey");
		}
		while (getButtonPress(buttonAny))
		{}
	}
}
//############################End of Order Processing Programs##################################
