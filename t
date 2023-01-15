
#ifndef UTILE_HPP
#define UTILE_HPP

#include <iostream>
#include <cstddef>

namespace ft {
/*class template: integral_constant*/
/* T: Aliased as member type integral_constant::value_type.
   V: Value of the integral constant.
Accessible as member integral_constant::value, or through type casting.*/
template <class T, T v> 
struct integral_constant{
    static const T value = v;
    typedef T  value_type;
    typedef integral_constant<T,v> type;
    operator T() { return v; } //returns the value of the integral_constant.
    
};

/*class true_type: Instantiation of integral_constant to represent the bool value true.*/
typedef integral_constant<bool,true> true_type;

/*class false_type: Instantitation of integral_constant to represent the bool value false.*/
typedef integral_constant<bool,false> false_type;


/* class template: enable_if */
/*Enable type if condition is met
The type T is enabled as member type enable_if::type if Cond is true.
Otherwise, enable_if::type is not defined.*/
//如果不成立 不是 true T 的type是空的
//如果成立， T 的type定义
template <bool Cond, class T = void> 
struct enable_if{}; 

template<class T> 
struct enable_if<true, T> { typedef T type; };

/* class template: is_integral*/
/*Trait class that identifies whether T is an integral type.*/
/*fundamental integral types
bool, char, char16_t, char32_t, wchar_t, signed char, short int
int, long int, long long int, unsigned char, unsigned short int
unsigned int, unsigned long int, unsigned long long int */
/*Inherited from integral_constant*/
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

/* function templat :equal */
/*如果两个序列的长度相同，并且对应元素都相等，测试两组元素是否相等。 两组的大小不必相等*/
//如果first1到last1范围内的所有元素都等于从first2开始的范围的元素，则返回true，否则返回false。
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

/*两个 迭代器是否满足 参数 4*/
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


/*function template : lexicographical_compare*/
/*true if the first range compares lexicographically less than the second.
false otherwise (including when all the elements of both ranges are equivalent).*/
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
//comp - 一个二进制函数，它接受两个参数并返回bool。
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

/*class template: pair*/
/*Pair of values
This class couples together a pair of values, which may be of different types (T1 and T2). 
The individual values can be accessed through its public members first and second.*/
//这个类将一对可能是不同类型的值（T1 和 T2）耦合在一起。 可以通过其公共成员首先和其次访问各个值。
template <class T1, class T2>
struct pair{

    typedef T1 first_type;
    typedef T2 second_type;

    first_type first;
    second_type second;
    public:
    // default (1)	
    pair(): first(), second() {};
    // copy (2)	
    template<class U, class V> 
    pair (const pair<U,V>& pr):first(pr.first), second(pr.second) {
        // this->first = pr.first;
        // this->second = pr.second;
    }
    // initialization (3)	
    pair (const first_type& a, const second_type& b){
        this->first = a;
        this->second = b;
    }

    pair& operator= (const pair& pr) {
        if (this == &pr) return *this;
        this->first = pr.first;
        this->second = pr.second;
        return *this;
    }
};

/*Non-member function overloads*/
/*function template : relational operators (pair)*/
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

}

template <class Arg1, class Arg2, class Result>
  struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
  };

  

#endif