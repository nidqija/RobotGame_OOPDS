#ifndef LOOKING_ROBOT_H
#define LOOKING_ROBOT_H

#include "robot2.h"
#include <iostream>
#include <vector>

class LookingBot {
public:
    void LookAction(Robot* self, const vector<Robot::RobotInfo>& detectedRobot) {
        int coordx = self->getX();
        int coordy = self->getY();

        cout << "[LOOK] " << self->getSymbol() << " looking around (" << coordx << "," << coordy << ")." << endl;
        
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int viewx = coordx + dx;
                int viewy = coordy + dy;

                if (dx == 0 && dy == 0) {
                    cout << self->getSymbol() << " stands here at (" << coordx << "," << coordy << ")." << endl;
                    continue;
                }

                for (const auto& r : detectedRobot) {
                    if (r.PosInitX == viewx && r.PosIntY == viewy) {
                        cout << "Enemy robot spotted at (" << viewx << "," << viewy << ")." << endl;
                        break;
                    }
                }
            }
        }
    }
};

class ScoutBot : public ThinkingBot {
private:
    int scanNum = 3;
    string decision;

public:

    ScoutBot() : scanNum(3) {}

    void ScoutAction( const vector<Robot::RobotInfo>& detectedRobot) {

        if (scanNum <= 0) {
            cout << "[SCOUT] No scans remaining." << endl;
            return;
        }

        scanNum--;

        cout << "[SCOUT] Full battlefield scan initiated by " << getSymbol() << "." << endl;

        for (const auto& r : detectedRobot) {
            cout << "Enemy: " << r.nameInitial << " at (" << r.PosInitX << ", " << r.PosIntY << ")." << endl;
        }

        cout << "Remaining number of scans: " << scanNum << "." << endl;
    }

};


#endif // LOOKING_ROBOT_H
