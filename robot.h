#define ROBOT_H

#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>


using namespace std;

class Robot {
public:
    string returnRobot() const {
        return "A"; 
    }
};

class MovingBot : public Robot {
private:
    int posX = 1;
    int posY = 1;

public:
    void Move(int frameWidth, int frameHeight, int wordLength) {
        posX = rand() % (frameWidth - wordLength - 2) + 1;  
        posY = rand() % (frameHeight - 2) + 1; 
    }

    int ReturnPosX() const {
        return posX;
    }

    int ReturnPosY() const {
        return posY;
    }
};

class LoopingRobotByPlayers {
     private:
        string line;
        vector<string> RobotNames;
        string name;


     public:
   void getRobotNames() {
    ifstream inputFile("input.txt");

    if (!inputFile) {
        cout << "Input file cannot be opened" << endl;
        return;
    }

    while (getline(inputFile, line)) {
        if (line.find("GenericRobot") != string::npos) {
            size_t StartPos = line.find("GenericRobot");
            istringstream iss(line.substr(StartPos));
            
            string tag, robotName;
            int x, y;

            iss >> tag >> robotName >> x >> y;

            RobotNames.push_back(robotName);
            cout << robotName << endl;  // ✅ Clean print
        }
    };


    inputFile.close();
}
  vector<string> ReturnRobotNames() const {
        return RobotNames;
}


};








