// Week 7 Programming Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

//Declaring and initializing constants
const string file = "BowlingScores.txt";
const int BOWLERS = 10;
const int NUMNAMES = 10;
const int NUMSCORES = 5;

//Bowling scores structure
struct BowlingScores
{
	string names; //Holds bowlers names
	int scores[NUMSCORES] = { 0 }; //Array for bowlers scores
	int average = 0; //Holds the average bowlers scores
};

//Function prototypes
bool GetBowlingData(string file, BowlingScores BowlerScores[BOWLERS]);
void GetAverageScores(BowlingScores BowlerScores[BOWLERS]);
void PrettyPrintResults(BowlingScores BowlerScores[BOWLERS]);

int main()
{
	//Variables
	BowlingScores BowlerScores[BOWLERS]; //Array for structure
	bool readSuccess;

	//Program title
	cout << setfill('*') << setw(75) << "*" << endl;
	cout << setw(55) << "Average Bowling Score's Calculator" << setw(20) << right << "*" << endl;
	cout << setw(75) << "*" << endl;

	readSuccess = GetBowlingData(file, BowlerScores);

	if (readSuccess == true) //If GetBowlingData is read successfully, continue
	{
		GetAverageScores(BowlerScores);
		PrettyPrintResults(BowlerScores);
	}
}

bool GetBowlingData(string file, BowlingScores BowlerScores[BOWLERS])
{
	//Function variables
	ifstream inFile;
	string name;
	int score;

	//Opens inFile
	inFile.open(file);
	
	//If file fails terminate program
	if (inFile.fail())
	{
		cout << "File failed to open" << endl;
		return 0;
	}

	while (!inFile.eof()) //Reads entire file
	{
		for (int i = 0; i < NUMNAMES; i++) //Outer loop to read names
		{
			inFile >> name;
			BowlerScores[i].names = name;

			for (int j = 0; j < NUMSCORES; j++) //Inner loop to read scores
			{
				//Reads in score from file
				inFile >> score;

				//If bowler is missing a score exit program
				if (score == 0)
				{
					cout << "Data read unsuccessful." << endl << endl;
					return 0;
				}
				else
					BowlerScores[i].scores[j] = score;
			}
		}
	}

	//Checks to see if there is 10 names in file
	for (int i = 0; i < NUMNAMES; i++)
	{
		if (BowlerScores[i].names == "") //If missing a name the program will terminate
		{
			cout << "Data read unsuccessful." << endl;
			return 0;
		}
	}

	cout << "Read was successful." << endl << endl;
	return true;

	//Closes file
	inFile.close();
}

void GetAverageScores(BowlingScores BowlerScores[BOWLERS])
{
	//Function variables
	int sum = 0;

	//Finds the sum of the scores and finds the average
	for (int i = 0; i < NUMNAMES; i++)
	{
		for (int j = 0; j < NUMSCORES; j++)
		{
			sum = sum + BowlerScores[i].scores[j];
		}
		BowlerScores[i].average = sum / NUMSCORES; //Divides sum of scores by number of scores
		sum = 0; //Reverts sum back to 0
	}
}

void PrettyPrintResults(BowlingScores BowlerScores[BOWLERS])
{
	//Prints results to console
	cout << "=========================================================================" << endl;
	cout << endl << setfill(' ') << "Name" << setw(38) << "Scores" << setw(39) << "Average Score" << endl;
	cout << "----" << setw(38) << "------" << setw(39) << "-------------" << endl;

	// Outer and inner loop to print names, scores, and average scores
	for (int i = 0; i < NUMNAMES; i++)
	{
		cout << setw(10) << left << BowlerScores[i].names << "|";
		for (int j = 0; j < NUMSCORES; j++)
		{
			cout << setw(10) << right << BowlerScores[i].scores[j];
		}
		cout << setw(8) << "|" << setw(8) << right << BowlerScores[i].average << endl;
	}
	cout << "========================================================================" << endl;
}

//////////////////////////////////
//////////Testing Code////////////
//////////////////////////////////

//Tests if values go into array
//for (int i = 0; i < 10; i++)
//{
	//cout << BowlerScores[i].names << endl;

	//for (int j = 0; j < 4; j++)
	//{
		//cout << BowlerScores[i].scores[j] << endl;
	//}
//}

//Tests if average scores are calculated and placed in array
//for (int i = 0; i < 10; i++)
//{
	//cout << BowlerScores[i].average << endl;
//}