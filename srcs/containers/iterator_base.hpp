/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_base.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/07/31 11:26:24 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_BASE_HPP
#define ITERATOR_BASE_HPP

#include <cstddef>

namespace ft
{
	/*
	** --------------------------------- ITERATORS  ---------------------------
	*/
	/*
	 * This is a base class template that can be used to derive iterator classes from it.
	 * It is not an iterator class and does not provide any of the functionality an iterator
	 * is expected to have.
	 *
	 * This base class only provides some member types, which in fact are not required to be
	 * present in any iterator type (iterator types have no specific member requirements),
	 * but they might be useful, since they define the members needed for the default
	 * iterator_traits class template to generate the appropriate instantiation automatically
	 * (and such instantiation is required to be valid for all iterator types).
	 *
	 * It is defined as:
	 */
	template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
			  typename _Pointer = _Tp *, typename _Reference = _Tp &>
	struct iterator
	{
		typedef _Category iterator_category;
		typedef _Tp value_type;
		typedef _Distance difference_type;
		typedef _Pointer pointer;
		typedef _Reference reference;
	};

	/*
	** --------------------------------- iterator_category ---------------------------
	*/
	/*
	 *
	 * Input iterators are iterators that can be used in sequential input
	 * operations, where each value pointed by the iterator is read only
	 * once and then the iterator is incremented.
	 *
	 * All forward, bidirectional and random-access iterators are also
	 * valid input iterators.
	 *
	 * There is not a single type of input iterator: Each container
	 * may define its own specific iterator type able to iterate through
	 * it and access its elements. But all input iterators support
	 * -at least- the following operations:
	 * see here https://cplusplus.com/reference/iterator/InputIterator/
	 */
	struct input_iterator_tag
	{
	};

	/*
	 * Traits class defining properties of iterators.
	 *
	 * Standard algorithms determine certain properties of the iterators
	 * passed to them and the range they represent by using the members of
	 * the corresponding iterator_traits instantiation.
	 *
	 * For every iterator type, a corresponding specialization of
	 * iterator_traits class template shall be defined, with at least
	 * the following member types defined:
	 * see here https://cplusplus.com/reference/iterator/OutputIterator/
	 */
	struct output_iterator_tag
	{
	};

	/*
	 * Forward iterators are iterators that can be used to access the sequence
	 * of elements in a range in the direction that goes from its beginning
	 * towards its end.
	 *
	 * Performing operations on a forward iterator that is dereferenceable
	 * never makes its iterator value non-dereferenceable. This enables
	 * algorithms that use this category of iterators to use multiple copies
	 * of an iterator to pass more than once by the same iterator values.
	 *
	 * All bidirectional and random-access iterators are also valid forward
	 * iterators.
	 *
	 * There is not a single type of forward iterator: Each container may
	 * define its own specific iterator type able to iterate through it and
	 * access its elements. But all forward iterators support -at least- the
	 * following operations:
	 * see here https://cplusplus.com/reference/iterator/ForwardIterator/
	 */

	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	/*
	 * Bidirectional iterators are iterators that can be used to access the
	 * sequence of elements in a range in both directions (towards the end
	 * and towards the beginning).
	 *
	 * All random-access iterators are also valid bidirectional iterators.
	 *
	 * There is not a single type of bidirectional iterator: Each container
	 * may define its own specific iterator type able to iterate through it
	 * and access its elements.
	 *
	 * Bidirectional iterators have the same properties as forward iterators,
	 * with the only difference that they can also be decremented:
	 * see here https://cplusplus.com/reference/iterator/BidirectionalIterator/
	 */
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};

	/*
	 * Random-access iterators are iterators that can be used to access
	 * elements at an arbitrary offset position relative to the element they
	 * point to, offering the same functionality as pointers.
	 *
	 * Random-access iterators are the most complete iterators in terms of
	 * functionality. All pointer types are also valid random-access
	 * iterators.
	 *
	 * There is not a single type of random-access iterator: Each container
	 * may define its own specific iterator type able to iterate through it
	 * and access its elements. But all random access iterators support -at
	 * least- the following operations:
	 * see here https://cplusplus.com/reference/iterator/RandomAccessIterator/
	 */
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};
}
#endif
