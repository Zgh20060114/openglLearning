cmake_minimum_required(VERSION 3.25)
project(opengllearning)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB SRC ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ./inc/) # 调用者也需要，因为让自己的源文件include

add_subdirectory(./third_party/glad/)
add_subdirectory(./third_party/glfw/)
# add_subdirectory(./third_party/glm/)

# target_include_directories(glad PUBLIC ./third_party/GLAD/include/) #让调用者可以直接include,不必使用相对路径
# target_include_directories(glfw PUBLIC ./third_party/glfw/include/)
# target_include_directories(glm INTERFACE ./third_party/glm/glm/)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw)
