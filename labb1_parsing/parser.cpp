#include "parser.h"

node* parser::parse_pattern() {
	
	
	auto pattern = parse_expr();
	return pattern;
}
node* parser::parse_expr() {

	auto expr = parse_subexpr();

	return expr;
}

node* parser::parse_subexpr() {
	
	//ignore kollar group sen str?

	auto or_pattern = parse_or();
	if (or_pattern) {
		return or_pattern;
	}

	lexer.recreate(); //korta bara v strängen när en bit är färdiganvänd

	//group

	//whichgroup

	auto pattern = parse_str();
	return pattern;
}

node* parser::parse_str() {
	
	

	
	token currenttoken = lexer.get_token();
	
	if (currenttoken.type != token::CHARACTER && currenttoken.type != token::ANY) {
		return nullptr;
	}
	node* str;
	if (lexer.peekforward().type == token::STAR) {
		str = parse_star();

	}
	else if(lexer.peekforward().type == token::RIGHTBRACE){
		str = parse_counter();
	}
	else {
		str = new str_node(lexer.lex());
		
	}
	lexer.stepforward();
	
	auto child = parse_str();

	if (child) {
		str->add(child);
	}

	return str;
}

node* parser::parse_or() {
	auto lexer2 = lexer;
	auto str1 = parse_str();
	if (!str1) {
		return nullptr;
	}
	if (lexer.get_token().type != token::OR) {
		return nullptr;
	}
	lexer.stepforward();
	auto str2 = parse_str();
	if (!str2) {
		return nullptr;
	}

	auto or_pattern = new or_node(str1, str2);
	return or_pattern;

}

node* parser::parse_star() {

	auto starnode = new star_node(lexer.lex());
	lexer.stepforward();
	

	return starnode;
}

node* parser::parse_counter() {

	auto counternode= new counter_node(lexer.lex());
	lexer.stepforward();
	if (lexer.get_token().type != token::LEFTBRACE) {
		return nullptr;
	}
	lexer.stepforward();
	if (lexer.get_token().type != token::INTEGER) {
		return nullptr;
	}
	else {
		counternode->setcounter(stoi(lexer.lex()));
	}
	lexer.stepforward();
	if (lexer.get_token().type != token::RIGHTBRACE) {
		return nullptr;
	}

	return counternode;
}

node* parser::parse_group() {

}