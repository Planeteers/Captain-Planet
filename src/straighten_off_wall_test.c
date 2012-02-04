#include "Movement.h"

int main()
{
	serializer_connect();
	turn_left(90.,1);
	block_digo_done();
	print_encoders();
	sleep(1.0);
	//straighten_off_wall(14,10);
	serializer_disconnect();
}

