#include "Sensor.h"

int main()
{
	float angle;
	while(!black_button())
	{
		angle = angle_offset(0,1);
		if(angle < 1 && angle > -1)
			beep();
	}
}
