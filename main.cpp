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
    LoopFrame frame;
    srand(time(0)); // Seed for random positions
    while(true){
     frame.LoopingFrameByRobot();
     return 0;
    }
  
}
