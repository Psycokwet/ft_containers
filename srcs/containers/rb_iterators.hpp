/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterators.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/28 17:16:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "iterator_base.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <typename _Tp, bool _isConst,
			  // for nodes
			  typename _Key,
			  typename _Val = ft::pair<_Key, void>,
			  typename _Compare = std::less<_Key>,
			  typename _Alloc = std::allocator<_Val> // bug indent
			  >
	struct _possible_const_members
	{
		typedef _Tp value_type;
		typedef typename ft::_Rb_tree::_Rb_tree_node_base<_Tp> *_Link_type;
		typedef _Tp &reference;
		typedef _Tp *pointer;
		typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
	};

	template <typename _Tp>
	struct _possible_const_members<_Tp, true>
	{
		typedef const _Tp value_type;
		typedef typename const ft::_Rb_tree::_Rb_tree_node_base<_Tp> *_Link_type;
		typedef const _Tp &reference;
		typedef const _Tp *pointer;
		typedef _Rb_tree_node_base::_Const_Base_ptr _Base_ptr;
	};

	template <typename _Tp, bool _isConst>
	struct _Rb_tree_iterator : public _possible_const_members<_Tp, _isConst>
	{
		// typedef _Tp value_type;
		// typedef typename enable_if<_isConst, const _Tp>::type value_type;
		// typedef typename enable_if<!_isConst, _Tp>::type value_type;
		// typedef _Tp value_type;

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		typedef _Rb_tree_iterator<_Tp, _isConst> _Self;
		typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;

		_Rb_tree_iterator() : _node() {}
		explicit _Rb_tree_iterator(_Base_ptr __x) : _node(__x) {}

		reference operator*() const { return _node->val(); }

		pointer operator->() const { return _node->val_ptr(); }

		_Self &operator++()
		{
			// _node = _node->getNextNode();
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			// _node = _node->getNextNode();
			return __tmp;
		}

		_Self &operator--()
		{
			// _node = _node->getPrevNode();
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			// _node = _node->getPrevNode();
			return __tmp;
		}

		bool operator==(const _Self &__x) const { return _node == __x._node; }

		bool operator!=(const _Self &__x) const { return _node != __x._node; }

		_Base_ptr _node;
	};

}
#endif
