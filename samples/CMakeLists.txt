add_library(fhe_matvec matvec.cpp)
add_library(fhe_sumf sumf.cpp)

target_link_libraries(fhe_matvec PRIVATE cheddar)
target_link_libraries(fhe_sumf PRIVATE cheddar)
