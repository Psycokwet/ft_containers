/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/09/02 18:06:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "iterator_base.hpp"

namespace ft
{
	template <typename _Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<_Iterator>::iterator_category,
						  typename iterator_traits<_Iterator>::value_type,
						  typename iterator_traits<_Iterator>::difference_type,
						  typename iterator_traits<_Iterator>::pointer,
						  typename iterator_traits<_Iterator>::reference>
	{
	protected:
		_Iterator current;

		typedef iterator_traits<_Iterator> __traits_type;

	public:
		typedef _Iterator iterator_type;
		typedef typename __traits_type::difference_type difference_type;
		typedef typename __traits_type::pointer pointer;
		typedef typename __traits_type::reference reference;

		reverse_iterator() : current() {}

		reverse_iterator(iterator_type __x) : current(__x) {}

		reverse_iterator(const reverse_iterator &__x) : current(__x.current) {}

		template <typename _Iter>
		reverse_iterator(const reverse_iterator<_Iter> &__x) : current(__x.base()) {}
		iterator_type base() const { return current; }
		reference operator*() const 
		{
			_Iterator __tmp = current;
			return *--__tmp; //to access end() -1 as rbegin and so on
		}
		pointer operator->() const { return &(operator*()); }

		reverse_iterator &operator++()
		{
			--current;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator __tmp = *this;
			--current;
			return __tmp;
		}
		reverse_iterator &operator--()
		{
			++current;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator __tmp = *this;
			++current;
			return __tmp;
		}
		reverse_iterator operator+(difference_type __n) const { return reverse_iterator(current - __n); }
		reverse_iterator &operator+=(difference_type __n)
		{
			current -= __n;
			return *this;
		}
		reverse_iterator operator-(difference_type __n) const { return reverse_iterator(current + __n); }
		reverse_iterator &operator-=(difference_type __n)
		{
			current += __n;
			return *this;
		}
		reference operator[](difference_type __n) const { return *(*this + __n); }
	};

	template <typename _Iterator>
	bool operator==(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y) { return __x.base() == __y.base(); }

	template <typename _Iterator>
	bool operator<(const reverse_iterator<_Iterator> &__x,
				   const reverse_iterator<_Iterator> &__y) { return __y.base() < __x.base(); }

	template <typename _Iterator>
	bool operator!=(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y) { return !(__x == __y); }

	template <typename _Iterator>
	bool operator>(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y) { return __y < __x; }

	template <typename _Iterator>
	bool operator<=(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y) { return !(__y < __x); }

	template <typename _Iterator>
	bool operator>=(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y) { return !(__x < __y); }

	template <typename _IteratorL, typename _IteratorR>
	bool operator==(const reverse_iterator<_IteratorL> &__x, const reverse_iterator<_IteratorR> &__y) { return __x.base() == __y.base(); }

	template <typename _IteratorL, typename _IteratorR>
	bool operator<(const reverse_iterator<_IteratorL> &__x, const reverse_iterator<_IteratorR> &__y) { return __y.base() < __x.base(); }

	template <typename _IteratorL, typename _IteratorR>
	bool operator!=(const reverse_iterator<_IteratorL> &__x, const reverse_iterator<_IteratorR> &__y) { return !(__x == __y); }

	template <typename _IteratorL, typename _IteratorR>
	bool operator>(const reverse_iterator<_IteratorL> &__x, const reverse_iterator<_IteratorR> &__y) { return __y < __x; }

	template <typename _IteratorL, typename _IteratorR>
	bool operator<=(const reverse_iterator<_IteratorL> &__x, const reverse_iterator<_IteratorR> &__y) { return !(__y < __x); }

	template <typename _IteratorL, typename _IteratorR>
	bool operator>=(const reverse_iterator<_IteratorL> &__x, const reverse_iterator<_IteratorR> &__y) { return !(__x < __y); }

	template <typename _Iterator>
	typename reverse_iterator<_Iterator>::difference_type operator-(const reverse_iterator<_Iterator> &__x, const reverse_iterator<_Iterator> &__y) { return __y.base() - __x.base(); }

	template <typename _IteratorL, typename _IteratorR>
	typename reverse_iterator<_IteratorL>::difference_type operator-(const reverse_iterator<_IteratorL> &__x, const reverse_iterator<_IteratorR> &__y) { return __y.base() - __x.base(); }

	template <typename _Iterator>
	reverse_iterator<_Iterator> operator+(typename reverse_iterator<_Iterator>::difference_type __n, const reverse_iterator<_Iterator> &__x) { return reverse_iterator<_Iterator>(__x.base() - __n); }
}
#endif
