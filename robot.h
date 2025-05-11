#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Robot{
    private:
     string word = "$";

    public:
       
      string returnRobot() const{
        return word;
      }
      
   
};



class GenericRobot : public Robot{
    private:
      int robotPositionX , robotPositionY;
      string line;
      string RobotName;
      string label;
      

    public:
      void Think(){

      }


      void Fire(){

      }


      int Move(){
          ifstream inputFile("input.txt");
          
          if(!inputFile){
            cout << "Cannot open file" << endl;
            return 1;
          }


          while(getline(inputFile , line)){
            if(line.find("GenericRobot")!= string::npos ){
              istringstream GetPosFromLine(line);
              int PosX , PosY;
              GetPosFromLine >> label >> RobotName >> PosX >> PosY;

              robotPositionX = PosX;
              robotPositionY = PosY;

            cout << "Name:" << RobotName << " " << endl;
            cout << "X:" << robotPositionX << " " << endl;
            cout << "Y:" << robotPositionY << " " << endl;



              

            
            }
          }  
      }


      int ReturnPosX(){
        return robotPositionX;
      }

      int ReturnPosY(){
        return robotPositionY;
      }
       
};



