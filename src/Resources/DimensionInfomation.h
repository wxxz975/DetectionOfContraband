#pragma once
#include <string>
#include <vector>


namespace Resources
{

  struct DimensionInfomation
  {
    std::string Name;
    size_t Size;
    std::vector<int64_t> Shape;



    DimensionInfomation(const std::string& _Name, std::vector<int64_t> _Shape)
    {
      Name = _Name;
      Shape = _Shape;
      Size = 1;

      for(const auto& dim : _Shape)
        Size *= dim;
    }

  };

}
