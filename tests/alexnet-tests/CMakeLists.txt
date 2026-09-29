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
  target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common/)
endfunction()


foreach(n 4096 8192 16384 32768)
  add_alexnet_test(
    alexnet_n${n}_ltests
    alexnet_n_ltests.cpp
    alexnet_n${n}_legacy
  )
  add_alexnet_test(
    alexnet_n${n}_lprofile
    alexnet_n_lprofile.cpp
    alexnet_n${n}_legacy
  )
endforeach()

foreach(n 4096 8192 16384 32768)
  add_alexnet_test(
    alexnet_n${n}_tests
    alexnet_n_tests.cpp
    alexnet_n${n}
  )

  add_alexnet_test(
    alexnet_n${n}_profile
    alexnet_n_profile.cpp
    alexnet_n${n}
  )
endforeach()

set(ALEXNET_PROFILE
  alexnet_n4096_profile
  alexnet_n8192_profile
  alexnet_n16384_profile
  alexnet_n32768_profile
)
# DO NOT USE ctest -R "AlexnetTinyProfile\." for profiling tests, run each test individually Ex: ./build/tests/alexnet-tests/alexnet_n4096_profile
foreach(alexnet_n ${ALEXNET_PROFILE})
  gtest_discover_tests(${alexnet_n})
  # add_test(NAME ${alexnet_n} COMMAND ${alexnet_n}) 
endforeach()