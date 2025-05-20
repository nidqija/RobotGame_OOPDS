
    #include <string>
    #include <cstdlib>
    #include <vector>
    #include <sstream>
    #include <ctime>
    #include <iostream>
    #include <vector>

    using namespace std;

class Robot {
private:
    string symbol;
    string line;
    
    vector<vector<int>>robotAmount;
    
public:
    int x, y;
    Robot() {
        x = 1; 
        y = 1;
        symbol = "R";
    }

      Robot(const Robot& robot) {
        x = robot.x;
        y = robot.y;
        symbol = robot.symbol;
    }

     


      

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int x_) { x = x_; }
    void setY(int y_) { y = y_; }
    string ReturnRobot() const { return symbol; }


    string DetectRobot(){
      ifstream inputFile("input.txt");

       while (getline(inputFile, line)) {
            // Process only lines that contain "GenericRobot"
            if (line.find("GenericRobot") != string::npos) {
                size_t StartPos = line.find("GenericRobot");
                
                // Create stream from substring starting from "GenericRobot"
                istringstream iss(line.substr(StartPos));
                
                string tag, robotName , robotInitial;
                int x, y;


                // Extract: tag (e.g., "GenericRobot"), name, and two coordinates
                iss >> tag >> robotName >> x >> y;
                robotInitial = robotName.substr(0,1);

  
                

                // Print robot name (can be removed for silent loading)
                cout << robotName << endl;
            }
        }

    }
};



    class MovingBot : public Robot{
        private:
        string line;
        int robotChoice;

        public:

        friend class Battlefield;
        int randomNumbers(){
            cout << robotChoice << endl;
        };


        MovingBot() : Robot(){
            robotChoice = 0;
        }


        MovingBot(const MovingBot& other ) : Robot(other){
            this-> robotChoice = other.robotChoice;
        }



       


     void MovetheBot() {
    robotChoice = rand() % 8;

    switch (robotChoice) {
        case 0: x -= 1; break;               // Left
        case 1: x += 1; break;               // Right
        case 2: y -= 1; break;               // Up
        case 3: y += 1; break;               // Down
        case 4: x += 1; y -= 1; break;       // Top-right
        case 5: x -= 1; y -= 1; break;       // Top-left
        case 6: x += 1; y += 1; break;       // Bottom-right
        case 7: x -= 1; y += 1; break;       // Bottom-left
    }
}



   int ReturnSetX() const{
     return x;
   }

     int ReturnSetY() const{
     return y;
   }



        
    };







