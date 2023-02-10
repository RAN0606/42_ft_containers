/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maptest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliu <rliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:03:52 by rliu              #+#    #+#             */
/*   Updated: 2023/02/09 15:49:38 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../../containers/map.hpp"
#include <map>

#define TESTED_NAMESPACE ft
#define T1 int
#define T2 int


int main ()
{
  ft::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

	TESTED_NAMESPACE::map<T1, T2> mp;
    TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin();
	TESTED_NAMESPACE::map<T1, T2>::const_iterator cit = mp.begin();

	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator rit(it);

	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit(rit);
	 TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit_(it);
	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit_2(cit);

	/* error expected
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator rit_(crit);
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator rit2(cit);
	TESTED_NAMESPACE::map<T1, T2>::iterator it2(rit);
	TESTED_NAMESPACE::map<T1, T2>::const_iterator cit2(crit);
	*/

	std::cout << "OK" << std::endl;
	return (0);
}