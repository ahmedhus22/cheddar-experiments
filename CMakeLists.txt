cmake_minimum_required(VERSION 3.20)

project(cheddar-exp LANGUAGES CUDA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CUDA_ARCHITECTURES 60 61 70 75 80 86 89 90)
# compile_commands.json for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CUDAToolkit_ROOT "/usr/local/cuda")
set(CMAKE_CUDA_COMPILER "/usr/local/cuda/bin/nvcc")
find_package(CUDAToolkit REQUIRED)

# Make sure to install Openfhe to this path
set(CMAKE_PREFIX_PATH "$HOME/local/openfhe")

add_subdirectory(thirdparty/libtommath)
set(BUILD_UNITTEST 0)
add_subdirectory(thirdparty/cheddar-fhe)
option(BUILD_STATIC "Set to ON to include static versions of the library" OFF)

find_package(OpenFHE CONFIG REQUIRED)

if(OpenFHE_FOUND)
  message(STATUS "FOUND PACKAGE OpenFHE")
  message(STATUS "OpenFHE Version: ${BASE_OPENFHE_VERSION}")
else()
  message(FATAL_ERROR "PACKAGE OpenFHE NOT FOUND")
endif()


# Create an interface target
add_library(openfhe_interface INTERFACE)

target_compile_options(openfhe_interface INTERFACE
  -Wno-error=sign-compare
)

target_include_directories(openfhe_interface INTERFACE
  ${OPENMP_INCLUDES}
  ${OpenFHE_INCLUDE}
  ${OpenFHE_INCLUDE}/third-party/include
  ${OpenFHE_INCLUDE}/core
  ${OpenFHE_INCLUDE}/pke
  ${OpenFHE_INCLUDE}/binfhe
)

if(UNIX AND NOT APPLE)
  target_link_options(openfhe_interface INTERFACE
    -Wl,--no-as-needed
  )
endif()


if(BUILD_STATIC)
  target_link_options(openfhe_interface INTERFACE
    ${OpenFHE_EXE_LINKER_FLAGS}
    -static
  )

  target_link_libraries(openfhe_interface INTERFACE
    ${OpenFHE_STATIC_LIBRARIES}
  )
else()
  if(OpenFHE_EXE_LINKER_FLAGS AND
   NOT OpenFHE_EXE_LINKER_FLAGS STREQUAL " ")
    target_link_options(openfhe_interface INTERFACE
      ${OpenFHE_EXE_LINKER_FLAGS}
    )
  endif()

  target_link_libraries(openfhe_interface INTERFACE
    ${OpenFHE_SHARED_LIBRARIES}
  )
endif()

add_subdirectory(samples)

enable_testing()
add_subdirectory(tests)
