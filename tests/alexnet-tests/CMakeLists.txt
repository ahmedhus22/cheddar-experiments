add_executable(alexnet_n4096_ltests alexnet_n4096_ltests.cpp)
target_link_libraries(
  alexnet_n4096_ltests
  PRIVATE
  GTest::gtest_main
  cheddar
  nlohmann_json::nlohmann_json
  alexnet_n4096_legacy
)
target_compile_definitions(alexnet_n4096_ltests PRIVATE
  TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../testdata/alexnet-tiny-n4096/")