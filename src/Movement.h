/**
 * File Name:   Movement.h
 * Date Made:   11-10-2011
 * Programmer:  Aaron Parker & David Lynn
 * Description: Basic movement library for serializer.
 **/
 
#include "Serial.h"
#include "Sensor.h"
#include "CaptainPlanetGlobals.h"
 
#ifndef MOVEMENT_H
#define MOVEMENT_H
 
int block_digo_done();
int is_digo_done();
int move_forward(float distance, int speed);
int move_forward_speed(float distance, int rspeed, int lspeed);
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
float distance_traveled();
int straighten_off_wall(int right,int speed);
int stop();
int move_forward_off_wall(float dist, int speed);
int move_backward_off_wall(float dist, int speed);

/**
 *	moves forward while continuously polling the side pointing IR sensor. if 
 *	the distance becomes significantly different from the first recorded value,
 *	vear either direction to straighten with the wall.
 **/
int move_backward_off_wall(float dist, int speed)
{
	float dist_from_wall = analog_to_inches_avg(rightFrontIR,10);
	float dist_traveled = 0;
	float cur_dist;
	clear_encoders();
	move_forward_at(-speed);
	while(dist_traveled <= dist)
	{
		cur_dist = analog_to_inches_avg(rightFrontIR,10);
		//printf("\ndist: %f\ncurrent_dist: %f\n",dist,dist_traveled);
		if(cur_dist <= dist_from_wall)
		{
			//printf("too close to wall\n");
			drive_direct_at(-speed+1,-speed);
			sleep(.05);
			move_forward_at(-speed);
			sleep(.05);
		}
		else if(cur_dist > dist_from_wall+.1)
		{
			//printf("too far from wall\n");
			drive_direct_at(-speed,-speed+2);
			sleep(.05);
			move_forward_at(-speed);
			sleep(.05);
		}
		dist_traveled = -distance_traveled();
	}
	stop();
}

/**
 *	moves forward while continuously polling the side pointing IR sensor. if 
 *	the distance becomes significantly different from the first recorded value,
 *	vear either direction to straighten with the wall.
 **/
int move_forward_off_wall(float dist, int speed)
{
	float dist_from_wall = analog_to_inches_avg(rightFrontIR,10);
	float dist_traveled = 0;
	float cur_dist;
	clear_encoders();
	move_forward_at(speed);
	while(dist_traveled <= dist)
	{
		cur_dist = analog_to_inches_avg(rightFrontIR,10);
		//printf("\ncur_dist: %f\nrecorded_dist: %f\n",cur_dist,dist_from_wall);
		if(cur_dist <= dist_from_wall)
		{
			//printf("too close to wall\n");
			drive_direct_at(speed-2,speed);
			sleep(.05);
			move_forward_at(speed);
			sleep(.05);
		}
		else if(cur_dist > dist_from_wall+.1)
		{
			//printf("too far from wall\n");
			drive_direct_at(speed,speed-1);
			sleep(.05);
			move_forward_at(speed);
			sleep(.05);
		}
		dist_traveled = distance_traveled();
	}
	stop();
}

/**
 *	estimate how many degrees from parallel we are using the side pointing IR 
 *	sensors and turn right that angle. if the angle is negative we will turn 
 *	left
 **/
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

/**
 *	query's the serializer for the encoder values and converts the returned 
 *	value into an inch distance based off of wheel circ. assumes straight 
 *	forward movement, i.e. turning will break this.
 *
 *	returns the distance traveled in inches as a float.
 **/
float distance_traveled()
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
	//printf("renc: %f\nlenc: %f\n",rdist,ldist);
	return (rdist+ldist)/2;
}

/**
 *	print the current values of the encoders to the screen.
 **/
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
 
/**
 *	block all robot logic until the digo command is done.
 **/
int block_digo_done()
{
	//sleep(.1);
	int is_done = 0;
	while(is_done != 2) 
	{
		is_done = is_digo_done();
		//printf("blocking till done! %d\n", is_done);
	}
	return 1;
}
 
/**
 *	ask if the digo command is done.
 **/
int is_digo_done()
{
    sprintf(obuf,"pids\r");
    if(send_command())
    {
        //printf("{%c,%c,%c}\n",ibuf[0],ibuf[1],ibuf[2]);
        if(ibuf[2] == '0')
           return 2;
        else return 1;
    }
	else
	{
		sleep(.1);
		illegal_command();
		//printf("%s\n",ibuf);
	}
    return NACK;
}
 
/**
 *	Moves forward Distance at speed rating. distance is in inches and speed 
 *	is 1-15.
 **/
int move_forward(float distance, int speed)
{ 
    return drive_direct(speed,distance,speed,distance);
}

/**
 *	Move forward a certain distance at specified speed. used to make the robot
 *	"vear" to the left and right, while still moving forward.
 **/
int move_forward_speed(float distance, int lspeed, int rspeed)
{
	return drive_direct(lspeed,distance,rspeed,distance);
}

/**
 *	Moves backward Distance at speed rating. distance is in inches and speed is 
 *	1-15.
 **/
int move_backward(float distance, int speed)
{
    return move_forward(-distance, speed);
}

/**
 *	drives each motor directly distance in inches at speed rating speed (1-15).
 *	distance is in inches, speed is a value between 1-15
 **/
int drive_direct(int lspeed, float ldistance, int rspeed, float rdistance)
{
    float rticks = (rdistance*(TICKS_PER_REV_RIGHT/WHEEL_CIRC));
    float lticks = (ldistance*(TICKS_PER_REV_LEFT/WHEEL_CIRC));
    sprintf(obuf,"digo 2:%d:%d 1:%d:%d\r",(int)rticks,rspeed,(int)lticks,lspeed);
    //printf("(r,l): (%f,%f)\n",rticks,lticks);
    return send_command();
}

/**
 *	Direct drive using only velocity control. (1-15)
 **/
int drive_direct_at(int lspeed, int rspeed)
{
    sprintf(obuf,"mogo 1:%d 2:%d\r",rspeed,lspeed);
    return send_command();
}

/**
 *	simplified version of drive_direct_at. only drives forward.
 **/
int move_forward_at(int speed)
{
    return drive_direct_at(speed, speed);
}

/**
 *	simplified version of drive_direct_at. only drives backward.
 **/
int move_backward_at(int speed)
{
    return drive_direct_at(-speed,-speed);
}

/**
 *	turns left at speed, speed is a value between 1-15
 **/
int turn_left_at(int speed)
{
    return drive_direct_at(speed,-speed);
}

/**
 *	turns right at speed, speed is a value between 1-15
 **/
int turn_right_at(int speed)
{
    return drive_direct_at(-speed,speed);
}

/**
 *	turns left specifed number of degrees at speed (1-15)
 **/
int turn_left(float degrees, int speed)
{
    float arc_length = (WHEEL_BASE*PIE)/360.0*degrees;
    
    return drive_direct(speed,arc_length,speed,-arc_length);
}

/**
 *	turns right specified number of degrees at speed (1-15)
 **/
int turn_right(float degrees, int speed)
{
	int offset = degrees*(1.1/90.0);
    return turn_left(-degrees+offset, speed);
}

/**
 *	sends the stop command to the serializer.
 **/
int stop()
{
    sprintf(obuf,"stop\r");
    return send_command();
}

#endif
