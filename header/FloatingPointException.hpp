#ifndef FLOATINGPOINTEXCEPTION_HPP
# define FLOATINGPOINTEXCEPTION_HPP

# include <exception>

class	FloatingPointException : public std::exception
{
public:
	FloatingPointException();
	FloatingPointException(const char *msg);
	FloatingPointException(const FloatingPointException &e);
	FloatingPointException	&operator=(const FloatingPointException &rhs);

	virtual ~FloatingPointException();

	virtual const char	*what() const throw();

private:
	const char	*_msg;
};

#endif
