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

	//ger programet som ska k�ras till lexern
	void set_program(std::string inprogram) {
		program = inprogram;
		programit = program.begin();

	}
	//tar n�sta token
	token get_token();
	

	void stepforward();

	token peekforward(int N);
		
	void recreate() {
		
		programit = program.begin();
	}
	void update();
	

	//returnar inneh�llet i token
	std::string lex() { 
		return lexeme;
	}
	std::string peeklex() {
		return peeklexeme;
	}


	std::string peeklexeme;
	std::string lexeme; // faktiska inneh�llet i token
	std::string program; //programmet som ska k�ras
	it programit; // itterator f�r programet
};



#endif

