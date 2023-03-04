#pragma once
#include <limits>


template<typename _T>
class Vec2
{
  public:
    Vec2(): _x(0), _y(0) {};
    
    Vec2(_T x): _x(x), _y(0) {};
    
    Vec2(_T x, _T y): _x(x), _y(y) {};    

    Vec2(const Vec2<_T>& other): _x(other._x), _y(other._y) {};
   
    _T operator[](std::size_t idx) {

      switch (idx) 
      {
        case 0:
          return _x;
        case 1:
          return _y;
        default:
          return std::numeric_limits<std::size_t>::min();
      }
    };

    Vec2<_T> operator=(const Vec2<_T>& other) {
      _x = other._x; _y = other._y;
    };
 
    bool operator==(const Vec2<_T>& other) {
      return (_x == other._x) && (_y == other._y);
    };

    Vec2<_T> operator-(const Vec2<_T>& other) {
      Vec2<_T> tmp(_x, _y);
      tmp -= other;

      return tmp;
    };
   
    Vec2<_T> operator+(const Vec2<_T>& other) {
      Vec2<_T> tmp(_x, _y);
      tmp += other;

      return tmp;
    };


    Vec2<_T> operator-(const _T& ele) {
      Vec2<_T> tmp(_x, _y);
      tmp -= ele;
      
      return tmp;
    };
     
    Vec2<_T> operator+(const _T& ele) {
      Vec2<_T> tmp(_x, _y);
      tmp += ele;
      
      return tmp;
    };

    Vec2<_T>& operator-=(const Vec2<_T>& other) {
      _x -= other._x; _y -= other._y;
      
      return *this;
    };

    Vec2<_T>& operator+=(const Vec2<_T>& other) {
      _x += other._x; _y += other._y;

      return *this;
    };

    Vec2<_T>& operator-=(const _T& ele) {
      _x -= ele; _y -= ele;
      
      return *this;
    };
  
    Vec2<_T>& operator+=(const _T& ele) {
      _x += ele; _y += ele;

      return *this;
    }
    
    Vec2<_T> operator*(const _T& ele) {
      Vec2<_T> tmp(_x, _y);
      tmp *= ele;

      return tmp;
    }

    Vec2<_T> operator/(const _T& ele) {
      Vec2<_T> tmp(_x, _y);
      tmp /= ele;

      return tmp;
    }

    Vec2<_T>& operator*=(const _T& ele) {
      _x *= ele; _y *= ele;

      return *this;
    }

    Vec2<_T>& operator/=(const _T& ele) {
      _x /= ele; _y /= ele;

      return *this;
    }

  public:

    _T _x, _y;
};

typedef Vec2<float> DcSize;

