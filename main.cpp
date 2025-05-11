#include <iostream>
#include "frame.h"

using namespace std;

int main(){
    Robot robot;
    GenericRobot generic;
    LoopFrame loopframe;
    loopframe.LoopingFrameByRobot();
    generic.Move();
    return 0;
}