#include <FloatingPointException.hpp>

FloatingPointException::FloatingPointException() : _msg("FloatingPointException") {};
FloatingPointException::FloatingPointException(const char *msg) : _msg(msg) {};

FloatingPointException::FloatingPointException(const FloatingPointException &e)
{
	*this = e;
}

FloatingPointException	&FloatingPointException::operator=
	(const FloatingPointException &rhs)
{
	*this = rhs;
	return (*this);
}

FloatingPointException::~FloatingPointException() throw() {};

const char	*FloatingPointException::what() const throw()
{
	return (this->_msg);
};

