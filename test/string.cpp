#include <string>
#include <iostream>
using namespace std;

int main() {
    string str = "hello world!";

    string nstr = str(1, 5);

    cout << nstr.c_str() << "\n";
    
    return 0;
}
