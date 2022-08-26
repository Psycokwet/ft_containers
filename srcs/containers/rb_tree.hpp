/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:05:33 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/26 11:22:57 by scarboni         ###   ########.fr       */
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

	public:
		typedef _Key key_type;
		typedef _Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		_Rb_tree()
		{
			_root = NULL;
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
			std::cout << "deleting tree :" << std::endl;
			_print();

			_delete_tree();
			std::cout << "deleted" << std::endl;
		}

	public:
		_Val *insertNode(_Key __key, _Val __val = _Val())
		{
			// return _insert(__key, __val);
			_Val *v = &(_insert(__key, __val)->_val);
			_print();
			return v;
		}
		void findNode(_Key __key)
		{
			return _findNode(__key);
		}
		void deleteNode(_Key __key)
		{
			_findAndDeleteNodeFromTree(_root, __key);
		}

	private:
		/*
		** --------------------------------- ORGANIZE TREE  ---------------------------
		*/
	
		void deleteFix(_Base_ptr x)
		{
			_Base_ptr s;
			while (x != _root && x->_color == _S_black)
			{
				if (x == x->_parent->_left)
				{
					s = x->_parent->_right;
					if (s->_color == _S_red)
					{
						s->_color = _S_black;
						x->_parent->_color = _S_red;
						_leftRotate(x->_parent);
						s = x->_parent->_right;
					}

					if (s->_left->_color == _S_black && s->_right->_color == _S_black)
					{
						s->_color = _S_red;
						x = x->_parent;
					}
					else
					{
						if (s->_right->_color == _S_black)
						{
							s->_left->_color = _S_black;
							s->_color = _S_red;
							_rightRotate(s);
							s = x->_parent->_right;
						}

						s->_color = x->_parent->_color;
						x->_parent->_color = _S_black;
						s->_right->_color = _S_black;
						_leftRotate(x->_parent);
						x = _root;
					}
				}
				else
				{
					s = x->_parent->_left;
					if (s->_color == _S_red)
					{
						s->_color = _S_black;
						x->_parent->_color = _S_red;
						_rightRotate(x->_parent);
						s = x->_parent->_left;
					}

					if (s->_right->_color == _S_black && s->_right->_color == _S_black)
					{
						s->_color = _S_red;
						x = x->_parent;
					}
					else
					{
						if (s->_left->_color == _S_black)
						{
							s->_right->_color = _S_black;
							s->_color = _S_red;
							_leftRotate(s);
							s = x->_parent->_left;
						}

						s->_color = x->_parent->_color;
						x->_parent->_color = _S_black;
						s->_left->_color = _S_black;
						_rightRotate(x->_parent);
						x = _root;
					}
				}
			}
			x->_color = _S_black;
		}
		void _rbTransplant(_Base_ptr u, _Base_ptr v)
		{
			if (u->_parent == NULL)
				_root = v;
			else if (u == u->_parent->_left)
				u->_parent->_left = v;
			else
				u->_parent->_right = v;
			v->_parent = u->_parent;
		}

		void _leftRotate(_Base_ptr x)
		{
			_Base_ptr y = x->_right;
			x->_right = y->_left;
			if (y->_left != NULL)
				y->_left->_parent = x;
			y->_parent = x->_parent;
			if (x->_parent == NULL)
				_root = y;
			else if (x == x->_parent->_left)
				x->_parent->_left = y;
			else
				x->_parent->_right = y;
			y->_left = x;
			x->_parent = y;
		}

		void _rightRotate(_Base_ptr x)
		{
			_Base_ptr y = x->_left;
			x->_left = y->_right;
			if (y->_right != NULL)
				y->_right->_parent = x;
			y->_parent = x->_parent;
			if (x->_parent == NULL)
				_root = y;
			else if (x == x->_parent->_right)
				x->_parent->_right = y;
			else
				x->_parent->_left = y;
			y->_right = x;
			x->_parent = y;
		}

		void _balanceTree(_Base_ptr __k)
		{
			_Base_ptr u = NULL;
			while (__k->_parent->_color == _S_red)
			{
				if (__k->_parent == __k->_parent->_parent->_right)
				{
					u = __k->_parent->_parent->_left;
					if (u->_color == _S_red)
					{
						u->_color = _S_black;
						__k->_parent->_color = _S_black;
						__k->_parent->_parent->_color = _S_red;
						__k = __k->_parent->_parent;
					}
					else
					{
						if (__k == __k->_parent->_left)
						{
							__k = __k->_parent;
							_rightRotate(__k);
						}
						__k->_parent->_color = _S_black;
						__k->_parent->_parent->_color = _S_red;
						_leftRotate(__k->_parent->_parent);
					}
				}
				else
				{
					u = __k->_parent->_parent->_right;

					if (u->_color == _S_red)
					{
						u->_color = _S_black;
						__k->_parent->_color = _S_black;
						__k->_parent->_parent->_color = _S_red;
						__k = __k->_parent->_parent;
					}
					else
					{
						if (__k == __k->_parent->_right)
						{
							__k = __k->_parent;
							_leftRotate(__k);
						}
						__k->_parent->_color = _S_black;
						__k->_parent->_parent->_color = _S_red;
						_rightRotate(__k->_parent->_parent);
					}
				}
				if (__k == _root)
					break;
			}
			_root->_color = _S_black;
		}

		/*
		** --------------------------------- FIND  ---------------------------
		*/

		_Base_ptr _minimum(_Base_ptr __root)
		{
			while (__root->_left)
				__root = __root->_left;
			return __root;
		}

		_Base_ptr _maximum(_Base_ptr __root)
		{
			while (__root->_right)
				__root = __root->_right;
			return __root;
		}

		_Base_ptr _findNodeInt(_Base_ptr __node, _Key __key)
		{
			if (!__node || __key == __node->_key)
				return __node;
			if (__key < __node->_key)
				return _findNodeInt(__node->_left, __key);
			return _findNodeInt(__node->_right, __key);
		}
		
		_Base_ptr _findNode(_Key __key)
		{
			return _findNodeInt(_root, __key);
		}

		/*
		** --------------------------------- INSERT  ---------------------------
		*/

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
		_Base_ptr _insert(_Key __key, _Val __val)
		{
			_Base_ptr node = _create_node();
			node->_key = __key;
			node->_val = __val;
			return _addNode(node);
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

		_Base_ptr _addNode(_Base_ptr node)
		{
			node->_color = _S_red;

			_Base_ptr parent = NULL;
			_Base_ptr current = _root;
			// std::cout << "test 270\n";
			// _printNode(current);
			// std::cout << "test 271\n";

			while (current != NULL)
			{
				parent = current;
				if (node->_key == current->_key)
				{
					current->_val = node->_val;
					_delete_node_clean(&node);
					// Node exist with same key, abort and replace content
					return current;
				}
				if (node->_key < current->_key)
					current = current->_left;
				else
					current = current->_right;
			}

			node->_parent = parent;
			if (parent == NULL)
				_root = node;
			else if (node->_key < parent->_key)
				parent->_left = node;
			else
				parent->_right = node;

			if (node->_parent == NULL)
			{
				node->_color = _S_black;
				return node;
			}

			if (node->_parent->_parent == NULL)
				return node;

			_balanceTree(node);
			return node;
		}

		/*
		** --------------------------------- DELETE  ---------------------------
		*/
	
		void _delete_sub_tree(_Base_ptr __root)
		{
			if (__root != NULL)
			{
				_delete_sub_tree(__root->_left);
				_delete_sub_tree(__root->_right);
				_delete_node_clean(&__root);
			}
		}

		void _delete_tree()
		{
			_delete_sub_tree(_root);
		}

		void _delete_node(_Base_ptr __node)
		{
			_Tp_alloc_type.deallocate(__node, 1);
		}

		void _delete_node_clean(_Base_ptr *__node)
		{
			_delete_node(* __node);
			*__node = NULL;
		}

		void _findAndDeleteNodeFromTree(_Base_ptr __root, _Key __key)
		{
			_Base_ptr node = _findNode(__key);
			if(!node)
				return;
			_deleteNodeFromTree(node);
		}
		void _deleteNodeFromTree(_Base_ptr __node) //_node must be in the tree, test beforehand
		{
			_Base_ptr x, y;

			y = __node;
			_Rb_tree_color y_original_color = y->_color;
			if (__node->_left == NULL)
			{
				x = __node->_right;
				_rbTransplant(__node, __node->_right);
			}
			else if (__node->_right == NULL)
			{
				x = __node->_left;
				_rbTransplant(__node, __node->_left);
			}
			else
			{
				y = minimum(__node->_right);
				y_original_color = y->_color;
				x = y->_right;
				if (y->_parent == __node)
				{
					x->_parent = y;
				}
				else
				{
					_rbTransplant(y, y->_right);
					y->_right = __node->_right;
					y->_right->_parent = y;
				}

				_rbTransplant(__node, y);
				y->_left = __node->_left;
				y->_left->_parent = y;
				y->_color = __node->_color;
			}
			_delete_node_clean(&__node);
			if (y_original_color == _S_black)
				deleteFix(x);
		}

		/*
		** --------------------------------- DEBUG  ---------------------------
		*/

		std::string _printNode(_Base_ptr __node, std::string __indent = "", char __src = 'R')
		{
			if (__node == NULL)
				return __indent;
			std::cout << __indent;
			__indent += __src == 'r' ? "|" : __src == 'l' ? " "
														  : "";
			__indent += "  ";
			std::cout << __src
					  << "----["
					  << __node->_key
					  << "]==["
					  << __node->_val.first
					  << "]:["
					  << __node->_val.second
					  << "]["
					  << (__node->_color == _S_red ? "RED" : "BLACK")
					  << "]"
					  << std::endl;
			return __indent;
		}
		void _printNodeRec(_Base_ptr __node, std::string __indent = "", char __src = 'R')
		{
			if (__node == NULL)
				return;
			__indent = _printNode(__node, __indent, __src);
			_printNodeRec(__node->_left, __indent, 'r');
			_printNodeRec(__node->_right, __indent, 'l');
		}
		void _print()
		{
			std::cout << "_______Start print tree______\n";
			if (_root)
				_printNodeRec(_root);
			std::cout << "_______End print tree______\n";
		}
	};

}

#endif
