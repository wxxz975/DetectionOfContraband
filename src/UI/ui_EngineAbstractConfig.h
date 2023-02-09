
#include <map>
#include <string>
#include <variant>

class ui_EngineAbstractConfig
{
protected:
    using ConfigNode = std::variant<float, int>; 
    /* data */
    std::map<std::string, ConfigNode> m_data;

public:
    
    ui_EngineAbstractConfig(/* args */) = default;
    
    ~ui_EngineAbstractConfig() = default;

    virtual inline ConfigNode& operator[](const std::string& key) {
        return m_data[key];
    };
    
    template<typename T>
    inline void insert(const std::string& key,  const T& value) {
        this->m_data[key] = value;
    }

/*
    template<typename T>
    virtual inline T& get(const std::string& key) {
        return this->m_data[key];
    }
*/
};

