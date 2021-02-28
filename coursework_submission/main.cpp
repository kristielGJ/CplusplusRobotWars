/*Gera Jahja C++ Coursework : December 2020
* Sources:
* https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
* https://stackoverflow.com/questions/36257202/c-changing-class-member-values-from-functions/36257312#36257312 */

#include "robot.h"
#include "command.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/*read command.txt*/
void read_command_file(std::vector<robot> &robots) {

    ifstream inFile2("commands.txt");
    std::string comm;
    command command;

    while (getline(inFile2, comm))
    {
        int b;
        string a;
        std::istringstream iss(comm);

        //if there are not two items on the line, then it must be either show or traveled
        if (!(iss >> a >> b)) {

            //calls commands functions that only recieve a string parameter
            if (comm.find("show") != string::npos) {
                command.show_command(robots);
            }
            else if (comm.find("travelled") != string::npos) {
                command.travelled_command(robots);
            }
        }
        //calls commands functions that  recieve a string AND an int parameter
        else {

            auto test = [b](robot r) {return r.getRobotNumber() == b; };
            int amount = count_if(robots.begin(), robots.end(), test);


            if (comm.find("within") != string::npos) {
               
                command.within_command(robots, b);
            }
            if (amount == 1) {
                if (comm.find("turnleft") != string::npos) {
                    command.turn_left_command(robots, b);
                   
                }
                else if (comm.find("turnright") != string::npos) {
                    command.turn_right_command(robots, b);
                    
                }
                else if (comm.find("move") != string::npos) {
                     command.move_command(robots, b);
                
                }
            }
        }
    }     
}

/*read command.txt, if robot does not exist,ignore command*/
void read_start_file(vector<robot> &robots){

    ifstream inFile1("start.txt");
    int r, t, x, y;
    int i = 0;
    while (inFile1 >> r >> t >> x>> y)
    {
        robots.emplace_back(robot(r, t, x,y,0,"north"));
        i += 1;
    }  
}

/*setup robot starting positions and run game commands*/
int main() {

    vector<robot> robots;

    read_start_file(robots);//set up map and robot initial positions
    read_command_file(robots);//edit robot attributes and display info

    return 0;

}
