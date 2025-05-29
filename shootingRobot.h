#ifndef SHOOTING_ROBOT_H
#define SHOOTING_ROBOT_H

#include "robot2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

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

    void startShooting(int targetX, int targetY, const string& targetName, vector<Robot::RobotInfo>& detectedRobots, const string& shooterInitial) {
        int roll = rand() % 10;
        bool hit = (roll <= 6);

        cout << "[THINK] Shot " << targetName << " at (" << targetX << "," << targetY << ") ";

        for (auto& robot : detectedRobots) {
            if (robot.nameInitial == targetName) {
                if (robot.isHidden) {
                    cout << "FAILED. Robot is hidden. Shot ignored.\n";
                    return;
                }

                if (hit) {
                    robot.lives--;
                    cout << "HIT! Lives left: " << robot.lives << endl;
                    if (robot.lives == 0) {
                        cout << "[DESTROYED] " << targetName << " is destroyed!\n";
                    }

                } else {
                    cout << "MISSED\n";
                }
                break;
            }
        }
    }

    string returnRobotChoices() const {
        return robotChoices;
    }
};

#endif // SHOOTING_ROBOT_H
