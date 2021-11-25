#ifndef ELEXERTOKENTYPE_HPP
# define ELEXERTOKENTYPE_HPP

typedef	enum lexerTokenType
{
	eLexerSeparator = 6,
	eLexerEndOfInput,
	eLexerOperatorPush,
	eLexerOperatorPop,
	eLexerOperatorDump,
	eLexerOperatorAssert,
	eLexerOperatorAdd,
	eLexerOperatorSub,
	eLexerOperatorMul,
	eLexerOperatorDiv,
	eLexerOperatorMod,
	eLexerOperatorPrint,
	eLexerOperatorExit,
	eLexerNumberTypeInt8,
	eLexerNumberTypeInt16,
	eLexerNumberTypeInt32,
	eLexerNumberTypeFloat,
	eLexerNumberTypeDouble,
	eLexerNumericalFloat,
	eLexerNumericalInt,
	eLexerOpenParenthesis,
	eLexerCloseParenthesis,
	eLexerUnknownToken
}		eLexerTokenType;

#endif
