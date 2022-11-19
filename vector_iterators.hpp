#pragma once
#include <iostream>
#include <memory>

namespace ft
{
	// ====================  RANDOM ACCESS ITERATOR  ====================
	template <class T>
	class random_access_iterator
	{
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;

			// ====================  CONSTRUCTORS  ====================
			random_access_iterator() : _ptr(NULL){};
			random_access_iterator(pointer ptr) : _ptr(ptr){};
			random_access_iterator(const random_access_iterator &other) : _ptr(other._ptr){};

			// ====================  DESTRUCTOR  ====================
			~random_access_iterator(){};

			// ====================  OPERATORS  ====================\

			// CAST TO CONST ITERATOR
			operator random_access_iterator<const T>() const { return random_access_iterator<const T>(_ptr); };

			// ASSIGNATION
			random_access_iterator &operator=(const random_access_iterator &other)
			{
				_ptr = other._ptr;
				return *this;
			};

			// DEREFERENCING AS AN LVALUE
			reference operator*() const { return *_ptr; };

			// DEREFERENCING AS AN RVALUE
			pointer operator->() const { return _ptr; };

			// INCREMENTATION PREFIX
			random_access_iterator &operator++()
			{
				_ptr++;
				return *this;
			};

			// INCREMENTATION BY AN INTEGER
			random_access_iterator operator++(int)
			{
				random_access_iterator tmp(*this);
				operator++();
				return tmp;
			};

			// DECREMENTATION PREFIX
			random_access_iterator &operator--()
			{
				_ptr--;
				return *this;
			};

			// DECREMENTATION BY AN INTEGER
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp(*this);
				operator--();
				return tmp;
			};

			// ADDITION BY AN INTEGER
			random_access_iterator operator+(difference_type n) const { return random_access_iterator(_ptr + n); };

			// SUBSTRACTION BY AN INTEGER
			random_access_iterator operator-(difference_type n) const { return random_access_iterator(_ptr - n); };

			// ADDITION ASSIGNATION BY AN INTEGER
			random_access_iterator &operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			};

			// SUBSTRACTION ASSIGNATION BY AN INTEGER
			random_access_iterator &operator-=(difference_type n)
			{
				_ptr -= n;
				return *this;
			};

			// SUBSTRACTION OF TWO ITERATORS
			difference_type operator-(const random_access_iterator &other) const { return _ptr - other._ptr; };

			// DEREFERENCING AN ITERATOR
			reference operator[](difference_type n) const { return *(_ptr + n); };

			// COMPARISON OPERATORS
			bool operator==(const random_access_iterator &other) const { return _ptr == other._ptr; };
			bool operator!=(const random_access_iterator &other) const { return _ptr != other._ptr; };
			bool operator<(const random_access_iterator &other) const { return _ptr < other._ptr; };
			bool operator<=(const random_access_iterator &other) const { return _ptr <= other._ptr; };
			bool operator>(const random_access_iterator &other) const { return _ptr > other._ptr; };
			bool operator>=(const random_access_iterator &other) const { return _ptr >= other._ptr; };
			


		private:
			pointer _ptr;
	};
	// ==================== CONST RANDOM ACCESS ITERATOR ====================
	template <class T>
	class const_random_access_iterator
	{
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef const T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;

			// ====================  CONSTRUCTORS  ====================
			const_random_access_iterator() : _ptr(NULL){};
			const_random_access_iterator(pointer ptr) : _ptr(ptr){};
			const_random_access_iterator(const const_random_access_iterator &other) : _ptr(other._ptr){};

			// ====================  DESTRUCTOR  ====================
			~const_random_access_iterator(){};

			// ====================  OPERATORS  ====================\
				// ASSIGNATION
			const_random_access_iterator &operator=(const const_random_access_iterator &other)
			{
				_ptr = other._ptr;
				return *this;
			};

			// DEREFERENCING AS AN LVALUE
			reference operator*() const { return *_ptr; };

			// DEREFERENCING AS AN RVALUE
			pointer operator->() const { return _ptr; };

			// INCREMENTATION PREFIX
			const_random_access_iterator &operator++()
			{
				_ptr++;
				return *this;
			};

			// INCREMENTATION BY AN INTEGER
			const_random_access_iterator operator++(int)
			{
				const_random_access_iterator tmp(*this);
				operator++();
				return tmp;
			};

			// DECREMENTATION PREFIX
			const_random_access_iterator &operator--()
			{
				_ptr--;
				return *this;
			};

			// DECREMENTATION BY AN INTEGER
			const_random_access_iterator operator--(int)
			{
				const_random_access_iterator tmp(*this);
				operator--();
				return tmp;
			};

			// ADDITION BY AN INTEGER
			const_random_access_iterator operator+(difference_type n) const { return const_random_access_iterator(_ptr + n); };

			// SUBSTRACTION BY AN INTEGER
			const_random_access_iterator operator-(difference_type n) const { return const_random_access_iterator(_ptr - n); };

			// ADDITION ASSIGNATION BY AN INTEGER
			const_random_access_iterator &operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			};

			// SUBSTRACTION ASSIGNATION BY AN INTEGER
			const_random_access_iterator &operator-=(difference_type n)
			{
				_ptr -= n;
				return *this;
			};

			// SUBSTRACTION OF TWO ITERATORS
			difference_type operator-(const const_random_access_iterator &other) const { return _ptr - other._ptr; };

			// DEREFERENCING AN ITERATOR
			reference operator[](difference_type n) const { return *(_ptr + n); };

			// COMPARISON OPERATORS
			bool operator==(const const_random_access_iterator &other) const { return _ptr == other._ptr; };
			bool operator!=(const const_random_access_iterator &other) const { return _ptr != other._ptr; };
			bool operator<(const const_random_access_iterator &other) const { return _ptr < other._ptr; };
			bool operator<=(const const_random_access_iterator &other) const { return _ptr <= other._ptr; };
			bool operator>(const const_random_access_iterator &other) const { return _ptr > other._ptr; };
			bool operator>=(const const_random_access_iterator &other) const { return _ptr >= other._ptr; };

		private:
			pointer _ptr;
	};
}