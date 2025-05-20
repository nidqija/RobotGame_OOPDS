
    #include <string>
    #include <cstdlib>
    #include <vector>
    #include <sstream>
    #include <ctime>
    #include <iostream>
    #include <vector>

    using namespace std;



    class A {
        public:
          int x;
          A(){};


          A(A& obj){
              x = obj.x;
              cout << "hello this is " << endl;
          }



    };


