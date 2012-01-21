/**
 *  File Name:   sensor_lib_test.c
 *  Date Made:   01-14-2012
 *  Programmer:  Aaron Parker
 *  Description: testing Sensor library functions
 **/
 
 #include "Sensor.h"
 
int main()
{
	int port_1 = 0;
	int port_2 = 1;
	printf("analog to inches (%d): %d\n",port_1,analogToInches(port_1));
	printf("analog to inches (%d): %d\n",port_2, analogToInches(port_2));
	printf("          angleOffSet: %d\n",angleOffSet(port_1,port_2));
}
