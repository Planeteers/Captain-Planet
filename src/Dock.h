/**
 *  File Name:   Dock.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Defines docking functionality.
 **/
#include "Sensor.h"
#include "Movement.h"

#define left 8
#define right 9
#define solar 1
#define hydro 2
#define wind 3
#define none 4
#define discharge 5 

#ifndef DOCK_H
#define DOCK_H

void docking_phase();
int scan_code();
void realign(int);
void send_charge_signal(int);
void bar_straight(int);
int charge(int);
void undock();


//Complex Movement leaves us right in front of the cubbie. This will take us to the first barcode.
void docking_phase()
{
	move_forward_at(6);
    bar_straight(1);
	stop();
	int code = scan_code();
	printf("%d", code);
	undock();
}

//Goes four inches reading each barcode and then returns the barcode
int scan_code()
{
    int leftCode = 1;
	int rightCode = 1;
	int preRight = 0;
	int preLeft = 0;
	int curRight = 0;
	int curLeft = 0;

	
	move_forward(4, 4);
	while(!is_digo_done())
	{
		curRight = see_bar(leftTophat);
		curLeft = see_bar(rightTophat);
		if(curLeft && !preLeft)
			leftCode++;
		if(curRight && !preRight)
			rightCode++;

		preLeft = curLeft;
		preRight = curRight;
	}
	printf("Barcode Left Number: %d", leftCode);
	printf("Barcode Right Number: %d", rightCode);
    return leftCode;
}

void realign(int corner)
{
    if(corner != wind)
    {
        turn_left(5, 10);
        move_forward(6, -10);
        move_forward(6, 10);
    }
    else
    {
        turn_left(-5, 10);
        move_forward(6, 10);
        move_forward(6, -10);
    }
}

/**
 * Signals serializer of which charge mode to currently be in.
 **/
void send_charge_signal(int corner)
{
    switch (corner)
    {
        case none:
            set_gpio(0,0);
            set_gpio(1,0);
            break;
        case solar:
            set_gpio(0,0);
            set_gpio(1,1);
            break;
        case hydro:
            set_gpio(0,1);
            set_gpio(1,0);
            break;
        case discharge:
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
	turn_left(185.0, 10);
	block_digo_done();
	//straighten_off_wall(int right,int speed)
}

#endif
