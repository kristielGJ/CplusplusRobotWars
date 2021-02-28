/*Gera Jahja C++ Coursework : December 2020*/

#include "command.h"
#include "robot.h"
#include <iostream>
#include <algorithm>

using namespace std;

/*returns robots in accending order*/
bool compare_robotNo(robot& robot1, robot& robot2) {

	return robot1.getRobotNumber() < robot2.getRobotNumber();
}

/*returns in order of most steps taken*/
bool compare_robotSteps(robot& robot1, robot& robot2) {

	return robot1.getRobotSteps() < robot2.getRobotSteps();
}

/*list all the current positions of all the robots still in the system*/
void command::show_command(vector<robot> &robots) {

	// vector sorted in accending order
	sort(robots.begin(), robots.end(), compare_robotNo);

	//prints existing robots to console, in the same format as start.tx
	for (robot& robot : robots) {

		cout << robot.getRobotNumber() << " " << robot.getRobotTeam() << " " << robot.getXCoord() << " " << robot.getYCoord() << " " << endl;
	}
}

/*list each existing robot number with number of steps they have traveled 
* should then be sorted in accending order*/
void command::travelled_command(vector<robot>& robots) {

	sort(robots.begin(), robots.end(), compare_robotNo);
	sort(robots.begin(), robots.end(), compare_robotSteps);

	for (robot& robot : robots) {
		cout <<robot.getRobotNumber()<<" " << robot.getRobotSteps() << "\n";
	}
}

/*take n as attribute (n=steps within origin -> user input)
* calculate and return no. of robots within n steps of the origin (0,0?):*/
void command::within_command(vector<robot>& robots,int &n) {

	auto stepCheck = [n](robot& r) {return abs(r.getXCoord()) + abs(r.getYCoord()) <= n; };
	int amount = count_if(robots.begin(), robots.end(), stepCheck);
	cout << amount << "\n";
}

/*take r as attribute (robot number = r)
* Make robot r turn to the left, e.g:
*
* north -> west -> south -> east -> north*/
void command::turn_left_command(vector<robot>& robots, int& n) {

	int number = n;

	for (robot& robot : robots) {

		if (robot.getRobotNumber() == number) {

			if (robot.getRobotDirection() == "north") {

				robot.updateDirection("west");

			}else if(robot.getRobotDirection() == "west") {

				robot.updateDirection("south");

			}else if (robot.getRobotDirection() == "south") {

				robot.updateDirection("east");

			}else {

				robot.updateDirection("north");
			}
		}
	}
}

/*take r as atribute (robot number = r)
* Make robot r turn to the right, e.g:
*
* north -> east -> south -> west -> north*/
void command::turn_right_command(vector<robot>& robots, int& n) {
	
	int number = n;
	
	for (robot& robot : robots) {
	
		if (robot.getRobotNumber() == number) {
		
			if (robot.getRobotDirection() == "north") {
			
				robot.updateDirection("east");

			}else if (robot.getRobotDirection() == "east") {
				
				robot.updateDirection("south");

			}else if (robot.getRobotDirection() == "south") {
				
				robot.updateDirection("west");

			}else {
				
				robot.updateDirection("north");
			}
		}
	}
}

/* re-align pointer position for Different Teams
*/
void command::findRobot(vector<robot>& robots, int& n, int &x, int&y) {

	for (auto &tempR: robots) {
		if (tempR.getRobotNumber() ==n) {
			tempR.updateX(x);
			tempR.updateY(y);
			tempR.updateSteps(tempR.getRobotSteps() + 1);
			return;
		}

	}

}

