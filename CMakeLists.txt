cmake_minimum_required(VERSION 3.10)
project(DetectionOfContraband)

add_definitions(-std=c++17)
add_definitions(-DAPI_EXPORTS)
option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_BUILD_TYPE Release)

# onnxruntime
set(onnxruntime_dir "/usr/local")
include_directories(${onnxruntime_dir}/include/onnxruntime)

# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "opencv include path:" ${OpenCV_INCLUDE_DIRS})

# UI: imgui
include_directories(${PROJECT_SOURCE_DIR}/third_party)
file(GLOB_RECURSE IMGUI_OBJ ${PROJECT_SOURCE_DIR}/third_party/imgui/*.cpp)
add_library(ImGui STATIC ${IMGUI_OBJ})
target_link_libraries(ImGui dl)

################################################################################################################


# main 
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE COMMON_SRC ${PROJECT_SOURCE_DIR}/src/Common/*.cpp)
add_library(COMMON STATIC ${COMMON_SRC})

file(GLOB_RECURSE MODEL_SRC ${PROJECT_SOURCE_DIR}/src/ModelAdapter/*.cpp)
add_library(MODEL STATIC ${MODEL_SRC})

add_library(FILE_BROWSER STATIC ${PROJECT_SOURCE_DIR}/src/UI/Widgets/ui_FileBrowser.cpp)
target_link_libraries(FILE_BROWSER ImGui GL glfw)

file(GLOB_RECURSE UI_SRC ${PROJECT_SOURCE_DIR}/src/UI/*.cpp)
add_library(UI STATIC ${UI_SRC})
target_link_libraries(UI MODEL COMMON ImGui FILE_BROWSER)

#foreach(name IN LISTS UI_OBJ)
#    message(STATUS "UI obj: " ${name})
#endforeach()

add_executable(${PROJECT_NAME}
    src/main.cpp
)


target_link_libraries(${PROJECT_NAME} 
        UI ${OpenCV_LIBS} "${onnxruntime_dir}/lib/libonnxruntime.so")


