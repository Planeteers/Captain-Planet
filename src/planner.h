#include "ComplexMovement.h"

int HYDRO_IS_ON = 0;
int SOLAR_IS_ON = 0;
int WIND_IS_ON = 0;

const float COMP_TIME_LENGTH = 3.0;
float START_TIME;
float CURRENT_TIME;

int TIMER_PROCESS_ID;

//
const float HYDRO_TIMES[][2] = {
	{0.0,60.0}
};

const float SOLAR_TIMES[][2] = {
	{0.0,60.0},
	{70.,130.}
};

const float WIND_TIMES[][2] = {
	{0.0,60.0}
};

void start_timer();
void init_captain_planet_with_our_powers_combined();

void start_timer()
{
	START_TIME = seconds();
	CURRENT_TIME = seconds() - START_TIME;
	while(CURRENT_TIME < COMP_TIME_LENGTH)
	{
		sleep(1.0);
		CURRENT_TIME = seconds()-START_TIME;
	}
	CURRENT_TIME = -1;
}

void init_captain_planet_with_our_powers_combined()
{
	set_each_analog_state(1,1,1,1,1,1,0,0);
    serializer_connect();
	TIMER_PROCESS_ID = start_process(start_timer);
}
