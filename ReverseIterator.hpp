#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#pragma once
#include "Choose.hpp"
#include "ChadIterator.hpp"
#include "IsIntegral.hpp"
#include "VectorIterator.hpp"

namespace ft
{
	// ReverseIterator = basic iterator but backwards (++ becomes -- and vice versa)
	template <class Iterator>
	class ReverseIterator
	{
		private:
			Iterator _it;
		public:
			typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer pointer;
			typedef typename ft::iterator_traits<Iterator>::reference reference;
			// ==================== Constructors ====================
			ReverseIterator() : _it() {}
			ReverseIterator(Iterator it) : _it(it) {}
			// Copy (base iterator)
			template <class IteratorCopy>
			ReverseIterator(const ReverseIterator<IteratorCopy>& other) : _it(other.base()) {}
			// ==================== (==) Operator ====================
			ReverseIterator& operator=(const ReverseIterator& other)
			{
				this->_it = other._it;
				return *this;
			}
			// ==================== Destructor ====================
			~ReverseIterator() {}
			// Base iterator
			Iterator base() const
			{
				return this->_it;
			}
			// Returns result of dereferencing the iterator decremented by one
			reference operator*() const
			{
				Iterator tmp = this->_it;
				return *--tmp;
			}
			// Returns adress of operator* function call
			pointer operator->() const
			{
				return &(this->operator*());
			}
			// Returns reference to element at index n
 			reference operator[](difference_type n) const
			{
				return *(*this + n);
			}
			// Post-increment
			ReverseIterator operator++(int)
			{
				ReverseIterator tmp(*this);
				this->_it--;
				return tmp;
			}
			// Post-decrement
			ReverseIterator operator--(int)
			{
				ReverseIterator tmp(*this);
				this->_it++;
				return tmp;
			}
			// Pre-increment
			ReverseIterator& operator++()
			{
				this->_it--;
				return *this;
			}
			// Pre-decrement
			ReverseIterator& operator--()
			{
				this->_it++;
				return *this;
			}
			// Enhanced addition
			ReverseIterator& operator+=(difference_type n)
			{
				this->_it -= n;
				return *this;
			}
			// Enhanced subtraction
			ReverseIterator& operator-=(difference_type n)
			{
				this->_it += n;
				return *this;
			}
			// Addition
			ReverseIterator operator+(difference_type n) const
			{
				ReverseIterator tmp(*this);
				return tmp += n;
			}
			// Subtraction
			ReverseIterator operator-(difference_type n) const
			{
				ReverseIterator tmp(*this);
				return tmp -= n;
			}
	};
	// Addition operator
	template <class Iterator>
	ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator>& other)
	{
		return (other + n);
	}
	// Subtraction operator
	template<class Iterator>
 	typename ReverseIterator<Iterator>::difference_type operator-(const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
	// Subtraction operator, but allowing mix of reverse and non-reverse iterators
	template <class Iterator, class OtherIterator>
	typename ReverseIterator<Iterator>::difference_type operator-(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return rhs.base() - lhs.base();
	} 
	template <class Iterator, class OtherIterator>
	bool operator==(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <class Iterator, class OtherIterator>
	bool operator!=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}
	template <class Iterator, class OtherIterator>
	bool operator<(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	template <class Iterator, class OtherIterator>
	bool operator>(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}
	template <class Iterator, class OtherIterator>
	bool operator<=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}
	template <class Iterator, class OtherIterator>
	bool operator>=(const ReverseIterator<Iterator>& lhs, const ReverseIterator<OtherIterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
}

#endif