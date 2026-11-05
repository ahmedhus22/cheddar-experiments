add_executable(matvec_openfhe_tests matvec_openfhe_tests.cpp)
target_link_libraries(
  matvec_openfhe_tests
  PRIVATE
  GTest::gtest_main
  nlohmann_json::nlohmann_json
  matvec_rotom_fhe
)
target_link_libraries(matvec_openfhe_tests
  PUBLIC
  openfhe_interface
)
target_compile_definitions(matvec_openfhe_tests PRIVATE
  TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../../testdata")