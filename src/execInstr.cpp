#include <execInstr.hpp>
#include <Stack.hpp>
#include <algorithm>

void	execInstr(std::vector<Instr> v)
{
	Stack	s;

	for_each(v.begin(), v.end(), [&s](const Instr &i){
			i.execute(s);
		});
}