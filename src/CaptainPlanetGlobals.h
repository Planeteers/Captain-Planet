#ifndef CAPTAIN_PLANET_GLOBALS_H
#define CAPTAIN_PLANET_GLOBALS_H

const int NUM_PHASES = 4;

const float PHASE[4] =
{ 60, 120, 180, 300};

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
#define MID 5

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

#define leftTophat 6
#define rightTophat 7
#define rightFrontIR 2
#define LIGHT_PORT 3

#define LIGHT_THRESHOLD 400
#define BAR_THRESHOLD 700

int CHARGED = 0;
int CURRENT = MID;
int PREV = NONE;
int DEST = NONE;
int CURRENT_PHASE = 0;

int CHARGING 		   = 6;
int ERROR 	 		   = 7;
int DONE 	 		   = 8;
int WAITING_FOR_SIGNAL = 9;
int TIME_UP			   = 10;

int GPIO_LINE_IN_ONE   = 8;
int GPIO_LINE_IN_TWO   = 9;
int GPIO_LINE_OUT_ONE  = 6;
int GPIO_LINE_OUT_TWO  = 7;

#endif
