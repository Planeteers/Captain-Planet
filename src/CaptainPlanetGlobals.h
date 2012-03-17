#ifndef CAPTAIN_PLANET_GLOBALS_H
#define CAPTAIN_PLANET_GLOBALS_H

//
const float SOLAR_TIMES[][2] = {
	{-1, -1}
};

const float HYDRO_TIMES[][2] = {
	{-1, -1}
};

const float WIND_TIMES[][2] = {
	{-1, -1}
};

const float COMP_TIME_LENGTH = 300.0;
float START_TIME;
float CURRENT_TIME;

int TIMER_PROCESS_ID;

#define LEFT 8
#define RIGHT 9
#define SOLAR 0
#define HYDRO 1
#define WIND 2
#define FLAG 3
#define NONE 4
#define SPEED 14

int HYDRO_IS_ON = 0;
int SOLAR_IS_ON = 0;
int WIND_IS_ON = 0;

#define SPEED 14
#define WALL_SPEED 8
#define WALL_TURN_DISTANCE 2.2

#define WHEEL_DIAMETER 2.31 //Diameter of the wheels
#define TICKS_PER_REV_RIGHT 463.0	//number of ticks for a full revolution
#define TICKS_PER_REV_LEFT  463.0
#define PIE 3.14159
#define WHEEL_CIRC (WHEEL_DIAMETER*PIE)	//calculation for the circumference of 
										//the wheels
#define WHEEL_BASE 9.0 //distance between center of wheels



#define thetaOne 0.0
#define thetaTwo 8.0 
#define pie 3.14159

#define leftTophat 14
#define rightTophat 15
#define rightFrontIR 2

#endif
