foreach(tests matvec_rotom_tests matvec_rotom_profile matvec_heir_profile)
  add_executable(${tests} ${tests}.cpp)

  if(tests STREQUAL "matvec_heir_profile")
    set(matvec_library matvec_heir_openfhe)
  else()
    set(matvec_library matvec_rotom_openfhe)
  endif()

  target_link_libraries(
    ${tests}
    PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    CUDA::cudart
    ${matvec_library}
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