/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/09/05 08:14:00 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
	template <typename _InputIterator1, typename _InputIterator2>
	bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2)
	{
		while (__first1 != __last1)
		{
			if (__first2 == __last2 || (*__first1 < *__first2))
				return false;
			if (*__first2 < *__first1)
				return true;
			++__first1, ++__first2;
		}
		return true;
	}
	template <typename _InputIterator1, typename _InputIterator2>
	bool equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2)
	{
		while (__first1 != __last1)
		{
			if (__first2 == __last2 || !(*__first1 == *__first2))
				return false;
			++__first1, ++__first2;
		}
		return (*__first1 == *__first2);
	}
	// template <typename Something>
	// void _swap(Something *__x, Something *__y)
	// {
	// 	Something *tmp = *__x;
	// 	*__x = *__y;
	// 	*__y = *tmp;
	// }
	template <typename Something>
	void _swap(Something &__x, Something &__y)
	{
		Something tmp = __x;
		__x = __y;
		__y = tmp;
	}
}
#endif
