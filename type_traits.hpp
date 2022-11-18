#pragma once
#include <iostream>
#include <memory>
/*
	- INTEGRAL_CONSTANT (TEMPLATE CLASS THAT REPRESENTS A CONSTANT VALUE OF ANY INTEGRAL TYPE)
	- IS_INTEGRAL (TEMPLATE CLASS THAT DETERMINES WHETHER A TYPE IS AN INTEGRAL TYPE)
	- ENABLE_IF (TEMPLATE CLASS THAT PROVIDES A MEMBER TYPE IF A CONDITION IS TRUE)
	- EQUAL (TEMPLATE FUNCTION THAT COMPARES TWO VALUES FOR EQUALITY)
	- ITERATOR_TRAITS (TEMPLATE CLASS THAT PROVIDES INFORMATION ABOUT ITERATOR TYPES)
*/
namespace ft {
	// ====================  INTEGRAL_CONSTANT ====================
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() const { return value; }
	};
	
	// ====================  IS_INTEGRAL ====================
	// OPERATOR OVERLOADS FOR INTEGRAL_CONSTANT
	template <class T>
	struct is_integral : public integral_constant<bool, false> {};
	template <>
	struct is_integral<bool> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<signed char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned char> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<wchar_t> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<short> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned short> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned int> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<long> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned long> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<long long> : public integral_constant<bool, true> {};
	template <>
	struct is_integral<unsigned long long> : public integral_constant<bool, true> {};

	// ====================  ENABLE_IF ====================
	template <bool Cond, class T = void>
	struct enable_if {};
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// ====================  EQUAL ====================
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	// USES PRED FUNCTION TO COMPARE ELEMENTS
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	// ====================  ITERATOR_TRAITS ====================
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
}