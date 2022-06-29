/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/06/24 15:30:30 by scarboni         ###   ########.fr       */
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
	class vector:
	{
	public:
		typedef _Alloc allocator_type;

		typedef _Tp value_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		// typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
		// typedef __gnu_cxx::__normal_iterator<const_pointer, vector>
		// 	const_iterator;
		// typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		// typedef std::reverse_iterator<iterator> reverse_iterator;
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
		void
		_M_fill_initialize(size_type __n, const value_type &__value)
		{
			this->_M_finish =
				std::__uninitialized_fill_n_a(this->_M_start, __n, __value,
											  _M_get_Tp_allocator());
		}
		void _M_create_storage(size_t __n)
		{
			this->_M_start = this->_M_allocate(__n);
			this->_M_finish = this->_M_start;
			this->_M_end_of_storage = this->_M_start + __n;
		}
	};

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
		_M_create_storage(__n);
		// _M_fill_initialize(__n, __value);
	}

	/*
	 *  @brief  %Vector copy constructor.
	 *  @param  __x  A vector of identical element and allocator types.
	 *
	 *  All the elements of @a __x are copied, but any unused capacity in
	 *  @a __x  will not be copied
	 *  (i.e. capacity() == size() in the new vector).
	 *
	 *  The newly-created vector uses a copy of the allocator object used
	 *  by @a __x (unless the allocator traits dictate a different object).
	 */
	vector(const vector &__x)
		: _Base(__x.size(),
				_Alloc_traits::_S_select_on_copy(__x._M_get_Tp_allocator()))
	{
		this->_M_finish =
			std::__uninitialized_copy_a(__x.begin(), __x.end(),
										this->_M_start,
										_M_get_Tp_allocator());
	}

	/*
	 *  @brief  Builds a vector from a range.
	 *  @param  __first  An input iterator.
	 *  @param  __last  An input iterator.
	 *  @param  __a  An allocator.
	 *
	 *  Create a vector consisting of copies of the elements from
	 *  [first,last).
	 *
	 *  If the iterators are forward, bidirectional, or
	 *  random-access, then this will call the elements' copy
	 *  constructor N times (where N is distance(first,last)) and do
	 *  no memory reallocation.  But if only input iterators are
	 *  used, then this will do at most 2N calls to the copy
	 *  constructor, and logN memory reallocations.
	 */
	// template <typename _InputIterator>
	// vector(_InputIterator __first, _InputIterator __last,
	// 	   const allocator_type &__a = allocator_type())
	// 	: _Base(__a)
	// {
	// 	// Check whether it's an integral type.  If so, it's not an iterator.
	// 	typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	// 	_M_initialize_dispatch(__first, __last, _Integral());
	// }

	/*
	 *  The dtor only erases the elements, and note that if the
	 *  elements themselves are pointers, the pointed-to memory is
	 *  not touched in any way.  Managing the pointer is the user's
	 *  responsibility.
	 */
	~vector()
	{
		for (size_type i = 0; i < _size; i++)
			_Tp_alloc_type.destroy(this->_M_start, this->_M_finish,
								   _M_get_Tp_allocator());
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

	/*
	 *  @brief  Assigns a range to a vector.
	 *  @param  __first  An input iterator.
	 *  @param  __last   An input iterator.
	 *
	 *  This function fills a vector with copies of the elements in the
	 *  range [__first,__last).
	 *
	 *  Note that the assignment completely changes the vector and
	 *  that the resulting vector's size is the same as the number
	 *  of elements assigned.
	 */
	// template <typename _InputIterator>
	// void
	// assign(_InputIterator __first, _InputIterator __last)
	// {
	// 	// Check whether it's an integral type.  If so, it's not an iterator.
	// 	typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	// 	_M_assign_dispatch(__first, __last, _Integral());
	// }

	/// Get a copy of the memory allocation object.
	using _Base::get_allocator;

	// iterators
	/*
	 *  Returns a read/write iterator that points to the first
	 *  element in the vector.  Iteration is done in ordinary
	 *  element order.
	 */
	// iterator
	// begin() _GLIBCXX_NOEXCEPT
	// {
	// 	return iterator(this->_M_start);
	// }

	/*
	 *  Returns a read-only (constant) iterator that points to the
	 *  first element in the vector.  Iteration is done in ordinary
	 *  element order.
	 */
	// const_iterator
	// begin() const _GLIBCXX_NOEXCEPT
	// {
	// 	return const_iterator(this->_M_start);
	// }

	/*
	 *  Returns a read/write iterator that points one past the last
	 *  element in the vector.  Iteration is done in ordinary
	 *  element order.
	 */
	// iterator
	// end() _GLIBCXX_NOEXCEPT
	// {
	// 	return iterator(this->_M_finish);
	// }

	/*
	 *  Returns a read-only (constant) iterator that points one past
	 *  the last element in the vector.  Iteration is done in
	 *  ordinary element order.
	 */
	// const_iterator
	// end() const _GLIBCXX_NOEXCEPT
	// {
	// 	return const_iterator(this->_M_finish);
	// }

	/*
	 *  Returns a read/write reverse iterator that points to the
	 *  last element in the vector.  Iteration is done in reverse
	 *  element order.
	 */
	// reverse_iterator
	// rbegin() _GLIBCXX_NOEXCEPT
	// {
	// 	return reverse_iterator(end());
	// }

	/*
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to the last element in the vector.  Iteration is done in
	 *  reverse element order.
	 */
	// const_reverse_iterator
	// rbegin() const _GLIBCXX_NOEXCEPT
	// {
	// 	return const_reverse_iterator(end());
	// }

	/*
	 *  Returns a read/write reverse iterator that points to one
	 *  before the first element in the vector.  Iteration is done
	 *  in reverse element order.
	 */
	// reverse_iterator
	// rend() _GLIBCXX_NOEXCEPT
	// {
	// 	return reverse_iterator(begin());
	// }

	/*
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to one before the first element in the vector.  Iteration
	 *  is done in reverse element order.
	 */
	// const_reverse_iterator
	// rend() const _GLIBCXX_NOEXCEPT
	// {
	// 	return const_reverse_iterator(begin());
	// }

	// [23.2.4.2] capacity
	/*  Returns the number of elements in the vector.  */
	size_type
	size() const _GLIBCXX_NOEXCEPT
	{
		return size_type(this->_M_finish - this->_M_start);
	}

	/*  Returns the size() of the largest possible vector.  */
	size_type
	max_size() const _GLIBCXX_NOEXCEPT
	{
		return _Alloc_traits::max_size(_M_get_Tp_allocator());
	}

	/*
	 *  @brief  Resizes the vector to the specified number of elements.
	 *  @param  __new_size  Number of elements the vector should contain.
	 *  @param  __x  Data with which new elements should be populated.
	 *
	 *  This function will %resize the vector to the specified
	 *  number of elements.  If the number is smaller than the
	 *  vector's current size the vector is truncated, otherwise
	 *  the vector is extended and new elements are populated with
	 *  given data.
	 */
	void
	resize(size_type __new_size, value_type __x = value_type())
	{
		if (__new_size > size())
			_M_fill_insert(end(), __new_size - size(), __x);
		else if (__new_size < size())
			_M_erase_at_end(this->_M_start + __new_size);
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
	 *  Returns true if the vector is empty.  (Thus begin() would
	 *  equal end().)
	 */
	bool
	empty() const _GLIBCXX_NOEXCEPT
	{
		return begin() == end();
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
	void
	reserve(size_type __n);

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
	reference
	operator[](size_type __n) _GLIBCXX_NOEXCEPT
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
	const_reference
	operator[](size_type __n) const _GLIBCXX_NOEXCEPT
	{
		__glibcxx_requires_subscript(__n);
		return *(this->_M_start + __n);
	}

protected:
	/// Safety check used only from at().
	void
	_M_range_check(size_type __n) const
	{
		if (__n >= this->size())
			__throw_out_of_range_fmt(__N("vector::_M_range_check: __n "
										 "(which is %zu) >= this->size() "
										 "(which is %zu)"),
									 __n, this->size());
	}

public:
	/*
	 *  @brief  Provides access to the data contained in the vector.
	 *  @param __n The index of the element for which data should be
	 *  accessed.
	 *  @return  Read/write reference to data.
	 *  @throw  std::out_of_range  If @a __n is an invalid index.
	 *
	 *  This function provides for safer data access.  The parameter
	 *  is first checked that it is in the range of the vector.  The
	 *  function throws out_of_range if the check fails.
	 */
	reference
	at(size_type __n)
	{
		_M_range_check(__n);
		return (*this)[__n];
	}

	/*
	 *  @brief  Provides access to the data contained in the vector.
	 *  @param __n The index of the element for which data should be
	 *  accessed.
	 *  @return  Read-only (constant) reference to data.
	 *  @throw  std::out_of_range  If @a __n is an invalid index.
	 *
	 *  This function provides for safer data access.  The parameter
	 *  is first checked that it is in the range of the vector.  The
	 *  function throws out_of_range if the check fails.
	 */
	const_reference
	at(size_type __n) const
	{
		_M_range_check(__n);
		return (*this)[__n];
	}

	/*
	 *  Returns a read/write reference to the data at the first
	 *  element of the vector.
	 */
	reference
	front() _GLIBCXX_NOEXCEPT
	{
		__glibcxx_requires_nonempty();
		return *begin();
	}

	/*
	 *  Returns a read-only (constant) reference to the data at the first
	 *  element of the vector.
	 */
	const_reference
	front() const _GLIBCXX_NOEXCEPT
	{
		__glibcxx_requires_nonempty();
		return *begin();
	}

	/*
	 *  Returns a read/write reference to the data at the last
	 *  element of the vector.
	 */
	reference
	back() _GLIBCXX_NOEXCEPT
	{
		__glibcxx_requires_nonempty();
		return *(end() - 1);
	}

	/*
	 *  Returns a read-only (constant) reference to the data at the
	 *  last element of the vector.
	 */
	const_reference
	back() const _GLIBCXX_NOEXCEPT
	{
		__glibcxx_requires_nonempty();
		return *(end() - 1);
	}

	// _GLIBCXX_RESOLVE_LIB_DEFECTS
	// DR 464. Suggestion for new member functions in standard containers.
	// data access
	/*
	 *   Returns a pointer such that [data(), data() + size()) is a valid
	 *   range.  For a non-empty vector, data() == &front().
	 */
	_Tp *
	data() _GLIBCXX_NOEXCEPT
	{
		return _M_data_ptr(this->_M_start);
	}

	const _Tp *
	data() const _GLIBCXX_NOEXCEPT
	{
		return _M_data_ptr(this->_M_start);
	}

	// [23.2.4.3] modifiers
	/*
	 *  @brief  Add data to the end of the vector.
	 *  @param  __x  Data to be added.
	 *
	 *  This is a typical stack operation.  The function creates an
	 *  element at the end of the vector and assigns the given data
	 *  to it.  Due to the nature of a vector this operation can be
	 *  done in constant time if the vector has preallocated space
	 *  available.
	 */
	void
	push_back(const value_type &__x)
	{
		if (this->_M_finish != this->_M_end_of_storage)
		{
			_Alloc_traits::construct(this->_M_impl, this->_M_finish,
									 __x);
			++this->_M_finish;
		}
		else
			_M_realloc_insert(end(), __x);
	}

	/*
	 *  @brief  Removes last element.
	 *
	 *  This is a typical stack operation. It shrinks the vector by one.
	 *
	 *  Note that no data is returned, and if the last element's
	 *  data is needed, it should be retrieved before pop_back() is
	 *  called.
	 */
	void
	pop_back() _GLIBCXX_NOEXCEPT
	{
		__glibcxx_requires_nonempty();
		--this->_M_finish;
		_Alloc_traits::destroy(this->_M_impl, this->_M_finish);
	}

	/*
	 *  @brief  Inserts given value into vector before specified iterator.
	 *  @param  __position  An iterator into the vector.
	 *  @param  __x  Data to be inserted.
	 *  @return  An iterator that points to the inserted data.
	 *
	 *  This function will insert a copy of the given value before
	 *  the specified location.  Note that this kind of operation
	 *  could be expensive for a vector and if it is frequently
	 *  used the user should consider using std::list.
	 */
	// iterator
	// insert(iterator __position, const value_type &__x);

	/*
	 *  @brief  Inserts a number of copies of given data into the vector.
	 *  @param  __position  An iterator into the vector.
	 *  @param  __n  Number of elements to be inserted.
	 *  @param  __x  Data to be inserted.
	 *
	 *  This function will insert a specified number of copies of
	 *  the given data before the location specified by @a position.
	 *
	 *  Note that this kind of operation could be expensive for a
	 *  vector and if it is frequently used the user should
	 *  consider using std::list.
	 */
	// void
	// insert(iterator __position, size_type __n, const value_type &__x)
	// {
	// 	_M_fill_insert(__position, __n, __x);
	// }
	/*
	 *  @brief  Inserts a range into the vector.
	 *  @param  __position  An iterator into the vector.
	 *  @param  __first  An input iterator.
	 *  @param  __last   An input iterator.
	 *
	 *  This function will insert copies of the data in the range
	 *  [__first,__last) into the vector before the location specified
	 *  by @a pos.
	 *
	 *  Note that this kind of operation could be expensive for a
	 *  vector and if it is frequently used the user should
	 *  consider using std::list.
	 */
	// template <typename _InputIterator>
	// void
	// insert(iterator __position, _InputIterator __first,
	// 	   _InputIterator __last)
	// {
	// 	// Check whether it's an integral type.  If so, it's not an iterator.
	// 	typedef typename std::__is_integer<_InputIterator>::__type _Integral;
	// 	_M_insert_dispatch(__position, __first, __last, _Integral());
	// }

	/*
	 *  @brief  Remove element at given position.
	 *  @param  __position  Iterator pointing to element to be erased.
	 *  @return  An iterator pointing to the next element (or end()).
	 *
	 *  This function will erase the element at the given position and thus
	 *  shorten the vector by one.
	 *
	 *  Note This operation could be expensive and if it is
	 *  frequently used the user should consider using std::list.
	 *  The user is also cautioned that this function only erases
	 *  the element, and that if the element is itself a pointer,
	 *  the pointed-to memory is not touched in any way.  Managing
	 *  the pointer is the user's responsibility.
	 */
	// iterator
	// erase(iterator __position)
	// {
	// 	return _M_erase(__position);
	// }

	/*
	 *  @brief  Remove a range of elements.
	 *  @param  __first  Iterator pointing to the first element to be erased.
	 *  @param  __last  Iterator pointing to one past the last element to be
	 *                  erased.
	 *  @return  An iterator pointing to the element pointed to by @a __last
	 *           prior to erasing (or end()).
	 *
	 *  This function will erase the elements in the range
	 *  [__first,__last) and shorten the vector accordingly.
	 *
	 *  Note This operation could be expensive and if it is
	 *  frequently used the user should consider using std::list.
	 *  The user is also cautioned that this function only erases
	 *  the elements, and that if the elements themselves are
	 *  pointers, the pointed-to memory is not touched in any way.
	 *  Managing the pointer is the user's responsibility.
	 */
	// iterator
	// erase(iterator __first, iterator __last)
	// {
	// 	return _M_erase(__first, __last);
	// }

	/*
	 *  @brief  Swaps data with another vector.
	 *  @param  __x  A vector of the same element and allocator types.
	 *
	 *  This exchanges the elements between two vectors in constant time.
	 *  (Three pointers, so it should be quite fast.)
	 *  Note that the global std::swap() function is specialized such that
	 *  std::swap(v1,v2) will feed to this function.
	 *
	 *  Whether the allocators are swapped depends on the allocator traits.
	 */
	void
	swap(vector &__x) _GLIBCXX_NOEXCEPT
	{
		this->_M_swap_data(__x);
		_Alloc_traits::_S_on_swap(_M_get_Tp_allocator(),
								  __x._M_get_Tp_allocator());
	}

	/*
	 *  Erases all the elements.  Note that this function only erases the
	 *  elements, and that if the elements themselves are pointers, the
	 *  pointed-to memory is not touched in any way.  Managing the pointer is
	 *  the user's responsibility.
	 */
	void
	clear() _GLIBCXX_NOEXCEPT
	{
		_M_erase_at_end(this->_M_start);
	}
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

template <typename T, class Alloc>
void swap(vector<_Tp, _Alloc> &__x, vector<_Tp, _Alloc> &__y)
{
	__x.swap(__y);
}
} // namespace std

#endif
