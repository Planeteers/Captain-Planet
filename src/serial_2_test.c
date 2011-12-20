/**
 *  File Name:   serial_2_test.h
 *  Date Made:   12-20-2011
 *  Programmer:  Aaron Parker
 *  Description: tests serial connection by querying firmware versions.
 **/

#include "Serial.h"

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
