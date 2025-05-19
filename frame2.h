#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "robot2.h"
using namespace std;

class Battlefield {
private:
    Robot robot;
    MovingBot movingbot;
    vector<vector<string>> Grid;
    string line;
    int extractedVal1 = 0, extractedVal2 = 0;

public:

 void PrintBattlefield() {
    ifstream inputFile("input.txt");

    if (!inputFile) {
        cout << "Input file cannot be opened" << endl;
        return;
    }

    while (getline(inputFile, line)) {
        if (line.find("50 70") != string::npos) {
            size_t StartPosition = line.find("70");
            size_t EndPosition = line.find("50");
            string val1 = line.substr(StartPosition, 2);  // width
            string val2 = line.substr(EndPosition, 2);    // height

            extractedVal1 = stoi(val1);
            extractedVal2 = stoi(val2);
            break;
        }
    }

    inputFile.close();

    Grid.resize(extractedVal2, vector<string>(extractedVal1, " "));

    // Create battlefield frame
    for (int row = 0; row < extractedVal2; ++row) {
        for (int col = 0; col < extractedVal1; ++col) {
            if (row == 0 || row == extractedVal2 - 1 || col == 0 || col == extractedVal1 - 1) {
                Grid[row][col] = "*";
            }
        }
    }

    // Main loop to animate robot movements
    for (int step = 0; step < 200; ++step) {
        // Clear inner grid
        for (int row = 1; row < extractedVal2 - 1; ++row) {
            for (int col = 1; col < extractedVal1 - 1; ++col) {
                Grid[row][col] = " ";
            }
        }

        // Move the robot
        movingbot.MovetheBot();
        int robotX = movingbot.ReturnSetX();
        int robotY = movingbot.ReturnSetY();
        string robotSymbol = robot.ReturnRobot();

        // Keep robot inside the battlefield
        robotX = max(1, min(robotX, extractedVal1 - 2));
        robotY = max(1, min(robotY, extractedVal2 - 2));
        movingbot.setX(robotX);
        movingbot.setY(robotY);

        // Place robot
        Grid[robotY][robotX] = robotSymbol;

        for (const auto& row : Grid) {
            for (const auto& cell : row) {
                cout << cell;
            }
            cout << endl;
        }

    }
}




};



