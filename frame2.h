#ifndef FRAME2_H
#define FRAME2_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "robot2.h"
#include "shootingRobot.h"
#include "lookingRobot.h"
using namespace std;    

class Battlefield {
private:
    vector<Robot*> bots;
    vector<vector<string>> Grid;
    int extractedVal1 = 70, extractedVal2 = 30;
    ShootingBot shooter;
    LookingBot looker;
    ScoutBot scouter;
    string robotChoices;

public:
    Robot robot;

    void delay(int milliseconds) {
        clock_t start_time = clock();
        while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 80)) {}
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
            bots.push_back(tbot);
        }

        shooter.loadTargetsFromFile("input.txt");
    }

    void PrintBattlefield() {
        Grid.resize(extractedVal2, vector<string>(extractedVal1, " "));

        for (int step = 0; step < 100; ++step) {
            // Reset battlefield
            for (int y = 0; y < extractedVal2; ++y)
                for (int x = 0; x < extractedVal1; ++x)
                    Grid[y][x] = ((y == 0 || y == extractedVal2 - 1 || x == 0 || x == extractedVal1 - 1) ? "*" : " ");

            for (Robot* bot : bots) {
                if (ThinkingBot* tbot = dynamic_cast<ThinkingBot*>(bot)) {
                    // Check hide status every turn
                    tbot->UpdateHideStatus(robot.detectedRobot);

                    // If still hidden, skip rendering and actions
                    if (tbot->getHidden()) continue;

                    // Decide and act
                    tbot->ThinkAction();
                    string decision = tbot->getDecision();

                    if (decision == "fire") {
                        bool destroyed = shooter.startShooting(tbot->getX(), tbot->getY(), tbot->getSymbol(), robot.detectedRobot, tbot->getSymbol());

                        // remove destroyed bots frm battlefield
                        if (destroyed) {
                            auto it = std::find(bots.begin(), bots.end(), tbot);
                            if (it != bots.end()) {
                                delete *it;
                                bots.erase(it);
                                continue;
                            }
                        }
                        int robotSelection2 = rand() % 10;
                        switch (robotSelection2) {
                            case 0: robotChoices = "HideBot"; break;
                            case 1: robotChoices = "JumpBot"; break;
                            case 2: robotChoices = "LongShotBot"; break;
                            case 3: robotChoices = "SemiAutoBot"; break;
                            case 4: robotChoices = "ThirtyShotBot"; break;
                            case 5: robotChoices = "ScoutBot"; break;
                            case 6: robotChoices = "TrackBot"; break;
                            case 7: robotChoices = "AvoiderBot"; break;
                            case 8: robotChoices = "RegenBot"; break;
                            case 9: robotChoices = "SpeedyBot"; break;

                        }

                        cout << "Robot " << tbot->getSymbol() << " chooses upgrade: " << robotChoices << "!\n";

                        if (robotChoices == "HideBot") {

                            string result = tbot->HideAction(robot.detectedRobot, tbot->getSymbol());
                            cout << "[HIDE] " << tbot->getSymbol() << ": " << result << endl;

                        } 

                        else if ( robotChoices == "JumpBot"){
                            cout << tbot->getSymbol() << " becomes JumpBot!" << endl; 
                            JumpBot* jbot = new JumpBot();
                            jbot -> setX(tbot->getX());
                            jbot-> setY(tbot->getY());
                            jbot -> setSymbol(tbot->getSymbol());

                              auto it = std::find(bots.begin(), bots.end(), tbot);
                              if (it != bots.end()) {
                                 delete *it;
                                  *it = jbot;
                                }

                                 string jumpResult = jbot->JumpAction(robot.detectedRobot, jbot->getSymbol());
                                 cout << "[JUMP] " << jbot->getSymbol() << ": " << jumpResult << endl;
                                 continue;
                        }

                        else if (robotChoices == "AvoiderBot") {
                            cout << tbot->getSymbol() << " becomes AvoiderBot!" << endl;
                            AvoiderBot* abot = new AvoiderBot();
                            abot->setX(tbot->getX());
                            abot->setY(tbot->getY());
                            abot->setSymbol(tbot->getSymbol());

                            auto it = std::find(bots.begin(), bots.end(), tbot);
                            if (it != bots.end()) {
                                delete *it;
                                *it = abot;
                             }
                             string avoidResult = abot->AvoidAction(robot.detectedRobot, abot->getSymbol());
                             cout << "[AVOID] " << abot->getSymbol() << ": " << avoidResult << endl;
                             continue;
                        } 
                        
                        else if (robotChoices == "RegenBot"){
                            cout << tbot->getSymbol() << " becomes RegenBot!" << endl;
                            RegenBot* rbot = new RegenBot();
                            rbot -> setX(tbot->getX());
                            rbot -> setY(tbot->getY());
                            rbot-> setSymbol(tbot->getSymbol());
                            auto it = find(bots.begin(), bots.end(), tbot);
                            if (it != bots.end()) {
                                delete *it;
                                *it = rbot;
                             }

                             string regenResult = rbot->generateHealthRobot(robot.detectedRobot,rbot->getSymbol());
                             cout << "[REGEN] " << rbot->getSymbol() << ": " << regenResult << endl;
                             continue;
                        }
                        else if (robotChoices == "SpeedyBot") {
                            cout << tbot->getSymbol() << " becomes SpeedyBot!" << endl;
                            SpeedyBot* sbot = new SpeedyBot();
                            sbot->setX(tbot->getX());
                            sbot->setY(tbot->getY());
                            sbot->setSymbol(tbot->getSymbol());

                            auto it = std::find(bots.begin(), bots.end(), tbot);
                            if (it != bots.end()) {
                                delete *it;
                                *it = sbot;
                            }
                            string speedResult = sbot->SpeedAction();
                            cout << "[SPEED] " << sbot->getSymbol() << ": " << speedResult << endl;
                            continue;
                        }

                        else if (robotChoices == "ScoutBot"){

                            ScoutBot* sbot = dynamic_cast<ScoutBot*>(tbot);
                            
                            if (dynamic_cast<ScoutBot*>(tbot)) {
                                cout << tbot->getSymbol() << " is already a ScoutBot!" << endl;
                                sbot->ScoutAction(robot.detectedRobot);
                            } 
                            
                            else {
                                cout << tbot->getSymbol() << " becomes ScoutBot!" << endl;
                                ScoutBot* newSbot = new ScoutBot();  
                                newSbot->setX(tbot->getX());
                                newSbot->setY(tbot->getY());
                                newSbot->setSymbol(tbot->getSymbol());

                                auto it = find(bots.begin(), bots.end(), tbot);
                                if (it != bots.end()) {
                                    delete *it;
                                    *it = newSbot;
                                }

                                newSbot->ScoutAction(robot.detectedRobot); 
                            }

                            continue;
                        }

                        else if (robotChoices == "longShotBot") {
                            cout << tbot->getSymbol() << "becomes LongShotBot!" << endl;
                            LongShotBot* lshotBot = new LongShotBot();
                            lshotBot->setX(tbot->getX());
                            lshotBot->setY(tbot->getY());
                            lshotBot->setSymbol(tbot->getSymbol());

                            auto it = std::find(bots.begin(), bots.end(), tbot);
                            if (it != bots.end()) {
                                delete *it;
                                *it = lshotBot;
                            }
                            continue;
                            
                        }

                        else if (robotChoices == "ThirtyShotBot") {
                            cout << tbot->getSymbol() << " becomes ThirtyShotBot!" << endl;
                            ThirtyShotBot* tshotBot = new ThirtyShotBot();
                            tshotBot->setX(tbot->getX());
                            tshotBot->setY(tbot->getY());
                            tshotBot->setSymbol(tbot->getSymbol());

                            auto it = std::find(bots.begin(), bots.end(), tbot);
                            if (it != bots.end()) {
                                delete *it;
                                *it = tshotBot;
                            }
                            continue;
                        }



                    } else if (decision == "move") {
                        tbot->MovetheBot();
                    } else if (decision == "look") {
                        looker.LookAction(tbot, robot.detectedRobot);
                    }
                }

                // Clamp position and place on grid if not hidden
                int x = max(1, min(bot->getX(), extractedVal1 - 2));
                int y = max(1, min(bot->getY(), extractedVal2 - 2));
                bot->setX(x);
                bot->setY(y);
                if (!bot->getHidden())
                    Grid[y][x] = bot->getSymbol();
            }

            delay(250);
            system("cls"); // Use "clear" on macOS/Linux
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
    };
};

#endif // FRAME2_H