#include <iostream>
#include "../container/vector.hpp"
#include <vector>
#include "test.hpp"
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
void printSize(TESTED_NAMESPACE::vector<int> const &vct, bool print_content = true)
{
	const size_t size = vct.size();
	const size_t capacity = vct.capacity();
	//const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << capacity << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		TESTED_NAMESPACE::vector<int>::const_iterator it = vct.begin();
		TESTED_NAMESPACE::vector<int>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it!= ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void test_assaign()
{
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

void test_operatorassign(){
    std::cout <<"********************vector::operrator assign****************************\n";
    TESTED_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized elements
    
    TESTED_NAMESPACE::vector<int>::size_type sz = myvector.size();
    // assign some values:
    for (unsigned i=0; i<sz; i++) myvector[i]=i;
    TESTED_NAMESPACE::vector<TESTED_TYPE> const myvector_const(myvector);
    //TESTED_NAMESPACE::vector<int>::size_type sz2 = myvector_const.size();
    // reverse vector using operator[]:
    for (unsigned i=0; i<sz/2; i++)
    {
        int temp;
        temp = myvector[sz-1-i];
        myvector[sz-1-i]=myvector[i];
        myvector[i]=temp;
    }
        /*for (unsigned i=0; i<sz2/2; i++)
    {
        int temp;
        temp = myvector_const[sz2-1-i];
        myvector_const[sz2-1-i]=myvector_const[i];
        myvector_const[i]=temp;
    }*/
        std::cout << "myvector: ";
        printSize(myvector);
        std::cout << "myvector_const: ";
        printSize(myvector_const);

}

void test_getallocator(){
    std::cout <<"********************vector::get_allocator****************************\n";

    TESTED_NAMESPACE::vector<int> myvector;
    int * p;
    unsigned int i;

    // allocate an array with space for 5 elements using vector's allocator:
    p = myvector.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

    std::cout << "The allocated array contains:";
    for (i=0; i<5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';

    // destroy and deallocate:
    for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p,5);
    }

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
void test_operatoraccess(){
    std::cout <<"********************vector::operato_acess****************************\n";

    TESTED_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized elements

    TESTED_NAMESPACE::vector<int>::size_type sz = myvector.size();

    // assign some values:
    for (unsigned i=0; i<sz; i++) myvector[i]=i;

    // reverse vector using operator[]:
    for (unsigned i=0; i<sz/2; i++)
    {
        int temp;
        temp = myvector[sz-1-i];
        myvector[sz-1-i]=myvector[i];
        myvector[i]=temp;
    }
    std::cout << "myvector contains:";
    for (unsigned i=0; i<sz; i++)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';
}
void test_front(){
    TESTED_NAMESPACE::vector<int> myvector;
    myvector.push_back(78);
    myvector.push_back(16);

    // now front equals 78, and back 16

    myvector.front() -= myvector.back();

    std::cout << "myvector.front() is now " << myvector.front() << '\n';
}
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

void test_end(){
    std::cout <<"********************vector::end****************************\n";
      
    TESTED_NAMESPACE::vector<int> myvector;
    for (int i=1; i<=5; i++) myvector.push_back(i);

    std::cout << "myvector contains:";
    for (TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}
void test_rbegin(){
    std::cout <<"********************vector::rbegin****************************\n";
    TESTED_NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints
    int i=0;
    TESTED_NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
    for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

    std::cout << "myvector contains:";
    for (TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}
void test_rend(){
    std::cout <<"********************vector::rend****************************\n";
    TESTED_NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints
    TESTED_NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();

    int i=0;
    for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
        *rit = ++i;

    std::cout << "myvector contains:";
    for (TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}
void test_size(){
    std::cout << "********************vector::size****************************\n";

    TESTED_NAMESPACE::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert (myints.end(),10,100);
    std::cout << "2. size: " << myints.size() << '\n';
    printSize(myints);

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
}
void test_maxsize(){
    TESTED_NAMESPACE::vector<int> myvector;
    // set some content in the vector:
    for (int i=0; i<100; i++) myvector.push_back(i);

    std::cout << "size: " << myvector.size() << "\n";
    std::cout << "capacity: " << myvector.capacity() << "\n";
    std::cout << "max_size: " << myvector.max_size() << "\n";
}
void test_capacity(){
    TESTED_NAMESPACE::vector<int> myvector;
    for (int i=0; i<100; i++) myvector.push_back(i);
    std::cout << "size: " << (int) myvector.size() << '\n';
    std::cout << "capacity: " << (int) myvector.capacity() << '\n';
    std::cout << "max_size: " << (int) myvector.max_size() << '\n';
}
void test_empty(){
    std::cout << "********************vector::empty****************************\n";

    TESTED_NAMESPACE::vector<int> myvector;
    int sum (0);

    for (int i=1;i<=10;i++) myvector.push_back(i);

    while (!myvector.empty())
    {
        sum += myvector.back();
        myvector.pop_back();
    }

  std::cout << "total: " << sum << '\n';
}
void test_reserve(){
    std::cout << "********************vector::reserve****************************\n";

    TESTED_NAMESPACE::vector<int>::size_type sz;

    TESTED_NAMESPACE::vector<int> foo;
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

void test_insert(){
    std::cout << "********************vector::insert****************************\n";

    TESTED_NAMESPACE::vector<int> myvector (3,100);
    TESTED_NAMESPACE::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert ( it , 200 );

    myvector.insert (it,2,300);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    TESTED_NAMESPACE::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());

    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);

    std::cout << "myvector contains:";
    for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void test_resize(){  
    std::cout << "********************vector::resize****************************\n";

    TESTED_NAMESPACE::vector<int> myvector;

    // set some initial content:
    for (int i=1;i<10;i++) myvector.push_back(i);
    printSize(myvector);
    myvector.resize(5);
     printSize(myvector);
    myvector.resize(8,100);
     printSize(myvector);
    myvector.resize(12);

    std::cout << "myvector contains:";
    printSize(myvector);
}

void test_pushback(){
    std::cout << "********************vector::push_back****************************\n";
    TESTED_NAMESPACE::vector<int> myvector;
    for (int i=1;i<10;i++) myvector.push_back(i);
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
void test_erase(){  
    TESTED_NAMESPACE::vector<int> myvector;
    std::cout << "********************vector::erase****************************\n";
    // set some values (from 1 to 10)
    for (int i=1; i<=10; i++) myvector.push_back(i);
    // erase the 6th element
    myvector.erase (myvector.begin()+5);

    // erase the first 3 elements:
    myvector.erase (myvector.begin(),myvector.begin()+3);

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); ++i)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';
}

void test_swap(){
    std::cout << "********************vector::swap****************************\n";

    TESTED_NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
    TESTED_NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200
    
    std::cout << "A.swap(&B)\n";
    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i=0; i<foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i=0; i<bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << '\n';
    swap(foo, bar);
    std::cout << "swap(&A,&B)\n";
        std::cout << "foo contains:";
    for (unsigned i=0; i<foo.size(); i++)
        std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i=0; i<bar.size(); i++)
        std::cout << ' ' << bar[i];
    std::cout << '\n';

 }
void test_cmp()
{
    TESTED_NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
    TESTED_NAMESPACE::vector<int> bar (2,200);   // two ints with a value of 200

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void test_vector(void){
    test_assaign();
    test_operatorassign();
    test_getallocator();
    test_at();
    test_operatoraccess();
    test_front();
    test_back();
    test_begin();
    test_end();
    test_rbegin();
    test_rend();
    test_size();
    test_maxsize();
    test_capacity();
    test_empty();
    test_reserve();
    test_resize();
    test_insert();
    test_clear();
    test_pushback();
    test_popback();
    test_resize();
    test_erase();
    test_swap();
    test_cmp();
}

int main(){
    test_vector();
}
