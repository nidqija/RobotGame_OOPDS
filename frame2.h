#ifndef FRAME2_H
#define FRAME2_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "robot2.h"
using namespace std;

class Battlefield {
private:
    vector<Robot*> bots;
    vector<vector<string>> Grid;
    int extractedVal1 = 70, extractedVal2 = 30;

   

public:
    Robot robot;

     void delay(int milliseconds) {
        clock_t start_time = clock();
        while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 700)) {
        }
    }

    Battlefield() {
        srand(time(0));
        robot.DetectRobot();
        vector<Robot::RobotInfo> detected = robot.ReturnRobotDetecteds();

        for (const auto& info : detected) {
            ThinkingBot* tbot = new ThinkingBot();
            tbot->setX(info.PosInitX);
            tbot->setY(info.PosInitY);
            tbot->setSymbol(info.nameInitial);
            bots.push_back(tbot);
        }
    }

    void PrintBattlefield() {
        Grid.resize(extractedVal2, vector<string>(extractedVal1, " "));

        for (int step = 0; step < 100; ++step) {
            for (int y = 0; y < extractedVal2; ++y)
                for (int x = 0; x < extractedVal1; ++x)
                    Grid[y][x] = ((y == 0 || y == extractedVal2 - 1 || x == 0 || x == extractedVal1 - 1) ? "*" : " ");

            for (Robot* bot : bots) {
                if (ThinkingBot* tbot = dynamic_cast<ThinkingBot*>(bot)) {
                    tbot->ThinkAction();
                    tbot->MovetheBot();
                }

                int x = max(1, min(bot->getX(), extractedVal1 - 2));
                int y = max(1, min(bot->getY(), extractedVal2 - 2));
                bot->setX(x);
                bot->setY(y);

                Grid[y][x] = bot->getSymbol();
            }

            delay(250); // reduced for better speed
            system("cls"); // use "clear" on Linux/macOS
            for (const auto& row : Grid) {
                for (const auto& cell : row)
                    cout << cell;
                cout << endl;
            }
        }
    }

    ~Battlefield() {
        for (Robot* bot : bots)
            delete bot;
    }
};

#endif // FRAME2_H
