#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <eOperandType.hpp>
# include <IOperand.hpp>
# include <Operand.hpp>

# include <string>
# include <map>
# include <cmath>

class	OperandFactory
{
public:
	OperandFactory(void);
	OperandFactory(OperandFactory const &f);
	OperandFactory	&operator=(OperandFactory const &rhs);

	~OperandFactory(void);

	IOperand const	*createOperand(eOperandType type, std::string const &value) const;

	typedef	IOperand const *(OperandFactory::*createOperandFunc)
		(std::string const &value) const;

	static std::map<eOperandType, createOperandFunc>	createMap(void);

private:
	static std::map<eOperandType, createOperandFunc>	_map;

	IOperand const	*createInt8(std::string const & value) const;
	IOperand const	*createInt16(std::string const & value) const;
	IOperand const	*createInt32(std::string const & value) const;
	IOperand const	*createFloat(std::string const & value) const;
	IOperand const	*createDouble(std::string const & value) const;
};


#endif
