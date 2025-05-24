#ifndef FRAME2_H
#define FRAME2_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "robot2.h"
#include "shootingRobot.h"
using namespace std;

class Battlefield {
private:
    vector<Robot*> bots;
    vector<vector<string>> Grid;
    int extractedVal1 = 70, extractedVal2 = 30;
    ShootingBot shooter; //shooting bot instance

public:
    Robot robot;

     void delay(int milliseconds) {
        clock_t start_time = clock();
        while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 100)) {
        }
    }

    Battlefield() {
          srand(time(0));
        robot.DetectRobot();
        vector<Robot::RobotInfo> detected = robot.ReturnRobotDetecteds();

        for (const auto& info : detected) {
            ThinkingBot* tbot = new ThinkingBot();
            tbot->setX(info.PosInitX);
            tbot->setY(info.PosIntY);
            tbot->setSymbol(info.nameInitial);
            // Initialize lives for each robot
            for (auto& robotInfo : robot.detectedRobot) {
                if (robotInfo.nameInitial == info.nameInitial) {
                    robotInfo.lives = 3; // Set initial lives to 3
                    break;
                }
            }
            bots.push_back(tbot);
        }
        shooter.loadTargetsFromFile("input.txt");
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
                    //tbot->MovetheBot();

                    string decision = tbot->getDecision();
                    if (decision == "fire") {
                        cout << " — ";
                        shooter.startShooting(tbot->getX(), tbot->getY(), tbot->getSymbol(), robot.detectedRobot);

                        // No movement this step if firing
                   }  
                   else if (decision == "move") {
                       tbot->MovetheBot();
                        // Optionally print move info here if needed
                   }
                    else if (decision == "look") {
                    // Optionally print look info if desired
                   }

                    


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
     
    void simulateShooting() {
        for (Robot* bot : bots) {
            if (ThinkingBot* tbot = dynamic_cast<ThinkingBot*>(bot)) {
                // Call the ThinkAction method to decide what to do
                tbot->ThinkAction();
                
                // Get the decision made by the ThinkingBot
                string decision = tbot->getDecision();
                cout << "[THINK] " << tbot->getSymbol() << " decided to " << decision
                     << " at (" << tbot->getX() << "," << tbot->getY() << ")";
                if (decision == "fire") {
                    cout << " — ";
                    // Call the shooting method and pass the target coordinates
                    shooter.startShooting(tbot->getX(), tbot->getY(), tbot->getSymbol(), robot.detectedRobot);

                } else {
                    cout << ", no fire." << endl;
                }
                cout << "-----" << endl;
            }
        }
    }

    ~Battlefield() {
        for (Robot* bot : bots)
            delete bot;
    }
};

#endif // FRAME2_H


