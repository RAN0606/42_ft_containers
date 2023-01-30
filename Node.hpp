/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:08:31 by rliu              #+#    #+#             */
/*   Updated: 2023/01/30 15:27:01 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include "utils.hpp"
# include <algortithm>

namespace ft{

typedef enum color {RED,BLACK}  tcolor;
typedef enum position {LEFT, RIGHT} tpos;

struct Node {
    tcolor      node_color;
    tpos        node_position
    Node        left_child;
    Node        right_child;
}
    
}