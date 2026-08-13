#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string filename = "data.txt";

    // =========================
    // 1. WRITE TO FILE
    // =========================

    ofstream outFile(filename);

    if(!outFile)
    {
        cout << "Error opening file for writing\n";
        return 1;
    }

    outFile << "Hello World\n";
    outFile << "This is C++ file handling.\n";
    outFile << "File handling is easy.\n";

    outFile.close();

    cout << "File written successfully.\n";


    // =========================
    // 2. READ FROM FILE
    // =========================

    ifstream inFile(filename);

    if(!inFile)
    {
        cout << "Error opening file for reading\n";
        return 1;
    }

    string line;

    cout << "\nFile contents:\n";

    while(getline(inFile, line))
    {
        cout << line << endl;
    }

    inFile.close();


    // =========================
    // 3. APPEND TO FILE
    // =========================

    ofstream appendFile(filename, ios::app);

    if(!appendFile)
    {
        cout << "Error opening file for appending\n";
        return 1;
    }

    appendFile << "This line was appended later.\n";

    appendFile.close();

    cout << "\nData appended successfully.\n";


    // =========================
    // 4. READ AGAIN
    // =========================

    ifstream file(filename);

    cout << "\nUpdated file contents:\n";

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

    return 0;
}