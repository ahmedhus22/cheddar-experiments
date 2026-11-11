foreach(file matmul_rotom_openfhe matmul_heir_openfhe)
  add_library(${file} ${file}.cpp)
  target_link_libraries(${file}
    PUBLIC
    openfhe_interface
  )
  target_compile_options(${file} PRIVATE
    -Wno-error=sign-compare
  )
endforeach()