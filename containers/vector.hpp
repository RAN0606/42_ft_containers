/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:21:10 by rliu              #+#    #+#             */
/*   Updated: 2023/02/09 14:38:38 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <memory>
# include <algorithm>
# include <iterator>
#include <stdexcept>
#include <exception>
#include <limits>
#include "utils/iterator.hpp"
# include "utils/utils.hpp"

namespace ft{

   template<class T, class Allocator = std::allocator<T> >
   class vector{
    public:
    
        /*******************************************************************************************/
        // public0 value types;
        
        typedef T                                                       value_type;
        typedef Allocator                                               allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef T*                                                      iterator;
        typedef const T*                                                const_iterator;
        typedef std::reverse_iterator<iterator>                         reverse_iterator;
        typedef std::reverse_iterator<const_iterator>                   const_reverse_iterator;
        typedef typename std::iterator_traits<iterator>::difference_type  difference_type;
        typedef typename allocator_type::size_type                      size_type;
                             
        /*******************************************************************************************/
        // constructors and destructors
        
        explicit vector(const allocator_type& alloc = allocator_type()):
            _allocator(alloc),_capacity(0), _array(0), _size(0){}
            
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
            _allocator(alloc), _capacity(n),_size(n){
                    this->_array = _allocator.allocate(n);
                    std::fill(this->begin(), this->end(), val);
        }
           
        template<class InputIterator> 
        vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, 
            const allocator_type& alloc = allocator_type()):_allocator(alloc){
                this->_size = last - first;
                this->_capacity =this->_size;
                this->_array = _allocator.allocate(this->_capacity);
                std::copy(first, last, this->begin);
            }
        
        /********************************************************************************************/
        //    const allocator_type& alloc = allocator_type();

        vector(const vector& x): _allocator(x.get_allocator()),_capacity(x.capacity()),_size(x.size())
        {
            this->_array = this->_allocator.allocate(this->_capacity);
            std::copy(x.begin(), x.end(), this->begin());
        }
        
        ~vector(){
            this->clear();
            this->_allocator.deallocate(this->begin(), capacity());
        }
        
        /*******************************************************************************************/
        // assign & con
        
        vector& operator= (const vector& x){    
            
            this->clear();
            this->_allocator.deallocate();
            this->_capacity = x.capacity();
            this->_size = x.size();
            this->_array = this->_allocator.allocate(this->_capacity);
            std::copy(x.begin(), x.end(), this->begin());
            return (*this);
        }
        
        template <class InputIterator> 
        void assign (InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                this->clear();
                this->reserve(last - first);
                iterator it = this->_array;
                for (;first != last; first++, this->_size++) {
                    this->_allocator.construct(it++, *first);
                }
            }
            
        void assign (size_type n, const value_type& val){
            this->clear();
            this->reserve(n);
            this->_size = n;
            iterator it=this->_array;
            while(n-- > 0)
                this->_allocator.construct(it++, val);
        }
        
         allocator_type get_allocator() const {return this->_allocator; }
         
        /*******************************************************************************************/
        // member fuctions - iterators
        
        iterator begin(){return iterator(this->_array);}
        
        const_iterator begin() const{return const_iterator(this->_array);}

        iterator end(){return iterator(this->_array + this->_size);}

        const_iterator  end() const{ return const_iterator(this->_array + this->_size);}

        reverse_iterator rbegin() {return reverse_iterator(this->end());}

        const_reverse_iterator rbegin() const{return const_reverse_iterator(this->end());} 

        reverse_iterator rend() {return reverse_iterator(this->begin());}

        const_reverse_iterator rend() const {return const_reverse_iterator(this->begin());}

        size_type size() const {return (this->_size);}

        size_type max_size() const {return(this->_allocator.max_size());}

        size_type capacity() const {return (this->_capacity);}

        bool empty() const {return (this->size() == 0);}

        void reserve (size_type n){
              if (n > max_size())
                throw std::length_error("vector");
              if (n > capacity()) {
                
                size_type pre_size = size();
                pointer pre_begin = this->begin();
                pointer pre_end = this->end();
                size_type pre_cap = capacity();
                
                this->_array = this->_allocator.allocate(n);
                this->_capacity =  n;
                iterator it = this->_array;
                while(pre_begin != pre_end){
                    this->_allocator.construct(it++, *pre_begin++);
                }
                this->_allocator.deallocate(pre_begin - pre_size, pre_cap);
            }
        }
        /*******************************************************************************************/
        // member function - element access    
        
        reference operator[] (size_type n) {return *(this->begin() + n);}
        
        const_reference operator[] (size_type n) const {return *(this->begin() + n);}
        
        reference at (size_type n) {
            if (n >= size())
                throw std::out_of_range("vector");
            return *(this->begin() + n);
        }
        
        const_reference at (size_type n) const {
            if (n >= size())
            throw std::out_of_range("vector");
            return *(this->begin() + n);
        }
        
        reference front() { return *(this->begin());}
        
        const_reference front() const { return * (this->begin());}
        
        reference back() {return *(this->end() -1);}
       
        const_reference back() const {return *(this->end() -1);}


        // memeber function - modifiers
        
        void push_back (const value_type& val){
            if (this->_size == this->_capacity){    
                size_type n = (size()> 0? capacity()*2:1);
                reserve(n);
                this->_capacity = n;
            }
            this->_allocator.construct(this->end(), val);
            this->_size++;
            
        }
        void pop_back(){
            if (this->_size > 0){
                this->get_allocator().destroy(&(*this)[this->size() - 1]);
                --this->_size;
            }
        }
        
        void resize (size_type n, value_type val = value_type()){
                if (n < this->_size){
                    iterator itend = this->end();
                    while(n < this->_size--)
                        this->_allocator.destroy(itend--);
                    this->_size++;
                }
                else{
                    if (n > capacity())
                        reserve(n);
                    iterator itend =this->end();
                    while(this->_size++ < n)
                    {
                        this->_allocator.construct(itend++, val);
                }
                this->_size--;
        }
    }
        iterator insert (iterator position, const value_type& val){
            size_type diff = position - begin();  
            insert(position, 1, val);
            return iterator(begin() + diff);
        }
        //fill (2)	
        void insert (iterator position, size_type n, const value_type& val) {
            size_type diff = position - begin(); 
            resize(size() + n);
            position = begin() + diff; 
            size_type diff_right = (end() - n) - position; //插入到结尾距离
            pointer pre_end = this->end() - n - 1;
            for(size_type i = 0; i < diff_right; i++)
                *(this->end() - 1 - i) = *pre_end--;
            for(size_type i = 0; i < n; i++)
            *(position + i) = val;
        }
        
        //range (3)
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
        {
            size_type diff = position - begin(); 
            size_type n = last - first;
            size_type diff_right = end() - position; 
            
            resize(size() + n); 
            position = begin() + diff; 
            pointer pre_end = this->end() - n - 1;
            for(size_type i = 0; i < diff_right; i++)
                *(this->end() - 1 - i) = *pre_end--;
            for(size_type j = 0; j < n && first != last ; j++, first++)
            *(position + j) = *first;
        }
        

        iterator erase (iterator position){

            this->get_allocator().destroy(position);
            std::copy(position + 1, this->end(), position);   
            this->get_allocator().destroy(this->end() - 1);
            --this->_size;
            return (position);
        }
        
        iterator erase (iterator first, iterator last){
                for (iterator it = first; it < last; ++it)
                    this->get_allocator().destroy(&*it);
                std::copy(last, this->end(), first);   
                this->_size -= (last - first);
                return (first);
        }
        
        void swap (vector& x){
            pointer         tmp_arr;
            allocator_type  tmp_alloc;
            size_type       tmp_size;
            size_type       tmp_capacity;

            tmp_arr = this->_array;
            tmp_size = this->size();
            tmp_capacity = this->capacity();
            tmp_alloc = this->get_allocator();
            this->_array = x._array;
            this->_size = x.size();
            this->_capacity = x.capacity();
            this->_allocator = x.get_allocator();
            x._array = tmp_arr;
            x._size = tmp_size;
            x._capacity = tmp_capacity;
            x._allocator = tmp_alloc;
        }
        
        void clear() {
            size_type n = size();
            iterator itend = this->end();
            while(n-- > 0)
                this->_allocator.destroy(--itend);
            this->_size = 0;
         }
            
    private:
        allocator_type      _allocator;
        size_type           _capacity;
        pointer             _array;
        size_type           _size; 
    };
    
template <class T, class Alloc>
  bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    if(lhs.size() != rhs.size())
      return (false);
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
  bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return !(lhs == rhs);
}

template <class T, class Alloc>
  bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

//use operator <
template <class T, class Alloc> 
  bool operator >  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return (rhs < lhs);
}

template <class T, class Alloc>
  bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return !(lhs > rhs);
}

template <class T, class Alloc>
  bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return (!(lhs < rhs));
}

/*Exchange contents of vectors*/
template <class T, class Alloc>
  void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y){
     x.swap(y);
  }
};
#endif