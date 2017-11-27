const int speed = 25; //Desired speed of the cup cart
const int drink = 1;
const int coffeeType = 0; //Position of drink 1
const int teaType = 220; //Position of drink 2
const int milk = 110; //Position of milk location
const int cup = 440; //Position of cup dispenser
const int cupDelivery = 750; //Position to deliver the cup
const string cupFell = "The cup fell!";
const string noCups = "No more cups!";
const float FLOWRATE = 1.0; //mL/s
const int openPos = 1;
const int closePos = -1;
const int goToError = 1;
const int getCupError = 2;
const int cartControlError = 3;


void operateValve(int toOpen, int valveType)
{
	if (toOpen == openPos)
	{
		if (valveType	== drink)
		{
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 200);
			motor[motorB] = 0;

		}
		else if (valveType == milk)
		{
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 135);
			motor[motorB] = 0;

		}
		else if (valveType == cup)
		{
			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -105);
			motor[motorB] = 0;
		}
	}
	else if (toOpen == closePos)
	{
		if (valveType	== drink)
		{

			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -8);
			motor[motorB] = 15;
			while(nMotorEncoder[motorB] < 0);
			motor[motorB] = 0;
		}
		else if (valveType == milk)
		{
			motor[motorB] = -33;
			while(nMotorEncoder[motorB] > -8);
			motor[motorB] = 15;
			while(nMotorEncoder[motorB] < 0);
			motor[motorB] = 0;
		}
		else 	if (valveType	== cup)
		{
			motor[motorB] = 33;
			while(nMotorEncoder[motorB] < 20);
			motor[motorB] = -20;
			while(nMotorEncoder[motorB] > 0);
			motor[motorB] = 0;
		}
	}
}

task main()
{

		nMotorEncoder[motorB] = 0;


    while (true)
    {
    	while (getButtonPress(buttonAny);
    	while (!getButtonPress(buttonAny);
				operateValve(openPos, cup);
			while (getButtonPress(buttonAny);
    	while (!getButtonPress(buttonAny);
					operateValve(closePos, cup);

   	}


}
