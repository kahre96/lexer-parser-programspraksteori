#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <iostream>

struct lexer {

	
	lexer() = default;

	//ger programet som ska köras till lexern
	void set_program(std::string inprogram) {
		program = inprogram;
		programit = program.begin();

	}
	//tar nästa token
	token next() {		
		if (programit == program.end()) {
			return token{ token::EOP };
		}
		auto ch = *programit; //här är felet, itterator out of range
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

	//returnar innehållet i token
	std::string lex() { 
		return lexeme;
	}

	std::string lexeme; // faktiska innehållet i token
	std::string program; //programmet som ska köras
	std::string::iterator programit; // itterator för programet
};



#endif

