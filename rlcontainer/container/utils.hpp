/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:32:38 by rliu              #+#    #+#             */
/*   Updated: 2023/02/20 14:11:46 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstddef>

namespace ft{
  
  struct  nullptr_t {
    void *_ptr;

    struct __nat { int __for_bool_; };

    nullptr_t() : _ptr(0) {}
    nullptr_t(int __nat::*) : _ptr(0) {}

    operator int __nat::*() const { return 0; }

    template <class _T>
    operator _T* () const {return 0;}

    template <class _T, class _U>
    operator _T _U::* () const {return 0;}

    friend  bool operator==(nullptr_t, nullptr_t) { return true; }
    friend  bool operator!=(nullptr_t, nullptr_t) { return false; }
  };

  #define ft_nullptr nullptr_t(0)
  
  
  template <class T, T v>
  struct integral_constant{
      static const T                  value = v;
      typedef T                       value_type;
      typedef integral_constant<T,v>  type;
      operator T(){return v;}         
  };

  /*class false_type: Instantitation of integral_constant to represent the bool value true*/
  typedef integral_constant<bool,true> true_type;

  /*class false_type: Instantitation of integral_constant to represent the bool value false.*/
  typedef integral_constant<bool,false> false_type;
  template <class T> struct is_integral : public false_type{};
  template<> struct is_integral<bool>: public true_type{};
  template<> struct is_integral<char>: public true_type{}; 
  template<> struct is_integral<wchar_t>: public true_type{};
  template<> struct is_integral<signed char>: public true_type{};
  template<> struct is_integral<short int>: public true_type{};
  template<> struct is_integral<int>: public true_type{};
  template<> struct is_integral<long int>: public true_type{};
  template<> struct is_integral<long long int>: public true_type{};
  template<> struct is_integral<unsigned char>: public true_type{};
  template<> struct is_integral<unsigned short int>: public true_type{};
  template<> struct is_integral<unsigned int>: public true_type{};
  template<> struct is_integral<unsigned long int>: public true_type{};
  template<> struct is_integral<unsigned long long int>: public true_type{};
  template <bool Cond, class T = void> 
  struct enable_if{};

  template<class T> 
  struct enable_if<true, T> { typedef T type; };

  template <class InputIterator1, class InputIterator2>
  bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
  {
      while (first1!=last1) {
      if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
        return false;
      ++first1; ++first2;
    }
    return true;
  }

  template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, BinaryPredicate pred){
      while (first1!=last1) {
      if (!pred(*first1,*first2))
        return false;
      ++first1; ++first2;
    }
    return true;       
  }
  template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2){
    while (first1 != last1)
    {
      if (first2 == last2 || *first2 < *first1) 
          return false;
      else if (*first1 < *first2) 
          return true;
      ++first1;
      ++first2;
    }
    return (first2 != last2);
  }

  template <class InputIterator1, class InputIterator2, class Compare>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2,
                                  Compare comp){
    while (first1 != last1)
    {
      if (first2 == last2 || comp(*first2 , *first1))
          return false;
      else if (comp(*first1, *first2)) 
          return true;
      ++first1;
      ++first2;
    }
    return (first2 != last2);                                  
  }

  template <class T1, class T2>
  struct pair{

      typedef T1 first_type;
      typedef T2 second_type;

      first_type first;
      second_type second;

      // default (1)	
    
      pair(): first(), second() {};
      // copy (2)	
      template<class U, class V> 
      pair (const pair<U,V>& pr):first(pr.first), second(pr.second) {
          // this->first = pr.first;
          // this->second = pr.second;
      }
      // initialization (3)	
      pair (const first_type& a, const second_type& b):
        first(a),
        second(b) {}

      pair& operator= (const pair& pr) {
          if (this == &pr) return *this;
          this->first = pr.first;
          this->second = pr.second;
          return *this;
      }
  };
  template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return lhs.first==rhs.first && lhs.second==rhs.second; }

  template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return !(lhs==rhs); }

  template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
  }

  template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return !(rhs<lhs); }

  template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return rhs<lhs; }

  template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return !(lhs<rhs); }

  /*function template :make_pair : Construct pair object*/
  template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y){
      return ( pair<T1,T2>(x,y) );
    }

  template <class Arg1, class Arg2, class Result>
    struct binary_function {
      typedef Arg1 first_argument_type;
      typedef Arg2 second_argument_type;
      typedef Result result_type;    
};
}
#endif