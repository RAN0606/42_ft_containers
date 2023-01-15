/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:21:10 by rliu              #+#    #+#             */
/*   Updated: 2023/01/15 18:17:33 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP


namespace ft{

   template<class T, class Allocator = std::allocator<T>>
    class vector{    
        public:
            typedef T                                                       value_type;
            typedef Allocator                                               allocator_type;
            
            typedef typename allocator_type::reference                      reference;
            typedef typename allocator_type::const_reference                const_reference;
            typedef typename allocator_type::pointer                        pointer;
            typedef typename allocator_type::const_pointer                  const_pointer;
            typedef pointer                                                 iterator;
            typedef const_pointer                                           const_iterator;
            typedef std::reverse_iterator<iterator>                         reverse_iterator;
            typedef std::reverse_iterator<const_iterator>                   const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::differenc_type  difference_type;
            typedef typename allocator_type::size_type                      size_type;

            explicit vector(const allocator_type& alloc = allocator_type()):
                _allocator(alloc),_capaccity(0),_begin(NULL), _end(NULL){}
                
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
                _allocator(alloc), _capacity(n){
                        this->_array = _allocator.allocate(n);
                        std::fill(this->begin(), this->end(), val)
            }
                
        //   template<class InputIterator> 
        //    vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
        //    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL):
        //        allocator(alloc)
        //    const allocator_type& alloc = allocator_type();

            vector(const vector& x): _allocator(x.get_allocator()), _capacity(x.capacity())
{
    this->_array = this->_allocator.allocate(this->_capacity);
    std::copy(x.begin(), x.end(), this->begin());
}

            ~vector();

            vector& operator= (const vector& x);
            iterator begin(){return iterator(this->_array);}
            const_iterator begin() const{return const_iterator(this->_array);}
            
            iterator end(){return iterator(this->_array + this->_size);}
            const_iterator  end() const{ return const_iterator(this->_array + this->_size);}
            
            reverse_iterator rbegin() {return reverse_iterator(this->end());}
            const_reverse_iterator rbegin() const{return const_reverse_iterator(this->end());} 
            
            reverse_iterator rend() {return reverse_iterator(this->begin());}
            const_reverse_iterator rend() const {return const_reverse_iterator(this->begin());}
            
//?            const_iterator cbegin() const noexcept;
//?            const_iterator cend() const noexcept;
//?            const_reverse_iterator crbegin() const noexcept;
//?            const_reverse_iterator crend() const noexcept;

            size_type size() const {return (this->_size);}
            size_type max_size() const {return(this->_allocator.max_size());}
            void resize (size_type n, value_type val = value_type());
            
            size_type capacity() const {return (this->_capacity);}
            bool empty() const {return (this->size == 0);}
            void reserve (size_type n);
            void shrink_to_fit();

            reference operator[] (size_type n);const_reference operator[] (size_type n) const; 
            reference at (size_type n);const_reference at (size_type n) const;
            reference front();const_reference front() const;
            reference back();const_reference back() const;
            value_type* data() noexcept;const value_type* data() const noexcept;
            
            
            template <class InputIterator>  void assign (InputIterator first, InputIterator last);
            void assign (size_type n, const value_type& val);
            void push_back (const value_type& val);
            void pop_back();

            iterator insert (iterator position, const value_type& val);
            void insert (iterator position, size_type n, const value_type& val);	
            template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last);

            iterator erase (iterator position);iterator erase (iterator first, iterator last);
            void swap (vector& x);
            void clear();
            template <class... Args>iterator emplace (const_iterator position, Args&&... args);           
            template <class... Args>  void emplace_back (Args&&... args);

            allocator_type get_allocator() const;

            template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
            template <class T, class Alloc>  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
            template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
            template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
            template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
            template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);         
            template <class T, class Alloc>  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
    
    private:
        allocator_type      _allocator;
        size_type           _capacity;
        pointer             _array;
        size_type           _size; 
    }
}


#endif