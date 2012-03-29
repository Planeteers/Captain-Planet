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
int opposite(int);
int get_phase(int time);
int timer_interrupt(int start_time);
void timer_watchdog();
int calculate_last_source();

void start_timer()
{
	START_TIME = seconds();
	CURRENT_TIME = seconds() - START_TIME;
	while(CURRENT_TIME < COMP_TIME_LENGTH)
	{
		CURRENT_TIME = seconds()-START_TIME;
		sleep(.1);
	}
	CURRENT_TIME = INVALID_TIME;
}

void init_captain_planet_with_our_powers_combined()
{
	set_each_analog_state(1,1,1,1,1,1,0,0);
	serializer_connect();
	TIMER_PROCESS_ID = start_process(start_timer);
	TIMER_WATCHDOG_ID = start_process(timer_watchdog);
}

int light_check()
{
	if(is_light_on()) return SOLAR;
	return HYDRO;
}

int opposite(int barcode)
{
	if(barcode == SOLAR) return HYDRO;
	return SOLAR;
}

int get_phase(int time)
{
	int i;
	for(i = 0;i<NUM_PHASES;i++)
	{
		if(time<PHASE_TIMES[i]) return i;
	}
	return i;
}

int timer_interrupt(int start_time)
{
	return (get_phase(start_time) < get_phase(CURRENT_TIME));
}

void timer_watchdog()
{
	while(CURRENT_TIME != INVALID_TIME)
	{
		if(WATCHDOG_ACTIVE)
		{
			float start_time = CURRENT_TIME;
			while(WATCHDOG_ACTIVE)
			{
				TIMER_INTERRUPT = timer_interrupt(start_time);
				sleep(.1);
			}
		}
		else if(TIMER_INTERRUPT == 1)
		{
			TIMER_INTERRUPT = 0;
		}
		sleep(.1);
	}
}

int calculate_desination()
{
	int start_time = CURRENT_TIME;
	int phase = get_phase(start_time);
	
	if(CHARGED == DONE) return FLAG;
	
	if(phase == 0)
		if(SOURCE_ORDER[phase] == UNKNOWN)
			return light_check();
		else
			return MID;
	else if(phase == 1)
		if(SOURCE_ORDER[0] == SOLAR || SOURCE_ORDER[0] == HYDRO)
			return opposite(SOURCE_ORDER[0]);
		else if(SOURCE_ORDER[phase] == UNKNOWN)
			return light_check();
		else
			return MID;
	else if(phase == 2)
		if(SOURCE_ORDER[2] != WIND)
			return SOURCE_ORDER[2];
		else
			return HYDRO;
	else
		return HYDRO;
}

void update_source_order(int cycle_start_time)
{
	//get the phase of the passed time
	int cycle_phase = get_phase(cycle_start_time);
	
	if(cycle_phase > 2) return;
	
	if((CURRENT == HYDRO || CURRENT == SOLAR) && (CHARGED == DONE || CHARGED == TIME_UP))
	{
		SOURCE_ORDER[cycle_phase] = CURRENT;
	}
	else if(CURRENT == HYDRO && CHARGED == ERROR)
	{
		SOURCE_ORDER[cycle_phase] == WIND;
	}
	else
	{
		printf("we are at solar and not charging or something went terribly wrong\n");
	}
	
	//attempt to calculate what we believe the last phase source is
	SOURCE_ORDER[2] = calculate_last_source();
	
	return;
}

int calculate_last_source()
{
	// if either of the previous two sources are unknown we cannot predict the third
	if(SOURCE_ORDER[0] == UNKNOWN || SOURCE_ORDER[1] == UNKNOWN)
	{
		return UNKNOWN;
	}
	if(SOURCE_ORDER[0] == WIND)
	{
		return opposite(SOURCE_ORDER[1]);
	}
	if(SOURCE_ORDER[1] == WIND)
	{
		return opposite(SOURCE_ORDER[0]);
	}
	return WIND;
}

#endif
