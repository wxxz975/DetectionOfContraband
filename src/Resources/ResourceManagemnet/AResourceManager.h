#pragma once
#include <string>
#include <unordered_map>


namespace Resources::ResourceManager
{
  template <typename T>
  class AResourceManager
  {
    public:
      
      T* LoadResource(const std::string& path);
      
      void UnloadResource(const std::string& path);

      void ReloadResource(const std::string& path);
 
      bool IsResourceLoaded(const std::string& path);
     
      void UnloadAllResources();

      T* GetResource(const std::string& path, bool loadIfNotLoaded = true);

      std::unordered_map<std::string, T*>& GetResources();
    
    protected:
      virtual T* LoadResourceImpl(const std::string& path) = 0;
      virtual void UnloadResourceImpl(T* resource) = 0;
      virtual void ReloadResourceImpl(T* resource) = 0;
      virtual bool IsResourceLoadedImpl(T* resource) = 0;
      virtual std::string GetRealPath() = 0;

    private:
      

  };

}
