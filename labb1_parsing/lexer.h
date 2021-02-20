#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <iostream>

struct lexer {

	lexer() = default;
	lexer(std::string inprogram):program(inprogram) {
		programit = program.begin();
	}

	//ger programet som ska köras till lexern
	void set_program(std::string inprogram) {
		program = inprogram;
		programit = program.begin();

	}
	//tar nästa token
	token get_token();

	void stepforward();
		

	

	//returnar innehållet i token
	std::string lex() { 
		return lexeme;
	}

	std::string lexeme; // faktiska innehållet i token
	std::string program; //programmet som ska köras
	std::string::iterator programit; // itterator för programet
};



#endif

