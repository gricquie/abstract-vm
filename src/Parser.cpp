#include <Parser.hpp>
#include <map>

std::map<eLexerTokenType, Instr::execF>	execFuncMap =
{
	{eLexerOperatorPush, &Instr::push},
	{eLexerOperatorPop, &Instr::pop},
	{eLexerOperatorDump, &Instr::dump},
	{eLexerOperatorAssert, &Instr::assert},
	{eLexerOperatorAdd, &Instr::add},
	{eLexerOperatorSub, &Instr::sub},
	{eLexerOperatorMul, &Instr::mul},
	{eLexerOperatorDiv, &Instr::div},
	{eLexerOperatorMod, &Instr::mod},
	{eLexerOperatorPrint, &Instr::print},
	{eLexerOperatorExit, &Instr::exit},
	{eLexerUnknownToken, nullptr}
};

Parser::Parser(std::vector<LexerToken> tokens) : tokens(tokens)
{
	pos = 0;
	line = 1;
	has_error = 0;
	state = &Parser::parseIdentifier;
	error = "";
	currF = nullptr;
	currT = eLexerUnknownToken;
	currO = nullptr;
}

Parser::Parser(Parser const &p)
{
	this->tokens = p.tokens;
	this->pos = p.pos;
	this->line = p.line;
	this->has_error = p.has_error;
	this->state = p.state;
	this->error = p.error;
	this->currF = p.currF;
	this->currT = p.currT;
	this->currO = p.currO;
}

Parser	&Parser::operator=(Parser const &rhs)
{
	*this = rhs;
	return (*this);
}

Parser::~Parser(void) {}

std::vector<Instr>	Parser::getInstr(void)
{
	run();
	if (has_error)
		throw new std::exception;
	return (instrs);
}

void		Parser::run()
{
	while (state != nullptr)
	{
		(this->*state)();
	}
}

void		Parser::addInstr(Instr::execF f, const IOperand *o)
{
	Instr	i(f, o);
	instrs.push_back(i);
}

LexerToken	Parser::next(void)
{
	if (pos >= tokens.size())
		return (LexerToken(eLexerEndOfInput, "", line));
	LexerToken	t = tokens.at(pos);
	pos++;
	return (t);
}

LexerToken	Parser::peek(void)
{
	if (pos >= tokens.size())
		return (LexerToken(eLexerEndOfInput, "", line));
	return (tokens.at(pos));
}

Instr::execF	Parser::getExecFunc(eLexerTokenType t)
{
	if (t < eLexerOperatorPush || t > eLexerOperatorExit)
		return (nullptr);
	return (execFuncMap[t]);
}

void	Parser::stateError(void)
{
	std::cout << "bad Syntax line " << line << " : " << error << std::endl;
	while (peek().type != eLexerSeparator && peek().type != eLexerEndOfInput)
		next();
	state = &Parser::parseIdentifier;
	has_error = true;
}

void	Parser::parseIdentifier(void)
{
	auto	t = next();

	if (t.type == eLexerEndOfInput)
	{
		state = nullptr;
		return ;
	}
	if (t.type < eLexerOperatorPush || t.type > eLexerOperatorExit)
	{
		state = &Parser::stateError;
		error = "expected operand";
		return ;
	}
	currF = getExecFunc(t.type);
	if (t.type == eLexerOperatorPush || t.type == eLexerOperatorAssert)
		state = &Parser::parseType;
	else
		state = &Parser::parseSeparator;
}

void	Parser::parseType(void)
{
	auto	t = next();
	
	if (t.type < eLexerNumberTypeInt8 || t.type > eLexerNumberTypeDouble)
	{
		state = &Parser::stateError;
		error = "expected type";
		return ;
	}
	currT = t.type;
	state = &Parser::parseLeftParen;
}

void	Parser::parseLeftParen(void)
{
	auto	t = next();

	if (t.type != eLexerOpenParenthesis)
	{
		state = &Parser::stateError;
		error = "expected '('";
		return ;
	}
	state = &Parser::parseInside;
}

void	Parser::parseInside(void)
{
	auto	t = next();

	if (currT < eLexerNumberTypeFloat && t.type == eLexerNumericalFloat)
	{
		state = &Parser::stateError;
		error = "expected integer, got float";
		return ;
	}
	if (currT >= eLexerNumberTypeFloat && t.type != eLexerNumericalFloat)
	{
		state = &Parser::stateError;
		error = "expected float, got integer";
		return ;
	}
	try
	{
		int		ot = currT - eLexerNumberTypeInt8 + eInt8;
		currO = factory.createOperand((eOperandType)ot, t.s);
		state = &Parser::parseRightParen;
	}
	catch (std::out_of_range &e)
	{
		state = &Parser::stateError;
		error = "numerical number is too large for given type";
	}
}

void	Parser::parseRightParen(void)
{
	auto	t = next();

	if (t.type != eLexerCloseParenthesis)
	{
		state = &Parser::stateError;
		error = "expected ')'";
		return ;
	}
	state = &Parser::parseSeparator;
}

void	Parser::parseSeparator(void)
{
	auto	t = next();
	if (t.type != eLexerSeparator && t.type != eLexerEndOfInput)
	{
		state = &Parser::stateError;
		error = "expected newline or end of input";
		return ;
	}
	if (t.type == eLexerEndOfInput)
		state = nullptr;
	else
		state = &Parser::parseIdentifier;
	addInstr(currF, currO);
	currF = nullptr;
	currT = eLexerUnknownToken;
	currO = nullptr;
	line = peek().line;
}
