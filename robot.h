#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <cstdlib>

class Robot {
public:
    std::string returnRobot() const {
        return "A"; // or any string like "BOT"
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

    int ReturnPosX() const { return posX; }
    int ReturnPosY() const { return posY; }
};

#endif
