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

// #include <sstream>			  add this include on files using SSTR
#define SSTR(x) static_cast<std::ostringstream &>(            \
					(std ::ostringstream() << std::dec << x)) \
					.str()

#define FOR_EACH_MACRO(LIST, SUB_MACRO) \
	LIST(SUB_MACRO)

// https://godbolt.org/ to see expanded macros, g++ -E
#endif