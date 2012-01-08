#include "Movement.h"

int main()
{
	serializer_connect();
	sprintf(obuf,"vel\r");
	if(SendCommand())
	printf("success\n");
	else printf("fail\n");
	printf("output: %s\n",ibuf);
	serializer_disconnect();
}
