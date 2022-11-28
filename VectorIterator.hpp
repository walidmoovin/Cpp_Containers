#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

// typename is a keyword that tells the compiler that an identifier is a type.
#pragma once
#include "Choose.hpp"
#include "ChadIterator.hpp"
#include "IsIntegral.hpp"

namespace ft
{ 
	template <typename T, bool isConst = false>
	class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, typename ft::choose<isConst, const T, T>::type>
	{
		protected:
			T* _ptr;
			typedef typename ft::iterator<ft::random_access_iterator_tag, typename ft::choose<isConst, const T, T>::type> it;																														
		public:
			// ==================== Constructors ====================
			VectorIterator(T* ptr) : _ptr(ptr) {}
			VectorIterator() : _ptr(NULL) {}
			VectorIterator(const VectorIterator<T, isConst>& other) : _ptr(other._ptr) {}
			// ==================== Destructors ====================
			~VectorIterator() {}
			// ===================== Non-const -> const conversion ====================
			operator VectorIterator<T, true>() const
			{
				return VectorIterator<T, true>(this->_ptr);
			}
			// ==================== (=) Operator ====================
			VectorIterator<T, isConst>& operator=(const VectorIterator& other)
			{
				this->_ptr = other._ptr;
				return *this;
			}
			// Post-increment
			VectorIterator<T, isConst> operator++(int)
			{
				VectorIterator<T, isConst> tmp(*this);
				this->_ptr++;
				return tmp;
			}
			// Post-decrement
			VectorIterator<T, isConst> operator--(int)
			{
				VectorIterator<T, isConst> tmp(*this);
				this->_ptr--;
				return tmp;
			}
			// Pre-increment
			VectorIterator<T, isConst>& operator++()
			{
				this->_ptr++;
				return *this;
			}
			// Pre-decrement
			VectorIterator<T, isConst>& operator--()
			{
				this->_ptr--;
				return *this;
			}
			// Enhanced addition
			VectorIterator<T, isConst>& operator+=(typename it::difference_type n)
			{
				this->_ptr += n;
				return *this;
			}
			// Enhanced subtraction
			VectorIterator<T, isConst>& operator-=(typename it::difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}
			// Addition
			VectorIterator<T, isConst> operator+(typename it::difference_type n) const
			{
				return VectorIterator<T, isConst>(this->_ptr + n);
			}
			// Subtraction
			VectorIterator<T, isConst> operator-(typename it::difference_type n) const
			{
				return VectorIterator<T, isConst>(this->_ptr - n);
			}
			// A*
			typename it::reference operator*() const
			{
				return *(this->_ptr);
			}
			// A->m
			typename it::pointer operator->() const
			{
				return this->_ptr;
			}
			// A[n]
			typename it::reference operator[](typename it::difference_type n) const
			{
				return *(this->_ptr + n);
			}
			// Difference between two iterators
			typename it::difference_type operator-(const VectorIterator<T, isConst>& other) const
			{
				return (this->_ptr - other._ptr);
			}
			// ==================== Friend operators (allow const and non-const in operators) (just prototype here, functions outside of the class) ====================
			template <typename Y, bool isConstFriend>
			friend VectorIterator<Y, isConstFriend> operator+(std::size_t n, const VectorIterator<Y, isConstFriend>& other);
			template <class Iterator, class OtherIterator>
			friend typename OtherIterator::difference_type operator-(const Iterator& lhs, const OtherIterator& rhs);
			template <typename Y, bool isConstFriend, bool isConstFriend2>
			friend bool operator!=(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2);
			template <typename Y, bool isConstFriend, bool isConstFriend2>
			friend bool operator==(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2);
			template <typename Y, bool isConstFriend, bool isConstFriend2>
			friend bool operator<(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2);
			template <typename Y, bool isConstFriend, bool isConstFriend2>
			friend bool operator>(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2);
			template <typename Y, bool isConstFriend, bool isConstFriend2>
			friend bool operator<=(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2);
			template <typename Y, bool isConstFriend, bool isConstFriend2>
			friend bool operator>=(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2);
	};
	template <typename Y, bool isConstFriend>
	VectorIterator<Y, isConstFriend> operator+(std::size_t n, const VectorIterator<Y, isConstFriend>& other)
	{
		return VectorIterator<Y, isConstFriend>(other._ptr + n);
	}
	template <class Iterator, class OtherIterator>
	typename OtherIterator::difference_type operator-(const Iterator& lhs, const OtherIterator& rhs)
	{
		return (lhs._ptr - rhs._ptr);
	}
	template <typename Y, bool isConstFriend, bool isConstFriend2>
	bool operator!=(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2)
	{
		return (other._ptr != other2._ptr);
	}
	template <typename Y, bool isConstFriend, bool isConstFriend2>
	bool operator==(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2)
	{
		return (other._ptr == other2._ptr);
	}
	template <typename Y, bool isConstFriend, bool isConstFriend2>
	bool operator<(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2)
	{
		return (other._ptr < other2._ptr);
	}
	template <typename Y, bool isConstFriend, bool isConstFriend2>
	bool operator>(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2)
	{
		return (other._ptr > other2._ptr);
	}
	template <typename Y, bool isConstFriend, bool isConstFriend2>
	bool operator<=(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2)
	{
		return (other._ptr <= other2._ptr);
	}
	template <typename Y, bool isConstFriend, bool isConstFriend2>
	bool operator>=(const VectorIterator<Y, isConstFriend>& other, const VectorIterator<Y, isConstFriend2>& other2)
	{
		return (other._ptr >= other2._ptr);
	}
}
#endif