#include <memory>
#include <iostream>

struct test
{
    int i;
    float f;
    test(int _i, float _f) :i(_i), f(_f){};
};


int main(int argc, char*argv[]) {
    std::unique_ptr<test> ptr = nullptr;

    ptr = std::make_unique<test>(10, 2.f);

    std::cout << ptr->i << "\t" << ptr->f <<"\n";    
    return 0;
}