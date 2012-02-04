/**
 *  File Name:   turn_4_90s_demo.c
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: turns 4 times to the left and prints encoder values after each turn.
 **/

#include "Movement.h"

int main()
{
    int speed = 10;
    
    serializer_connect();
    turn_right(90.,speed);
    block_digo_done();
    sleep(1.0);
    print_encoders();
    turn_right(90.,speed);
    block_digo_done();
    sleep(1.0);
    print_encoders();
    turn_right(90.,speed);
    block_digo_done();
    sleep(1.0);
    print_encoders();
    turn_right(90.,speed);
    block_digo_done(); 
    print_encoders();
	sleep(1.0);
    serializer_disconnect();
}

/*Function definitions go below.*/
