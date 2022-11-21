#ifndef CHAD_ITERATOR_HPP
#define CHAD_ITERATOR_HPP

#pragma once
#include <cstddef> // Standard library header for ptrdiff_t and size_t

namespace ft
{
	// ==================== ITERATOR_TAGS ====================
	// Iterator tag functions are a method for accessing information that is associated with iterators.
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	// ==================== ITERATOR_TRAITS ====================
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type; // Difference between 2 iterators
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t	difference_type; // Distance between 2 pointer
		typedef T			value_type;
		typedef T*			pointer;
		typedef T&			reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t	difference_type;
		typedef T			value_type;
		typedef T*			pointer;
		typedef T&			reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};
	// ==================== ITERATOR ====================
	// chad original iterator template, the first and the only one
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};
}

#endif