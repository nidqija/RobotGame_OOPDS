#include <iostream>
#include "frame.h"

using namespace std;

int main(){
    Robot robot;
    DrawFrame drawframe;
    LoopFrame loopframe;
    drawframe.drawTheFrame(robot);
    
    return 0;
}