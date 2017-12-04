//Merge all functions related to valve and cart control here pls

const int CART_SPEED = 25; //Desired speed of the cup cart
const int DRINK_TYPE = 1;
//const int COFFEE_TYPE = 0; //Declared in previous file
//const int TEA_TYPE = 220;
const int MILK_TYPE = 120; //Position of milk location
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

//Function prototypes for functions that are below others
void goTo(int pos);
void getCup();
void cartControl(int drinkSelect, int numMilk);

//Calibrates the cart with the touch sensor at the start of the track
void calibrateCart()
{
	//Slowly moves the motor until it hits the beginning
	motor[motorA] = -10;
	while(SensorValue[S2] == 0)
	{}
	motor[motorA] = 0;
	wait1Msec(150);
	nMotorEncoder[motorA] = 0;

}

//Helper function to get a button press
void wait4Button()
{
	while (!getButtonPress(buttonAny))
	{}
	while (getButtonPress(buttonAny))
	{}
}


//Error message function to display error messages
void errorMessage(string errorCode)
{

	//Plays alert sound and shows error codes
	playSoundFile("Ouch");
	displayCenteredTextLine(13, "ERROR!");
	displayCenteredTextLine(14, "%s", errorCode);

	while(errorCode == CUP_CART_FELL)
	{} //Fatal error needs human intervention so we go into an infinite loop and wait for operators to manually quit and fix the robot

	//Clears the errors
	displayCenteredTextLine(15, "Press to resolve");
	wait4Button();
	displayTextLine(13, " ");
	displayTextLine(14, " ");
	displayTextLine(15, " ");

}

//receives selection and calculates the amount of time each valve should be open for in milliseconds
float pourTime(int valveType, int numMilks)
{
	int timeToPour = 0;

	if (valveType == DRINK_TYPE)
	{
		//Returns the time it takes to fill a cup with drink. Calculates the amount of liquid displaced by the milks
		timeToPour = ((350.0 - (numMilks * 10))* 1000.0) / FLOWRATE_DRINK;
	}
	else if (numMilks > 0)
	{
		//Calculates the time to pour specified amount of milk
		timeToPour = ((numMilks * 10 * 1000.0) / FLOWRATE_MILK);
	}
	return timeToPour;
}

//#######################~Cup Error Detection Functions~#######################################3
//Detects if an empty cup is missing
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

//For detecting cup errors when moving from one place to another
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

//For detecting cup errors after dropping the completed drink
bool detectCupError (int errorProtocol, int drinkSelect, int numMilks)
{
	bool isError = false;
	if (SensorValue[S1] == 0)
	{
		if (errorProtocol == CARTCONTROL_ERROR)
		{
			errorMessage(CUP_FELL_ERROR);

			//Gets the new drink again
			cartControl(drinkSelect, numMilks);
			isError = true;
		}
	}
	return isError;
}
//###############################~End of cup error detection functions~######################################

//A go to error detection function to find go to a specified position
void goTo(int pos)
{
	//Sets the direction to go backwards or forwards
	int direction = 1;
	int previousEncoder = nMotorEncoder[motorA];
	bool hasCup = true;

	//Sets the direction to go forwards or backwards
	if (pos < nMotorEncoder[motorA])
		direction = -1;

	//Checks if it has to detect for cups throughout the program
	if (SensorValue[S1] == 0)
		hasCup = false;

	//A timer is used here to detect the cup detection every fraction of a second
	clearTimer(T2);

	//Sets the cart speed with direction
	motor[motorA] = CART_SPEED * direction;

	//Lets the cart travel until it reaches a distance away from the desired position based off the speed
	//It will also check if the cup "falls off" the cart when in motion
	while (abs(nMotorEncoder[motorA] - pos) > CART_SPEED * 2 && !(SensorValue[S1] == 0 && hasCup))
	{
		//every 500ms, it will check if the cart is stuck somewhere on the track
		if((time1(T2)) > 500)
		{
			//Will check if the motor does not turn more than 3 degrees within the last 500ms
			if(abs(nMotorEncoder[motorA] - previousEncoder) < 3)
			{
				motor[motorA] = 0;
				errorMessage(CUP_CART_FELL);
			}
			previousEncoder = nMotorEncoder[motorA];
			clearTimer(T2);
		}
	}

	//After it is within the position range, it will slowly stop the cart as a function of how far it is from the position.
	while ((direction * (pos - nMotorEncoder[motorA] )) > 1 && !(SensorValue[S1] == 0 && hasCup))
	{
		motor[motorA] = (1.0 * pos - nMotorEncoder[motorA]) / 2;
	}

	//Stops the cart
	motor[motorA] = 0;

	//Will detect if the cup fell off if it had a cup to begin with.
	if (hasCup)
	{
		detectCupError(GOTO_ERROR, pos);
	}
}


