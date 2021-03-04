#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <iostream>
using it = std::string::iterator;

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

	token peekforward(int N);
		
	void recreate() {
		
		programit = program.begin();
	}
	void update();
	

	//returnar innehållet i token
	std::string lex() { 
		return lexeme;
	}
	std::string peeklex() {
		return peeklexeme;
	}


	std::string peeklexeme;
	std::string lexeme; // faktiska innehållet i token
	std::string program; //programmet som ska köras
	it programit; // itterator för programet
};



#endif

