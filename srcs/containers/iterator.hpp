/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/28 16:02:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "iterator_base.hpp"

namespace ft
{
	// using ft::iterator;
	using ft::iterator_traits;
	template <typename _Iterator, typename _Container>
	class __normal_iterator
	{
	protected:
		_Iterator _M_current;

		typedef iterator_traits<_Iterator> __traits_type;

	public:
		typedef _Iterator iterator_type;
		typedef typename __traits_type::iterator_category iterator_category;
		typedef typename __traits_type::value_type value_type;
		typedef typename __traits_type::difference_type difference_type;
		typedef typename __traits_type::reference reference;
		typedef typename __traits_type::pointer pointer;

		__normal_iterator()
			: _M_current(_Iterator()) {}

		explicit __normal_iterator(const _Iterator &__i)
			: _M_current(__i) {}

		template <typename _Iter>
		// Allow iterator to const_iterator conversion
		__normal_iterator(const __normal_iterator<_Iter,
												  typename ft::enable_if<
													  (std::__are_same<_Iter, typename _Container::pointer>::__value),
													  _Container>::type> &__i)
			: _M_current(__i.base())
		{
		}

		reference operator*() const { return *_M_current; }

		pointer operator->() const { return _M_current; }

		__normal_iterator &operator++()
		{
			++_M_current;
			return *this;
		}

		__normal_iterator operator++(int) { return __normal_iterator(_M_current++); }

		__normal_iterator &operator--()
		{
			--_M_current;
			return *this;
		}

		__normal_iterator operator--(int) { return __normal_iterator(_M_current--); }

		reference operator[](difference_type __n) const { return _M_current[__n]; }

		__normal_iterator &operator+=(difference_type __n)
		{
			_M_current += __n;
			return *this;
		}

		__normal_iterator operator+(difference_type __n) const { return __normal_iterator(_M_current + __n); }
		__normal_iterator &operator-=(difference_type __n)
		{
			_M_current -= __n;
			return *this;
		}

		__normal_iterator operator-(difference_type __n) const { return __normal_iterator(_M_current - __n); }

		const _Iterator &base() const { return _M_current; }
	};

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	bool operator==(const __normal_iterator<_IteratorL, _Container> &__lhs,
					const __normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() == __rhs.base(); }

	template <typename _Iterator, typename _Container>
	bool operator==(const __normal_iterator<_Iterator, _Container> &__lhs,
					const __normal_iterator<_Iterator, _Container> &__rhs) { return __lhs.base() == __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	bool operator!=(const __normal_iterator<_IteratorL, _Container> &__lhs,
					const __normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() != __rhs.base(); }

	template <typename _Iterator, typename _Container>
	bool operator!=(const __normal_iterator<_Iterator, _Container> &__lhs,
					const __normal_iterator<_Iterator, _Container> &__rhs) { return __lhs.base() != __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	bool operator<(const __normal_iterator<_IteratorL, _Container> &__lhs,
				   const __normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() < __rhs.base(); }

	template <typename _Iterator, typename _Container>
	bool operator<(const __normal_iterator<_Iterator, _Container> &__lhs,
				   const __normal_iterator<_Iterator, _Container> &__rhs) { return __lhs.base() < __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	bool operator>(const __normal_iterator<_IteratorL, _Container> &__lhs,
				   const __normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() > __rhs.base(); }

	template <typename _Iterator, typename _Container>
	bool operator>(const __normal_iterator<_Iterator, _Container> &__lhs,
				   const __normal_iterator<_Iterator, _Container> &__rhs) { return __lhs.base() > __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	bool operator<=(const __normal_iterator<_IteratorL, _Container> &__lhs,
					const __normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() <= __rhs.base(); }

	template <typename _Iterator, typename _Container>
	bool operator<=(const __normal_iterator<_Iterator, _Container> &__lhs,
					const __normal_iterator<_Iterator, _Container> &__rhs) { return __lhs.base() <= __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	bool operator>=(const __normal_iterator<_IteratorL, _Container> &__lhs,
					const __normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() >= __rhs.base(); }

	template <typename _Iterator, typename _Container>
	bool operator>=(const __normal_iterator<_Iterator, _Container> &__lhs,
					const __normal_iterator<_Iterator, _Container> &__rhs) { return __lhs.base() >= __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	typename __normal_iterator<_IteratorL, _Container>::difference_type
	operator-(const __normal_iterator<_IteratorL, _Container> &__lhs,
			  const __normal_iterator<_IteratorR, _Container> &__rhs) { return __lhs.base() - __rhs.base(); }

	template <typename _Iterator, typename _Container>
	typename __normal_iterator<_Iterator, _Container>::difference_type
	operator-(const __normal_iterator<_Iterator, _Container> &__lhs,
			  const __normal_iterator<_Iterator, _Container> &__rhs) { return __lhs.base() - __rhs.base(); }

	template <typename _Iterator, typename _Container>
	__normal_iterator<_Iterator, _Container>
	operator+(typename __normal_iterator<_Iterator, _Container>::difference_type __n,
			  const __normal_iterator<_Iterator, _Container> &__i) { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }

}
#endif
