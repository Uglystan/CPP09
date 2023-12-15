#include "RPN.hpp"

RPN::RPN(char *str)
{
	_res = createStack(str);
	std::cout << _res << std::endl;
}

RPN::~RPN()
{

}

RPN::RPN(RPN const& substitue)
{
	_res = substitue._res;
}

RPN& RPN::operator=(RPN const& substitue)
{
	if (this != &substitue)
	{
		_res = substitue._res;
	}
	return (*this);
}

void	addNbr(char c, std::stack<int> & splitInput)
{
	double nb = 0;
	int nb1 = splitInput.top();
	splitInput.pop();
	int nb2 = splitInput.top();
	splitInput.pop();
	if(c == '+')
		nb = nb2 + nb1;
	else if (c == '*')
		nb = nb2 * nb1;
	else if (c == '-')
		nb = nb2 - nb1;
	else if (c == '/')
		nb = nb2 / nb1;
	if (nb < -2147483648 || nb > 2147483647)
		throw error("Error : number too hight");
	splitInput.push(nb);
}

std::stack<int>	split(std::string const& str, char sep)
{
	std::stack<int> splitInput;
	int j = 0;
	unsigned int i = 0;

	while (i <= str.size())
	{
		if (str[i] == sep ||  i == str.size())
		{
			std::string line = str.substr(j, i - j);
			if (line.size() >= 2)
				throw error("Error : input too long");
			if (!std::isdigit(line[0]) && line[0] != '-' && line[0] != '+' && line[0] != '*' && line[0] != '/')
				throw error("Error : input unknown");
			if(std::isdigit(line[0]))
				splitInput.push(atoi(line.c_str()));
			else
			{
				if(splitInput.size() < 2)
					throw error("Error : input order invalid");
				addNbr(line[0], splitInput);
			}
			j = i + 1;
		}
		i++;
	}
	if (splitInput.size() != 1)
		throw error("Error : input number of sign or input invalid");
	return (splitInput);
}

int	RPN::createStack(char *str)
{
	std::string input(str);
	std::stack<int> base = split(input, ' ');
	return (base.top());
}

error::error(const char* msg)
{
	_msg = msg;
}

const char*	error::what() const throw()
{
	return (_msg);
}
