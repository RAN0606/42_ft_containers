/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:04:08 by rliu              #+#    #+#             */
/*   Updated: 2023/02/20 14:02:07 by rliu             ###   ########.fr       */
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


//** Define the iteartor_traits;
template <class Iterator>
  struct iterator_traits{
    typedef typename Iterator::value_type            value_type;
    typedef typename Iterator::difference_type       difference_type;
    typedef typename Iterator::reference        		reference;
    typedef typename Iterator::pointer		          pointer;
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
  template <class InputIterator, class Distance> // need to test
	void advance(InputIterator& it, Distance n) { it += n; }


	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		typename iterator_traits<InputIterator>::difference_type count = 0;
		for (; first != last; ++first)
			++count;

		return count;
	}

	template < class Category,
		class T,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T& >
	struct iterator {
	/* member types */

		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};
  template <class Iterator>
	class reverse_iterator {
		public:
		/* member types */

			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		public:
		/* member functions */

		/* constructor / destructor */

			reverse_iterator(void) : _it() {}
			
			explicit reverse_iterator(iterator_type it) : _it(it) {}

			template< class Iter >
			reverse_iterator(const reverse_iterator<Iter> & rev_it) : _it(rev_it.base()) {}

			virtual ~reverse_iterator(void) {}
		

			iterator_type base(void) const { return _it; }


			reference operator*(void) const { 
				iterator_type tmp = _it;

				return *(--tmp);
			}

			reverse_iterator operator+ (difference_type n) const { return reverse_iterator(_it - n); }

			reverse_iterator& operator++(void) {
				--_it;
				return *this;
			}

			reverse_iterator  operator++(int) {
				reverse_iterator tmp(*this);
				operator++();
				return tmp;
			}

			reverse_iterator& operator+= (difference_type n) {
				_it -= n;
				return *this;
			}

			reverse_iterator operator- (difference_type n) const { return reverse_iterator(_it + n); }

		
			reverse_iterator& operator--(void) {
				++_it;
				return *this;
			}

			reverse_iterator  operator--(int) {
				reverse_iterator tmp(*this);
				operator--();
				return tmp;
			}

			reverse_iterator& operator-= (difference_type n) {
				_it += n;
				return *this;
			}

			pointer operator->() const { return &(operator*()); }

			
			reference operator[] (difference_type n) const { return _it[-n - 1]; }

		
			friend bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() == rhs.base();
			}

			template < class _IteratorR >
			friend bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() == rhs.base();
			}

			friend bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() != rhs.base();
			}

			template < class _IteratorR >
			friend bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() != rhs.base();
			}

			friend bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() > rhs.base();
			}

			template < class _IteratorR >
			friend bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() > rhs.base();
			}

			friend bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() >= rhs.base();
			}

			template < class _IteratorR >
			friend bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() >= rhs.base();
			}

			friend bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() < rhs.base();
			}

			template < class _IteratorR >
			friend bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() < rhs.base();
			}

			friend bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() <= rhs.base();
			}

			template < class _IteratorR >
			friend bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() <= rhs.base();
			}

			
			friend reverse_iterator<Iterator> operator+ (difference_type n, const reverse_iterator<Iterator>& rev_it) {
				return rev_it + n;
			}

			
			friend difference_type operator- (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs) {
				return rhs.base() - lhs.base();
			}

			template < class _IteratorR >
			friend difference_type operator- (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<_IteratorR>& rhs) {
				return rhs.base() - lhs.base();
			}

		private:
		/* attributes */
		
			iterator_type	_it;
	};

}
#endif