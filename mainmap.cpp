#include "map.hpp"

// main testing map
int main(void)
{
	ft::map<int, std::string> mp;
	std::cout << "mp.size() = " << mp.size() << std::endl;
	ft::pair<int, std::string> tmp;
	tmp = ft::make_pair(42, "lol");
	std::cout << "tmp = " << tmp.first << " | " << tmp.second << std::endl;
	mp.insert(tmp);
	mp[0] = "lol";
	std::cout << mp[0] << std::endl;
}