#include "../../testing/Tester.h"
// TextBuddy alpha version
// by: Ignatius Damai
// Assumptions used:
// -mytextfile.txt located on the same folder as the project.
// -all commands are typed with lower case
// -if the text file is not found, the program ends
// The main function of this program is to store the input sentence from the user
// and to manipulate the content of a text file.This version enables the user to
// enter commands such as add, delete, display,and clear to the program. 
// changelog from pre-alpha version:
// -allows running the program with parameter
// upcoming update:
// - usage of dynamic array of strings to simplify the usage of upcoming sort
//   and search function.
// - sorting function
// - search function
// - more update info will be released later
#include<iostream>
#include<vector>

using namespace std;

#include<fstream>
#include<sstream>
#include<string>

#include "TextBuddy.h"

const string PARAM_ERROR_MESSAGE="usage: TextBuddy <filename>";
const string FILENAME_ERROR_MESSAGE="file not found";

// This method is to test whether the file could be opened or not
bool isFileAccessable(string fileName);
bool isParameterCorrect(int numberOfArguments);
void printErrorMessage(string message);

int main (int argc,char *argv[])
{	
	runTest(argc, argv);
	/*if (isParameterCorrect(argc)) {
		// The argv[1] should contain the filename
		if (isFileAccessable(argv[1])) {
			TextBuddy run(argv[1]);
			run.runProgram();			
		} else {
		printErrorMessage(FILENAME_ERROR_MESSAGE);
		}
	}
	else {
		// We print argv[0] assuming it is the program name
			printErrorMessage(PARAM_ERROR_MESSAGE);
	}*/

	return 0;
}

//This method checks whether the textfile can be accessed or not.
bool isFileAccessable(string fileName){
	ifstream fileIO ( fileName );
		if ( !fileIO.is_open() ) {
			fileIO.close();
			return false;
		} else {
			fileIO.close();
			return true;
		}
}
//this method checks whether the argument given while starting up the program
//right or wrong.
bool isParameterCorrect(int numberOfArguments) {
	// argc should be 2 for correct execution, the first one contatins the path

	// to the program itself while the second one contains the parameter
	if (numberOfArguments==2) {
		return true;
	} else {
		return false;
	}
}
//This method prints the error message to the user
void printErrorMessage(string message) {
	cout<<message<<endl;
	
}