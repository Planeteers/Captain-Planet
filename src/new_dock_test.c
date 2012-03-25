
#include "Planner.h"

int main()
{
	init_captain_planet_with_our_powers_combined();
	move_to(MID, SOLAR);
	dock(SOLAR);
	move_to(SOLAR, MID);
	//dock(HYDRO);
	move_to(MID, HYDRO);
	dock(HYDRO);
	move_to(HYDRO, MID);

	serializer_disconnect();
}
