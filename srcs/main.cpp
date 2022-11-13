#include "vector.hpp"

int main(void)
{
	try
	{
		ft::Vector<int> first;
		
		std::cout << "first.size() = " << first.size() << std::endl;
		std::cout << "first.capacity() = " << first.capacity() << std::endl;
		std::cout << "first.max_size() = " << first.max_size() << std::endl;
		std::cout << "first.empty() = " << first.empty() << std::endl;
		first.push_back(10);
		std::cout << first.at(0) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}