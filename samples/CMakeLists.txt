add_library(fhe_matvec matvec.cpp)
add_library(fhe_sumf sumf_cheddar.cpp)
add_library(fhe_mv_identity matvec_identity.cpp)

target_link_libraries(fhe_matvec PRIVATE cheddar)
target_link_libraries(fhe_sumf PRIVATE cheddar)
target_link_libraries(fhe_mv_identity PRIVATE cheddar)
