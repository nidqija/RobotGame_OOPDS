#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Frame {
private:
    string line;
    int extractedVal1 = 0, extractedVal2 = 0;

public:
    // Method to read and extract values from file
    void FindFrame() {
        ifstream inputFile("input.txt");

        if (!inputFile) {
            cout << "Input file cannot be opened" << endl;
            return;
        }

        while (getline(inputFile, line)) {
            if (line.find("40 50") != string::npos) {
                cout << "Frame : 40 50" << endl;

                size_t StartPosition = line.find("40");
                size_t EndPosition = line.find("50");

                string val1 = line.substr(StartPosition, 2);
                string val2 = line.substr(EndPosition, 2);

                extractedVal1 = stoi(val1);
                extractedVal2 = stoi(val2);

                cout << "Extracted X: " << extractedVal1 << endl;
                cout << "Extracted Y: " << extractedVal2 << endl;
                break;
            }
        }
    }

    // Getters
    int xval() const {
        return extractedVal1;
    }

    int yval() const {
        return extractedVal2;
    }
};

class DrawFrame : public Frame {
public:
    void drawTheFrame() {
        FindFrame();  // First, parse the file and set values

        int xValue = xval();
        int yValue = yval();

        cout << "\nDrawing frame of size: " << xValue << " x " << yValue << "\n\n";

        // Print top border
        for (int column = 0; column < xValue; ++column) {
            cout << "*";
        }
        cout << "\n";

        // Print middle part of the frame
        for (int row = 0; row < yValue - 2; ++row) {  // Exclude top and bottom rows
            cout << "*";
            for (int column = 0; column < xValue - 2; ++column) {
                cout << " ";
            }
            cout << "*\n";
        }

        // Print bottom border
        for (int column = 0; column < xValue; ++column) {
            cout << "*";
        }
        cout << "\n";
    }
};

int main() {
    DrawFrame df;
    df.drawTheFrame();
    return 0;
}
