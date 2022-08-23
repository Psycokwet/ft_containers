/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:05:33 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/23 17:03:38 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "iterator_traits.hpp"

namespace ft
{

	enum _Rb_tree_color
	{
		_S_red = false,
		_S_black = true
	};

	struct _Rb_tree_node_base
	{
		typedef _Rb_tree_node_base *_Base_ptr;
		typedef const _Rb_tree_node_base *_Const_Base_ptr;

		_Rb_tree_color _M_color;
		_Base_ptr _M_parent;
		_Base_ptr _M_left;
		_Base_ptr _M_right;
	};

	template <typename _Key, typename _Val,
			  typename _Compare, typename _Alloc = std::allocator<_Val> >
	class _Rb_tree
	{

	public:
		typedef _Alloc allocator_type;
		allocator_type _Tp_alloc_type;

	protected:
		typedef _Rb_tree_node_base *_Base_ptr;
		typedef const _Rb_tree_node_base *_Const_Base_ptr;

	private:
		typedef _Compare _base_key_compare;
		typedef allocator_type _node_allocator;
		_Base_ptr _root;

	public:
		typedef _Key key_type;
		typedef _Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		// allocation/deallocation
		_Rb_tree()
		{
		}

		_Rb_tree(const _Compare &__comp,
				 const allocator_type &__a = allocator_type())
			: _base_key_compare(__comp), _node_allocator(__a), _root(NULL)
		{
		}

		_Rb_tree(const _Rb_tree &__x)
			: _base_key_compare(__x.__comp), _node_allocator(__x.__a), _root(NULL)
		{
			// if (__x._root != NULL)
			// 	_root = _M_copy(__x);
		}

		~_Rb_tree()
		{
			// _M_erase(_M_begin());
		}
	};

}

#endif
