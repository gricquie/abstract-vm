#include <Operand.hpp>
#include <iostream>
#include <FloatingPointException.hpp>

std::map<eOperandType, std::string>	operandTypeLiteralMap = {
	{eUnknownOperandType, "unknown"},
	{eInt8, "Int8"},
	{eInt16, "Int16"},
	{eInt32, "Int32"},
	{eFloat, "Float"},
	{eDouble, "Double"}
};

template<typename T>
Operand<T>::Operand(T value) : _value(value) {}

template<typename T>
Operand<T>::Operand(Operand<T> const &o)
{
	*this = o;
}

template<typename T>
Operand<T>	&Operand<T>::operator=(const Operand<T> &rhs)
{
	*this = rhs;
	return (*this);
}

template<typename T>
Operand<T>::~Operand() {}

template<typename T>
T		Operand<T>::getValue(void) const
{
	return (this->_value);
}

template<typename T>
int		Operand<T>::getPrecision(void) const
{
	return (sizeof(T));
}

template<>
eOperandType	Operand<char>::getType(void) const
{
	return (eInt8);
}

template<>
eOperandType	Operand<short>::getType(void) const
{
	return (eInt16);
}

template<>
eOperandType	Operand<int>::getType(void) const
{
	return (eInt32);
}

template<>
eOperandType	Operand<float>::getType(void) const
{
	return (eFloat);
}

template<>
eOperandType	Operand<double>::getType(void) const
{
	return (eDouble);
}

template<typename T>
T				Operand<T>::getIOperandValue(IOperand const &rhs) const
{
	switch	(rhs.getType())
	{
		case eUnknownOperandType:
			return (0);
		case eInt8:
			return (reinterpret_cast<const Int8 &>(rhs).getValue());
		case eInt16:
			return (reinterpret_cast<const Int16 &>(rhs).getValue());
		case eInt32:
			return (reinterpret_cast<const Int32 &>(rhs).getValue());
		case eFloat:
			return (reinterpret_cast<const Float &>(rhs).getValue());
		case eDouble:
			return (reinterpret_cast<const Double &>(rhs).getValue());
	}
	return (0);
}

template<typename T>
const IOperand 	*Operand<T>::adaptType(eOperandType t) const
{
	switch	(t)
	{
		case eUnknownOperandType:
			return (0);
		case eInt8:
			return (new Int8(this->_value));
		case eInt16:
			return (new Int16(this->_value));
		case eInt32:
			return (new Int32(this->_value));
		case eFloat:
			return (new Float(this->_value));
		case eDouble:
			return (new Double(this->_value));
	}
	return (nullptr);
}

template<typename T>
IOperand const	*Operand<T>::operator+(IOperand const &rhs) const
{
	if (this->getType() < rhs.getType())
		return (*this->adaptType(rhs.getType()) + rhs);

	const T		v = this->getIOperandValue(rhs);
	const T		k = this->_value + v;

	if (std::numeric_limits<T>::has_infinity)
	{
		if (k == std::numeric_limits<T>::infinity())
			throw std::overflow_error
				("adding two operands results in overflow");
		else if (k == -std::numeric_limits<T>::infinity())
			throw std::underflow_error
				("adding two operands results in underflow");
	}
	if (this->_value < 0 && v < 0 && v < k)
		throw std::underflow_error("adding two operand results in underflow");
	if (this->_value > 0 && v > 0 && v > k)
		throw std::overflow_error("adding two operand results in overflow");
	return (new Operand<T>(k));
}

template<typename T>
IOperand const	*Operand<T>::operator-(IOperand const &rhs) const
{
	if (this->getType() < rhs.getType())
		return (*this->adaptType(rhs.getType()) - rhs);

	const T				v = this->getIOperandValue(rhs);
	const T				k = this->_value - v;

	if (std::numeric_limits<T>::has_infinity)
	{
		if (k == std::numeric_limits<T>::infinity())
			throw std::overflow_error
				("subbing two operands results in overflow");
		else if (k == -std::numeric_limits<T>::infinity())
			throw std::underflow_error
				("subbing two operands results in underflow");
	}
	if (this->_value < 0 && v > 0 && this->_value < k)
		throw std::underflow_error("subbing two operand results in underflow");
	if (this->_value > 0 && v < 0 && this->_value > k)
		throw std::overflow_error("subbing two operand results in overflow");
	return (new Operand<T>(k));
}

template<typename T>
IOperand const	*Operand<T>::operator*(IOperand const &rhs) const
{
	if (this->getType() < rhs.getType())
		return (*this->adaptType(rhs.getType()) * rhs);

	const T		v = this->getIOperandValue(rhs);
	const T		k = this->_value * v;

	if (std::numeric_limits<T>::has_infinity)
	{
		if (k == std::numeric_limits<T>::infinity())
			throw std::overflow_error
				("multiplying two operands results in overflow");
		else if (k == -std::numeric_limits<T>::infinity())
			throw std::underflow_error
				("multiplying two operands results in underflow");
	}
	else if (v != 0 && k / v != this->_value)
	{
		if ((v < 0 && this->_value < 0) || (v > 0 && this->_value > 0))
			throw std::overflow_error
				("multiplying two operands results in overflow");
		else
			throw std::underflow_error
				("multiplying two operands results in underflow");
	}

	return (new Operand<T>(k));
}

template<typename T>
IOperand const	*Operand<T>::operator/(IOperand const &rhs) const
{
	if (this->getType() < rhs.getType())
		return (*this->adaptType(rhs.getType()) / rhs);
	
	const T		v = this->getIOperandValue(rhs);

	if	(v == 0)
		throw FloatingPointException("division by 0");
	const T		k = this->_value / v;
	if (std::numeric_limits<T>::has_infinity)
	{
		if (k == std::numeric_limits<T>::infinity())
			throw std::overflow_error
				("dividing two operands results in overflow");
		else if (k == -std::numeric_limits<T>::infinity())
			throw std::underflow_error
				("diiding two operands results in underflow");
	}
	return (new Operand<T>(k));
}

template<typename T>
IOperand const	*Operand<T>::operator%(IOperand const &rhs) const
{
	if (this->getType() < rhs.getType())
		return (*this->adaptType(rhs.getType()) % rhs);

	const T		v = this->getIOperandValue(rhs);

	if (v == 0)
		throw FloatingPointException("modulo by 0");
	return (new Operand<T>(this->_value % v));
}

template<>
IOperand const	*Operand<float>::operator%(IOperand const &rhs) const
{
	(void)rhs;
	throw FloatingPointException("impossible operator on floating point number");
}

template<>
IOperand const	*Operand<double>::operator%(IOperand const &rhs) const
{
	(void)rhs;
	throw FloatingPointException("impossible operator on floating point number");
}

template<typename T>
std::string const	&Operand<T>::toString(void) const
{
	return (*(new std::string(std::to_string(this->_value))));
}

std::ostream	&operator<<(std::ostream &o, const IOperand &rhs)
{
	o << rhs.toString();
	return (o);
}

std::ostream	&operator<<(std::ostream &o, const IOperand *rhs)
{
	o << rhs->toString();
	return (o);
}

template class Operand<char>;
template class Operand<short>;
template class Operand<int>;
template class Operand<float>;
template class Operand<double>;
