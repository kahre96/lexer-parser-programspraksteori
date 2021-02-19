#include "lexer.h"

token lexer::get_token() {
	if (programit == program.end()) {
		return token{ token::EOP };
	}
	auto ch = *programit; //här är felet, itterator out of range
	lexeme = ch;
	switch (ch) {
	case '+':
		return token{ token::OR };
	case '(':
		return token{ token::LEFTPARENTHESE };
	case ')':
		return token{ token::RIGHTPARENTHESE };;
	case '\\':
		return token{ token::BACKSLASH };;
	case '{':
		return token{ token::LEFTBRACE };;
	case '}':
		return token{ token::RIGHTBRACE };;
	case '.':
		return token{ token::ANY };;
	case '*':
		return token{ token::STAR };;
	}

	if (ch >= 'A' && ch <= 'z') {
		return token{ token::CHARACTER };;
	}
	return token{ token::UNKNOWN };;
}

void lexer::stepforward(){
	programit++;


}