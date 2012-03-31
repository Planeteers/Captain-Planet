/**
 *  File Name:   Dock.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Defines docking functionality.
 **/
#include "Sensor.h"
#include "Movement.h"
#include "CaptainPlanetGlobals.h"

#ifndef DOCK_H
#define DOCK_H

void docking_phase();
void send_charge_signal(int);
void bar_straight(int);
int charge(int);
void undock();
int get_charge_signal();
int wait_for_change_from_arduino();

int dock(int corner)
{
	if(corner != MID)
	{
		int signal_from_arduino;
		docking_phase();
		signal_from_arduino=charge(corner);
		undock();
		return signal_from_arduino;
	}
	return CHARGED;
}

//Complex Movement leaves us right in front of the cubbie. This will take us to the first barcode.
void docking_phase()
{
	move_backward_at(6);
	bar_straight(-1);
	stop();
	move_backward(7.5,WALL_SPEED-1);
	block_digo_done();
	//printf("%d", code);
	//undock();
}

/**
 * Signals serializer of which charge mode to currently be in.
 **/
void send_charge_signal(int corner)
{
    switch (corner)
    {
        case NONE:
            set_gpio(GPIO_LINE_OUT_ONE,0);
            set_gpio(GPIO_LINE_OUT_TWO,0);
            break;
        case SOLAR:
            set_gpio(GPIO_LINE_OUT_ONE,0);
            set_gpio(GPIO_LINE_OUT_TWO,1);
            break;
        case HYDRO:
            set_gpio(GPIO_LINE_OUT_ONE,1);
            set_gpio(GPIO_LINE_OUT_TWO,0);
            break;
        case FLAG:
            set_gpio(GPIO_LINE_OUT_ONE,1);
            set_gpio(GPIO_LINE_OUT_TWO,1);
            break;
		default:
			printf("Invalid Switch Case: Dock.h, send_charge_signal\n");
			break;
    }
}

void bar_straight(int direction)
{
	while(!bar_sensor(rightTophat,leftTophat))
	{
		if(see_bar(leftTophat))
			drive_direct_at(direction*-1, direction*3);
		else if(see_bar(rightTophat))
			drive_direct_at(direction*3, direction*-1);
	} 
	stop();
	sleep(.1);
}

int charge(int corner)
{
	return ERROR;
	int return_value = NONE;
	int signal_from_arduino = get_charge_signal();
    send_charge_signal(corner);
	signal_from_arduino = wait_for_change_from_arduino(signal_from_arduino);
	
	if(signal_from_arduino == ERROR)
	{
		send_charge_signal(NONE);
		signal_from_arduino = wait_for_change_from_arduino(ERROR);
		if(signal_from_arduino != WAITING_FOR_SIGNAL)
			printf("Expected waiting for signal after recieving initial error (tried to charge but failed)\n");
		return ERROR;
	}
	else if(signal_from_arduino == CHARGING)
	{
		int prev_signal_from_arduino = signal_from_arduino;
		int start_time = CURRENT_TIME;
		WATCHDOG_ACTIVE = 1;
		while(!TIMER_INTERRUPT && signal_from_arduino != prev_signal_from_arduino)
		{
			signal_from_arduino = get_charge_signal();
			//printf("Time: %f\n",CURRENT_TIME);
			sleep(1.0);
		}
		WATCHDOG_ACTIVE = 0;
		if(signal_from_arduino == DONE)
			return_value = DONE;
		else if(signal_from_arduino == ERROR)
			return_value = ERROR;
		else
			return_value = TIME_UP;
		send_charge_signal(NONE);
		signal_from_arduino = wait_for_change_from_arduino(signal_from_arduino);
		if(signal_from_arduino != WAITING_FOR_SIGNAL)
			printf("We successfully started charging or timer interrupt, or we're full.\n");
		return return_value;
	}
	else
		printf("WTF\n");
	return ERROR;
}

int wait_for_change_from_arduino(int prev_signal_from_arduino)
{	
	int signal_from_arduino = get_charge_signal();
	while(signal_from_arduino != prev_signal_from_arduino)
	{
		signal_from_arduino = get_charge_signal();
		sleep(1.0);
	}	
	return signal_from_arduino;
}

void undock()
{
    move_forward_at(6);
    bar_straight(1);
	move_forward(10,SPEED);
	block_digo_done();
	//straighten_off_wall(int right,int speed)
}

int get_charge_signal()
{
	int gpio_line_one = get_gpio(GPIO_LINE_IN_ONE);
	int gpio_line_two = get_gpio(GPIO_LINE_IN_TWO);
	printf("recieving: %d%d\n\n",gpio_line_one,gpio_line_two);
	if(gpio_line_one == 0 && gpio_line_two == 0)
		return WAITING_FOR_SIGNAL;
	if(gpio_line_one == 0 && gpio_line_two == 1)
		return ERROR;
	if(gpio_line_one == 1 && gpio_line_two == 0)
		return DONE;
	if(gpio_line_one == 1 && gpio_line_two == 1)
		return CHARGING;
	if(gpio_line_one == -1 || gpio_line_two == -1)
		return -1;
}

#endif
