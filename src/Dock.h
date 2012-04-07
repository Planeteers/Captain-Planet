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

void docking_phase(int);
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
		docking_phase(corner);
		signal_from_arduino=charge(corner);
		undock();
		return signal_from_arduino;
	}
	return CHARGED;
}

//Complex Movement leaves us right in front of the cubbie. This will take us to the first barcode.
void docking_phase(int corner)
{
	int distance = 0;
	if(corner == HYDRO)
		distance = 4;
	else if(corner == FLAG)
		distance = 2;
	move_backward_at(6);
	bar_straight(-1);
	stop();
	move_backward(6-distance,3);
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
	#ifdef NO_ARDUINO
		return DONE;
	#endif
	int return_value = NONE;
	int signal_from_arduino = get_charge_signal();
	
	printf("Resseting by sending none a bunch\n");
	while(signal_from_arduino != WAITING_FOR_SIGNAL)
	{
		send_charge_signal(NONE);
		signal_from_arduino = get_charge_signal();
		printf("in reset\n");
	}
	
	printf("Setting charge state to corner\n");
    while(signal_from_arduino == WAITING_FOR_SIGNAL)
	{
		send_charge_signal(corner);
		signal_from_arduino = get_charge_signal();
		printf("in set state\n");
	}
	
	printf("dealing with response from setting state to corner\n");
	if(signal_from_arduino == CHARGING)
	{
		if(corner != FLAG)
		{
			WATCHDOG_ACTIVE = 1;
		}
		while(signal_from_arduino == CHARGING && !TIMER_INTERRUPT)
		{
			printf("charging, time: %f\n",CURRENT_TIME);
			signal_from_arduino = get_charge_signal();
		}
		WATCHDOG_ACTIVE = 0;
	}
	else if(signal_from_arduino == ERROR)
	{
		printf("We got a error when trying to charge!\n");
		return ERROR;
	}
	
	
	///Returning Done all the time even when expecting none
	printf("interrpreting signal from charge phase\n");
	if(signal_from_arduino == DONE)
		return DONE;
	else if(signal_from_arduino == ERROR)
		return ERROR;
	else if(signal_from_arduino == CHARGING)
	{
		//printf("Interrupting charging\n");
		while(signal_from_arduino != WAITING_FOR_SIGNAL)
		{
			send_charge_signal(NONE);
			signal_from_arduino = get_charge_signal();
			printf(".");
		}
		//printf("\nInterrupted!\n");
		return NONE;
	}
	else 
	{
		printf("Charge: WTF\n");
		return ERROR;
	}
}

int wait_for_change_from_arduino(int prev_signal_from_arduino)
{	
	int signal_from_arduino = get_charge_signal();
	while(signal_from_arduino != prev_signal_from_arduino)	
	{
		printf("in wait_for_change_from_arduino\n");
		signal_from_arduino = get_charge_signal();
		sleep(.5);
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
	if(gpio_line_one == 0 && gpio_line_two == 0)
	{
		printf("Recieved: WAITING_FOR_SIGNAL\n");
		return WAITING_FOR_SIGNAL;
	}
	if(gpio_line_one == 0 && gpio_line_two == 1)
	{
		printf("Recieved: ERROR\n");
		return ERROR;
	}
	if(gpio_line_one == 1 && gpio_line_two == 0)
	{
		printf("Recieved: DONE\n");
		return DONE;
	}
	if(gpio_line_one == 1 && gpio_line_two == 1)
	{
		printf("Recieved: CHARGING\n");
		return CHARGING;
	}
	if(gpio_line_one == -1 || gpio_line_two == -1)
	{
		return -1;
	}
}

#endif
