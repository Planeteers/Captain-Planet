/**
 *  File Name:   large_l_demo.c
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: Drives stinger robot in a 8 foot long 4 foot wide L shape (right)
 **/

#include "Movement.h"

int main()
{
    int speed = 10;
    
    serializer_connect();
    move_forward(8.*12.0,speed);
    block_digo_done();
    turn_right(90.,speed);
    block_digo_done();
    move_forward(4.*12.0,speed);
    block_digo_done();
    turn_right(180.,speed);
    block_digo_done();
    move_forward(4.*12.0,speed);
    block_digo_done();
    turn_left(90.,speed);
    block_digo_done();
    move_forward(8.*12.,speed);
    block_digo_done();
    turn_left(180.,speed);
    block_digo_done();
    serializer_disconnect();
}

/*Function definitions go below.*/
