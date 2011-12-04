/**
 * File Name:		movement.c
 **/

#include "movement.h"

int main()
{
	int speed = 10;
	
	serializer_connect();
	turn_left(360.,speed);
	block_digo_done();
	//stop();
	printf("done!\n");
	serializer_disconnect();
}

/*Function definitions go below.*/
