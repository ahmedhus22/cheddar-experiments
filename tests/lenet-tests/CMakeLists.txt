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
  target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common/)
endfunction()

foreach(n 2048 8192 16384)
  add_lenet_test(
    lenet_n${n}_tests
    lenet_n_tests.cpp
    lenet_n${n}
  )

  add_lenet_test(
    lenet_n${n}_profile
    lenet_n_profile.cpp
    lenet_n${n}
  )
endforeach()

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

if(BUILD_LENET_LEGACY)
  foreach(n 2048 8192 16384 32768)
    add_alexnet_test(
        lenet_n${n}_lprofile
        lenet_n_lprofile.cpp
        lenet_n${n}_legacy
    )
endforeach()
endif()