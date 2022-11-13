#include "vector.hpp"

int main(void)
{
	try
	{
		ft::Vector<int> first;
		ft::Vector<int> second;

		first.push_back(10);
		first.push_back(20);
		first.push_back(30);
		second.push_back(100);
		second.push_back(200);
		second.push_back(300);

		for (unsigned i = 0; i < first.size(); i++)
			std::cout << first[i] << std::endl;
		first.swap(second);
		for (unsigned i = 0; i < first.size(); i++)
			std::cout << first[i] << std::endl;
		std::cout << "is first empty : " << first.empty() << std::endl;
		first.pop_back();
		first.pop_back();
		first.pop_back();
		std::cout << "is first empty : " << first.empty() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}