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

    void delay(int milliseconds) {
        clock_t start_time = clock();
        while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000)) {
            // busy wait
        }
    }

public:
    Robot robot;
    vector<string> robotInitial;

    Battlefield() {
        srand(time(0));
        robot.DetectRobot();
        robotInitial = robot.ReturnVectorRobotInitial();

        for (int i = 0; i < 5; ++i) {
            if (i % 2 == 0) { // Even index → ThinkingBot
                ThinkingBot* tbot = new ThinkingBot();
                tbot->setX(2 + i);
                tbot->setY(2 + i);
                if (i < robotInitial.size()) {
                    tbot->setIcon(robotInitial[i]);
                } else {
                    tbot->setIcon("?");
                }
                bots.push_back(tbot);
            }
        }
    }

    void PrintBattlefield() {
        Grid.resize(extractedVal2, vector<string>(extractedVal1, " "));

        for (int step = 0; step < 100; ++step) {
            // Clear grid
            for (int y = 0; y < extractedVal2; ++y)
                for (int x = 0; x < extractedVal1; ++x)
                    Grid[y][x] = ((y == 0 || y == extractedVal2 - 1 || x == 0 || x == extractedVal1 - 1) ? "*" : " ");

            // Move and place each bot
            for (Robot* bot : bots) {
                // ThinkingBot logic
                if (ThinkingBot* tbot = dynamic_cast<ThinkingBot*>(bot)) {
                    tbot->ThinkAction();
                }

                // MovingBot logic
                if (MovingBot* mbot = dynamic_cast<MovingBot*>(bot)) {
                    mbot->MovetheBot();
                }

                int x = max(1, min(bot->getX(), extractedVal1 - 2));
                int y = max(1, min(bot->getY(), extractedVal2 - 2));
                bot->setX(x);
                bot->setY(y);

               Grid[y][x] = bot->getSymbol() ;
            }

            // Draw grid
            delay(2500); // adjust if needed
            system("cls"); // use "clear" for Linux/macOS
            for (const auto& row : Grid) {
                for (const auto& cell : row)
                    cout << cell;
                cout << endl;
            }
        }
    }

    ~Battlefield() {
        for (Robot* bot : bots) {
            delete bot;
        }
    }
};

#endif // FRAME2_H
