#include "Planner.h"

void main()
{
	init_captain_planet_with_our_powers_combined();
	start_movement();
	CURRENT = MID;
	
	float cycle_start_time;
	while(CURRENT_TIME != INVALID_TIME)
	{
		cycle_start_time = CURRENT_TIME;
		DESTINATION=calculate_destination();
		move_to(CURRENT,DESTINATION);
		CURRENT = DESTINATION;
		CHARGED = dock(CURRENT);
		update_source_order(cycle_start_time);
	}
	
	serializer_disconnect();
}
