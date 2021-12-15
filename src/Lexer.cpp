#include <Lexer.hpp>
#include <map>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cctype>

std::map<std::string, eLexerTokenType> lexerTokensMap =
{
	{"push", eLexerOperatorPush},
	{"pop", eLexerOperatorPop},
	{"dump", eLexerOperatorDump},
	{"assert", eLexerOperatorAssert},
	{"add", eLexerOperatorAdd},
	{"sub", eLexerOperatorSub},
	{"mul", eLexerOperatorMul},
	{"div", eLexerOperatorDiv},
	{"mod", eLexerOperatorMod},
	{"print", eLexerOperatorPrint},
	{"exit", eLexerOperatorExit},
	{"Int8", eLexerNumberTypeInt8},
	{"Int16", eLexerNumberTypeInt16},
	{"Int32", eLexerNumberTypeInt32},
	{"Float", eLexerNumberTypeFloat},
	{"Double", eLexerNumberTypeDouble}
};

Lexer::Lexer(std::string source) : input(source), start(0), pos(0),
						line(1), state(&Lexer::lexText), has_error(false) {}

Lexer::Lexer(Lexer const &l)
{
	this->input = l.input;
	this->start = l.start;
	this->pos = l.pos;
	this->line = l.line;
	this->state = l.state;
	this->tokens = l.tokens;
}

Lexer::~Lexer(void) {};

Lexer	&Lexer::operator=(Lexer const &rhs)
{
	*this = rhs;
	return (*this);
}

std::vector<LexerToken>	Lexer::getTokens(void)
{
	run();
	if (has_error)
		throw std::range_error("");
	return (tokens);
}

void	Lexer::addToken(eLexerTokenType t)
{
	if (start < input.size())
		this->tokens.push_back(LexerToken(t,
			input.substr(start, pos - start), line));
	start = pos;
}

char	Lexer::next(void)
{
	pos++;
	if (pos > input.size())
	{
		pos--;
		return (0);
	}
	char r = input.at(pos - 1);
	if (r == 0)
		pos--;
	return (r);
}

char	Lexer::peek(void)
{
	if (pos >= input.size())
		return (0);
	return (input.at(pos));
}

void	Lexer::ignore(void)
{
	start = pos;
}

void	Lexer::backup(void)
{
	pos--;
}

bool	Lexer::contains(std::string valid, char c)
{
	for (char i : valid)
	{
		if (i == c)
			return (true);
	}
	return (false);
}

bool	Lexer::accept(std::string valid)
{
	if (contains(valid, peek()))
	{
		next();
		return (true);
	}
	return (false);
}

void	Lexer::run(void)
{
	while (state != nullptr)// && pos < input.size())
	{
		while (accept(" "))
			;
		ignore();
		(this->*state)();
	}
	addToken(eLexerEndOfInput);
}

void	Lexer::lexText(void)
{
	while (1)
	{
		if (peek() == ';')
			state = &Lexer::lexSemiColumn;
		if (peek() == '\n' || peek() == '\r')
			state = &Lexer::lexNewline;
		else if (std::isalpha(peek()))
			state = &Lexer::lexAlphanum;
		if (state != &Lexer::lexText)
		{
			if (pos > start)
			{
				addToken(eLexerUnknownToken);
				error = "unknown token ";
				error += input.substr(start, pos - start);
				state = &Lexer::stateError;
				ignore();
			}
			return ;
		}
		if (next() == 0)
			break ;
	}
	if (pos > start)
	{
		addToken(eLexerUnknownToken);
		error = "unknown token ";
		error += input.substr(start, pos - start);
		state = &Lexer::stateError;
		ignore();
	}
	else
		state = nullptr;
}

eLexerTokenType	Lexer::classify(void)
{
	std::string	s = input.substr(start, pos - start);
	if (lexerTokensMap[s])
		return (lexerTokensMap[s]);
	return (eLexerUnknownToken);
}

void	Lexer::lexAlphanum(void)
{
	std::string	alnum = "ABCDEFGHIJKLMNOPQURSTUVWXYZ"
						"abcdefghijklmnopqurstuvwxyz0123456789";
	while (accept(alnum))
		;
	accept(alnum);
	eLexerTokenType t = classify();
	if (t >= eLexerNumberTypeInt8 && t <= eLexerNumberTypeDouble)
		state = &Lexer::lexLeftParen;
	else if (t != eLexerUnknownToken)
		state = &Lexer::lexText;
	else
	{
		error = "unknown identifier : ";
		error += input.substr(start, pos - start);
		state = &Lexer::stateError;
		ignore();
		return ;
	}
	addToken(t);
	return ;
}

void	Lexer::lexNumber(void)
{
	std::string	digits = "0123456789";
	bool		isFloat = false;

	accept("+-");
	while (accept(digits))
		;
	if (accept("."))
		isFloat = true;
	while (accept(digits))
		;
	addToken(isFloat ? eLexerNumericalFloat : eLexerNumericalInt);
	state = &Lexer::lexRightParen;
}

void	Lexer::lexLeftParen(void)
{
	if (!accept("("))
	{
		error = "open parenthesis expected";
		state = &Lexer::stateError;
		return ;
	}
	addToken(eLexerOpenParenthesis);
	state = &Lexer::lexNumber;
}

void	Lexer::lexRightParen(void)
{
	if (!accept(")"))
	{
		error = "closed parenthesis expected";
		state = &Lexer::stateError;
		return;
	}
	addToken(eLexerCloseParenthesis);
	state = &Lexer::lexText;
}

void	Lexer::lexNewline(void)
{
	while (accept("\n\r"))
		line++;
	addToken(eLexerSeparator);
	state = &Lexer::lexText;
}

void	Lexer::lexSemiColumn(void)
{
	accept(";");
	if (accept(";"))
	{
		addToken(eLexerEndOfInput);
		state = &Lexer::lexText;
		return ;
	}
	while (peek() != '\n' && peek() != 0)
		next();
	ignore();
	state = &Lexer::lexText;
}

void	Lexer::stateError(void)
{
	has_error = true;
	std::cout << "bad Syntax line " << line << " : " << error << std::endl;
	state = &Lexer::lexText;
}
