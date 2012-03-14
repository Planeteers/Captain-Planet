/**
 *  File Name:   Dock.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Defines docking functionality.
 **/
#include "Sensor.h"
#include "Movement.h"

#define LEFT 8
#define RIGHT 9
#define SOLAR 0
#define HYDRO 1
#define WIND 2
#define FLAG 3
#define NONE 4

#ifndef DOCK_H
#define DOCK_H

int DOCK_INTERRUPT = 0;

void docking_phase();
void send_charge_signal(int);
void bar_straight(int);
int charge(int);
void undock();

void dock(int corner)
{
	docking_phase();
	send_charge_signal(corner);
	send_charge_signal(NONE);
	undock();
}

//Complex Movement leaves us right in front of the cubbie. This will take us to the first barcode.
void docking_phase()
{
	move_forward_at(6);
    bar_straight(1);
	stop();
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
            set_gpio(0,0);
            set_gpio(1,0);
            break;
        case SOLAR:
            set_gpio(0,0);
            set_gpio(1,1);
            break;
        case HYDRO:
            set_gpio(0,1);
            set_gpio(1,0);
            break;
        case FLAG:
            set_gpio(0,1);
            set_gpio(1,1);
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
    send_charge_signal(corner);
	int signal_from_arduino = 0;
	while(!DOCK_INTERRUPT && !signal_from_arduino)
	{
		signal_from_arduino = get_gpio(5);
	}
   // while(charging())
    //sleep(1);
    //send_Charge_Signal(none);
}

void undock()
{
    move_forward_at(-6);
    bar_straight(-1);
	move_backward(6,14);
	block_digo_done();
	//straighten_off_wall(int right,int speed)
}

#endif
