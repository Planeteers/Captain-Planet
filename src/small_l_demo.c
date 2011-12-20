/**
 *  File Name:   small_l_demo.c
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: drives stinger robot in a 2 foot by 1 foot long L shape (right)
 **/

#include "Movement.h"

int main()
{
    int speed = 10;
    
    serializer_connect();
    move_forward(2*12.0,speed);
    block_digo_done();
    turn_right(90.,speed);
    block_digo_done();
    move_forward(12.0,speed);
    block_digo_done();
    turn_left(180.,speed);
    block_digo_done();
    move_forward(12.0,speed);
    block_digo_done();
    turn_left(90.,speed);
    block_digo_done();
    move_forward(2.*12.,speed);
    block_digo_done();
    turn_left(180.,speed);
    block_digo_done();
    serializer_disconnect();
}

/*Function definitions go below.*/
