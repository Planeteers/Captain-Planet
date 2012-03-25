#include "Dock.h"

int main()
{
	set_each_analog_state(1,1,1,1,1,1,0,0);
    serializer_connect();
	while(!black_button())
	{
		send_charge_signal(HYDRO);
		printf("sending HYDRO\n");
		get_charge_signal();
		//printf("recieved: %d\n\n",get_charge_signal());
	}
	while(black_button());
	while(!black_button())
	{
		send_charge_signal(NONE);
		printf("sending NONE\n");
		get_charge_signal();
	}
	
	
	serializer_disconnect();
}
