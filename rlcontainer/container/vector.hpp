/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:21:10 by rliu              #+#    #+#             */
/*   Updated: 2023/02/17 15:10:38 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <memory>
# include <algorithm>
# include <iterator>
# include <stdexcept>
# include <exception>
# include <limits>
# include "iterator.hpp"
# include "utils.hpp"

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
        typedef ft::reverse_iterator<iterator>                         reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                   const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type  difference_type;
        typedef typename allocator_type::size_type                      size_type;
                             
        /*******************************************************************************************/
        // constructors and destructors
        
        explicit vector(const allocator_type& alloc = allocator_type()):
            _allocator(alloc),_capacity(0), _array(0), _size(0){}
            
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
            _allocator(alloc), _capacity(n),_size(n){
                    this->_array = _allocator.allocate(n);
                    for (; n != 0; n--)
                        _allocator.construct(this->end()- n, val);
                    
        }
           
        template<class InputIterator> 
        vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, 
            const allocator_type& alloc = allocator_type()):_allocator(alloc){
                this->_size = last - first;
                this->_capacity =this->_size;
                this->_array = _allocator.allocate(this->_capacity);
                iterator it = begin();
                for (size_type n =0; n < size(); n++)
                _allocator.construct(it++, *first++ );
            }
        
        /********************************************************************************************/
        //    const allocator_type& alloc = allocator_type();

        vector(const vector& x): _allocator(x.get_allocator()),_capacity(x.size()),_size(x.size())
        {
            this->_array = this->_allocator.allocate(this->_capacity);
            const_iterator tmp = x.begin();
            
            for (size_type n = x.size(); n != 0; n--)
					this->_allocator.construct(this->end()-n, *tmp++);
        }
        
        ~vector(){
            this->clear();
            this->_allocator.deallocate(this->begin(), this->capacity());
        }
        
        /*******************************************************************************************/
        // assign & con
        
        vector& operator= (const vector& x){  
            if (this== &x)
                return(*this);
            if (x.capacity() == 0 || x.capacity() > this->capacity()){
                this->_capacity = x.capacity();
                this->clear();
                this->_allocator.deallocate(this->begin(), this->capacity());
                this->_array = this->_allocator.allocate(this->_capacity);
            }
            else 
                this->clear();
            this->_size = x.size();
            const_iterator tmp = x.begin();
            for (size_type n = x.size(); n != 0; n--)
					this->_allocator.construct(this->end()-n, *tmp++);
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
                throw std::length_error("vector::reserve");
              if (n > capacity()) {
                
                pointer pre_begin = this->begin();
                pointer pre_end = this->end();
                size_type pre_cap = capacity();
                size_type pre_size = size();
                
                iterator it = this->_allocator.allocate(n);
                iterator it2 = it;
                this->_capacity =  n;
                while(pre_begin != pre_end){
                    this->_allocator.construct(it++, *pre_begin);
                    pre_begin++;
                }
                this->clear();
                this->_allocator.deallocate(pre_begin-pre_size, pre_cap);
                this->_array = it2;
                _size = pre_size;
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
            if (this->_size != this->_capacity){  
                this->_allocator.construct(this->end(), val);
                this->_size++;
            }
            else{
                size_type n = (size()> 0? capacity()*2:1);
                reserve(n);
                this->_capacity = n;
                push_back(val);
            }
            
        }
        void pop_back(){
            if (this->_size > 0){
                this->get_allocator().destroy(&(*this)[this->size() - 1]);
                --this->_size;
            }
        }
        
        void resize (size_type n, value_type val = value_type() ){
            if (n < size())
                erase(begin() + n, end());
            else
                insert(end(), n - size(), val);        
        }
        //void resize(size_type n){ resize(n, T());}
                //fill (2)	
        void insert (iterator position, size_type n, const value_type& val) {
            if (n != 0){
                if(capacity()-size() >= n){
                    T value_copy = val;
                    const size_type elems_after = end() - position;
                    iterator oldend = end();
                    if (elems_after > n){
                        std::uninitialized_copy(end()-n, end(), end());
                        _size += n;
                        std::copy_backward(position, oldend -n, oldend);
                        std::fill(position, position + n, value_copy);    
                    }
                    else{
                        std::uninitialized_fill_n(end(), n - elems_after, value_copy);
                        _size += n - elems_after;
                        std::uninitialized_copy(position, oldend, end());
                        _size += elems_after;
                        std::fill(position, oldend, value_copy);
                    }
                }
                else{
                    const size_type old_size = size();
                    const size_type len = old_size + std::max(old_size, n);
                    iterator new_array = _allocator.allocate(len);
                    iterator new_end = new_array;
                    new_end = std::uninitialized_copy(_array, position, new_array );
                    new_end = std::uninitialized_fill_n(new_end, n, val);
                    new_end = std::uninitialized_copy(position, end(), new_end);    
            
                    this->clear();
                    this->_allocator.deallocate(this->begin(), this->capacity());
                    this->_array = new_array;
                    _size = new_end - new_array;
                    _capacity = len;
                }
            }
        
            // if (n !=0){
            // size_type diff = position - begin(); 
            
            // resize(size() + n)
            // position = begin() + diff; 
            // size_type diff_right = (end() - n) - position; //插入到结尾距离
            // pointer pre_end = this->end() - n - 1;
            // for(size_type i = 0; i < diff_right; i++)
            //     *(this->end() - 1 - i) = *pre_end--;
            // for(size_type i = 0; i < n; i++)
            // *(position + i) = val;
        }
        
        iterator insert (iterator position, const value_type& val){
            size_type diff = position - begin();  
            insert(position, 1, val);
            return iterator(begin() + diff);
        }

        
        //range (3)
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
        {
             size_type n = last - first;
            const size_type old_size = size();
            const size_type len = std::max(old_size + n, capacity());
            iterator new_array = _allocator.allocate(len);
            iterator new_end = new_array;
            new_end = std::uninitialized_copy(_array, position, new_array );
            new_end = std::uninitialized_copy(first, last, new_end);
            new_end = std::uninitialized_copy(position, end(), new_end);    
    
            this->clear();
            this->_allocator.deallocate(this->begin(), this->capacity());
            this->_array = new_array;
            _size = new_end - new_array;
            _capacity = len;

            
            // size_type diff = position - begin(); 
            // size_type n = last - first;
            // size_type diff_right = end() - position; 
            // resize(size() + n); 
            // position = begin() + diff; 
            // pointer pre_end = this->end() - n - 1;
            // for(size_type i = 0; i < diff_right; i++){
            //     _allocator.destroy(this->end()-1-i);
            //     _allocator.construct(this->end()-1 -i, *pre_end--);
            // }
            // for(size_type j = 0; j < n && first != last ; j++, first++){
            //     _allocator.destroy(position + j);
            //     _allocator.construct(position + j, *first);
            // }
                
        }
        

        iterator erase (iterator position){
            if(position + 1 != end())
              std::copy(position + 1, this->end(), position);
            --this->_size;     
            this->get_allocator().destroy(this->end());
            return (position);
        }
        
        iterator erase (iterator first, iterator last){
                
                iterator i=std::copy(last, this->end(), first);
                iterator ite = this->end();
                while (i != ite)
                    this->get_allocator().destroy(i++);
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
          erase(begin(),end());
         }
            
    protected:
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