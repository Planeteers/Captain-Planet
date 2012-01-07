#include "Serial.h"
int main()
{
	//printf("test");
	serializer_connect();
	while(!black_button())
	{
		printf("setting to 1\n");
		SetGPIO(0,1);
		sleep(1);
		printf("setting to 0\n");
		SetGPIO(0,0);
		sleep(1);
	}
	serializer_disconnect();
}

/*Function definitions go below.*/
