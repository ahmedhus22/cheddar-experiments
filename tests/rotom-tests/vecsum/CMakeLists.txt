foreach(tests vecsum_rotom_profile vecsum_heir_profile)
  add_executable(${tests} vecsum_rotom_heir_profile.cpp)

  if(tests STREQUAL "vecsum_heir_profile")
    set(vecsum_library vecsum_heir_openfhe)
  else()
    set(vecsum_library vecsum_rotom_openfhe)
  endif()

  target_link_libraries(
    ${tests}
    PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    CUDA::cudart
    ${vecsum_library}
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