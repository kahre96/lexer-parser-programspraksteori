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
		IGNORES,
		WHICHGROUP,
		UNKNOWN,
		INTEGER,
		EOP
	};
	type type;
};


/*
* <pattern> -> <expr>
* <expr> -> <subexp> <expr> | <subexpr>
* <subexpr> -> <ignore>
*			| <or>
*			| <group>
*			| <whichgroup>
*			| <str>
*	< or > -> <str> + <str>
*	<str> <star>[<str] |  <char> [<str>]  | <counter><str>
*	<char> -> [ A-z]
*	<star> -> <char> "*"
*	<group> -> ( <subexpr> )
*	< any > ->  "."
*	< counter > -> <char> "{"  { <integer> }  "}"
*	< integer > ->[0..9]
*	<ignore> -> <group> \I | <str> \I
*	<whichgroup> ->  "\O{ <integer> }"
*/
#endif