//Operates the valve given the position desired (open or close) and which valve it is
void operateValve(int toOpen, int valveType)
{
	//Opens the specified valve
	if (toOpen == OPEN_POS)
	{
		if (valveType	== DRINK_TYPE)
		{
			//Opens the main drink valves to 200 degrees for compromise between pour time and operation speed
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 200)
			{}
			motor[motorB] = 0;

		}
		else if (valveType == MILK_TYPE)
		{
			//Opens the valve enough for more percise dispensing
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 135)
			{}
			motor[motorB] = 0;
		}
		else if (valveType == CUP_POS)
		{
			//Opens the valve to get a cup
			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -100)
			{}
			motor[motorB] = 0;
		}
	}
	//Closes the valves
	else if (toOpen == CLOSE_POS)
	{
		if (valveType	== DRINK_TYPE || valveType == MILK_TYPE)
		{
			//Closes the valve by turning ~10 too much to get the valve parallel with each other
			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -10)
			{}
			motor[motorB] = 15;
			while(nMotorEncoder[motorB] < 0)
			{}
			motor[motorB] = 0;
		}
		else 	if (valveType	== CUP_POS)
		{
			//Returns the cup dispenser mechanism to original position
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 20)
			{}
			motor[motorB] = -25;
			while(nMotorEncoder[motorB] > 0)
			{}
			motor[motorB] = 0;
		}
	}
}


void getCup()
{
	goTo(CUP_POS);

	//If there is a cup, it will not get a cup, and throw an error.
	if (SensorValue[S1] != 0)
	{

		errorMessage(CUP_EXISTS_ERROR);
		goTo(CUP_DELIVERY_POS);
		while (SensorValue[S1] != 0)
		{}
		wait1Msec(1000);
		goTo(CUP_POS);
	}

	//Operates the valve to get a cup
	operateValve(OPEN_POS, CUP_POS);
	wait1Msec(250);
	operateValve(CLOSE_POS, CUP_POS);

	//Detects if there are no more cups (if the cup did not fall)
	wait1Msec(250);
	detectCupError(GETCUP_ERROR);
}

//This is the main drink preparation function. Given the drink type and number of milks, the robot will go and prepare that drink.
void cartControl(int drinkSelect, int numMilk)
{
	//Gets a cup and goes to the drink selected
	getCup();
	goTo(drinkSelect);

	//Calcilates the time to pour the specified drink
	float timeToPourDrink = pourTime(DRINK_TYPE, numMilk);
	float timeToPourMilk = pourTime(0, numMilk);
	bool wasError = false;

	//Operates the drink valve if the cup is there
	if ((drinkSelect == COFFEE_TYPE || drinkSelect == TEA_TYPE) && SensorValue[S1] != 0)
	{
		clearTimer(T1);
		operateValve(OPEN_POS, DRINK_TYPE);
		//Waits while the valve is open for specified amount of time given the flow rate required
		while (time1[T1] < 18000 && time1[T1] < timeToPourDrink && SensorValue[S1] != 0)
		{}
		operateValve(CLOSE_POS, DRINK_TYPE);
	}

	//Detects if the cup disappeared during/after the pouring process
	wasError = detectCupError(CARTCONTROL_ERROR, drinkSelect, numMilk);

	//Continues if there was no error
	if (!wasError)
	{
		if (numMilk > 0 && SensorValue[S1] != 0)
		{
			//Goes to the milk valve position
			goTo(MILK_TYPE);

			//Detects if there was a error while getting there
			detectCupError(CARTCONTROL_ERROR, drinkSelect, 0);

			clearTimer(T1);

			//Opens the valve for specified amount of time for the milk
			operateValve(OPEN_POS, MILK_TYPE);
			while (time1[T1] < 6000 && time1[T1] < timeToPourMilk && SensorValue[S1] != 0)
			{}
			operateValve(CLOSE_POS, MILK_TYPE);

			//Detects if the cup fell during the pouring of the milk
			detectCupError(CARTCONTROL_ERROR, drinkSelect, numMilk);
		}
	}

	//If a cup is in the cart, it will deliver the drink
	if (SensorValue[S1] != 0)
	{
		//Goes to deliver the drink
		goTo(CUP_DELIVERY_POS);

		//Detect cup errors
		detectCupError(CARTCONTROL_ERROR, drinkSelect, numMilk);

		//Shows that the drink is ready
		dispIsReady();

		//It will wait 1.5 seconds after the cup has been last seen
		clearTimer(T1);
		while ((time1[T1] < 1500))
		{
			if (SensorValue[S1] != 0)
			{
				clearTimer(T1);
			}
		}

		//Goes to the cup dispenser position for the next cup
		goTo(CUP_POS);
	}

}
