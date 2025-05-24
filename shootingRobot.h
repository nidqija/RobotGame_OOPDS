#ifndef SHOOTING_ROBOT_H
#define SHOOTING_ROBOT_H

#include "robot2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct TargetInfo {
    string name;
    int x;
    int y;
};

// ShootingBot simply reads targets and shoots
class ShootingBot {
private:
    vector<TargetInfo> robotTargets;

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

    void startShooting(int targetX, int targetY, const string& targetName, vector<Robot::RobotInfo>& detectedRobots) {
    int roll = rand() % 10; // 0 to 9
    bool hit = (roll <= 6); // 70% chance to hit

    cout << "[THINK] Shot " << targetName << " at (" << targetX << "," << targetY << ") ";
    if (hit) {
        // Find the robot in detectedRobots and decrement lives
        for (auto& robot : detectedRobots) {
            if (robot.nameInitial == targetName) {
                robot.lives--; // Decrement lives
                cout << "got shot! HIT! Lives left: " << robot.lives << endl;
                if (robot.lives <= 0) {
                    cout << targetName << " is destroyed!" << endl;
                }
                break;
            }
        }
    } else {
        cout << "MISSED" << endl;
    }
 }

};

#endif // SHOOTING_ROBOT_H
