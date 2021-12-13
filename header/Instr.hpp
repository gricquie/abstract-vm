#ifndef INSTR_HPP
# define INSTR_HPP

# include <IOperand.hpp>
# include <Stack.hpp>

class	Instr
{
public:
	Instr(bool (Instr::*f)(Stack &, const IOperand*) const);
	Instr(bool (Instr::*f)(Stack &, const IOperand*) const, const IOperand *o);
	Instr(Instr const &i);
	Instr	&operator=(Instr const &rhs);

	~Instr(void);

	bool	execute(Stack &s) const;

	typedef	bool (Instr::*execF)(Stack &, const IOperand *) const;
	
	bool	push(Stack &s, const IOperand* o) const;
	bool	pop(Stack &s, const IOperand* o) const;
	bool	dump(Stack &s, const IOperand* o) const;
	bool	assert(Stack &s, const IOperand* o) const;
	bool	add(Stack &s, const IOperand* o) const;
	bool	sub(Stack &s, const IOperand* o) const;
	bool	mul(Stack &s, const IOperand* o) const;
	bool	div(Stack &s, const IOperand* o) const;
	bool	mod(Stack &s, const IOperand* o) const;
	bool	print(Stack &s, const IOperand* o) const;
	bool	exit(Stack &s, const IOperand* o) const;

private:
	bool			(Instr::*execFunc)(Stack &, const IOperand *) const;
	const IOperand	*operand;
};

#endif
