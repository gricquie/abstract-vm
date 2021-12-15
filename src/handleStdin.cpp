#include <handleStdin.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <execInstr.hpp>
#include <stack.hpp>
#include <AssertException.hpp>
#include <iostream>
#include <string>
#include <vector>

int		handleStdin(void)
{
	std::string	input;
	int			ret = EXIT_FAILURE;
	Stack		s;

	while (std::cin && ret == EXIT_FAILURE)
	{
		std::cout << "> ";
		getline(std::cin, input);
		try
		{
			Lexer	l(input);
			Parser	p(l.getTokens());
			for (const Instr i : p.getInstr())
			{
				if (i.execute(s))
					ret = EXIT_SUCCESS;
			}
		}
		catch (std::range_error &e)
		{
			continue ;
		}
		catch (AssertException &e)
		{
			std::cout << e.what() << std::endl;
			continue ;
		}
		catch (std::out_of_range &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	if (ret == EXIT_FAILURE)
		throw std::range_error("no exit instr");
	return (ret);
}