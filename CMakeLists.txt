cmake_minimum_required(VERSION 3.20)

project(cheddar-exp LANGUAGES CUDA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CUDA_ARCHITECTURES 60 61 70 75 80 86 89 90)
# compile_commands.json for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make sure to install Openfhe to this path
set(CMAKE_PREFIX_PATH "$HOME/local/openfhe")

add_subdirectory(thirdparty/libtommath)
add_subdirectory(thirdparty/cheddar-fhe)
add_subdirectory(samples)

enable_testing()
add_subdirectory(tests)
