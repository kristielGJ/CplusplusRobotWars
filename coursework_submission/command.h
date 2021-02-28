/*Gera Jahja C++ Coursework : December 2020*/

#ifndef COMMAND_H
#define COMMAND_H

#include "robot.h"
#include <vector>

class command
{

public: 

	void show_command(std::vector<robot> &robots);
	void travelled_command(std::vector<robot>& robots);
	void within_command(std::vector<robot>& robots,int &n);

	void turn_left_command(std::vector<robot>& robots, int& n);
	void turn_right_command(std::vector<robot>& robots, int& n);
	
	void findRobot(std::vector<robot>& robots, int& n, int& x, int& y);
	bool testPositionIsFreeAndDifferentTeam(std::vector<robot>& robots, int& n);
	bool testPositionIsFreeAndSameTeam(std::vector<robot>& robots, int& n);

	void move_command(std::vector<robot>& robots, int& n);
	

};
#endif



