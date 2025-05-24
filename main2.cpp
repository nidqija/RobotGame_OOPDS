#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "frame2.h"
#include "shootingRobot.h"
#include "robot2.h"


using namespace std;

int main() {
    srand(time(0));
    Battlefield game;
    game.PrintBattlefield();
    game.delay(2000);
<<<<<<< HEAD
// g++ main2.cpp -o main2.exe
// .\main2.exe
=======
    game.simulateShooting(); // Call the shooting simulation
>>>>>>> dell

    return 0;
}