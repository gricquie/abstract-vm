#ifndef ASSERTEXCEPTION_HPP
# define ASSERTEXCEPTION_HPP

# include <exception>

class	AssertException : public std::exception
{
public:
	AssertException();
	AssertException(const char *msg);
	AssertException(const AssertException &e);
	AssertException	&operator=(const AssertException &rhs);

	virtual ~AssertException();

	virtual const char	*what() const throw();

private:
	const char	*_msg;
};

#endif
