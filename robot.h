#define ROBOT_H

#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

// Base Robot class with a function to return the robot's symbol
class Robot {
public:
    // Returns a single-character symbol representing the robot
    virtual string returnRobot() const {
        return "A"; 
    }
};

// Inherits from Robot and adds movement functionality
class MovingBot : public Robot {
private:
    int posX = 1;  // X position in the frame
    int posY = 1;  // Y position in the frame

public:
    // Randomly moves the bot within frame boundaries, considering word length
    void Move(int frameWidth, int frameHeight, int wordLength) {
        posX = rand() % (frameWidth - wordLength - 2) + 1;  // Avoid borders
        posY = rand() % (frameHeight - 2) + 1;              // Avoid borders
    }

    // Get X position
    int ReturnPosX() const {
        return posX;
    }

    // Get Y position
    int ReturnPosY() const {
        return posY;
    }
};

// Handles reading player-defined robot names from a file
class LoopingRobotByPlayers {
private:
    string line;                   // To store each line read from file
    vector<string> RobotNames;     // Stores robot names from input file
    vector<string> RobotIcon;
    string name;                   // Unused, could be removed

public:
    // Reads robot names from "input.txt" where lines start with "GenericRobot"
    void getRobotNames() {
        ifstream inputFile("input.txt");  // Open file

        if (!inputFile) {  // Check if file failed to open
            cout << "Input file cannot be opened" << endl;
            return;
        }

        // Read file line by line
        while (getline(inputFile, line)) {
            // Process only lines that contain "GenericRobot"
            if (line.find("GenericRobot") != string::npos) {
                size_t StartPos = line.find("GenericRobot");
                
                // Create stream from substring starting from "GenericRobot"
                istringstream iss(line.substr(StartPos));
                
                string tag, robotName , robotInitial;
                int x, y;


                // Extract: tag (e.g., "GenericRobot"), name, and two coordinates
                iss >> tag >> robotName >> x >> y;
                robotInitial = robotName.substr(0,1);
  
                // Add robot name to the list
                RobotNames.push_back(robotName);
                RobotIcon.push_back(robotInitial);
                

                // Print robot name (can be removed for silent loading)
                cout << robotName << endl;
            }
        }

        inputFile.close();  // Always close the file
    }

    // Return the list of robot names
    vector<string> ReturnRobotNames() const {
        return RobotNames;
    }


    vector <string> ReturnRobotInit() const{
        return RobotIcon;
    }
};
