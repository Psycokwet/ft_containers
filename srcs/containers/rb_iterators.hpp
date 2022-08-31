/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterators.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:11:55 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/29 19:56:39 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_ITERATOR_HPP
#define RB_ITERATOR_HPP

#include "rb_tree.hpp"

namespace ft
{
	template <typename _Tree,
			  typename _Tp,
			  bool _isConst>
	struct _possible_const_members
	{
	public:
		typedef _Tp value_type;
		typedef typename _Tree::_Rb_tree_node_base _Base;
		typedef _Base *_Link_type;
		typedef _Tp &reference;
		typedef _Tp *pointer;
		typedef typename _Base::_Base_ptr _Base_ptr;
	};

	template <typename _Tree,
			  typename _Tp>
	struct _possible_const_members<_Tree, _Tp, true>
	{
	public:
		typedef const _Tp value_type;
		typedef typename _Tree::_Rb_tree_node_base _Base;
		typedef _Base *_Link_type;
		typedef const _Tp &reference;
		typedef const _Tp *pointer;
		typedef typename _Base::_Const_Base_ptr _Base_ptr;
	};

	template <typename _Tree,
			  typename _Tp,
			  bool _isConst,
			  typename _Traits = _possible_const_members<_Tree, _Tp, _isConst> // bug indent
			  >
	struct _Rb_tree_iterator
	{
		typedef typename _Traits::value_type value_type;
		typedef typename _Traits::_Base _Base;
		typedef typename _Traits::_Link_type _Link_type;
		typedef typename _Traits::reference reference;
		typedef typename _Traits::pointer pointer;
		typedef typename _Traits::_Base_ptr _Base_ptr;
		_Base_ptr _node;
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef _Rb_tree_iterator<_Tree, _Tp, _isConst> _Self;

		_Rb_tree_iterator() : _node() {}

		explicit _Rb_tree_iterator(_Base_ptr __x) : _node(__x) {}

		reference operator*() const { return _node->val(); }

		pointer operator->() const { return _node->val_ptr(); }

		_Self &operator++()
		{
			_node = _Tree::getNextNode(_node);
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_node = _Tree::getNextNode(_node);
			return __tmp;
		}

		_Self &operator--()
		{
			_node = _Tree::getPrevNode(_node);
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			_node = _Tree::getPrevNode(_node);
			return __tmp;
		}

		bool operator==(const _Self &__x) const { return _node == __x._node; }

		bool operator!=(const _Self &__x) const { return _node != __x._node; }
	};

}
#endif
