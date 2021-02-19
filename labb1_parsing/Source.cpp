#include <iostream>
#include <Windows.h>
#include <string>

#include "lexer.h"

lexer luthor;

int main(int argc, char* argv[]){

	std::string input;
	std::getline(std::cin, input);
	luthor.set_program(input);


	while (luthor.programit != luthor.program.end()) {
		std::cout << luthor.get_token().type << "    ";
		std::cout << luthor.lex() << "\n";
		luthor.stepforward();
	}

	



















/*
	std::cout << "amount of argc: " << argc << std::endl;

	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}

	std::string lineInput;
	while (std::cin >> lineInput) {
		std::cout << lineInput;
	}
*/
	for (;;) Sleep(1000);
	
	
	
	return 0;

}



// TOKEN == BACKSLASH
// NEXT == i -> IGNORE FUNCITON
// NEXT == = -> INFANGFUNC



/*parse_pattern
* auto pare or= parse_or();
* if(!parse or){
	parse_mul = parse_mul();
	} etc
* if(!parse_mul)
* 
* 
* 
* I EXCECUTE MÖNSTERANPASSNING . = ANY CHAR RETURN TRUE
* 
* */