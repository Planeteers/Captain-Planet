/**
 *  File Name:   ComplexMovement.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Complex movements to navigate from one corner of an 8x8 square to another.
 **/
 
 #include "Movement.h"
 #include "Sensor.h"
#define topHat1 14
#define topHat2 15

#define speed 14

void top();
void bottom();
void diagnol();

void align_with_bar()
{
	move_forward_at(6);
    while(!bar_sensor(topHat2,topHat1))
	{
		if(see_bar(topHat1))
			drive_direct_at(-1, 3);
		else if(see_bar(topHat2))
			drive_direct_at(3, -1);
	}
    stop();
}

void top()
{
    move_forward(4.5*12.0, speed);
	block_digo_done();
    turn_right(90, speed);
	block_digo_done();
    move_backward(1.2*12.0, speed);
	block_digo_done();
    turn_left(90, speed);
	block_digo_done();
    move_forward(1.8*12.0,speed);
	block_digo_done();
	move_backward(2.5,speed);
	block_digo_done();
	turn_right(90.0,speed);
	block_digo_done();
    align_with_bar();
}

void bottom()
{
    turn_left(-90, speed);
	block_digo_done();
    move_backward(5*12, speed);
	block_digo_done();
    turn_left(-90, speed);
	block_digo_done();
    move_forward(2.2*12, speed);
	block_digo_done();
	move_backward(2.5,speed);
	block_digo_done();
    turn_left(-90, speed);
	block_digo_done();
	align_with_bar();
	
}

void diagonal()
{
    turn_left(30, speed);
	block_digo_done();
	move_forward(4.9*12, speed);
	block_digo_done();
	turn_left(60, speed);
	block_digo_done();
	move_forward(5.05*12, speed);
	block_digo_done();
	move_backward(2.5,speed);
	block_digo_done();
	turn_left(-90, speed);
	block_digo_done();
	align_with_bar();
}
