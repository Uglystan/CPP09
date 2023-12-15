#include "RPN.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc == 2)
		{
			RPN rpn(argv[1]);
		}
		else
			std::cout << "Invalid number argument" << std::endl;
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}