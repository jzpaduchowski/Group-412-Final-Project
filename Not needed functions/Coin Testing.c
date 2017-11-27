
task main()
{

	displayBigTextLine(0, "Put In Toonie");
	while (!getButtonPress(buttonAny));
	while (getButtonPress(buttonAny));

	SensorType[S1] = sensorEV3_Touch;

	motor[motorA] = 75;
	while(SensorValue[S1] == 0);

	nMotorEncoder[motorA] = 0;

	motor[motorA] = -75;

	while (nMotorEncoder[motorA] > -1500);

	motor[motorA] = 0;

	wait1Msec(100);

	eraseDisplay();

	motor[motorA] = 75;
	while (nMotorEncoder[motorA] < -400);
	motor[motorA] = 0;

	nMotorEncoder[motorA] = 0;

	eraseDisplay();

	int coinType = 0;
	string coin = " ";
	float totalCoin = 0;
	int coinReverse = 0;

	while(1 < 2)
	{

		while (!getButtonPress(buttonAny))
		{}
		while (getButtonPress(buttonAny))
		{}

		wait1Msec(100);



		motor[motorA] = 75;

		while(SensorValue[S1] == 0)
		{}

		motor[motorA] = 0;

		coinType = nMotorEncoder[motorA];

		if (350 < coinType && coinType < 450)
		{
			coin = "Toonie";
			totalCoin += 2;
			coinReverse = 950;
		}
		else if (460 < coinType && coinType < 590)
		{
			coin = "Loonie";
			totalCoin += 1;
			coinReverse = 875;
		}
		else if (610 < coinType && coinType < 750)
		{
			coin = "Quarter";
			totalCoin += 0.25;
			coinReverse = 600;
		}
		else if (800 < coinType && coinType < 900)
		{
			coin = "Nickel";
			totalCoin += 0.05;
			coinReverse = 400;
		}

		else if (950 < coinType && coinType < 1150)
		{
			coin = "Dime";
			totalCoin += 0.1;
			coinReverse = 200;
		}
		else if (1300 < coinType)
		{
			coin = "nul";
		}
		else
		{
			coin = "none";
		}


		displayTextLine(3, "%s", coin);
		displayTextLine(6, "%.2d", nMotorEncoder[motorA]);
		displayTextLine(9, "$%.2f", totalCoin);


		motor[motorA] = -75;

		while(nMotorEncoder[motorA] > -coinReverse);

		motor[motorA] = 75;

		while (nMotorEncoder[motorA] < 0);
		motor[motorA] = 0;

	}
}
