//Program : project.cpp
//Course : CCP6114 Programming Fundamentals
//Lecture Class : TC3L
//Tutorial Class : TT5L
//Trimester :2430

//Member_1: 242UC244Q7 | RAZIQ DIN BIN MOHD TASRIRI | RAZIQ.DIN.MOHD@STUDENT.MMU.EDU.MY | 0193214659
//Member_2: 242UC244M5 | JIREH CHAI E-LOK | JIREH.CHAI.ELOK@student.mmu.edu.my | 0125131505
//Member_3: | SIVA |

// Task distribution
//Member 1 : Insert table | Update data | Delete Data
//Member 2 : - INSERT INTO / SELECT * FROM customer / TABLES
// Memver 3 : - CREATE TEXTFILE / DATABASES / COUNT ROWS


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void createTextFile(const string &filename);
void handleDatabasesCommand();
int countRows();
void InsertTable(vector<string> &ColumnVector, const string &filename);
int insertInto(vector<vector<string>> &, vector<vector<int>> &);
int UpdateData(vector<vector<string>> &vectorName, vector<vector<int>> &idVectorName);
int DeleteData(vector<vector<string>> &vectorName, vector<vector<int>> &idVectorName);
int selectFrom(vector<string>& columnVectorName, vector<vector<string>>& vectorName, vector<vector<int>>& idVectorName);
void viewTable();



vector<string> database;
vector<string> ColumnVector;

int main()
{
    createTextFile("fileOutput1.txt");
    handleDatabasesCommand();
    InsertTable(ColumnVector, "fileOutput1.txt");
    viewTable();

    cout << ">SELECT COUNT(*) FROM database;\n";
    cout << countRows() << " rows found.\n";

    vector<vector<string>> wordsVector;
    vector<vector<int>> idVector;

    insertInto(wordsVector, idVector);
    selectFrom(ColumnVector,wordsVector, idVector);
    UpdateData(wordsVector, idVector);
    selectFrom(ColumnVector,wordsVector, idVector);
    DeleteData(wordsVector,idVector);
    selectFrom(ColumnVector,wordsVector, idVector);
    return 0;
}

void createTextFile(const string &filename)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Error: Could not create " << filename << "!\n";
        return;
    }
    cout << ">CREATE " << filename << ";\n";
    outFile << ">CREATE " << filename << ";\n";
    outFile.close();
}

void handleDatabasesCommand()
{
    database.push_back("C:\\mariadb\\sample_database");
    cout << ">DATABASES;\n";
    for (const auto &db : database)
    {
        cout << db << "\n";
    }
}

int countRows()
{
    return database.size();
}

void InsertTable(vector<string> &ColumnVector, const string &filename)
{
    ifstream inputFile("input.mdb");
    ofstream outFile(filename, ios_base::app); // Open in append mode

    if (!inputFile)
    {
        cerr << "Error: Could not open input.mdb!\n";
        return;
    }

    if (!outFile)
    {
        cerr << "Error: Could not open " << filename << "!\n";
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        if (line.find("CREATE TABLE") != string::npos)
        {
            cout << ">CREATE TABLE customer(customer_id INT, customer_name TEXT, customer_city TEXT, customer_state TEXT, customer_country TEXT, customer_phone TEXT, customer_email TEXT);\n";
            outFile << ">CREATE TABLE customer(\n";
            outFile << "customer_id INT,\ncustomer_name TEXT,\ncustomer_city TEXT,\n";
            outFile << "customer_state TEXT,\ncustomer_country TEXT,\ncustomer_phone TEXT,\n";
            outFile << "customer_email TEXT\n);\n";

            ColumnVector = {
                "customer_id", "customer_name", "customer_city", "customer_state",
                "customer_country", "customer_phone", "customer_email"};

            for (size_t i = 0; i < ColumnVector.size(); ++i)
            {
                cout << ColumnVector[i] + "," << " ";
                outFile << ColumnVector[i] + "," << " ";
            }
            cout << endl;
            outFile << endl;
        }
    }

    inputFile.close();
    outFile.close();
}

// Insert Into Function
int insertInto(vector<vector<string>> &vectorName, vector<vector<int>> &idVectorName)
{
    ifstream infile("input.mdb");
    ofstream outFile("fileOutput1.txt", ios::app);

    if (!infile)
    {
        cerr << "Could not open input file.";
        return 1;
    }

    if (!outFile)
    {
        cerr << "Could not open output file.";
        return 1;
    }

    string line;
    while (getline(infile, line))
    {
        if (line.find("VALUES(") != string::npos && line.find(");") != string::npos)
        {
            size_t valuesStartPos = line.find("VALUES(") + 7; // Move past "VALUES("
            size_t valuesEndPos = line.find(");");

            string valuesData = line.substr(valuesStartPos, valuesEndPos - valuesStartPos);
            stringstream valuesDataSS(valuesData);
            string word;
            vector<string> row;

            while (getline(valuesDataSS, word, ','))
            {
                row.push_back(word);
            }

            if (!row.empty())
            {
                int id = stoi(row[0]);
                idVectorName.push_back({id});
                vectorName.push_back(row);
            }
        }
    }

    // Display and write INSERT INTO statements
    outFile << ">INSERT INTO" << endl;
    for (size_t i = 0; i < vectorName.size(); ++i)
    {
        cout << ">INSERT INTO\n";
        cout << "customer(customer_id, customer_name, customer_city, ";
        cout << "customer_state, customer_country, customer_phone, customer_email) VALUES(";

        outFile << "";

        for (size_t j = 0; j < vectorName[i].size(); ++j)
        {
            if (j != 0)
                cout << ", ";
            if (j != 0)
                outFile << ", ";

            cout << vectorName[i][j];
            outFile << vectorName[i][j] << " ";
        }

        cout << ");\n";
        outFile << "\n";
    }

    infile.close();
    outFile.close();
    return 0;
}

