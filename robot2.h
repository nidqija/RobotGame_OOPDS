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

public:
    Robot() : x(1), y(1), symbol("R") {}

    Robot(const Robot& robot) {
        this->x = robot.x;
        this->y = robot.y;
        this->symbol = robot.symbol;
    }

    virtual ~Robot() {}

    int getX() const {
         return x; 
        
    }

    int getY() const {
         return y; 
        }

    void setX(int x_) {
         x = x_; 
        }

    void setY(int y_) {
         y = y_; 
        }

    string getSymbol() const {
         return symbol; 
        }

    void DetectRobot() {
        ifstream inputFile("input.txt");
        string line;
        robotInitialLineup.clear();

        while (getline(inputFile, line)) {
            if (line.find("GenericRobot") != string::npos) {
                istringstream iss(line);
                string tag, robotName;
                int x, y;
                iss >> tag >> robotName >> x >> y;
                string initial = robotName.substr(0, 1);
                robotInitialLineup.push_back(initial);
            }
        }
    }

    vector<string> ReturnVectorRobotInitial() const {
        return robotInitialLineup;
    }
};

class MovingBot : public Robot {
private:
    int robotChoice;
    string icon;

public:
    MovingBot() : robotChoice(0) {}

    MovingBot(const MovingBot& other) : Robot(other), robotChoice(other.robotChoice), icon(other.icon) {}

    void MovetheBot() {
        robotChoice = rand() % 8;
        switch (robotChoice) {
            case 0: x -= 1; break; // Left
            case 1: x += 1; break; // Right
            case 2: y -= 1; break; // Up
            case 3: y += 1; break; // Down
            case 4: x += 1; y -= 1; break; // Top-right
            case 5: x -= 1; y -= 1; break; // Top-left
            case 6: x += 1; y += 1; break; // Bottom-right
            case 7: x -= 1; y += 1; break; // Bottom-left
        }
    }

    void setIcon(const string& icon_) {
        icon = icon_;
    }

    string getIcon() const {
        return icon;
    }
};

class ThinkingBot : public Robot {
private:
    string decision;
    int thinkMode;

public:
    ThinkingBot() : decision("none"), thinkMode(0) {}

    ThinkingBot(const ThinkingBot& other)
        : Robot(other), decision(other.decision), thinkMode(other.thinkMode) {}

    void ThinkAction() {
        thinkMode = rand() % 3; // 0 = move, 1 = fire, 2 = look

        switch (thinkMode) {
            case 0:
                decision = "move";
                break;
            case 1:
                decision = "fire";
                break;
            case 2:
                decision = "look";
                break;
        }

        cout << "[THINK] " << getSymbol() << " decided to " << decision << endl;
    }

    string getDecision() const {
        return decision;
    }

    void setDecision(const string& d) {
        decision = d;
    }
};
