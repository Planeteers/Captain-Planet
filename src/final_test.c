#include "Planner.h"
#include "ComplexMovement.h"

void main()
{
	init_captain_planet_with_our_powers_combined();
	start_movement();
	
	int cycle_start_time;
	while(!black_button())
	{
		cycle_start_time = CURRENT_TIME;
		DESTINATION=calculate_desination();
		move_to(CURRENT,DESTINATION);
		CURRENT=DESTINATION;
		CHARGED = dock(CURRENT);
		update_source_order(cycle_start_time);
	}
	serializer_disconnect();
}
