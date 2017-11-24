//Merge all functions related to valve and cart control here pls


/*
-------------------------------CONSTANTS--------------------------------------
*/
const int CART_SPEED = 25; //Desired speed of the cup cart
const int DRINK_TYPE = 1;
//const int COFFEE_TYPE = 0; //Declared in previous file
//const int TEA_TYPE = 220;
const int MILK_TYPE = 110; //Position of milk location
const int CUP_POS = 440; //Position of cup dispenser
const int CUP_DELIVERY_POS = 750; //Position to deliver the cup
string CUP_FELL_ERROR = "The cup fell!";
string NO_CUP_ERROR = "No more cups!";
string CUP_EXISTS_ERROR = "Cup exists!";
string CUP_CART_FELL = "Cart is off the track!";

const float FLOWRATE_DRINK = 23.33; //mL/s
const float FLOWRATE_MILK = 8; //mL/s
const int OPEN_POS = 1;
const int CLOSE_POS = -1;
const int GOTO_ERROR = 1;
const int GETCUP_ERROR = 2;
const int CARTCONTROL_ERROR = 3;

//place any constants here pls



void goTo(int pos);
void getCup();
void cartControl(int drinkSelect, int numMilk);



void wait4Button()
{
	while (!getButtonPress(buttonAny));
	while (getButtonPress(buttonAny));
}

void errorMessage(string errorCode)
{

	playSoundFile("Ouch");

	displayCenteredTextLine(13, "ERROR!");
	displayCenteredTextLine(14, "%s", errorCode);
	displayCenteredTextLine(15, "Press to resolve");

	wait4Button();
	displayTextLine(13, " ");
	displayTextLine(14, " ");
	displayTextLine(15, " ");

}

//receives array with menu selections and calculates the amount of time each valve should be open for in milliseconds
float pourTime(int valveType, int numMilks)
{
	int timeToPour = 0;

	if (valveType == DRINK_TYPE)
	{
		//Returns the time it takes to fill a cup with drink according to equation:
		//time = flowrate (in ml/s) * 1000ms * 350ml - numMilks * 1000ms * 10ml
		timeToPour = ((350.0 - (numMilks * 10))* 1000.0) / FLOWRATE_DRINK;
	}
	else if (numMilks > 0)
	{
		//Calculates the time to pour specified amount of milk
		timeToPour = ((numMilks * 10 * 1000.0) / FLOWRATE_MILK);
	}
	return timeToPour;
}

void detectCupError (int errorProtocol)
{
	if (SensorValue[S1] == 0)
	{
		if (errorProtocol == GETCUP_ERROR)
		{
			errorMessage(NO_CUP_ERROR);
			getCup();
		}
	}
}


void detectCupError (int errorProtocol, int pos)
{
	if (SensorValue[S1] == 0)
	{
		if (errorProtocol == GOTO_ERROR)
		{
			errorMessage(CUP_FELL_ERROR);
			goTo(pos);
		}
	}
}

void detectCupError (int errorProtocol, int drinkSelect, int numMilks)
{
	if (SensorValue[S1] == 0)
	{
		if (errorProtocol == CARTCONTROL_ERROR)
		{
			errorMessage(CUP_FELL_ERROR);

			//Gets the new drink again
			cartControl(drinkSelect, numMilks);
		}
	}
}

void goTo(int pos)
{
	//Sets the direction to go backwards or forwards
	int direction = 1;

	bool hasCup = true;

	if (pos < nMotorEncoder[motorA])
		direction = -1;


	if (SensorValue[S1] == 0)
	{
		hasCup = false;
	}

	clearTimer(T2);
	int currentTime = time1(T2);
	motor[motorA] = CART_SPEED * direction;

	while (abs(nMotorEncoder[motorA] - pos) > CART_SPEED * 2 && !(SensorValue[S1] == 0 && hasCup))
	{

		if(((time1(T2) - currentTime) > 500))
		{

			int currentEnc = nMotorEncoder[motorA];

			if(abs(currentEnc - tempEnc) < 5)
			{
				motor[motorA] = 0;
				errorMessage(CUP_CART_FELL);
				while(1 < 2)
				{} //Fatal error needs human intervention so we go into an infinite loop and wait
			}

			int tempTime = currentTime;
			int tempEnc = nMotorEncoder[motorA];
			clearTimer(T2);
		}
	}

	//Impementing slow stopping
	while ((abs(nMotorEncoder[motorA] - pos) / 2) < CART_SPEED * 2 + 5 && abs(nMotorEncoder[motorA] - pos) > 1 && !(SensorValue[S1] == 0 && hasCup))
	{
		motor[motorA] = (1.0 * pos - nMotorEncoder[motorA]) / 2;
	}
	motor[motorA] = 0;

	if (false && hasCup)
		detectCupError(GOTO_ERROR, pos);

}


