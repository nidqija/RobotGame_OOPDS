#ifndef SHOOTING_ROBOT_H
#define SHOOTING_ROBOT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

//shootingBot -> fire bullets

class ShootingBot {
    private:
      int totalBullets;
      vector<string> robotTargets;


    public:
      ShootingBot(int initialBullets = 5) {
        totalBullets = initialBullets;
      }

      //read robot names from inputtxt file
      void loadTargetsFromFile(const string& filename){
        ifstream inputFile(filename);
        string line;

        if(!inputFile){
          cout << "X could not open " << filename << endl;
          return;
        }

        while (getline(inputFile, line)) {
          if(line.find("GenericRobot") != string::npos) {
            istringstream iss(line);
            string tag, name;
            int x, y;

            iss >> tag >> name >> x >> y;
            robotTargets.push_back(name); //store the name only
          }
        }

        inputFile.close();
      }


      // simulate shooting each target

      void startShooting() {
        for (const string& target : robotTargets) {
          if (totalBullets > 0) {
            cout << "Boom Shooting " << target << "!" << endl;
            totalBullets--;
          } else {
            cout << "Out of Bullets! cannot shoot " << target << endl;
          }
        }

        cout << "Shooting complete. Bullets left: "<< totalBullets << endl;

      }

      //fn 2 reload bullets
      void reload(int bullets) {
        totalBullets += bullets;
        cout << "Reloaded. Total bullets: " << totalBullets << endl;
      }

      // how many bullets left
      int checkBullets() const  {
        return totalBullets;
      }
};

#endif