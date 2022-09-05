/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/09/05 11:10:59 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm.hpp> //swap

#include "../util/macros.hpp" //SSTR
#include <sstream>			  //SSTR
#include "iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

	template <typename _Tp, typename _Alloc = std::allocator<_Tp> // bug indent
			  >
	class vector
	{
	public:
		typedef _Alloc allocator_type;

		typedef _Tp value_type;
		typedef typename allocator_type::pointer pointer;				  //_Tp *
		typedef typename allocator_type::const_pointer const_pointer;	  // const _Tp *
		typedef typename allocator_type::reference reference;			  //_Tp &
		typedef typename allocator_type::const_reference const_reference; // const _Tp &
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef ft::__normal_iterator<pointer, vector> iterator;
		typedef ft::__normal_iterator<const_pointer, vector> const_iterator;

		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;

	private:
		allocator_type _Tp_alloc_type;
		pointer _start;
		pointer _finish;
		pointer _end_of_storage;

		iterator _insert_range(iterator __position, const size_type __n, const value_type &__val)
		{
			iterator new_position = _resize_and_move_at_end(__position, __n);
			for (size_type i = 0; i < __n; i++)
				new_position = _insert_single(new_position, __val);
			return new_position;
		}

		iterator _insert_dispatch(iterator __position,
								  size_type __n,
								  value_type &__val,
								  true_type)
		{
			return _insert_range(__position, __n, __val);
		}

		template <typename _InputIterator1, typename _InputIterator2>
		iterator _insert_dispatch(_InputIterator1 __position,
								  _InputIterator2 __first,
								  _InputIterator2 __last,
								  false_type)
		{
			iterator new_position = _resize_and_move_at_end(__position, __last - __first);
			while (__first != __last)
			{
				new_position = _insert_single(new_position, *__first);
				__first++;
			}
			return new_position;
		}
		iterator _insert_single(iterator __position, const value_type &__x) // must reserve and move next first
		{
			*__position = __x;
			return ++__position;
		}
		iterator _resize_and_move_at_end(iterator __position, size_type __add)
		{
			size_type diff_end = this->end() - __position;
			size_type diff_start = __position - this->begin();
			if (capacity() < size() + __add)
				reserve(_next_capacity());
			iterator it_end = this->end();
			_finish += __add;
			pointer _current = _finish - 1;
			while (diff_end != 0)
			{
				diff_end--;
				it_end--;
				_Tp_alloc_type.construct(_current, *(it_end));
				_current--;
			}
			iterator position = begin();
			position += diff_start;
			return position;
		}

		size_type _next_capacity()
		{
			return (capacity() == 0 ? 1 : capacity() * 2);
		}
		template <typename _Integer>
		void _assign_dispatch(_Integer __n, _Integer __val, true_type)
		{
			if (__n < 0)
				return;
			size_type n = __n;
			if (capacity() >= n)
			{
				clear();
				_fill(__n, __val);
			}
			else
			{
				_destroy();
				_build(__n, __val);
			}
		}

		template <typename _InputIterator>
		void _assign_dispatch(_InputIterator __first, _InputIterator __last, false_type)
		{
			if ((__last - __first) < 0)
				return;
			size_type n = (__last - __first);
			if (capacity() >= n)
			{
				clear();
			}
			else
			{
				_destroy();
				reserve(n);
			}
			while (__first != __last)
				push_back(*__first++);
		}

		void _destroy()
		{
			// clear();
			_Tp_alloc_type.deallocate(_start, _end_of_storage - _start);
			_build(0);
		}

		void _build(size_type __n, const value_type &__value = value_type())
		{
			_create_storage(__n);
			_fill(__n, __value);
		}

		void _copy(iterator __begin, iterator __end)
		{
			while (__begin != __end)
			{
				push_back(*__begin);
				__begin++;
			}
		}

		void _fill(size_type __n, const value_type &__value = value_type())
		{
			for (size_type i = 0; i < __n; i++)
				push_back(__value);
		}

		template <typename _Integer>
		void _initialize_dispatch(_Integer __n, _Integer __value, true_type)
		{
			_build(__n, __value);
		}

		template <typename _InputIterator>
		void _initialize_dispatch(_InputIterator __first, _InputIterator __last,
								  false_type)
		{
			_create_storage(__last - __first);
			_copy(__first, __last);
		}

		pointer _allocate(size_t __n)
		{
			return __n != 0 ? _Tp_alloc_type.allocate(__n) : pointer();
		}
		void _create_storage(size_t __n)
		{
			_create_storage(this->_start,
							this->_finish,
							this->_end_of_storage, __n);
		}

		void _create_storage(pointer &_start,
							 pointer &_finish,
							 pointer &_end_of_storage, size_t __n)
		{
			_start = _allocate(__n);
			_finish = _start;
			_end_of_storage = _start + __n;
		}
		void _range_check(size_type __n) const
		{
			if (__n >= this->size())
				throw std::out_of_range(SSTR("vector::_range_check: __n (which is ") //
										+ SSTR(__n)									 //
										+ SSTR(" ) >= this->size() (which is ")		 //
										+ SSTR(this->size()) + SSTR(")"));			 //
		}

	public:
		/*
		** --------------------------------- CONSTRUCTORS --------------------------
		*/
		/*
		 * empty container constructor (default constructor)
		 * Constructs an empty container, with no elements.
		 */
		explicit vector(const allocator_type &__a = allocator_type())
			: _Tp_alloc_type(__a),
			  _start(),
			  _finish(),
			  _end_of_storage()
		{
		}

		/*
		 * fill constructor
		 * Constructs a container with n elements. Each element is a copy of val.
		 */
		explicit vector(size_type __n, const value_type &__value = value_type(),
						const allocator_type &__a = allocator_type())
			: _Tp_alloc_type(__a),
			  _start(),
			  _finish(),
			  _end_of_storage()
		{
			_initialize_dispatch(__n, __value, true_type());
		}
		/*
		 * range constructor
		 * Constructs a container with as many elements as the range [first,last),
		 * with each element constructed from its corresponding element in that
		 * range, in the same order.
		 */

		template <typename _InputIterator>
		vector(_InputIterator __first, _InputIterator __last,
			   const allocator_type &__a = allocator_type())
			: _Tp_alloc_type(__a)
		{
			typedef typename ft::is_integral<_InputIterator>::type _Integral;
			_initialize_dispatch(__first, __last, _Integral());
		}
		/*
		 * copy constructor
		 * Constructs a container with a copy of each of the elements in x, in the same order.
		 */
		vector(const vector &__x)
		{
			_create_storage(__x.size());
			_copy(__x.begin(), __x.end());
		}

		/*
		** --------------------------------- DESTRUCTOR --------------------------
		*/
		/*
		 *  The dtor only erases the elements, and note that if the
		 *  elements themselves are pointers, the pointed-to memory is
		 *  not touched in any way.  Managing the pointer is the user's
		 *  responsibility.
		 */
		~vector()
		{
			_destroy();
		}

		/*
		** --------------------------------- ASSIGNATION --------------------------
		*/
		/*
		 * Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		 */
		vector &operator=(const vector &__x)
		{
			_destroy();
			// this->clear();
			if (this->capacity() < __x.capacity())
				this->reserve(__x.capacity());
			_copy(__x.begin(), __x.end());
			return (*this);
		}

		/*
		** --------------------------------- ITERATORS --------------------------
		*/
		// done

		/* Return iterator to beginning
		 * Returns an iterator pointing to the first element in the vector.
		 * Notice that, unlike member vector::front, which returns a reference to the first element,
		 * this function returns a random access iterator pointing to it.
		 * If the container is empty, the returned iterator value shall not be dereferenced.
		 */

		iterator begin()
		{
			return iterator(this->_start);
		}

		const_iterator begin() const
		{
			return const_iterator(this->_start);
		}

		/* Return iterator to end
		 * Returns an iterator referring to the past-the-end element in the vector container.
		 * The past-the-end element is the theoretical element that would follow the last element in the vector.
		 * It does not point to any element, and thus shall not be dereferenced.
		 * Because the ranges used by functions of the standard library do not include the element pointed by
		 * their closing iterator, this function is often used in combination with vector::begin to specify a
		 * range including all the elements in the container.
		 * If the container is empty, this function returns the same as vector::begin.
		 */

		iterator end()
		{
			return iterator(this->_finish);
		}

		const_iterator end() const
		{
			return const_iterator(this->_finish);
		}

		/* Return reverse iterator to reverse beginning
		 * Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
		 *
		 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
		 *
		 * rbegin points to the element right before the one that would be pointed to by member end.
		 *
		 * Notice that unlike member vector::back, which returns a reference to this same element,
		 *		 this function returns a reverse random access iterator.
		 */
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		/* Return reverse iterator to reverse end
		 * Returns a reverse iterator pointing to the theoretical element preceding the first element
		 * in the vector (which is considered its reverse end).
		 *
		 * The range between vector::rbegin and vector::rend contains all the elements of the vector (in reverse order).
		 */
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		/*
		 ** --------------------------------- CAPACITY --------------------------
		 */
		// done

		/*  Returns the number of elements in the vector.  */
		size_type size() const _GLIBCXX_NOEXCEPT
		{
			return this->_finish - this->_start;
		}

		/*  Returns the size() of the largest possible vector.  */
		size_type max_size() const _GLIBCXX_NOEXCEPT
		{
			return _Tp_alloc_type.max_size();
		}
		/* Change size
		 * Resizes the container so that it contains n elements.
		 * If n is smaller than the current container size, the content is reduced
		 * to its first n elements, removing those beyond (and destroying them).
		 * If n is greater than the current container size, the content is expanded
		 * by inserting at the end as many elements as needed to reach a size of n.
		 * If val is specified, the new elements are initialized as copies of val,
		 * otherwise, they are value-initialized.
		 * If n is also greater than the current container capacity, an automatic
		 * reallocation of the allocated storage space takes place.
		 * Notice that this function changes the actual content of the container
		 * by inserting or erasing elements from it.
		 */
		void resize(size_type __new_size, value_type __x = value_type())
		{
			if (__new_size > capacity())
				reserve(__new_size);
			if (__new_size > size())
				_fill(__new_size - size(), __x);
			while (__new_size < size())
				pop_back();
		}

		/*
		 *  Returns the total number of elements that the vector can
		 *  hold before needing to allocate more memory.
		 */
		size_type capacity() const
		{
			return size_type(this->_end_of_storage - this->_start);
		}

		/*
		 *  Test whether vector is empty
		 *  Returns whether the vector is empty (i.e. whether its size is 0).
		 * 	This function does not modify the container in any way. To clear the content of a vector, see vector::clear.
		 */
		bool empty() const
		{
			return begin() == end();
		}

		/*
		 *  Request a change in capacity
		 *  Requests that the vector capacity be at least enough to contain n elements.
		 *  If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
		 *  In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
		 *  This function has no effect on the vector size and cannot alter its elements.
		 */
		void reserve(size_type __n)
		{
			if (__n > max_size())
				throw std::length_error("vector::reserve");
			if (capacity() >= __n)
				return;
			iterator it_begin = this->begin();
			iterator it_end = this->end();
			pointer _start_tmp = this->_start;
			pointer _end_of_storage_tmp = this->_end_of_storage;
			_create_storage(__n);
			_copy(it_begin, it_end);
			_Tp_alloc_type.deallocate(_start_tmp, _end_of_storage_tmp - _start_tmp);
		}

		/*
		** --------------------------------- ELEMENT ACCESS --------------------------
		*/
		// done

		/* const_reference operator[] (size_type n) const;
		 * Access element
		 * Returns a reference to the element at position n in the vector container.
		 * A similar member function, vector::at, has the same behavior as this operator function, except that vector::at is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
		 * Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.
		 */

		reference operator[](size_type __n)
		{
			return *(this->_start + __n);
		}

		const_reference operator[](size_type __n) const
		{
			return *(this->_start + __n);
		}

		/* Access element
		 * Returns a reference to the element at position n in the vector.
		 * The function automatically checks whether n is within the bounds
		 * of valid elements in the vector, throwing an out_of_range exception
		 * if it is not (i.e., if n is greater than, or equal to, its size).
		 * This is in contrast with member operator[], that does not check against bounds.
		 */
		reference at(size_type __n)
		{
			_range_check(__n);
			return (*this)[__n];
		}
		const_reference at(size_type __n) const
		{
			_range_check(__n);
			return (*this)[__n];
		}

		/*
		 * Access first element
		 * Returns a reference to the first element in the vector.
		 *
		 * Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
		 *
		 * Calling this function on an empty container causes undefined behavior.
		 */
		reference front()
		{
			return *begin(); // iterator
							 // return (*this)[0];
		}

		const_reference front() const
		{
			return *begin(); // iterator
							 // return (*this)[0];
		}

		/* Access last element
		 * Returns a reference to the last element in the vector.
		 *
		 * Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
		 *
		 * Calling this function on an empty container causes undefined behavior.
		 */
		reference back()
		{
			return *(end() - 1);
		}

		const_reference back() const
		{
			return *(end() - 1);
		}

		/*
		** --------------------------------- MODIFIERS --------------------------
		*/
		// assign //done
		// push_back //done
		// pop_back //done
		// insert
		// erase
		// swap
		// clear //done

		/* Assign vector content
		 * Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		 */
		template <class InputIterator>
		void assign(InputIterator __first, InputIterator __last) // iterator
		{
			typedef typename ft::is_integral<InputIterator>::type _Integral;
			_assign_dispatch(__first, __last, _Integral());
		}
		void assign(size_type __n, const value_type &__value)
		{
			_assign_dispatch(__n, __value, true_type());
		}

		/*Add element at the end
		 * Adds a new element at the end of the vector, after its current last element.
		 * The content of val is copied (or moved) to the new element.
		 * This effectively increases the container size by one, which causes an automatic
		 * reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
		 */
		void push_back(const value_type &__val)
		{
			if (this->_finish == this->_end_of_storage)
				reserve(_next_capacity());
			_Tp_alloc_type.construct(_finish, __val);
			this->_finish++;
		}
		/*
		 * Delete last element
		 * Removes the last element in the vector, effectively reducing the container size by one.
		 * This destroys the removed element.
		 */
		void pop_back()
		{
			if (!size())
				return;
			_Tp_alloc_type.destroy(this->_finish);
			this->_finish--;
		}

		/*
		 * Insert elements
		 * The vector is extended by inserting new elements before the element at the specified position,
		 * effectively increasing the container size by the number of elements inserted.
		 *
		 * This causes an automatic reallocation of the allocated storage space if -and only if- the new
		 * vector size surpasses the current vector capacity.
		 *
		 * Because vectors use an array as their underlying storage, inserting elements in positions other
		 * than the vector end causes the container to relocate all the elements that were after position
		 * to their new positions. This is generally an inefficient operation compared to the one performed
		 * for the same operation by other kinds of sequence containers (such as list or forward_list).
		 *
		 * The parameters determine how many elements are inserted and to which values they are initialized:
		 *
		 */
		iterator insert(iterator __position, const value_type &__x)
		{
			iterator new_position = _resize_and_move_at_end(__position, 1);
			_insert_single(new_position, __x);
			return new_position;
			// // return _insert_dispatch(__position, 1, __x, true_type());
			// return _insert_range(__position, 1, __x);
		}
		void insert(iterator __position, size_type __n, const value_type &__x)
		{
			_insert_range(__position, __n, __x);
		}
		template <class _InputIterator>
		void insert(iterator __position, _InputIterator __first, _InputIterator __last)
		{
			typedef typename ft::is_integral<_InputIterator>::type _Integral;
			_insert_dispatch(__position, __first, __last, _Integral());
		}
		/*
		 * Erase elements
		 * Removes from the vector either a single element (position) or a range
		 * of elements ([first,last)).
		 *
		 * This effectively reduces the container size by the number of elements
		 * removed, which are destroyed.
		 *
		 * Because vectors use an array as their underlying storage, erasing
		 * elements in positions other than the vector end causes the container
		 * to relocate all the elements after the segment erased to their new
		 * positions. This is generally an inefficient operation compared to the
		 * one performed for the same operation by other kinds of sequence
		 * containers (such as list or forward_list).
		 */

		iterator _move_from_end(iterator __first, iterator __last)
		{
			while (__last != end())
			{
				*__first = *__last;
				__first++;
				__last++;
			}
			_finish -= __last-__first;
			return __first;
		}//https://legacy.cplusplus.com/reference/vector/vector/swap/
		iterator erase(iterator __position)
		{
			iterator __position_end = __position;
			__position_end++;
			return erase(__position, __position_end);
		}
		iterator erase(iterator __first, iterator __last)
		{
			return _move_from_end( __first,  __last);
		}
		/*
		 * 	Swap content
		 * Exchanges the content of the container by the content of x, which
		 * is another vector object of the same type. Sizes may differ.
		 *
		 * After the call to this member function, the elements in this
		 * container are those which were in x before the call, and the
		 * elements of x are those which were in this. All iterators,
		 * references and pointers remain valid for the swapped objects.
		 *
		 * Notice that a non-member function exists with the same name,
		 * swap, overloading that algorithm with an optimization that
		 * behaves like this member function.
		 */
		void swap(vector &__x)
		{
			_swap(_Tp_alloc_type, __x._Tp_alloc_type);
			_swap(_start, __x._start);
			_swap(_finish, __x._finish);
			_swap(_end_of_storage, __x._end_of_storage);
		}
		/*
		 *  Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		 */
		void clear()
		{
			_finish = _start;
			// _destroy();
			// while (size())
			// 	pop_back();
		}

		/*
		** --------------------------------- ALLOCATOR --------------------------
		*/
		/*
		 * get_allocator done
		 */
		allocator_type get_allocator() const
		{
			return _Tp_alloc_type;
		}

	public:
	};

	/*
	** --------------------------------- COMPARISONS  ---------------------------
	*/
	/*
	 * Performs the appropriate comparison operation between the vector
	 * containers __x and __y.
	 *
	 * The equality comparison (operator==) is performed by first comparing
	 * sizes, and if they match, the elements are compared sequentially using
	 * operator==, stopping at the first mismatch (as if using algorithm equal).
	 *
	 * The less-than comparison (operator<) behaves as if using algorithm
	 * lexicographical_compare, which compares the elements sequentially
	 * using operator< in a reciprocal manner (i.e., checking both a<b and b<a)
	 * and stopping at the first occurrence.
	 *
	 * The other operations also use the operators == and < internally to compare
	 * the elements, behaving as if the following equivalent operations were
	 * performed:
	 */
	template <typename _Tp, typename _Alloc>
	bool operator==(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return (__x.size() == __y.size() && ft::equal(__x.begin(), __x.end(),
													  __y.begin(), __y.end()));
	}

	template <typename _Tp, typename _Alloc>
	bool operator<(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return ft::lexicographical_compare(__x.begin(), __x.end(),
										   __y.begin(), __y.end());
	}

	template <typename _Tp, typename _Alloc>
	bool operator!=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Tp, typename _Alloc>
	bool operator>(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Tp, typename _Alloc>
	bool operator<=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Tp, typename _Alloc>
	bool operator>=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Tp, typename _Alloc>
	void swap(vector<_Tp, _Alloc> &__x, vector<_Tp, _Alloc> &__y)
	{
		__x.swap(__y);
	}
}
#endif
