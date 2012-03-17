// Created on Wed Mar 14 2012
#include "ComplexMovement.h"
#include "Planner.h"

int main() 
{
	init_captain_planet_with_our_powers_combined();
	
	/*while(!black_button())
		printf("current_time: %f\nsolar: %d\nwind: %d\nhydro: %d\n\n\n",CURRENT_TIME,SOLAR_IS_ON,WIND_IS_ON,HYDRO_IS_ON);*/
	move_to(NONE,SOLAR);
	dock(SOLAR);
	move_to(SOLAR, HYDRO);
	dock(HYDRO);
	
    serializer_disconnect();
}
