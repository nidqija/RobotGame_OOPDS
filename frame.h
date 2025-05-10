#include <iostream>
#include <fstream>
#include <string>
#include "robot.h"

using namespace std;


class Frame {
    private:
      string line;
      int extractedVal1 = 0 , extractedVal2 = 0;
      
      

    public:
      friend class LoopFrame;

       void FindFrame(){
          ifstream inputFile("input.txt");
    
    
          if(!inputFile){
              cout << "Input file cannot be opened" << endl;
          } 
        
          while (getline(inputFile , line)){
            if(line.find("40 50") != string::npos){
                cout << "Frame : 40 50" << endl;
                size_t StartPosition = line.find("40");
                size_t EndPosition = line.find("50");
                string val1 = line.substr(StartPosition , 2);
                string val2 = line.substr(EndPosition , 2);

                extractedVal1 = stoi(val1);
                extractedVal2 = stoi(val2);

                cout << extractedVal1 << endl;
                cout << extractedVal2<< endl;
                break;
            }  
              
          }

          inputFile.close();
        
        }

          int xval() const{
            return extractedVal1;
           }
    
           int yval() const{
            return extractedVal2;
           }

        
};





class DrawFrame : public Frame {
    public:
   void drawTheFrame(const Robot& robot) {
    FindFrame(); 
    int xValue = xval();
    int yValue = yval();
    string word = robot.returnRobot() ;
    int wordLength = word.length();
    int midRow = yValue / 2;
    int midColStart = (xValue - wordLength) / 2;

    for (int row = 0; row < yValue; ++row) {
        for (int col = 0; col < xValue; ++col) {
            if (row == 0 || row == yValue - 1) {
                cout << "*";
            }
            else if (col == 0 || col == xValue - 1) {
                cout << "*";
            }
            else if (row == midRow && col >= midColStart && col < midColStart + wordLength) {
                cout << word[col - midColStart];
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}


        };


class LoopFrame :public DrawFrame{

     private:
       string line;
       int RobotAmount;

     public:
       
       void LoopingFrameByRobot(){
          ifstream InputFile("input.txt");
          while(getline(InputFile , line)){
               if(line.find("robots:") != string::npos){
                   size_t StartPos = line.find(":");
                   string Robotsnum = line.substr(StartPos + 1);
                   RobotAmount = stoi(Robotsnum);
                   cout << "Amount of Robots: " << RobotAmount << endl;
                   
               }

          }

          for (int i = 0 ; i < RobotAmount ; i++){
             Robot robot;
             drawTheFrame(robot);
          }
       }

       

       
      
        
};
    











