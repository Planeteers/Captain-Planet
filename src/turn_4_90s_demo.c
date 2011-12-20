/**
 * File Name:		Turn_4_90s.c
 **/

#include "movement.h"

int main()
{
	int speed = 10;
	
	serializer_connect();
	turn_left(90.,speed);
	block_digo_done();
	sleep(1.0);
	print_encoders();
	turn_left(90.,speed);
	block_digo_done();
	sleep(1.0);
	print_encoders();
	turn_left(90.,speed);
	block_digo_done();
	sleep(1.0);
	print_encoders();
	turn_left(90.,speed);
	block_digo_done();
	sleep(1.0); 
	print_encoders();
	serializer_disconnect();
}

/*Function definitions go below.*/