/* Move case: robot from a different team is infront of robot n:
* Robot infront is destroyed
* Robot n moves forward
*/
bool command::testPositionIsFreeAndDifferentTeam(vector<robot>& robots, int& n) {

	auto test = [n](robot& r) {return r.getRobotNumber() == n; };
	auto find_position = find_if(robots.begin(), robots.end(), test);

	int x = find_position->getXCoord();
	int y = find_position->getYCoord();
	int robotStepNumber = find_position->getRobotSteps();
	
	for (auto p = robots.begin(); p != robots.end(); ++p)
	{

		if ((p->getRobotTeam() != find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord()) && (p->getYCoord() == find_position->getYCoord() + 1) && (find_position->getRobotDirection() == "north"))
		{
			robots.erase(p);
			y = y + 1;
	
			findRobot(robots, n, x, y);
			return true;
		}
		else if ((p->getRobotTeam() != find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord() + 1) && (p->getYCoord() == find_position->getYCoord()) && (find_position->getRobotDirection() == "east"))
		{
			robots.erase(p);
			x = x + 1;
			findRobot(robots, n, x, y);
	
			return true;
		}
		else if ((p->getRobotTeam() != find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord()) && (p->getYCoord() == find_position->getYCoord() - 1) && (find_position->getRobotDirection() == "south"))
		{
			robots.erase(p);
			y = y - 1;
			findRobot(robots, n, x, y);
			return true;
		}
		else if ((p->getRobotTeam() != find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord() - 1) && (p->getYCoord() == find_position->getYCoord()) && (find_position->getRobotDirection() == "west"))
		{
			robots.erase(p);
			x = x - 1;
			findRobot(robots, n, x, y);
			return true;
		}
	}
	return false;
}
	
/* Move case: robot from a same team is infront of robot n:
* Robot infront and robot n do not move 
*/
bool command::testPositionIsFreeAndSameTeam(vector<robot> &robots, int& n) {

	auto test = [n](robot& r) {return r.getRobotNumber() == n; };
	auto find_position = find_if(robots.begin(), robots.end(), test);

	int x = find_position->getXCoord();
	int y = find_position->getYCoord();
	
	for (auto p = robots.begin(); p != robots.end(); ++p)
	{
		if ((p->getRobotTeam() == find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord()) && (p->getYCoord() == find_position->getYCoord() + 1) && (find_position->getRobotDirection() == "north"))
		{
			return true;
		}
		else if ((p->getRobotTeam() == find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord() + 1) && (p->getYCoord() == find_position->getYCoord()) && (find_position->getRobotDirection() == "east"))
		{
			return true;
		}
		else if ((p->getRobotTeam() == find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord()) && (p->getYCoord() == find_position->getYCoord() - 1) && (find_position->getRobotDirection() == "south"))
		{
			return true;
		}
		else if ((p->getRobotTeam() == find_position->getRobotTeam()) && (p->getXCoord() == find_position->getXCoord() - 1) && (p->getYCoord() == find_position->getYCoord()) && (find_position->getRobotDirection() == "west"))
		{
			return true;
		}
	}
}

/* move in direction (i.e update robot object details)(coord addition:)
	* n+=(0,1)
	* s+=(0,-1)
	* e+=(1,0)
	* w+=(-1,0)
	
* if functions return false:
	move robot r one step in facing direction*/
void command::move_command(vector<robot>& robots, int& n) {

	//find robot position (n)
	auto test = [n](robot& r) {return r.getRobotNumber() == n; };
	auto find_position = find_if(robots.begin(), robots.end(), test);

	int x = find_position->getXCoord();
	int y = find_position->getYCoord();
	int robotStepNumber = find_position->getRobotSteps();

	if (testPositionIsFreeAndSameTeam(robots, n) == true) {
		//stays in the same position
		return;
	}
	else if (testPositionIsFreeAndDifferentTeam(robots,n) == false) {
		//move the robot
		if (find_position->getRobotDirection() == "north") {
			find_position->updateY(y + 1);
			find_position->updateSteps(robotStepNumber + 1);
		}
		else if (find_position->getRobotDirection() == "west") {

			find_position->updateX(x - 1);
			find_position->updateSteps(robotStepNumber + 1);
		}
		else if (find_position->getRobotDirection() == "east") {

			find_position->updateX(x + 1);
			find_position->updateSteps(robotStepNumber + 1);
		}
		else if (find_position->getRobotDirection() == "south") {

			find_position->updateY(y - 1);
			find_position->updateSteps(robotStepNumber + 1);
		}
	}
}


