#include <stdio.h>
#include <math.h>
#define thetaOne 0
#define thetaTwo 6

int main()
{
}

int analogToInches(int port)
{
	return (5027.9*pow(analog10(port),1.086));
	//set_each_analog_state(1,1,1,1,1,1,0,0);
}

int angleOffSet(int port1, int port2)
{
	return(atan2(analogToInches(port1)-analogToInches(port2)-thetaOne,thetaTwo));
}

