/*
Written by Andrew Yahnke
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::endl;
using std::cin;

class className
{
    public:
    className (string, int);

    void incCount();
    string showName();
    int showClassCount();

    private:
    string name;
    int classCount;
};

className::className (string newName, int newClassCount)
{
    name = newName;

    classCount = newClassCount;
}

string className::showName()
{
    return name;
}

int className::showClassCount()
{
    return classCount;
}

void className::incCount()
{
    classCount++;
    return;
}

int main (void)
{
    ifstream inputFile;
    string inputData;

    vector <className> classVector;

    //Path
    string filePath = "test.log";

    string token;

    unsigned lineCount = 0;
    unsigned MOCTcount = 0;
    unsigned SMPPcount = 0;

    cout << "****************************************************************************************************\n" << endl;

    //Open File

    cout << "File is: " << filePath << endl;

    cout << "\n****************************************************************************************************" << endl;

    cout << "\nOpening log..." << endl;

    inputFile.open( filePath );

    if (!inputFile.is_open())
    {
        cout << "Could not open log" << endl;
        return 1;
    }
    else
    {
        cout << "Log file is open\n" << endl;
    }

    while(inputFile)
    {
        //Get line from inputFile and store it in inputData then push to inputVector
        getline(inputFile, inputData, '\n');

        if (!inputData.empty())
        {
            cout << inputData << "\n" << endl;

            if (inputData.find("Processing: ") != string::npos)
            {
                token = inputData.substr((inputData.find("Processing: ") + 12), inputData.find("\n"));

                for (unsigned i = 0; i  <= classVector.size(); i++)
                {

                    if ((classVector.size() == 0) || (i == classVector.size()))
                    {
                            className newClass (token, 1);
                            classVector.push_back (newClass);
                            break;
                    }

                    if (token == classVector[i].showName())
                    {
                        classVector[i].incCount();
                        break;
                    }
                }

            }

            if (inputData.find("MOCT") != string::npos)
            {
                MOCTcount++;
            }

            if (inputData.find("SMPP") != string::npos)
            {
                SMPPcount++;
            }

            lineCount++;
        }
        if (inputFile.eof())
        {
            break;
        }
    }

    cout << "\nInput file parsing finished\n" << endl;

    cout << "****************************************************************************************************\n" << endl;
    //Close File
    inputFile.close();

    cout << lineCount << " Message(s) read\n" << endl;

    cout << MOCTcount << " MOCT message(s) found\n" << endl;

    cout << SMPPcount << " SMPP message(s) found\n" << endl;

    cout << "****************************************************************************************************" << endl;

    for (unsigned i = 0; i  < classVector.size(); i++)
    {
        cout << "\n" << classVector[i].showClassCount() << " instance(s) of " << classVector[i].showName() << " found" <<endl;
    }

    cout << "\n****************************************************************************************************" << endl;

    cout << "Exiting Program" << endl;

    return (0);
}
