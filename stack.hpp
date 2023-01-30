/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:53:58 by rliu              #+#    #+#             */
/*   Updated: 2023/01/24 17:55:07 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"
namespace ft{
    
    template<class T, class Container=ft::vector<T> >
    class stack{
    public:
        typedef T                                   value_type;
        typedef Container                           container_type;
        typedef typename container_type::size_type  size_type;
        typedef typename Container::reference           reference;
        typedef typename Container::const_reference     const_reference;
        
        explicit stack(const container_type& ctnr = container_type()): _containerVec(ctnr){}
        ~stack(){}
        reference top(){return _containerVec.back();}
        const_reference top() const {return this->_containerVec.back();}
        bool empty() const {return this->_containerVec.empty();}
        size_type size() const {return this->_containerVec.size();}
        void push( const value_type& value ){return this->_containerVec.push_back(value);}
        void pop(){return this->_containerVec.pop_back();}

        friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
                        return lhs._containerVec == rhs._containerVec;
                }
                
        friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
            return !(lhs == rhs);
        }
        
        friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
            return lhs._containerVec < rhs._containerVec;
        }
        
        friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
            return rhs < lhs;
        }
        
        friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
            return !(rhs < lhs);
        }
        
        friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
            return !(lhs < rhs);
        }

    protected:
        container_type _containerVec;
    };
 
}
#endif