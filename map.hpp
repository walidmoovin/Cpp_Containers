#ifndef MAP_HPP
#define MAP_HPP

#pragma once
#include "Pair.hpp"
#include "RedBlackTree.hpp"
#include "Equal.hpp"
#include <memory>

/* map specificities:
	- Associative (KEY -> VALUE)
	- Ordered (by KEY)
	- Unique (no two equivalent keys)
	- Allocator-aware
*/
namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
		private:
			typedef RedBlackTree<std::pair<const Key, T>, Compare, Alloc>	_redblacktree;
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const Key, T> value_type;
			typedef Compare key_compare;
			struct value_compare
			{
				bool operator()(value_type const &lhs, value_type const &rhs) const
				{
					Compare comp;
					return comp(lhs.first, rhs.first);
				}
			};
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename _redblacktree::iterator iterator;
			typedef typename _redblacktree::const_iterator const_iterator;
			typedef typename _redblacktree::reverse_iterator reverse_iterator;
			typedef typename _redblacktree::const_reverse_iterator const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
		private:
			key_compare _comp;
			allocator_type _alloc;
			_redblacktree _tree;
			bool inferior(value_type const &lhs, value_type const &rhs) const { return this->_comp(lhs, rhs); }
			bool equal(value_type const &lhs, value_type const &rhs) const { return !this->_comp(lhs, rhs) && !this->_comp(rhs, lhs); }
			bool superior(value_type const &lhs, value_type const &rhs) const { return this->_comp(rhs, lhs); }
		public:
		// ==================== Constructors / Destructor ====================
			map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _comp(comp), _alloc(alloc), _tree() { }
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree() { while (first != last) this->_tree.insert(*first++); }
			map(map const &x): _comp(x._comp), _alloc(x._alloc), _tree(x._tree) { }
			~map() { }
		// ==================== (=) Operator ====================
			map &operator=(map const &x)
			{
				if (this != &x)
				{
					this->_comp = x._comp;
					this->_alloc = x._alloc;
					this->_tree = x._tree;
				}
				return *this;
			}
		// ==================== Accessors ====================
			bool empty() const { return _tree.size() == 0; }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _tree.max_size(); }
			allocator_type get_allocator() const { return this->_alloc; }
			key_compare key_comp() const { return this->_comp; }
			value_compare value_comp() const { return value_compare(); }
		// ==================== Iterators ====================
			iterator begin(){ return _tree.begin(); }
			const_iterator begin() const { return _tree.begin(); }
			iterator end(){ return _tree.end(); }
			const_iterator end() const { return _tree.end(); }
			reverse_iterator rbegin(){ return _tree.rbegin(); }
			const_reverse_iterator rbegin() const { return _tree.rbegin(); }
			reverse_iterator rend(){ return _tree.rend(); }
			const_reverse_iterator rend() const { return _tree.rend(); }
		// ==================== Modifiers =====================
			void clear() { _tree.clear(); }
			void swap(map &x) { _tree.swap(x._tree); }
		// ===================== Find =======================
			// Search for element associated with key
			iterator find(const key_type &key)
			{
				value_type val(key, mapped_type());
				typename _redblacktree::rb_node* value;
				value = _tree.find(val);
				if (value == NULL)
					return this->end();
				else
					return iterator(value);
			}
			const_iterator find(const key_type &key) const
			{
				value_type val(key, mapped_type());
				typename _redblacktree::rb_node* value;
				value = _tree.find(val);
				if (value == NULL)
					return this->end();
				else
					return const_iterator(value);
			}
			// 1 if element is found, 0 otherwise
			size_type count(const key_type &key) const
			{
				value_type val(key, mapped_type());
				if (_tree.find(val) == NULL)
					return 0;
				else
					return 1;
			}
		};
		template <class Key, class T, class Compare, class Alloc>
		void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) { x.swap(y); }
}
#endif