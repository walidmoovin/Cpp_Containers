#include "vector.hpp"

int main(void)
{
	try
	{
		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int>::iterator it;

		first.push_back(10);
		first.push_back(20);
		first.push_back(30);
		second.push_back(100);
		second.push_back(200);
		second.push_back(300);

		// print size
		std::cout << "Size of first: " << int(first.size()) << std::endl;
		// iterate through first using iterator
		for (it = first.begin(); it != first.end(); it++)
			std::cout << *it << " ";
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}