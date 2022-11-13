#pragma once
#include <iostream>
#include <memory>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class Vector
	{
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;	

		public:
			// ====================  CONSTRUCTORS  ====================
			// EMPTY CONSTRUCTOR
			explicit Vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _data(NULL){};

			// FILL CONSTRUCTOR
			explicit Vector(size_t n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _data(_alloc.allocate(n)){
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_data + i, val);
			};

			// RANGE CONSTRUCTOR
			template <class InputIterator>
			Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

			// COPY CONSTRUCTOR
			Vector(const Vector &x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _data(_alloc.allocate(x._capacity)){
				for (size_t i = 0; i < x._size; i++)
					_alloc.construct(_data + i, x._data[i]);
			};

			// ====================  DESTRUCTOR  ====================
			~Vector(){
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
			};

			// ====================  ACCESSORS  ====================
			allocator_type get_allocator() const{ return _alloc; };
			size_t size() const{ return _size; };
			size_t max_size() const{ return _alloc.max_size(); };
			size_t capacity() const{ return _capacity; };
			bool empty() const{ return _size == 0; };

			// ====================  MUTATORS  ====================
			// ASSIGNATION OPERATOR
			Vector &operator=(const Vector &x){
				if (this != &x){
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

			// ====================  ITERATORS  ====================
			iterator begin(){ return iterator(_data); };

			iterator end(){ return iterator(_data + _size); };

			reverse_iterator rbegin(){ return reverse_iterator(_data + _size - 1); };

			reverse_iterator rend(){ return reverse_iterator(_data - 1); };                                                                             

			// ====================  CAPACITY  ====================
			// REQUEST A CHANGE IN CAPACITY
			void reserve(size_t n){
				if (n > _capacity){
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

			// CONTAINER RESIZE
			void resize(size_t n, value_type val = value_type()){
				if (n > _capacity)
					reserve(n);
				if (n > _size){
					for (size_t i = _size; i < n; i++)
						_alloc.construct(_data + i, val);
				}
				else if (n < _size){
					for (size_t i = n; i < _size; i++)
						_alloc.destroy(_data + i);
				}
				_size = n;
			};

			// ====================  ELEMENT ACCESS  ====================
			// ACCESS ELEMENT, no check if out of range, undefined behavior. (faster)
			reference operator[](size_t n){ return _data[n]; };
			const_reference operator[](size_t n) const{ return _data[n]; };

			// ACCESS ELEMENT, check if out of range, throw exception. (slower)
			reference at(size_t n){
				if (n >= _size)
					throw std::out_of_range("Vector::at : index out of range");
				return _data[n];
			};
			const_reference at(size_t n) const{
				if (n >= _size)
					throw std::out_of_range("Vector::at : index out of range");
				return _data[n];
			};

			// ACCESS FIRST ELEMENT
			reference front(){ return _data[0]; };
			const_reference front() const{ return _data[0]; };

			// ACCESS LAST ELEMENT
			reference back(){ return _data[_size - 1]; };
			const_reference back() const{ return _data[_size - 1]; };

			// ====================  MODIFIERS  ====================
			// ADD ELEMENT AT THE END
			void push_back(const value_type &val){
				if (_size == _capacity)
					reserve(_capacity * 2);
				std::cout << "debug : " << _size << std::endl;
				_alloc.construct(_data + _size, val);
				_size++;
			};
			// REMOVE LAST ELEMENT
			void pop_back(){
				_alloc.destroy(_data + _size - 1);
				_size--;
			};
			// REMOVE ALL ELEMENTS
			void clear(){
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_size = 0;
			};
			// SWAP CONTENTS OF TWO VECTORS
			void swap(Vector &x){
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
			// INSERT SINGLE ELEMENT
			iterator insert(iterator position, const value_type &val){
				size_t pos = position - begin();
				if (_size == _capacity)
					reserve(_capacity * 2);
				for (size_t i = _size; i > pos; i--)
					_alloc.construct(_data + i, _data[i - 1]);
				_alloc.construct(_data + pos, val);
				_size++;
				return iterator(_data + pos);
			};
			// INSERT FILL	
			void insert(iterator position, size_t n, const value_type &val){
				size_t pos = position - begin();
				if (_size + n > _capacity)
					reserve(_size + n);
				for (size_t i = _size; i > pos; i--)
					_alloc.construct(_data + i + n - 1, _data[i - 1]);
				for (size_t i = pos; i < pos + n; i++)
					_alloc.construct(_data + i, val);
				_size += n;
			};
			// INSERT RANGE
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last){
				size_t pos = position - begin();
				size_t n = last - first;
				if (_size + n > _capacity)
					reserve(_size + n);
				for (size_t i = _size; i > pos; i--)
					_alloc.construct(_data + i + n - 1, _data[i - 1]);
				for (size_t i = pos; i < pos + n; i++)
					_alloc.construct(_data + i, *first++);
				_size += n;
			};
		private:
			allocator_type _alloc;
			size_t _size;
			size_t _capacity;
			value_type *_data;
	};

	// ====================  NON-MEMBER FUNCTIONS OVERLOADS  ====================
	// RELATIONAL OPERATORS
	template <class T, class Alloc>
	bool operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs){
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	};

	template <class T, class Alloc>
	bool operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs){
		if (lhs.size() != rhs.size())
			return true;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return true;
	};

	template <class T, class Alloc>
	bool operator<(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs){
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()){
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
	bool operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs){
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()){
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
	bool operator>(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs){
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()){
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
	bool operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs){
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()){
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

	// ====================  SWAP ====================
	template <class T, class Alloc>
	void swap(Vector<T, Alloc> &x, Vector<T, Alloc> &y){
		x.swap(y);
	};
}
