#include <iostream>
#include <Windows.h>
#include <string>

#include "parser.h"

lexer luthor;

int main(int argc, char* argv[]){
	//std::string data = "promise to (Love+Hate)\\I you\\O{1}";
	std::string data = "promise to (Love+Hate)\\I you\\O{1}";
	std::string input;
	std::getline(std::cin, input);

	luthor.set_program(data);


	while (luthor.programit != luthor.program.end()) {
		std::cout << luthor.get_token().type << "    ";
		std::cout << luthor.lex() << "\n";
		luthor.stepforward();
	}

	parser test(data);

	auto result = test.parse_pattern();
	result->print();
	result->set_input(input);
	if (result->evaluate()) {
		result->view_match();
		return EXIT_SUCCESS;
	}
	else {
		std::cout << "???" << std::endl;
		return EXIT_FAILURE;
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



//skapa lokal itterator som startar på först parametern