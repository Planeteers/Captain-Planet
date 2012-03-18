#include "Planner.h"

void main()
{
	init_captain_planet_with_our_powers_combined();
	start_movement();
	while(!black_button())
	{
		DEST=logic();
		move_to(CURRENT,DEST);
		PREV=CURRENT;
		CURRENT=DEST;
		DEST=NONE;
		CHARGED = dock(CURRENT);
		CURRENT_PHASE++;
	}
	serializer_disconnect();
}
