const int coffee = 1;
const int tea = 2;


void updateDisplay(int numCoffee, int numTea, int drink)
{
	//eraseDisplay();

	if (drink == coffee)
		drawBmpfile(0, 127, "menuCoffee");
	else if (drink == tea)
		drawBmpfile(0, 127, "menuTea");

	displayBigStringAt(150, 64, "%d", numCoffee);
	displayBigStringAt(150, 27, "%d", numTea);

}


task main()
{
	//int numMilk = 0;
	int numTea = 0;
	int numCoffee = 0;
	int selection = coffee;

	updateDisplay(numCoffee, numTea, coffee);

	while (!getButtonPress(buttonAny));

	while (!getButtonPress(buttonEnter))
	{

		while (!getButtonPress(buttonAny));

		if (getButtonPress(buttonUp))
			selection = coffee;
		else if (getButtonPress(buttonDown))
			selection = tea;

		if (selection == coffee)
		{
			if (getButtonPress(buttonRight))
				if (numCoffee < 9)
					numCoffee++;
			else if (getButtonPress(buttonLeft))
			{
				if (numCoffee > 0)
					numCoffee--;
			}

			updateDisplay(numCoffee, numTea, coffee);

		}
		else if (selection == tea)
		{

			if (getButtonPress(buttonRight))
				if (numTea < 9)
					numTea++;
			else if (getButtonPress(buttonLeft))
			{
				if (numTea > 0)
					numTea--;
			}

			updateDisplay(numCoffee, numTea, tea);

		}

		while (getButtonPress(buttonAny));
	}


}
