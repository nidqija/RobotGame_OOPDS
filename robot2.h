
    #include <string>
    #include <cstdlib>
    #include <vector>
    #include <sstream>
    #include <ctime>
    #include <iostream>

    using namespace std;

class Robot {
private:
    string symbol;

public:
    int x, y;
    Robot() {
        x = 1; // default to frame
        y = 1;
        symbol = "R";
    }

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int x_) { x = x_; }
    void setY(int y_) { y = y_; }
    string ReturnRobot() const { return symbol; }
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