/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:27:55 by rliu              #+#    #+#             */
/*   Updated: 2023/02/24 16:00:34 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <cstddef>
#include <exception>
#include "utils.hpp"
#include "RBT.hpp"
#include "treeIte.hpp"
#include "iterator.hpp"

namespace ft{
	template < class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map {
		public:
		/* member types */

			typedef				Key													key_type;
			typedef				T													mapped_type;
			typedef				ft::pair<const key_type, mapped_type>				value_type;
			typedef				Compare												key_compare;

		
			class value_compare : public binary_function<value_type, value_type, bool> {
				friend class map;
		
				protected:
					key_compare comp;

					value_compare(key_compare c) : comp(c) {}

				public:
					typedef bool 		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

			typedef				Alloc															allocator_type;
			typedef	typename	allocator_type::reference										reference;
			typedef	typename	allocator_type::const_reference									const_reference;
			typedef	typename	allocator_type::pointer											pointer;
			typedef	typename	allocator_type::const_pointer									const_pointer;
			
			/** @note usually the same as ptrdiff_t */
			typedef	typename	allocator_type::difference_type									difference_type;
			/** @note usually the same as size_t */
			typedef	typename	allocator_type::size_type										size_type;

			typedef				ft::treeIterator<value_type, ft::RBT_Node<value_type> >			iterator;
			typedef				ft::treeIterator<const value_type, ft::RBT_Node<value_type> >	const_iterator;
			typedef				ft::reverse_iterator<iterator>									reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		public:
		/* member functions: constructor / destructor / operator= */

	
			explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _rbt(value_compare(comp)) { (void)alloc; }
		
			
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _rbt(value_compare(comp)) {
					(void)alloc;
					insert(first, last);
			}

		
			map(const map& x) : _rbt(value_compare(key_compare())) {
				insert(x.begin(), x.end());
			}
			
		
   			~map(void) {
				clear();
				_rbt.destroyNull();
			}

		
			map& operator=(const map& x) {
				if (this == &x) return *this;

				this->~map();
				_rbt = ft::RBT<value_type, value_compare>(value_compare(key_compare()));
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

		/* member functions: capacity */
		
	
			bool		empty() const { return begin() == end(); }

		
			size_type	size() const { return _rbt.size(); }

		
			size_type	max_size(void) const { return _rbt.max_size(); }

		/* member functions: element access */
			
			
			mapped_type& operator[](const key_type& k) { return insert(ft::make_pair(k, mapped_type())).first->second; }


			mapped_type&	at( key_type& k)
			{
				iterator	i = this->find(k);

				if (i == end())
					throw (std::out_of_range("map::at"));
				return ((*i).second);
			}
			
			ft::pair<iterator, bool> insert(const value_type& val) {
				if (_rbt.insert(val) == false)
					return ft::make_pair(find(val.first), false);
				return ft::make_pair(find(val.first), true);
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
				erase(position->first);
			}
			
			size_type erase(const key_type& k) {
				if (_rbt.deleteNode(ft::make_pair(k, mapped_type())) == false)
					return 0;
				return 1;
			}

			void  erase(iterator first, iterator last) {
				while (first != last) {
					// refix current ptr
					first = find(first->first);
					erase(first++);
				}
			}
	
			void swap (map& x) { _rbt.swap(x._rbt); }

		
			void clear() { _rbt.destroyTree(); }


			key_compare	key_comp() const { return key_compare(); }

			value_compare  value_comp() const { return value_compare(key_comp()); }

	
			iterator find(const key_type& k) {
				return iterator(_rbt.getRoot(), _rbt.searchTree(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

			const_iterator find(const key_type& k) const {
				return const_iterator(_rbt.getRoot(), _rbt.searchTree(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

		
			size_type count(const key_type& k) const {
				if (find(k) == end())
					return 0;
				return 1;
			}
			
	
			iterator lower_bound(const key_type& k) {
				return iterator(_rbt.getRoot(), _rbt.lower_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}
			
			const_iterator lower_bound(const key_type& k) const {
				return const_iterator(_rbt.getRoot(), _rbt.lower_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

		
			iterator upper_bound(const key_type& k) {
				return iterator(_rbt.getRoot(), _rbt.upper_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}
			
			const_iterator upper_bound(const key_type& k) const {
				return const_iterator(_rbt.getRoot(), _rbt.upper_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

		
			ft::pair<iterator, iterator> equal_range(const key_type& k) {
				return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}
			
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
				return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}

	
			allocator_type get_allocator() const { return allocator_type(); }

		private:
		/* attributes */

			ft::RBT<value_type, value_compare>	_rbt;
	};
	

		template <class Key, class T, class Compare, class Allocator>
		bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs,
				const ft::map<Key, T, Compare, Allocator>& rhs) {
					if (lhs.size() != rhs.size())
						return false;
					return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <class Key, class T, class Compare, class Allocator>
		bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return !(lhs == rhs); }

		template <class Key, class T, class Compare, class Allocator>
		bool operator< (const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) {
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class Key, class T, class Compare, class Allocator>
		bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return !(rhs < lhs); }

		template <class Key, class T, class Compare, class Allocator>
		bool operator> (const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return rhs < lhs; }

		template <class Key, class T, class Compare, class Allocator>
		bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return !(lhs < rhs); }

		template <class Key, class T, class Compare, class Allocator>
		void swap(map<Key, T, Compare, Allocator>& x,
			map<Key, T, Compare, Allocator>& y) { x.swap(y); }
}


#endif
