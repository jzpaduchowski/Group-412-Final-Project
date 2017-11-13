void customWait()
{
					while (!getButtonPress(buttonAny))
				{}

				while (getButtonPress(buttonAny))
				{}
}


task main()
{

		nMotorEncoder[motorA] = 0;


    while (true)
    {

		    motor[motorA] = 33;

		    while(nMotorEncoder[motorA] < 180)
		  	{}

		    motor[motorA] = 0;

		    wait1Msec(1500);


				motor[motorA] = -33;

		    while(nMotorEncoder[motorA] > -5)
		    {}

		    motor[motorA] = 20;

		    while(nMotorEncoder[motorA] < 0)
		    {}

		    motor[motorA] = 0;

		    wait1Msec(1500);

   }


}
