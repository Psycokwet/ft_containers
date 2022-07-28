/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/07/28 21:55:47 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include "macros.hpp"

namespace ft
{
	// is integral

	/*
	** All the next part is an adaptation of is_integral.
	** "is_integral" for this project in C++98 is a structure
	** that contain if the type given to it is a type from this list :
	**  - bool
	**  - char
	**  - char16_t
	**  - char32_t
	**  - wchar_t
	**  - signed char
	**  - short int
	**  - int
	**  - long int
	**  - long long int
	**  - unsigned char
	**  - unsigned short int
	**  - unsigned int
	**  - unsigned long int
	**  - unsigned long long int
	*/

	/*
	** @brief The basic struct of is_integral has
	** has a boolean ("value") that contain true if the type is from.
	** the list, otherwise false.
	*/
	template <bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T type;
		static const bool value = is_integral;
	};

	/*
	** @brief default template of the structure is_integral_type.
	** If the type given in argument is from the list, the structure
	** will be overide by nexts, in according to it type.
	** If the type given is argument isn't in the list,
	** stocked value will be false. So it's not a integral type.
	*/
	template <typename T>
	struct is_integral_type : public is_integral_res<false, T>
	{
	};

#define IS_INTEGRAL_LIST(FOR_EACH) \
	FOR_EACH(bool)                 \
	FOR_EACH(int)

	FOR_EACH_MACRO(IS_INTEGRAL_LIST)

	/*
	** @brief Give a structure who contain is the
	** typename given in template is integral or not,
	** stocked in "value".
	*/
	template <typename T>
	struct is_integral : public is_integral_type<T>
	{
	};

}

#endif
