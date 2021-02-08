#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <iostream>

struct lexer {

	
	lexer() = default;

	//ger programet som ska k�ras till lexern
	void set_program(std::string inprogram) {
		program = inprogram;
		programit = program.begin();

	}
	//tar n�sta token
	token next() {		
		if (programit == program.end()) {
			return token{ token::EOP };
		}
		auto ch = *programit; //h�r �r felet, itterator out of range
		lexeme = ch;
		switch (ch) {
		case '+':
			return token{token::OR};
		case '(':
			return token{ token::LEFTPARENTHESE };
		case ')':
				return token{ token::RIGHTPARENTHESE };;
		case '\\':
			return token{ token::BACKSLASH };;
		case '{':
			return token{ token::LEFTBRACE };;
		case '}':
			return token{ token::RIGHTBRACE };;
		case '.':
			return token{ token::ANY };;
		case '*':
			return token{ token::STAR };;
		}
		
		if (ch >= 'A' && ch <= 'z') {
			return token{ token::CHARACTER };;
		}
		return token{ token::UNKNOWN };;

	}

	//returnar inneh�llet i token
	std::string lex() { 
		return lexeme;
	}

	std::string lexeme; // faktiska inneh�llet i token
	std::string program; //programmet som ska k�ras
	std::string::iterator programit; // itterator f�r programet
};



#endif

