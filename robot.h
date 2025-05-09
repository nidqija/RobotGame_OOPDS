#include <iostream>
#include <string>
using namespace std;

class Robot {
    private:
      int RobotPosX , RobotPosY;
      int PosX , PosY;

    public:
      
      Robot(int RobotPosX , int RobotPosY){
        PosX = 0;
        PosY = 0;
      }

      int Move(int RobotPos , char c){
        if (c == 'x'){
          PosX = PosX + RobotPos;
        } else if ( c == 'y'){
          PosY = PosY + RobotPos;
        }
        return abs(PosX) + abs(PosY);
      }

      

};



