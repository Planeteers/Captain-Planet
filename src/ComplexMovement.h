/**
 *  File Name:   ComplexMovement.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Complex movements to navigate from one corner of an 8x8 square to another.
 **/
 
#include "Movement.h"
#include "Sensor.h"
#include "CaptainPlanetGlobals.h"

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
void start_movement();
void move_to_mid_from(int orginCorner);
void move_from_mid_to(int barcode);

void top()
{
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
	move_backward(WALL_TURN_DISTANCE,SPEED);
	block_digo_done();
	turn_left(90.0,SPEED);
	block_digo_done();
}

void bottom()
{
    turn_right(90, SPEED);
	block_digo_done();
	move_forward(5.0, WALL_SPEED);
	block_digo_done();
    move_backward(1.5*12.0, SPEED);
	block_digo_done();
    turn_right(90, SPEED);
	block_digo_done();
    move_forward(1.7*12, WALL_SPEED);
	block_digo_done();
	move_backward(3.0,SPEED);
	block_digo_done();
    turn_left(90, SPEED);
	block_digo_done();
	move_backward_off_wall(4.1*12.0,SPEED);
	turn_right(90.,SPEED);
	block_digo_done();
	move_forward(5.0,WALL_SPEED);
	block_digo_done();
	move_backward(WALL_TURN_DISTANCE,SPEED);
	block_digo_done();
	turn_left(90.,SPEED);
	block_digo_done();
}

void diagonal()
{
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
	move_backward(WALL_TURN_DISTANCE,SPEED);
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
	move_backward(WALL_TURN_DISTANCE,SPEED);
	block_digo_done();
	turn_left(90.0,SPEED);
	block_digo_done();
}

void move_to_mid_from(int orginCorner)
{
	if (orginCorner == SOLAR) 
	{
		move_forward_off_wall(2.*12, SPEED);
		turn_right(90, SPEED);
		block_digo_done();
		move_forward(5, WALL_SPEED);
		block_digo_done();
		move_backward(2.4, SPEED);
		block_digo_done();
	}
	else if(orginCorner == HYDRO)
	{
		turn_right(90, SPEED);
		block_digo_done();
		move_forward(5.0, WALL_SPEED);
		block_digo_done();
		move_backward(1.5*12.0, SPEED);
		block_digo_done();
		turn_right(90, SPEED);
		block_digo_done();
		move_forward(1.7*12, WALL_SPEED);
		block_digo_done();
		move_backward(3.0,SPEED);
		block_digo_done();
		turn_left(90, SPEED);
		block_digo_done();
		move_backward_off_wall(1.8*12.0,SPEED);
		turn_right(90,SPEED);
		block_digo_done();
		move_forward(5,WALL_SPEED);
		block_digo_done();
		move_backward(2.4,SPEED);
	}
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
	else if(orginCorner == NONE)
		start_movement();
	else if(orginCorner == MID)
		move_from_mid_to(destination);
	else
		printf("%d\n", destination);
}

void move_from_solar_to(int barcode)
{
	if(barcode == HYDRO)
		top();
	else if(barcode == WIND)
		diagonal();
	else if(barcode == FLAG)
		bottom();
	else if(barcode == MID)
		move_to_mid_from(SOLAR);
}

void move_from_hydro_to(int barcode)
{
	if(barcode == WIND)
		top();
	else if(barcode == FLAG)
		diagonal();
	else if(barcode == SOLAR)
		bottom();
	else if(barcode == MID)
		move_to_mid_from(HYDRO);
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

void move_from_mid_to(int barcode)
{
	if (barcode == HYDRO) 
	{
		// Go to Hydro
		turn_left(90, SPEED);
		block_digo_done();
		move_forward_off_wall(1.7*12, SPEED);
		turn_right(90.0, SPEED);
		block_digo_done();
		move_backward((1.2*12),SPEED);
		block_digo_done();
		turn_left(90.0,SPEED);
		block_digo_done();
		move_forward(1.8*12, WALL_SPEED);
		block_digo_done();
		move_backward(2.2,SPEED);
		block_digo_done();
		turn_left(90.0,SPEED);
		block_digo_done();
	}
	else if(barcode == SOLAR)
	{
		// Go to Solar
		turn_left(88, SPEED);
		block_digo_done();
		move_backward_off_wall(1.7*12, SPEED);
		turn_right(90, SPEED);
		block_digo_done();
		move_forward(5, WALL_SPEED);
		block_digo_done();
		move_backward(2.2, SPEED);
		block_digo_done();
		turn_left(90, SPEED);
		block_digo_done();
	}

}

void start_movement()
{
	move_forward(3*12, WALL_SPEED);
	block_digo_done();
	move_backward(2.4, SPEED);
	block_digo_done();
}

#endif
