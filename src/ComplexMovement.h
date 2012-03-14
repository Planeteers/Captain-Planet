/**
 *  File Name:   ComplexMovement.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Complex movements to navigate from one corner of an 8x8 square to another.
 **/
 
#include "Movement.h"
#include "Sensor.h"
#include "Dock.h"
#define SPEED 14
#define WALL_SPEED 8

#ifndef COMPLEX_MOVEMENT_H
#define COMPLEX_MOVEMENT_H

void top();
void bottom();
void diagnol();
void move_from_solar_to(int);
void move_from_hydro_to(int);
void move_from_wind_to(int);
void move_from_flag_to(int);
void move_to(int, int);

void top()
{
	turn_left(180.,SPEED);
	block_digo_done();
    move_forward_off_wall(4.2*12.0, SPEED);
	//dist += analog_to_inches_avg(rightFrontIR,10);
    turn_right(90, SPEED);
	block_digo_done();
    move_backward((1.2*12.0), SPEED);
	block_digo_done();
    turn_left(90, SPEED);
	//printf("turning left!\n");
	block_digo_done();
    move_forward(1.8*12.0,WALL_SPEED);
	block_digo_done();
	move_backward(2.2,SPEED);
	block_digo_done();
	turn_right(90.0,SPEED);
	block_digo_done();
}

void bottom()
{
    turn_left(90, SPEED);
	block_digo_done();
	move_forward(5.0, WALL_SPEED);
	block_digo_done();
    move_backward(1.2*12.0, SPEED);
	block_digo_done();
    turn_right(90, SPEED);
	block_digo_done();
    move_forward(1.7*12, WALL_SPEED);
	block_digo_done();
	move_backward(3.0,SPEED);
	block_digo_done();
    turn_left(90, SPEED);
	block_digo_done();
	move_backward_off_wall(4.*12.0,SPEED);
	turn_right(90.,SPEED);
	block_digo_done();
	move_forward(5.0,WALL_SPEED);
	block_digo_done();
	move_backward(2.2,SPEED);
	block_digo_done();
	turn_right(90.,SPEED);
	block_digo_done();
}

void diagonal()
{
	turn_left(180.,SPEED);
	block_digo_done();
    move_forward_off_wall(4.2*12.0, SPEED);
	//dist += analog_to_inches_avg(rightFrontIR,10);
    turn_right(90, SPEED);
	block_digo_done();
    move_backward((1.2*12.0), SPEED);
	block_digo_done();
    turn_left(90, SPEED);
	//printf("turning left!\n");
	block_digo_done();
    move_forward(1.8*12.0,WALL_SPEED);
	block_digo_done();
	move_backward(2.2,SPEED);
	block_digo_done();
	turn_left(90.0,SPEED);
	block_digo_done();
	move_forward_off_wall(4.2*12.0, SPEED);
	//dist += analog_to_inches_avg(rightFrontIR,10);
    turn_right(90, SPEED);
	block_digo_done();
    move_backward((1.2*12.0), SPEED);
	block_digo_done();
    turn_left(90, SPEED);
	//printf("turning left!\n");
	block_digo_done();
    move_forward(1.8*12.0,WALL_SPEED);
	block_digo_done();
	move_backward(2.2,SPEED);
	block_digo_done();
	turn_right(90.0,SPEED);
	block_digo_done();
}

void move_to(int orginCorner, int destination)
{
	if(orginCorner == HYDRO)
		move_from_hydro_to(destination);
	else if(orginCorner == SOLAR)
		move_from_solar_to(destination);
	else if(orginCorner == WIND)
		move_from_wind_to(destination);
	else if(orginCorner == FLAG)
		move_from_flag_to(destination);
	else
		printf("%d\n", destination);
}

void move_from_solar_to(int barcode)
{
	if(barcode == HYDRO)
		top();
	else if(barcode == WIND)
		diagonal();
	else
		bottom();
}

void move_from_hydro_to(int barcode)
{
	if(barcode == WIND)
		top();
	else if(barcode == FLAG)
		diagonal();
	else
		bottom();
}

void move_from_wind_to(int barcode)
{
	if(barcode == FLAG)
		top();
	else if(barcode == SOLAR)
		diagonal();
	else
		bottom();
}

void move_from_flag_to(int barcode)
{
	if(barcode == SOLAR)
		top();
	else if(barcode == HYDRO)
		diagonal();
	else
		bottom();
}

#endif
