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
		Lexer					l("push Int8(4)\npush Double(3.5)\nsub\n pop");
		std::vector<LexerToken>	t = l.getTokens();
		Parser					p(t);
		std::vector<Instr>		is = p.getInstr();

		execInstr(is);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
