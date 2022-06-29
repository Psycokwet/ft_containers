/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:15:42 by scarboni          #+#    #+#             */
/*   Updated: 2022/06/23 10:52:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <vector.hpp>
namespace ft

{
	template <typename _Tp, typename _Sequence = ft::vector<_Tp> >
	class stack
	{
		template <typename _Tp1, typename _Seq1>
		friend bool
		operator==(const stack<_Tp1, _Seq1> &, const stack<_Tp1, _Seq1> &);

		template <typename _Tp1, typename _Seq1>
		friend bool
		operator<(const stack<_Tp1, _Seq1> &, const stack<_Tp1, _Seq1> &);

	public:
		typedef typename _Sequence::value_type value_type;
		typedef typename _Sequence::reference reference;
		typedef typename _Sequence::const_reference const_reference;
		typedef typename _Sequence::size_type size_type;
		typedef _Sequence container_type;

	protected:
		_Sequence c;

	public:
		explicit stack(const _Sequence &__c = _Sequence())
			: c(__c)
		{
		}

		/*
		 *  Returns true if the stack is empty.
		 */
		bool empty() const
		{
			return c.empty();
		}

		/*  Returns the number of elements in the stack.  */
		size_type size() const
		{
			return c.size();
		}

		/*
		 *  Returns a read/write reference to the data at the first
		 *  element of the stack.
		 */
		reference top()
		{
			return c.back();
		}

		/*
		 *  Returns a read-only (constant) reference to the data at the first
		 *  element of the stack.
		 */
		const_reference top() const
		{
			return c.back();
		}

		/*
		 *  @brief  Add data to the top of the stack.
		 *  @param  __x  Data to be added.
		 *
		 *  This is a typical stack operation.  The function creates an
		 *  element at the top of the stack and assigns the given data
		 *  to it.  The time complexity of the operation depends on the
		 *  underlying sequence.
		 */
		void push(const value_type &__x)
		{
			c.push_back(__x);
		}

		/*
		 *  @brief  Removes first element.
		 *
		 *  This is a typical stack operation.  It shrinks the stack
		 *  by one.  The time complexity of the operation depends on the
		 *  underlying sequence.
		 *
		 *  Note that no data is returned, and if the first element's
		 *  data is needed, it should be retrieved before pop() is
		 *  called.
		 */
		void pop()
		{
			c.pop_back();
		}
	};

	/*
	 *  @brief  Stack equality comparison.
	 *  @param  __x  A stack.
	 *  @param  __y  A stack of the same type as @a __x.
	 *  @return  True iff the size and elements of the stacks are equal.
	 *
	 *  This is an equivalence relation.  Complexity and semantics
	 *  depend on the underlying sequence type, but the expected rules
	 *  are: this relation is linear in the size of the sequences, and
	 *  stacks are considered equivalent if their sequences compare
	 *  equal.
	 */
	template <typename _Tp, typename _Seq>
	inline bool operator==(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return __x.c == __y.c;
	}

	/*
	 *  @brief  Stack ordering relation.
	 *  @param  __x  A stack.
	 *  @param  __y  A stack of the same type as @a x.
	 *  @return  True iff @a x is lexicographically less than @a __y.
	 *
	 *  This is an total ordering relation.  Complexity and semantics
	 *  depend on the underlying sequence type, but the expected rules
	 *  are: this relation is linear in the size of the sequences, the
	 *  elements must be comparable with @c <, and
	 *  std::lexicographical_compare() is usually used to make the
	 *  determination.
	 */
	template <typename _Tp, typename _Seq>
	inline bool operator<(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return __x.c < __y.c;
	}

	/// Based on operator==
	template <typename _Tp, typename _Seq>
	inline bool operator!=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return !(__x == __y);
	}

	/// Based on operator<
	template <typename _Tp, typename _Seq>
	inline bool operator>(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return __y < __x;
	}

	/// Based on operator<
	template <typename _Tp, typename _Seq>
	inline bool operator<=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return !(__y < __x);
	}

	/// Based on operator<
	template <typename _Tp, typename _Seq>
	inline bool operator>=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
	{
		return !(__x < __y);
	}

} // namespace

#endif