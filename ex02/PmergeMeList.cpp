#include "PmergeMeList.hpp"

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

static void	putInVector(char **in, std::deque<t_nbr> & array)
{
	unsigned int i = 1;

	while (in[i] != NULL)
	{
		std::string line = in[i];
		if(onlyDigit(line) == 1)
			throw InvalidInput();;
		t_nbr value;
		value.numb = atoi(line.c_str());
		value.index = 0;
		array.push_back(value);
		i++;
	}
}

void	PmergeMeList::makePair(std::deque<t_nbr> arrayInt)
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

void	mergeSort(std::deque<t_nbr>::iterator iter1, std::deque<t_nbr>::iterator iter2, bool (*cmp)(const s_nbr &, const s_nbr &))
{
	size_t size = iter2 - iter1;
	std::deque<t_nbr>::iterator iterMiddle = iter1 + size / 2;

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

std::deque<t_nbr>::iterator	PmergeMeList::findIndex(std::deque<t_nbr>::iterator search, std::deque<t_nbr> & array)
{
	for(std::deque<t_nbr>::iterator begin = array.begin(); begin != array.end(); begin++)
	{
		if (begin->index == search->index)
			return(begin);
	}
	return (array.end());
}

t_nbr	PmergeMeList::findIndex(unsigned int search, std::deque<t_nbr> & array)
{
	for(unsigned int begin = 0; begin < array.size(); begin++)
	{
		if (static_cast<unsigned int>(array[begin].index) == search)
			return(array[begin]);
	}
	return (array[0]);
}


int Jacobsthal(int n)
{
    if (n == 0)
        return 2;
 
    if (n == 1)
        return 2;
 
    return Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2);
}


void	PmergeMeList::addPending(std::deque<t_nbr>::iterator begin, std::deque<t_nbr>::iterator end)
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

void	PmergeMeList::sortPending()
{
	unsigned int add = 0;
	unsigned int i = 0;
	std::deque<t_nbr>::iterator begin = _P.begin();
	std::deque<t_nbr>::iterator end = _P.begin() + add - 1;

	while(add < _P.size())
	{
		add += Jacobsthal(i);
		if (add > _P.size())
			add = _P.size();
		end = _P.begin() + add - 1;
		addPending(begin, end);
		begin = end + 1;

		i++;
	}
}

void	PmergeMeList::replaceTab()
{
	for(std::deque<t_nbr>::iterator begin = _S.begin(); begin != _S.end(); begin++)
	{
		_returnList.push_back(begin->numb);
	}
}

std::deque<int>	PmergeMeList::getList(void)
{
	return (_returnList);
}

PmergeMeList::PmergeMeList(char **input)
{
	for(int i = 0; i < 30; i++)
	{
		_suite[i] = Jacobsthal(i);
	}
	std::deque<t_nbr> arrayInt;
	putInVector(input, arrayInt);
	if (arrayInt.size() == 1)
		_returnList.push_back(arrayInt.begin()->numb);
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

PmergeMeList::~PmergeMeList()
{
}