/*Gera Jahja C++ Coursework : December 2020*/

#include "robot.h"
#include <string>

//define robot 
robot::robot(int robotNo, int robotTeam,int xCoord, int yCoord, int robotSteps, std::string robotDirection) :

    r(robotNo), t(robotTeam),x(xCoord),y(yCoord),s(robotSteps),d(robotDirection) {}


