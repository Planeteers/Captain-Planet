/**
 *  File Name:   complex_movement_test.c
 *  Date Made:   1-21-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Tests complex movment libraries
 **/

#include "ComplexMovement.h"

int main()
{
	serializer_connect();
	top();
	while(!black_button());
	turn_left(180.0,14);
	block_digo_done();
	move_backward(5.0,14);
	block_digo_done();
	align_with_bar();
	serializer_disconnect();
}

/*Function definitions go below.*/
