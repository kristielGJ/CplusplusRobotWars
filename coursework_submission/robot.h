#pragma once

#ifndef ROBOT_H
/*Gera Jahja C++ Coursework : December 2020*/

#define ROBOT_H
#include <string>

class robot {

private:

    int r, t, x, y,s;
    std::string d;

public:

    // Initialize robot info
    robot(int robotNo, int robotTeam, int xCoord, int yCoord, int robotSteps, std::string robotDirection);

    //getters
    int getRobotNumber() { return r; };
    int getRobotTeam() { return t; };
    int getXCoord() { return x; };
    int getYCoord() { return y; };
    int getRobotSteps() { return s; };
    std::string& getRobotDirection() { return d; };

    //setters
    void updateDirection(std::string newDir) {d = newDir;}
    void updateX(int newx) {x = newx;}
    void updateY(int newy) {y = newy;}
    void updateSteps(int newStep) {s =newStep;}

};
#endif
