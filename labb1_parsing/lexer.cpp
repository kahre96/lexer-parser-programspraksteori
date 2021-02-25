#include "lexer.h"



token lexer::get_token() {
	if (programit == program.end()) {
		return token{ token::EOP };
	}
	auto ch = *programit; //här är felet, itterator out of range
	lexeme = ch;
	if (ch == '\\') {
		programit++;
		ch = *programit;
		lexeme += ch;
		if (ch == 'I') {
			return token{ token::IGNORES };;
		}
		else if (ch == 'O') {
			return token{ token::WHICHGROUP };;
		}
		else {
			lexeme = ch;
		}
	}
	switch (ch) {
	case '+':
		return token{ token::OR };
	case '(':
		return token{ token::LEFTPARENTHESE };
	case ')':
		return token{ token::RIGHTPARENTHESE };;
	
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
	if (isdigit(ch)) {
		return token{ token::INTEGER };
	}
	return token{ token::UNKNOWN };;
}

void lexer::stepforward(){
	programit++;


}

token lexer::peekforward()
{
	if (programit == program.end()-1) {
		return token{ token::UNKNOWN };
	}
	auto next = std::next(programit, 1);

	auto nextchar = *next;
	if (nextchar == '{') {
		return token{ token::RIGHTBRACE };
	}
	if (nextchar == '*') {
		return token{ token::STAR };
	}
	return token{ token::UNKNOWN };
}

