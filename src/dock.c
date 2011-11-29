int scanCode()
{
	int code = 0;
	if(!barSensor())
	{
		moveFoward(.4, -10);
		moveFoward(10);
		while(!barSensor());
		stop();
	}
	code++;
	for(int i=0; i<3; i++)
	{
		moveFoward(1,10);
		if(!barSensor())
			break;
		code++;
	}
	return code;
}

void sendChargeSignal()
{
}