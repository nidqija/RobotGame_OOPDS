
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
    string icon;

public:
    struct RobotInfo {
        string nameInitial;
        int PosInitX;
        int PosIntY;
        int lives;
    };

    vector<RobotInfo> detectedRobot;

    Robot() : x(1), y(1), symbol("R") {}

    Robot(const Robot& robot) {
        this->x = robot.x;
        this->y = robot.y;
        this->symbol = robot.symbol;
    }

    virtual ~Robot() {}

    void setIcon(const string& icon_) { icon = icon_; }
    string getIcon() const { return icon; }

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int x_) { x = x_; }
    void setY(int y_) { y = y_; }

    string getSymbol() const { return symbol; }
    void setSymbol(const string& s) { symbol = s; }

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
                detectedRobot.push_back({initial, posinitx, posinity});
            }
        }

        inputFile.close();
    }

    vector<string> ReturnVectorRobotInitial() const {
        return robotInitialLineup;
    }

    vector<RobotInfo> ReturnRobotDetecteds() const {
        return detectedRobot;
    }
};

class MovingBot : public Robot {
private:
    int robotChoice;

public:
    MovingBot() : robotChoice(0) {}
    MovingBot(const MovingBot& other) : Robot(other), robotChoice(other.robotChoice) {}

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

    void HideBot(){
        
    }


    void JumpBot(){

    }
};

class ThinkingBot : public MovingBot {
private:
    string decision;
    int thinkMode;

public:
    ThinkingBot() : decision("none"), thinkMode(0) {}
    ThinkingBot(const ThinkingBot& other)
        : MovingBot(other), decision(other.decision), thinkMode(other.thinkMode) {}

    void ThinkAction() {
        thinkMode = rand() % 3; // 0 = move, 1 = fire, 2 = look

        switch (thinkMode) {
            case 0: decision = "move"; break;
            case 1: decision = "fire"; break;
            case 2: decision = "look"; break;
        }

        cout << "[THINK] " << getSymbol() << " decided to " << decision
             << " at " << getX() << ", " << getY() << endl;
    }

    string getDecision() const { return decision; }
    void setDecision(const string& d) { decision = d; }
};

/*class LookingBot : virtual public Robot {
    public:
    void LookAction(){
        DetectRobot();

        int coordx = getX();
        int coordy = getY();

        cout << "[LOOKING] Looking around (" << coordx << "," << coordy << ")" << endl;

        for (int dy = -1; dy <= 1; ++dy){
            for (int dx = -1; dx <= 1; ++dx){
                int viewx = coordx + dx;
                int viewy = coordy + dy;

                if (dx == 0 && dy == 0){
                    cout << getSymbol() << "stands here at coordinates (" << coordx << "," << coordy << ")." << endl;
                    continue;
                }

                bool present = false;
                for (const auto& r : ReturnRobotDetecteds()){
                    if (r.PosInitX == viewx && r.PosIntY == viewy){
                        cout << "Enemy Robot spotted at (" << viewx << "," << viewy << ")." << endl;
                        present = true;
                        break;
                    }
                }
            }
        }
    }

}; */




class RobotUpgrades : public MovingBot {
     private:
        int robotSelection2;
        string robotChoices;
        Robot robot;


     public:
       RobotUpgrades() : robotChoices("none"), robotSelection2(0) {}
        RobotUpgrades(const RobotUpgrades& other)
        : MovingBot(other), robotChoices(other.robotChoices), robotSelection2(other.robotSelection2) {}

        void RobotUpgradeRandomizer(const string& robotInitial) {
            robotSelection2 = rand() % 7;
            switch ( robotSelection2) {
                case 0:
                   robotChoices = "HideBot" ;
                   HideBot();
                    break;
                case 1:
                   robotChoices = "JumpBot"; 
                   JumpBot();
                   break;
                case 2 :
                   robotChoices = "LongShotBot"; break;

                case 3:
                   robotChoices = "SemiAutoBot"; break;

                case 4:
                   robotChoices = "ThirtyShotBot"; break;

                case 5:
                   robotChoices = "ScoutBot"; break;
                
                case 6:
                   robotChoices = "TrackBot";break;
            }

            cout << "Robot " << getSymbol() << robotChoices << " !"<< endl;
            cout << "Robot " << getSymbol() << "becomes " << robotChoices << " !" << endl;
            
         
            
        };


        string getRobotChoices() const {
            return robotChoices;
        };



        void setRobotChoices(const string& rbc) {
          robotChoices = rbc;
        };



};





#endif
