#ifndef INSTR_HPP
# define INSTR_HPP

# include <IOperand.hpp>
# include <Stack.hpp>

class	Instr
{
public:
	Instr(void (Instr::*f)(Stack &, const IOperand*) const);
	Instr(void (Instr::*f)(Stack &, const IOperand*) const, const IOperand *o);
	Instr(Instr const &i);
	Instr	&operator=(Instr const &rhs);

	~Instr(void);

	void	execute(Stack &s) const;

	typedef	void (Instr::*execF)(Stack &, const IOperand *) const;
	
	void	push(Stack &s, const IOperand* o) const;
	void	pop(Stack &s, const IOperand* o) const;
	void	dump(Stack &s, const IOperand* o) const;
	void	assert(Stack &s, const IOperand* o) const;
	void	add(Stack &s, const IOperand* o) const;
	void	sub(Stack &s, const IOperand* o) const;
	void	mul(Stack &s, const IOperand* o) const;
	void	div(Stack &s, const IOperand* o) const;
	void	mod(Stack &s, const IOperand* o) const;
	void	print(Stack &s, const IOperand* o) const;
	void	exit(Stack &s, const IOperand* o) const;

private:
	void			(Instr::*execFunc)(Stack &, const IOperand *) const;
	const IOperand	*operand;
};

#endif
