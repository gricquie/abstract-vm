#ifndef LEXERTOKEN_HPP
# define LEXERTOKEN_HPP

# include <eLexerTokenType.hpp>
# include <IOperand.hpp>
# include <string>

class	LexerToken
{
public:
	LexerToken(eLexerTokenType type, std::string s, unsigned int l);
	LexerToken(eLexerTokenType type, std::string s,
			unsigned int l, IOperand *o);
	LexerToken(LexerToken const &t);
	LexerToken	&operator=(LexerToken const &rhs);

	virtual	~LexerToken(void);
	
	eLexerTokenType	type;
	std::string		s;
	unsigned int	line;
	IOperand		*o;
};

#endif
