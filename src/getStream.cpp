#include <getStream.hpp>

std::istream	*getStream(int argc, char **argv)
{
	if (argc == 1)
		return (&std::cin);
	if (argc > 2)
		return (nullptr);
	std::ifstream	*is = new std::ifstream(argv[1], std::ios::binary);
	if (!is->is_open())
		throw	std::exception();
	return (is);
}
