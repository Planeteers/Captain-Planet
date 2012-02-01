#include "Movement.h"

int main()
{
	serializer_connect();
	//move_forward(12.0,5.);
	sleep(1.0);
	stop();
	distance_traveled();
	serializer_disconnect();
}

/*Function definitions go below.*/
