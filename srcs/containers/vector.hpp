/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/06/30 13:40:39 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm.hpp>
#include <cstddef>
#include <tgmath.h>

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
			_M_create_storage(__n);
			for (size_type i = 0; i < __n; i++)
			{
				_Tp_alloc_type.construct(_M_finish, __value);
				_M_finish++;
			}
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
			clear();
			_Tp_alloc_type.deallocate(_M_start, _M_end_of_storage - _M_start);
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
			while (__new_size > size())
			{
				push_back(__x);
			}
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
			if (capacity() < __n)
			{

				pointer _M_start_tmp;
				pointer _M_finish_tmp;
				pointer _M_end_of_storage_tmp;
				_M_create_storage(_M_start_tmp,
								  _M_finish_tmp,
								  _M_end_of_storage_tmp, __n);

				for (size_type i = 0; i < size(); i++)
				{
					_Tp_alloc_type.construct(_M_finish_tmp, 42); // iterator copy
					_M_finish_tmp++;
				}
				_Tp_alloc_type.deallocate(_M_start, _M_end_of_storage - _M_start);

				this->_M_start = _M_start_tmp;
				this->_M_finish = _M_finish_tmp;
				this->_M_end_of_storage = _M_end_of_storage_tmp;
			}
		}

		/*
		** --------------------------------- ELEMENT ACCESS --------------------------
		*/
		/*
		 * operator[]
		 * at
		 * front
		 * back
		 */

		/*
		** --------------------------------- MODIFIERS --------------------------
		*/
		// assign
		// push_back
		// pop_back
		// insert
		// erase
		// swap
		// clear //done

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
			--this->_M_finish;
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
		 * get_allocator
		 */

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
