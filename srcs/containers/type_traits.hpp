/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/07/28 22:39:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include "macros.hpp"
#include <uchar.h>

namespace ft
{
	/*
	** ---------------------------------- is integral ----------------------------------
	*/
	/* This template is designed to provide compile-time constants as types.
	 * It is used by several parts of the standard library as the base class for trait types,
	 * especially in their bool variant: see true_type and false_type.
	 * Its definition in the Standard Library has the same behavior as:
	 */
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() { return v; }
	};
	/*
	 * Instantiation of integral_constant to represent the bool value true.
	 */
	typedef integral_constant<bool, true> true_type;
	/*
	 * Instantiation of integral_constant to represent the bool value false.
	 */
	typedef integral_constant<bool, false> false_type;

	/*
	 * default template to cover all non fundamental integral type
	 */
	template <typename T>
	struct __is_integral_helper : public false_type
	{
	};

	/*
	 * Applied model for generating is_integral code for each integral types
	 */
#define IS_INTEGRAL(value)                                \
	template <>                                           \
	struct __is_integral_helper<value> : public true_type \
	{                                                     \
	};

	/*
	 * list of fundamental integral types
	 * All fundamental integral types, along with all their aliases (like those in cstdint),
	 * are considered integral types by this class, including their const and volatile
	 * qualified variants.
	 * Enums are not considered integral types in C++.
	 * char16_t and char32_t are not here because they are redundant with ints definition
	 */
#define IS_INTEGRAL_LIST(FOR_EACH) \
	FOR_EACH(bool)                 \
	FOR_EACH(char)                 \
	FOR_EACH(wchar_t)              \
	FOR_EACH(signed char)          \
	FOR_EACH(short int)            \
	FOR_EACH(int)                  \
	FOR_EACH(long int)             \
	FOR_EACH(long long int)        \
	FOR_EACH(unsigned char)        \
	FOR_EACH(unsigned short int)   \
	FOR_EACH(unsigned int)         \
	FOR_EACH(unsigned long int)    \
	FOR_EACH(unsigned long long int)

	/*
	 * Generation of corresponding code
	 */
	FOR_EACH_MACRO(IS_INTEGRAL_LIST, IS_INTEGRAL)

	/*
	 * Wrapper for user use
	 */
	template <typename T>
	struct is_integral : public __is_integral_helper<T>
	{
	};

}

#endif
