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
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;
		};
}
#endif