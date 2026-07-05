add_library(fhe_matvec matvec.cpp)
add_library(fhe_sumf sumf_cheddar.cpp)
add_library(fhe_matvec_8x8 matvec_8x8_cheddar.cpp)

target_link_libraries(fhe_matvec PRIVATE cheddar)
target_link_libraries(fhe_sumf PRIVATE cheddar)
target_link_libraries(fhe_matvec_8x8 PRIVATE cheddar)
