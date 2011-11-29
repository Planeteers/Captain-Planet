/**
 * File Name:	movement.h
 * Date Made:	11-10-2011
 * Programmer:	Aaron Parker & David Lynn
 * Description:	Basic movement library for serializer.
 **/
 
 #include "serial.h"
 
 #define WHEEL_DIAMETER 2.25 //inches
 #define TICKS_PER_REV 450.0 //ish
 #define SECONDS_PER_LOOP 0.021
 #define PIE 3.14159
 #define WHEEL_CIRC (WHEEL_DIAMETER*PIE)
 #define TICKS_PER_DISTANCE
 
 #define WHEEL_BASE 8.5 //inches
 
 int moveForward(float distance, int vel);
 int driveDirect(int rspeed, float rdistance, int lspeed, float ldistance);
 int turnLeft(float degrees, int vel);
 
 /**
  * Moves forward fast. Distance is in inches.
  **/
 int moveForward(float distance, int vel)
 { 
	 return driveDirect(vel,distance,vel,distance);
 }
 
 int driveDirect(int rspeed, float rdistance, int lspeed, float ldistance)
 {
	 int rticks = (int)(rdistance*(TICKS_PER_REV/WHEEL_CIRC));
	 int lticks = (int)(ldistance*(TICKS_PER_REV/WHEEL_CIRC));
	 sprintf(obuf,"digo 1:%d:%d 2:%d:%d \r",rticks,rspeed,lticks,lspeed);
	 return SendCommand();
 }

 int turnLeft(float degrees, int vel)
 {
	 int arc_length = (WHEEL_BASE*PIE)/360.0*degrees;
	 
	 return driveDirect(vel,-arc_length,vel,arc_length);
 }
