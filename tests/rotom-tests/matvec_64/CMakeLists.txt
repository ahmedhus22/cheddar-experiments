foreach(tests matvec_openfhe_tests matvec_rotom_profile)
  add_executable(${tests} ${tests}.cpp)
  target_link_libraries(
    ${tests}
    PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    CUDA::cudart
    matvec_rotom_fhe
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