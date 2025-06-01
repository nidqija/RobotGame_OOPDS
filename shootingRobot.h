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
     int shells = 30;  // For ThirtyShotBot

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



    void ReturnShells(){
        shells = 30;
    }

       bool semiAutoShoot(int shooterX, int shooterY, const string& targetName,
                       vector<Robot::RobotInfo>& detectedRobots, const string& shooterInitial) 
    {
        for (int shot = 0; shot < 3; ++shot) {
            if (shells <= 0) {
                cout << "[SEMI-AUTO] No shells left to fire.\n";
                return false;
            }
            shells--;

            int roll = rand() % 10;
            bool hit = (roll <= 6); // 70% chance

            cout << "[SEMI-AUTO] Shot " << (shot + 1) << " at " << targetName << ": ";

            for (auto& robot : detectedRobots) {
                if (robot.nameInitial == targetName) {
                    if (robot.isHidden) {
                        cout << "FAILED. Robot is hidden.\n";
                        return false;
                    }

                    if (!isWithinRange(shooterX, shooterY, robot.x, robot.y, 2)) { // assuming range 2
                        cout << "Out of range.\n";
                        return false;
                    }

                    if (hit) {
                        robot.lives--;
                        cout << "HIT! Lives left: " << robot.lives << endl;
                        if (robot.lives <= 0) {
                            cout << "[DESTROYED] " << targetName << " is destroyed!\n";
                            return true; // target destroyed, stop firing
                        }
                    } else {
                        cout << "MISSED\n";
                    }
                    break;
                }
            }
        }
        return false; // target not destroyed after 3 shots
    }


        bool startShootingWithShells(int shooterX, int shooterY, const string& targetName,
                                vector<Robot::RobotInfo>& detectedRobots, const string& shooterInitial) 
    {
        if (shells <= 0) {
            cout << "[THIRTYSHOT] No shells left to fire.\n";
            return false;
        }

        shells--;

        return startShooting(shooterX, shooterY, targetName, detectedRobots, shooterInitial);
    }
};

    


#endif // Reset shells to 30 for ThirtyShotBot
 