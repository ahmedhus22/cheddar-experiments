add_library(alexnet_tiny alexnet-tiny_cheddar.cpp)

target_link_libraries(alexnet_tiny PRIVATE cheddar)