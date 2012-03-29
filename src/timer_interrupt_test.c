// Created on Wed Mar 28 2012

#include "Planner.h"

int main() 
{
	init_captain_planet_with_our_powers_combined();
	
	while(!black_button())
	{
		WATCHDOG_ACTIVE = 1;
		printf("Time: %f\ntimer_interrupt: %d\n\n",CURRENT_TIME,TIMER_INTERRUPT);
		if(TIMER_INTERRUPT)
			WATCHDOG_ACTIVE = 0;
		sleep(1);
	}
	
	serializer_disconnect();
}
