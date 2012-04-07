/**
 *  File Name:   turn_4_90s_demo.c
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: turns 4 times to the left and prints encoder values after each turn.
 **/

#include "Planner.h"

int main()
{	
	init_captain_planet_with_our_powers_combined();
	
	int speed = 14;
	
	move_forward_at(WALL_SPEED);
	
	while(!b_button());
	
	stop();
	
    serializer_disconnect();
}

/*Function definitions go below.*/
