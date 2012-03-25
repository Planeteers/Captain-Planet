#include "Dock.h"
#include "CaptainPlanetGlobals.h"

int main()
{
	init_captain_planet_with_our_powers_combined();
	dock(HYDRO);
	
	serializer_disconnect();
}
