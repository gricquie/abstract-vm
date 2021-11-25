#ifndef STACK_HPP
# define STACK_HPP

# include <IOperand.hpp>
# include <vector>

class	Stack
{
public:
	Stack(void);
	Stack(Stack const &s);
	Stack	&operator=(Stack const &rhs);

	~Stack(void);

	void			push(const IOperand *o);
	const IOperand	*pop(void);

private:
	std::vector<const IOperand*>	stack;
};

#endif
