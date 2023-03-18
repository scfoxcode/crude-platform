cmake_minimum_required(VERSION 3.7)
set(CMAKE_CPP_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# This provides data needed by clangd lsp in neovim to find imports
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

project(platformer)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Our own includes
include_directories("src/")

# Include glm for vector/matrix operations
include_directories("libs/glm-master/")

add_executable(platformer
    src/main.cpp
)

target_link_libraries(platformer ${SDL2_LIBRARIES})
