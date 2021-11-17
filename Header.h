#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <fstream>

using namespace std;

extern string isKeyword[];

extern char isSeparator[];

extern char isOperator[];
/*  letter decimal separator operator '$' '!' 'sp || \n'
0      1      2        3         5     6   4   6 
1      1      1        3         5     1   4   2
2      0	  0		   3         5     0   0   0(final state)
3      0      0        3         5     3   4   0(separator state)
4      4      4        4         4     4   2   4(comments state)
5      0      0        3         5     3   4   0(operator state)
6      0      0        0         0     0   0   0 (invalid state)*/
struct tokens {
	string tokenString;
	int tokenType;
	tokens(string inString, int inToken) {
		tokenString = inString;
		tokenType = inToken;
	};
	/*if	keyword tokenType = 0
			Identifier tokenType = 1
			Separator tokenType= 2
			Operator TokenType= 3
			Decimal Tokentype= 4
			Comments =5
			space,\n = 6*/
};
class lexemes {
	private:
		vector <tokens>	allTokens;
		vector <string> temp;
		string temporaryHolder;
		int tokenTypeTemp;
	public:
		void getInputFromFile();
		void print();
		void lexer();
		void finalState();
		void commentState(char curChar,int &curState);
		void checker(int&curState, char tempChar);
		bool operatorChecker(char curChar);
		bool separatorChecker(char curChar);
		bool commentChecker(char curChar);
		bool keyWordChecker();
};
