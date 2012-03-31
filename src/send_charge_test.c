#include "Dock.h"

int main()
{
	set_each_analog_state(1,1,1,1,1,1,0,0);
    serializer_connect();
	
	send_charge_signal(NONE);
	sleep(1);
	
	while(!b_button())
	{
		send_charge_signal(HYDRO);
		printf("sending HYDRO\n");
		get_charge_signal();
		//printf("recieved: %d\n\n",get_charge_signal());
	}
	while(b_button());
	while(!b_button())
	{
		send_charge_signal(NONE);
		printf("sending NONE\n");
		get_charge_signal();
	}
	
	
	serializer_disconnect();
}
