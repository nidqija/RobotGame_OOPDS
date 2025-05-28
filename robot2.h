#ifndef ROBOT2_H
#define ROBOT2_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
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
        int lives;
        bool isHidden = false;
        int hidesLeft = 3;
        int hideTimer = 0; // NEW: for tracking hide duration
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
                detectedRobot.push_back({initial, posinitx, posinity, 3, false, 3, 0});
            }
        }
    }

    vector<string> ReturnVectorRobotInitial() const { return robotInitialLineup; }
    vector<RobotInfo> ReturnRobotDetecteds() const { return detectedRobot; }
};

class MovingBot : public Robot {
protected:
    int robotChoice;

public:
    MovingBot() : robotChoice(0) {}

    void MovetheBot() {
        robotChoice = rand() % 8;
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

    void JumpBot() {
        cout << "[JUMP] " << getSymbol() << " jumps to a new location!" << endl;
        x = rand() % 68 + 1;
        y = rand() % 28 + 1;
    }
};

class ThinkingBot : public MovingBot {
private:
    string decision;
    int hideTimer = 0; // NEW: local timer

public:
    ThinkingBot() : decision("none") {}

    void ThinkAction() {
        int thinkMode = rand() % 4;
        switch (thinkMode) {
            case 0: decision = "move"; break;
            case 1: decision = "fire"; break;
            case 2: decision = "look"; break;
        }
        cout << "[THINK] " << getSymbol() << " decided to " << decision << " at " << getX() << ", " << getY() << endl;
    }

    string getDecision() const { return decision; }

    string HideAction(vector<RobotInfo>& robots, const string& symbol) {
        for (auto& r : robots) {
            if (r.nameInitial == symbol) {
                if (r.isHidden) return "Already hidden.";
                if (r.hidesLeft <= 0) return "No hides left.";
                r.isHidden = true;
                r.hidesLeft--;
                r.hideTimer = 3; // NEW: set duration
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


class JumpBot{
    private: 
      
};

#endif // ROBOT2_H
