#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#define BLACK 0
#define RED 1
#define NIL 2

#pragma once
#include "Pair.hpp"
#include <memory>
#include <iostream>
#include <iomanip>
#include "MapIterator.hpp"
#include "ReverseIterator.hpp"
#include <functional>

/*
	RedBlackTree specificities:
	- self-balancing binary search tree
	- Nodes are red | black
	- Root & NIL nodes -> black
	- Red nodes have black children
	- All paths from a node to its NIL children have the same number of black nodes
	- longest path (alternating red and black) from root to NIL node is no more than twice as long as the shortest path (all black nodes)
	- 3 operations: insert, delete, search, time complexity: O(log n)
	- rotation rearranges subtress -> changes structure -> decreases height -> increases performance (doesn't affect order), time complexity: O(1)
*/
template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class RedBlackTree
{
	public:
	// ==================== Typedefs ====================
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef Compare data_compare;
		typedef ft::MapIterator<RedBlackTree<T, Compare, Allocator>, false> iterator;
		typedef ft::MapIterator<RedBlackTree<T, Compare, Allocator>, true> const_iterator;
		typedef ft::ReverseIterator<iterator> reverse_iterator;
		typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;
	// ==================== RedBlackTree node structure ====================
		struct rb_node
		{
			rb_node* parent;
			rb_node* left;
			rb_node* right;
			value_type data;
			bool color; // 0 -> black | 1 -> red
			// ==================== Constructors ====================
			rb_node() : data(), parent(NULL), left(NULL), right(NULL), color(RED) {}
			rb_node(typename allocator_type::reference v) : data(v), parent(NULL), left(NULL), right(NULL), color(RED) {}
			rb_node(const rb_node& x) : data(x.data), parent(x.parent), left(x.left), right(x.right), color(x.color) {}
		};
	private:
		allocator_type _alloc;
		std::allocator<rb_node> _node_alloc;
		data_compare _comp;
		rb_node* _root;
		rb_node* _nil; // NIL node is used to represent the "End" of the tree (Not a real node)
	// ==================== Private functions ====================
		rb_node* create_node(const value_type& data = value_type())
		{
			rb_node* node = this->_node_alloc.allocate(1);
			this->_alloc.construct(&(node->data), data);
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			node->color = RED;
			return node;
		}
		// Deletes node = destroys data + deallocates memory
		void delete_node(rb_node* node)
		{
			if (node != NULL)
			{
				if (node == this->_root)
					this->_root = NULL;
				this->_alloc.destroy(&(node->data));
				this->_node_alloc.deallocate(node, 1);
			}
		}
		void new_nil()
		{
			this->_nil = this->create_node();
			this->_nil->color = NIL;
		}
		// Moves NIL node to end of the tree
		void move_nil()
		{
			rb_node* node = this->_root;
			while (node != NULL && node->right)
				node = node->right;
			if (node != NULL && node->right != this->_nil)
				node->right = this->_nil;
			this->_nil->parent = node;
		}
		// Hides NIL node (used when inserting and searching in the tree because NIL isn't a real node)
		void hide_nil()
		{
			if (this->_nil->parent != NULL)
				this->_nil->parent->right = NULL;
			this->_nil->parent = NULL;
		}
		// Cool recursive functions
		size_t size_from_node(rb_node* node) const
		{
			if (node != NULL && node != this->_nil)
				return(size_from_node(node->left) + size_from_node(node->right) + 1);
			return 0;
		}
		void clear_from_node(rb_node* node)
		{
			if (node != NULL && node != this->_nil)
			{
				clear_from_node(node->left);
				clear_from_node(node->right);
				this->delete_node(node);
			}
		}
		// Print binary tree in a nice way :D
		void printBT(const std::string& prefix, const rb_node* node, bool isLeft) const
		{
			if (node != nullptr)
			{
				std::cout << prefix;
				std::cout << (isLeft ? "|--" : "L--");
				std::cout << node->data;
				std::cout << (node->color == RED ? "R" : (node->color == BLACK ? "B" : "N")) << std::endl;
				printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
				printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
			}
		}
	// ==================== RedBlackTree Rotations ====================
		void rotate_right(rb_node* X)
		{
			rb_node* Y = X->left;
			X->left = Y->right;
			if (Y->right != NULL)
				Y->right->parent = X;
			Y->parent = X->parent;
			if (X->parent == NULL)
				this->_root = Y;
			else if (is_right_child(X))
				X->parent->right = Y;
			else
				X->parent->left = Y;
			Y->right = X;
			X->parent = Y;
		}
		void rotate_left(rb_node* X)
		{
			rb_node* Y = X->right;
			X->right = Y->left;
			if (Y->left != NULL)
				Y->left->parent = X;
			Y->parent = X->parent;
			if (X->parent == NULL)
				this->_root = Y;
			else if (is_left_child(X))
				X->parent->left = Y;
			else
				X->parent->right = Y;
			Y->left = X;
			X->parent = Y;
		}
	// ==================== Node family ====================
		rb_node* parent(rb_node* node) const
		{
			if (node != NULL)
				return node->parent;
			return NULL;
		}
		rb_node* grandparent(rb_node* node)
		{
			if (node && node->parent && node->parent->parent)
				return node->parent->parent;
			return NULL;
		}
		rb_node* uncle(rb_node* node)
		{
			rb_node* g = grandparent(node);
			if (g == NULL)
				return NULL;
			if (node->parent == g->left)
				return g->right;
			else
				return g->left;
		}
		rb_node* sibling(rb_node* node)
		{
			if (node == node->parent->left)
				return node->parent->right;
			else
				return node->parent->left;
		}
		bool is_left_child(rb_node* node)
		{
			if (node && node->parent)
				return node == node->parent->left;
			return false;
		}
		bool is_right_child(rb_node* node)
		{
			if (node && node->parent)
				return node == node->parent->right;
			return false;
		}
	// ==================== RedBlackTree modifications ====================
		void recolor(rb_node* node)
		{
			if (node->color == BLACK)
				node->color = RED;
			node->color = BLACK;
		}
		void switch_node(rb_node* base_node, rb_node* switch_node)
		{
			// base_node parent points to switch_node after this
			if (base_node == this->_root)
				this->_root = switch_node;
			else if (base_node == base_node->parent->left)
				base_node->parent->left = switch_node;
			else
				base_node->parent->right = switch_node;
			// switch_node points to base_node parent after this
			if (switch_node != NULL)
				switch_node->parent = base_node->parent;
		}
		/*
			Insertion fix strategy (for a node Z = red):
			- 4 scenarios
				1. Z = root -> color Z black
				2. Z.uncle = red -> recolor Z.parent & Z.uncle && Z.grandparent
				3. Z.uncle = black (triangle formation with Z && Z.parent && Z.grandparent) -> rotate Z.parent
				4. Z.uncle = black (line formation with Z && Z.parent && Z.grandparent) -> rotate Z.grandparent && recolor new Z.parent & Z.grandparent
		*/
		void insertion_tree_fix(rb_node* Z) // From Z to _root
		{
			while (parent(Z)->color == RED)
			{
				if (is_right_child(parent(Z)))
				{
					if (uncle(Z) && uncle(Z)->color == RED) // scenario 2
					{
						uncle(Z)->color = BLACK;
						parent(Z)->color = BLACK;
						grandparent(Z)->color = RED;
						Z = grandparent(Z);
					}
					else // scenario 3 && 4
					{
						if (is_left_child(Z))
						{
							Z = parent(Z);
							rotate_right(Z);
						}
						parent(Z)->color = BLACK;
						grandparent(Z)->color = RED;
						rotate_left(grandparent(Z));
					}
				}
				else // mirror scenarios
				{
					if (uncle(Z) && uncle(Z)->color == RED) // 2
					{
						uncle(Z)->color = BLACK;
						parent(Z)->color = BLACK;
						grandparent(Z)->color = RED;
						Z = grandparent(Z);
					}
					else // 3 && 4
					{
						if (is_right_child(Z))
						{
							Z = parent(Z);
							rotate_left(Z);
						}
						parent(Z)->color = BLACK;
						grandparent(Z)->color = RED;
						rotate_right(grandparent(Z));
					}
				}
				if (Z == this->_root)
					break;
			}
			this->_root->color = BLACK;
		}
		/* 
			Deletion fix strategy (only for a node Z = black):
			- 5 scenarios
				1. Z = root -> done
				2. Z.sibling = red -> recolor Z.sibling && Z.parent = red && rotate_left Z.parent && Z.sibling = Z.parent.right
				3. Z.sibling = black && Z.sibling.left = black && Z.sibling.right = black -> recolor Z.sibling && Z = Z.parent
				4. Z.sibling = black && Z.sibling.left = red && Z.sibling.right = black -> recolor Z.sibling && Z.sibling.left = black && rotate_right Z.sibling && Z.sibling = Z.parent.right
				5. Z.sibling = black && Z.sibling.right = red -> recolor Z.sibling = Z.parent.color && Z.parent.color = black && Z.sibling.right.color = black && rotate_left Z.parent && Z = root
		*/
		void deletion_tree_fix(rb_node* Z) // From Z to _root
		{
			if (Z != NULL)
			{
				while (Z != this->_root && Z->color == BLACK) // scenario 1 is automatically handled
				{
					if (is_left_child(Z))
					{
						rb_node* S = sibling(Z);
						if (S->color == RED) // scenario 2
						{
							S->color = BLACK;
							parent(Z)->color = RED;
							rotate_left(parent(Z));
							S = parent(Z)->right;
						}
						if (S->left->color == BLACK && S->right->color == BLACK) // scenario 3
						{
							S->color = RED;
							Z = parent(Z);
						}
						else // scenario 4 && 5
						{
							if (S->right->color == BLACK) // 4
							{
								S->left->color = BLACK;
								S->color = RED;
								rotate_right(S);
								S = parent(Z)->right;
							}
							S->color = parent(Z)->color; // 5
							parent(Z)->color = BLACK;
							S->right->color = BLACK;
							rotate_left(parent(Z));
							Z = this->_root;
						}
					}
					else // mirror scenarios
					{
						rb_node* S = sibling(Z);
						if (S->color == RED) // 2
						{
							S->color = BLACK;
							parent(Z)->color = RED;
							rotate_right(parent(Z));
							S = parent(Z)->left;
						}
						if (S->left->color == BLACK && S->right->color == BLACK) // 3
						{
							S->color = RED;
							Z = parent(Z);
						}
						else // 4 && 5
						{
							if (S->left->color == BLACK) // 4
							{
								S->right->color = BLACK;
								S->color = RED;
								rotate_left(S);
								S = parent(Z)->left;
							}
							S->color = parent(Z)->color; // 5
							parent(Z)->color = BLACK;
							S->left->color = BLACK;
							rotate_right(parent(Z));
							Z = this->_root;
						}
					}
				}
				Z->color = BLACK;
			}
		}
		// ==================== Comparison ====================
		bool inferior(const value_type& a, const value_type& b) const { return this->_comp(a, b); }
		bool superior(const value_type& a, const value_type& b) const { return this->_comp(b, a); }
		bool equal(const value_type& a, const value_type& b) const { return (!this->_comp(a, b) && !this->_comp(b, a)); }
	public :
		// ==================== Constructors ====================
		RedBlackTree(const data_compare& compare = data_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _node_alloc(), _comp(compare), _root(NULL), _nil(NULL) { this->new_nil(); }
		RedBlackTree(const RedBlackTree<T, Compare, Allocator>& rbt): _alloc(rbt._alloc), _node_alloc(rbt._node_alloc), _comp(rbt._comp), _root(NULL), _nil(NULL)
		{
			this->new_nil();
			for (const_iterator it = rbt.begin(); it != rbt.end(); ++it)
				this->insert(*it);
		}
		// ==================== Destructor ====================
		~RedBlackTree()
		{
			this->clear();
			this->delete_node(this->_nil);
		}
		// ==================== (=) Operator ====================
		RedBlackTree<T, Compare, Allocator>& operator=(const RedBlackTree<T, Compare, Allocator>& rbt)
		{
			if (this != &rbt)
			{
				this->clear();
				this->_comp = rbt._comp;
				this->_alloc = rbt._alloc;
				this->_node_alloc = rbt._node_alloc;
				this->_root = NULL;
				this->new_nil();
				for (const_iterator it = rbt.begin(); it != rbt.end(); ++it)
					this->insert(*it);
				this->move_nil();
			}
			return (*this);
		}
		// ==================== Accessors ====================
		size_t max_size() const { return _node_alloc.max_size(); }
		const rb_node* getRoot() const { return this->_root; }
		const rb_node* getNil() const { return this->_nil; }
		size_t size() const	{ return this->size_from_node(this->_root); }
		allocator_type get_allocator() const { return allocator_type(); }
		rb_node* first() const
		{
			rb_node* tmp = this->_root;
			while (tmp != NULL && tmp->left != NULL)
				tmp = tmp->left;
			return tmp;
		}
		rb_node* last() const
		{
			rb_node* tmp = this->_root;
			while (tmp != NULL && tmp->right != NULL)
				tmp = tmp->right;
			return tmp;
		}
		iterator begin()
		{
			rb_node* tmp = this->first();
			if (tmp != NULL)
				return iterator(tmp);
			return iterator(this->end());
		}
		const_iterator begin() const
		{
			rb_node* tmp = this->first();
			if (tmp != NULL)
				return const_iterator(tmp);
			return const_iterator(this->end());
		}
		iterator end() { return iterator(this->_nil); }
		const_iterator end() const { return const_iterator(this->_nil); }
		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }
		// ==================== Modifiers =====================
		/*
			https://stackoverflow.com/questions/3381867/iterating-over-a-map
			to iterate over a map we can :
			- use the recursive implementation of the in-order traversal
				1. simple
				2. iterator would have to maintain a stack in order to be able to go back to the parent (keeping track of current node's path)
			- use the iterative implementation of the in-order traversal
				1. more complex
				2. no need to maintain a stack (speed go brrrr)
		*/
		template <class Node>
		static rb_node* successor_in_order(Node* current)
		{
			if (current == NULL)
				return (NULL);
			if (current->right != NULL) // node has right child -> traverse link to child then go left as far as we can (smallest value in right subtree)
			{
				current = current->right;
				while (current->left != NULL)
					current = current->left;
			}
			else // node is on the furthest right of it's subtree, up until find a left child node, successor is this node's parent
			{
				while (current->parent != NULL && current == current->parent->right)
					current = current->parent;
				current = current->parent;
			}
			return (current);
		}
		template <class Node>
		static rb_node* predecessor_in_order(Node* current)
		{
			if (current == NULL)
				return (NULL);
			if (current->left != NULL)
			{
				current = current->left;
				while (current->right != NULL)
					current = current->right;
			}
			else
			{
				while (current->parent != NULL && current == current->parent->left)
					current = current->parent;
				current = current->parent;
			}		
			return (current);
		}	
		void swap(RedBlackTree<T, Compare, Allocator>& other)
		{
			std::swap(this->_root, other._root);
			std::swap(this->_nil, other._nil);
			std::swap(this->_comp, other._comp);
			std::swap(this->_alloc, other._alloc);
			std::swap(this->_node_alloc, other._node_alloc);
		}
		void print() const
		{
			if (this->_root == NULL)
				std::cout << "Empty tree" << std::endl;
			else
				this->printBT("", this->_root, false);
			std::cout << "======================" << std::endl;
		}
		rb_node* find(const value_type& val) const
		{
			if (this->equal(val, this->_root->data) || this->_root == NULL)
				return this->_root;
			rb_node* tmp = this->_root;
			while (tmp != NULL)
			{
				if (this->equal(val, tmp->data))
					return tmp;
				else if (this->inferior(val, tmp->data))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (tmp == this->_nil)
				return NULL;
			return tmp;
		}
		bool insert(const value_type& val)
		{
			rb_node* Z = this->create_node(val);
			this->hide_nil();
			if (this->_root == NULL) // empty tree
			{
				Z->color = BLACK;
				this->_root = Z;
				this->move_nil();
				return true;
			}
			rb_node* tmp = this->_root;
			rb_node* parent = NULL;
			while (tmp != NULL)
			{
				parent = tmp;
				if (this->equal(Z->data, tmp->data))
				{ // (map has unique keys -> no duplicates)
					this->move_nil();
					return false;
				}
				else if (this->inferior(Z->data, tmp->data))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			// relation kid -> parent
			Z->parent = parent;
			// relation parent -> kid
			if (this->inferior(Z->data, parent->data))
				parent->left = Z;
			else
				parent->right = Z;
			this->insertion_tree_fix(Z);
			this->move_nil();
			return true;
		}
		void remove(rb_node* node)
		{
			if (node != NULL)
			{
				this->hide_nil();
				int color = node->color;
				rb_node* tmp = NULL;
				if (node->left == NULL && node->right == NULL) // max 1 child
					this->switch_node(node, NULL);
				else if (node->right == NULL) // only left child
				{
					tmp = node->left;
					this->switch_node(node, node->left);
				}
				else if (node->left == NULL) // only right child
				{
					tmp = node->right;
					this->switch_node(node, node->right);
				}
				else // 2 children
				{
					rb_node* successor = this->successor_in_order(node); // successor will replace node
					color = successor->color;
					tmp = successor->right;
					if (successor->parent != node)
					{
						this->switch_node(successor, successor->right);
						successor->right = node->right;
						successor->right->parent = successor;
					}
					this->switch_node(node, successor);
					successor->left = node->left;
					successor->left->parent = successor;
					successor->color = node->color;
				}
				this->delete_node(node);
				if (color == BLACK)
					this->deletion_tree_fix(tmp);
				this->move_nil();
			}
		}
		void remove(const T& val) { this->remove(this->find(val)); }
		void clear()
		{
			this->clear_from_node(this->_root);
			this->_nil->parent = NULL;
			this->_root = NULL;
		}
};
#endif