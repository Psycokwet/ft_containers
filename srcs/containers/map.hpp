/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:05:33 by scarboni          #+#    #+#             */
/*   Updated: 2022/09/02 10:02:36 by scarboni         ###   ########.fr       */
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

	template <typename _Key,									   // map::key_type
			  typename _Tp,										   // map::mapped_type
			  typename _Compare = std::less<_Key>,				   // map::key_compare
			  typename _Alloc = std::allocator<ft::pair<_Key, _Tp> // bug indent
											   >				   // map::allocator_type
			  >
	class map
	{
		/*
		** --------------------------------- PUBLIC MEMBERS ---------------------------
		*/
		// complete

	public:
		class value_compare;
		typedef _Key key_type;
		typedef _Tp mapped_type;
		typedef ft::pair<_Key, _Tp> value_type;
		typedef _Compare key_compare;
		typedef value_compare value_compare;
		typedef _Alloc allocator_type;

	private:
		typedef _Rb_tree<key_type, value_type, key_compare, allocator_type>
			_Tree_type;
		_Tree_type _t;

	public:
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;

		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename _Tree_type::iterator iterator;
		typedef typename _Tree_type::const_iterator const_iterator;

		// typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef typename _Tree_type::difference_type difference_type;
		typedef typename _Tree_type::size_type size_type;

	public:
		/*
		** --------------------------------- VALUE COMPARE  ---------------------------
		*/
		class value_compare // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			: public std::binary_function<value_type, value_type, bool>
		{

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
		/*
		** --------------------------------- CONSTRUCTORS  ---------------------------
		*/
		// done
		//  empty (1)
		explicit map(const _Compare &__comp = key_compare(),
					 const allocator_type &__a = allocator_type())
			: _t(__comp, __a)
		{
		}

		// range (2)
		template <typename _InputIterator>
		map(_InputIterator __first, _InputIterator __last,
			const _Compare &__comp = key_compare(),
			const allocator_type &__a = allocator_type())
			: _t(__comp, __a)
		{
			insert(__first, __last);
		}

		// copy (3)
		map(const map &__x)
			: _t(__x._t)
		{
			insert(__x.begin(), __x.end());
		}

		/*
		** --------------------------------- Copy container content  ---------------------------
		*/

		map &operator=(const map &__x)
		{
			_t = __x._t;
			insert(__x.begin(), __x.end());
			return *this;
		}

		/*
		** --------------------------------- ITERATORS ---------------------------
		*/
		// reverse_iterators TODO
		iterator begin()
		{
			return _t.begin();
		}

		const_iterator begin() const
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		const_iterator end() const
		{
			return _t.end();
		}

		// reverse_iterator rbegin()
		// {
		// 	return _t.rbegin();
		// }

		// const_reverse_iterator rbegin() const
		// {
		// 	return _t.rbegin();
		// }

		// reverse_iterator rend()
		// {
		// 	return _t.rend();
		// }

		// const_reverse_iterator rend() const
		// {
		// 	return _t.rend();
		// }

		/*
		** --------------------------------- CAPACITY ---------------------------
		*/
		bool empty() const
		{
			return _t.empty();
		}

		size_type size() const
		{
			return _t.size();
		}

		size_type max_size() const
		{
			return _t.max_size();
		}

		/*
		** --------------------------------- ELEMENTS ACCESS  ---------------------------
		*/
		// done
		mapped_type &operator[](const key_type &__k)
		{
			return _t.insertNode(__k)->second;
		}

		// oooops it was c++11
		//  mapped_type &at(const key_type &__k)
		//  {
		//  	value_type *tmp = _t.findNode(__k);
		//  	if (!tmp)
		//  		throw std::out_of_range("map::at");
		//  	return tmp->second;
		//  }

		// const mapped_type &at(const key_type &__k) const
		// {
		// 	value_type *tmp = _t.findNode(__k);
		// 	if (!tmp)
		// 		throw std::out_of_range("map::at");
		// 	return tmp->second;
		// }

		/*
		** --------------------------------- MODIFIERS ---------------------------
		*/
		// TODO swap
		ft::pair<iterator, bool> insert(const value_type &__x)
		{
			bool second = true;
			value_type *tmp = _t.findNode(__x.first);
			if (!tmp)
				second = false;
			return ft::make_pair(_t.insertNodeGetIterator(__x), second);
		}

		iterator insert(iterator __position, const value_type &__x)
		{
			(void)__position;
			return this->insert(__x).first;
		}

		template <typename _InputIterator>
		void insert(_InputIterator __first, _InputIterator __last)
		{
			while (__first != __last)
				this->insert(*__first++);
		}

		void erase(iterator __position)
		{
			_t.deleteNode(__position->first);
		}

		size_type erase(const key_type &__x)
		{
			return _t.deleteNode(__x) == true ? 1 : 0;
		}

		void erase(iterator __first, iterator __last)
		{
			while (__first != __last)
				this->erase(__first++);
		}

		// void swap(map &__x)
		// {
		// 	_t.swap(__x._t);
		// }

		void clear()
		{
			_t.clear();
		}

		/*
		** --------------------------------- OBSERVERS ---------------------------
		*/
		// TODO
		//  key_compare key_comp() const
		//  {
		//  	return _t.key_comp();
		//  }

		// value_compare value_comp() const
		// {
		// 	return value_compare(_t.key_comp());
		// }

		/*
		** --------------------------------- OPERATIONS ---------------------------
		*/
		// TODO most of it
		iterator find(const key_type &__x)
		{
			value_type *tmp = _t.findNode(__x);
			if (!tmp)
				return iterator(_t.end());
			return iterator(tmp);
		}

		const_iterator find(const key_type &__x) const
		{
			value_type *tmp = _t.findNode(__x);
			if (!tmp)
				return const_iterator(_t.end());
			return const_iterator(tmp);
		}

		// size_type count(const key_type &__x) const
		// {
		// 	return _t.find(__x) == _t.end() ? 0 : 1;
		// }

		// iterator lower_bound(const key_type &__x)
		// {
		// 	return _t.lower_bound(__x);
		// }

		// const_iterator lower_bound(const key_type &__x) const
		// {
		// 	return _t.lower_bound(__x);
		// }

		// iterator upper_bound(const key_type &__x)
		// {
		// 	return _t.upper_bound(__x);
		// }

		// const_iterator upper_bound(const key_type &__x) const
		// {
		// 	return _t.upper_bound(__x);
		// }

		// ft::pair<iterator, iterator> equal_range(const key_type &__x)
		// {
		// 	return _t.equal_range(__x);
		// }

		// ft::pair<const_iterator, const_iterator> equal_range(const key_type &__x) const
		// {
		// 	return _t.equal_range(__x);
		// }

		/*
		** --------------------------------- ALLOCATOR ---------------------------
		*/
		allocator_type get_allocator() const
		{
			return _t.get_allocator();
		}

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
		return __x._t == __y._t;
	}

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator<(const map<_Key, _Tp, _Compare, _Alloc> &__x,
				   const map<_Key, _Tp, _Compare, _Alloc> &__y)
	{
		return __x._t < __y._t;
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
