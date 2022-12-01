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
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef Compare key_compare;
			struct pair_compair
			{
				bool operator()(value_type const lhs, value_type const rhs) const
				{
					Compare comp;
					return comp(lhs.first, rhs.first);
				}
			};
		private:
			typedef RedBlackTree<ft::pair<const Key, T>, pair_compair, Alloc>	_redblacktree;
		public:
			typedef pair_compair pair_compair;
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
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _comp(comp), _alloc(alloc), _tree() { }
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree() { while (first != last) this->_tree.insert(*first++); }
			map(map const &x): _comp(x._comp), _alloc(x._alloc), _tree(x._tree) { }
			~map() { }
		// ==================== (=) Operator ====================
			map &operator=(const map &x)
			{
				this->_comp = x._comp;
				this->_alloc = x._alloc;
				this->_tree = x._tree;
				return *this;
			}
		// ==================== ([]) Operator =======================
			// Insert new element if key exist'nt
			mapped_type &operator[](key_type const &k)
			{
				return ((this->insert(ft::make_pair(k, mapped_type())).first)->second);
			}
		// ==================== Accessors ====================
			bool empty() const { return _tree.size() == 0; }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _tree.max_size(); }
			allocator_type get_allocator() const { return this->_alloc; }
			key_compare key_comp() const { return this->_comp; }
			pair_compair value_comp() const { return pair_compair(); }
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
			void swap(map& x)
			{
				key_compare tmp_comp = this->_comp;
				allocator_type tmp_alloc = this->_alloc;
				this->_comp = x._comp;
				this->_alloc = x._alloc;
				x._comp = tmp_comp;
				x._alloc = tmp_alloc;
				this->_tree.swap(x._tree);
			}
			// insert in all cases
			ft::pair<iterator, bool> insert(value_type const &val)
			{
				bool inserted = this->_tree.insert(val);
				return ft::make_pair(iterator(this->_tree.find(val)), inserted);
			}
			iterator insert(iterator position, value_type const &val) { (void)position; return this->insert(val).first; }
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) { while (first != last) this->insert(*first++); }
			size_type erase(key_type const &k)
			{
				size_type erased_count = 0;
				value_type tmp(k, mapped_type());
				if (this->_tree.find(tmp) != NULL)
				{
					this->_tree.remove(tmp);
					erased_count = 1;
				}
				return erased_count;
			}
			void erase(iterator position) { this->_tree.remove(*position); }
			// save next node before erase
			void erase(iterator first, iterator last)
			{
				iterator next;
				while (first != last)
				{
					next = first;
					++first;
					this->_tree.remove(*next);
				}
			}
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
			// simple explanation: if the key is not found, the lower bound is the first element that is greater than the key
			iterator lower_bound(const key_type& key)
			{
				typename _redblacktree::rb_node* curr = this->_tree.first();		
				while (curr != NULL && this->inferior(curr->data.first, key))
					curr = _redblacktree::successor_in_order(curr);
				if (curr == NULL || curr == this->_tree.getNil())
					return (this->end());
				return (iterator(curr));
			}
			const_iterator lower_bound(const key_type& key) const
			{
				typename _redblacktree::rb_node* curr = this->_tree.first();	
				while (curr != NULL && this->inferior(curr->data.first, key))
					curr = _redblacktree::successor_in_order(curr);
				if (curr == NULL || curr == this->_tree.getNil())
					return (this->end());
				return (const_iterator(curr));
			}
			iterator upper_bound(const key_type& key)
			{
				typename _redblacktree::rb_node* curr = this->_tree.first();		
				while (curr != NULL && !this->inferior(key, curr->data.first))
					curr = _redblacktree::successor_in_order(curr);
				if (curr == NULL || curr == this->_tree.getNil())
					return (this->end());
				return (iterator(curr));
			}
			const_iterator upper_bound(const key_type& key) const
			{
				
				typename _redblacktree::rb_node* curr = this->_tree.first();			
				while (curr != NULL && !this->inferior(key, curr->data.first))
					curr = _redblacktree::successor_in_order(curr);
				if (curr == NULL || curr == this->_tree.getNil())
					return (this->end());
				return (const_iterator(curr));
			}
			ft::pair<iterator, iterator> equal_range(const key_type& key)
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
			{
				return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
			}
	};
	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> &x, ft::map<Key, T, Compare, Alloc> &y) { x.swap(y); }
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return !(lhs == rhs); }
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it1 = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		while (it1 != lhs.end() && it2 != rhs.end())
		{
			if (*it1 < *it2)
				return true;
			else if (*it2 < *it1)
				return false;
			++it1;
			++it2;
		}
		if (it1 == lhs.end() && it2 != rhs.end())
			return true;
		return false;
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return !(rhs < lhs); }
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return rhs < lhs; }
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) { return !(lhs < rhs); }
}
#endif