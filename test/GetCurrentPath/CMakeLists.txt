# 版本设置  
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)  

add_definitions("-Wall -g")
# 声明项目名称与语言
project(GetClassNames LANGUAGES CXX)  
# 构建hello  
add_executable(GetClassNames 
    testReadClassName.cpp
    ModelClassNameManager.cpp)   
 
