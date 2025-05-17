#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "frame.h"
#include "shootingRobot.h"

using namespace std;

int main() {
    LoopFrame loopFrame;
    LoopingRobotByPlayers NameRobot;
    loopFrame.LoopingFrameByRobot();
    NameRobot.getRobotNames();

    //shootingrobot section ----------------------
    ShootingBot shooter(3); 
    shooter.loadTargetsFromFile("input.txt"); //reads robot from file
    shooter.startShooting(); //print shooting messgaes

    shooter.reload(2); //reloads bullets
    shooter.startShooting(); //shoots again
    
}
