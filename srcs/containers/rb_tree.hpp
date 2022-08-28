/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:05:33 by scarboni          #+#    #+#             */
/*   Updated: 2022/08/28 14:40:34 by scarboni         ###   ########.fr       */
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
			_Rb_tree_color _color;
			_Base_ptr _parent;
			_Base_ptr _left;
			_Base_ptr _right;

		public:
			_Key *key_ptr()
			{
				return &(_val.first);
			}
			_Key key()
			{
				return _val.first;
			}
		};

		// https://alp.developpez.com/tutoriels/templaterebinding/
		typedef typename _Alloc::template rebind<_Rb_tree_node_base>::other allocator_type;

		allocator_type _Tp_alloc_type;

	private:
#define NO_PARENT NULL

		typedef _Rb_tree_node_base _Base;
		typedef const _Rb_tree_node_base _Const_Base;
		typedef _Rb_tree_node_base *_Base_ptr;
		typedef const _Rb_tree_node_base *_Const_Base_ptr;

		typedef _Compare _base_key_compare;
		_Base_ptr _root;	// m_header
		_Base_ptr _leaf;	// end leafs
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
			_leaf = _initLeaf();
			_root = _leaf;
			_node_count = 0;
		}

		_Rb_tree(const _Compare &__comp, const allocator_type &__a = allocator_type())
			: _base_key_compare(__comp), allocator_type(__a), _root(NULL), _leaf(_initLeaf()), _node_count(0)
		{
			_root = _leaf;
		}

		_Rb_tree(const _Rb_tree &__x)
			: _base_key_compare(__x.__comp), allocator_type(__x.__a), _root(NULL), _leaf(_initLeaf()), _node_count(0)
		{
			_root = _leaf;
			// if (__x._root != NULL)
			// 	_root = _copy(__x);
		}

		~_Rb_tree()
		{
			std::cout << "deleting tree :" << std::endl;
			_print();

			_delete_tree();
			_node_count = 0;
			std::cout << "deleted" << std::endl;
			_delete_node_clean(&_leaf);
		}

	public:
		_Val *insertNode(_Key __key, _Val __val = _Val())
		{
			_Val *v = &(_insert(__key, __val)->_val);
			std::cout << "Added node in tree :" << std::endl;
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
		** --------------------------------- CONSTRUCTION  ---------------------------
		*/
		_Base_ptr _initLeaf()
		{
			_Base_ptr leaf = _create_node();
			leaf->_left = leaf;
			leaf->_right = leaf;
			return leaf;
		}
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
			if (u->_parent == NO_PARENT)
				_root = v;
			else if (u == u->_parent->_left)
				u->_parent->_left = v;
			else
				u->_parent->_right = v;
			v->_parent = u->_parent;
		}

		void _rotate(_Base_ptr __x, _Base_ptr _Base::*__otherSide, _Base_ptr _Base::*__sideRotate)
		{
			// step 1 is condition initials
			_Base_ptr y = __x->*__otherSide;
			__x->*__otherSide = y->*__sideRotate; // step 2 :No issue if otherSide gets a leaf
			if (y->*__sideRotate != _leaf)		  // fix y->sideRotate parent
				(y->*__sideRotate)->_parent = __x;
			y->_parent = __x->_parent;	   // No issue if y->_parent gets NO_PARENT
			if (__x->_parent == NO_PARENT) // step 3
				_root = y;
			// step 4-5 replace original x parent's parent by y
			else if (__x == __x->_parent->*__sideRotate)
				__x->_parent->*__sideRotate = y;
			else
				__x->_parent->*__otherSide = y;
			// step 6 assign y as x parent's
			__x->_parent = y;
			y->*__sideRotate = __x;
		}
		void _leftRotate(_Base_ptr x)
		{
			_rotate(x, &_Base::_right, &_Base::_left);
		}
		void _rightRotate(_Base_ptr x)
		{
			_rotate(x, &_Base::_left, &_Base::_right);
		}
		
		_Base_ptr _balance_int(_Base_ptr __newNode,
							   void (_Rb_tree::*__firstRotate)(_Base_ptr),
							   void (_Rb_tree::*__secondRotate)(_Base_ptr),
							   _Base_ptr _Base::*__side)
		{
			_Base_ptr gp = __newNode->_parent->_parent;

			if ((gp->*__side)->_color == _S_red)
			{
				gp->_right->_color = _S_black; // step a
				gp->_left->_color = _S_black;  // step a
				gp->_color = _S_red;		   // step a
				return gp;					   // step b. gp is the new newNode
			}
			else
			{
				if (__newNode == __newNode->_parent->*__side)
				{
					__newNode = __newNode->_parent;	   // step c
					(this->*__firstRotate)(__newNode); // step d
					return __newNode;
				}
				__newNode->_parent->_color = _S_black;				  // step e
				__newNode->_parent->_parent->_color = _S_red;		  // step e
				(this->*__secondRotate)(__newNode->_parent->_parent); // step f
				return __newNode;
			}
		}
		void _balanceTree(_Base_ptr __newNode)
		{
			while (__newNode->_parent->_color == _S_red) // step 1
			{
				if (__newNode->_parent == __newNode->_parent->_parent->_left) // step 2
					__newNode = _balance_int(__newNode,						  // case 1
											 &_Rb_tree::_leftRotate,
											 &_Rb_tree::_rightRotate,
											 &_Base::_right);
				else
					__newNode = _balance_int(__newNode, // case 2
											 &_Rb_tree::_rightRotate,
											 &_Rb_tree::_leftRotate,
											 &_Base::_left);

				if (__newNode == _root)
					break;
			}
			_root->_color = _S_black;
		}

		/*
		** --------------------------------- FIND  ---------------------------
		*/

		_Base_ptr _minimum(_Base_ptr __root)
		{
			while (__root->_left == _leaf)
				__root = __root->_left;
			return __root;
		}

		_Base_ptr _maximum(_Base_ptr __root)
		{
			while (__root->_right == _leaf)
				__root = __root->_right;
			return __root;
		}

		_Base_ptr _findClosest(_Base_ptr __root,_Key __key)
		{
			_Base_ptr closestParent = NO_PARENT;
			_Base_ptr current = __root;
			while (current != _leaf)
			{
				closestParent = current;
				if (__key == current->key())
					return current;
				current = current->key() <= __key ? current->_right : current->_left;
			}
			return closestParent;
		}

		_Base_ptr _findNodeInt(_Base_ptr __root, _Key __key)
		{
			_Base_ptr result = _findClosest( __root, __key);
			if (result &&  result->key() != __key)
				return NULL;
			return result;
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
			return node;
		}
		_Base_ptr _insert(_Key __key, _Val __val)
		{
			_Base_ptr node = _create_node();
			node->_val = __val;
			*(node->key_ptr()) = __key; // never set key value before val, since val encompass it
			return _addNode(node);
		}
		_Base_ptr _init_node(_Base_ptr __node)
		{
			_Base tmp;
			tmp._val = value_type();
			*(tmp.key_ptr()) = key_type();
			tmp._parent = NO_PARENT;
			tmp._left = _leaf;
			tmp._right = _leaf;
			tmp._color = _S_black;
			_Tp_alloc_type.construct(__node, tmp);
			return __node;
		}

		_Base_ptr _addNode(_Base_ptr node)
		{
			_Base_ptr parent = _findClosest(_root, node->key()); // step 4 (works to find if root == null for step 3 later)
			if (parent != NO_PARENT && parent->key() == node->key())
			{
				// Node exist with same key, abort and replace content
				parent->_val = node->_val; // should I use construct ?
				_delete_node_clean(&node);
				return parent; // obv not parent in this case
			}

			_node_count++;			 // here I know I will add a node for sure
			if (parent == NO_PARENT) // step 3, color already black
			{
				_root = node;
				return node;
			}
			node->_parent = parent;			 // step 5
			if (node->key() > parent->key()) // step 6
				parent->_right = node;
			else
				parent->_left = node;				 // step 7
			node->_color = _S_red;					 // step 9 (no need for step 8, done at init)
			if (node->_parent->_parent == NO_PARENT) // parent is black since root, so work finished here
				return node;

			_balanceTree(node);
			return node;
		}

		/*
		** --------------------------------- DELETE  ---------------------------
		*/

		void _delete_sub_tree(_Base_ptr __root)
		{
			if (__root != _leaf)
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
			std::cout << "deleting node :"<< __node<< std::endl;
			_printNode(__node);
			_Tp_alloc_type.deallocate(__node, 1);
		}

		void _delete_node_clean(_Base_ptr *__node)
		{
			_delete_node(*__node);
			*__node = NULL;
		}

		void _findAndDeleteNodeFromTree(_Base_ptr __root, _Key __key)
		{
			_Base_ptr node = _findNode(__key);
			if (!node)
				return;
			_deleteNodeFromTree(node);
		}
		void _deleteNodeFromTree(_Base_ptr __node) //_node must be in the tree, test beforehand
		{
			_node_count--;
			_Base_ptr x, y;

			y = __node;
			_Rb_tree_color y_original_color = y->_color;
			if (__node->_left == _leaf)
			{
				x = __node->_right;
				_rbTransplant(__node, __node->_right);
			}
			else if (__node->_right == _leaf)
			{
				x = __node->_left;
				_rbTransplant(__node, __node->_left);
			}
			else
			{
				y = _minimum(__node->_right);
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
			if (__node == _leaf)
				return __indent;
			std::cout << __indent;
			__indent += __src == 'r' ? "|" : __src == 'l' ? " "
														  : "";
			__indent += "  ";
			std::cout << __src
					  << "----["
					  << __node->key()
					  << "]->["
					  << __node->_val.second
					  << "]["
					  << (__node->_color == _S_red ? "RED" : "BLACK")
					  << "]"
					  << std::endl;
			return __indent;
		}
		void _printNodeRec(_Base_ptr __node, std::string __indent = "", char __src = 'R')
		{
			if (__node == _leaf)
				return;
			__indent = _printNode(__node, __indent, __src);
			_printNodeRec(__node->_left, __indent, 'r');
			_printNodeRec(__node->_right, __indent, 'l');
		}
		void _print()
		{
			std::cout << "_______Start print tree______" << _node_count << "\n";
			if (_root)
				_printNodeRec(_root);
			std::cout << "_______End print tree______\n";
		}
	};

}

#endif
