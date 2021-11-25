#ifndef OPERAND_HPP
# define OPERAND_HPP

# include <eOperandType.hpp>
# include <IOperand.hpp>
# include <limits>
# include <stdexcept>

template<typename T>
class	Operand : public IOperand
{
public:
	Operand<T>(T value);
	Operand<T>(Operand<T> const &o);
	Operand<T>	&operator=(const Operand<T> &rhs);

	virtual	~Operand<T>(void);

	virtual	int				getPrecision(void) const;
	virtual	eOperandType	getType(void) const;

	virtual	IOperand const	*operator+(IOperand const &rhs) const;
	virtual	IOperand const	*operator-(IOperand const &rhs) const;
	virtual	IOperand const	*operator*(IOperand const &rhs) const;
	virtual	IOperand const	*operator/(IOperand const &rhs) const;
	virtual	IOperand const	*operator%(IOperand const &rhs) const;

	virtual std::string const	&toString(void) const;

	T		getValue(void) const;

private:
	T				getIOperandValue(IOperand const &i) const;
	const IOperand	*adaptType(eOperandType t) const;

	T		_value;
};

std::ostream	&operator<<(std::ostream &o, const IOperand &rhs);
std::ostream	&operator<<(std::ostream &o, const IOperand *rhs);

typedef		Operand<char>	Int8;
typedef		Operand<short>	Int16;
typedef		Operand<int>	Int32;
typedef		Operand<float>	Float;
typedef		Operand<double>	Double;

#endif
