#ifndef LOOKING_ROBOT_H
#define LOOKING_ROBOT_H

#include "robot2.h"
#include <iostream>
#include <vector>

class LookingBot {
public:
    static void LookAction(Robot* self, const vector<Robot::RobotInfo>& detectedRobot) {
        int coordx = self->getX();
        int coordy = self->getY();

        cout << "[LOOK] " << self->getSymbol() << " looking around (" << coordx << "," << coordy << ")." << endl;

        vector<Robot::RobotInfo> visibleRobots;
        
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
                        visibleRobots.push_back(r);
                        break;
                    }
                }
            }
        }
    }

    return visibleRobots;
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

class TrackBot : public ThinkingBot {
    private:

        int trackersRemaining = 3;
        vector<pair<string, pair<int, int>>> trackedBots;

    public:

        string TrackAction(Robot* self, const vector<Robot::RobotInfo>& detectedRobot) {
            if (trackersRemaining <= 0){
                return "[TRACK] No trackers remaining.";
            }
                
            // Use LookAction from LookingBot to detect nearby robots
            vector<Robot::RobotInfo> visible = LookingBot::LookAction(self, detectedRobot);

            for (const auto& r : visible) {
                if (r.nameInitial == self->getSymbol() || r.isHidden)
                    continue;

                trackedBots.push_back({r.nameInitial, {r.PosInitX, r.PosIntY}});
                trackersRemaining--;

                return "[TRACK] Tracker planted on " + r.nameInitial +
                    " at (" + to_string(r.PosInitX) + ", " + to_string(r.PosIntY) + "). " +
                    "Trackers left: " + to_string(trackersRemaining);
            }

            return "[TRACK] No visible enemy to track.";
        }

        void DisplayTrackedBots() const {
            for (const auto& [symbol, pos] : trackedBots) {
                cout << "[TRACKING] " << symbol << " at (" << pos.first << ", " << pos.second << ")" << endl;
            }
        }
};


#endif // LOOKING_ROBOT_H
