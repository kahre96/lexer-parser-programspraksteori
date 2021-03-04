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
	pattern_node* parse_pattern();
	expr_node* parse_expr();
	subexpr_node* parse_subexpr();
	str_node* parse_str();
	star_node* parse_star();
	counter_node* parse_counter();
	or_node* parse_or();
	group_node* parse_group();
	whichgroup_node* parse_which_group();
	ignore_node* parse_ignore();
	any_node* parse_any();
	char_node* parse_char();

	std::string programcode;
	lexer lexer;
	
	
};




#endif


//parser för either anropar str
//parser