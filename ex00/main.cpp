#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	try
	{
		if (argc == 2)
		{
			BitcoinExchange test(argv[1]);
		}
		else
			std::cout << "Invalid number argument" << std::endl;
	}
	catch (std::exception const& error)
	{
		std::cout << error.what() << std::endl;
		return (1);
	}
	return (0);
}