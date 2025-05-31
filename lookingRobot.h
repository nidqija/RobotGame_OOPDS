#ifndef LOOKING_ROBOT_H
#define LOOKING_ROBOT_H

#include "robot2.h"
#include <iostream>
#include <vector>
#include <string>

class LookingBot {

    public:

        static vector<Robot::RobotInfo> LookAround(Robot* self, const vector<Robot::RobotInfo>& detectedRobots) {
            
            vector<Robot::RobotInfo> presentBots;
            int x = self->getX();
            int y = self->getY();

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int checkX = x + dx;
                    int checkY = y + dy;

                    if (dx == 0 && dy == 0) continue; // skip own tile

                    for (const auto& bot : detectedRobots) {
                        if (bot.PosInitX == checkX && bot.PosIntY == checkY) {
                            presentBots.push_back(bot);
                            break;
                        }
                    }
                }
            }

            return presentBots;
            
        }

        static void LookAction( Robot* self, const vector<Robot::RobotInfo>& detectedRobots) {

            int x = self->getX();
            int y = self->getY();

            cout << "[LOOK] " << self->getSymbol() << " looking around (" << x << "," << y << ")." << endl;
            cout << self->getSymbol() << " stands here at (" << x << "," << y << ")." << endl;

            auto presentBots = LookAround(self, detectedRobots);

            for (const auto& bot : presentBots) {
                cout << "Enemy robot spotted at (" << bot.PosInitX << "," << bot.PosIntY << ")." << endl;
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

            if (r.nameInitial == getSymbol() || r.isHidden)
                continue;

            cout << "Enemy: " << r.nameInitial << " at (" << r.PosInitX << ", " << r.PosIntY << ")." << endl;
        }

        cout << "Remaining number of scans: " << scanNum << "." << endl;
    }

};

class TrackBot : public ThinkingBot {
    private:

        int trackersRemaining = 3;
        vector<string> trackedBotSymbols;

    public:

        void TrackAction(Robot* self, const vector<Robot::RobotInfo>& detectedRobot) {
            if (trackersRemaining <= 0){
                cout << "[TRACK] No trackers remaining." << endl;
                return;
            }
                
            vector<Robot::RobotInfo> presentBots = LookingBot::LookAround(self, detectedRobot);

            for (const auto& r : presentBots) {
                if (r.nameInitial == self->getSymbol() || r.isHidden)
                    continue;

                if (find(trackedBotSymbols.begin(), trackedBotSymbols.end(), r.nameInitial) == trackedBotSymbols.end()) {
                    trackedBotSymbols.push_back(r.nameInitial);
                    trackersRemaining--;

                    cout << "[TRACK] Tracker placed on " << r.nameInitial << " at (" << r.PosInitX << ", " << r.PosIntY << "). " << "Trackers left: " << trackersRemaining << endl;

                    return;
                }  


            }   

            cout << "[TRACK] No presentBots enemy to track." << endl;

        }

        void DisplayTrackedBots(const vector<Robot::RobotInfo>& detectedRobots) const {

            cout << "[TRACKLOG] " << getSymbol() << "'s tracklog:" << endl;
            
            if (trackedBotSymbols.empty()) {
                cout << "  No bots currently being tracked." << endl;
                return;
            }

            for (const auto& symbol : trackedBotSymbols) {
                bool found = false;
                for (const auto& r : detectedRobots) {
                    if (r.nameInitial == symbol) {
                        cout << "  [TRACKING] " << symbol << " at (" << r.PosInitX << ", " << r.PosIntY << ")" << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "  [TRACKING] " << symbol << " is not visible right now." << endl;
                }
            }
        }


};


#endif // LOOKING_ROBOT_H
