#include <AssertException.hpp>

AssertException::AssertException() : _msg("AssertException") {};
AssertException::AssertException(const char *msg) : _msg(msg) {};

AssertException::AssertException(const AssertException &e)
{
	*this = e;
}

AssertException	&AssertException::operator=
	(const AssertException &rhs)
{
	*this = rhs;
	return (*this);
}

AssertException::~AssertException() throw() {};

const char	*AssertException::what() const throw()
{
	return (this->_msg);
};

