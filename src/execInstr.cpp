#include <execInstr.hpp>
#include <Stack.hpp>
#include <algorithm>

bool	execInstr(std::vector<Instr> v)
{
	Stack	s;

	for (const Instr i : v)
	{
		if (i.execute(s))
			return (true);
	};
	return (false);
}