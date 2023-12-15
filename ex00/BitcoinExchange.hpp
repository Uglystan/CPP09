#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <exception>

class	BitcoinExchange
{
	public:
		BitcoinExchange(std::string fileName);
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const& substitue);
		BitcoinExchange const& operator=(BitcoinExchange const& substitue);
		void fillData(std::string fileName);
		void fillInput(std::string fileName);

	private:
		std::multimap<std::string, double> _data;
};

class	cantOpenFile : public std::exception
{
	public :
		const char*	what() const throw();
};

class	emptyFile : public std::exception
{
	public :
		const char*	what() const throw();
};

class	tooLargeNbr : public std::exception
{
	public :
		const char*	what() const throw();
};

class	negativeNbr : public std::exception
{
	public :
		const char*	what() const throw();
};

class	formatErrorCsvFile : public std::exception
{
	public :
		const char*	what() const throw();
};