#include "map.hpp"
#include <map>

void print_map(ft::map<int, std::string> &mp, std::string which_map);
void print_std_map(std::map<int, std::string> &mp);

int main(void)
{
	ft::map<int, std::string> mp;
	ft::pair<int, std::string> tmp;
	tmp = ft::make_pair(42, "lol");
	mp.insert(tmp);
	tmp = ft::make_pair(21, "lul");
	mp.insert(tmp);
	tmp = ft::make_pair(84, "lel");
	mp.insert(tmp);
	tmp = ft::make_pair(63, "lil");
	mp.insert(tmp);
	mp[120] = "PUTE";
	print_map(mp, "mp");
	std::cout << "first element: " << mp.begin()->first << " | " << mp.begin()->second << std::endl;
	std::cout << "last element: " << (--mp.end())->first << " | " << (--mp.end())->second << std::endl;


	ft::map<int, std::string> mp3;
	mp3.insert(mp.begin(), mp.end());
	print_map(mp3, "bite");


	// remove some elements
	mp.erase(mp.begin());
	print_map(mp, "mp");
	mp.erase(--mp.end());
	print_map(mp, "mp");
	// remove range of elements
	mp.erase(mp.begin(), mp.end());
	print_map(mp, "mp");


	std::map<int, std::string> mp2;
	mp2.insert(std::make_pair(42, "lol"));
	mp2.insert(std::make_pair(21, "lul"));
	mp2.insert(std::make_pair(84, "lel"));
	mp2.insert(std::make_pair(63, "lil"));
	mp2[120] = "PUTE";
	print_std_map(mp2);
	std::cout << "first element: " << mp2.begin()->first << " | " << mp2.begin()->second << std::endl;
	std::cout << "last element: " << (--mp2.end())->first << " | " << (--mp2.end())->second << std::endl;


	// removing some elements
	mp2.erase(mp2.begin());
	print_std_map(mp2);
	mp2.erase(--mp2.end());
	print_std_map(mp2);

}

void print_map(ft::map<int, std::string> &mp, std::string which_map)
{
	ft::map<int, std::string>::iterator it = mp.begin();
	ft::map<int, std::string>::iterator ite = mp.end();
	if (which_map == "mp")
		std::cout << "========================= MAP PRINT =========================" << std::endl;
	else
		std::cout << "========================= MAP 3 PRINT =========================" << std::endl;
	for (ft::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); it++)
		std::cout << it->first << " | " << it->second << std::endl;
	std::cout << "============================================================" << std::endl;
}

void print_std_map(std::map<int, std::string> &mp)
{
	std::cout << "========================= STD MAP PRINT =========================" << std::endl;
	for (std::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); it++)
		std::cout << it->first << " | " << it->second << std::endl;
	std::cout << "============================================================" << std::endl;
}