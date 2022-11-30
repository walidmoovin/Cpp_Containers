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
		typedef Compare key_compare;
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
		key_compare _comp;
		rb_node* _root;
		rb_node* _nil; // NIL node is used to represent the "End" of the tree (Not a real node)
		// ==================== Private functions ====================
		rb_node* Z(const value_type& data = value_type())
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
			this->_nil = this->Z();
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
				std::cout << node->data << std::endl;
				printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
				printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
			}
		}
		// ==================== RedBlackTree Rotations ====================
		void rotate_right(rb_node* node)
		{
			rb_node* newNode = node->left;
			node->left = newNode->right;
			if (newNode->right != NULL)
				newNode->right->parent = node;
			newNode->parent = node->parent;
			if (node->parent == NULL)
				this->_root = newNode;
			else if (node == node->parent->right)
				node->parent->right = newNode;
			else
				node->parent->left = newNode;
			newNode->right = node;
			node->parent = newNode;
		}
		void rotate_left(rb_node* node)
		{
			rb_node* newNode = node->right;
			node->right = newNode->left;
			if (newNode->left != NULL)
				newNode->left->parent = node;
			newNode->parent = node->parent;
			if (node->parent == NULL)
				this->_root = newNode;
			else if (node == node->parent->left)
				node->parent->left = newNode;
			else
				node->parent->right = newNode;
			newNode->left = node;
			node->parent = newNode;
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
		// ==================== Comparison ====================
		bool inferior(const value_type& a, const value_type& b) const { return this->_comp(a, b); }
		bool superior(const value_type& a, const value_type& b) const { return this->_comp(b, a); }
		bool equal(const value_type& a, const value_type& b) const { return (!this->_comp(a, b) && !this->_comp(b, a)); }
	public :
		// ==================== Constructors ====================
		RedBlackTree(const key_compare& compare = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _node_alloc(), _comp(compare), _root(NULL), _nil(NULL) { this->new_nil(); }
		// ==================== Destructor ====================
		~RedBlackTree()
		{
			this->clear();
			this->delete_node(this->_nil);
		}
		// ==================== Accessors ====================
		size_t max_size() const { return this->std::allocator<rb_node>.max_size(); }
		const rb_node* getRoot() const { return this->_root; }
		const rb_node* getNil() const { return this->_nil; }
		size_t size() const	{ return this->size_from_node(this->_root); }
		allocator_type get_allocator() const { return allocator_type(); }
		rb_node* first() const
		{
			rb_node* tmp = this->_root;
			while (tmp->left != this->_nil)
				tmp = tmp->left;
			return tmp;
		}
		rb_node* last() const
		{
			rb_node* tmp = this->_root;
			while (tmp->right != this->_nil)
				tmp = tmp->right;
			return tmp;
		}
		// ==================== Modifiers ====================
		void swap(RedBlackTree<T, Compare, Allocator>& other)
		{
			std::swap(this->_root, other._root);
			std::swap(this->_size, other._size);
			std::swap(this->_comp, other._comp);
			std::swap(this->_alloc, other._alloc);
		}
		void print() const
		{
			if (this->_root == NULL)
				std::cout << "Empty tree" << std::endl;
			else
				this->printBT("", this->_root, false);
		}
		void insert (const value_type& val)
		{
			rb_node* Z = this->Z(val);
			this->hide_nil();
			if (this->_root == NULL) // empty tree
			{
				Z->color = BLACK;
				this->_root = Z;
				this->move_nil();
				return;
			}
			rb_node* tmp = this->_root;
			rb_node* parent = NULL;
			while (tmp != NULL)
			{
				parent = tmp;
				if (this->equal(val, tmp->data)) // (map has unique keys -> no duplicates)
					return;
				else if (this->inferior(val, tmp->data))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			// relation kid -> parent
			Z->parent = parent;
			// relation parent -> kid
			if (this->inferior(val, parent->data))
				parent->left = Z;
			else
				parent->right = Z;
			this->insertion_tree_fix(Z);
			this->move_nil();
		}
		void remove(const T& value) { this->remove(this->find(value)); }
		void clear()
		{
			this->clear_from_node(this->_root);
			this->_nil->parent = NULL;
			this->_root = NULL;
		}
};
#endif