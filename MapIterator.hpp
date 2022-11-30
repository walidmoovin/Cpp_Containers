#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#pragma once
#include "ChadIterator.hpp"
#include "Choose.hpp"

namespace ft
{
	template <class RedBlackTree, bool isConst = false>
	class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, typename ft::choose<isConst, const typename RedBlackTree::value_type, typename RedBlackTree::value_type>::type> 
	{
		protected:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename ft::choose<isConst, const typename RedBlackTree::value_type, typename RedBlackTree::value_type>::type> iterator;
			typename RedBlackTree::rb_node* _ptr;
		public:
			// ==================== Constructors ====================
			MapIterator() : _ptr(NULL) {}
			MapIterator(typename RedBlackTree::rb_node* ptr) : _ptr(ptr) {}
			MapIterator(const MapIterator<RedBlackTree, isConst>& other) : _ptr(other._ptr) {}
			// ==================== Destructors ====================
			~MapIterator() {}
			// ===================== Non-const -> const conversion ====================
			operator MapIterator<RedBlackTree, true>() const
			{
				return MapIterator<RedBlackTree, true>(this->_ptr);
			}
			// ==================== (=) Operator ====================
			MapIterator<RedBlackTree, isConst>& operator=(const MapIterator<RedBlackTree, isConst>& other)
			{
				this->_ptr = other._ptr;
				return *this;
			}
			// ==================== (*) Operator ====================
			typename iterator::reference operator*() const
			{
				return this->_ptr->data;
			}
			// ==================== (->) Operator ====================
			typename iterator::pointer operator->() const
			{
				return &(this->_ptr->data);
			}
			// ==================== (++it) Operator ====================
			MapIterator<RedBlackTree, isConst>& operator++()
			{
				if (this->_ptr->color == 2)
					return (*this);
				this->_ptr = RedBlackTree::successor_in_order(this->_ptr);
				return (*this);
			}
			// ==================== (--it) Operator ====================
			MapIterator<RedBlackTree, isConst>& operator--()
			{
				if (RedBlackTree::predecessor_in_order(this->_node) == NULL)
					return (*this);
				this->_node = RedBlackTree::predecessor_in_order(this->_node);
				return (*this);
			}
			// ==================== (it++) Operator ====================	
			MapIterator<RedBlackTree, isConst> operator++(int)
			{
				MapIterator<RedBlackTree, isConst> tmp(*this);
				++(*this);
				return (tmp);
			}		
			// ==================== (it--) Operator ====================
			MapIterator<RedBlackTree, isConst> operator--(int)
			{
				MapIterator<RedBlackTree, isConst> tmp(*this);
				--(*this);
				return (tmp);
			}
			// ==================== Friend operator ====================
			template <class RedBlackTree1, bool isConst1, class RedBlackTree2, bool isConst2>
			friend bool operator==(const MapIterator<RedBlackTree1, isConst1>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs);
			template <class RedBlackTree1, bool isConst1, class RedBlackTree2, bool isConst2>
			friend bool operator!=(const MapIterator<RedBlackTree1, isConst1>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs);
	};
	template <class RedBlackTree1, bool isConst1, class RedBlackTree2, bool isConst2>
	bool operator==(const MapIterator<RedBlackTree1, isConst1>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs)
	{
		return lhs._ptr == rhs._ptr;
	}
	template <class RedBlackTree1, bool isConst1, class RedBlackTree2, bool isConst2>
	bool operator!=(const MapIterator<RedBlackTree1, isConst1>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs)
	{
		return lhs._ptr != rhs._ptr;
	}
}
#endif