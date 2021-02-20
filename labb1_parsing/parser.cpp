#include "parser.h"


node* parser::parse_str() {
	token currenttoken = lexer.get_token();
	
	if (currenttoken.type != token::CHARACTER && currenttoken.type != token::ANY) {
		return nullptr;
	}
	node* str = new str_node(lexer.lex());
	lexer.stepforward();
	auto child = parse_str();

	if (child) {
		str->add(child);
	}

	return str;
}