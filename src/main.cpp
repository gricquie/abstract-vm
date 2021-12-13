#include <abstract-vm.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	try
	{
		Lexer					l("push Int8(42)\nprint\nexit");
		std::vector<LexerToken>	t = l.getTokens();
		Parser					p(t);
		std::vector<Instr>		is = p.getInstr();

		if (!execInstr(is))
			throw std::range_error("no exit"); // exit error
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
