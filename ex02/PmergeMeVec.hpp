#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <utility>
#include <ctime>
#include <unistd.h>

typedef struct s_nbr
{
	int numb;
	int index;
	s_nbr *pair;
	public :
		bool	operator<(const s_nbr& other) const;
		bool	operator==(s_nbr other) const;
} t_nbr;

class PmergeMeVec
{
	public:
		PmergeMeVec(char **input);
		~PmergeMeVec();
		void	makePair(std::vector<t_nbr> arrayInt);
		std::vector<t_nbr>::iterator	findIndex(std::vector<t_nbr>::iterator search, std::vector<t_nbr> & array);
		t_nbr	findIndex(unsigned int search, std::vector<t_nbr> & array);
		void	sortPending();
		void	addPending(std::vector<t_nbr>::iterator begin, std::vector<t_nbr>::iterator end);
		void	replaceTab();
		std::vector<int>	getArray(void);
	private:
		unsigned int _suite[30];
		std::vector<t_nbr> _S;
		std::vector<t_nbr> _P;
		std::vector<int> _returnArray;
};

class InvalidInput : public std::exception
{
	public :
		const char*	what() const throw();
};
