#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string fileName)
{
	fillData("data.csv");
	fillInput(fileName);
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& substitue)
{
	_data = substitue._data;
}

BitcoinExchange const& BitcoinExchange::operator=(BitcoinExchange const& substitue)
{
	if (this != &substitue)
	{
		_data = substitue._data;
	}
	return (*this);
}

static std::string	test(std::string temp, char delim)
{
	unsigned int i = 0;

	while(temp[i] != delim && i < temp.size())
		i++;
	if (delim == '|')
		i--;
	if (temp.size() == 0)
		return (temp);
	return(temp.substr(0, i));
}

static double	converToDouble(std::string temp, char delim)
{
	unsigned int i = 0;

	while(temp[i] != delim && i < temp.size())
		i++;
	i++;
	if (temp.size() == 0)
		throw formatErrorCsvFile();
	double nbr = atof(temp.substr(i, temp.size() - i).c_str());
	if (nbr < 0)
		throw negativeNbr();
	if (nbr > 2147483647)
		throw tooLargeNbr();
	return (nbr);
}

static double	converToDoubleForInput(std::string temp, char delim)
{
	unsigned int i = 0;

	while(temp[i] != delim && i < temp.size())
		i++;
	i++;
	if (temp.size() == 0)
	{
		std::cout << "Error : bad input" << std::endl;
		return (-1);
	}
	double nbr = atof(temp.substr(i, temp.size() - i).c_str());
	if (nbr < 0)
	{
		std::cout << "Error : not a positive number" << std::endl;
		return (-1);
	}
	if (nbr > 1000)
	{
		std::cout << "Error : too large a number" << std::endl;
		return (-1);
	}
	if (!std::isdigit(temp[i]) && !std::isdigit(temp[i + 1]))
	{
		std::cout << "Error : bad input" << std::endl;
		return (-1);
	}
	return (nbr);
}

static int	checkline(std::string line, char delim)
{
	unsigned int i = 0;
	while (i != line.size())
	{
		if (i <= 3 && std::isdigit(line[i]) == 0)
			return (1);
		if (i == 4 && line[i] != '-')
			return (1);
		if ((i >= 5 && i <= 6) && ((std::isdigit(line[i]) == 0) || (line[5] >= '2') || (line[5] == '1' && line[6] >= '3')))
			return (1);
		if (i == 7 && line[i] != '-')
			return (1);
		if ((i >= 8 && i <= 9) && ((std::isdigit(line[i]) == 0) || (line[8] >= '4') || (line[8] == '3' && line[9] >= '2') || (line[5] == '0' && (line[6] == '4' || line[6] == '6' || line[6] == '9') && line[8] == '3' && line[9] != '0') || (line[5] == '1' && line[6] == '1' && line[8] == '3' && line[9] != '0') || (line[5] == '0' && line[6] == '2' && line[8] > '2')))
			return (1);
		if (delim == ',' && i == 10 && line[i] != ',')
			return (1);
		if (delim == '|' && i == 10 && line[i + 1] != '|')
			return (1);
		i++;
	}
	return (0);
}

void	BitcoinExchange::fillData(std::string fileName)
{
	std::fstream file;
	std::string temp;

	file.open(fileName.c_str());
	if (file.is_open() == false)
		throw cantOpenFile();
	while (getline(file, temp))
	{
		if (temp == "date,exchange_rate")
			continue;
		if (checkline(temp, ',') == 1)
		{
			file.close();
			throw formatErrorCsvFile();
		}
		_data.insert(std::make_pair(test(temp, ','), converToDouble(temp, ',')));
	}
	if (_data.size() == 0)
		throw emptyFile();
	file.close();
}

void	BitcoinExchange::fillInput(std::string fileName)
{
	std::fstream file;
	std::string temp;

	file.open(fileName.c_str());
	if (file.is_open() == false)
		throw cantOpenFile();
	while (getline(file, temp))
	{
		if (temp == "date | value")
			continue;
		if (checkline(temp, '|') == 1)
		{
			std::cout << "Error : bad input => " + temp << std::endl;
			continue;
		}
		std::string date = test(temp, '|');
		double value = converToDoubleForInput(temp, '|');
		if (value < 0)
			continue;
		std::multimap<std::string, double>::iterator j = _data.begin();

		while (j != _data.end() && j->first < date)
			j++;
		if (j == _data.end())
			j--;
		else if (j != _data.begin() && j->first > date)
			j--;
		if (j->first > date)
		{
			std::cout << "No date nor nearest lower date for this => " + date << std::endl;
			continue;
		}
		std::cout << std::fixed << date << " => " << value << " = " << value * j->second << std::endl;
	}
	file.close();
}

const char * cantOpenFile::what() const throw()
{
	return ("Error : Can't open file");
}

const char * emptyFile::what() const throw()
{
	return ("Error : Empty file");
}

const char * tooLargeNbr::what() const throw()
{
	return ("Error : too large number");
}

const char * negativeNbr::what() const throw()
{
	return ("Error : Negative number");
}

const char * formatErrorCsvFile::what() const throw()
{
	return ("Error : Bad format in data.csv");
}