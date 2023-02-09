#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[])
{
    char buf[256] = {0};
    getcwd(buf, sizeof(buf));

    std::cout << buf << std::endl;
    
    return 0;
}
