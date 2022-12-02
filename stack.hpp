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
		private:
			container_type _container;
		public:
		// ==================== Constructors / Destructor ====================
			explicit stack(const container_type &ctnr = container_type()): _container(ctnr) { }
			stack(stack const &other): _container(other._container) { }
			~stack(void) { }
		// ==================== Operators ====================
			stack &operator=(stack const &other)
			{
				this->_container = other._container;
				return (*this);
			}
		// ==================== Member functions ====================
			bool empty(void) const { return this->_container.empty(); }
			size_type size(void) const { return this->_container.size(); }
			value_type &top(void) { return this->_container.back(); }
			const value_type &top(void) const { return this->_container.back(); }
			void push(const value_type &val) { this->_container.push_back(val); }
			void pop(void) { this->_container.pop_back(); }
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
	bool operator==(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs._container == rhs._container; }
	template <class T, class Container>
	bool operator!=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs._container != rhs._container; }
	template <class T, class Container>
	bool operator<(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs._container < rhs._container; }
	template <class T, class Container>
	bool operator<=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs._container <= rhs._container; }
	template <class T, class Container>
	bool operator>(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs._container > rhs._container; }
	template <class T, class Container>
	bool operator>=(stack<T, Container> const &lhs, stack<T, Container> const &rhs) { return lhs._container >= rhs._container; }
}

#endif
