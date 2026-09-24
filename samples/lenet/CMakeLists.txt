add_library(lenet_n2048 lenet_n2048.cpp)
add_library(lenet_n8192 lenet_n8192.cpp)
add_library(lenet_n16384 lenet_n16384.cpp)

target_link_libraries(lenet_n2048 PRIVATE cheddar)
target_link_libraries(lenet_n8192 PRIVATE cheddar)
target_link_libraries(lenet_n16384 PRIVATE cheddar)

if(BUILD_LENET_LEGACY)
  foreach(n 2048 8192 16384 32768)
    add_library(lenet_n${n}_legacy lenet_n${n}_legacy.cpp)
    target_link_libraries(lenet_n${n}_legacy PRIVATE cheddar)
  endforeach()
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lenet_n32768.cpp")
  add_library(lenet_n32768 lenet_n32768.cpp)
  target_link_libraries(lenet_n32768 PRIVATE cheddar)
endif()