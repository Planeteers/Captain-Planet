/**
 *  File Name:   Serial.h
 *  Date Made:   11-10-2011
 *  Programmer:  Aaron Parker
 *  Description:	Serial library for communicating to the serializer board 
 *					onboard a stinger robot. It's important to note that all 
 *					serial commands wait a certain amount of time before 
 *					returning.
 **/

#ifndef SERIAL_H
#define SERIAL_H

//size of the i/o buffer used to communicate with the serializer
#define   BUF_SIZE   64
#define   LEFT       1 //left motor number
#define   RIGHT      2 //right motor number
#define   ACK        1 //Acknowledged signal
#define   NACK       0 //not acknowledged signal
#define   TRUE       1 
#define   FALSE      0
#define   CHAR_DLY   0.001 //amount of time to sleep to send one character 
							//over serial

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef __WIN32
#include <sys/select.h>
#include <termios.h>
#endif

#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define CREATE_UART "/dev/uart1"

// Serial input and outpus buffers

    char   ibuf[BUF_SIZE] = "" ;
    char   obuf[BUF_SIZE] = "" ;
    char   NACKstr[]= "NACK" ;
    int    SERIALIZER ;

/*Function prototypes below*/

    void  serializer_connect(void) ;
    int   send_command(void) ;
    int   drive(int, int) ;
    int   pid_init(void) ;
    int   is_done(void) ;
    int   illegal_command(void) ;
    void  serializer_disconnect(void) ;


/*Function definitions go below.*/

//if compiling on an apple computer create the strnlen function.
#ifdef __APPLE__
size_t strnlen(const char *s, size_t n)
{
  const char *p = (const char *)memchr(s, 0, n);
  return(p ? p-s : n);
}
#endif

//if compiling on windows, just create empty definitions for all functions
#ifdef __WIN32

void  serializer_connect(void) {}
int   send_command(void) {return 0;}
int   drive(int x, int y) {return 0;}
int   pid_init(void) {return 0;}
int   is_done(void) {return 0;}
int   illegal_command(void) {return 0;}
void  serializer_disconnect(void) {}

#else
/**
 *	Function to initialize the serial port on back of CBC
 **/
void serializer_connect() {
    
    int     fd = -1 ;
    struct  termios oldtio,newtio;
    
    fd = open(CREATE_UART, O_RDWR | O_NONBLOCK);
    if (fd<0) {
        perror(CREATE_UART); 
        printf("Serial port init failed ... aborting!\r") ;
        exit(-1);
    }
    tcgetattr(fd,&oldtio);
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = CS8 | CREAD;
    tcflush(fd, TCIOFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);  
    SERIALIZER = fd ;
	
    return ;
}

/**
 *	Routine to send a command to the Serializer 3.0 
 *	Command should be placed in global output buffer, obuf.
 *	Waits for response from the Serializer which is placed in ibuf.
 **/
int send_command() 
{
    int   bytes_read ;
    
    write(SERIALIZER, obuf, strnlen(obuf, BUF_SIZE));
    sleep(BUF_SIZE * CHAR_DLY) ; // wait for response from Serializer
    bytes_read = read(SERIALIZER, ibuf, BUF_SIZE);  // get the response
    if ( (bytes_read != 0) && (strstr(ibuf, NACKstr) == NULL) ) return ACK ;
    else {
		printf("FAILURE\n");
		//illegal_command();
		return NACK ;
	}
}

/**
 *	initialize the pid control on the stinger (only have to call once)
 **/
int pid_init() 
{       
    sprintf(obuf, "rpid s\r") ; 
    if(send_command()) return ACK ;  
    else return NACK ;
}

/**
 *	set the general purpose I/O line on the serializer to value, (high or low)
 **/
int set_gpio(int pin, int value)
{
    sprintf(obuf,"setio %d:%d\r",pin,value);
    if(!send_command()) return FALSE;
    return TRUE;
}

/**
 *	send an illegal command to the serializer for testing purposes.
 **/
int  illegal_command()
{
    sprintf(obuf, "gle 0 1\r") ;    // No such command
    if (send_command()) return ACK ;
    else return NACK ;
}

/**
 *	disconnect from the serializer
 **/
void serializer_disconnect()
{
    close(SERIALIZER);
}

/**
 *	clear the encoders stored value.
 **/
int clear_encoders()
{
	sprintf(obuf, "clrenc 1 2\r");
	if(send_command()) return ACK;
	else return NACK;
}
#endif	//end the else of if __WIN32
#endif

