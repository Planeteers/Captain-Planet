#include "ComplexMovement.h"

int HYDRO_IS_ON = 0;
int SOLAR_IS_ON = 0;
int WIND_IS_ON = 0;

const float COMP_TIME_LENGTH = 300.0;
float START_TIME;
float CURRENT_TIME;

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

void planner(int);
void move_from_solar_to(int);
void move_from_hyrdo_to(int);
void move_from_wind_to(int);
void move_from_flag_to(int);

void move_from_solar_to(int barcode)
{
	if(barcode == HYDRO)
		top();
	else if(barcode == WIND)
		diagonal();
	else
		bottom();
}

void move_from_hydro_to(int barcode)
{
	if(barcode == WIND)
		top();
	else if(barcode == FLAG)
		diagonal();
	else
		bottom();
}

void move_from_wind_to(int barcode)
{
	if(barcode == FLAG)
		top();
	else if(barcode == SOLAR)
		diagonal();
	else
		bottom();
}

void move_from_flag_to(int barcode)
{
	if(barcode == SOLAR)
		top();
	else if(barcode == HYDRO)
		diagonal();
	else
		bottom();
}

void start_timer()
{
	START_TIME = seconds();
	CURRENT_TIME = seconds() - START_TIME;
	while(CURRENT_TIME < COMP_TIME_LENGTH)
	{
		sleep(1.0);
		CURRENT_TIME = seconds()-START_TIME;
	}
}
