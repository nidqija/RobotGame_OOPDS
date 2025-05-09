#include <iostream>
#include "frame.h"
#include "robot.h"

using namespace std;

int main(){
    DrawFrame drawframe;
    LoopFrame loopframe;
    drawframe.drawTheFrame();
    loopframe.LoopingFrameByRobot();
    
    return 0;
}