#include <Instr.hpp>
#include <iostream>
#include <algorithm>

Instr::Instr(void (Instr::*f)(Stack &, const IOperand*) const) :
		execFunc(f), operand(nullptr) {}
Instr::Instr(void (Instr::*f)(Stack &, const IOperand*) const,
		const IOperand *o) :
		execFunc(f), operand(o) {}

Instr::Instr(Instr const &i)
{
	execFunc = i.execFunc;
	operand = i.operand;
}

Instr	&Instr::operator=(Instr const &rhs)
{
	*this = rhs;
	return (*this);
}

Instr::~Instr(void) {}

void	Instr::execute(Stack &s) const
{
	(this->*this->execFunc)(s, operand);
}

void	Instr::push(Stack &s, const IOperand *o) const
{
	s.push(o);
}

void	Instr::pop(Stack &s, const IOperand *o) const
{
	(void)o;
	s.pop();
}

void	Instr::dump(Stack &s, const IOperand *o) const
{
	(void)o;

	for_each(s.stack.rbegin(), s.stack.rend(), [](const IOperand *o){
		std::cout << operandTypeLiteralMap[o->getType()] << " : " << o->toString() << std::endl;
	});
}
void	Instr::assert(Stack &s, const IOperand *o) const
{
	std::cout << "assert not immplemented\n";
	(void)s;
	(void)o;
}

void	Instr::add(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first;

	first = s.pop();
	s.push(*first + *s.pop());
}

void	Instr::sub(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first;

	first = s.pop();
	s.push(*first - *s.pop());
}
void	Instr::mul(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first;

	first = s.pop();
	s.push(*first * *s.pop());
}

void	Instr::div(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first;

	first = s.pop();
	s.push(*first / *s.pop());
}

void	Instr::mod(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first;

	first = s.pop();
	s.push(*first % *s.pop());
}

void	Instr::print(Stack &s, const IOperand *o) const
{
	std::cout << "print not immplemented\n";
	(void)s;
	(void)o;
}

void	Instr::exit(Stack &s, const IOperand *o) const
{
	std::cout << "exit not immplemented\n";
	(void)s;
	(void)o;
}
