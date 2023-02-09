#pragma once

#include <vector>
#include <string>

class ModelClassNameManager
{
protected:
    typedef struct _DetectionResultNode
    {
        int x, y;
        int classIndex;
        float confidence;
    }DetectionResultNode, *pDetectionResultNode;
    
    
    std::vector<std::string> m_classNames;
public: 
    
    ModelClassNameManager();
    
    virtual ~ModelClassNameManager();
    virtual bool readClassNameFromFile(const std::string& fullPath = "");
    
    // return the class name when input the class index;
    const std::string operator[](int index) {
        return index < m_classNames.size() ? m_classNames[index] : "error index";
    };
    



};
