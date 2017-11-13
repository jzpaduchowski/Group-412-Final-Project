const int speed = 25;
const int cup = 1;
const int drink = 2;

void updateDisplay()
{
	displayBigTextLine(6, "%d", nMotorEncoder[motorA]);
}

void wait4Buton()
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

	while (abs(nMotorEncoder[motorA] - pos) < speed * 2 + 5 && abs(nMotorEncoder[motorA] - pos) >= 2)
	{
		motor[motorA] =  ((pos - nMotorEncoder[motorA]) / 1.5);
updateDisplay();
	}
	motor[motorA] = 0;

}

void valveControl(int valveType)
{
	updateDisplay(); b.com.com
	if (valveType == drink)
	{

		displayTextLine(9, "Drink");
		motor[motorB] = 33;

		while(nMotorEncoder[motorB] < 270);

		motor[motorB] = 0;

		wait1Msec(1500);


		motor[motorB] = -33;

		while(nMotorEncoder[motorB] > -5);

		motor[motorB] = 20;

		while(nMotorEncoder[motorB] < 0);

		motor[motorB] = 0;

	}
	else if (valveType == cup)
	{

		displayTextLine(9, "Cup");

		motor[motorB] Encoder[motorB] > 0);
= -33;

		while(nMotorEncoder[motorB] > -105);

		motor[motorB] = 0;

		wait1Msec(500);

		motor[motorB] = 33;

		while(nMotorEncoder[motorB] < 20);

		motor[motorB] = -20;

		while(nMotor
		motor[motorB] = 0;
	}
}



task main()
{

	displayBigTextLine(2, "Press a button ");
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;

	while(1 < 2)
	{

		while (!getButtonPress(buttonAny))

		if (getButtonPress(buttonLeft))
		{
			goTo(0);
			wait4Buton();
			valveControl(drink);
		}

		if (getButtonPress(buttonEnter))
		{
			goTo(110);
			wait4Buton();
			valveControl(drink);
		}

		if (getButtonPress(buttonRight))
		{
			goTo(220);
			wait4Buton();
			valveControl(drink);
		}
		if (getButtonPress(buttonUp))
		{
			goTo(440);
			wait4Buton();
			valveControl(cup);
		}
		if (getButtonPress(buttonDown))
			goTo(825);

		updateDisplay();

	}

}
