#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "node.h"
#include <string>

class parser {
public:
	parser(std::string program) :lexer(program), programcode(program) {

	}
	using sit = std::string::iterator;
	node* parse_pattern();
	node* parse_expr();
	node* parse_subexpr();
	node* parse_str();
	node* parse_star();
	node* parse_counter();
	node* parse_or();
	node* parse_group();

	std::string programcode;
	lexer lexer;
	
	
};




#endif


//parser för either anropar str
//parser