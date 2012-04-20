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
int calculate_desination();
int light_check();
int opposite(int);
int get_phase(float time);
int timer_interrupt(float start_time);
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
	set_each_analog_state(1,1,1,0,0,0,0,0);
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
	else if(barcode == HYDRO) return SOLAR;
	else return UNKNOWN;
}

int get_phase(float time)
{
	int i;
	for(i = 0;i<NUM_PHASES;i++)
	{
		if(time<PHASE_TIMES[i]) return i;
	}
	return i;
}

int timer_interrupt(float start_time)
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

int calculate_destination()
{
	float start_time = CURRENT_TIME;
	int phase = get_phase(start_time);
	
	if(CHARGED == DONE && CURRENT != FLAG) return FLAG;
	
	else if(phase == 0)
	{
		if(SOURCE_ORDER[phase] == UNKNOWN)
			return light_check();
		else if(SOURCE_ORDER[phase] == SOLAR || SOURCE_ORDER[phase] == HYDRO)
			return SOURCE_ORDER[0];
		else 
			return MID;
	}
	else if(phase == 1)
	{
		if(SOURCE_ORDER[0] == SOLAR || SOURCE_ORDER[0] == HYDRO)
			return opposite(SOURCE_ORDER[0]);
		else if(SOURCE_ORDER[phase] == UNKNOWN)
			return light_check();
		else if(SOURCE_ORDER[phase+1] != UNKNOWN)
			return SOURCE_ORDER[phase+1];
	    else
			return MID;
	}
	else if(phase == 2)
	{
		if(SOURCE_ORDER[2] != WIND && SOURCE_ORDER[2] != UNKNOWN)
			return SOURCE_ORDER[2];
		else if(SOURCE_ORDER[2] == UNKNOWN && CURRENT != MID)
			return MID;
		else if(SOURCE_ORDER[2] == UNKNOWN)
			return light_check();
		else
			return SOLAR;
	}
	else
	{
		if(CURRENT == HYDRO)
			return HYDRO;
		else
			return SOLAR;
	}
}

void update_source_order(float cycle_start_time)
{
	//get the phase of the passed time
	int cycle_phase = get_phase(cycle_start_time);
	
	//printf("cycle_phase: %d\n", cycle_phase);
	
	if(cycle_phase > 2) return;
	
	if(SOURCE_ORDER[cycle_phase] == UNKNOWN)
	{
		
		if((CURRENT == HYDRO || CURRENT == SOLAR) && (CHARGED == DONE || CHARGED == TIME_UP))
		{
			SOURCE_ORDER[cycle_phase] = CURRENT;
		}
		else if(CURRENT == SOLAR)
			SOURCE_ORDER[cycle_phase] = SOLAR;
		else if(CURRENT == HYDRO && CHARGED == SIG_ERROR && SOURCE_ORDER[0] != WIND && SOURCE_ORDER[1]!=WIND)
			SOURCE_ORDER[cycle_phase] = WIND;
		else
			printf("Not enough information to make an accurate guess of source orders.\n");
	}
	
	//attempt to calculate what we believe the last phase source is
	SOURCE_ORDER[2] = calculate_last_source();
	
	//printf("SOURCE_ORDER: {%d,%d,%d} @ %f\n\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],CURRENT_TIME);
	
	return;
}

int calculate_last_source()
{
	// if either of the previous two sources are unknown we cannot predict the third
	if(SOURCE_ORDER[0] == UNKNOWN || SOURCE_ORDER[1] == UNKNOWN)
		return UNKNOWN;
	if(SOURCE_ORDER[0] == WIND)
		return opposite(SOURCE_ORDER[1]);
	if(SOURCE_ORDER[1] == WIND)
		return opposite(SOURCE_ORDER[0]);
	return WIND;
}

#endif
