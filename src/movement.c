/**
 * File Name:		movement.c
 **/

#include "movement.h"

int main()
{
	int speed = 10;
	
	serializer_connect();
	move_forward_at(speed);
	turn_left_at(speed);
	turn_right_at(speed);
	move_backward_at(speed);
	serializer_disconnect();
}

/*Function definitions go below.*/
