/**
 *  File Name:   movement_test.c
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: test bed for movement functionality
 **/

#include "Movement.h"

int main()
{
    int speed = 10;
    
    serializer_connect();
    turn_left(360.,speed);
    block_digo_done();
    //stop();
    printf("done!\n");
    serializer_disconnect();
}

/*Function definitions go below.*/
