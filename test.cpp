#include <iostream>
#include "vector.hpp"
#include <vector>

#define TESTED_TYPE int

template <typename T_STACK>
void	printSize(T_STACK &stck)
{
	std::cout << "size: " << stck.size() << std::endl;
	std::cout << "capacity: " << stck.capacity() << std::endl;
    for(size_t i = 0; i < stck.size(); i++)
        std::cout << stck[i] << " ";
    std::cout << std::endl;

	std::cout << "###############################################" << std::endl;
}

void test_assaign(){
    std::cout <<"********************vector::assign****************************\n";


	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_two(4);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_three;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printSize(vct);
	printSize(vct_two);

    }
void test_operatorassign(){}
void test_getallocator(){}
/*****************element access***********************/
void    test_at(){
    std::cout <<"********************vector::at****************************\n";

    TESTED_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized ints

    // assign some values:
    for (unsigned i=0; i<myvector.size(); i++)
        myvector.at(i)=i;

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); i++)
        std::cout << ' ' << myvector.at(i);
    std::cout << '\n';

}
void test_operatoraccess(){}
void test_front(){}
void test_back(){
    std::cout <<"********************vector::back****************************\n";

    TESTED_NAMESPACE::vector<int> myvector;

    myvector.push_back(10);

    while (myvector.back() != 0)
    {
        myvector.push_back ( myvector.back() -1 );
    }

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size() ; i++)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';
}
/***************iterators***************************/
void test_begin(){
    std::cout <<"********************vector::begin****************************\n";
    TESTED_NAMESPACE::vector<int> myvector;
    for (int i=1; i<=5; i++) myvector.push_back(i);

    std::cout << "myvector contains:";
    for (TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void test_end(){}
void test_rbegin(){}
void test_rend(){}
void test_size(){}
void test_maxsize(){}
void test_capacity(){}
void test_empty()
void test_reserve(){
    std::cout << "********************vector::reserve****************************\n";

    TESTED_NAMESPACE::vector<int>::size_type sz;

    std::vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i=0; i<100; ++i) {
        foo.push_back(i);
        if (sz!=foo.capacity()) {
        sz = foo.capacity();
        std::cout << "capacity changed: " << sz << '\n';
        }
    }

    TESTED_NAMESPACE::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);   // this is the only difference with foo above
    std::cout << "making bar grow:\n";
    for (int i=0; i<100; ++i) {
        bar.push_back(i);
        if (sz!=bar.capacity()) {
        sz = bar.capacity();
        std::cout << "capacity changed: " << sz << '\n';
        }
    }
}
/*************modifiers***********************/

void test_insert(){}

void test_resize(){}

void test_pushback(){
    std::cout << "********************vector::push_back****************************\n";
    TESTED_NAMESPACE::vector<int> myvector;
    int myint;
    printSize(myvector);
    std::cout << "Please enter some integers (enter 0 to end):\n";

    do {
    std::cin >> myint;
    myvector.push_back (myint);
    } while (myint);
    printSize(myvector);
}

void test_popback(){
    std::cout << "********************vector::pop_back****************************\n";
    TESTED_NAMESPACE::vector<int> myvector;
    int sum (0);
    printSize(myvector);
    myvector.push_back (100);
    printSize(myvector);
    myvector.push_back (200);
    printSize(myvector);
    myvector.push_back (300);
    printSize(myvector);
    while (!myvector.empty())
    {
    sum+=myvector.back();
    myvector.pop_back();
    printSize(myvector);
    }
    printSize(myvector);

    std::cout << "The elements of myvector add up to " << sum << '\n';

}
void test_clear(){

    std::cout << "********************vector::clear****************************\n";
  
  TESTED_NAMESPACE::vector<int> myvector;
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  printSize(myvector);
  myvector.clear();
  printSize(myvector);
  myvector.push_back (1101);
  myvector.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}
void test_erase(){}

void test _swap(){}

int main(){
    //test_assaign();
    //test_at();
    //test_back();
    //test_begin();
    //test_clear();
    //test_pushback();
    //test_popback();
    //test_reserve();
}
