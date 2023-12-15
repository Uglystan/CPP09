#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>

class RPN
{
	public:
		RPN(char *str);
		~RPN();
		RPN(RPN const& substitue);
		RPN&	operator=(RPN const& substitue);
		int	createStack(char *str);

	private:
		int _res;
};

class	error : public std::exception
{
	public :
		error(const char* msg);
		const char*	what() const throw();
	private :
		const char* _msg;
};

