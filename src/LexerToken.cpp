#include <LexerToken.hpp>

LexerToken::LexerToken(eLexerTokenType type, std::string s, unsigned int l)
	: type(type), s(s), line(l) {}

LexerToken::LexerToken(LexerToken const &t)
	: type(t.type), s(t.s), line(t.line) {}

LexerToken	&LexerToken::operator=(LexerToken const &rhs)
{
	*this = rhs;
	return (*this);
}

LexerToken::~LexerToken()
{}
