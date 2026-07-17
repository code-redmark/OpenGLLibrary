cmake_minimum_required(VERSION 3.15)
project(EASUI)

find_package(OpenGL REQUIRED)

# -- Glad setup

add_library(glad STATIC 
    EASUI/DEPENDENCIES/glad/src/glad.c
)

target_include_directories(glad PUBLIC 
    EASUI/DEPENDENCIES/glad/include
)





file(GLOB_RECURSE C_CODE "EASUI/*.c" "EASUI/*.cpp")

add_executable(EASUI 
    ${C_CODE}
    "TEST.c"
)

# -- GLFW setup
target_link_directories(EASUI PRIVATE 
    "${CMAKE_SOURCE_DIR}/EASUI/DEPENDENCIES/GLFW/lib"
)

target_link_libraries(EASUI PRIVATE 
    OpenGL::GL
    glad
    "glfw3.lib"
)