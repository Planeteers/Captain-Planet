/**
 * File Name:		movement.c
 **/

#include "movement.h"

int main()
{
	int speed = 10;
	
	serializer_connect();
	moveForward(12.,speed);
	/*while(!IsDone());
	turnLeft(-90.,speed);
	while(!IsDone());
	moveForward(4.*12.,speed);
	while(!IsDone());
	turnLeft(-180.,speed);
	while(!IsDone());
	moveForward(4.*12.,speed);
	while(!IsDone());
	turnLeft(90.,speed);
	while(!IsDone());
	moveForward(8.*12.,speed);
	while(!IsDone());
	turnLeft(180.,speed);
	while(!IsDone());
	printf("done!");*/
	serializer_disconnect();
}

/*Function definitions go below.*/
