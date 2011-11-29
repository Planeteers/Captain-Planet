
#include "serial.h"

int main()
{
	serializer_connect();
	sprintf(obuf,"fw \r");
	if(SendCommand()) printf("worked\n");
	else printf("not worked\n");
	while(!IsDone());
	printf("%s\n",ibuf);
	serializer_disconnect();
}
