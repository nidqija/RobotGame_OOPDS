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

        cout << "[LOOK] " << self->getSymbol() << " looking around (" << coordx << "," << coordy << ")\n";
        
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int viewx = coordx + dx;
                int viewy = coordy + dy;

                if (dx == 0 && dy == 0) {
                    cout << self->getSymbol() << " stands here at (" << coordx << "," << coordy << ")\n";
                    continue;
                }

                for (const auto& r : detectedRobot) {
                    if (r.PosInitX == viewx && r.PosIntY == viewy) {
                        cout << "Enemy robot spotted at (" << viewx << "," << viewy << ")\n";
                        break;
                    }
                }
            }
        }
    }
};

#endif // LOOKING_ROBOT_H
