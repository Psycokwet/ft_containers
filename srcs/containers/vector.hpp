/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/07/03 22:06:03 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm.hpp>
#include <cstddef>
#include <tgmath.h>
#include "../util/util.hpp"
namespace ft
{
	template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
	class vector
	{
	public:
		typedef _Alloc allocator_type;

		typedef _Tp value_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		// ok so far
	private:
		allocator_type _Tp_alloc_type;
		pointer _M_start;
		pointer _M_finish;
		pointer _M_end_of_storage;

		void _destroy()
		{
			clear();
			_Tp_alloc_type.deallocate(_M_start, _M_end_of_storage - _M_start);
		}

		void _build(size_type __n, const value_type &__value = value_type())
		{
			_M_create_storage(__n);
			_fill(__n, __value);
		}

		void _fill(size_type __n, const value_type &__value = value_type())
		{
			for (size_type i = 0; i < __n; i++)
				push_back(__value);
		}

		pointer _M_allocate(size_t __n)
		{
			return __n != 0 ? _Tp_alloc_type.allocate(__n) : pointer();
		}
		void _M_create_storage(size_t __n)
		{
			_M_create_storage(this->_M_start,
							  this->_M_finish,
							  this->_M_end_of_storage, __n);
		}

		void _M_create_storage(pointer &_M_start,
							   pointer &_M_finish,
							   pointer &_M_end_of_storage, size_t __n)
		{
			_M_start = _M_allocate(__n);
			_M_finish = _M_start;
			_M_end_of_storage = _M_start + __n;
		}
		void _M_range_check(size_type __n) const
		{
			if (__n >= this->size())
				throw std::out_of_range(SSTR("vector::_M_range_check: __n (which is ") //
										+ SSTR(__n)									   //
										+ SSTR(" ) >= this->size() (which is ")		   //
										+ SSTR(this->size()) + SSTR(")"));			   //
		}

	public:
		/*
		** --------------------------------- CONSTRUCTORS --------------------------
		*/
		/*
		 *  @brief  Creates a vector with no elements.
		 *  @param  __a  An allocator object.
		 */
		explicit vector(const allocator_type &__a = allocator_type())
			: _Tp_alloc_type(__a),
			  _M_start(),
			  _M_finish(),
			  _M_end_of_storage() {}

		/*
		 *  @brief  Creates a vector with copies of an exemplar element.
		 *  @param  __n  The number of elements to initially create.
		 *  @param  __value  An element to copy.
		 *  @param  __a  An allocator.
		 *
		 *  This constructor fills the vector with @a __n copies of @a __value.
		 */
		explicit vector(size_type __n, const value_type &__value = value_type(),
						const allocator_type &__a = allocator_type())
			: _Tp_alloc_type(__a),
			  _M_start(),
			  _M_finish(),
			  _M_end_of_storage()
		{
			_build(__n, __value);
		}
		/*
		 *  @brief  iterator copy constructor
		 *  @param  first  iterator begin to copy.
		 *  @param  last  iterator last to copy.
		 */
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last,
		// 	   const allocator_type &alloc = allocator_type()) {}
		/*
		 *  @brief  Copy constructor
		 *  @param  x  Another vector to copy.
		 */
		vector(const vector &x) {}

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
		 *  @brief  Vector assignment operator.
		 *  @param  __x  A vector of identical element and allocator types.
		 *
		 *  All the elements of @a __x are copied, but any unused capacity in
		 *  @a __x will not be copied.
		 *
		 */
		vector &operator=(const vector &__x)
		{
			this->clear();
			if (this->m_capacity < __x.m_capacity)
				this->reserve(__x.m_capacity);
			// std::memcpy(static_cast<void *>(this->m_container), static_cast<void *>(__x.m_container), __x.m_size * sizeof(value_type));
			return (*this);
		}

		/*
		** --------------------------------- CAPACITY --------------------------
		*/
		/*
		 * size //done
		 * max_size//done
		 * resize //done
		 * capacity //done
		 * empty //wip ITERATOR
		 * reserve //wip ITERATOR
		 */

		/*  Returns the number of elements in the vector.  */
		size_type size() const _GLIBCXX_NOEXCEPT
		{
			return size_type(this->_M_finish - this->_M_start);
		}

		/*  Returns the size() of the largest possible vector.  */
		size_type max_size() const _GLIBCXX_NOEXCEPT
		{
			return _Tp_alloc_type.max_size();
		}
		// Change size
		// Resizes the container so that it contains n elements.
		// If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
		// If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
		// If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
		// Notice that this function changes the actual content of the container by inserting or erasing elements from it.

		void resize(size_type __new_size, value_type __x = value_type())
		{
			if (__new_size > capacity())
			{
				reserve(__new_size);
			}
			if (__new_size > size())
				_fill(__new_size - size(), __x);
			while (__new_size < size())
			{
				pop_back();
			}
		}

		/*
		 *  Returns the total number of elements that the vector can
		 *  hold before needing to allocate more memory.
		 */
		size_type capacity() const
		{
			return size_type(this->_M_end_of_storage - this->_M_start);
		}

