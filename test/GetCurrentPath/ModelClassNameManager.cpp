#include "ModelClassNameManager.h"
#include <unistd.h>
#include <fstream>

ModelClassNameManager::ModelClassNameManager()
{

}

ModelClassNameManager::~ModelClassNameManager()
{

}

// If you want to use the default path, you must transfer the current workspace to the executable path
bool ModelClassNameManager::readClassNameFromFile(const std::string& fullPath) {
    
    std::string path = fullPath;
    if(path.empty()) {
        char szPath[1024];
        getcwd(szPath, sizeof(szPath));
        //std::cout << szPath << std::endl;
        path = std::string(szPath) + "/ClassNames.conf";
        
    }
    
    std::ifstream file(path.c_str(), std::ios::in);
    if(!file.good()) {
        file.close();
        return false;
    }

    m_classNames.clear();
    std::string name;
    while(std::getline(file, name)) {
        m_classNames.push_back(name);
    }
    file.close();
    
    return true;
}
