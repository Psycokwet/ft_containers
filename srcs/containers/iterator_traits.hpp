/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/01 15:26:57 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "iterator_base.hpp"
#include <cstddef>

namespace ft
{

	/*
	** --------------------------------- ITERATORS TRAITS ---------------------------
	*/
	/*
	 * Traits class defining properties of iterators.
	 * Standard algorithms determine certain properties of the iterators passed
	 * to them and the range they represent by using the members of the
	 * corresponding iterator_traits instantiation.
	 * For every iterator type, a corresponding specialization of iterator_traits
	 * class template shall be defined, with at least the following member types
	 * defined:
	 */

	template <typename _Iterator>
	struct iterator_traits
	{
		typedef typename _Iterator::iterator_category iterator_category;
		typedef typename _Iterator::value_type value_type;
		typedef typename _Iterator::difference_type difference_type;
		typedef typename _Iterator::pointer pointer;
		typedef typename _Iterator::reference reference;
	};
	template <typename _Tp>
	struct iterator_traits<_Tp *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef ptrdiff_t difference_type;
		typedef _Tp *pointer;
		typedef _Tp &reference;
	};
	template <typename _Tp>
	struct iterator_traits<const _Tp *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef _Tp value_type;
		typedef ptrdiff_t difference_type;
		typedef const _Tp *pointer;
		typedef const _Tp &reference;
	};

}
#endif
