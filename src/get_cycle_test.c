#include "Planner.h"

int main()
{
	init_captain_planet_with_our_powers_combined();
	
	int phase = get_phase(CURRENT_TIME);
	
	while(!black_button())
	{
		int phase = get_phase(CURRENT_TIME);
		
		printf("%d\n",phase);
	}
	
	serializer_disconnect();
}
