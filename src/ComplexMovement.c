void top()
{
	turnLeft(30, 10);
	moveForward(5, 10);
	turnLeft(-30, 10);
	moveForward(3, 10);
	turnLeft(-90, 10);
	moveFowardAt(10);
	while(!barSensor());
	stop();
}

void bottom()
{
	turnLeft(90, 10);
	moveForward(5, 10);
	turnLeft(90, 10);
	moveForward(2, 10);
	turnLeft(-90, 10);
	moveFowardAt(10);
	while(!barSensor());
	stop();
}

void diagonal()
{
	turnLeft(90, 10);
	moveForward(7, 10);
	turnLeft(-90, 10);
	moveFowardAt(10);
	while(!barSensor());
	stop();
}