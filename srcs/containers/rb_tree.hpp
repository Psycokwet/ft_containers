/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:05:33 by scarboni          #+#    #+#             */
/*   Updated: 2022/09/05 08:14:30 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "iterator_traits.hpp"
#include <algorithm.hpp> //swap
#include "pair.hpp"
#include "rb_iterators.hpp"
#include "reverse_iterator.hpp"

#define NO_PARENT NULL
namespace ft
{
	enum _Rb_tree_color
	{
		_S_red = false,
		_S_black = true,
		_S_leaf = 2,
	};

	template <typename _Key,
			  typename _Val = ft::pair<_Key, void> // bug indent
			  >
	struct Rb_tree_node_base
	{
		typedef Rb_tree_node_base _Base;
		typedef Rb_tree_node_base *_Base_ptr;
		typedef const Rb_tree_node_base *_Const_Base_ptr;

		_Val _val;
		_Rb_tree_color _color;
		_Base_ptr _parent;
		_Base_ptr _left;
		_Base_ptr _right;
		_Base_ptr *_beginLeaf;
		_Base_ptr *_endLeaf;

	public:
		_Key *key_ptr()
		{
			return &_val.first;
		}
		_Key key()
		{
			return _val.first;
		}
		_Val &val()
		{
			return _val;
		}
		_Val *val_ptr()
		{
			return (&_val);
		}
		bool set_color(_Rb_tree_color color)
		{
			if (_color == _S_leaf)
				return false;
			_color = color;
			return true;
		}
		_Rb_tree_color get_color() const
		{
			if (_color == _S_leaf)
				return _S_black;
			return _color;
		}

		bool isLeaf()
		{
			return _color == _S_leaf;
		}
		bool isNotLeaf()
		{
			return !isLeaf();
		}
		_Base_ptr get___Node(_Base_ptr __x,
							 _Base_ptr *_Base::*__sideLeaf,
							 _Base_ptr _Base::*__sideAdvance,
							 _Base_ptr _Base::*__otherSide)
		{
			if (!__x) // should  not happen
				return NULL;
			if (__x->isLeaf() &&
				__x->_parent != NO_PARENT &&
				__x != *(__x->*__sideLeaf))
				__x = __x->_parent;

			else if ((__x->*__sideAdvance)->isNotLeaf())
			{
				__x = __x->*__sideAdvance;
				while ((__x->*__otherSide)->isNotLeaf())
					__x = __x->*__otherSide;
			}
			else
			{
				_Base_ptr __y = __x->_parent;
				while (__y != NO_PARENT && __x == __y->*__sideAdvance)
				{
					__x = __y;
					__y = __y->_parent;
				}
				if (__x->*__sideAdvance != __y)
				{
					if (__y == NO_PARENT)
						__x = *(__x->*__sideLeaf);
					else
						__x = __y;
				}
			}
			return __x;
		}

		_Base_ptr getNextNode()
		{
			return get___Node(this,
							  &_Base::_endLeaf,
							  &_Base::_right,
							  &_Base::_left);
		}

		_Base_ptr getPrevNode()
		{
			return get___Node(this,
							  &_Base::_beginLeaf,
							  &_Base::_left,
							  &_Base::_right);
		}
	};

	template <typename _Key,
			  typename _Val = ft::pair<_Key, void>,
			  typename _Compare = std::less<_Key>,
			  typename _Alloc = std::allocator<_Val> // bug indent
			  >
	class _Rb_tree
	{
	public:
		typedef Rb_tree_node_base<_Key, _Val> _Rb_tree_node_base;

		// https://alp.developpez.com/tutoriels/templaterebinding/
		typedef typename _Alloc::template rebind<_Rb_tree_node_base>::other allocator_type;

		allocator_type _Tp_alloc_type;

	private:
		typedef _Rb_tree<_Key, _Val, _Compare, _Alloc> _Self;
		// typedef Rb_tree_node_base<_Key, _Val> _Rb_tree_node_base;
		typedef _Rb_tree_node_base _Base;
		typedef const _Rb_tree_node_base _Const_Base;
		typedef _Rb_tree_node_base *_Base_ptr;
		typedef const _Rb_tree_node_base *_Const_Base_ptr;

		typedef _Compare key_compare;
		_Compare _comp;
		_Base_ptr _leaf; // end leafs
		_Base_ptr _root;
		_Base_ptr _beginLeaf; // past to begin leaf
		_Base_ptr _endLeaf;	  // past to end leaf
		size_t _node_count;	  // Keeps track of size of tree.

	public:
		typedef _Rb_tree_iterator<_Self, _Val, false> iterator;
		typedef _Rb_tree_iterator<_Self, _Val, true> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef _Key key_type;
		typedef _Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		_Rb_tree(const _Compare &__comp = _Compare(), const allocator_type &__a = allocator_type())
			: _Tp_alloc_type(__a),
			  _comp(__comp),
			  _leaf(_initLeaf()),
			  _root(_leaf),
			  _beginLeaf(_initLeaf()),
			  _endLeaf(_initLeaf()),
			  _node_count(0)
		{
		}

		_Rb_tree(const _Rb_tree &__x) // must copy content with iterator outside from there
			: _Tp_alloc_type(__x._Tp_alloc_type),
			  _comp(__x._comp),
			  _leaf(_initLeaf()),
			  _root(_leaf),
			  _beginLeaf(_initLeaf()),
			  _endLeaf(_initLeaf()),
			  _node_count(0)
		{
		}

		_Rb_tree &operator=(const _Rb_tree &__x) // prefer to refill using iterator so must do outside
		{
			clear();
			_Tp_alloc_type = __x._Tp_alloc_type;
			_comp = __x._comp;
			return *this;
		}

		void clear()
		{
			_delete_tree();
			_node_count = 0;
		}

		~_Rb_tree()
		{
			// std::cout << "deleting tree :" << std::endl;
			// _print();
			clear();
			// std::cout << "deleting leafs" << std::endl;
			_delete_node_clean(&_leaf);
			_delete_node_clean(&_endLeaf);
			_delete_node_clean(&_beginLeaf);
			// std::cout << "deleted" << std::endl;
		}

	public:
		iterator insertNodeGetIterator(_Val __val)
		{
			return insertNodeGetIterator(__val.first, __val, true);
		}
		iterator insertNodeGetIterator(_Key __key, _Val __val = _Val(), bool replaceIfPresent = false)
		{
			return iterator(_insert(__key, __val, replaceIfPresent));
		}
		_Val *insertNode(_Val __val)
		{
			return insertNode(__val.first, __val);
		}
		_Val *insertNode(_Key __key, _Val __val = _Val(), bool replaceIfPresent = false)
		{
			_Val *v = _insert(__key, __val, replaceIfPresent)->val_ptr();
			// std::cout << "Added node in tree :" << std::endl;
			// _print();
			return v;
		}
		_Base_ptr findNode(_Key __key)
		{
			_Base_ptr find = _findNode(__key);
			if (!find)
				return NULL;
			return find;
		}
		bool deleteNode(_Key __key)
		{
			return _findAndDeleteNodeFromTree(__key);
		}

		/*
		** --------------------------------- ALLOCATOR --------------------------
		*/
		/*
		 * get_allocator done
		 */
		allocator_type get_allocator() const
		{
			return _Tp_alloc_type;
		}

		/*
		** --------------------------------- ITERATORS --------------------------
		*/

		iterator begin()
		{
			_Base_ptr tmp = _minimum(_root);
			if (tmp->isLeaf())
				return iterator(*(tmp->_endLeaf));
			return iterator(tmp);
		}

		const_iterator begin() const
		{
			_Base_ptr tmp = _const_minimum(_root);
			if (tmp->isLeaf())
				return const_iterator(*(tmp->_endLeaf));
			return const_iterator(tmp);
		}

		iterator end()
		{
			return iterator(_end());
		}

		const_iterator end() const
		{
			return const_iterator(_end());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		bool empty() const
		{
			return !size();
		}

		size_type size() const
		{
			return _node_count;
		}

		size_type max_size() const
		{
			return _Tp_alloc_type.max_size();
		}

		void swap(_Rb_tree &__x)
		{
			_swap(_Tp_alloc_type, __x._Tp_alloc_type);
			_swap(_comp, __x._comp);
			_swap(_leaf, __x._leaf);
			_swap(_root, __x._root);
			_swap(_beginLeaf, __x._beginLeaf);
			_swap(_endLeaf, __x._endLeaf);
			_swap(_node_count, __x._node_count);
		}

		iterator lower_bound(const _Key &__k)
		{
			return iterator(_findClosest(_root, __k));
		}

		const_iterator lower_bound(const _Key &__k) const
		{
			return const_iterator(_findClosest(_root, __k));
		}

		iterator upper_bound(const _Key &__k)
		{
			return iterator(_findClosest(_root, __k)->getNextNode());
		}

		const_iterator upper_bound(const _Key &__k) const
		{
			return const_iterator(_findClosest(_root, __k)->getNextNode());
		}

		key_compare key_comp() const
		{
			return _comp;
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
			leaf->_color = _S_leaf;
			return leaf;
		}
		/*
		** --------------------------------- ORGANIZE TREE  ---------------------------
		*/

		void _place_y_instead_of_x(_Base_ptr __x, _Base_ptr __y) // don't care for childs of x and y
		{
			if (__x->_parent == NO_PARENT)
				_root = __y;
			else if (__x == __x->_parent->_left)
				__x->_parent->_left = __y;
			else
				__x->_parent->_right = __y;
			__y->_parent = __x->_parent;
		}

		void _rotate(_Base_ptr __x, _Base_ptr _Base::*__otherSide, _Base_ptr _Base::*__sideRotate)
		{
			// step 1 is condition initials
			_Base_ptr y = __x->*__otherSide;
			__x->*__otherSide = y->*__sideRotate; // step 2 :No issue if otherSide gets a leaf
			if ((y->*__sideRotate)->isNotLeaf())  // fix y->sideRotate parent
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

			if ((gp->*__side)->get_color() == _S_red)
			{
				gp->_right->set_color(_S_black); // step a
				gp->_left->set_color(_S_black);	 // step a
				gp->set_color(_S_red);			 // step a
				return gp;						 // step b. gp is the new newNode
			}
			else
			{
				if (__newNode == __newNode->_parent->*__side)
				{
					__newNode = __newNode->_parent;	   // step c
					(this->*__firstRotate)(__newNode); // step d
					return __newNode;
				}
				__newNode->_parent->set_color(_S_black);			  // step e
				__newNode->_parent->_parent->set_color(_S_red);		  // step e
				(this->*__secondRotate)(__newNode->_parent->_parent); // step f
				return __newNode;
			}
		}
		void _balanceTree(_Base_ptr __newNode)
		{
			while (__newNode->_parent->get_color() == _S_red) // step 1
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
			_root->set_color(_S_black);
		}

		/*
		** --------------------------------- FIND  ---------------------------
		*/

		_Base_ptr _end() const
		{
			return _endLeaf;
		}

		_Base_ptr _const_minimum(_Base_ptr __root) const
		{
			while (__root->_left != _leaf)
				__root = __root->_left;
			return __root;
		}

		_Base_ptr _const_maximum(_Base_ptr __root) const
		{
			while (__root->_right != _leaf)
				__root = __root->_right;
			return __root;
		}
		_Base_ptr _minimum(_Base_ptr __root)
		{
			while (__root->_left != _leaf)
				__root = __root->_left;
			_beginLeaf->_parent = __root;
			return __root;
		}

		_Base_ptr _maximum(_Base_ptr __root)
		{
			while (__root->_right != _leaf)
				__root = __root->_right;
			_endLeaf->_parent = __root;
			return __root;
		}

		_Base_ptr _findClosest(_Base_ptr __root, const _Key __key) const
		{
			_Base_ptr closestParent = NO_PARENT;
			_Base_ptr current = __root;
			while (current->isNotLeaf())
			{
				closestParent = current;
				if (__key == current->key())
					return current;
				current = _comp(current->key(), __key) ? current->_right : current->_left;
			}
			return closestParent;
		}

		_Base_ptr _findNodeInt(_Base_ptr __root, _Key __key)
		{
			_Base_ptr result = _findClosest(__root, __key);
			if (result && result->key() != __key)
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

		void _update_max_min()
		{
			_minimum(_root);
			_maximum(_root);
		}

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
		_Base_ptr _insert(_Key __key, _Val __val, bool replaceIfPresent = false)
		{
			_Base_ptr node = _create_node();
			node->_val = __val;
			*(node->key_ptr()) = __key; // never set key value before val, since val encompass it
			return _addNode(node, replaceIfPresent);
		}
		_Base_ptr _init_node(_Base_ptr __node)
		{
			_Base tmp;
			tmp._val = value_type();
			*(tmp.key_ptr()) = key_type();
			tmp._parent = NO_PARENT;
			tmp._beginLeaf = &_beginLeaf;
			tmp._endLeaf = &_endLeaf;
			tmp._left = _leaf;
			tmp._right = _leaf;
			tmp._color = _S_black;
			_Tp_alloc_type.construct(__node, tmp);
			return __node;
		}

		_Base_ptr _addNode(_Base_ptr node, bool replaceIfPresent)
		{
			_Base_ptr parent = _findClosest(_root, node->key()); // step 4 (works to find if root == null for step 3 later)
			if (parent != NO_PARENT && parent->key() == node->key())
			{
				// Node exist with same key, abort and replace content
				if (replaceIfPresent)
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
			node->_parent = parent;				   // step 5
			if (_comp(parent->key(), node->key())) // step 6
				parent->_right = node;
			else
				parent->_left = node;				 // step 7
			node->set_color(_S_red);				 // step 9 (no need for step 8, done at init)
			if (node->_parent->_parent == NO_PARENT) // parent is black since root, so work finished here
				return node;

			_balanceTree(node);

			_update_max_min();
			return node;
		}

		/*
		** --------------------------------- DELETE  ---------------------------
		*/

		void _delete_sub_tree(_Base_ptr __root)
		{
			if (__root->isNotLeaf())
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
			// std::cout << "deleting node :" << __node << std::endl;
			// _printNode(__node);
			_Tp_alloc_type.deallocate(__node, 1);
		}

		void _delete_node_clean(_Base_ptr *__node)
		{
			_delete_node(*__node);
			*__node = NULL;
		}

		bool _findAndDeleteNodeFromTree(_Key __key)
		{
			_Base_ptr node = _findNode(__key);
			if (!node)
				return false;
			_deleteNodeFromTree(node);

			_update_max_min();
			return true;
		}

		_Base_ptr deleteFixInt(_Base_ptr x, _Base_ptr _Base::*__side, _Base_ptr _Base::*__otherSide)
		{
			_Base_ptr s = x->_parent->*__side;
			if (s->get_color() == _S_red)
			{
				s->set_color(_S_black);
				x->_parent->set_color(_S_red);
				_rotate(x->_parent, __side, __otherSide);
				s = x->_parent->*__side;
			}

			if ((s->*__otherSide)->get_color() == _S_black && (s->*__otherSide)->get_color() == _S_black)
			{
				s->set_color(_S_red);
				x = x->_parent;
			}
			else
			{
				if ((s->*__side)->get_color() == _S_black)
				{
					(s->*__otherSide)->set_color(_S_black);
					s->set_color(_S_red);
					_rotate(s, __otherSide, __side);
					s = x->_parent->*__side;
				}
				s->set_color(x->_parent->get_color());
				x->_parent->set_color(_S_black);
				(s->*__side)->set_color(_S_black);
				_rotate(x->_parent, __side, __otherSide);
				x = _root;
			}
			return x;
		}
		void deleteFix(_Base_ptr x)
		{
			while (x != _root && x->get_color() == _S_black)
			{
				if (x == x->_parent->_left)
					x = deleteFixInt(x, &_Base::_right, &_Base::_left);
				else
					x = deleteFixInt(x, &_Base::_left, &_Base::_right);
			}
			x->set_color(_S_black);
		}

		_Base_ptr _replace_other_side_if_one_side_is_leaf(_Base_ptr __node, _Base_ptr _Base::*__side, _Base_ptr _Base::*__other_side)
		{
			_Base_ptr result = NULL;
			if ((__node->*__side)->isNotLeaf())
				return result;

			result = __node->*__other_side;
			_place_y_instead_of_x(__node, __node->*__other_side);
			return result;
		}
		void _deleteNodeFromTree(_Base_ptr __node)
		{
			_node_count--;
			_Base_ptr x, y;

			y = __node;
			_Rb_tree_color y_original_color = y->_color;
			// one or both side are leaves
			x = _replace_other_side_if_one_side_is_leaf(__node, &_Base::_left, &_Base::_right);
			if (!x)
				x = _replace_other_side_if_one_side_is_leaf(__node, &_Base::_right, &_Base::_left);
			if (!x) // none are leaves
			{
				y = _minimum(__node->_right);
				y_original_color = y->get_color();
				x = y->_right;
				if (y->_parent == __node)
				{
					x->_parent = y;
				}
				else
				{
					_place_y_instead_of_x(y, y->_right);
					y->_right = __node->_right;
					y->_right->_parent = y;
				}

				_place_y_instead_of_x(__node, y);
				y->_left = __node->_left;
				y->_left->_parent = y;
				y->set_color(__node->_color);
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
			if (__node->isLeaf())
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
					  << "]["
					  << (__node->_parent ? __node->_parent->key() : _Key()) << (__node->_parent ? "P" : "NOP")
					  << "]"
					  << std::endl;
			return __indent;
		}
		void _printNodeRec(_Base_ptr __node, std::string __indent = "", char __src = 'R')
		{
			if (__node == _leaf)
				return;
			__indent = _printNode(__node, __indent, __src);
			_printNodeRec(__node->_right, __indent, 'r');
			_printNodeRec(__node->_left, __indent, 'l');
		}
		void _print()
		{
			std::cout << "_______Start print tree______" << _node_count << "\n";
			if (_endLeaf->_parent)
				std::cout << "max key:" << _endLeaf->_parent->key() << "\n";
			if (_beginLeaf->_parent)
				std::cout << "min key:" << _beginLeaf->_parent->key() << "\n";
			if (_root)
				_printNodeRec(_root);
			std::cout << "_______End print tree______\n";
		}

	public:
		// void print()
		// {
		// 	_print();
		// }
	};

}

#endif
