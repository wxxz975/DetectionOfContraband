#include "../../src/Algorithm/Message.h"
#include <iostream>


void testCreateResultList(DA::DetectionResultList& results) {
    

    for(int i = 0; i < 10; ++i)
    {
        int x = i;
        int y = i;
        int index = i*i;
        float conf = 3*i;
        
        results.push_back({x, y, index, conf});
    }

}


void testResultList() {
    
    using namespace DA;
    using namespace std;

    // create the result list
    DetectionResultList results;
    testCreateResultList(results);
        

    // show the result
    for(const auto iter: results)
    {   
        cout << "class index:" 
            << iter.classIndex
            << " x:"
            << iter.x
            << " y:"
            << iter.y
            << " confidence:"
            << iter.confidence
            << "\n";
    }

}


// name , 
using ParamsNode = std::map<std::string, std::pair<ParamsType, void*>>;


void testParamsList() {
    using namespace DA;
    using namespace std;

    DetectionParamsList params;
    


    for(const auto iter: params)
    {
        cout << "name:" << 
        
    }
    

}


int main(int agrc, char*argv[]) {
    
    using namespace DA;
    testResultList();


    
    return 0;
}
