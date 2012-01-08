/***************************************************************************
*********  This comment area should be filled with a description  
*********         of your program and what it does.               
***************************************************************************/
/* Libraries used in Botball are automatically included, but list any additional includes below */
/* #defines and constants go below.*/

/* Global variables go below (if you absolutely need them).*/

/*Function prototypes below*/
#include "Movement.h"

int main()
{
	serializer_connect();
	while(!black_button())
	{
		print_encoders();
		sleep(.1);
	}
	stop();
	serializer_disconnect();
}

/*Function definitions go below.*/
