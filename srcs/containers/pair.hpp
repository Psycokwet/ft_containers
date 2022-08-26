/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/25 20:32:26 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <typename _U1, typename _U2>
	class __pair_base
	{
	};

	/**
	 *  @brief Struct holding two objects of arbitrary type.
	 *
	 *  @tparam _T1  Type of first object.
	 *  @tparam _T2  Type of second object.
	 */
	template <typename _T1, typename _T2>
	struct pair : private __pair_base<_T1, _T2>
	{
		typedef _T1 first_type;	 //	The first template parameter (T1)
		typedef _T2 second_type; // The second template parameter (T2)

		_T1 first;	// The first value in the pair
		_T2 second; // The second value in the pair

		/* Constructs a pair object with its elements value-initialized. */
		pair() : first(), second() {}

		/* The object is initialized with the contents of the pr pair object.
		 * The corresponding member of pr is passed to the constructor of each of its members
		 */
		template <typename _U1, typename _U2>
		pair(const pair<_U1, _U2> &__p) : first(__p.first), second(__p.second) {}

		/* Member first is constructed with a and member second with b. */
		pair(const _T1 &__a, const _T2 &__b) : first(__a), second(__b) {}

		// implicitly declared:
		// pair& operator= (const pair& pr);
	};

	template <typename _T1, typename _T2>
	bool operator==(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y) { return __x.first == __y.first && __x.second == __y.second; }

	template <typename _T1, typename _T2>
	bool operator<(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y) { return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second); }

	template <typename _T1, typename _T2>
	bool operator!=(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y) { return !(__x == __y); }

	template <typename _T1, typename _T2>
	bool operator>(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y) { return __y < __x; }

	template <typename _T1, typename _T2>
	bool operator<=(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y) { return !(__y < __x); }

	template <typename _T1, typename _T2>
	bool operator>=(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y) { return !(__x < __y); }

	/**
	 * Constructs a pair object with its first element set to x and its second element set to y.
	 * The template types can be implicitly deduced from the arguments passed to make_pair.
	 * pair objects can be constructed from other pair objects containing different types, if the respective types are implicitly convertible.
	 */
	template <typename _T1, typename _T2>
	pair<_T1, _T2> make_pair(_T1 __x, _T2 __y) { return pair<_T1, _T2>(__x, __y); }

}

#endif
