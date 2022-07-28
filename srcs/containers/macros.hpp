/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:19:46 by scarboni          #+#    #+#             */
/*   Updated: 2022/07/28 18:19:46 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
#define MACROS_H

#define IS_INTEGRAL(value)                                               \
	template <>                                                          \
	struct is_integral_type<value> : public is_integral_res<true, value> \
	{                                                                    \
	};

// expansion macro for enum value definition
#define APPLY_SUB_MACRO(name) IS_INTEGRAL(name)

/// declare the access function and define enum values
#define FOR_EACH_MACRO(LIST) \
	LIST(APPLY_SUB_MACRO)

#endif