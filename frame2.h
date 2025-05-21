#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "robot2.h"
using namespace std;

class Battlefield {
private:
    vector<MovingBot> bots;
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
            MovingBot bot;
            bot.setX(2 + i);
            bot.setY(2 + i);
            if (i < robotInitial.size()) {
                bot.setIcon(robotInitial[i]);
            } else {
                bot.setIcon("?");
            }
            bots.push_back(bot);
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
            for (auto& bot : bots) {
                bot.MovetheBot();
                int x = max(1, min(bot.getX(), extractedVal1 - 2));
                int y = max(1, min(bot.getY(), extractedVal2 - 2));
                bot.setX(x);
                bot.setY(y);
                Grid[y][x] = bot.getIcon();
            }

            // Draw grid
            delay(1200); // half-second delay
            system("cls"); // for Windows
            for (const auto& row : Grid) {
                for (const auto& cell : row)
                    cout << cell;
                cout << endl;
            }
        }
    }
};


