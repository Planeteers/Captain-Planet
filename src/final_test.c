#include "Planner.h"
#include "ComplexMovement.h"

void main()
{
	init_captain_planet_with_our_powers_combined();
	start_movement();
	move_to(MID, SOLAR);
	dock(SOLAR);
	move_to(SOLAR,MID);
	move_to(MID,HYDRO);
	dock(HYDRO);
	move_to(HYDRO,MID);
	/*while(!black_button())
	{
		DEST=calculate_desination();
		move_to(CURRENT,DEST);
		PREV=CURRENT;
		CURRENT=DEST;
		DEST=NONE;
		CHARGED = dock(CURRENT);
		CURRENT_PHASE++;
	}*/
	serializer_disconnect();
}
