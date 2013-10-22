#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

#include"TextBuddy.h"



//set standard commands
const string TextBuddy::COMMAND_ADD="add";
const string TextBuddy::COMMAND_CLEAR="clear";
const string TextBuddy::COMMAND_DELETE="delete";
const string TextBuddy::COMMAND_DISPLAY="display";
const string TextBuddy::COMMAND_EXIT="exit";
const string TextBuddy::COMMAND_SEARCH="search";
const string TextBuddy::COMMAND_SORT="sort";

//set default output strings
const string TextBuddy::WELCOME_MESSAGE = "Welcome to TextBuddy.\n";
const string TextBuddy::ASK_FOR_COMMAND="command: ";
const string TextBuddy::ADD_SUCCESS="added to %s: \"%s\"\n";
const string TextBuddy::CLEAR_SUCCESS="all content deleted from %s\n";
const string TextBuddy::DELETE_SUCCESS="deleted from %s: \"%s\"\n";
const string TextBuddy::DISPLAY_SUCCESS="";
const string TextBuddy::SORT_SUCCESS="successfully sorted\n";

//set default error messages
const string TextBuddy::COMMAND_ERROR_MESSAGE="wrong command\nplease retry\n";
const string TextBuddy::DELETE_ERROR_MESSAGE= "error! exceeded the number of available data\n";
const string TextBuddy::DISPLAY_ERROR_MESSAGE="%s is empty\n";


// In constructor we set the initiate value of fileName and fileAppend
// The value of fileIn and fileOut is not initiated because we need to
// reset the cursor every time
TextBuddy::TextBuddy(string file){
	fileName=file;
	fileAppend.open(file,fstream::app);
}


// This function manages the command inputs and calls the run command function
void TextBuddy::runProgram(){

	string userCommand;
	showToUser(WELCOME_MESSAGE);
	showToUser(ASK_FOR_COMMAND);
	userCommand=readUserInput();
	while(userCommand!=COMMAND_EXIT){		
		runCommand(userCommand);
		showToUser(ASK_FOR_COMMAND);
		userCommand=readUserInput();
	}
}


//this method is for reading user input
string TextBuddy::readUserInput(){
	string userInput;
	cin>> userInput;
	return userInput;
}

// handles command operation inside text buddy program
void TextBuddy::runCommand(string userCommand) {
	if (userCommand==COMMAND_ADD) {						
		addText();
					
	} else if (userCommand==COMMAND_CLEAR) {
		clearText();

	} else if (userCommand==COMMAND_DISPLAY) {
		displayText();

	} else if (userCommand==COMMAND_DELETE) {
		deleteText();
	} else if (userCommand==COMMAND_SEARCH) {
		searchText();
	} else if (userCommand==COMMAND_SORT) {
		sortText();	
	} else if (userCommand==COMMAND_EXIT) {
		exit;
	} else {
		showToUser(COMMAND_ERROR_MESSAGE);
	}
}

//This method copies everything inside the textfile to temporary vector
void TextBuddy::storeToTempContent() {

	string temp;
	fileIn.open(fileName);

	while (getline(fileIn,temp)) {
		tempContent.push_back(temp);
	}

	fileIn.close();

}

//This method writes the contents of the tempContent to .txt file.
void TextBuddy::copyTempContentToFile(){
	int size = tempContent.size();
	int i;

	clearTextFile();

	for (i=0;i<size;i++) {
		fileAppend<<tempContent[i]<<endl;
	}

}

//This method empties tempContent vector
void TextBuddy::emptyTempContent() {
	int originalSize = tempContent.size();
	int i;

	for (i=0;i<originalSize;i++) {
		tempContent.pop_back();
	}
}


// Method to add text using getline then append it to the end of text file
void TextBuddy::addText(){
	string tempLine;
	// this get char eats the space character from user's input
	getchar();
	getline(cin,tempLine);	
	operationResult=addTextToFile(tempLine);
	showToUser(operationResult);
}



//clears the text file by rewriting the fle to ""
void TextBuddy::clearText(){
	operationResult=clearTextFile();
	showToUser(operationResult);
}

//read in input from user which will state the index of the line going to be deleted
//deleteing the text by storing the text file contents to tempLines first
//appending the texts back text file after operation finishes
void TextBuddy::deleteText(){

	int index;
	cin>>index;
	operationResult=deleteFromFile(index);
	showToUser(operationResult);
	
}

// reading the file contents from the beginning of the file and print it one by one
void TextBuddy::displayText(){
	operationResult=printFileContent();
	showToUser(operationResult);	
}

//This method shows the user every content that contains the keyword user entered
void TextBuddy::searchText() {
	int size;
	int i;

	string keyword;
	keyword=readUserInput();
	storeToTempContent();
	size=tempContent.size();

	for (i=0;i<size;i++)
	{
		if (!tempContent[i].find(keyword)) {
			showToUser(tempContent[i]+"\n");
		}
	}
	emptyTempContent();

}

//This method copies everything in the file to the tempContent vector and sort it
//after the sorting process is finished, the content of tempContent will be copied back to .txt file
void TextBuddy::sortText(){
	operationResult=sortFileContent();
	showToUser(operationResult);
}

string TextBuddy::addTextToFile(string toBeAdded) {
	fileAppend<<toBeAdded<<endl;
	sprintf_s(buffer,ADD_SUCCESS.c_str(),fileName.c_str(),toBeAdded.c_str());
	return buffer;
}

string TextBuddy::deleteFromFile(int index) {
	string toBeDeleted;
	storeToTempContent();

	if (tempContent.size()<index) {
		return DELETE_ERROR_MESSAGE;		
	}
	else {
		toBeDeleted=tempContent[index-1];

		for (int i=index-1;i<tempContent.size()-1;i++){
			tempContent[i]=tempContent[i+1];
		}

		tempContent.pop_back();
		clearTextFile();

		for (int j=0;j<tempContent.size();j++) {
			fileAppend<<tempContent[j]<<endl;
		}

		emptyTempContent();
		sprintf_s(buffer,DELETE_SUCCESS.c_str(),fileName.c_str(),toBeDeleted.c_str());
		return buffer;
	}
}

string TextBuddy::clearTextFile() {
	fileOut.open(fileName);
	fileOut.close();
	sprintf(buffer,CLEAR_SUCCESS.c_str(),fileName.c_str());
	return  buffer;
}

// This method prints the content of the file by reading the lines from the text file
string TextBuddy::printFileContent() {
	string tempLine;
	int counter=0;

	fileIn.open(fileName);

	while (getline(fileIn,tempLine)){
		cout<<++counter<<". "<<tempLine<<endl;
	}
	
	fileIn.close();
	if (counter<=0){
		sprintf(buffer,DISPLAY_ERROR_MESSAGE.c_str(),fileName.c_str());
		return buffer;
	} else {
		return DISPLAY_SUCCESS;
	}
}
//this method sorts the file contennt using built in sort algorithm
string TextBuddy::sortFileContent() {
	storeToTempContent();
	sort(tempContent.begin(),tempContent.end(),isAlphabeticallyOrdered);
	copyTempContentToFile();
	emptyTempContent();
	return  SORT_SUCCESS;
}

// printing the result of each operation
void TextBuddy::showToUser(string output) {
	cout<<output;
}



TextBuddy::~TextBuddy(){
	fileAppend.close();
}

//This is the strict weak ordering condition for the sort function
bool isAlphabeticallyOrdered(string &str1, string &str2) {
	return str1<str2;
}