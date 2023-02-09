#include "ModelClassNameManager.h"
#include <iostream>


int main(void)
{
    ModelClassNameManager modelMgr;
    if(modelMgr.readClassNameFromFile("/home/wxxz/workspace/DetectionOfContraband/test/GetCurrentPath/ClassNames.conf")){
    std::cout << "success\n";
    }
    
    for(;;)
    {
        int i;
        std::cout << "please input index:(exit == -1):";
        std::cin >> i;
        if(i == -1)
            break;

        std::cout <<"class name:" << modelMgr[i] << "\n";
    }

    return 0;
}
