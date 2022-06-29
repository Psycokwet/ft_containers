/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/06/29 22:04:16 by scarboni         ###   ########.fr       */
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
			// this->_M_start = _Tp_alloc_type.allocate(__n);
			this->_M_start = _M_allocate(__n);
			this->_M_finish = this->_M_start;
			this->_M_end_of_storage = this->_M_start + __n;
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
			for (size_type i = 0; i < size(); i++)
			{
				_Tp_alloc_type.destroy(_M_start + i);
			}
			_Tp_alloc_type.deallocate(_M_start, _M_end_of_storage - _M_start);
		}

		/*
		 *  @brief  %Vector assignment operator.
		 *  @param  __x  A vector of identical element and allocator types.
		 *
		 *  All the elements of @a __x are copied, but any unused capacity in
		 *  @a __x will not be copied.
		 *
		 *  Whether the allocator is copied depends on the allocator traits.
		 */
		vector &operator=(const vector &__x);

		// [23.2.4.2] capacity
		/*  Returns the number of elements in the vector.  */
		size_type size() const _GLIBCXX_NOEXCEPT
		{
			return size_type(this->_M_finish - this->_M_start);
		}

		/*  Returns the size() of the largest possible vector.  */
		size_type max_size() const _GLIBCXX_NOEXCEPT
		{
			return allocator_type::max_size();
		}

		/*
		 *  Returns the total number of elements that the vector can
		 *  hold before needing to allocate more memory.
		 */
		size_type capacity() const
		{
			return size_type(this->_M_end_of_storage - this->_M_start);
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
