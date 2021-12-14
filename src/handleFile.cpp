#include <handleFile.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>
#include <execInstr.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include <iostream>
#include <algorithm>

int		handleFile(std::string filename)
{
	std::ifstream	file;
	file.open(filename);
	if (!file.is_open())
	{
		std::cout << "unable to open file" << std::endl;
		return (EXIT_FAILURE);
	}
	file.seekg(0, std::ios::end);
	int size = file.tellg();
	std::string	input(size, 0);
	file.seekg(0);
	file.read(&input[0], size - 1);
	file.close();

	Lexer					l(input);
	std::vector<LexerToken> t = l.getTokens();
	Parser					p(t);
	std::vector<Instr>		is = p.getInstr();

	if (!execInstr(is))
		throw std::range_error("no exit instr");
}