#include <iostream>
#include "robot3.h"

using namespace std;



int main(){
      A obj1;

        obj1.x = 10;
        cout << "Object is " << obj1.x << endl;

        A obj2(obj1);
        cout << "Object is " << obj2.x << endl;

        return 0;
}