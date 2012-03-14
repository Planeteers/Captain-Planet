// Created on Wed Mar 14 2012
#include "ComplexMovement.h"
#include "planner.h"

int main() 
{
	init_captain_planet_with_our_powers_combined();
	
	while(!black_button())
	printf("Current_time: %f\n",CURRENT_TIME);
	move_to(FLAG, SOLAR);
	dock(SOLAR);
	move_to(SOLAR, HYDRO);
	dock(HYDRO);
	move_to(HYDRO, WIND);
	dock(WIND);
	move_to(WIND, FLAG);
	
    serializer_disconnect();
}
