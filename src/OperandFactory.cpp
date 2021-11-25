#include <OperandFactory.hpp>

OperandFactory::OperandFactory() {}
OperandFactory::~OperandFactory() {}

OperandFactory::OperandFactory(OperandFactory const &f)
{
	*this = f;
}

OperandFactory	&OperandFactory::operator=(OperandFactory const &rhs)
{
	return (*new OperandFactory(rhs));
}

std::map<eOperandType, OperandFactory::createOperandFunc>
	OperandFactory::_map = OperandFactory::createMap();

std::map<eOperandType, OperandFactory::createOperandFunc>
OperandFactory::createMap()
{
	std::map<eOperandType, createOperandFunc>	map;

	map[eInt8] = &OperandFactory::createInt8;
	map[eInt16] = &OperandFactory::createInt16;
	map[eInt32] = &OperandFactory::createInt32;
	map[eFloat] = &OperandFactory::createFloat;
	map[eDouble] = &OperandFactory::createDouble;

	return map;
}

IOperand const	*OperandFactory::createInt8(std::string const &value) const
{
	int	i = stoi(value, nullptr, 10);
	if (i > std::numeric_limits<char>::max()
			|| i < std::numeric_limits<char>::min())
		throw std::out_of_range("Int8 initialized with value out of range");
	return (new Int8(i));
}

IOperand const	*OperandFactory::createInt16(std::string const &value) const
{
	int	i = stoi(value, nullptr, 10);
	if (i > std::numeric_limits<short>::max() || i < std::numeric_limits<short>::min())
		throw std::out_of_range("Int16 initialized with value out of range");
	return (new Int16(i));
}

IOperand const	*OperandFactory::createInt32(std::string const &value) const
{
	int	i = stoi(value, nullptr, 10);
	return (new Int32(i));
}

IOperand const	*OperandFactory::createFloat(std::string const &value) const
{
	float f = stof(value, nullptr);
	if (f == std::numeric_limits<float>::infinity()
			|| f == -std::numeric_limits<float>::infinity())
		throw std::out_of_range("inf not supported");
	if (std::isnan(f))
		throw std::out_of_range("nan not suported");
	return (new Float(f));
}

IOperand const	*OperandFactory::createDouble(std::string const &value) const
{
	double d = stod(value, nullptr);
	if (d == std::numeric_limits<double>::infinity()
			|| d == -std::numeric_limits<double>::infinity())
		throw std::out_of_range("inf not supported");
	if (std::isnan(d))
		throw std::out_of_range("nan not supported");
	return (new Double(d));
}

IOperand const	*OperandFactory::createOperand
	(eOperandType type, std::string const &value) const
{
	return (this->*_map[type])(value);
}
