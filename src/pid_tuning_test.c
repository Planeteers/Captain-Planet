#include "Serial.h"

int main()
{
	serializer_connect();
	sprintf(obuf,"pwm 1:100\r");
	if(SendCommand())
	printf("success\n");
	else printf("fail\n");
	printf("output: %s\n",ibuf);
	serializer_disconnect();
}
