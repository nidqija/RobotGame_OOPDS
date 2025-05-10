void drawTheFrame() {
    FindFrame(); 
    int xValue = xval();
    int yValue = yval();

    string word = "ROBOT";
    int wordLength = word.length();
    int midRow = yValue / 2;
    int midColStart = (xValue - wordLength) / 2;

    for (int row = 0; row < yValue; ++row) {
        for (int col = 0; col < xValue; ++col) {
            // Top or bottom border
            if (row == 0 || row == yValue - 1) {
                cout << "*";
            }
            // Side borders
            else if (col == 0 || col == xValue - 1) {
                cout << "*";
            }
            // Center row: insert word
            else if (row == midRow && col >= midColStart && col < midColStart + wordLength) {
                cout << word[col - midColStart];
            }
            // Empty space
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}
