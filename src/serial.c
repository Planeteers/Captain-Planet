/**
 *	File Name:		serial.c
 *	Date Made:		11-10-2011
 *	Programmer:		Aaron Parker
 *	Description:	test driver for the serial.h library
 **/
 
#include "serial.h"

int main()
{
	float begin;
	float end;
	int ticks = 1000;
	int speed = 10;
	sleep(.7);
	//printf("begin: %f",begin);
	serializer_connect();
	sprintf(obuf,"cfg units 1\r");
	SendCommand();
	sprintf(obuf,"clrenc 1 2\r");
	SendCommand();
	begin = seconds();
	sleep(.7);
	begin = seconds();
	Drive(ticks,speed);
	while(!IsDone());
	end = seconds();
	sprintf(obuf,"getenc 1 2\r");
	SendCommand();
	printf("%s",ibuf);
	printf("begin: %f\n", begin);
	printf("end: %f\n", end);
	printf("difference: %f\n\n",end - begin);
	printf("ticks/second: %f\n",((float)(ticks))/(end-begin));
	//serializer_disconnect();
}
