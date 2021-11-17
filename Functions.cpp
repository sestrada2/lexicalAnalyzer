#include "Header.h"

//Gets input from file, insert Input.txt, Input1.txt, or Input2.txt
void lexemes::getInputFromFile()
{
	ifstream inFile;
	string tempForInfile;
	string space = " ";
	inFile.open("Input.txt");
	if (inFile) {
		while (inFile >> tempForInfile) {
			temp.push_back(tempForInfile);
			temp.push_back(space);
		}
	}
	else
		cout << "\nFile did not open, please rename file Input.txt";

	inFile.close();
}

//main lexer function, initial state calls multiple functions depending on current state
void lexemes::lexer()
{
	int curState= 0, m = 0;
	char theCharChecking;
	string theStringChecking;
	for (auto it = temp.begin(); it!=temp.end();it++) {
		theStringChecking = *it;
		for (unsigned int i = 0; i < theStringChecking.length();i++){
			theCharChecking = theStringChecking.at(i);
			//cout << theCharChecking << curState << endl;
			switch (curState) {
			case 0:
				temporaryHolder.push_back(theCharChecking);
				checker(curState, theCharChecking);
				break;
			case 1:
				checker(curState, theCharChecking);
				break;
			case 2:
				checker(curState, theCharChecking);
				break;
			case 3:
				finalState();
				temporaryHolder.clear();
				curState = 0;
				break;
			case 4:
				temporaryHolder.clear();
				commentState(theCharChecking,curState);
				break;
			case 6:
				cout << "invalid state lexer\n";
				curState = 0;
				temporaryHolder.clear();
			default:
				cout << "\n\nCase broke lexer\n\n";
				curState = 0;
				break;
			}
		}
	}
}
//print function after analyzer has completed
void lexemes::print()
{
	int j = 0;
	cout << "TOKENS\t\t\t\t" << "LEXEMES\n\n";
	for (auto& i : allTokens) {
		switch (i.tokenType) {
		case 0:
			cout << "KEYWORD\t\t\t\t" << i.tokenString << endl;
			break;
		case 1:
			cout << "IDENTIFIER\t\t\t" << i.tokenString << endl;
			break;
		case 2:
			cout << "SEPARATOR\t\t\t" << i.tokenString << endl;
			break;
		case 3:
			cout << "OPERATOR\t\t\t" << i.tokenString << endl;
			break;
		case 4:
			cout << "DECIMAL\t\t\t\t" << i.tokenString << endl;
			break;
		}
	}
}
//final state function where 
void lexemes::finalState()
{
	if (tokenTypeTemp <= 1) {
		if (keyWordChecker())
			tokenTypeTemp = 0;
		else
			tokenTypeTemp = 1;
	}
	allTokens.push_back(tokens(temporaryHolder, tokenTypeTemp));
}

void lexemes::commentState(char curChar,int &curState)
{
	if (commentChecker(curChar)) {
		curState = 0;
		temporaryHolder.clear();
	}
	else {
		curState = 4;
	}
}
//verifies current state and determines which action is next which
void lexemes::checker(int& curState, char tempChar) {

	if (isalpha(tempChar)) {
		switch (curState) {
		case 0:
			curState = 1;
			tokenTypeTemp = 1;
			break;
		case 1:
			temporaryHolder.push_back(tempChar);
			curState = 1;
			tokenTypeTemp = 1;
			break;
		case 3:
			cout << "Invalid state\n";
			curState = 0;
			break;
		case 4:
			curState = 4;
			break;
		default:
			cout << "\n\nCase Broke alpha";
			curState = 0;
			break;
		}
	}
	if (isdigit(tempChar)) {
		switch (curState) {
		case 0:
			curState = 2;
			tokenTypeTemp = 4;
			break;
		case 1:
			temporaryHolder.push_back(tempChar);
			curState = 1;
			tokenTypeTemp = 1;
			break;
		case 2:
			temporaryHolder.push_back(tempChar);
			curState = 2;
			tokenTypeTemp = 4;
			break;
		default:
			cout << "\n\nCase Broke decimal\n\n";
			curState = 0;
			break;

		}
	}
	if (operatorChecker(tempChar)) {
		switch (curState) {
		case 0:
			curState = 0;
			tokenTypeTemp = 3;
			finalState();
			temporaryHolder.clear();
			break;
		case 1:
			finalState();
			temporaryHolder.clear();
			temporaryHolder.push_back(tempChar);
			curState = 3;
			tokenTypeTemp = 3;
			break;
		case 2:
			curState = 3;
			finalState();
			temporaryHolder.clear();
			temporaryHolder.push_back(tempChar);
			tokenTypeTemp = 3;
			break;
		case 3:
			curState = 3;
			break;
		default:
			cout << "invalid operator switch \n";
			break;
		}
	}
	if (separatorChecker(tempChar)) {
		switch (curState) {
		case 0:
			curState = 0;
			tokenTypeTemp = 2;
			finalState();
			temporaryHolder.clear();
			break;
		case 1:
			finalState();
			temporaryHolder.clear();
			temporaryHolder.push_back(tempChar);
			curState = 0;
			tokenTypeTemp = 2;
			finalState();
			temporaryHolder.clear();
			break;
		case 2:
			finalState();
			temporaryHolder.clear();
			temporaryHolder.push_back(tempChar);
			curState = 0;
			tokenTypeTemp = 2;
			finalState();
			temporaryHolder.clear();
			break;
		case 3:
			curState = 3;
			break;
		default:
			cout << "invalid separator switch \n";
			break;
		}
	}
	if (tempChar == '$') {
		if (curState == 1) {
			temporaryHolder.push_back(tempChar);
			curState = 1;
		}
		else {
			curState = 6;
		}
	}
	if (commentChecker(tempChar)) {
		curState = 4;
	}
	if (tempChar == ' ') {
		//cout << "in function " << curState<<endl;
		switch (curState)
		{
		case 0:
			temporaryHolder.clear();
			curState = 0;
			break;
		case 1:
			finalState();
			temporaryHolder.clear();
			curState = 0;
			break;
		case 2:
			finalState();
			temporaryHolder.clear();
			curState = 0;
			break;
		default:
			cout << "invalid space checker";
			break;
		}
	}
	if (tempChar == '.') {
		if (curState == 2) {
			temporaryHolder.push_back(tempChar);
			curState = 2;
		}
		else {
			tokenTypeTemp = 2;
			curState = 0;
			finalState();
			temporaryHolder.clear();
		}
			
	}
}
//bool function to see if current character is an operator returns true
bool lexemes::operatorChecker(char curChar)
{
	for (int i = 0; i < 8; i++) {
		if (curChar == isOperator[i])
			return true;
	}
	return false;
}
//bool function to see if current character is a separator returns true
bool lexemes::separatorChecker(char curChar){
	for (int i = 0; i < 11; i++) {
		if (curChar == isSeparator[i])
			return true;
	}
	return false;
}
//bool function to identify ! as a comment section returns true
bool lexemes::commentChecker(char curChar)
{
	if (curChar == '!')
		return true;
	else
	{
		return false;
	}
}
//Bool function to identify keywords returns true
bool lexemes::keyWordChecker()
{
	bool key = false;
	for (int i = 0; i < 20; i++) {
		if (isKeyword[i].length() == temporaryHolder.length()) {
			for (unsigned int j = 0; j < isKeyword[i].length(); j++)
			{
				if (temporaryHolder.at(j) != isKeyword[i].at(j)) {
					j = 25;
					key = false;
				}
				else
					return true;
			}
		}
		else
			key = false;
	}
	return false;
}
