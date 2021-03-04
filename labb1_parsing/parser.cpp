#include "parser.h"

//<pattern> -> <expr>
pattern_node* parser::parse_pattern() {
	
	pattern_node* pattern = new pattern_node;
	auto expr = parse_expr();
	if (expr) {
		pattern->add(expr);
		
	}
	return pattern;
}
//<expr> -> <subexp> <expr> | <subexpr>
expr_node* parser::parse_expr() {

	
	
	expr_node* expr = new expr_node;
	while (lexer.programit != lexer.program.end()) {
		
		auto subexpr = parse_subexpr();
		if (subexpr) {
			expr->add(subexpr);

		}
	}
	
	return expr;
}

//<subexpr> -> <ignore> | < or > | <group> | <whichgroup> | <str>
subexpr_node* parser::parse_subexpr() {
	lexer.update();
	
	subexpr_node* subexpr_pattern = new subexpr_node;

	//parsar efter ignore
	ignore_node* ignore_pattern = parse_ignore();
	if (ignore_pattern) {
		subexpr_pattern = new subexpr_node;
		subexpr_pattern->add(ignore_pattern);
		return subexpr_pattern;
	}
	lexer.recreate();


	or_node* or_pattern = parse_or();
	if (or_pattern) {
		subexpr_pattern->add(or_pattern);
		return subexpr_pattern;
	}

	lexer.recreate(); //korta bara v strängen när en bit är färdiganvänd

	group_node* group_pattern = parse_group();
	if (group_pattern) {
		subexpr_pattern->add(group_pattern);
		return subexpr_pattern;
	}
	whichgroup_node* which_group_pattern = parse_which_group();
	if (which_group_pattern) {
		subexpr_pattern->add(which_group_pattern);
		return subexpr_pattern;
	}


	str_node* str_pattern = parse_str();
	if (str_pattern) {
		subexpr_pattern->add(str_pattern);
		return subexpr_pattern;
	}



	lexer.stepforward();
	return nullptr;
}

//<str> <star>[<str] |  <char> [<str>]  | <counter><str>
str_node* parser::parse_str() {






	if (lexer.get_token().type != token::CHARACTER && lexer.get_token().type != token::ANY) {
		return nullptr;
	}
	str_node* str = new str_node(lexer.lex());
	if (lexer.peekforward(1).type == token::STAR) {
		star_node* starchild = parse_star();

		if (starchild) {
			str->add(starchild);
		}
		lexer.stepforward();

	}
	else if (lexer.peekforward(1).type == token::LEFTBRACE) {
		counter_node* counterchild = parse_counter();
		if (counterchild) {
			str->add(counterchild);
		}
		lexer.stepforward();
	}
	else {

		char_node* child = parse_char();

		if (child) {
			str->add(child);
		}
		lexer.stepforward();
		str_node* child2 = parse_str();

		if (child2) {
			str->add(child2);
		}

	}
	




	return str;
}

//< or > -> <str> + <str>
or_node* parser::parse_or() {
	
	str_node* str1 = parse_str();
	if (!str1) {
		return nullptr;
	}
	if (lexer.get_token().type != token::OR) {
		return nullptr;
	}
	lexer.stepforward();
	str_node* str2 = parse_str();
	if (!str2) {
		return nullptr;
	}

	or_node* or_pattern = new or_node(str1, str2);
	return or_pattern;

}

//<star> -> <char> "*"
star_node* parser::parse_star() {

	star_node* starnode = new star_node(lexer.lex());

	char_node* child = parse_char();

	if (child) {
		starnode->add(child);
	}
	any_node* child2 = parse_any();

	if (child2) {
		starnode->add(child2);
	}

	lexer.stepforward();
	/*
	if (child2) {
		if (lexer.peekforward(1).type == token::RIGHTPARENTHESE) {
			if (lexer.peekforward(2).type == token::CHARACTER || lexer.peekforward(2).type == token::ANY) {
				starnode->setbreak(lexer.peeklex());
			}

		}
		else if (lexer.peekforward(2).type == token::CHARACTER || lexer.peekforward(2).type == token::ANY) {
			starnode->setbreak(lexer.peeklex());
		}
	}
	*/

	return starnode;
}

//< counter > -> <char> "{"  { <integer> }  "}"
counter_node* parser::parse_counter() {

	counter_node* counternode= new counter_node(lexer.lex());
	char_node* child = parse_char();

	if (child) {
		counternode->add(child);
	}
	any_node* child2 = parse_any();

	if (child2) {
		counternode->add(child2);
	}
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

//<group> -> ( <subexpr> )
group_node* parser::parse_group() {

	

	if (lexer.get_token().type != token::LEFTPARENTHESE) {
		return nullptr;
	}
	lexer.stepforward();
	group_node* group = new group_node;
	subexpr_node* child = parse_subexpr();

	if (child) {
		group->add(child);
	}
	if (lexer.get_token().type == token::RIGHTPARENTHESE) {
		lexer.stepforward();
	}
	return group;
}

//<whichgroup> ->  "\O{ <integer> }"
whichgroup_node* parser::parse_which_group() {

	
	int counter;
	if (lexer.get_token().type != token::WHICHGROUP) {
		return nullptr;
	}
	lexer.stepforward();
	lexer.stepforward();
	if (lexer.get_token().type != token::LEFTBRACE) {
		return nullptr;
	}
	lexer.stepforward();
	if (lexer.get_token().type != token::INTEGER) {
		return nullptr;
	}
	else {
		counter = stoi(lexer.lex());
	}
	lexer.stepforward();
	if (lexer.get_token().type != token::RIGHTBRACE) {
		return nullptr;
	}
	lexer.stepforward();
	whichgroup_node* whichnode = new whichgroup_node(counter);
	
	return whichnode;

}

//<ignore> -> <group> \I | <str> \I
ignore_node* parser::parse_ignore() {
	ignore_node* ignore = new ignore_node();
	if (lexer.get_token().type == token::LEFTPARENTHESE) {
		group_node* groupignore = parse_group();
		if (groupignore) {

			if (lexer.get_token().type != token::IGNORES) {
				return nullptr;
			}
			ignore->add(groupignore);
			lexer.stepforward();
			lexer.stepforward();
			return ignore;

		}
	}
	
	
	
	str_node* strignore = parse_str();
	if (!strignore) {
		return nullptr;
	}
	if (lexer.get_token().type != token::IGNORES) {
		return nullptr;
	}
	ignore->add(strignore);
	lexer.stepforward();
	lexer.stepforward();
	return ignore;

}

any_node* parser::parse_any() {

	if (lexer.get_token().type != token::ANY) {
		return nullptr;
	}
	any_node* any = new any_node;

	return any;

}
char_node* parser::parse_char() {
	if (lexer.get_token().type != token::CHARACTER) {
		return nullptr;
	}
	char_node* charp = new char_node(lexer.lex());

	return charp;
}