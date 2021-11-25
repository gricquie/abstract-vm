#include <Stack.hpp>
#include <stdexcept>

Stack::Stack(void) {};

Stack::Stack(Stack const &s)
{
	this->stack = s.stack;
}

Stack	&Stack::operator=(Stack const &rhs)
{
	*this = rhs;
	return (*this);
}

Stack::~Stack(void) {};

void		Stack::push(const IOperand *o)
{
	stack.push_back(o);
}

const IOperand	*Stack::pop(void)
{
	const IOperand	*l;

	if (stack.size() == 0)
		throw (std::out_of_range("pop on empty stack"));
	l = stack.back();
	stack.pop_back();
	return (l);
}
