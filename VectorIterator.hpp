#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "ChadIterator.hpp"
#include "EnableIf.hpp"
#include "Choose.hpp"

namespace ft
{ 
	// isConst = true, type is const, otherwise type is not const
	template <typename T, bool isConst>
	class VectorIterator : public ft::ChadIterator<ft::random_access_iterator_tag, typename ft::choose<isConst, const T, T>::type>
	{

	}
}

#endif