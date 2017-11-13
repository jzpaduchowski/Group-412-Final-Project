task main()
{
	displayTextLine(3,"goodbye");

	nMotorEncoder[motorA] = 0;
	while( 1 < 2)
	{
		for (int i = 1; i <= 3; i++)
		{

	    while (!getButtonPress(buttonAny))
		  {}
		  motor[motorA] = 35;
		  while (nMotorEncoder[motorA] < (i*120))
		  {}
		  motor[motorA] = 0;
		}
	}
}
