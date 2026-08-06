add_executable(bert_openfhe_profile bert_openfhe_profile.cpp)
target_link_libraries(bert_openfhe_profile PRIVATE openfhe_bert)
target_include_directories(bert_openfhe_profile PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_compile_definitions(bert_openfhe_profile PRIVATE
  TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../testdata")
target_compile_options(bert_openfhe_profile PRIVATE
  -O3
  -g
  -fno-omit-frame-pointer
)

add_executable(bert_cheddar_profile bert_cheddar_profile.cpp)
target_link_libraries(bert_cheddar_profile PRIVATE cheddar fhe_bert_attention)
target_include_directories(bert_cheddar_profile PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_compile_definitions(bert_cheddar_profile PRIVATE
  TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../testdata")
target_compile_options(bert_cheddar_profile PRIVATE
  -O3
  -g
  -fno-omit-frame-pointer
)