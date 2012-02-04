/**
 *  File Name:   move_forward_1_foot_demo.h
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: drives forward 1 foot
 **/

#include "Movement.h"

int main()
{
    int speed = 3;
    
    serializer_connect();
    move_forward(12.0,speed);
    block_digo_done();
	print_encoders();
    serializer_disconnect();
}

/*Function definitions go below.*/
