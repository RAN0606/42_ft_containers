/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:21:10 by rliu              #+#    #+#             */
/*   Updated: 2023/01/17 19:08:18 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP


namespace ft{

   template<class T, class Allocator = std::allocator<T>>
   class vector{
    public:
        // public value types;
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
        // constructors and destructors
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

        // member fuctions - iterators
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
        // member function - capacity
        size_type size() const {return (this->_size);}
        size_type max_size() const {return(this->_allocator.max_size());}
        size_type capacity() const {return (this->_capacity);}
        bool empty() const {return (this->size == 0);}
        void reserve (size_type n){
            if (n > this->capacity())
            {
                if (n > this->max_size())
                    throw std::lenth_error("vector");
                pointer newarr = this->get_allocator.allocate(n);
                std::copy(this->begin(), this->end(), newarr);
                for (long unsigned int i = 0; i < this->size(); ++i)
                    this->get_allocator().destroy(this->_array, this->capacity());
                    this->_array = newarr;
                    this->_capaity = n;
            }
        // member function - element access    
        reference operator[] (size_type n) {return *(this->begin() + n);}
        const_reference operator[] (size_type n) const {return *(this->begin() + n);}
        reference at (size_type n) {
            if (n >= size())
            throw std::out_of_range("vector");
            return (*this)[n];
        }
        
        const_reference at (size_type n) const {
            if (n >= size())
            throw std::out_of_range("vector");
            return (*this)[n];
        }
        
        reference front() { return *(this->benin());}
        const_reference front() const { return * (this->begin());}
        
        reference back() {return *(this->end() -1);}
        const_reference back() const {return *(this->end() -1);}

        template <class InputIterator> 
        void assign (InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                clear();
                reserve(last - first);
                for (;first != last; first++) {
                  _allocator.construct(this->_end++, *first);
                }
            }
            
        void assign (size_type n, const value_type& val){
            clear();
            reserve(n);
            while(n-- > 0)
                _allocator.construct(this->end++, val);
        }
        // memeber function - modifiers
        
        void push_back (const value_type& val){
            
            
            if (this->_end == this->_capacity){
                
                size_type n = (size()> 0? :capacity() * 2: 1)
                reserve(n);
                _allocator.construct(this->_end, val);
                this->_end++
                this->_size++;
                this->_capaccity = n;
        }
    
        void pop_back(){
            if (this->_size > 0){
                this->get_allocator().destroy(&(*this)[this->size() - 1]);
                --this->_size;
            }
        }
        
        void resize (size_type n, value_type val = value_type()){
                if (n < this->_size){
                    while(n < this->_size--)
                        _allocator.destroy(this->_end--);
                }
                else{
                    if (n > capacity())
                        reserve(n);
                    while(_size++ < n)
                        _allocator.construct(this->end++, val);
                }
        }


        iterator insert (iterator position, const value_type& val){
            
        }
        void insert (iterator position, size_type n, const value_type& val){
              size_type diff = position - begin(); 

        }
        template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last);

        iterator erase (iterator position){

            this->get_allocator().destroy(position);
            std::copy(position + 1, this->end(), position);   
            this->get_allocator().destroy(this->end() - 1));
            --this->_size;
            return (position);
        }
        
        iterator erase (iterator first, iterator last){
                for (ft::vector<T,A>::iterator it = first; it < last; ++it)
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
            while(n-- > 0)
                this->_allocator.destroy(--this->_end);
        }
    
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
}
#endif