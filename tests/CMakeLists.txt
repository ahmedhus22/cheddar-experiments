include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  jsoncpp
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(jsoncpp)

enable_testing()

add_executable(sumf_test sumf_test.cpp)
target_link_libraries(
  sumf_test
  PRIVATE
  GTest::gtest_main
  cheddar
  nlohmann_json::nlohmann_json
  fhe_sumf
)

add_executable(matvec_8x8_tests matvec_8x8_tests.cpp)
target_link_libraries(
  matvec_8x8_tests
  PRIVATE
  GTest::gtest_main
  cheddar
  nlohmann_json::nlohmann_json
  fhe_matvec_8x8
)

add_executable(alexnet_tiny_tests alexnet-tiny_tests.cpp)
target_link_libraries(
  alexnet_tiny_tests
  PRIVATE
  GTest::gtest_main
  cheddar
  nlohmann_json::nlohmann_json
  alexnet_tiny
)

target_compile_definitions(alexnet_tiny_tests PRIVATE
  TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/testdata")

include(GoogleTest)
gtest_discover_tests(sumf_test matvec_8x8_tests)
