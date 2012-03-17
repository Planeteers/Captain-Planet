/**
 *  File Name:   Sensor.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Defines basic sensor fucntions and conversions from raw sensor data to usable representations.
 **/

#include <stdio.h>
#include <math.h>
#include "CaptainPlanetGlobals.h"

#ifndef SENSOR_H
#define SENSOR_H

float analog_to_inches(int);
float analog_to_inches_avg(int, int);
float radian_to_degree(float);
float degree_to_radian(float);
float angle_offset(int, int);
int see_bar(int);
int bar_sensor(int, int);

int analog_10_avg(int port)
{
	int i,j=0;
	for(i=0;i<10;i++)
	{
		j+=analog10(port);
	}
	return j/10;
}

float analog_to_inches(int port)
{
	float x = analog10(port);
	float ret;
	if(x<=350)
	{
		ret = (0.000589*powf(x,2))-(0.510602*x)+115.14;
	}
	else
	{
		ret =  (5027.9*pow(analog10(port),-1.086));
	}
	if(ret < 5.) return 5.;
	return ret;
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

//float left_avg_distance(int iterations)
//{
//	return (analog_to_inches_avg(leftFrontIR,iterations) + analog_to_inches_avg(leftBackIR,iterations))/2.0;
//}

//float right_avg_distance(int iterations)
//{
//	return (analog_to_inches_avg(rightFrontIR,iterations) + analog_to_inches_avg(rightBackIR,iterations))/2.0;
//}

float radian_to_degree(float radians)
{
	return(radians*(180.0/pie));
}

float degree_to_radian(float degree)
{
	return(degree*(pie/180));
}

float angle_offset(int port1, int port2)
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
