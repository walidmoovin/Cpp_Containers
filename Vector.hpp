#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once
#include "VectorIterator.hpp"
#include "ReverseIterator.hpp"

/* vector specificities:
	- Sequence (ordered)
	- Random access
	- Allocator-aware
*/
namespace ft
{
	// ====================  Vector  ====================
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{

		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef T &reference;
			typedef const T &const_reference;
			typedef T *pointer;
			typedef const T *const_pointer;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef ft::VectorIterator<T, false> iterator;
			typedef ft::VectorIterator<T, true> const_iterator;
			typedef ft::ReverseIterator<iterator> reverse_iterator;
			typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;

			// ====================  Constructors  ====================
			// Empty
			explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _data(NULL){};
			// Fill
			explicit vector(size_t n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _data(_alloc.allocate(n))
			{
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_data + i, val);
			};
			// Range
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _data(NULL)
			{
				assign(first, last);
			};
			// Copy
			vector(const vector &x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _data(_alloc.allocate(x._capacity))
			{
				for (size_t i = 0; i < x._size; i++)
					_alloc.construct(_data + i, x._data[i]);
			};
			// ====================  Destructors  ====================
			~vector()
			{
				clear();
				_alloc.deallocate(_data, _capacity);
			};
			// ====================  Accessors  ====================
			allocator_type get_allocator() const { return _alloc; };
			size_t size() const { return _size; };
			size_t max_size() const { return _alloc.max_size(); };
			size_t capacity() const { return _capacity; };
			bool empty() const { return _size == 0; };
			// ==================== (=) Operator ====================
			vector &operator=(const vector &x)
			{
				if (this != &x)
				{
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
					_alloc = x._alloc;
					_size = x._size;
					_capacity = x._capacity;
					_data = _alloc.allocate(x._capacity);
					for (size_t i = 0; i < x._size; i++)
						_alloc.construct(_data + i, x._data[i]);
				}
				return *this;
			};
			// ====================  Iterators  ====================
			iterator begin() { return iterator(_data); };
			const_iterator begin() const { return const_iterator(_data); };

			iterator end() { return iterator(_data + _size); };
			const_iterator end() const { return const_iterator(_data + _size); };

			reverse_iterator rbegin() { return reverse_iterator(_data + _size); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_data + _size); };

			reverse_iterator rend() { return reverse_iterator(_data); };
			const_reverse_iterator rend() const { return const_reverse_iterator(_data); };
			// ====================  Capacity  ====================
			// Request a change in capacity
			void reserve(size_t n)
			{
				if (n > _capacity)
				{
					pointer tmp = _alloc.allocate(n);
					for (size_t i = 0; i < _size; i++)
						_alloc.construct(tmp + i, _data[i]);
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
					_data = tmp;
					_capacity = n;
				}
			};
			// Resize the container
			void resize(size_t n, value_type val = value_type())
			{
				if (n > _capacity)
					reserve(n);
				if (n > _size)
				{
					for (size_t i = _size; i < n; i++)
						_alloc.construct(_data + i, val);
				}
				else if (n < _size)
				{
					for (size_t i = n; i < _size; i++)
						_alloc.destroy(_data + i);
				}
				_size = n;
			};
			// ====================  Element accerss  ====================
			// no check if out of range, undefined behavior. (faster)
			reference operator[](size_t n) { return _data[n]; };
			const_reference operator[](size_t n) const { return _data[n]; };
			// check if out of range, throw exception. (slower)
			reference at(size_t n)
			{
				if (n >= _size)
					throw std::out_of_range("vector::at : index out of range");
				return _data[n];
			};
			const_reference at(size_t n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector::at : index out of range");
				return _data[n];
			};
			// First element
			reference front() { return _data[0]; };
			const_reference front() const { return _data[0]; };
			// Last element
			reference back() { return _data[_size - 1]; };
			const_reference back() const { return _data[_size - 1]; };
			// ====================  Modifiers  ====================
			// Assign content (fill)
			void assign(size_t n, const value_type &val)
			{
				clear();
				for (size_t i = 0; i < n; i++)
					push_back(val);
			};
			// Assign content (range)
			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last)
			{
				clear();
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
			};
			// Add element at end
			void push_back(const value_type &val)
			{
				if (_capacity == 0)
					reserve(1);
				if (_size == _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_data + _size, val);
				_size++;
			};
			// Remove last element
			void pop_back()
			{
				if (_size > 0)
				{
					_alloc.destroy(_data + _size - 1);
					_size--;
				}
			};
			// Remove all
			void clear()
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_size = 0;
			};
			// Swap content
			void swap(vector &x)
			{
				pointer tmp = _data;
				_data = x._data;
				x._data = tmp;
				size_t tmp2 = _size;
				_size = x._size;
				x._size = tmp2;
				tmp2 = _capacity;
				_capacity = x._capacity;
				x._capacity = tmp2;
				allocator_type tmp3 = _alloc;
				_alloc = x._alloc;
				x._alloc = tmp3;
			};
			// Insert (1)
			iterator insert(iterator position, const value_type &val)
			{
				size_t pos = position - begin();
				if (_size == 0)
					reserve(1);
				if (_size == _capacity)
					reserve(_capacity * 2);
				for (size_t i = _size; i > pos; i--)
					_alloc.construct(_data + i, _data[i - 1]);
				_alloc.construct(_data + pos, val);
				_size++;
				return iterator(_data + pos);
			};
			// Insert (fill)
			void insert(iterator position, size_t n, const value_type &val)
			{
				size_t pos = position - begin();
				if (_size + n > _capacity)
					reserve(_size + n);
				for (size_t i = _size; i > pos; i--)
					_alloc.construct(_data + i + n - 1, _data[i - 1]);
				for (size_t i = pos; i < pos + n; i++)
					_alloc.construct(_data + i, val);
				_size += n;
			};
			// Insert (range)
			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type insert(iterator position, InputIterator first, InputIterator last)
			{
				size_t pos = position - begin();
				size_t n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				if (_size + n > _capacity)
					reserve(_size + n);
				for (size_t i = _size; i > pos; i--)
					_alloc.construct(_data + i + n - 1, _data[i - 1]);
				for (size_t i = pos; i < pos + n; i++)
				{
					_alloc.construct(_data + i, *first);
					first++;
				}
				_size += n;
			};
			// Erase (1)
			iterator erase(iterator position)
			{
				size_t pos = position - begin();
				_alloc.destroy(_data + pos);
				for (size_t i = pos; i < _size - 1; i++)
					_alloc.construct(_data + i, _data[i + 1]);
				_size--;
				return iterator(_data + pos);
			};
			// Erase (range)
			iterator erase(iterator first, iterator last)
			{
				size_t pos = first - begin();
				size_t n = last - first;
				for (size_t i = pos; i < pos + n; i++)
					_alloc.destroy(_data + i);
				for (size_t i = pos; i < _size - n; i++)
					_alloc.construct(_data + i, _data[i + n]);
				_size -= n;
				return iterator(_data + pos);
			};
		private:
			allocator_type _alloc;
			size_t _size;
			size_t _capacity;
			value_type *_data;
	};
	// ==================== Relational operators ====================
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	};
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return true;
		return false;
	};
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size())
		{
			if (lhs[i] < rhs[i])
				return true;
			else if (lhs[i] > rhs[i])
				return false;
			i++;
		}
		if (i == lhs.size() && i != rhs.size())
			return true;
		return false;
	};

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size())
		{
			if (lhs[i] < rhs[i])
				return true;
			else if (lhs[i] > rhs[i])
				return false;
			i++;
		}
		if (i == lhs.size() && i != rhs.size())
			return true;
		if (i == lhs.size() && i == rhs.size())
			return true;
		return false;
	};
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size())
		{
			if (lhs[i] < rhs[i])
				return false;
			else if (lhs[i] > rhs[i])
				return true;
			i++;
		}
		if (i != lhs.size() && i == rhs.size())
			return true;
		return false;
	};
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size())
		{
			if (lhs[i] < rhs[i])
				return false;
			else if (lhs[i] > rhs[i])
				return true;
			i++;
		}
		if (i != lhs.size() && i == rhs.size())
			return true;
		if (i == lhs.size() && i == rhs.size())
			return true;
		return false;
	};
	// Swap
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	};
}

#endif