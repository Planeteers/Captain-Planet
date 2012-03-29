#include "Planner.h"

int main()
{
	printf("SOURCE_ORDER: {%d,%d,%d}\nLast Source: %d\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],calculate_last_source());
	SOURCE_ORDER[0] = SOLAR;
	SOURCE_ORDER[1] = HYDRO;
	while(!black_button());
	while(black_button());
	printf("SOURCE_ORDER: {%d,%d,%d}\nLast Source: %d\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],calculate_last_source());
	SOURCE_ORDER[0] = WIND;
	SOURCE_ORDER[1] = HYDRO;
	while(!black_button());
	while(black_button());
	printf("SOURCE_ORDER: {%d,%d,%d}\nLast Source: %d\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],calculate_last_source());
	SOURCE_ORDER[0] = WIND;
	SOURCE_ORDER[1] = SOLAR;
	while(!black_button());
	while(black_button());
	printf("SOURCE_ORDER: {%d,%d,%d}\nLast Source: %d\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],calculate_last_source());
	SOURCE_ORDER[0] = SOLAR;
	SOURCE_ORDER[1] = WIND;
	while(!black_button());
	while(black_button());
	printf("SOURCE_ORDER: {%d,%d,%d}\nLast Source: %d\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],calculate_last_source());
	SOURCE_ORDER[0] = HYDRO;
	SOURCE_ORDER[1] = WIND;
	while(!black_button());
	while(black_button());
	printf("SOURCE_ORDER: {%d,%d,%d}\nLast Source: %d\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],calculate_last_source());
	SOURCE_ORDER[0] = HYDRO;
	SOURCE_ORDER[1] = SOLAR;
	while(!black_button());
	while(black_button());
	printf("SOURCE_ORDER: {%d,%d,%d}\nLast Source: %d\n",SOURCE_ORDER[0],SOURCE_ORDER[1],SOURCE_ORDER[2],calculate_last_source());
}
