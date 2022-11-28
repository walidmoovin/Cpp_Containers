#ifndef MAP_HPP
#define MAP_HPP

#pragma once
#include "Pair.hpp"

/* map specificities:
	- Associative (KEY -> VALUE)
	- Ordered (by KEY)
	- Unique (no two equivalent keys)
	- Allocator-aware
*/
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{	
	};
}
#endif