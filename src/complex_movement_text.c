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
	turn_left(180.0,14);
	block_digo_done();
	move_backward(6.0,14);
	block_digo_done();
	align_with_bar();
	move_forward(.7*12,14);
	block_digo_done();
	bottom();
	turn_left(180.0,14);
	block_digo_done();
	move_backward(6.0,14);
	block_digo_done();
	align_with_bar();
	move_forward(.7*12,14);
	block_digo_done();
	diagonal();
	serializer_disconnect();
}

/*Function definitions go below.*/
