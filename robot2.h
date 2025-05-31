#ifndef ROBOT2_H
#define ROBOT2_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "shootingRobot.h"

using namespace std;

class Robot {
protected:
    int x, y;
    string symbol;
    vector<string> robotInitialLineup;
    bool isHidden = false;

public:
    struct RobotInfo {
        string nameInitial;
        int PosInitX;
        int PosIntY;
        int lives = 3;
        bool isHidden = false;
        int hidesLeft = 3;
        int hideTimer = 0;
        int x, y;
    };

    Robot() : x(1), y(1), symbol("R") {}
    virtual ~Robot() {}

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int x_) { x = x_; }
    void setY(int y_) { y = y_; }

    string getSymbol() const { return symbol; }
    void setSymbol(const string& s) { symbol = s; }

    void setHidden(bool hidden) { isHidden = hidden; }
    bool getHidden() const { return isHidden; }

    vector<RobotInfo> detectedRobot;

    void DetectRobot() {
        ifstream inputFile("input.txt");
        string line;
        robotInitialLineup.clear();
        detectedRobot.clear();

        while (getline(inputFile, line)) {
            if (line.find("GenericRobot") != string::npos) {
                istringstream iss(line);
                string tag, robotName;
                int posinitx, posinity;
                iss >> tag >> robotName >> posinitx >> posinity;
                string initial = robotName.substr(0, 1);
                robotInitialLineup.push_back(initial);
                detectedRobot.push_back({initial, posinitx, posinity, 3, false, 3, 0, posinitx, posinity});
            }
        }
    }

    vector<string> ReturnVectorRobotInitial() const {
        return robotInitialLineup;
    }

    vector<RobotInfo> ReturnRobotDetecteds() const {
        return detectedRobot;
    }

    const RobotInfo* GetMyInfo() const {
        for (const auto& rinfo : detectedRobot) {
            if (rinfo.nameInitial == symbol) {
                return &rinfo;
            }
        }
        return nullptr;
    }

    int ReturnLives() const {
        const RobotInfo* robotinfo = GetMyInfo();
        return (robotinfo != nullptr) ? robotinfo->lives : 0;
    }
};

// -------------------- MovingBot --------------------
class MovingBot : public Robot {
public:
    void MovetheBot() {
        int robotChoice = rand() % 8;
        switch (robotChoice) {
            case 0: x -= 1; break;
            case 1: x += 1; break;
            case 2: y -= 1; break;
            case 3: y += 1; break;
            case 4: x += 1; y -= 1; break;
            case 5: x -= 1; y -= 1; break;
            case 6: x += 1; y += 1; break;
            case 7: x -= 1; y += 1; break;
        }
    }
};

// -------------------- ThinkingBot --------------------
class ThinkingBot : public MovingBot {
private:
    string decision;
    int hideTimer = 0;

public:
    ThinkingBot() : decision("none") {}

    void ThinkAction() {
        int thinkMode = rand() % 3;
        switch (thinkMode) {
            case 0: decision = "move"; break;
            case 1: decision = "fire"; break;
            case 2: decision = "look"; break;
        }
        cout << "[THINK] " << getSymbol() << " decided to " << decision
             << " at " << getX() << ", " << getY() << endl;
    }

    string getDecision() const { return decision; }

    string HideAction(vector<RobotInfo>& robots, const string& symbol) {
        for (auto& r : robots) {
            if (r.nameInitial == symbol) {
                if (r.isHidden) return "Already hidden.";
                if (r.hidesLeft <= 0) return "No hides left.";

                r.isHidden = true;
                r.hidesLeft--;
                r.hideTimer = 3;

                this->setHidden(true);
                hideTimer = 3;
                return "Now hiding for 3 turns.";
            }
        }
        return "Robot not found.";
    }

    void UpdateHideStatus(vector<RobotInfo>& robots) {
        if (hideTimer > 0) {
            hideTimer--;
            if (hideTimer == 0) {
                setHidden(false);
                for (auto& r : robots) {
                    if (r.nameInitial == getSymbol()) {
                        r.isHidden = false;
                        r.hideTimer = 0;
                        break;
                    }
                }
                cout << "[REVEAL] " << getSymbol() << " is now visible again!" << endl;
            }
        }
    }
};

// -------------------- JumpBot --------------------
class JumpBot : public ThinkingBot {
public:
    string JumpAction(vector<RobotInfo>& robots, const string& symbol) {
        for (auto& r : robots) {
            if (r.nameInitial == symbol) {
                int updatePos = rand() % 5;
                switch (updatePos) {
                    case 0: r.x += 2; r.y += 4; break;
                    case 1: r.x += 4; r.y += 12; break;
                    case 2: r.x += 6; r.y += 3; break;
                    case 3: r.x += 8; r.y += 20; break;
                    case 4: r.x += 10; r.y += 19; break;
                }

                setX(r.x);
                setY(r.y);
                return "Jumped to (" + to_string(r.x) + ", " + to_string(r.y) + ")";
            }
        }
        return "Robot not found.";
    }
};

// -------------------- AvoiderBot --------------------
class AvoiderBot : public MovingBot {
public:
    string AvoidAction(vector<RobotInfo>& robots, const string& symbol) {
        for (const auto& r : robots) {
            if (r.nameInitial != symbol) {
                int dx = r.x - getX();
                int dy = r.y - getY();

                if (abs(dx) <= 2 && abs(dy) <= 2) {
                    if (abs(dx) > abs(dy)) {
                        setX(getX() + (dx > 0 ? -1 : 1));
                    } else {
                        setY(getY() + (dy > 0 ? -1 : 1));
                    }
                    return "Avoided nearby robot.";
                }
            }
        }

        MovetheBot();  // fallback
        return "No bot nearby, moving randomly.";
    }
};

// -------------------- RegenBot --------------------
class RegenBot : public ThinkingBot {
public:
    string generateHealthRobot(vector<RobotInfo>& robots, const string& symbol) {
        for (auto& robot : robots) {
            if (robot.nameInitial == symbol) {
                robot.lives += 1;
                stringstream ss;
                ss << "RegenBot " << symbol << " regenerated 1 life. Total lives: " << robot.lives;
                return ss.str();
            }
        }
        return "No matching robot found to regenerate.";
    }

    string getType() const {
        return "RegenBot";
    }
};

// -------------------- SpeedyBot --------------------
class SpeedyBot : public MovingBot {
public:
    string SpeedAction() {
        MovetheBot();
        MovetheBot();
        MovetheBot();
        return "SpeedyBot moved quickly!";
    }
};

// ---------------------LongShotBot-------------------
class LongShotBot : public ShootingBot {
public:
    LongShotBot() {
        ammo = 10;
    }

    bool startShooting(int shooterX, int shooterY, const string& targetName, vector<Robot::RobotInfo>& detectedRobots, const string& shooterInitial) {
        return ShootingBot::startShooting(shooterX, shooterY, targetName, detectedRobots, shooterInitial, true);

    }
};

//----------------------ThirtyShotBot-------------------
class ThirtyShotBot : public ShootingBot {
public: 
    ThirtyShotBot() {
        ammo = 30; 
    }

    bool startShooting(int shooterX, int shooterY, const string& targetName, vector<Robot::RobotInfo>& detectedRobots, const string& shooterInitial) {
        return ShootingBot::startShooting(shooterX, shooterY, targetName, detectedRobots, shooterInitial, false);

    }
};

#endif // ROBOT2_H