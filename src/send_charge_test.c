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
			printf("result of charge: %d\n",charge(HYDRO));
		}
		else if(b_button())
		{
			while(b_button());
			printf("result of charge: %d\n",charge(SOLAR));
		}
		else if(up_button())
		{
			while(up_button());
			printf("result of charge: %d\n",charge(FLAG));
		}
	
	
	serializer_disconnect();
}
