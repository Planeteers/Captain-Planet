
#include "serial.h"

int main()
{
	serializer_connect();
	sprintf(obuf,"fw \r");
	printf("sending command: %s\n",obuf);
	if(SendCommand()==ACK)
		printf("returned: %s\n",ibuf);
	else
		printf("failed\n");
	serializer_disconnect();
}
