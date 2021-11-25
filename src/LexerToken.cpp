#include <LexerToken.hpp>

LexerToken::LexerToken(eLexerTokenType type, std::string s, unsigned int l)
	: type(type), s(s), line(l), o(nullptr) {}

LexerToken::LexerToken(eLexerTokenType type, std::string s,
			unsigned int l, IOperand *o)
	: type(type), s(s), line(l), o(o) {}

LexerToken::LexerToken(LexerToken const &t)
	: type(t.type), s(t.s) {}

LexerToken	&LexerToken::operator=(LexerToken const &rhs)
{
	*this = rhs;
	return (*this);
}

LexerToken::~LexerToken()
{}
