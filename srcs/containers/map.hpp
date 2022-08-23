/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:05:33 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/23 17:01:11 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "rb_tree.hpp"

namespace ft
{

	/*
	 * Maps are associative containers that store elements formed by a
	 * combination of a key value and a mapped value, following a specific order.
	 *
	 * In a map, the key values are generally used to sort and uniquely identify
	 * the elements, while the mapped values store the content associated to this
	 * key. The types of key and mapped value may differ, and are grouped together
	 * in member type value_type, which is a pair type combining both:
	 *
	 */

	template <typename _Key,											   // map::key_type
			  typename _Tp,												   // map::mapped_type
			  typename _Compare = std::less<_Key>,						   // map::key_compare
			  typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > // map::allocator_type
			  >
	class map
	{
	public:
		typedef _Key key_type;
		typedef _Tp mapped_type;
		typedef ft::pair<const _Key, _Tp> value_type;
		typedef _Compare key_compare;
		typedef _Alloc allocator_type;

	private:
	public:
		class value_compare // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			: public std::binary_function<value_type, value_type, bool>
		{
			friend class map<_Key, _Tp, _Compare, _Alloc>;

		protected:
			_Compare comp;

			value_compare(_Compare __c)
				: comp(__c) {} // constructed with map's comparison object

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			/*
			 * The public member of this comparison class returns
			 * true if the key of the first argument is considered
			 * to go before that of the second (according to the
			 * strict weak ordering specified by the container's
			 * comparison object, key_comp), and false otherwise.
			 *
			 * Notice that value_compare has no public constructor,
			 * therefore no objects can be directly created from
			 * this nested class outside map members.
			 *
			 */
			bool operator()(const value_type &__x, const value_type &__y) const
			{
				return comp(__x.first, __y.first);
			}
		};

	private:
		/// This turns a red-black tree into a [multi]map.

		typedef _Rb_tree<key_type, value_type, key_compare, allocator_type>
			_Rep_type;

		/// The actual tree structure.
		_Rep_type _M_t;

	public:
		// many of these are specified differently in ISO, but the following are
		// "functionally equivalent"
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;

		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		// typedef typename _Rep_type::iterator iterator;
		// typedef typename _Rep_type::const_iterator const_iterator;

		// typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// typedef typename _Rep_type::difference_type difference_type;
		// typedef typename _Rep_type::size_type size_type;

		map() //: _M_t()
		{
		}

		explicit map(const _Compare &__comp,
					 const allocator_type &__a = allocator_type())
		//: _M_t(__comp, _Pair_alloc_type(__a))
		{
		}

		map(const map &__x)
		//:  _M_t(__x._M_t)
		{
		}

		// template <typename _InputIterator>
		// map(_InputIterator __first, _InputIterator __last)
		// 	: _M_t()
		// {
		// 	_M_t._M_insert_unique(__first, __last);
		// }

		// template <typename _InputIterator>
		// map(_InputIterator __first, _InputIterator __last,
		// 	const _Compare &__comp,
		// 	const allocator_type &__a = allocator_type())
		// 	: _M_t(__comp, _Pair_alloc_type(__a))
		// {
		// 	_M_t._M_insert_unique(__first, __last);
		// }

		map &operator=(const map &__x)
		{
			// _M_t = __x._M_t;
			return *this;
		}

		allocator_type get_allocator() const
		{
			return allocator_type(); //_M_t.get_allocator());
		}

		// iterator begin()
		// {
		// 	return _M_t.begin();
		// }

		// const_iterator begin() const
		// {
		// 	return _M_t.begin();
		// }

		// iterator end()
		// {
		// 	return _M_t.end();
		// }

		// const_iterator end() const
		// {
		// 	return _M_t.end();
		// }

		// reverse_iterator rbegin()
		// {
		// 	return _M_t.rbegin();
		// }

		// const_reverse_iterator rbegin() const
		// {
		// 	return _M_t.rbegin();
		// }

		// reverse_iterator rend()
		// {
		// 	return _M_t.rend();
		// }

		// const_reverse_iterator rend() const
		// {
		// 	return _M_t.rend();
		// }

		// bool empty() const
		// {
		// 	return _M_t.empty();
		// }

		// size_type size() const
		// {
		// 	return _M_t.size();
		// }

		// size_type max_size() const
		// {
		// 	return _M_t.max_size();
		// }

