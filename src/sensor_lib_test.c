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
	set_each_analog_state(1,1,1,1,1,1,0,0);
	while(!black_button())
	{
		//cbc_display_clear();
		printf("    see_bar(%d): %d\n",14,see_bar(14));
		printf("    see_bar(%d): %d\n",15,see_bar(15));
		printf("bar sensor (%d): %d\n",port_1, bar_sensor(14, 15));
		//printf("analog to inches (%d): %f\n",port_1,analog_to_inches_avg(port_1,10));
		//printf("analog to inches (%d): %f\n",port_2, analog_to_inches_avg(port_2,10));
		//printf("          angleOffSet: %f\n\n",angle_off_set(port_1,port_2));
		sleep(.3);
		
	}
}
