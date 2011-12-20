/**
 *  File Name:   ComplexMovement.h
 *  Date Made:   12-20-2011
 *  Programmer:  David Lynn & Aaron Parker
 *  Description: Complex movements to navigate from one corner of an 8x8 square to another.
 **/

void top()
{
    turnLeft(30, 10);
    moveForward(5, 10);
    turnLeft(-30, 10);
    moveForward(3, 10);
    turnLeft(-90, 10);
    moveFowardAt(10);
    while(!barSensor());
    stop();
}

void bottom()
{
    turnLeft(90, 10);
    moveForward(5, 10);
    turnLeft(90, 10);
    moveForward(2, 10);
    turnLeft(-90, 10);
    moveFowardAt(10);
    while(!barSensor());
    stop();
}

void diagonal()
{
    turnLeft(90, 10);
    moveForward(7, 10);
    turnLeft(-90, 10);
    moveFowardAt(10);
    while(!barSensor());
    stop();
}
