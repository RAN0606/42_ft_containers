/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:23:53 by rliu              #+#    #+#             */
/*   Updated: 2023/02/03 19:19:14 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include "RBNode.hpp"

namespace ft{

enum RBTcolor {RED, BLACK};


template<class T>
class RBNode {
    T&          key_value;
    RBTcolor    color;
    RBNode      *parent;
    RBNode      *left;
    RBNode      *right;

    RBNode(T& value, RBTcolor c, RBNode p, RBNode l, RBNode r):
        data(value), color(c), parent(p), left(l), right(r){}
};

template< class T, class Compare, class A =std::allocator< RBNode<T> > > 
class RBTree{
    private:
        node_ptr            mRoot;
        allocator_type      _alloc;
    
    public:
        typedef T           value_type;
        typedef RBNode<T>   node_type;
        typedef node_type   *node_ptr;
        typedef A           allocator_type;
    
        RBTree():mRoot(NULL){}
        ~RBNode(){destroy();}
                
        node_ptr search(node_ptr x, T key) const{
            if (x ==NULL || x->key==key)
                return(x);
            if (x < x->key)
                return search(x->left, key);
            else        
                return search(x->right, key);
        }
        
        
        node_ptr minimum(node_ptr tree){ }
        
        node_ptr maximum(node_ptr tree);
        void leftRotate(node_ptr &root, node_ptr x){
            node_ptr y = x->right;
            
            x->right = y->left;
            if(y->left !=NULL)
                y->left->parent = x;
            
            y->parent = x->parent;

            if{x->parent == NULL}
                root = y
            else
            {
                if (x->parent->left == x)
                    x->parent->left = y;
                else
                    x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
            
        }
        void rightRotate(node_ptr &root, node_ptr y){
            node_ptr x = y->left;
            
            y->left = x->right;
            if(x->right != NULL)
                x->right->parent = y;
            
            x->parent = y->parent;
            if (y->parent == NULL)
                root = x;
            else{
                if (y == y->parent->right)
                    y->parent->right = x;
                else
                    y->parent->left = x;
            }  
        }
        
        void insert(node_ptr &root, node_ptr node)[
            node_ptr *y = null;
            node_ptr *x = root;

            while(x != NULL)
            {
                y = x;
                if (node->key < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
            node->parent = y;
            if (y!=NULL){
                if (node->key < y->key)
                    y->left = node;
                else
                    y->right = node;
            }
            else
                root = node;
            node->color = RED;
            
        ]
        void insert(T& key){
            node_ptr z = this->_alloc.construct()
        }
        void insertFixUp(node_ptr &root, node_ptr node);
        void remove(node_ptr &root, RBTNode<T> *node);
        void removeFixUp(node_ptr &root, RBTNode<T> *node, RBTNode<T> *parent);
        void destroy(node_ptr &tree);
        void print(node_ptr tree, T key, int direction);
        #define rb_parent(r)   ((r)->parent)
        #define rb_color(r) ((r)->color)
        #define rb_is_red(r)   ((r)->color==RED)
        #define rb_is_black(r)  ((r)->color==BLACK)
        #define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
        #define rb_set_red(r)  do { (r)->color = RED; } while (0)
        #define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
        #define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
        
}

}