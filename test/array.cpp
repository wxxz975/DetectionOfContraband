#include <iostream>
#include <stdlib.h>
using namespace std;


struct test {
    int len;
    float conf[0];
};

int main() {
    test t;
    int len = 10;
    t.conf = (float*)malloc(sizeof(float)*len);
    t.len = len;

    cout << "size:" << sizeof(test) << 
        "\n";
    

    return 0;
}

