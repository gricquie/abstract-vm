#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <string>
# include <LexerToken.hpp>
# include <eLexerTokenType.hpp>

class	Lexer
{
public:
	Lexer(std::string source);
	Lexer(Lexer const &l);
	Lexer	&operator=(Lexer const &rhs);

	~Lexer(void);

	std::vector<LexerToken>	getTokens(void);

private:
	typedef	void	(Lexer::*stateFunc)(void);

	std::string				input;
	size_t					start;
	size_t					pos;
	unsigned int			line;

	stateFunc				state;
	std::string				error;
	bool					has_error;
	std::vector<LexerToken>	tokens;

	void	addToken(eLexerTokenType t);
	char	next(void);
	char	peek(void);
	void	ignore(void);
	void	backup(void);
	bool	contains(std::string valid, char c);
	bool	accept(std::string valid);
	eLexerTokenType	classify(void);

	void			run(void);
	void			lexText(void);
	void			lexAlphanum(void);
	void			lexNumber(void);
	void			lexLeftParen(void);
	void			lexRightParen(void);
	void			lexNewline(void);
	void			lexSemiColumn(void);
	void			stateError(void);
};

#endif
