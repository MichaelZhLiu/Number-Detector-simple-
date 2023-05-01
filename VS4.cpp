#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;



class TrainingData
{
public:
    int AssiociatedNumber = 0;
    vector<string> DotData; // Initialize vector to size 30
};

class PreferenceData
{
public:
    int AssiociatedNumber = 0;
    vector<double> PreferencePerDot = vector<double>(30); // Initialize vector to size 30
};




//Preferences
vector<PreferenceData> Preferences;

//Inputs
vector<double> InputedNumberDrawingDots;
string InputedNumberDrawing;

//Datas
vector<TrainingData> TrainingDatas;
int AmountOfCharacters = 30;



//Misc
double TempValue = 0;
int MostLikleyInputedValue = -999;

void SetData() {
    // For each number
    for (int x = 0; x < 10; x++) {
        // Initialize preference values to zero
        for (int i = 0; i < AmountOfCharacters; i++) {
            Preferences[x].PreferencePerDot[i] = 0.0;
        }

        // For each element of the data
        for (size_t e = 0; e < TrainingDatas[x].DotData.size(); e++) {
            // For the specific letter in an element of data
            for (int z = 0; z < AmountOfCharacters; z++) {
                string Buffer = TrainingDatas[x].DotData[e];

                char TempSymbol = Buffer[z]; // Use char instead of string for indexing

                if (TempSymbol == '#') { // Compare with char instead of string
                    Preferences[x].PreferencePerDot[z]++;
                }
            }
        }

        //Normalize preference values
        for (int i = 0; i < AmountOfCharacters; i++) {
            Preferences[x].PreferencePerDot[i] /= TrainingDatas[x].DotData.size(); // Use compound assignment operator
        }
    }
}

void Test(string TestString)
{
    //Convert TestString to a series of numbers
    vector<int> TestStringAsDigits;
    for (size_t i = 0; i < TestString.length(); i++)
    {
        if (TestString[i] == '#')
        {
            TestStringAsDigits.push_back(1);
        }
        else
        {
            TestStringAsDigits.push_back(0);
        }
    }

    double Difference = 0;
    double LeastDifference = 99999;

    for (size_t i = 0; i < 10; i++)
    {
        Difference = 0;

        for (int x = 0; x < AmountOfCharacters; x++) 
        {
            Difference += abs(Preferences[i].PreferencePerDot[x] - TestStringAsDigits[x]);
        }

        if (LeastDifference > Difference)
        {
            LeastDifference = Difference;
            MostLikleyInputedValue = i;
        }
        
    }
}

int main()
{
    //Initalize Prefrences
    for (int i = 0; i < 10; i++) 
    {
        PreferenceData TempPreferences;
        TempPreferences.AssiociatedNumber = (i + 1);
        Preferences.push_back(TempPreferences);
    }

    //Initalize Data Storage
    for (int i = 0; i < 10; i++)
    {
        TrainingData TempTrainingData;
        TempTrainingData.AssiociatedNumber = (i + 1);
        TrainingDatas.push_back(TempTrainingData);
    }


    //Initialize Training Data
    TrainingDatas[1].DotData.push_back("...##...#.#..#..#.....#.######");
    TrainingDatas[1].DotData.push_back("...##...#.#..#..#.....#..#####");
    TrainingDatas[2].DotData.push_back("..###..#...#....#....#...#####");
    TrainingDatas[3].DotData.push_back("..###..#...#....#..#...#..###.");
    TrainingDatas[4].DotData.push_back("....#....##...#.#..####.....#.");
    TrainingDatas[5].DotData.push_back("..###..#......###.....#..####.");
    TrainingDatas[6].DotData.push_back("..###..#.....####..#...#..###.");
    TrainingDatas[7].DotData.push_back("######....#....#....#....#....");
    TrainingDatas[7].DotData.push_back("######....#....#....#...#.....");
    TrainingDatas[7].DotData.push_back("######....#...#.....#....#....");
    TrainingDatas[8].DotData.push_back("..###..#...#..###..#...#..###.");
    TrainingDatas[9].DotData.push_back("..###..#...#..####....#...###.");
    TrainingDatas[0].DotData.push_back("..###..#...#.#.#.#.#...#..###.");


    char ContinueProgramAnswer;

    SetData();
    bool ContinueProgram = true;
    while (ContinueProgram) 
    {
        bool AcceptedInput = true;

        cout << "Input Number Drawing: ";
        cin >> InputedNumberDrawing;

        for (int i = 0; i < InputedNumberDrawing.length(); i++)
        {
            if (InputedNumberDrawing[i] != '.' && InputedNumberDrawing[i] != '#') 
            {
                AcceptedInput = false;
            }
        }

        if (AcceptedInput == true) 
        {
     
            Test(InputedNumberDrawing);
            cout << "Most likely inputed value is " << MostLikleyInputedValue << endl;
        }
        else 
        {
            cout << "Please Only Input Periods Or Hashmarks";
            cout << endl;
        }

        cout << "Ask another number? ";
        cin >> ContinueProgramAnswer;
        ContinueProgramAnswer = tolower(ContinueProgramAnswer);
        if (ContinueProgramAnswer == 'y' || ContinueProgramAnswer == 'yea' || ContinueProgramAnswer == 'yes' || ContinueProgramAnswer == 'yeah' || ContinueProgramAnswer == 'ye')
        {
            ContinueProgram = true;
        }
        else
        {
            exit(0);
        }
    }
}
/*
*


Ones:

...##.
..#.#.
.#..#.
....#.
######

...##...#.#..#..#.....#.######



...##.
..#.#.
.#..#.
....#.
.#####

...##...#.#..#..#.....#..#####


two:
..###.
.#...#
....#.
...#..
.#####

..###..#...#....#....#...#####



three:
..###.
.#...#
....#.
.#...#
..###.

..###..#...#....#..#...#..###.


four:
....#.
...##.
..#.#.
.####.
....#.
....#....##...#.#..####.....#.


five:
..###.
.#....
..###.
....#.
.####.

..###..#......###.....#..####.

six:
..###.
.#....
.####.
.#...#
..###.

..###..#.....####..#...#..###.

Sevens:
######
....#.
...#..
..#...
.#....


######....#....#....#....#....

######
....#.
...#..
..#...
#.....


######....#....#....#...#.....

######
....#.
..#...
..#...
.#....

######....#...#.....#....#....

eight:

..###.
.#...#
..###.
.#...#
..###.
..###..#...#..###..#...#..###.


nine:

..###.
.#...#
..####
....#.
..###.

..###..#...#..####....#...###.

zero:
..###.
.#...#
.#.#.#
.#...#
..###.
..###..#...#.#.#.#.#...#..###.

*/