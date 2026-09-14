function(add_alexnet_test TEST_NAME SOURCE TEST_LIBRARY)
  add_executable(${TEST_NAME} ${SOURCE})

  target_link_libraries(${TEST_NAME}
    PRIVATE
      GTest::gtest_main
      cheddar
      nlohmann_json::nlohmann_json
      ${TEST_LIBRARY}
  )

  target_compile_definitions(${TEST_NAME}
    PRIVATE
      TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../testdata/alexnet-tiny-n4096/"
  )
endfunction()

add_alexnet_test(
  alexnet_n4096_ltests
  alexnet_n4096_ltests.cpp
  alexnet_n4096_legacy
)

add_alexnet_test(
  alexnet_n4096_tests
  alexnet_n4096_tests.cpp
  alexnet_n4096
)
add_alexnet_test(
  alexnet_n4096_profile
  alexnet_n4096_profile.cpp
  alexnet_n4096
)

add_alexnet_test(
  alexnet_n8192_tests
  alexnet_n4096_tests.cpp
  alexnet_n8192
)
add_alexnet_test(
  alexnet_n8192_profile
  alexnet_n4096_profile.cpp
  alexnet_n8192
)