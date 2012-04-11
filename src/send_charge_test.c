#include "Dock.h"

int main()
{
	set_each_analog_state(1,1,1,1,1,1,0,0);
	serializer_connect();
	
	send_charge_signal(NONE);
	
	printf("press a to send hydro\npress b to send solar\npress up to send flag\n\n");
	
	while(!a_button() && !b_button() && !up_button());
	if(a_button())
	{
		while(a_button());
		while(!b_button())
		{
			send_charge_signal(HYDRO);
			printf("sending: HYDRO\n");
			get_charge_signal();
			printf("\npress: B to stop\n\n\n");
			sleep(.5);
		}
	}
	else if(b_button())
	{
		while(b_button());
		while(!b_button())
		{
			send_charge_signal(SOLAR);
			printf("sending: SOLAR\n");
			get_charge_signal();
			printf("\npress: B to stop\n\n\n");
			sleep(.5);
		}
	}
	else if(up_button())
	{
		while(up_button());
		while(!b_button())
		{
			send_charge_signal(FLAG);
			printf("sending: FLAG\n");
			get_charge_signal();
			printf("\npress: B to stop\n\n\n");
			sleep(.5);
		}
	}
	while(b_button());
	while(!b_button())
	{
		send_charge_signal(NONE);
		printf("sending NONE\n");
		get_charge_signal();
		printf("\nPress: B to end the program\n\n\n");
		sleep(.5);
	}
	
	
	serializer_disconnect();
}
