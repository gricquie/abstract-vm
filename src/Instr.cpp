#include <Instr.hpp>
#include <AssertException.hpp>
#include <Operand.hpp>
#include <iostream>
#include <algorithm>

Instr::Instr(bool (Instr::*f)(Stack &, const IOperand*) const) :
		execFunc(f), operand(nullptr) {}
Instr::Instr(bool (Instr::*f)(Stack &, const IOperand*) const,
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

bool	Instr::execute(Stack &s) const
{
	return ((this->*this->execFunc)(s, operand));
}

bool	Instr::push(Stack &s, const IOperand *o) const
{
	s.push(o);
	return (false);
}

bool	Instr::pop(Stack &s, const IOperand *o) const
{
	(void)o;
	s.pop();
	return (false);
}

bool	Instr::dump(Stack &s, const IOperand *o) const
{
	(void)o;

	for_each(s.stack.rbegin(), s.stack.rend(), [](const IOperand *o){
		std::cout << operandTypeLiteralMap[o->getType()] << " : " << o->toString() << std::endl;
	});
	return (false);
}
bool	Instr::assert(Stack &s, const IOperand *o) const
{
	const IOperand *top = s.pop();

	s.push(top);
	if (top->getType() != o->getType())
		throw AssertException("assert exception");
	else if (top->toString() != o->toString())
		throw AssertException("assert exception");
	return (false);
}

bool	Instr::add(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first = s.pop();
	const IOperand	*sec = s.pop();

	s.push(*sec + *first);
	delete first;
	delete sec;
	return (false);
}

bool	Instr::sub(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first = s.pop();
	const IOperand	*sec = s.pop();

	s.push(*sec - *first);
	delete first;
	delete sec;
	return (false);
}

bool	Instr::mul(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first = s.pop();
	const IOperand	*sec = s.pop();

	s.push(*sec * *first);
	delete first;
	delete sec;
	return (false);
}

bool	Instr::div(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first = s.pop();
	const IOperand	*sec = s.pop();

	s.push(*sec / *first);
	delete first;
	delete sec;
	return (false);
}

bool	Instr::mod(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*first = s.pop();
	const IOperand	*sec = s.pop();

	s.push(*sec % *first);
	delete first;
	delete sec;
	return (false);
}

bool	Instr::print(Stack &s, const IOperand *o) const
{
	(void)o;
	const IOperand	*top = s.pop();

	s.push(top);
	if (top->getType() != eInt8)
		throw AssertException("not and Int8 on top");
	const Int8	*c = reinterpret_cast<const Int8 *>(top);
	std::cout << (char)c->getValue();
	return (false);
}

bool	Instr::exit(Stack &s, const IOperand *o) const
{
	(void)s;
	(void)o;
	return (true);
}
