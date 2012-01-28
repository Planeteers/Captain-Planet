/**
 *  File Name:   Serial.h
 *  Date Made:   11-10-2011
 *  Programmer:  Aaron Parker
 *  Description: Serial library for communicating to the serializer board onboard a stinger robot. 
 **/

#ifndef SERIAL_H
#define SERIAL_H

#define   BUF_SIZE   64
#define   LEFT       1
#define   RIGHT      2
#define   ACK        1
#define   NACK       0
#define   TRUE       1
#define   FALSE      0
#define   CHAR_DLY   0.001

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
    int   SendCommand(void) ;
    int   Drive(int, int) ;
    int   PIDinit(void) ;
    int   IsDone(void) ;
    int   IllegalCommand(void) ;
    void  serializer_disconnect(void) ;


/*Function definitions go below.*/

#ifdef __APPLE__
size_t strnlen(const char *s, size_t n)
{
  const char *p = (const char *)memchr(s, 0, n);
  return(p ? p-s : n);
}
#endif

#ifdef __WIN32

void  serializer_connect(void) {}
int   SendCommand(void) {return 0;}
int   Drive(int x, int y) {return 0;}
int   PIDinit(void) {return 0;}
int   IsDone(void) {return 0;}
int   IllegalCommand(void) {return 0;}
void  serializer_disconnect(void) {}
void  send_psoc();

#else
/*
 *  Function to initialize the serial port on back of CBC
*/
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

/*
 * Routine to send a command to the Serializer 3.0 
 * Command should be placed in global output buffer, obuf.
 * Waits for response from the Serializer which is placed in ibuf.
*/

int SendCommand() 
{
    int   bytes_read ;
    
    write(SERIALIZER, obuf, strnlen(obuf, BUF_SIZE));
    sleep(BUF_SIZE * CHAR_DLY) ; // wait for response from Serializer
    bytes_read = read(SERIALIZER, ibuf, BUF_SIZE);  // get the response
    if ( (bytes_read != 0) && (strstr(ibuf, NACKstr) == NULL) ) return ACK ;
    else return NACK ;
}


// Set PID default parameters for Stinger platform

int PIDinit() 
{       
    sprintf(obuf, "rpid s\r") ; 
    if(SendCommand()) return ACK ;  
    else return NACK ;
}

// Routine used to drive the Stinger specified distance at specified velocity

int  Drive(int DistInTics, int VelInTics)
{
    sprintf(obuf, "digo %d:%d:%d %d:%d:%d\r", 
            LEFT, DistInTics, VelInTics, RIGHT, DistInTics, VelInTics) ;    
    if (SendCommand()) return ACK ;
    else return NACK ;
}

// Routine to check if Serializer is ready to accept a new digo command
// pids command is used to query Serializer about its readiness
// Serializer will send back CR, LF and then either a 0 or a 1
// A 1 means the Serializer is still busy performing previous digo command
// ibuf[0] is CR, ibuf[1] is LF
//

int IsDone() 
{
    sprintf(obuf, "pids\r") ;   
    if (!SendCommand()) return FALSE ;
    if (ibuf[2] == '0') return TRUE ;
    else return FALSE ;
    
}

int SetGPIO(int pin, int value)
{
    sprintf(obuf,"setio %d:%d\r",pin,value);
    if(!SendCommand()) return FALSE;
    return TRUE;
}

// Routine to send the Serializer a bad command

int  IllegalCommand()
{
    sprintf(obuf, "gle 0 1\r") ;    // No such command
    if (SendCommand()) return ACK ;
    else return NACK ;
}

void serializer_disconnect()
{
    close(SERIALIZER);
}
#endif
#endif

