#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "frame.h"
#include "shootingbot.h"

using namespace std;



int main() {
    LoopFrame loopFrame;
    LoopingRobotByPlayers NameRobot;
    loopFrame.LoopingFrameByRobot();
    NameRobot.getRobotNames();
    return 0;
}
