#pragma once
#include <limits>
#include <vector>
#include <memory>


template<typename _T>
class Vec
{
  private:
    bool reserve(std::size_t size)
    {
      if(m_pData != nullptr) delete m_pData;

      m_pData = new _T[size];
      
      if(m_pData != nullptr) {
        m_capacity = size;
        return true;
      }
      return false;
    }

  public:
    
    Vec() { };
    

    Vec(const _T* args, std::size_t size) {
      bool valid = reserve(size);

      std::vector<int> a;
      a.begin();
      std::copy(args, args+size, m_pData); 
      
      m_size = size;
    };   

    
    const std::size_t size() const {
      return m_size;
    }

    const std::size_t capacity() const {
      return m_capacity;
    }

    _T operator[](std::size_t idx) {
      return (idx < m_size && idx >= 0) ? 
        m_pData[idx] : std::numeric_limits<std::size_t>::min();
    };


    Vec<_T>& operator=(const Vec<_T>& other) {
      if(m_capacity < other.size()) {
         bool valid = reverse(other.size());
         // TODO: Validate the return 
      }
      
      std::copy(other.m_pData, other.m_pData+other.size(), m_pData);

      return *this;
    };

    Vec<_T>& operator=(Vec<_T>&& other) {
      m_pData = other.m_pData;
      m_size = other.size();
      m_capacity = other.capacity();

      other.m_pData = nullptr;

      return *this;
    }

 
    bool operator==(const Vec<_T>& other) {
      if(m_size != other.size()) return false;
      
      for(std::size_t idx = 0; idx < m_size; ++idx) {
        if(m_pData[idx] != other[idx]) return false;
      }
      return true;
    };

    Vec<_T>& operator-(const Vec<_T>& other) {
      
      Vec<_T> tmp(*this);
      if(m_size >= other.size()) 
      {
        for(std::size_t idx = 0; idx < other.size(); ++idx)
        {
          m_pData[idx] -= other[idx];
        }
      }
      
      return tmp;
    };
   
    Vec<_T>& operator+(const Vec<_T>& other) {
      Vec<_T> tmp(*this);
      if(m_size >= other.size()) 
      {
        for(std::size_t idx = 0; idx < other.size(); ++idx)
        {
          m_pData[idx] += other[idx];
        }
      }

      return tmp;
    };


    Vec<_T>& operator-(const _T& ele) {
      Vec<_T> tmp(*this);
      
      for(std::size_t idx = 0; idx < m_size; ++idx)
        tmp[idx] -= ele;

      return tmp;
    };
     
    Vec<_T>& operator+(const _T& ele) {
      Vec<_T> tmp(*this);
      
      for(std::size_t idx = 0; idx < m_size; ++idx)
        tmp[idx] += ele;


      return tmp;
    };

    Vec<_T>& operator-=(const Vec<_T>& other) {
       
      return *this;
    };

    Vec<_T>& operator+=(const Vec<_T>& other) {

      return *this;
    };

    Vec<_T>& operator-=(const _T& ele) {
      
      return *this;
    };
  
    Vec<_T>& operator+=(const _T& ele) {

      return *this;
    }
    
    Vec<_T> operator*(const _T& ele) {

      return tmp;
    }

    Vec<_T> operator/(const _T& ele) {

      return tmp;
    }

    Vec<_T>& operator*=(const _T& ele) {

      return *this;
    }

    Vec<_T>& operator/=(const _T& ele) {

      return *this;
    }

  private:

    _T* m_pData = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};

typedef Vec<float> DcSize;

