
task main()
{

	displayBigTextLine(3, "Press up or down");


	while(true)
	{

		while(getButtonPress(buttonUp))
		{
			motor[motorA] = 25;
			displayBigTextLine(7, "Turns: %d", nMotorEncoder[motorA]);
		}



		while(getButtonPress(buttonDown))
		{
			motor[motorA] = -25;
			displayBigTextLine(7, "Turns: %d", nMotorEncoder[motorA]);
		}

		motor[motorA] = 0;

		if (getButtonPress(buttonEnter))
				nMotorEncoder[motorA] = 0;

		displayBigTextLine(7, "Turns: %d", nMotorEncoder[motorA]);
	}
}
