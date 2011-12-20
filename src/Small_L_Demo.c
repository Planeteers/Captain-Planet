/**
 * File Name:		Small_L_Demo.c
 **/

#include "movement.h"

int main()
{
	int speed = 10;
	
	serializer_connect();
	move_forward(2*12.0,speed);
	block_digo_done();
	turn_right(90.,speed);
	block_digo_done();
	move_forward(12.0,speed);
	block_digo_done();
	turn_left(180.,speed);
	block_digo_done();
	move_forward(12.0,speed);
	block_digo_done();
	turn_left(90.,speed);
	block_digo_done();
	move_forward(2.*12.,speed);
	block_digo_done();
	turn_left(180.,speed);
	block_digo_done();
	serializer_disconnect();
}

/*Function definitions go below.*/
