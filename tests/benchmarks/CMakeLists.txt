add_executable(bert_openfhe_profile bert_openfhe_profile.cpp)
target_link_libraries(bert_openfhe_profile PRIVATE openfhe_bert)
target_compile_definitions(bert_openfhe_profile PRIVATE
  TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../testdata")