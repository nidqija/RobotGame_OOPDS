#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "robot.h"

using namespace std;



void delay(int milliseconds) {
    for (int i = 0; i < milliseconds * 2000; ++i) {
    }
}

void slowPrint(const string& text, int delayMs = 2000) {
    for (char ch : text) {
        cout << ch << flush;
        delay(delayMs);
    }
}

class Frame {
private:
    string line;
    int extractedVal1 = 0, extractedVal2 = 0;
    

public:
    friend class LoopFrame;

    void FindFrame() {
        ifstream inputFile("input.txt");

        if (!inputFile) {
            cout << "Input file cannot be opened" << endl;
            return;
        }

        while (getline(inputFile, line)) {
            if (line.find("50 70") != string::npos) {  // Change this to your required frame size
                size_t StartPosition = line.find("70");
                size_t EndPosition = line.find("50");
                string val1 = line.substr(StartPosition, 2);
                string val2 = line.substr(EndPosition, 2);

                extractedVal1 = stoi(val1);
                extractedVal2 = stoi(val2);
                break;
            }
        }

        inputFile.close();
    }

    int xval() const {
        return extractedVal1;
    }

    int yval() const {
        return extractedVal2;
    }
};



class DrawFrame : public Frame {
public:
    // Draw frame with multiple robot icons at given positions
    void drawTheFrame(const vector<string>& robotIcons, const vector<int>& posX, const vector<int>& posY) {
        FindFrame();
        int xValue = xval();
        int yValue = yval();

        for (int row = 0; row < yValue; ++row) {
            for (int col = 0; col < xValue; ++col) {
                if (row == 0 || row == yValue - 1 || col == 0 || col == xValue - 1) {
                    cout << "*";  // Frame border
                } else {
                    bool printed = false;
                    for (size_t i = 0; i < robotIcons.size(); ++i) {
                        if (posX[i] == col && posY[i] == row) {
                            cout << robotIcons[i];
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) {
                        cout << " ";  // Empty inside frame
                    }
                }
            }
            cout << "\n";
        }
    }
};


class LoopFrame : public DrawFrame {
private:
    string line;
    int RobotAmount;
    friend class LoopingRobotByPlayers;
    int numberofSteps;
    int NumFrame;

public:
   void LoopingFrameByRobot() {
    ifstream InputFile("input.txt");
    while (getline(InputFile, line)) {
        if (line.find("robots:") != string::npos) {
            size_t StartPos = line.find(":");
            string Robotsnum = line.substr(StartPos + 1);
            RobotAmount = stoi(Robotsnum);
            cout << "Amount of Robots: " << RobotAmount << endl;
            break;
        }
    }
    InputFile.close();

    NumberOfFrames();

    LoopingRobotByPlayers nameRobot;
    nameRobot.getRobotNames();
    vector<string> robotNames = nameRobot.ReturnRobotNames();
    vector<string> robotIcons = nameRobot.ReturnRobotInit();

    MovingBot movingBot;
    int frameWidth = xval();
    int frameHeight = yval();

    vector<int> posXList(robotNames.size());
    vector<int> posYList(robotNames.size());

    for (int step = 0; step < NumFrame; ++step) {
        // Move each robot to a new random position
        for (size_t i = 0; i < robotNames.size(); ++i) {
            movingBot.Move(frameWidth, frameHeight, 1);  // wordLength = 1 for icon
            posXList[i] = movingBot.ReturnPosX();
            posYList[i] = movingBot.ReturnPosY();
        }

        // Draw frame with all robots at their positions
        drawTheFrame(robotIcons, posXList, posYList);

        // Delay for animation

   
    }
}



    void NumberOfFrames(){
         ifstream InputFile("input.txt");
        while (getline(InputFile, line)) {
            if (line.find("steps:") != string::npos) {
                size_t StartPos = line.find(":");
                string FrameNum = line.substr(StartPos + 1);
                NumFrame = stoi(FrameNum);
                cout << "Number of Steps: " << NumFrame << endl;
                break;
            }
        }
        InputFile.close();

       
};  

  int ReturnNumberofFrames() const{
    return NumFrame;
  }
};



