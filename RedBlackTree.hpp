#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#define BLACK 0
#define RED 1
#define NIL 2

#pragma once
#include "Pair.hpp"
#include "memory"
#include "iostream"

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
		// ==================== Rbt node ====================
		struct rb_node
		{
			rb_node* parent;
			rb_node* left;
			rb_node* right;
			bool color; // 0 -> black | 1 -> red
			T data;
			// ==================== Constructors ====================
			rb_node() : parent(NULL), left(NULL), right(NULL), color(RED), data() {}
			rb_node(const T& data) : parent(NULL), left(NULL), right(NULL), color(RED), data(data) {}
			rb_node(const rb_node& x) : parent(x.parent), left(x.left), right(x.right), color(x.color), data(x.data) {}
		};
		// ==================== Typedefs ====================
		typedef rb_node* node_ptr;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		// ==================== Accessors ====================
		allocator_type get_allocator() const
		{
			return allocator_type();
		}
	private:
		std::allocator<rb_node> _node_alloc;
		Allocator _alloc;
		rb_node* _root;
		rb_node* _nil;
		Compare _comp;
		// Creates new node
		rb_node* new_node(const T& data = value_type())
		{
			rb_node* node = this->_alloc.allocate(1);
			_alloc.construct(&(node->data), data);
			node->color = RED;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			return node;
		}
		// Creates NIL node that is used to recognize end of tree
		rb_node* new_nil()
		{
			rb_node* node = this->_alloc.allocate(1);
			_alloc.construct(&(node->data), value_type());
			node->color = BLACK;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			return node;
		}
		// Moves NIL node to end of the tree
		void move_nil()
		{
			rb_node* node = this->_root;
			while (node && node->right != NULL)
				node = node->right;
			node->right = this->_nil;
			this->_nil->parent = node;
		}
		// Deletes node
		void delete_node(rb_node* node)
		{
			if (node)
			{
				_alloc.destroy(&(node->data));
				this->_alloc.deallocate(node, 1);
			}
		}
		// Rotates node X right
		void rotate_right(rb_node* X)
		{
			// Y = left child of X, X becomes right child of Y
			rb_node* Y = X->left;
			X->left = Y->right;

			// If Y.right != NIL, Y.right.parent = X
			if (Y->right != this->_nil)
				Y->right->parent = X;
			
			// reassign all links
			// Y.parent = X.parent
			Y->parent = X->parent;
			if (X->parent == this->_nil) // becomes root
				this->_root = Y;
			else if (X == X->parent->right)
				X->parent->right = Y;
			else
				X->parent->left = Y;

			// swap X & Y
			Y->right = X;
			X->parent = Y;
		}
		// Rotates node X left
		void rotate_left(rb_node* X)
		{
			// Y = right child of X, X becomes left child of Y
			rb_node* Y = X->right;
			X->right = Y->left;

			// If Y.left != NIL, Y.left.parent = X
			if (Y->left != this->_nil)
				Y->left->parent = X;

			// reassign all links
			// Y.parent = X.parent
			Y->parent = X->parent;
			if (X->parent == this->_nil) // becomes root
				this->_root = Y;
			else if (X == X->parent->left)
				X->parent->left = Y;
			else
				X->parent->right = Y;

			// swap X & Y
			Y->left = X;
			X->parent = Y;
		}
		rb_node* grandparent(rb_node* node)
		{
			if (node && node->parent)
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
		void recolor(rb_node* node)
		{
			if (node->color == BLACK)
				node->color == RED;
			node->color == BLACK;
			return;
		}
		void replace(rb_node* base, rb_node* replace)
		{
			// base parent points to replace after this
			if (base->parent == this->_nil)
				this->_root = replace;
			else if (base == base->parent->left)
				base->parent->left = replace;
			else
				base->parent->right = replace;
			// replace points to base parent after this
			replace->parent = base->parent;
		}
		void clear_from_node(rb_node* node)
		{
			if (node && node != this->_nil)
			{
				Clear(node->left);
				Clear(node->right);
				delete_node(node);
			}
		}
		size_type size_from_node(rb_node* node)
		{
			if (node == this->_nil || node == NULL)
				return 0;
			return 1 + Size(node->left) + Size(node->right);
		}
		/*
			Insertion fix strategy (for a node Z = red):
			- 4 scenarios
				1. Z = root -> color Z black
				2. Z.uncle = red -> recolor Z.parent & Z.uncle && Z.grandparent th
				3. Z.uncle = black (triangle formation with Z && Z.parent && Z.grandparent) -> rotate Z.parent
				4. Z.uncle = black (line formation with Z && Z.parent && Z.grandparent) -> rotate Z.grandparent && recolor new Z.parent & Z.grandparent
		*/
		// Tree fix after insertion
		void insertion_tree_fix(rb_node* Z) // starts from Z to root
		{
			while (Z->parent->color == RED)
			{
				if (Z == this->_root) // scenario 1
				{
					Z->color = BLACK;
					break;
				}
				if (is_right_child(Z->parent))
				{
					if (uncle(Z) && uncle(Z)->color == RED) // scenario 2
					{
						recolor(Z->parent);
						recolor(uncle(Z));
						recolor(grandparent(Z));
					}
					else
					{
						if (is_left_child(Z)) // scenario 3
						{
							rotate_right(Z->parent);
							Z = Z->right;
						}
						// scenario 4
						rotate_left(grandparent(Z));
						recolor(Z->parent);
						recolor(grandparent(Z));
					}
				}
				else
				{
					if (uncle(Z) && uncle(Z)->color == RED) // scenario 2
					{
						recolor(Z->parent);
						recolor(uncle(Z));
						recolor(grandparent(Z));
					}
					else
					{
						if (is_right_child(Z)) // scenario 3
						{
							rotate_left(Z->parent);
							Z = Z->left;
						}
						// scenario 4
						rotate_right(grandparent(Z));
						recolor(Z->parent);
						recolor(grandparent(Z));
					}
				}
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
		// Tree fix after deletion
		void deletion_tree_fix(rb_node* Z) // starts from Z to root
		{
			if (Z == NULL)
				return;
			if (Z == this->_root) // scenario 1
				return;
			while (Z != this->_root && Z->color == BLACK)
			{
				if (is_left_child(Z))
				{
					if (sibling(Z)->color == RED) // scenario 2
					{
						recolor(sibling(Z));
						recolor(Z->parent);
						rotate_left(Z->parent);
						Z->sibling = Z->parent->right;
					}
					else if (sibling(Z)->left->color == BLACK && sibling(Z)->right->color == BLACK) // scenario 3
					{
						recolor(sibling(Z));
						Z = Z->parent;
					}
					else
					{
						if (sibling(Z)->right->color == BLACK) // scenario 4
						{
							recolor(sibling(Z));
							recolor(sibling(Z)->left);
							rotate_right(sibling(Z));
							sibling(Z) = Z->parent->right;
						}
						// scenario 5
						sibling(Z)->color = Z->parent->color;
						Z->parent->color = BLACK;
						sibling(Z)->right->color = BLACK;
						rotate_left(Z->parent);
						Z = this->_root;
					}
				}
				else
				{
					if (sibling(Z)->color == RED) // scenario 2
					{
						recolor(sibling(Z));
						recolor(Z->parent);
						rotate_right(Z->parent);
						sibling(Z) = Z->parent->left;
					}
					else if (sibling(Z)->right->color == BLACK && sibling(Z)->left->color == BLACK) // scenario 3
					{
						recolor(sibling(Z));
						Z = Z->parent;
					}
					else
					{
						if (sibling(Z)->left->color == BLACK) // scenario 4
						{
							recolor(sibling(Z));
							recolor(sibling(Z)->right);
							rotate_left(sibling(Z));
							sibling(Z) = Z->parent->left;
						}
						// scenario 5
						sibling(Z)->color = Z->parent->color;
						Z->parent->color = BLACK;
						sibling(Z)->left->color = BLACK;
						rotate_right(Z->parent);
						Z = this->_root;
					}
				}
			}
			Z->color = BLACK;
		}
		bool inferior(const T& a, const T& b) const
		{
			return (this->_comp(a, b));
		}
		bool superior(const T& a, const T& b) const
		{
			return (this->_comp(b, a));
		}
		bool equal(const T& a, const T& b) const
		{
			return (!this->_comp(a, b) && !this->_comp(b, a));
		}
		public :
		// ==================== Constructors ====================
		// Default
		RedBlackTree() : _root(NULL), _nil(NULL), _alloc(allocator_type()), _comp(key_compare())
		{
			this->new_nil();
		}
		// Copy
		RedBlackTree(RedBlackTree<T, Compare, Allocator> &other) : _alloc(other._alloc), _node_alloc(other._node_alloc), _comp(other._comp), _root(NULL), _nil(NULL)
		{
			this->new_nil();
			for (const_iterator it = other.begin(); it != other.end(); it++)
				this->insert(*it);
		}
		// ==================== Destructor ====================
		~RedBlackTree()
		{
			this->clear();
			this->delete_node(this->_nil);
		}
		// ==================== Accessors ====================
		size_type max_size() const
		{
			return (this->std::allocator<rb_node>.max_size());
		}
		const rb_node* getRoot() const
		{
			return (this->_root);
		}
		const rb_node* getNil() const
		{
			return (this->_nil);
		}
		rb_node* first() const
		{
			rb_node* tmp = this->_root;
			while (tmp->left != this->_nil)
				tmp = tmp->left;
			return (tmp);
		}
		rb_node* last() const
		{
			rb_node* tmp = this->_root;
			while (tmp->right != this->_nil)
				tmp = tmp->right;
			return (tmp);
		}
		size_type size() const
		{
			return (this->size_from_node(this->_root));
		}
		// ==================== Modifiers ====================
		void swap(RedBlackTree<T, Compare, Allocator>& other)
		{
			std::swap(this->_root, other._root);
			std::swap(this->_size, other._size);
			std::swap(this->_comp, other._comp);
			std::swap(this->_alloc, other._alloc);
		}
		void remove(const T& value)
		{
			this->remove(this->find(value));
		}
		void clear()
		{
			this->clear_from_node(this->_root);
			this->_nil->parent = NULL;
			this->_root = NULL;
		}
};
#endif