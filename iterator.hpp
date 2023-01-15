/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:04:08 by rliu              #+#    #+#             */
/*   Updated: 2023/01/12 13:14:10 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//* This file contains the 
#ifndef ITERATOR_HPP
#define ITERATOR_HPP
namespace ft{
//**define iterator tags which are used for the category of iterator;
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


//** Define the base of iterator;
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
  struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
  };

//** Define the iteartor_traits;
template <class Iterator>
  struct iterator_traits{
    typedef Iterator::value_type            value_type;
    typedef Iterator::difference_type       difference_type;
    typedef Iterator::reference_type        reference_type;
    typedef Iterator::pointer_type          pointer_type;
    typedef Iterator::iterator_category     iterator_category;
  }
 
//** define
//template <class Iterator>
//** define the
}
#endif