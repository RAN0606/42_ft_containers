/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBNode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:08:31 by rliu              #+#    #+#             */
/*   Updated: 2023/02/03 13:46:33 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
# define RBNODE_HPP

# include "utils.hpp"
# include <algortithm>

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

    
}