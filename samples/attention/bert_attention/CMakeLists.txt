add_library(fhe_bert_attention bert_attention.cpp)
target_link_libraries(fhe_bert_attention PRIVATE cheddar)


add_library(openfhe_bert bert_attention_openfhe.cpp)
target_compile_options(openfhe_bert PRIVATE
    -Wno-error=sign-compare
)

option(BUILD_STATIC "Set to ON to include static versions of the library" OFF)

find_package(OpenFHE CONFIG REQUIRED)
if(OpenFHE_FOUND)
    message(STATUS "FOUND PACKAGE OpenFHE")
    message(STATUS "OpenFHE Version: ${BASE_OPENFHE_VERSION}")
    message(STATUS "OpenFHE installed as shared libraries: ${OpenFHE_SHARED}")
    message(STATUS "OpenFHE include files location: ${OpenFHE_INCLUDE}")
    message(STATUS "OpenFHE lib files location: ${OpenFHE_LIBDIR}")
    message(STATUS "OpenFHE Native Backend size: ${OpenFHE_NATIVE_SIZE}")
else()
    message(FATAL_ERROR "PACKAGE OpenFHE NOT FOUND")
endif()

set(CMAKE_CXX_FLAGS ${OpenFHE_CXX_FLAGS})

target_include_directories(openfhe_bert PRIVATE ${OPENMP_INCLUDES})
target_include_directories(openfhe_bert PRIVATE ${OpenFHE_INCLUDE})
target_include_directories(openfhe_bert PRIVATE ${OpenFHE_INCLUDE}/third-party/include)
target_include_directories(openfhe_bert PRIVATE ${OpenFHE_INCLUDE}/core)
target_include_directories(openfhe_bert PRIVATE ${OpenFHE_INCLUDE}/pke)
target_include_directories(openfhe_bert PRIVATE ${OpenFHE_INCLUDE}/binfhe)
### add directories for other OpenFHE modules as needed for your project

if(UNIX AND NOT APPLE)
    add_link_options(-Wl,--no-as-needed)
endif()

target_include_directories(openfhe_bert PRIVATE ${OpenFHE_LIBDIR})
target_include_directories(openfhe_bert PRIVATE ${OPENMP_LIBRARIES})
if(BUILD_STATIC)
    set(CMAKE_EXE_LINKER_FLAGS "${OpenFHE_EXE_LINKER_FLAGS} -static")
    target_link_libraries(openfhe_bert PRIVATE ${OpenFHE_STATIC_LIBRARIES})
else()
    set(CMAKE_EXE_LINKER_FLAGS ${OpenFHE_EXE_LINKER_FLAGS})
    target_link_libraries(openfhe_bert PRIVATE ${OpenFHE_SHARED_LIBRARIES})
endif()

