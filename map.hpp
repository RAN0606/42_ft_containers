/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:27:55 by rliu              #+#    #+#             */
/*   Updated: 2023/01/30 14:33:22 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_HPP
#define MAP_HPP

# include<memory>
# include<iterator>
# include "utils.hpp"
# include "iterator_traits.hpp"

namespace ft{
    template<class Key, class T, class Compare = std::less<key_type>, class A = std::allocator<pair<const Key, T> > >  >
    class map{
        public:
            typedef Key                key_type;
            typedef T                  mapped_type;
            typedef parir<const key_type, mapped_type>      value_type;
            typedef Compare                                 key_compare;

        private:
            // nested class: if a nested class could control map without use firend? 
            class pair_compare
            {
                friend class map;
                protected:
                    Compare _comp;
                    pair_compare(Compare c): _comp(c){}
                public:
                    pair_compare(void): _comp(Compare()){}
                    typedef bool        result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;
                    
                    bool operator()(const value_type &x, const value_type &y) const
                    {
                        return _comp(x.first, y.first);
                    } 
            }
    public:
            typedef pair_compare                                value_compare;
            typedef RBTree<value_type, value_compare, A>        tree_type;
            typedef RBNode<value_type, value_compare>           node_type;
            typedef A                                           allocator_type;
            typedef std::size_t                                 size_type;
            typedef ptrdiff_t                                   difference_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;

            typedef t_iterator<node_type>                       iterator;
            typedef t_const_iterator<node_type>                 const_iterator;
            typedef std::reverse_iterator<iterator>              reverse_iterator;
            typedef std::reverse_iterator<const_iterator>        const_reverse_iterator;
    
            explicit map(const key_compare &comp = key_compare(), \
                        const allocator_type &alloc = allocator_type())
            : _tree(value_compare(comp)), _allocator(alloc), \
              _compare(comp), _size(0) {}
              
            // Range
            template <class InputIterator>
            map(InputIterator first, InputIterator last, \
                const key_compare& comp = key_compare(), \
                const allocator_type& alloc = allocator_type())
            : _tree(value_compare(comp)), _allocator(alloc), _compare(comp), \
              _size(0)
            { this->insert(first, last); }
            
            // Copy
            map(const map &x)
            : _tree(value_compare(key_compare())), _allocator(x._allocator), \
              _compare(x._compare), _size(0)
            { *this = x; }

            // Destructor
            ~map(void) {};

            /* ************************************************************** */
            /*  OPERATOR OVERLOADS                                            */
            /* ************************************************************** */
            mapped_type             &operator[](const key_type &k)
            {
                iterator    it;
                
                it = this->_tree.search(value_type(k, mapped_type()));
                if (it == this->_tree.get_end())
                    it = this->insert(value_type(k, mapped_type())).first;
                return ((*it).second);    
            }

            map                     &operator=(const map &x)
            {
                this->_tree = x._tree;
                this->_size = x.size();
                return (*this);
            }

            /* ************************************************************** */
            /*  MEMBER FUNCTIONS                                              */
            /* ************************************************************** */
            // Iterators
            iterator                begin(void)
            { return iterator(this->_tree.get_min()); }

            iterator                end(void)
            { return iterator(this->_tree.get_end()); }

            const_iterator          begin(void) const
            { return const_iterator(this->_tree.get_min()); }

            const_iterator          end(void) const
            { return const_iterator(this->_tree.get_end()); }
            
            reverse_iterator        rbegin(void)
            { return reverse_iterator(this->_tree.get_end()); }
            
            const_reverse_iterator  rbegin(void) const
            { return const_reverse_iterator(this->_tree.get_end()); }

            reverse_iterator        rend(void)
            { return reverse_iterator(this->_tree.get_min()); }

            const_reverse_iterator  rend(void) const
            { return const_reverse_iterator(this->_tree.get_min()); }

            // Capacity
            bool                    empty(void) const
            { return (this->_size == 0); }
            
            size_type               size(void) const
            { return (this->_size); }

            size_type               max_size(void) const
            { return (this->_allocator.max_size()); }
            
            // Modifiers
            pair<iterator, bool>    insert(const value_type &val)
            {
                node_type       *ret;
                node_type       *node;
                int             dir;
                value_compare   comp = this->value_comp(); 

                ret = this->_tree.find_insert_pos(val);
                if (ret == NULL) // Insert first node
                {
                    node = this->_tree.get_allocator().allocate(1);
                    this->_tree.get_allocator().construct(node, val);
                    this->_tree.insert(node, ret, LEFT);
                    ++this->_size;
                }
                else if (ret->value.first == val.first) // Key already exists
                    return (pair<iterator, bool>(ret, false));
                else // New node
                {
                    dir = comp(ret->value, val);
                    node = this->_tree.get_allocator().allocate(1);
                    this->_tree.get_allocator().construct(node, val);
                    this->_tree.insert(node, ret, dir);
                    ++this->_size;
                }
                return (pair<iterator, bool>(node, true));
            }
            
            iterator                insert(iterator position, \
                                           const value_type &val)
            {
                node_type       *node;
                int             dir;
                value_compare   comp = this->value_comp(); 
                
                // Compare the value with hint and prev(hint)
                if (comp(*position, val) && comp(val, *(++position)))
                {
                    dir = comp(*position, val);
                    node = this->_tree.get_allocator().allocate(1);
                    this->_tree.get_allocator().construct(node, val);
                    this->_tree.insert(node, position._p, dir);
                    ++this->_size;
                    return (iterator(node));
                }
                // Insert as usual
                return (this->insert(val).first);
            }

            template<class InputIterator>
            void                    insert(InputIterator first, \
                                           InputIterator last)
            {
                while (first != last)
                {
                    this->insert(*first);
                    ++first;
                }
            }
 
            void                    erase(iterator position)
            {
                if (position._p != NULL)
                {
                    this->_tree.erase(position);
                    --this->_size;
                }
            }

            size_type               erase(const key_type &k)
            {
                if (this->_tree.erase(value_type(k, mapped_type())) == 1)
                {
                    --this->_size;
                    return (1);
                }
                return (0);
            }

            void                    erase(iterator first, iterator last)
            {
                iterator    next;
                
                while (first != last)
                {
                    next = first._p->successor();
                    this->erase(first);
                    first = next;
                }
            }

            void                    swap(map &x)
            {
                this->_tree.swap(x._tree);
                std::swap(this->_size, x._size);
            }
            
            void                    clear(void)
            {
                this->_tree.clear();
                this->_size = 0;
            }
            
            // Allocator
            allocator_type              get_allocator(void) const
            { return allocator_type(this->_allocator); }
            
            // Observers
            key_compare                 key_comp(void) const
            { return this->_compare; }

            value_compare               value_comp(void) const
            { return value_compare(key_compare()); }
            
            // Operations
            iterator                    find(const key_type &k)
            { return (iterator(\
                      this->_tree.search(value_type(k, mapped_type())))); }

            const_iterator              find(const key_type &k) const
            { return (const_iterator(\
                      this->_tree.search(value_type(k, mapped_type())))); }
            
            size_type                   count(const key_type &k) const
            { return ((this->_tree.search(value_type(k, mapped_type())) 
                       == this->_tree.get_end()) ? 0 : 1); }

            iterator                    lower_bound(const key_type &k)
            { return (\
                this->_tree.get_lower_bound(value_type(k, mapped_type()))); }
            
            const_iterator              lower_bound(const key_type &k) const
            { return (const_cast<iterator>(\
                this->_tree.get_lower_bound(value_type(k, mapped_type())))); }

            iterator                    upper_bound(const key_type &k)
            { return (\
                this->_tree.get_upper_bound(value_type(k, mapped_type()))); }
            
            const_iterator              upper_bound(const key_type &k) const
            { return (const_cast<iterator>(\
                this->_tree.get_upper_bound(value_type(k, mapped_type())))); }

            pair<iterator, iterator>    equal_range(const key_type &k)
            {
               return (pair<iterator, iterator>(this->lower_bound(k), \
                                                this->upper_bound(k)));
            }

            pair<const_iterator, const_iterator>    equal_range(\
                                                     const key_type &k) const
            {
               return (pair<const_iterator, const_iterator>(\
                       this->lower_bound(k), this->upper_bound(k)));
            }

        private:
            // Attributes
            tree_type       _tree;
            allocator_type  _allocator;
            key_compare     _compare;
            size_type       _size;
    };
}
