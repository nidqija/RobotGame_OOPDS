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



using namespace std;




int main() {
    Battlefield game;
    game.PrintBattlefield();
    game.delay(2000);
// g++ main2.cpp -o main2.exe
// .\main2.exe

    return 0;
}