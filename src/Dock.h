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
#define topHat1 14
#define topHat2 15

#ifndef DOCK_H
#define DOCK_H

void docking_phase();
int scanCode();
void realign(int);
void send_Charge_Signal(int);
void bar_Straight();
int charge(int);
void dock(int);
void undock(int);

void align_with_bar()
{
	move_forward_at(6);
    while(!bar_sensor(topHat2,topHat1))
	{
		if(see_bar(topHat1))
			drive_direct_at(-1, 3);
		else if(see_bar(topHat2))
			drive_direct_at(3, -1);
	}
	stop();
	int code = scanCode();
	printf("Barcode Number: %d", code);
}

int scanCode()
{
    int code = 0;
    if(!bar_sensor(topHat1, topHat2))
    {
        move_forward(.4, -10);
        move_forward(10);
        while(!bar_sensor(topHat1, topHat2));
        stop();
    }
    code++;
	int i = 0;
    for(i=0; i<3; i++)
    {
        moveFoward(1,10);
        if(!bar_sensor(topHat1, topHat2))
            break;
        code++;
    }
    return code;
}

void realign(int corner)
{
    if(corner != wind)
    {
        turnLeft(5, 10);
        move_forward(6, -10);
        move_forward(6, 10);
    }
    else
    {
        turnLeft(-5, 10);
        move_forward(6, 10);
        move_forward(6, -10);
    }
}

/**
 * Signals serializer of which charge mode to currently be in.
 **/
void send_Charge_Signal(int corner)
{
    switch (corner)
    {
        case none:
            setGPIO(0,0);
            setGPIO(1,0);
            break;
        case solar:
            setGPIO(0,0);
            setGPIO(1,1);
            break;
        case hydro:
            setGPIO(0,1);
            setGPIO(1,0);
            break;
        case discharge:
            setGPIO(0,1);
            setGPIO(1,1);
            break;
    }
}

void bar_Straight()
{
    int rCurSensorSpeed = 0;
    int rPrevSensorSpeed = 0;
    int lCurSensorSpeed = 0;
    int lPrevSensorSpeed = 0;
    while(!bar_sensor(topHat1, topHat2))
    {
        if(see_bar(topHat1))
            lCurSensorSpeed = 100;
        else
            lCurSensorSpeed = -100;
        if(see_bar(topHat2))
            rCurSensorSpeed = 100;
        else
            rCurSensorSpeed = -100;
        if(rCurSensorSpeed != rPrevSensorSpeed || lCurSensorSpeed != lPrevSensorSpeed)
        {
            rPrevSensorSpeed = rCurSensorSpeed;
            lPrevSensorSpeed = lCurSensorSpeed;
            drive_Direct(rCurSensorSpeed, lCurSensorSpeed);
        }
    }
}

int charge(int corner)
{
    send_Charge_Signal(corner);
    while(charging())
    sleep(1);
    send_Charge_Signal(none);
}

void dock(int corner)
{
    if(corner != wind)
        moveFoward(11,10);
    else
        moveFoward(11,-10);
    charge(corner);
        
}

void undock(int corner)
{
    if(corner != wind)
    {
        moveFoward(14, -10);
        turnLeft(180, 10);
    }   
    else
        moveFoward(14, 10);
}

#endif
