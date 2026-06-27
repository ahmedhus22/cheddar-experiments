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

include(GoogleTest)
gtest_discover_tests(sumf_test)
