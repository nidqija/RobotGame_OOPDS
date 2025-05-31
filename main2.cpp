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
#include "lookingRobot.h"


using namespace std;

int main() {
    srand(time(0));
    Battlefield game;
    game.PrintBattlefield();

    return 0;
}