/**
 *  File Name:   turn_360_demo.c
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: turns 360 degrees to the left and prints the encoder
 **/

#include "Movement.h"

int main()
{
    int speed = 10;
    
    serializer_connect();
    turn_left(360.,speed);
    block_digo_done();
    sleep(1.0);
    print_encoders();
    serializer_disconnect();
}

/*Function definitions go below.*/
