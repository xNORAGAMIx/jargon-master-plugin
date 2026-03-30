cmake_minimum_required(VERSION 3.13)
project(MyClangTidyPlugin)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})

file(GLOB CHECKS "checks/*.cpp")

add_library(MyClangTidyPlugin SHARED
    MyModule.cpp
    ${CHECKS}
)

target_link_libraries(MyClangTidyPlugin
    clangTidy
    clangASTMatchers
    clangAST
    clangBasic
    clangFrontend
)