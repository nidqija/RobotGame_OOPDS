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
    vector<MovingBot> bots;
    vector<vector<string>> Grid;
    int extractedVal1 = 70, extractedVal2 = 50; // Use defaults or extract from file

public:

void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000)) {
        // busy wait
    }
}
    Battlefield() {
        srand(time(0)); // Seed RNG
        for (int i = 0; i < 5; ++i) {
            MovingBot bot;
            bot.setX(1 + i); 
            bot.setY(1 + i);
            bots.push_back(bot);
        }
    }

    void PrintBattlefield() {
        Grid.resize(extractedVal2, vector<string>(extractedVal1, " "));

        for (int step = 0; step < 100; ++step) {
            // Clear grid
            for (int y = 0; y < extractedVal2; ++y)
                for (int x = 0; x < extractedVal1; ++x)
                    Grid[y][x] = ((y == 0 || y == extractedVal2 - 1 || x == 0 || x == extractedVal1 - 1) ? "*" : " ");

            // Move and place each bot
            for (auto& bot : bots) {
                bot.MovetheBot();
                int x = max(1, min(bot.getX(), extractedVal1 - 2));
                int y = max(1, min(bot.getY(), extractedVal2 - 2));
                bot.setX(x); bot.setY(y);
                Grid[y][x] = "R";
            }

            // Draw grid
            delay(2000); // Delay for 1 second (1000 milliseconds)
            system("cls"); // Use "CLS" on Windows
            for (const auto& row : Grid) {
                for (const auto& cell : row)
                    cout << cell;
                cout << endl;
            }

        }
    }
};
