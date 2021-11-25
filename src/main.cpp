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
		Lexer					l("push Int8(54)\n pop");
		std::vector<LexerToken>	t = l.getTokens();
		
		for_each(t.begin(), t.end(), [](const LexerToken &t){
			std::cout << t.type << " => " << t.s << std::endl;
		});
	
		Parser					p(t);
		std::vector<Instr>		is = p.getInstr();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
