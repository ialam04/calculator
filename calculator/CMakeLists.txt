cmake_minimum_required(VERSION 3.27)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

# Add the main application executable
add_executable(calculator main.cpp token.cpp token_stream.cpp)
