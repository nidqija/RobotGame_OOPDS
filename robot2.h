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
        int x;
        int y;
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

    vector<string> ReturnVectorRobotInitial() const {
         return robotInitialLineup; 
        }
    vector<RobotInfo> ReturnRobotDetecteds() const { 
        return detectedRobot; 
    }
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
                if (r.isHidden) 
                return "Already hidden.";
                if (r.hidesLeft <= 0) 
                return "No hides left.";
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


class JumpBot : public ThinkingBot{

    private:
       int updatePos;


    public:
        string JumpAction(vector<RobotInfo>& robots, const string& symbol){
         for (auto& r : robots){
            if ( r.nameInitial == symbol){
                updatePos = rand () % 10;

                switch (updatePos){
                    case 0:
                      r.x += 2;
                      r.y += 4;
                      break;
                    case 1:
                      r.x += 4;
                      r.y += 12;
                      break;
                    case 2:
                      r.x += 6;
                      r.y += 3;
                      break;
                    case 3:
                      r.x += 8;
                      r.y += 20;
                      break;
                    case 4:
                      r.x += 10;
                      r.y += 19;
                      break;
                }

                setX(r.x);
                setY(r.y);
                return "Jumped to (" + to_string(r.x) + ", " + to_string(r.y) + ")";

         }
    }; 
            return "Robot not found.";

};
};

class AvoiderBot : public MovingBot {
public:
    AvoiderBot() {
        setSymbol("A");  // Symbol for AvoiderBot
    }

    string AvoidAction(vector<RobotInfo>& robots, const string& symbol) {
        for (const auto& r : robots) {
            if (r.nameInitial != symbol) {
                int dx = r.x - getX();
                int dy = r.y - getY();

                if (abs(dx) <= 2 && abs(dy) <= 2) {
                    if (abs(dx) > abs(dy)) {
                        if (dx > 0) setX(getX() - 1);  // move left
                        else setX(getX() + 1);         // move right
                    } else {
                        if (dy > 0) setY(getY() - 1);  // move up
                        else setY(getY() + 1);         // move down
                    }
                    return "Avoided nearby robot.";
                }
            }
        }

        MovetheBot();  // fallback
        return "No bot nearaby, moving randomly.";
    }
};


class RegenBot : public ThinkingBot {
public:
    string generateHealthRobot(vector<Robot::RobotInfo>& robots, const string& symbol) {
        for (auto& robot : robots) {
            if (robot.nameInitial == symbol) {
                robot.lives += 1;  // Increase life
                stringstream ss;
                ss << "RegenBot " << symbol << " regenerated 1 life. Total lives: " << robot.lives;
                return ss.str();
            }
        }
        return "No matching robot found to regenerate.";
    }

    string getType() const  {
        return "RegenBot";
    }
};

class SpeedyBot : public MovingBot {
public:
    SpeedyBot() {
        setSymbol("Z"); // Use "Z" or any unused symbol for visual identification
    }

    string SpeedAction() {
        // Move 3 times in one frame
        MovetheBot();
        MovetheBot();
        MovetheBot();
        return "Speedybot is becuming faster";
    }
};

#endif // ROBOT2_H
