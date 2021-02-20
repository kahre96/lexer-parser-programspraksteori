#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "node.h"
#include <string>

class parser {
public:
	parser(std::string program) :lexer(program), programcode(program) {

	}


	node* parse_str();

	std::string programcode;
	lexer lexer;
};




#endif


//parser för either anropar str
//parser