#ifndef TOKEN_H
#define TOKEN_H

struct token {

	enum type {
		OR,
		CHARACTER,
		LEFTPARENTHESE,
		RIGHTPARENTHESE,
		LEFTBRACE,
		RIGHTBRACE,
		STAR,
		ANY,
		BACKSLASH,
		UNKNOWN,
		EOP
	};
	type type;
};


/*
* <pattern> -> <expr>
* <expr> -> <subexp> <expr> | <subexpr>
* <subexpr> -> <or>
*			| <infang>
*			|<str>
*	< or > -> <str> + <str>
*	<str> <star>[<str] |  <char> [<str>]  | <counter><str>
*	<char> -> <any> | [ A-z]
*	<star> -> <char> "*"
*	<infang> -> ( <patern> )
*	< any > ->  "."
*	< counter > -> <char> "{"  { <integer> }  "}"
*	< integer > ->[0..9]
*	<ignore> -> <str> \I
*	<vilkeninfang> ->  "\O{ <integer> }"
*/
#endif