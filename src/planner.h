/**
 *  File Name:   Planner.h
 *  Date Made:   03-17-2012
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Planning library for executing and tracking timings of power sources
 **/

#include "ComplexMovement.h"
#include "Dock.h"
#include "CaptainPlanetGlobals.h"

#ifndef PLANNER_H
#define PLANNER_H

void start_timer();
void init_captain_planet_with_our_powers_combined();
int parse_time_array(const float array[][2]);
int calculate_desination();
int light_check();
void wait_phase();
int opposite(int);

void start_timer()
{
	START_TIME = seconds();
	CURRENT_TIME = seconds() - START_TIME;
	while(CURRENT_TIME < COMP_TIME_LENGTH)
	{
		CURRENT_TIME = seconds()-START_TIME;
		//check_time();
		sleep(1.0);
	}
	CURRENT_TIME = -1;
}

void init_captain_planet_with_our_powers_combined()
{
	set_each_analog_state(1,1,1,1,1,1,0,0);
    serializer_connect();
	TIMER_PROCESS_ID = start_process(start_timer);
}

int parse_time_array(const float array[][2])
{
	int i;
	for(i = 0; array[i][0] != -1; i++)
		if(CURRENT_TIME >= array[i][0] && CURRENT_TIME <= array[i][1]) 
			return 1;
	return 0;
}

int calculate_desination()
{
	if(PREV == HYDRO && CURRENT == MID)
		wait_phase();
	if(CURRENT == MID && !CHARGED)
		return light_check();
	if(CHARGED)
		return FLAG;
	if (!CHARGED && CURRENT == FLAG)
		return opposite(PREV);
	if(!CHARGED)
		return MID;
}

void wait_phase()
{
	while(CURRENT_TIME < PHASE[CURRENT_PHASE])
		sleep(1);
}

int light_check()
{
	if(is_light_on())
		return SOLAR;
	return HYDRO;
}

int opposite(int barcode)
{
	if(barcode == SOLAR)
		return HYDRO;
	return SOLAR;
}

#endif
