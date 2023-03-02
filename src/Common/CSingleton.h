#pragma once
#include <mutex>
#include <memory>

template<typename _T, typename... _Args>
class CSingleton
{
  public:
    
    static _T& GetInstance(_Args&&... __Args) 
    {
      static std::once_flag s_flag;
      std::call_once(s_flag, 
          [&]() {
        _instance.reset(new _T);
      });

      return *_instance;
    }
   
    ~CSingleton() = default;

    CSingleton() = default;

    CSingleton(const _T&) = delete;

    CSingleton& operator=(const _T&) = delete;

  private:
    static std::unique_ptr<_T> _instance;
};
