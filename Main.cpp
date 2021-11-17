#include "Header.h"
string isKeyword[] = { "int", "float", "bool", "true", "false", "if", "else", "then", "endif", "while", "whileend",
"do", "doend", "for", "forend", "input", "output", "and", "or", "not" };

char isSeparator[] = { '\'','(',')','{','}','[',']',',' ,':',';' };

char isOperator[] = { '*','+','-','=','/','>','<','%' };
int main() {
	lexemes lex;
	lex.getInputFromFile();
	lex.lexer();
	lex.print();
	system("pause");
}