void operateValve(int toOpen, int valveType)
{
	if (toOpen == OPEN_POS)
	{
		if (valveType	== DRINK_TYPE)
		{
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 200);
			motor[motorB] = 0;

		}
		else if (valveType == MILK_TYPE)
		{
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 135);
			motor[motorB] = 0;
		}
		else if (valveType == CUP_POS)
		{
			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -100);
			motor[motorB] = 0;
		}
	}
	else if (toOpen == CLOSE_POS)
	{
		if (valveType	== DRINK_TYPE)
		{

			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -8);
			motor[motorB] = 15;
			while(nMotorEncoder[motorB] < 0);
			motor[motorB] = 0;
		}
		else if (valveType == MILK_TYPE)
		{
			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -10);
			motor[motorB] = 15;
			while(nMotorEncoder[motorB] < 0);
			motor[motorB] = 0;
		}
		else 	if (valveType	== CUP_POS)
		{
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 20);
			motor[motorB] = -25;
			while(nMotorEncoder[motorB] > 0);
			motor[motorB] = 0;
		}
	}
}


void getCup()
{
	goTo(CUP_POS);

	if (SensorValue[S1] != 0)
	{

		errorMessage(CUP_EXISTS_ERROR);
		goTo(CUP_DELIVERY_POS);
		while (SensorValue[S1] != 0);
		wait1Msec(1000);
		goTo(CUP_POS);

	}

	operateValve(OPEN_POS, CUP_POS);
	wait1Msec(250);
	operateValve(CLOSE_POS, CUP_POS);

	wait1Msec(250);
	detectCupError(GETCUP_ERROR);
}



//This is the main drink preparation function. Given the drink type and number of milks, the robot will go and prepare that drink.
void cartControl(int drinkSelect, int numMilk)
{

	getCup();

	goTo(drinkSelect);

	float timeToPourDrink = pourTime(DRINK_TYPE, numMilk);
	float timeToPourMilk = pourTime(0, numMilk);

	//Operates the drink valve if the cup is there
	if ((drinkSelect == COFFEE_TYPE || drinkSelect == TEA_TYPE) && SensorValue[S1] != 0)
	{
		clearTimer(T1);
		operateValve(OPEN_POS, DRINK_TYPE);
		//Waits while the valve is open for specified amount of time given the flow rate required

		while (time1[T1] < 18000 && time1[T1] < timeToPourDrink && SensorValue[S1] != 0);
		operateValve(CLOSE_POS, DRINK_TYPE);
	}

	//Detects if the cup disappeared during the pouring process
	detectCupError(CARTCONTROL_ERROR, drinkSelect, 0);

	if (numMilk > 0 && SensorValue[S1] != 0)
	{
		goTo(MILK_TYPE);
		clearTimer(T1);

		operateValve(OPEN_POS, MILK_TYPE);
		while (time1[T1] < 6000 && time1[T1] < timeToPourMilk && SensorValue[S1] != 0);
		operateValve(CLOSE_POS, MILK_TYPE);

		detectCupError(CARTCONTROL_ERROR, drinkSelect, numMilk);
	}

	//If a cup is in the cart, it will deliver the drink
	if (SensorValue[S1] != 0)
	{
		//Goes to deliver the drink
		goTo(CUP_DELIVERY_POS);
		//It will wait
		clearTimer(T1);
		while ((time1[T1] < 1500))
		{
			if (SensorValue[S1] != 0)
			{
				clearTimer(T1);
			}
		}
		goTo(CUP_POS);
	}

}