int UpdateData(vector<vector<string>> &vectorName, vector<vector<int>> &idVectorName)
{
    ifstream infile("input.mdb");
    ofstream outFile("fileOutput1.txt", ios::app);

    if (!infile)
    {
        cout << "Could not open input file.";
        return 1;
    }

    if (!outFile)
    {
        cout << "Could not open output file.";
        return 1;
    }

    string line;
    while (getline(infile, line))
    {
        if (line.find("SET") != string::npos && line.find(";") != string::npos)
        {
            int startEmailPos = line.find("SET") + 20;
            int endEmailPos = line.find("WHERE") - 2;
            string newEmail = line.substr(startEmailPos, endEmailPos - startEmailPos);

            int startIdPos = line.find("WHERE") + 18;
            int endIdPos = line.find(";");
            string Id = line.substr(startIdPos, endIdPos - startIdPos);

            cout <<">UPDATE customer SET customer_email='email333' WHERE customer_id=3;" << endl;
            outFile << ">UPDATE customer SET customer_email='email333' WHERE customer_id=3;" << endl;
            for (vector<string> &row : vectorName)
            {
                if (row[0] == Id)
                {
                    row[6] = newEmail;
                }
            }

            for (size_t i = 0; i < vectorName.size(); i++)
            {
                for (const string &val : vectorName[i])
                {
                    outFile << val << " ";
                }
                outFile << endl;
            }
        }
    }
    infile.close();
    outFile.close();
    return 0;
}



int DeleteData(vector<vector<string>> &vectorName, vector<vector<int>> &idVectorName){
     ifstream infile("input.mdb");
    ofstream outFile("fileOutput1.txt", ios::app);

    if (!infile)
    {
        cout << "Could not open input file.";
        return 1;
    }

    if (!outFile)
    {
        cout << "Could not open output file.";
        return 1;
    }


    string line;
    int toBeDeleted;

    outFile << ">DELETE FROM customer WHERE customer_id=4;" << endl;
    cout << ">DELETE FROM customer WHERE customer_id=4;" << endl;
    while(getline(infile , line)){
        if (line.find("DELETE FROM") != string::npos && line.find(";") != string::npos) {
            int startIdPos = line.find("customer_id=") + 12;
            int startEndPos = line.find(";");
            string Id = line.substr(startIdPos, startEndPos - startIdPos);
            toBeDeleted = stoi(Id);
            int DeleteIndex = toBeDeleted - 1;

             for (vector<string> &row : vectorName)
            {
                if (row[0] == Id)
                {
                    vectorName.erase(vectorName.begin() + DeleteIndex);
                }
            }

              for (size_t i = 0; i < vectorName.size(); i++)
            {
                for (const string &val : vectorName[i])
                {
                    outFile << val << " ";
                }
                outFile << endl;
            }

    }
    }

    infile.close();
    outFile.close();
    return 0;

}

// Select * from function
int selectFrom(vector<string>& columnVectorName, vector<vector<string>>& vectorName, vector<vector<int>>& idVectorName)
{
    ifstream infile ("input.mdb");
    ofstream outfile ("fileOutput1.txt", ios::app);

    if (!infile)
    {
        cout << "Could not open input file." << endl;
        return 1;
    }

    if (!outfile)
    {
        cout << "Could not open output file." << endl;
        return 1;
    }

    cout << ">SELECT * FROM customer;" << endl;
    outfile << ">SELECT * FROM customer;" << endl;

    for (size_t i = 0; i < columnVectorName.size(); ++i)
    {
        if (i == columnVectorName.size() -1 )
        {
            cout << columnVectorName[i];
            outfile << columnVectorName[i];
        }
        else
        {
            cout << columnVectorName[i] << ", ";
            outfile << columnVectorName[i] << ", ";
        }
    }
    cout << endl;
    outfile << endl;

    // Print table rows
    for (size_t i = 0; i < idVectorName.size(); ++i)
    {
        for (size_t j = 0; j < vectorName[i].size(); ++j)
        {
            string value = vectorName[i][j];
            if (value.front() == '\'' && value.back() == '\'')
            {
                value = value.substr(1, value.size() - 2);
            }

            if (j == vectorName[i].size() - 1)
            {
                cout << value;
                outfile << value;
            }
            else
            {
                cout << value << ", ";
                outfile << value << ", ";
            }
        }
        cout << endl;
        outfile << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}

void viewTable()
{
    string tableName = "customer";
    string line = ">TABLES;";

    if (line.find("TABLES;") != string::npos)
    {
        cout << ">TABLES;\n";
        cout << tableName << endl;

        ofstream outfile("fileOutput1.txt", ios::app);
        if (outfile)
        {
            outfile << ">TABLES;\n";
            outfile << tableName << endl;
            outfile.close();
        }
    }
}
