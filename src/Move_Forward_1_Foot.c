/**
 * File Name:		Move_Forward_1_Foot.c
 **/

#include "movement.h"

int main()
{
	int speed = 10;
	
	serializer_connect();
	move_forward(12.0,speed);
	block_digo_done();
	serializer_disconnect();
}

/*Function definitions go below.*/
