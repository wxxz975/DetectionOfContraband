cmake_minimum_required(VERSION 3.10)
project(DetectionOfContraband)

add_definitions(-std=c++17)
add_definitions(-DAPI_EXPORTS)
option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_BUILD_TYPE Debug)



# onnxruntime = v1.14.1
set(onnxruntime_dir "/usr/local/onnxruntime/onnxruntime-v1.14.1")
include_directories(${onnxruntime_dir}/include)



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


#file(GLOB_RECURSE MAIN_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE COMMON_SRC ${PROJECT_SOURCE_DIR}/src/Common/*.cpp)
add_library(COMMON STATIC ${COMMON_SRC})

file(GLOB_RECURSE MODEL_SRC ${PROJECT_SOURCE_DIR}/src/OnnxModelAdapter/*.cpp)
add_library(MODEL STATIC ${MODEL_SRC})

add_library(FILE_BROWSER STATIC ${PROJECT_SOURCE_DIR}/src/UI/Widgets/External/ui_FileBrowser.cpp)

# opengl
target_link_libraries(FILE_BROWSER ImGui GL glfw)


file(GLOB_RECURSE STYLE_SRC ${PROJECT_SOURCE_DIR}/src/UI/Style/*.cpp)
add_library(STYLE STATIC ${STYLE_SRC})
target_link_libraries(STYLE ImGui)

file(GLOB UI_SRC ${PROJECT_SOURCE_DIR}/src/UI/*.cpp)
add_library(UI STATIC ${UI_SRC})
target_link_libraries(UI MODEL COMMON FILE_BROWSER)



foreach(name IN LISTS STYLE_SRC)
  message(STATUS "MAIN obj: " ${name})
endforeach()

add_executable(${PROJECT_NAME}
    src/main.cpp
    #${MAIN_SRC}
)


target_link_libraries(${PROJECT_NAME}
  UI STYLE ${OpenCV_LIBS} "${onnxruntime_dir}/lib/libonnxruntime.so")


