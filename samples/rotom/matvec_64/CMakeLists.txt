add_library(matvec_rotom_fhe matvec.cpp)
target_link_libraries(matvec_rotom_fhe
  PUBLIC
  openfhe_interface
)
target_compile_options(matvec_rotom_fhe PRIVATE
  -Wno-error=sign-compare
)