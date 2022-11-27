#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#pragma once
#include "Choose.hpp"
#include "ChadIterator.hpp"
#include "IsIntegral.hpp"
#include "VectorIterator.hpp"

namespace ft
{
	// reverse iterator = fucking basic iterator but backwards (DIRECTION IS INVERTED, so ++ becomes -- and vice versa)
	template <class Iterator>
	class ReverseIterator
	{
		private:
			Iterator _it;
		public:
			typedef typename ft::iterator_traits<Iterator>::pointer pointer;
			typedef typename ft::iterator_traits<Iterator>::reference reference;
			// ==================== CONSTRUCTORS ====================
			ReverseIterator() : _it() {}
			ReverseIterator(Iterator it) : _it(it) {}
			// copy constructor (copying the base iterator is enough)
			template <class IteratorCopy>
			ReverseIterator(const ReverseIterator<IteratorCopy>& other) : _it(other.base()) {}
			
			// ==================== COPY ASSIGNMENT OPERATOR ====================
			ReverseIterator& operator=(const ReverseIterator& other)
			{
				this->_it = other._it;
				return *this;
			}

			// ==================== DESTRUCTOR ====================
			~ReverseIterator() {}

			// ==================== MEMBER FUNCTIONS ====================
			// returns the base iterator
			Iterator base() const
			{
				return this->_it;
			}
			// returns result of dereferencing the iterator that has been decremented by one
			reference operator*() const
			{
				Iterator tmp = this->_it;
				return *--tmp;
			}
			// returns adress of operator* function call
			pointer operator->() const
			{
				return &(this->operator*());
			}
			// [] operator overload (returns reference to element at index n)
 			reference operator[](std::size_t n) const
			{
				return *(*this + n);
			}

			// post-increment
			ReverseIterator operator++(int)
			{
				ReverseIterator tmp(*this);
				this->_it--;
				return tmp;
			}
			// post-decrement
			ReverseIterator operator--(int)
			{
				ReverseIterator tmp(*this);
				this->_it++;
				return tmp;
			}

			// pre-increment
			ReverseIterator& operator++()
			{
				this->_it--;
				return *this;
			}
			// pre-decrement
			ReverseIterator& operator--()
			{
				this->_it++;
				return *this;
			}

			// enhanced addition
			ReverseIterator& operator+=(std::size_t n)
			{
				this->_it -= n;
				return *this;
			}
			// enhanced subtraction
			ReverseIterator& operator-=(std::size_t n)
			{
				this->_it += n;
				return *this;
			}

			// addition
			ReverseIterator operator+(std::size_t n) const
			{
				ReverseIterator tmp(*this);
				return tmp += n;
			}
			// subtraction
			ReverseIterator operator-(std::size_t n) const
			{
				ReverseIterator tmp(*this);
				return tmp -= n;
			}
	};
	// addition operator
	template <class Iterator>
	std::size_t operator+(std::size_t n, const ReverseIterator<Iterator>& rhs)
	{
		return rhs.base() - n;
	}
	// subtraction operator
	template <class Iterator, class OtherIterator>
	std::size_t operator-(std::size_t n, const ReverseIterator<OtherIterator>& rhs)
	{
		return rhs.base() + n;
	}
	// subtraction operator, but allowing mix of reverse and non-reverse iterators
	template <class Iterator, class OtherIterator>
	std::size_t operator-(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() - rhs.base();
	} 
	// equality operator
	template <class Iterator, class OtherIterator>
	bool operator==(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	// inequality operator
	template <class Iterator, class OtherIterator>
	bool operator!=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}
	// less than operator
	template <class Iterator, class OtherIterator>
	bool operator<(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	// greater than operator
	template <class Iterator, class OtherIterator>
	bool operator>(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}
	// less than or equal to operator
	template <class Iterator, class OtherIterator>
	bool operator<=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}
	// greater than or equal to operator
	template <class Iterator, class OtherIterator>
	bool operator>=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
}

#endif