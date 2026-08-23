add_library(alexnet_tiny alexnet-tiny_cheddar.cpp)
add_library(alexnet_n4096 alexnet_n4096.cpp)

target_link_libraries(alexnet_tiny PRIVATE cheddar)
target_link_libraries(alexnet_n4096 PRIVATE cheddar)