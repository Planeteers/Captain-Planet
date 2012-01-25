#include "ComplexMovement.h"

#define solar 1
#define hydro 2
#define wind  3 
#define flag  4

void planner(int);
void move_from_solar(int);
void move_from_hyrdo(int);
void move_from_wind(int);
void move_from_flag(int);


void move_from_solar(int barcode)
{
	if(barcode == hydro)
		top();
	else if(barcode == wind)
		diagonal();
	else
		bottom();
}

void move_from_hydro(int barcode)
{
	if(barcode == wind)
		top();
	else if(barcode == flag)
		diagonal();
	else
		bottom();
}

void move_from_wind(int barcode)
{
	if(barcode == flag)
		top();
	else if(barcode == solar)
		diagonal();
	else
		bottom();
}

void move_from_flag(int barcode)
{
	if(barcode == solar)
		top();
	else if(barcode == hydro)
		diagonal();
	else
		bottom();
}
