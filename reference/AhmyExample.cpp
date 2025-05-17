#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm> // For std::remove_if

using namespace std;

class Battlefield;
class Robot;

enum class CellContent { EMPTY, ROBOT, WALL };

struct CellInfo {
    int x, y;
    CellContent content;
    string robotName;
};

class Robot {
protected:
    int posX, posY;
    string name;
    int lives;
    Battlefield* battlefield;
    bool isHidden = false;

public:
    Robot(int x, int y, string n, Battlefield* bf) 
        : posX(x), posY(y), name(n), lives(3), battlefield(bf) {}
    virtual ~Robot() = default;

    virtual void think() = 0;
    virtual vector<CellInfo> look(int x, int y) = 0;
    virtual bool fire(int x, int y) = 0;
    virtual bool move(int dx, int dy) = 0;

    string getName() const { return name; }
    int getX() const { return posX; }
    int getY() const { return posY; }
    int getLives() const { return lives; }
    bool getIsHidden() const { return isHidden; }

    void setPosition(int x, int y) { posX = x; posY = y; }
    void takeDamage() { lives--; }
    void setHidden(bool hidden) { isHidden = hidden; }
};

class Battlefield {
private:
    int width, height;
    vector<vector<CellContent>> grid;
    vector<shared_ptr<Robot>> robots;

public:
    Battlefield(int w, int h) : width(w), height(h) {
        grid.resize(height, vector<CellContent>(width, CellContent::EMPTY));
    }

    void addRobot(shared_ptr<Robot> robot) {
        robots.push_back(robot);
        grid[robot->getY()][robot->getX()] = CellContent::ROBOT;
    }

    void display() const {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x] == CellContent::ROBOT) {
                    bool printed = false;
                    for (const auto& robot : robots) {
                        if (robot->getX() == x && robot->getY() == y && !robot->getIsHidden()) {
                            cout << robot->getName()[0];
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) cout << ".";
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }
    }

    CellInfo getCellInfo(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return {x, y, CellContent::WALL, ""};
        }

        if (grid[y][x] == CellContent::ROBOT) {
            for (const auto& robot : robots) {
                if (robot->getX() == x && robot->getY() == y) {
                    return {x, y, CellContent::ROBOT, robot->getName()};
                }
            }
        }
        return {x, y, grid[y][x], ""};
    }

    bool updateRobotPosition(Robot* robot, int newX, int newY) {
        if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
            return false;
        }

        if (grid[newY][newX] != CellContent::EMPTY) {
            return false;
        }

        grid[robot->getY()][robot->getX()] = CellContent::EMPTY;
        grid[newY][newX] = CellContent::ROBOT;
        robot->setPosition(newX, newY);
        return true;
    }

    bool hasRobot(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) return false;
        return grid[y][x] == CellContent::ROBOT;
    }

    vector<shared_ptr<Robot>>& getRobots() { return robots; }
};

class GenericRobot : public Robot {
private:
    int shells = 10;

public:
    GenericRobot(int x, int y, string n, Battlefield* bf) 
        : Robot(x, y, n, bf) {}

    void think() override {
        cout << name << " is thinking..." << endl;
    }

    vector<CellInfo> look(int x, int y) override {
        vector<CellInfo> info;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int lookX = posX + x + dx;
                int lookY = posY + y + dy;
                info.push_back(battlefield->getCellInfo(lookX, lookY));
            }
        }
        return info;
    }

    bool fire(int x, int y) override {
        if (shells <= 0) {
            cout << name << " is out of shells!" << endl;
            return false;
        }

        if (x == 0 && y == 0) {
            cout << name << " refuses to commit suicide!" << endl;
            return false;
        }

        int targetX = posX + x;
        int targetY = posY + y;
        
        if (!battlefield->hasRobot(targetX, targetY)) {
            cout << name << " fired at (" << targetX << "," << targetY << ") but missed!" << endl;
            shells--;
            return false;
        }

        if (rand() % 100 < 70) {
            cout << name << " scored a hit at (" << targetX << "," << targetY << ")!" << endl;
            for (auto& robot : battlefield->getRobots()) {
                if (robot->getX() == targetX && robot->getY() == targetY) {
                    robot->takeDamage();
                    if (robot->getLives() <= 0) {
                        cout << robot->getName() << " was destroyed!" << endl;
                    }
                    break;
                }
            }
        } else {
            cout << name << " fired at (" << targetX << "," << targetY << ") but missed!" << endl;
        }
        shells--;
        return true;
    }

    bool move(int dx, int dy) override {
        int newX = posX + dx;
        int newY = posY + dy;
        return battlefield->updateRobotPosition(this, newX, newY);
    }
};

class Simulator {
private:
    Battlefield battlefield;
    int maxTurns;
    int currentTurn = 0;
    ofstream logFile;

public:
    Simulator(int width, int height, int turns) 
        : battlefield(width, height), maxTurns(turns) {
        logFile.open("battle_log.txt");
        srand(static_cast<unsigned>(time(nullptr)));
    }

    void addRobot(shared_ptr<Robot> robot) {
        battlefield.addRobot(robot);
    }

    Battlefield& getBattlefield() { return battlefield; }

    void run() {
        while (currentTurn < maxTurns && battlefield.getRobots().size() > 1) {
            currentTurn++;
            cout << "\n=== Turn " << currentTurn << " ===" << endl;
            logFile << "\n=== Turn " << currentTurn << " ===" << endl;

            battlefield.display();

            for (auto& robot : battlefield.getRobots()) {
                if (robot->getLives() <= 0) continue;

                robot->think();
                int action = rand() % 3;
                switch (action) {
                    case 0: {
                        int dx = (rand() % 3) - 1;
                        int dy = (rand() % 3) - 1;
                        if (dx != 0 || dy != 0) {
                            if (robot->move(dx, dy)) {
                                cout << robot->getName() << " moved to (" 
                                     << robot->getX() << "," << robot->getY() << ")" << endl;
                            }
                        }
                        break;
                    }
                    case 1: {
                        int dx = (rand() % 3) - 1;
                        int dy = (rand() % 3) - 1;
                        if (dx != 0 || dy != 0) {
                            robot->fire(dx, dy);
                        }
                        break;
                    }
                    case 2: {
                        auto info = robot->look(0, 0);
                        cout << robot->getName() << " looked around and saw:" << endl;
                        for (const auto& cell : info) {
                            if (cell.content == CellContent::ROBOT) {
                                cout << "  Robot " << cell.robotName << " at (" 
                                     << cell.x << "," << cell.y << ")" << endl;
                            }
                        }
                        break;
                    }
                }
            }

            auto& robots = battlefield.getRobots();
            robots.erase(
                remove_if(robots.begin(), robots.end(),
                    [](const shared_ptr<Robot>& r) { return r->getLives() <= 0; }),
                robots.end());
        }

        cout << "\n=== Simulation Ended ===" << endl;
        if (battlefield.getRobots().size() == 1) {
            cout << "Winner: " << battlefield.getRobots()[0]->getName() << endl;
        } else {
            cout << "Draw! No clear winner." << endl;
        }
        logFile.close();
    }
};

int main() {
    Simulator sim(10, 10, 20);
    Battlefield& bf = sim.getBattlefield();

    sim.addRobot(make_shared<GenericRobot>(1, 1, "Alpha", &bf));
    sim.addRobot(make_shared<GenericRobot>(8, 8, "Bravo", &bf));
    sim.addRobot(make_shared<GenericRobot>(4, 4, "Charlie", &bf));
    sim.addRobot(make_shared<GenericRobot>(7, 2, "Delta", &bf));

    sim.run();

    return 0;
}