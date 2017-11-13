
task main()
{

	displayBigTextLine(0, "Put In Toooonie");
	while (!getButtonPress(buttonAny))
	{}
	while (getButtonPress(buttonAny))
	{}

	SensorType[S1] = sensorEV3_Touch;

		motor[motorA] = 75;
		while(SensorValue[S1] == 0)
		{}
		motor[motorA] = -75;
		wait1Msec(750);
		motor[motorA] = 0;
		nMotorEncoder[motorA] = 0;

	wait1Msec(250);

	eraseDisplay();


	displayBigTextLine(0, "fff");
	motor[motorA] = 75;
	while (nMotorEncoder[motorA] < 400);
	motor[motorA] = 0;

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

		if (750 < coinType && coinType < 840)
		{
				coin = "Toonie";
				totalCoin += 2;
				coinReverse = 800;
		}
		else if (850 < coinType && coinType < 950)
		{
				coin = "Loonie";
				totalCoin += 1;
				coinReverse = 750;
		}
		else if (1000 < coinType && coinType < 1150)
		{
				coin = "Quarter";
				totalCoin += 0.25;
				coinReverse = 550;
		}
		else if (1175 < coinType && coinType < 1300)
		{
				coin = "Nickel";
				totalCoin += 0.05;
				coinReverse = 200;
		}

		else if (1375 < coinType && coinType < 2000)
		{
				coin = "Dime";
				totalCoin += 0.1;
				coinReverse = 50;
		}
		else
		{
			coin = "???";
		}


		displayBigTextLine(3, "%s", coin);
		displayBigTextLine(6, "%.2d", nMotorEncoder[motorA]);
		displayBigTextLine(9, "$%.2f", totalCoin);


		motor[motorA] = -75;

		while(nMotorEncoder[motorA] > -coinReverse)
		{}

		motor[motorA] = 75;

		while (nMotorEncoder[motorA] < 400);
		motor[motorA] = 0;

	}
}