		/*
		 *  Test whether vector is empty
		 *  Returns whether the vector is empty (i.e. whether its size is 0).
		 * 	This function does not modify the container in any way. To clear the content of a vector, see vector::clear.
		 */
		bool empty() const
		{
			// return begin() == end(); //iterator
			return false;
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
			pointer _M_start_tmp = this->_M_start;
			pointer _M_end_of_storage_tmp = this->_M_end_of_storage;
			_M_create_storage(__n);
			size_type current_size = size();
			_fill(current_size, 42); // replace iterator
			_Tp_alloc_type.deallocate(_M_start_tmp, _M_end_of_storage_tmp - _M_start_tmp);
		}

		/*
		** --------------------------------- ELEMENT ACCESS --------------------------
		*/
		/*
		 * operator[] //done
		 * at //done
		 * front // done but it
		 * back //it
		 */
		/* const_reference operator[] (size_type n) const;
		 * Access element
		 * Returns a reference to the element at position n in the vector container.
		 * A similar member function, vector::at, has the same behavior as this operator function, except that vector::at is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
		 * Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.
		 */

		reference operator[](size_type __n)
		{
			return *(this->_M_start + __n);
		}

		const_reference operator[](size_type __n) const
		{
			return *(this->_M_start + __n);
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
			_M_range_check(__n);
			return (*this)[__n];
		}
		const_reference at(size_type __n) const
		{
			_M_range_check(__n);
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
			// return *begin();//iterator
			return (*this)[0];
		}

		const_reference front() const
		{
			// return *begin();//iterator
			return (*this)[0];
		}

		/* Access last element
		 * Returns a reference to the last element in the vector.
		 *
		 * Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
		 *
		 * Calling this function on an empty container causes undefined behavior.
		 */
		// reference back()
		// {
		// 	return *(end() - 1);
		// }

		// const_reference back() const
		// {
		// 	return *(end() - 1);
		// }

		/*
		** --------------------------------- MODIFIERS --------------------------
		*/
		// assign //done but iterator
		// push_back //done
		// pop_back //done
		// insert
		// erase
		// swap
		// clear //done

		/* Assign vector content
		 * Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		 */
		// template <class InputIterator>
		// void assign(InputIterator first, InputIterator last) // iterator
		// {
		// 	_destroy();
		// }
		void assign(size_type __n, const value_type &__value)
		{
			if (capacity() < __n)
			{
				_destroy();
				_build(__n, __value);
				return;
			}
			_fill(__n, __value);
		}

		/*Add element at the end
		 * Adds a new element at the end of the vector, after its current last element.
		 * The content of val is copied (or moved) to the new element.
		 * This effectively increases the container size by one, which causes an automatic
		 * reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
		 */
		void push_back(const value_type &val)
		{
			if (this->_M_finish == this->_M_end_of_storage)
			{
				resize(capacity() * 1.5);
			}
			_Tp_alloc_type.construct(_M_finish, val);
			this->_M_finish++;
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
			_Tp_alloc_type.destroy(this->_M_finish);
			this->_M_finish--;
		}
		/*
		 *  Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		 */
		void clear()
		{
			for (size_type i = 0; i < size(); i++)
			{
				_Tp_alloc_type.destroy(_M_start + i);
			}
			this->_M_finish = this->_M_start;
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
	 *  @brief  Vector equality comparison.
	 *  @param  __x  A vector.
	 *  @param  __y  A vector of the same type as @a __x.
	 *  @return  True iff the size and elements of the vectors are equal.
	 *
	 *  This is an equivalence relation.  It is linear in the size of the
	 *  vectors.  Vectors are considered equivalent if their sizes are equal,
	 *  and if corresponding elements compare equal.
	 */
	template <typename _Tp, typename _Alloc>
	inline bool operator==(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return (__x.size() == __y.size() && ft::equal(__x.begin(), __x.end(),
													  __y.begin(), __y.end()));
	}

	/*
	 *  @brief  Vector ordering relation.
	 *  @param  __x  A vector.
	 *  @param  __y  A vector of the same type as @a __x.
	 *  @return  True iff @a __x is lexicographically less than @a __y.
	 *
	 *  This is a total ordering relation.  It is linear in the size of the
	 *  vectors.  The elements must be comparable with @c <.
	 *
	 */
	template <typename _Tp, typename _Alloc>
	inline bool operator<(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return ft::lexicographical_compare(__x.begin(), __x.end(),
										   __y.begin(), __y.end());
	}

	/// Based on operator==
	template <typename _Tp, typename _Alloc>
	inline bool operator!=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	/// Based on operator<
	template <typename _Tp, typename _Alloc>
	inline bool operator>(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return __y < __x;
	}

	/// Based on operator<
	template <typename _Tp, typename _Alloc>
	inline bool operator<=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	/// Based on operator<
	template <typename _Tp, typename _Alloc>
	inline bool operator>=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	/// See std::vector::swap().

	template <typename _Tp, typename _Alloc>
	void swap(vector<_Tp, _Alloc> &__x, vector<_Tp, _Alloc> &__y)
	{
		__x.swap(__y);
	}
} // namespace std

#endif
