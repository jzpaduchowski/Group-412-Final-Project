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

		  motor[motorA] = 80;

		  while (nMotorEncoder[motorA] < (i*60))
		  {}

		  motor[motorA] = 0;

		  wait1Msec(500);

		  motor[motorA] = 30;

		  while (nMotorEncoder[motorA] < (i*120))
		  {}
		  motor[motorA] = 0;
		}
	}
}
