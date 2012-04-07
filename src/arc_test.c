#include "Planner.h"

int main()
{
	init_captain_planet_with_our_powers_combined();
	move_arc(95, 12*3.2525252525252525252);
	block_digo_done();
	run_into_wall(SPEED);
	serializer_disconnect();
}
