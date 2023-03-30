#pragma once
#include <string>
#include <unordered_map>
#include <variant>

namespace Resources
{

  class ModelConfig
  {
    typedef std::variant<std::string, int, float, bool> ConfigValue;
    public:
      ModelConfig();
      ~ModelConfig();

      // ini format file 
      bool LoadConfig(const std::string& p_path, bool p_autoSave = true);
      
      void SaveConfig(const std::string& p_path);

      // get original value by key
      std::string GetOriginalValue(const std::string& key) const;

      ConfigValue operator[](const std::string& key) const;

       
    private:
      std::string m_configPath;
      std::unordered_map<std::string, std::string> m_modelConfig;


  };
}
