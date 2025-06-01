// ThirtyShotBot.h
#ifndef THIRTYSHOTBOT_H
#define THIRTYSHOTBOT_H

#include "robot2.h"
#include "shootingRobot.h"

class ThirtyShotBot : public Robot {
private:
    ShootingBot shooter;
public:
    ThirtyShotBot() {
        setSymbol("T");  // Symbol for ThirtyShotBot
        setLives(3);     // Initial lives
    }

    bool Shoot(std::vector<Robot::RobotInfo>& detectedRobots) {
        // Sync shooter position and symbol
        setX(getX());
        setY(getY());
        setSymbol(getSymbol());

        return shooter.startShootingWithShells(
            getX(),
            getY(),
            "Any",  // Target name or identifier (adjust as needed)
            detectedRobots,
            getSymbol().substr(0, 1)  // Use first character of symbol as string
        );
    }
};

#endif
