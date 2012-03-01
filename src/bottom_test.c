/**
 *  File Name:   complex_movement_test.c
 *  Date Made:   1-21-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Tests complex movment libraries
 **/

#include "ComplexMovement.h"

int main()
{
	
	set_each_analog_state(1,1,1,1,1,1,0,0);
	serializer_connect();
	while(!black_button())
		bottom();
	docking_phase();
	serializer_disconnect();
}

/*Function definitions go below.*/
