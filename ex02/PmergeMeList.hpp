#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <deque>
#include <utility>
#include "PmergeMeVec.hpp"

class PmergeMeList
{
	public:
		PmergeMeList(char **input);
		~PmergeMeList();
		void	makePair(std::deque<t_nbr> arrayInt);
		std::deque<t_nbr>::iterator	findIndex(std::deque<t_nbr>::iterator search, std::deque<t_nbr> & array);
		t_nbr	findIndex(unsigned int search, std::deque<t_nbr> & array);
		void	sortPending();
		void	addPending(std::deque<t_nbr>::iterator begin, std::deque<t_nbr>::iterator end);
		void	replaceTab();
		std::deque<int>	getList(void);
	private:
		unsigned int _suite[30];
		std::deque<t_nbr> _S;
		std::deque<t_nbr> _P;
		std::deque<int> _returnList;
};