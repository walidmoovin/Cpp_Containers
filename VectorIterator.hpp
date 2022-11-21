#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#pragma once
#include "Choose.hpp"
#include "ChadIterator.hpp"
#include "IsIntegral.hpp"

namespace ft
{ 
	template <typename T, bool isConst>
	class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, typename ft::choose<isConst, const T, T>::type>
	{
		protected:
			T* _ptr;
			typedef typename ft::iterator<ft::random_access_iterator_tag, typename ft::choose<isConst, const T, T>::type> it;																														
		public:
			// ==================== CONSTRUCTORS ====================
			VectorIterator() : _ptr(NULL) {}
			VectorIterator(T* ptr) : _ptr(ptr) {}
			VectorIterator(const VectorIterator<T, isConst>& other) : _ptr(other._ptr) {}
			// ==================== DESTRUCTOR ====================
			~VectorIterator() {}
			// ===================== CONVERSION NON-CONST TO CONST ====================
			operator VectorIterator<T, true>() const
			{
				return VectorIterator<T, true>(this->_ptr);
			}
			// ==================== ASSIGNMENT OPERATOR ====================
			VectorIterator<T, isConst>& operator=(const VectorIterator& other)
			{
				this->_ptr = other._ptr;
				return *this;
			}

			// ==================== OPERATORS ====================
			// post-increment
			VectorIterator<T, isConst>& operator++(int)
			{
				VectorIterator<T, isConst> tmp(*this);
				this->_ptr++;
				return *this;
			}
			// post-decrement
			VectorIterator<T, isConst>& operator--(int)
			{
				VectorIterator<T, isConst> tmp(*this);
				this->_ptr--;
				return *this;
			}
			// pre-increment
			VectorIterator<T, isConst>& operator++()
			{
				this->_ptr++;
				return *this;
			}
			// pre-decrement
			VectorIterator<T, isConst>& operator--()
			{
				this->_ptr--;
				return *this;
			}
			// enhanced addition
			VectorIterator<T, isConst>& operator+=(typename it::difference_type n)
			{
				this->_ptr += n;
				return *this;
			}
			// enhanced subtraction
			VectorIterator<T, isConst>& operator-=(typename it::difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}
			// addition
			VectorIterator<T, isConst> operator+(typename it::difference_type n) const
			{
				return VectorIterator<T, isConst>(this->_ptr + n);
			}
			// subtraction
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
			// ==================== COMPARISON OPERATORS ====================
			// ==
			bool operator==(const VectorIterator<T, isConst>& other) const
			{
				return this->_ptr == other._ptr;
			}
			// !=
			bool operator!=(const VectorIterator<T, isConst>& other) const
			{
				return this->_ptr != other._ptr;
			}
			// <
			bool operator<(const VectorIterator<T, isConst>& other) const
			{
				return this->_ptr < other._ptr;
			}
			// >
			bool operator>(const VectorIterator<T, isConst>& other) const
			{
				return this->_ptr > other._ptr;
			}
			// <=
			bool operator<=(const VectorIterator<T, isConst>& other) const
			{
				return this->_ptr <= other._ptr;
			}
			// >=
			bool operator>=(const VectorIterator<T, isConst>& other) const
			{
				return this->_ptr >= other._ptr;
			}	

	};
}

#endif