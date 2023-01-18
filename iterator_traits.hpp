/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:04:08 by rliu              #+#    #+#             */
/*   Updated: 2023/01/18 17:36:14 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//* This file contains the 
#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP
namespace ft{
//**define iterator tags which are used for the category of iterator;
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


//** Define the iteartor_traits;
template <class Iterator>
  struct iterator_traits{
    typedef typename Iterator::value_type            value_type;
    typedef typename Iterator::difference_type       difference_type;
    typedef typename Iterator::reference_type        reference_type;
    typedef typename Iterator::pointer_type          pointer_type;
    typedef typename Iterator::iterator_category     iterator_category;
  };
  template < class T >
  struct iterator_traits<T *>
  {
      typedef ptrdiff_t                       difference_type;
      typedef T                               value_type;
      typedef T                               *pointer;
      typedef T                               &reference;
      typedef random_access_iterator_tag      iterator_category;
  };
  template < class T >
  struct iterator_traits<const T *>
  {
      typedef ptrdiff_t                       difference_type;
      typedef T                               value_type;
      typedef const T                         *pointer;
      typedef const T                         &reference;
      typedef random_access_iterator_tag      iterator_category;
  };
//** define
//template <class Iterator>
//** define the
}
#endif