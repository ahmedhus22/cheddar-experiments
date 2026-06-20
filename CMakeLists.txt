cmake_minimum_required(VERSION 3.20)

project(cheddar-exp LANGUAGES CUDA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

add_subdirectory(thirdparty/cheddar-fhe)
add_subdirectory(samples)