#include "Planner.h"
int main()
{
	
		printf("press a to send hydro\npress b to send solar\npress up to send flag\n\n");
	
		while(!a_button() && !b_button() && !up_button());
		if(a_button())
		{
			while(a_button());
			init_captain_planet_with_our_powers_combined();
			//kill_process(TIMER_WATCHDOG_ID);
			printf("result of charge: %d\n",charge(HYDRO));
		}
		else if(b_button())
		{
			while(b_button());
			init_captain_planet_with_our_powers_combined();
			//kill_process(TIMER_WATCHDOG_ID);
			printf("result of charge: %d\n",charge(SOLAR));
		}
		else if(up_button())
		{
			while(up_button());
			init_captain_planet_with_our_powers_combined();
			//kill_process(TIMER_WATCHDOG_ID);
			printf("result of charge: %d\n",charge(FLAG));
		}
	
	kill_process(TIMER_PROCESS_ID);
	serializer_disconnect();
}
