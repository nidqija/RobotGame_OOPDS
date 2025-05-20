#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include "frame2.h"


using namespace std;




    int main() {
    Battlefield bf;
    MovingBot movingbot;
    Robot Rrobot;
    
    bf.PrintBattlefield();
    movingbot.randomNumbers();
    movingbot.MovetheBot();


    return 0;


}