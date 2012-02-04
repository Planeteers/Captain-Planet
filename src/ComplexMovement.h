/**
 *  File Name:   ComplexMovement.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Complex movements to navigate from one corner of an 8x8 square to another.
 **/
 
#include "Movement.h"
#include "Sensor.h"
#include "Dock.h"
#define speed 14

#ifndef COMPLEX_MOVEMENT_H
#define COMPLEX_MOVEMENT_H

void top();
void bottom();
void diagnol();

void top()
{
	float dist = -4;
    move_forward_off_wall(4.5*12.0, speed);
	dist += analog_to_inches_avg(rightFront,10);
    turn_right(90, speed);
	block_digo_done();
    move_backward((1.2*12.0)-dist, speed);
	block_digo_done();
    turn_left(90, speed);
	block_digo_done();
    move_forward(1.8*12.0,speed);
	block_digo_done();
	move_backward(2.2,speed);
	block_digo_done();
	turn_right(90.0,speed);
	block_digo_done();
    docking_phase();
}

void bottom()
{
    turn_left(-90, speed);
	block_digo_done();
    move_backward((5*12)+8, speed);
	block_digo_done();
    turn_left(-90, speed);
	block_digo_done();
    move_forward(2.2*12, speed);
	block_digo_done();
	move_backward(2.2,speed);
	block_digo_done();
    turn_left(-90, speed);
	block_digo_done();
	docking_phase();	
}

void diagonal()
{
    turn_left(25, speed);
	block_digo_done();
	move_forward(5.0*12, speed);
	block_digo_done();
	turn_left(65, speed);
	block_digo_done();
	move_forward(5.50*12, speed);
	block_digo_done();
	move_backward(2.2,speed);
	block_digo_done();
	turn_left(-90, speed);
	block_digo_done();
	docking_phase();
}

#endif
