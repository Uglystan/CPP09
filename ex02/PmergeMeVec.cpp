#include "PmergeMeVec.hpp"

static int	onlyDigit(std::string const& str)
{
	if (str == "")
		return (1);
	for(unsigned int i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
			return (1);
	}
	return (0);
}

static void	putInVector(char **in, std::vector<t_nbr> & array)
{
	unsigned int i = 1;

	while (in[i] != NULL)
	{
		std::string line = in[i];
		if(onlyDigit(line) == 1)
			throw InvalidInput();
		t_nbr value;
		value.numb = atoi(line.c_str());
		value.index = 0;
		array.push_back(value);
		i++;
	}
}

void	PmergeMeVec::makePair(std::vector<t_nbr> arrayInt)
{
	int index = 1;
	unsigned int j = 1;

	for(unsigned int i = 0; i < arrayInt.size(); i+= 2)
	{
		if (i == arrayInt.size() - 1)
		{
			arrayInt[i].index = index;
			arrayInt[i].pair = NULL;
			_P.push_back(arrayInt[i]);
		}
		else
		{
			arrayInt[i].index = index;
			arrayInt[j].index = index;
			arrayInt[i].pair = &arrayInt[j];
			arrayInt[j].pair = &arrayInt[i];
			if(arrayInt[i].numb > arrayInt[j].numb)
			{
				_S.push_back(arrayInt[i]);
				_P.push_back(arrayInt[j]);
			}
			else
			{
				_S.push_back(arrayInt[j]);
				_P.push_back(arrayInt[i]);
			}
		}
		index++;
		j += 2;
	}
}

void	mergeSort(std::vector<t_nbr>::iterator iter1, std::vector<t_nbr>::iterator iter2, bool (*cmp)(const s_nbr &, const s_nbr &))
{
	size_t size = iter2 - iter1;
	std::vector<t_nbr>::iterator iterMiddle = iter1 + size / 2;

	if (size > 1)
	{
		mergeSort(iter1, iterMiddle, cmp);
		mergeSort(iterMiddle, iter2, cmp);
		if (cmp == NULL)
			std::inplace_merge(iter1, iterMiddle, iter2);
		else
			std::inplace_merge(iter1, iterMiddle, iter2, cmp);
	}
}

std::vector<t_nbr>::iterator	PmergeMeVec::findIndex(std::vector<t_nbr>::iterator search, std::vector<t_nbr> & array)
{
	for(std::vector<t_nbr>::iterator begin = array.begin(); begin != array.end(); begin++)
	{
		if (begin->index == search->index)
			return(begin);
	}
	return (array.end());
}

t_nbr	PmergeMeVec::findIndex(unsigned int search, std::vector<t_nbr> & array)
{
	for(unsigned int begin = 0; begin < array.size(); begin++)
	{
		if (static_cast<unsigned int>(array[begin].index) == search)
			return(array[begin]);
	}
	return (array[0]);
}


static int Jacobsthal(int n)
{
    if (n == 0)
        return 2;
 
    if (n == 1)
        return 2;
 
    return Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2);
}


void	PmergeMeVec::addPending(std::vector<t_nbr>::iterator begin, std::vector<t_nbr>::iterator end)
{
	while(end != begin)
	{
		s_nbr temp;
		temp.index = end->index;
		temp.numb = end->numb;
		temp.pair = end->pair;
		_S.insert(std::upper_bound(_S.begin(), _S.end(), temp), temp);
		end = end - 1;
	}
	s_nbr temp;
	temp.index = end->index;
	temp.numb = end->numb;
	temp.pair = end->pair;
	_S.insert(std::upper_bound(_S.begin(), _S.end(), temp), temp);
}

void	PmergeMeVec::sortPending()
{
	unsigned int add = 0;
	unsigned int i = 0;
	std::vector<t_nbr>::iterator begin = _P.begin();
	std::vector<t_nbr>::iterator end = _P.begin() + add - 1;

	while(add < _P.size())
	{
		add += Jacobsthal(i);
		end = _P.begin() + add - 1;
		if (end >= _P.end())
			end = _P.end() - 1;
		addPending(begin, end);
		begin = end + 1;

		i++;
	}
}

void	PmergeMeVec::replaceTab()
{
	for(std::vector<t_nbr>::iterator begin = _S.begin(); begin != _S.end(); begin++)
	{
		_returnArray.push_back(begin->numb);
	}
}

std::vector<int>	PmergeMeVec::getArray(void)
{
	return (_returnArray);
}

PmergeMeVec::PmergeMeVec(char **input)
{
	for(int i = 0; i < 30; i++)
	{
		_suite[i] = Jacobsthal(i);
	}
	std::vector<t_nbr> arrayInt;
	putInVector(input, arrayInt);
	if (arrayInt.size() == 1)
		_returnArray.push_back(arrayInt.begin()->numb);
	else
	{
		makePair(arrayInt);
		mergeSort(_S.begin(), _S.end(), NULL);
		_S.insert(_S.begin(), *(findIndex(_S.begin(), _P)));
		_P.erase(findIndex(_S.begin(), _P));
		sortPending();
		replaceTab();
	}
}

bool	t_nbr::operator<(const s_nbr& other) const
{
	return(this->numb < other.numb ? 1 : 0);
}

bool	t_nbr::operator==(s_nbr other) const
{
	return(this->numb == other.numb ? 1 : 0);
}

const char*	InvalidInput::what() const throw()
{
	return("Error : invalid input");
}

PmergeMeVec::~PmergeMeVec()
{
}