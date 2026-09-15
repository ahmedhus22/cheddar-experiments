function(add_lenet_test TEST_NAME SOURCE TEST_LIBRARY)
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
      TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../testdata/lenet-n2048/"
  )
endfunction()

add_lenet_test(
  lenet_n2048_tests
  lenet_n_tests.cpp
  lenet_n2048
)