#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "frame.h"

using namespace std;



int main() {
    LoopFrame loopFrame;
    loopFrame.LoopingFrameByRobot();
    return 0;
}
