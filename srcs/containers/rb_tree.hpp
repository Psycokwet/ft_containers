/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:05:33 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/25 15:26:16 by scarboni         ###   ########.fr       */
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

	template <typename _Key,
			  typename _Val = ft::pair<_Key, void>,
			  typename _Compare = std::less<_Key>,
			  typename _Alloc = std::allocator<_Val> // bug indent
			  >
	class _Rb_tree
	{
	public:
		struct _Rb_tree_node_base
		{
			typedef _Rb_tree_node_base *_Base_ptr;
			typedef const _Rb_tree_node_base *_Const_Base_ptr;

			_Val _val;
			_Key _key;
			_Rb_tree_color _color;
			_Base_ptr _parent;
			_Base_ptr _left;
			_Base_ptr _right;
		};

		// https://alp.developpez.com/tutoriels/templaterebinding/
		typedef typename _Alloc::template rebind<_Rb_tree_node_base>::other allocator_type;

		allocator_type _Tp_alloc_type;

	private:
		typedef _Rb_tree_node_base _Base;
		typedef const _Rb_tree_node_base _Const_Base;
		typedef _Rb_tree_node_base *_Base_ptr;
		typedef const _Rb_tree_node_base *_Const_Base_ptr;

		typedef _Compare _base_key_compare;
		_Base_ptr _root;	// m_header
		size_t _node_count; // Keeps track of size of tree.

		_Base_ptr _get_node()
		{
			return _Tp_alloc_type.allocate(1);
		}

		_Base_ptr _create_node()
		{
			_Base_ptr node = _get_node();
			node = _init_node(node);
			// __tmp->
			// _construct_node(__tmp, __args);
			return node;
		}
		void _delete_node(_Base_ptr __x)
		{
			_Tp_alloc_type.deallocate(__x, 1);
		}

	public:
		typedef _Key key_type;
		typedef _Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		// typedef typename allocator_type::pointer pointer;				  //_Tp *
		// typedef typename allocator_type::const_pointer const_pointer;	  // const _Tp *
		// typedef typename allocator_type::reference reference;			  //_Tp &
		// typedef typename allocator_type::const_reference const_reference; // const _Tp &
		// allocation/deallocation
		_Rb_tree()
		{
			_root = NULL;
			_Key key = key_type();
			_Val val = value_type();

			insert(key, val);
			// _Base_ptr cc = _create_node();
			// insert(key_type(), value_type());
			_print();
			_delete_node(_root);
		}

		_Rb_tree(const _Compare &__comp,
				 const allocator_type &__a = allocator_type())
			: _base_key_compare(__comp), allocator_type(__a), _root(NULL)
		{
		}

		_Rb_tree(const _Rb_tree &__x)
			: _base_key_compare(__x.__comp), allocator_type(__x.__a), _root(NULL)
		{
			// if (__x._root != NULL)
			// 	_root = _copy(__x);
		}

		~_Rb_tree()
		{
			// _erase(_begin());
		}

	public:
		void insert(_Key __key, _Val __val)
		{
			_Base_ptr node = _create_node();
			node->_key = __key;
			node->_val = __val;
			_addNode(node);
		}
		_Base_ptr _init_node(_Base_ptr __node)
		{
			_Base tmp;
			tmp._key = key_type();
			tmp._val = value_type();
			tmp._parent = NULL;
			tmp._left = NULL;
			tmp._right = NULL;
			tmp._color = _S_black;
			_Tp_alloc_type.construct(__node, tmp);
			return __node;
		}

	private:
		void _printInt(_Base_ptr __node, std::string __indent = "", char __src = 'R')
		{
			if (__node == NULL)
				return;
			std::cout << __indent;
			__indent += __src == 'r' ? "|" : __src == 'l' ? " "
														  : "";
			__indent += "  ";
			std::cout << __src
					  << "----"
					  << __node->_key
					  << "=="
					  << __node->_val.first
					  << ":"
					  << __node->_val.second
					  << "["
					  << (__node->_color == _S_red ? "RED" : "BLACK")
					  << "]"
					  << std::endl;
			_printInt(__node->_left, __indent, 'r');
			_printInt(__node->_right, __indent, 'l');
		}
		void _print()
		{
			std::cout << "_______Start print tree______\n";
			if (_root)
				_printInt(_root);
			std::cout << "_______End print tree______\n";
		}
		void _addNode(_Base_ptr node)
		{
			node->_color = _S_red;

			_Base_ptr y = NULL;
			_Base_ptr x = _root;

			while (x != NULL)
			{
				y = x;
				if (node->_key == x->_key)
				{
					x->_val = node->_val;
					_delete_node(node);
					return;
				}
				if (node->_key < x->_key)
				{
					x = x->_left;
				}
				else
				{
					x = x->_right;
				}
			}

			node->_parent = y;
			if (y == NULL)
			{
				_root = node;
			}
			else if (node->_key < y->_key)
			{
				y->_left = node;
			}
			else
			{
				y->_right = node;
			}

			if (node->_parent == NULL)
			{
				node->_color = _S_black;
				return;
			}

			if (node->_parent->_parent == NULL)
			{
				return;
			}

			// insertFix(node);
		}
	};

}

#endif