		// mapped_type &operator[](const key_type &__k)
		// {
		// 	iterator __i = lower_bound(__k);
		// 	// __i->first is greater than or equivalent to __k.
		// 	if (__i == end() || key_comp()(__k, (*__i).first))

		// 		__i = insert(__i, value_type(__k, mapped_type()));
		// 	return (*__i).second;
		// }

		// mapped_type &at(const key_type &__k)
		// {
		// 	iterator __i = lower_bound(__k);
		// 	if (__i == end() || key_comp()(__k, (*__i).first))
		// 		__throw_out_of_range(__N("map::at"));
		// 	return (*__i).second;
		// }

		// const mapped_type &at(const key_type &__k) const
		// {
		// 	const_iterator __i = lower_bound(__k);
		// 	if (__i == end() || key_comp()(__k, (*__i).first))
		// 		__throw_out_of_range(__N("map::at"));
		// 	return (*__i).second;
		// }

		// ft::pair<iterator, bool> insert(const value_type &__x)
		// {
		// 	return _M_t._M_insert_unique(__x);
		// }

		// iterator insert(iterator __position, const value_type &__x)
		// {
		// 	return _M_t._M_insert_unique_(__position, __x);
		// }

		// template <typename _InputIterator>
		// void insert(_InputIterator __first, _InputIterator __last)
		// {
		// 	_M_t._M_insert_unique(__first, __last);
		// }

		// void erase(iterator __position)
		// {
		// 	_M_t.erase(__position);
		// }

		// size_type erase(const key_type &__x)
		// {
		// 	return _M_t.erase(__x);
		// }

		// void erase(iterator __first, iterator __last)
		// {
		// 	_M_t.erase(__first, __last);
		// }

		// void swap(map &__x)
		// {
		// 	_M_t.swap(__x._M_t);
		// }

		// void clear()
		// {
		// 	_M_t.clear();
		// }

		// key_compare key_comp() const
		// {
		// 	return _M_t.key_comp();
		// }

		// value_compare value_comp() const
		// {
		// 	return value_compare(_M_t.key_comp());
		// }

		// iterator find(const key_type &__x)
		// {
		// 	return _M_t.find(__x);
		// }

		// const_iterator find(const key_type &__x) const
		// {
		// 	return _M_t.find(__x);
		// }

		// size_type count(const key_type &__x) const
		// {
		// 	return _M_t.find(__x) == _M_t.end() ? 0 : 1;
		// }

		// iterator lower_bound(const key_type &__x)
		// {
		// 	return _M_t.lower_bound(__x);
		// }

		// const_iterator lower_bound(const key_type &__x) const
		// {
		// 	return _M_t.lower_bound(__x);
		// }

		// iterator upper_bound(const key_type &__x)
		// {
		// 	return _M_t.upper_bound(__x);
		// }

		// const_iterator upper_bound(const key_type &__x) const
		// {
		// 	return _M_t.upper_bound(__x);
		// }

		// ft::pair<iterator, iterator> equal_range(const key_type &__x)
		// {
		// 	return _M_t.equal_range(__x);
		// }

		// ft::pair<const_iterator, const_iterator> equal_range(const key_type &__x) const
		// {
		// 	return _M_t.equal_range(__x);
		// }

		template <typename _K1, typename _T1, typename _C1, typename _A1>
		friend bool operator==(const map<_K1, _T1, _C1, _A1> &,
							   const map<_K1, _T1, _C1, _A1> &);

		template <typename _K1, typename _T1, typename _C1, typename _A1>
		friend bool operator<(const map<_K1, _T1, _C1, _A1> &,
							  const map<_K1, _T1, _C1, _A1> &);
	};

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator==(const map<_Key, _Tp, _Compare, _Alloc> &__x,
					const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return __x._M_t == __y._M_t;
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator<(const map<_Key, _Tp, _Compare, _Alloc> &__x,
				   const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return __x._M_t < __y._M_t;
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator!=(const map<_Key, _Tp, _Compare, _Alloc> &__x,
					const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator>(const map<_Key, _Tp, _Compare, _Alloc> &__x,
				   const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return __y < __x;
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator<=(const map<_Key, _Tp, _Compare, _Alloc> &__x,
					const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator>=(const map<_Key, _Tp, _Compare, _Alloc> &__x,
					const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return !(__x < __y);
	}

	// template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	// void swap(map<_Key, _Tp, _Compare, _Alloc> &__x,
	// 		  map<_Key, _Tp, _Compare, _Alloc> &__y)
	// {
	// 	__x.swap(__y);
	// }

}

#endif
