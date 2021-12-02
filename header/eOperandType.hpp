#ifndef EOPERANDTYPE_HPP
# define EOPERANDTYPE_HPP

# include <map>
# include <string>

typedef	enum operandType
{
	eUnknownOperandType = 0,
	eInt8,
	eInt16,
	eInt32,
	eFloat,
	eDouble
}		eOperandType;

extern std::map<eOperandType, std::string>	operandTypeLiteralMap;

#endif
