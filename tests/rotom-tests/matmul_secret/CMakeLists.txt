foreach(tests matmul_rotom_profile)
  add_executable(${tests} ${tests}.cpp)

  if(tests STREQUAL "matmul_heir_profile")
    set(matmul_library matmul_heir_openfhe)
  else()
    set(matmul_library matmul_rotom_openfhe)
  endif()

  target_link_libraries(
    ${tests}
    PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    CUDA::cudart
    ${matmul_library}
  )
  target_link_libraries(${tests}
    PUBLIC
    openfhe_interface
  )
  target_compile_definitions(${tests} PRIVATE
    TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../../testdata")
  target_include_directories(${tests} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common/)
endforeach()