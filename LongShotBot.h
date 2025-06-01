// LongShotBot.h
#ifndef LONGSHOTBOT_H
#define LONGSHOTBOT_H

#include "robot2.h"
#include "shootingRobot.h"

class LongShotBot : public Robot {
private:
    ShootingBot shooter;
public:
    LongShotBot() {
        setSymbol("L");  // Set bot symbol
        setLives(3);     // Set bot lives
    }

    bool Shoot(std::vector<Robot::RobotInfo>& detectedRobots) {
        // Sync shooter's position and symbol
        setX(getX());
        setY(getY());
        setSymbol(getSymbol());

        return shooter.startShooting(
            getX(),
            getY(),
            "Any",  // Adjust as needed for targeting
            detectedRobots,
            getSymbol().substr(0, 1),  // Fix: extract first character as string
            true  // isLongShot
        );
    }
};

#endif
