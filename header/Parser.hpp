#ifndef PARSER_HPP
# define PARSER_HPP

# include <Lexer.hpp>
# include <LexerToken.hpp>
# include <eLexerTokenType.hpp>
# include <Instr.hpp>
# include <OperandFactory.hpp>
# include <vector>
# include <string>
# include <iostream>

class	Parser
{
public:
	Parser(std::vector<LexerToken>);
	Parser(Parser const &p);
	Parser	&operator=(Parser const &rhs);

	~Parser(void);

	std::vector<Instr>	getInstr(void);

private:
	typedef void	(Parser::*parserState)(void);

	std::vector<LexerToken>	tokens;
	OperandFactory			factory;
	size_t					pos;
	size_t					line;

	Instr::execF			currF;
	eLexerTokenType			currT;
	const IOperand			*currO;

	parserState				state;
	std::string				error;
	std::vector<Instr>		instrs;

	void		run(void);
	void		addInstr(Instr::execF f, const IOperand *o);
	LexerToken	next(void);
	LexerToken	peek(void);
	Instr::execF	getExecFunc(eLexerTokenType t);

	void	parseIdentifier(void);
	void	parseType(void);
	void	parseLeftParen(void);
	void	parseInside(void);
	void	parseRightParen(void);
	void	parseSeparator(void);
	void	stateError(void);
};

#endif
