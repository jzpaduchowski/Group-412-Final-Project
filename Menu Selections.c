const int MENU_EMPTY = 0;
const int MENU_COFFEE = 1;
const int MENU_TEA = 2;
const int MENU_MILKS = 3;
const int ORDER_FAILED = -1;
const int ORDER_SUCCESS = 0;
const float COFFEE_PRICE = 1.5;
const float TEA_PRICE = 1.5;


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
		displayCenteredBigTextLine(9, "Thank you!");
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
	displayCenteredBigTextLine(12, "Coins Left: $%.2f", orderCost);

}
//############################End of Order Processing Programs##################################
