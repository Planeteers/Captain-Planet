/**
 * File Name:   Movement.h
 * Date Made:   11-10-2011
 * Programmer:  Aaron Parker & David Lynn
 * Description: Basic movement library for serializer.
 **/
 
#include "Serial.h"
#include "Sensor.h"
 
#ifndef MOVEMENT_H
#define MOVEMENT_H
 
#define WHEEL_DIAMETER 2.25 //inches
#define TICKS_PER_REV_RIGHT 463.0//450.0 //ish
#define TICKS_PER_REV_LEFT  463.0
#define SECONDS_PER_LOOP 0.021
#define PIE 3.14159
#define WHEEL_CIRC (WHEEL_DIAMETER*PIE)
#define TICKS_PER_DISTANCE
 
#define WHEEL_BASE 8.50 //inches
 
int block_digo_done();
int is_digo_done();
int move_forward(float distance, int speed);
int move_backward(float distance, int speed);
int move_forward_at(int speed);
int move_backward_at(int speed);
int drive_direct_at(int rspeed, int lspeed);
int drive_direct(int rspeed, float rdistance, int lspeed, float ldistance);
int turn_left(float degrees, int speed);
int turn_right(float degrees, int speed);
int turn_left_at(int speed);
int turn_right_at(int speed);
int print_encoders();
int distance_traveled();
 
int straighten_off_wall(int right,int speed)
{
	float angle;
	int i;
	for(i = 0;i<3;i++)
	{
		angle = angle_offset(0,1);
		if(angle < 1.0 && angle > -1.0) return 0;
		turn_right(angle,speed);
	}
	return 1;
}
 
int distance_traveled()
{
	sprintf(obuf,"getenc 1\r");
	int renc, lenc;
	if(send_command())
	{
		lenc = atoi(ibuf);
		//printf("number: %d\nnumber: %d",number1,number2);
	}
	sprintf(obuf,"getenc 2\r");
	if(send_command())
	{
		renc = atoi(ibuf);
	}
	float rdist = renc*WHEEL_CIRC/TICKS_PER_REV_RIGHT;
	float ldist = lenc*WHEEL_CIRC/TICKS_PER_REV_LEFT;
	printf("renc: %f\nlenc: %f\n",rdist,ldist);
}
 
int print_encoders()
{
	sprintf(obuf,"getenc 1 2\r");
	if(send_command())
    {
        int i;
        for(i = 1;i < 20;i++)
        {
            if(ibuf[i] != '\n' && ibuf[i] != '>')
			printf("%c",ibuf[i]);
        }
		printf("\n");
	}
	return NACK;
}
 
int block_digo_done()
{
	while(!is_digo_done());
	return 1;
}
 
int is_digo_done()
{
    sprintf(obuf,"pids \r");
    if(send_command())
    {
        //printf("{%c,%c,%c}\n",ibuf[0],ibuf[1],ibuf[2]);
        if(ibuf[2] == '1')
           return 0;
        else return 1;
    }
    return NACK;
}
 
/**
 * Moves forward Distance at speed rating. distance is in inches and speed is 1-15
 **/
int move_forward(float distance, int speed)
{ 
    return drive_direct(speed,distance,speed,distance);
}

/**
 * Moves backward Distance at speed rating. distance is in inches and speed is 1-15
 **/
int move_backward(float distance, int speed)
{
    return move_forward(-distance, speed);
}

/**
 * drives each motor directly distance in inches at speed rating speed (1-15).
 **/
int drive_direct(int rspeed, float rdistance, int lspeed, float ldistance)
{
    float rticks = (rdistance*(TICKS_PER_REV_RIGHT/WHEEL_CIRC));
    float lticks = (ldistance*(TICKS_PER_REV_LEFT/WHEEL_CIRC));
    sprintf(obuf,"digo 2:%d:%d 1:%d:%d \r",(int)rticks,rspeed,(int)lticks,lspeed);
    //printf("(r,l): (%f,%f)\n",rticks,lticks);
    return send_command();
}

/**
 * Direct drive using only velocity control. (1-15)
 **/
int drive_direct_at(int rspeed, int lspeed)
{
    sprintf(obuf,"mogo 1:%d 2:%d \r",rspeed,lspeed);
    return send_command();
}

/**
 * Drive forward at speed
 **/
int move_forward_at(int speed)
{
    return drive_direct_at(speed, speed);
}

/**
 * Drive backward at speed
 **/
int move_backward_at(int speed)
{
    return drive_direct_at(-speed,-speed);
}

/**
 * turns left at speed
 **/
int turn_left_at(int speed)
{
    return drive_direct_at(speed,-speed);
}

/**
 * turns right at speed
 **/
int turn_right_at(int speed)
{
    return drive_direct_at(-speed,speed);
}

/**
 * turns left specifed number of degrees at speed (1-15)
 **/
int turn_left(float degrees, int speed)
{
    float arc_length = (WHEEL_BASE*PIE)/360.0*degrees;
    
    return drive_direct(speed,arc_length,speed,-arc_length);
}

/**
 * turns right specified number of degrees at speed (1-15)
 **/
int turn_right(float degrees, int speed)
{
    return turn_left(-degrees, speed);
}

/**
 * 
 **/
int stop()
{
    sprintf(obuf,"stop \r");
    return send_command();
}

#endif
