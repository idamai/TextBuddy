#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

const int DEFAULT_BUFFER_SIZE=255;
// TextBuddy class is used to store all functionalities inside the
// TextBuddy program it includes adding, deleting, displaying,
// and clearing functions
bool isAlphabeticallyOrdered(string &str1,string & str2);

class TextBuddy{
public:
	//output string container
	char buffer[DEFAULT_BUFFER_SIZE];
	//default output strings
	//set standard commands
	static const string COMMAND_ADD;
	static const string COMMAND_CLEAR;
	static const string COMMAND_DELETE;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_EXIT;
	static const string COMMAND_SEARCH;
	static const string COMMAND_SORT;

	//set default output strings
	static const string WELCOME_MESSAGE;
	static const string ASK_FOR_COMMAND;
	static const string ADD_SUCCESS;
	static const string CLEAR_SUCCESS;
	static const string DELETE_SUCCESS;
	static const string DISPLAY_SUCCESS;
	static const string SORT_SUCCESS;

	//set default error messages
	static const string COMMAND_ERROR_MESSAGE;
	static const string DELETE_ERROR_MESSAGE;
	static const string DISPLAY_ERROR_MESSAGE;

	string fileName;
	string operationResult;
	fstream fileAppend;
	ifstream fileIn;
	ofstream fileOut;
	vector<string> tempContent;

	string readUserInput();
	void runCommand(string userCommand);
	void storeToTempContent();
	void emptyTempContent();
	void copyTempContentToFile();
	//Method that directly interfacing the run command method
	void addText();
	void clearText();	
	void deleteText();	
	void displayText();
	void searchText();
	void sortText();
	//Methods that contains the implementation of the functionalities
	string addTextToFile(string toBeAdded);
	string deleteFromFile(int index);
	string printFileContent();
	string sortFileContent();
	string clearTextFile();
	void showToUser(string output);

public:
	TextBuddy(string file);
	void runProgram();
	~TextBuddy();
};

#endif