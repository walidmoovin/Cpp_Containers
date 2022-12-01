#include "RedBlackTree.hpp"
#include <iostream>
#include <random>

int main(void)
{
	RedBlackTree<int> tree;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1000);
	for (int i = 0; i < 1; i++)
	{
		int num = dis(gen);
		tree.insert(num);
		std::cout << "insert " << num << "\n\n";
		tree.print();
		// 1/2 chance to remove the number
		// std::cout << "- 50 % chance to remove " << num << "\n\n";
		// if (dis(gen) % 2 == 0)
		// {
		// 	tree.remove(num);
		// 	std::cout << "!!! remove " << num << "\n\n";
		// 	tree.print();
		// }
		// else
		// 	std::cout << "!!! no remove" << "\n\n";
		std::cout << "|| END ||" << std::endl;
	}
	RedBlackTree<int> tree1(tree);
	tree1.print();
	return (0);
}