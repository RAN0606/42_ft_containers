/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:28:55 by rliu              #+#    #+#             */
/*   Updated: 2023/02/17 15:43:19 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include <memory>
#include <cstddef>
#include <exception>
#include "treeIte.hpp"
#include "utils.hpp"


namespace ft{

	template < class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T> >
	class set {
		public:
		/* member types */

			typedef				T													key_type;
			typedef				T													value_type;
			typedef				Compare												key_compare;
			typedef				Compare												value_compare;

			typedef				Alloc															allocator_type;
			typedef	typename	allocator_type::reference										reference;
			typedef	typename	allocator_type::const_reference									const_reference;
			typedef	typename	allocator_type::pointer											pointer;
			typedef	typename	allocator_type::const_pointer									const_pointer;
			
			/** @note usually the same as ptrdiff_t */
			typedef	typename	allocator_type::difference_type									difference_type;
			/** @note usually the same as size_t */
			typedef	typename	allocator_type::size_type										size_type;

			typedef				ft::treeIterator<const value_type, ft::RBT_Node<value_type> >	iterator;
			typedef				ft::treeIterator<const value_type, ft::RBT_Node<value_type> >	const_iterator;
			typedef				ft::reverse_iterator<iterator>									reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		public:
		/* member functions: constructor / destructor / operator= */

			
			explicit set(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _rbt(comp) { (void)alloc; }
		
			
			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _rbt(comp) {
					(void)alloc;
					insert(first, last);
			}
            
			set(const set& x) : _rbt(value_compare()) {
				insert(x.begin(), x.end());
			}
			
   			~set(void) {
				clear();
				_rbt.destroyNull();
			}

			set& operator=(const set& x) {
				if (this == &x) return *this;

				this->~set();
				_rbt = ft::RBT<value_type, value_compare>(value_compare());
				insert(x.begin(), x.end());
				return *this;
			}

		/* member functions: iterators */

			
			iterator begin() { return iterator(_rbt.getRoot(), _rbt.min(), _rbt.getNull()); }
			const_iterator begin() const { return const_iterator(_rbt.getRoot(), _rbt.min(), _rbt.getNull()); }
			
			
			iterator end() { return iterator(_rbt.getRoot(), _rbt.getNull(), _rbt.getNull()); }
			const_iterator end() const { return const_iterator(_rbt.getRoot(), _rbt.getNull(), _rbt.getNull()); }

			
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

			
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

			bool		empty() const { return begin() == end(); }

			
			size_type	size() const { return _rbt.size(); }

			
			size_type	max_size(void) const { return _rbt.max_size(); }

		
			ft::pair<iterator, bool> insert(const value_type& val) {
				if (_rbt.insert(val) == false)
					return ft::make_pair(find(val), false);
				return ft::make_pair(find(val), true);
			}

			iterator insert(iterator position, const value_type& val) {
				(void)position;
				return insert(val).first;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				for (; first != last; first++)
					insert(*first);
			}

			void  erase(iterator position) {
				erase(*position);
			}
			
			size_type erase(const value_type& val) {
				if (_rbt.deleteNode(val) == false)
					return 0;
				return 1;
			}

			void  erase(iterator first, iterator last) {
				while (first != last) {
					// refix current ptr
					first = find(*first);
					erase(first++);
				}
			}
	
			
			void swap (set& x) { _rbt.swap(x._rbt); }

			
			void clear() { _rbt.destroyTree(); }

		
			key_compare	key_comp() const { return key_compare(); }
			
			
			value_compare  value_comp() const { return value_compare(); }

	
			iterator find(const value_type& val) {
				return iterator(_rbt.getRoot(), _rbt.searchTree(val), _rbt.getNull());
			}

			const_iterator find(const value_type& val) const {
				return const_iterator(_rbt.getRoot(), _rbt.searchTree(val), _rbt.getNull());
			}

			size_type count(const value_type& val) const {
				if (find(val) == end())
					return 0;
				return 1;
			}
			
			
			iterator lower_bound(const value_type& val) {
				return iterator(_rbt.getRoot(), _rbt.lower_bound(val), _rbt.getNull());
			}
			
			const_iterator lower_bound(const value_type& val) const {
				return const_iterator(_rbt.getRoot(), _rbt.lower_bound(val), _rbt.getNull());
			}

			
			iterator upper_bound(const value_type& val) {
				return iterator(_rbt.getRoot(), _rbt.upper_bound(val), _rbt.getNull());
			}
			
			const_iterator upper_bound(const value_type& val) const {
				return const_iterator(_rbt.getRoot(), _rbt.upper_bound(val), _rbt.getNull());
			}

		
			ft::pair<iterator, iterator> equal_range(const value_type& val) {
				return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
			}
			
			ft::pair<const_iterator, const_iterator> equal_range(const value_type& val) const {
				return ft::make_pair<const_iterator, const_iterator>(lower_bound(val), upper_bound(val));
			}

		
			allocator_type get_allocator() const { return allocator_type(); }

		private:
		/* attributes */

			ft::RBT<value_type, value_compare>	_rbt;
	};
	
	/* non-member function: set */

		template <class T, class Compare, class Allocator>
		bool operator==(const ft::set<T, Compare, Allocator>& lhs,
				const ft::set<T, Compare, Allocator>& rhs) {
					if (lhs.size() != rhs.size())
						return false;
					return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <class T, class Compare, class Allocator>
		bool operator!=(const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return !(lhs == rhs); }

		template <class T, class Compare, class Allocator>
		bool operator< (const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) {
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class T, class Compare, class Allocator>
		bool operator<=(const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return !(rhs < lhs); }

		template <class T, class Compare, class Allocator>
		bool operator> (const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return rhs < lhs; }

		template <class T, class Compare, class Allocator>
		bool operator>=(const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return !(lhs < rhs); }

		template <class T, class Compare, class Allocator>
		void swap(set<T, Compare, Allocator>& x,
			set<T, Compare, Allocator>& y) { x.swap(y); }

}

#endif