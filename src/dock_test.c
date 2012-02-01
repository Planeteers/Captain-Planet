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
	//docking_phase();
	serializer_disconnect();
}

/*Function definitions go below.*/
