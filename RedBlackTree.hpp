#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#define BLACK 0
#define RED 1

#pragma once
#include "Pair.hpp"

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

/*
	Insertion strategy (for a node Z = red):
	- 4 scenarios
		1. Z = root -> color Z black
		2. Z.uncle = red -> recolor Z.parent & Z.uncle && Z.grandparent
		3. Z.uncle = black (triangle formation with Z && Z.parent && Z.grandparent) -> rotate Z.parent
		4. Z.uncle = black (line formation with Z && Z.parent && Z.grandparent) -> rotate Z.grandparent && recolor new Z.parent & Z.grandparent
*/

template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
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
		typedef T value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
};
#endif