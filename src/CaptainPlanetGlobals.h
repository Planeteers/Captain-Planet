#ifndef CAPTAIN_PLANET_GLOBALS_H
#define CAPTAIN_PLANET_GLOBALS_H

#define NO_ARDUINO

#define NUM_PHASES 4
#define COMP_TIME_LENGTH 300.0
#define INVALID_TIME -1

#define SPEED 14
#define WALL_SPEED 14
#define WALL_TURN_DISTANCE 2.2

#define WHEEL_DIAMETER 2.31 //Diameter of the wheels
#define TICKS_PER_REV_RIGHT 463.0	//number of ticks for a full revolution
#define TICKS_PER_REV_LEFT  463.0
#define PIE 3.14159
#define WHEEL_CIRC (WHEEL_DIAMETER*PIE)	//calculation for the circumference of 
										//the wheels
#define WHEEL_BASE 8.6 //distance between center of wheels

#define thetaOne 0.0
#define thetaTwo 8.0 
#define pie 3.14159

#define leftTophat 6
#define rightTophat 7
#define rightFrontIR 2
#define LIGHT_PORT 3

#define LIGHT_THRESHOLD 400
#define BAR_THRESHOLD 700

#define GPIO_LINE_IN_ONE 8  //red
#define GPIO_LINE_IN_TWO 9  //black
#define GPIO_LINE_OUT_ONE 6 //yellow
#define GPIO_LINE_OUT_TWO 7 //green

#define ACCEL_THRESHOLD 45

const enum {
	CHARGING = 0,
	ERROR,
	DONE,
	WAITING_FOR_SIGNAL,
	TIME_UP
}SIGNALS;

const enum {
	SOLAR = 0,
	HYDRO,
	WIND,
	FLAG,
	NONE,
	MID,
	ALL,
	UNKNOWN
}CORNERS;

const float PHASE_TIMES[NUM_PHASES] = { 60, 120, 180, COMP_TIME_LENGTH};

float START_TIME;
float CURRENT_TIME;

int WATCHDOG_ACTIVE = 0;
int TIMER_INTERRUPT = 0;
int CHARGED = 0;
int CURRENT = MID;
int DESTINATION = NONE;

int TIMER_PROCESS_ID;
int TIMER_WATCHDOG_ID;

int SOURCE_ORDER[NUM_PHASES] = {UNKNOWN,UNKNOWN,UNKNOWN,ALL};

#endif
