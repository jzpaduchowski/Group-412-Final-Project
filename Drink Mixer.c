//Merge all functions related to valve and cart control here pls


/*
-------------------------------CONSTANTS--------------------------------------
*/
const int speed = 25; //Desired speed of the cup
const int drink = 1; //General drink assignment
const int drink1 = 0; //Position of drink 1
const int drink2 = 110; //Position of drink 2
const int drink3 = 220; //Position of drink 3
const int cup = 440; //Position of cup dispenser
const int cupDelivery = 750; //Position to deliver the cup
const string cupFell = "The cup fell!";
const string noCups = "No more cups!";
const float FLOWRATE = 1.0; //mL/s
//place any constants here pls


void errorMessage(const string errorCode)
{
	displayCenteredBigTextLine(3, "ERROR!");
	displayCenteredBigTextLine(6, "%s", errorCode);
	displayCenteredTextLine(9, "Press a button to resolve");

	while (!getButtonPress(buttonAny));
	while (getButtonPress(buttonAny));
}

void updateDisplay()
{
	displayBigTextLine(6, "%d", nMotorEncoder[motorA]);
}

void wait4Button()
{
	wait1Msec(750);
}

void goTo(int pos)
{
	int direction = 1;

	if (pos < nMotorEncoder[motorA])
		direction = -1;

	motor[motorA] = speed * direction;
	while (abs(nMotorEncoder[motorA] - pos) > speed * 2)
		updateDisplay();

  //Impementing slow stopping
	while ((abs(nMotorEncoder[motorA] - pos) / 2) < speed * 2 + 5 && abs(nMotorEncoder[motorA] - pos) >= 2)
	{
		motor[motorA] = (1.0 * pos - nMotorEncoder[motorA]) / 2;
		updateDisplay();
	}
	motor[motorA] = 0;
}

void valveControl(int valveType, int valvePos)
{
	updateDisplay();

	goTo(valvePos);

	//Operates the drink valve if the cup is there
	if (valveType == drink && SensorValue[S1] != 0)
	{
		displayTextLine(9, "Drink");

		motor[motorB] = 33;
		while(nMotorEncoder[motorB] < 200);
		motor[motorB] = 0;

		clearTimer(T1);
		while (time1[T1] < 3500 && SensorValue[S1] != 0);

		motor[motorB] = -33;
		while(nMotorEncoder[motorB] > -8);
		motor[motorB] = 15;
		while(nMotorEncoder[motorB] < 0);
		motor[motorB] = 0;

		if (SensorValue[S1] == 0)
		{
			errorMessage(cupFell);
			wait4Button();
			valveControl(cup, cup);
			wait4Button();
			valveControl(valveType, valvePos);
		}
	}
	else if (valveType == cup)
	{
		displayTextLine(9, "Cup");

		motor[motorB] = -33;
		while(nMotorEncoder[motorB] > -100);
		motor[motorB] = 0;

		wait1Msec(500);

		motor[motorB] = 33;
		while(nMotorEncoder[motorB] < 20);
		motor[motorB] = -20;
		while(nMotorEncoder[motorB] > 0);
		motor[motorB] = 0;

		if (SensorValue[S1] == 0)
		{
				errorMessage(noCups);
				wait4Button();
				valveControl(cup, cup);
		}
	}

}

//receives array with menu selections and calculates the amount of time each valve should be open for in milliseconds
float drinkVolume(int numMainDrink, int numMilks)
{
	if(numMainDrink == 1)
	{
		return (numMainDrink * FLOWRATE * 1000 * 350) - (numMilks * FLOWRATE * 1000 * 10);
	}
	else
	{
		return (numMilks * FLOWRATE * 1000 * 10);
	}
}
