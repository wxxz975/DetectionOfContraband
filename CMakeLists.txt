cmake_minimum_required(VERSION 3.10)
project(DetectionOfContraband)

add_definitions(-std=c++17)
add_definitions(-DAPI_EXPORTS)
option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_BUILD_TYPE Debug)


# tensorrt
include_directories(/usr/include/aarch64-linux-gnu)
link_directories(/usr/lib/aarch64-linux-gnu)

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
link_directories(${PROJECT_SOURCE_DIR}/third_party/lib/lib64)

add_library(ImGui SHARED ${IMGUI_OBJ})

################################################################################################################


# main 
#file(GLOB_RECURSE MAIN_H ${PROJECT_SOURCE_DIR}/src/*.h)
include_directories(${PROJECT_SOURCE_DIR}/src)


#target_link_libraries(UI ImGui)

file(GLOB_RECURSE COMMON_OBJ ${PROJECT_SOURCE_DIR}/src/Common/*.cpp)
add_library(COMMON STATIC ${COMMON_OBJ})

file(GLOB_RECURSE MODEL_OBJ ${PROJECT_SOURCE_DIR}/src/ModelAdapter/*.cpp)
add_library(MODEL STATIC ${MODEL_OBJ})

foreach(name IN LISTS UI_OBJ)
    message(STATUS "UI obj: " ${name})
endforeach()

file(GLOB_RECURSE UI_OBJ ${PROJECT_SOURCE_DIR}/src/UI/*.cpp)
add_library(UI STATIC ${UI_OBJ})
target_link_libraries(UI MODEL COMMON ImGui)


add_executable(${PROJECT_NAME}
    src/main.cpp
)


target_link_libraries(${PROJECT_NAME} 
        UI
        GL glfw ${OpenCV_LIBS} "${onnxruntime_dir}/lib/libonnxruntime.so")


