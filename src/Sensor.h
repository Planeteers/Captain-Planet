/**
 *  File Name:   Sensor.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Defines basic sensor fucntions and conversions from raw sensor data to usable representations.
 **/

#include <stdio.h>
#include <math.h>

#define thetaOne 0.0
#define thetaTwo 8.0 
#define pie 3.14159
#define topHat1 14
#define topHat2 15

#ifndef SENSOR_H
#define SENSOR_H

float analog_to_inches(int);
float analog_to_inches_avg(int, int);
float radian_to_degree(float);
float degree_to_radian(float);
float angle_off_set(int, int);
int see_bar(int);
int bar_sensor(int, int);

float analog_to_inches(int port)
{
    return (5027.9*pow(analog10(port),-1.086));
}

float analog_to_inches_avg(int port,int iterations)
{
	float avg = 0;
	int i;
	for(i=0;i<iterations;i++)
	{
		avg+=analog_to_inches(port);
	}
	return (avg/((float)iterations));
}

float radian_to_degree(float radians)
{
	return(radians*(180.0/pie));
}

float degree_to_radian(float degree)
{
	return(degree*(pie/180));
}

float angle_off_set(int port1, int port2)
{
	float radians = atan2(analog_to_inches_avg(port1, 10)-analog_to_inches_avg(port2, 10),thetaTwo);
    return(radian_to_degree(radians));
}

int see_bar(int port1)
{
	return(!digital(port1));
}

int bar_sensor(int port1, int port2)
{
	return(see_bar(port1) && see_bar(port2));
}

#endif
