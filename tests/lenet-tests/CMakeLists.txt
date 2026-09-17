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
add_lenet_test(
  lenet_n2048_profile
  lenet_n_profile.cpp
  lenet_n2048
)

add_lenet_test(
  lenet_n8192_tests
  lenet_n_tests.cpp
  lenet_n8192
)
add_lenet_test(
  lenet_n8192_profile
  lenet_n_profile.cpp
  lenet_n8192
)

add_lenet_test(
  lenet_n16384_tests
  lenet_n_tests.cpp
  lenet_n16384
)
add_lenet_test(
  lenet_n16384_profile
  lenet_n_profile.cpp
  lenet_n16384
)

if(TARGET lenet_n32768)
  add_lenet_test(
    lenet_n32768_tests
    lenet_n_tests.cpp
    lenet_n32768
  )
  add_lenet_test(
    lenet_n32768_profile
    lenet_n_profile.cpp
    lenet_n32768
  )
endif()