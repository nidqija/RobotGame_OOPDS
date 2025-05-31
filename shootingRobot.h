#ifndef SHOOTING_ROBOT_H
#define SHOOTING_ROBOT_H

#include "robot2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cmath> 

using namespace std;

struct TargetInfo {
    string name;
    int x;
    int y;
};

class ShootingBot {
private:
    vector<TargetInfo> robotTargets;
    int robotSelection2;
    string robotChoices;

public:
    ShootingBot() {}

    void loadTargetsFromFile(const string& filename) {
        ifstream inputFile(filename);
        string line;

        if (!inputFile) {
            cout << "[ERROR] Could not open " << filename << endl;
            return;
        }

        while (getline(inputFile, line)) {
            if (line.find("GenericRobot") == 0) {
                istringstream iss(line);
                string tag, name;
                int rx, ry;
                iss >> tag >> name >> rx >> ry;
                robotTargets.push_back({name, rx, ry});
                cout << "[LOAD] Target: " << name << " at (" << rx << "," << ry << ")\n";
            }
        }

        inputFile.close();
    }

    bool isWithinRange(int shooterX, int shooterY, int targetX, int targetY, int range) {
        return abs(shooterX - targetX) + abs(shooterY - targetY) <= range;
    }

    bool startShooting(int shooterX, int shooterY, const string& targetName, vector<Robot::RobotInfo>& detectedRobots, const string& shooterInitial, bool isLongShot = false) {
        int shootRange = isLongShot ? 3 : 2; //longer range for lngsht bot
        bool targetFound = false;

        for (auto& robot : detectedRobots) {
            if (robot.nameInitial == targetName) {
                targetFound = true;

                if (robot.isHidden) {
                    cout << "[THINK] Shot " << targetName << " at (" << robot.x << "." << robot.y << ") FAILED. Robot is hidden.\n";
                    return false;
                }

                if (isWithinRange(shooterX, shooterY, robot.x, robot.y, shootRange)) {
                    int roll = rand() % 10;
                    bool hit = (roll <= 6); //70% 

                     cout << "[THINK] Shot " << targetName << " at (" << robot.x << "," << robot.y << ") ";

                    if (hit) {
                        robot.lives--;
                        cout << "HIT! Lives left: " << robot.lives << endl;
                        if (robot.lives == 0) {
                            cout << "[DESTROYED] " << targetName << " is destroyed!\n";
                            return true;
                        }
                    } else {
                         cout << "MISSED\n";
                    }
                } else {
                    cout << "THINK " << targetName << " is out of range. No shot fired.\n";
                }
                break;
            }
        }

        if (!targetFound) {
            cout << "[WARNING] Target " << targetName << " not found in detected robots.\n";
        }

        return false;
    }  

    string returnRobotChoices() const {
        return robotChoices;
    }
};

#endif // SHOOTING_ROBOT_H
