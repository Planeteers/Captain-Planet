/**
 *  File Name:   turn_4_90s_demo.c
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: turns 4 times to the left and prints encoder values after each turn.
**/

#include "Movement.h"

int main()
{
	int speed = 14;
	
	serializer_connect();
	
	while(!b_button())
	{
		printf("left/right: choose direction\nup/down: change speed\nspeed: %d\n\n",speed);
		if(up_button() && speed < 14)
			speed+=1;
		else if(down_button() && speed > 0)
			speed-=1;
		else if(right_button())
		{
			while(right_button());
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
		}
		else if(left_button())
		{
			while(left_button());
			turn_left(90.,speed);
			block_digo_done();
			sleep(1.0);
			print_encoders();
			turn_left(90.,speed);
			block_digo_done();
			sleep(1.0);
			print_encoders();
			turn_left(90.,speed);
			block_digo_done();
			sleep(1.0);
			print_encoders();
			turn_left(90.,speed);
			block_digo_done(); 
			print_encoders();
			sleep(1.0);
		}
	}
	serializer_disconnect();
}

/*Function definitions go below.*/
