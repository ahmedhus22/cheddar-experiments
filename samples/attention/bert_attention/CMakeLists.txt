add_library(fhe_bert_attention bert_attention.cpp)
target_link_libraries(fhe_bert_attention PRIVATE cheddar)


add_library(openfhe_bert bert_attention_openfhe.cpp)
target_link_libraries(openfhe_bert
  PUBLIC
  openfhe_interface
)
target_compile_options(openfhe_bert PRIVATE
  -Wno-error=sign-compare
)


