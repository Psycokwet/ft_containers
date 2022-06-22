/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/06/22 20:32:51 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

namespace ft
{
	template <typename _Tp, typename _Sequence = std::vector<_Tp> >
	class stack

	{
	public:
		typedef typename _Sequence::value_type value_type;
		typedef typename _Sequence::reference reference;
		typedef typename _Sequence::const_reference const_reference;
		typedef typename _Sequence::size_type size_type;
		typedef _Sequence container_type;

	protected:
		//  See queue::c for notes on this name.
		_Sequence c;

	public:
		// explicit allow to avoid automatic conversion of a container to my stack for example
		explicit stack(const _Sequence &__c = _Sequence())
			: c(__c) {}

		/**
		 *  Returns true if the %stack is empty.
		 */
		bool empty() const
		{
			return c.empty();
		}

		/**  Returns the number of elements in the %stack.  */
		size_type size() const
		{
			return c.size();
		}

		/**
		 *  Returns a read/write reference to the data at the first
		 *  element of the %stack.
		 */
		reference top()
		{
			__glibcxx_requires_nonempty();
			return c.back();
		}

		/**
		 *  Returns a read-only (constant) reference to the data at the first
		 *  element of the %stack.
		 */
		const_reference top() const
		{
			__glibcxx_requires_nonempty();
			return c.back();
		}

		/**
		 *  @brief  Add data to the top of the %stack.
		 *  @param  __x  Data to be added.
		 *
		 *  This is a typical %stack operation.  The function creates an
		 *  element at the top of the %stack and assigns the given data
		 *  to it.  The time complexity of the operation depends on the
		 *  underlying sequence.
		 */
		void push(const value_type &__x)
		{
			c.push_back(__x);
		}

		/**
		 *  @brief  Removes first element.
		 *
		 *  This is a typical %stack operation.  It shrinks the %stack
		 *  by one.  The time complexity of the operation depends on the
		 *  underlying sequence.
		 *
		 *  Note that no data is returned, and if the first element's
		 *  data is needed, it should be retrieved before pop() is
		 *  called.
		 */
		void pop()
		{
			__glibcxx_requires_nonempty();
			c.pop_back();
		}

		template <typename _Tp1, typename _Seq1>
		friend bool operator==(const stack<_Tp1, _Seq1> &, const stack<_Tp1, _Seq1> &);

		template <typename _Tp1, typename _Seq1>
		friend bool operator<(const stack<_Tp1, _Seq1> &, const stack<_Tp1, _Seq1> &);
	};
}

#endif