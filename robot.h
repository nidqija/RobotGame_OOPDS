#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <cstdlib>

using namespace std;

class Robot {
public:
    string returnRobot() const {
        return "A"; 
    }
};

class MovingBot {
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





#endif
