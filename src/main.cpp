#include <abstract-vm.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

int		main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cout << "usage : abstract-vm [file]" << std::endl;
		return -1;
	}
	try
	{
//		if (argc == 1)
//			return (handleStdin());
//		else
			return (handleFile(argv[1]));
	}
	catch (std::exception &e)
	{
		std::cout << "exception catched" << std::endl;
		std::cout << e.what() << std::endl;
	}
}