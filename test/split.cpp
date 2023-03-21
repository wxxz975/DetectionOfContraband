#include <vector>
#include <string>
#include <iostream>



std::vector<std::string> split(const std::string& str, const std::string& pattern)
{
    std::vector<std::string> ret;
    if (pattern.empty())
    {
        return ret;
    }
    size_t start = 0, index = str.find_first_of(pattern,0);
    while (index != str.npos)
    {
        if (start != index)
        {
            ret.push_back(str.substr(start,index-start));
        }
        start = index + 1;
        index = str.find_first_of(pattern, start);
    }
    if (!str.substr(start).empty())
    {
        ret.push_back(str.substr(start));
    }
    return ret;
}

using namespace std;

int main() {
    string str = "hello world, this is my first test!";
    auto ret = split(str, "\'");
    
    cout << "ret cnt:" << ret.size() << "\n";
    
    return 0;
}
