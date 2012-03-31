#include "Planner.h"
#include "ComplexMovement.h"

void main()
{
	init_captain_planet_with_our_powers_combined();
	start_movement();
	
	float cycle_start_time;
	while(!black_button())
	{
		cycle_start_time = CURRENT_TIME;
		DESTINATION=calculate_destination();
		printf("Setting Dest to: %d from: %d\n",DESTINATION,CURRENT);
		move_to(CURRENT,DESTINATION);
		CURRENT=DESTINATION;
		CHARGED = dock(CURRENT);
		printf("dock returned: %d\n", CHARGED);
		update_source_order(cycle_start_time);
		printf("SOURCE_ORDER: {%d,%d,%d} @ %f\n\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],cycle_start_time);
	}
	serializer_disconnect();
}
