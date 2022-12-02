#ifndef STACK_HPP
#define STACK_HPP

#pragma once
#include "vector.hpp"

// stack is just a cringe way to use vector, don't use it please it's bad
namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;
		protected:
			container_type c;
		public:
		// ==================== Constructors / Destructor ====================
			explicit stack(const container_type &ctnr = container_type()): c(ctnr) { }
			stack(stack const &other): c(other.c) { }
			~stack(void) { }
		// ==================== Operators ====================
			stack &operator=(stack const &other)
			{
				this->c = other.c;
				return (*this);
			}
		// ==================== Member functions ====================
			bool empty(void) const { return this->c.empty(); }
			size_type size(void) const { return this->c.size(); }
			value_type &top(void) { return this->c.back(); }
			const value_type &top(void) const { return this->c.back(); }
			void push(const value_type &val) { this->c.push_back(val); }
			void pop(void) { this->c.pop_back(); }
		// ==================== Non-member functions ====================
			template <class U, class C>
			friend bool operator==(stack<U, C> const &lhs, stack<U, C> const &rhs);
			template <class U, class C>
			friend bool operator!=(stack<U, C> const &lhs, stack<U, C> const &rhs);
			template <class U, class C>
			friend bool operator<(stack<U, C> const &lhs, stack<U, C> const &rhs);
			template <class U, class C>
			friend bool operator<=(stack<U, C> const &lhs, stack<U, C> const &rhs);
			template <class U, class C>
			friend bool operator>(stack<U, C> const &lhs, stack<U, C> const &rhs);
			template <class U, class C>
			friend bool operator>=(stack<U, C> const &lhs, stack<U, C> const &rhs);
	};
	// ==================== Non-member functions ====================
	template <class T, class Container>
	bool operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs.c == rhs.c; }
	template <class T, class Container>
	bool operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs.c != rhs.c; }
	template <class T, class Container>
	bool operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs.c < rhs.c; }
	template <class T, class Container>
	bool operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs.c <= rhs.c; }
	template <class T, class Container>
	bool operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs.c > rhs.c; }
	template <class T, class Container>
	bool operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs.c >= rhs.c; }
}

#endif
