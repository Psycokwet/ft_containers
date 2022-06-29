/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/06/29 21:27:15 by scarboni         ###   ########.fr       */
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

	public:
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
		}

		/*
		 *  The dtor only erases the elements, and note that if the
		 *  elements themselves are pointers, the pointed-to memory is
		 *  not touched in any way.  Managing the pointer is the user's
		 *  responsibility.
		 */
		~vector()
		{
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
		vector &
		operator=(const vector &__x);

		/*
		 *  @brief  Assigns a given value to a vector.
		 *  @param  __n  Number of elements to be assigned.
		 *  @param  __val  Value to be assigned.
		 *
		 *  This function fills a vector with @a __n copies of the given
		 *  value.  Note that the assignment completely changes the
		 *  vector and that the resulting vector's size is the same as
		 *  the number of elements assigned.
		 */
		void
		assign(size_type __n, const value_type &__val)
		{
			_M_fill_assign(__n, __val);
		}

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

		/*
		 *  @brief  Attempt to preallocate enough memory for specified number of
		 *          elements.
		 *  @param  __n  Number of elements required.
		 *  @throw  std::length_error  If @a n exceeds @c max_size().
		 *
		 *  This function attempts to reserve enough memory for the
		 *  vector to hold the specified number of elements.  If the
		 *  number requested is more than max_size(), length_error is
		 *  thrown.
		 *
		 *  The advantage of this function is that if optimal code is a
		 *  necessity and the user can determine the number of elements
		 *  that will be required, the user can reserve the memory in
		 *  %advance, and thus prevent a possible reallocation of memory
		 *  and copying of vector data.
		 */
		void reserve(size_type __n);

		// element access
		/*
		 *  @brief  Subscript access to the data contained in the vector.
		 *  @param __n The index of the element for which data should be
		 *  accessed.
		 *  @return  Read/write reference to data.
		 *
		 *  This operator allows for easy, array-style, data access.
		 *  Note that data access with this operator is unchecked and
		 *  out_of_range lookups are not defined. (For checked lookups
		 *  see at().)
		 */
		reference operator[](size_type __n) _GLIBCXX_NOEXCEPT
		{
			__glibcxx_requires_subscript(__n);
			return *(this->_M_start + __n);
		}

		/*
		 *  @brief  Subscript access to the data contained in the vector.
		 *  @param __n The index of the element for which data should be
		 *  accessed.
		 *  @return  Read-only (constant) reference to data.
		 *
		 *  This operator allows for easy, array-style, data access.
		 *  Note that data access with this operator is unchecked and
		 *  out_of_range lookups are not defined. (For checked lookups
		 *  see at().)
		 */
		const_reference operator[](size_type __n) const _GLIBCXX_NOEXCEPT
		{
			__glibcxx_requires_subscript(__n);
			return *(this->_M_start + __n);
		}

	protected:
		/// Safety check used only from at().
		void _M_range_check(size_type __n) const
		{
			if (__n >= this->size())
				__throw_out_of_range_fmt(__N("vector::_M_range_check: __n "
											 "(which is %zu) >= this->size() "
											 "(which is %zu)"),
										 __n, this->size());
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
