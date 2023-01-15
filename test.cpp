#include <iostream>

struct test1 {};
struct test2: public test1 {};

void dotest1(test1)
{
    std::cout << "test1 \n";
}
void dotest1(test2)
{
    std::cout << "test2 \n";
}
int main(){
    struct test1 x;
    struct test2 y;
    dotest1(y);
    //dotest1(test2);
}

/*#include<stdio.h>
#include<stddef.h>
#include<string.h>
int main(int argc,char *argv[])
{
    char str[] = "Hello world!";
    char *pstart = str;
    char *pend = str + strlen(str);
    ptrdiff_t difp = pend - pstart;
    printf("%td\n", difp);
    return 0;
}*/