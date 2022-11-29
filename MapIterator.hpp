#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#pragma once

namespace ft
{
	template <class RedBlackTree, bool isConst = false>
	class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, typename ft::choose<isConst, const typename RedBlackTree::value_type, typename RedBlackTree::value_type>::type> 
	{
		protected:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename ft::choose<isConst, const typename RedBlackTree::value_type, typename RedBlackTree::value_type>::type iterator;
			typename RedBlackTree::node_ptr _ptr;
		public:
			// ==================== Constructors ====================
			MapIterator() : _ptr(NULL) {}
			MapIterator(typename RedBlackTree::node_ptr ptr) : _ptr(ptr) {}
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
			// ==================== (it++) Operator ====================
			// ==================== (--it) Operator ====================
			// ==================== (it--) Operator ====================
			// ==================== Friend operator ====================
			template <class RedBlackTree, bool isConst, class RedBlackTree2, class isConst2>
			friend bool operator==(const MapIterator<RedBlackTree, isConst>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs);
			template <class RedBlackTree, bool isConst, class RedBlackTree2, class isConst2>
			friend bool operator!=(const MapIterator<RedBlackTree, isConst>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs);
	}
	template <class RedBlackTree, bool isConst, class RedBlackTree2, class isConst2>
	bool operator==(const MapIterator<RedBlackTree, isConst>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs)
	{
		return lhs._ptr == rhs._ptr;
	}
	template <class RedBlackTree, bool isConst, class RedBlackTree2, class isConst2>
	bool operator!=(const MapIterator<RedBlackTree, isConst>& lhs, const MapIterator<RedBlackTree2, isConst2>& rhs)
	{
		return lhs._ptr != rhs._ptr;
	}
}
#endif