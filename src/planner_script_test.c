#include "planner.h"
#include "ComplexMovement.h"

int main()
{
	init_captain_planet_with_our_powers_combined();
	timing(0, FLAG);
	printf("DONE");
	timing(1, HYDRO);
	timing(2, SOLAR);
	serializer_disconnect();
}

