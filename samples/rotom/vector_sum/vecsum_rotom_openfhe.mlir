!cc = !openfhe.crypto_context
!ct = !openfhe.ciphertext
!params = !openfhe.cc_params
!pk = !openfhe.public_key
!pt = !openfhe.plaintext
!sk = !openfhe.private_key
#layout = #tensor_ext.layout<"{ [i0, i1] -> [ct, slot] : i0 = 0 and ct = 0 and (-i1 + slot) mod 1024 = 0 and 0 <= i1 <= 1023 and 0 <= slot <= 1023 }">
#original_type = #tensor_ext.original_type<originalType = tensor<1x1024xf32>, layout = #layout>
module attributes {backend.openfhe, scheme.actual_slot_count = 4096 : i64, scheme.ckks, scheme.requested_slot_count = 1024 : i64} {
  func.func @vecsum(%cc: !cc, %arg0: tensor<1x!ct> {heir.kernel_info = {gap_factor = 1 : i64, result_shape = array<i64: 1, 1024>}, tensor_ext.original_type = #original_type}, %arg1: tensor<1x!ct> {heir.kernel_info = {gap_factor = 1 : i64, result_shape = array<i64: 1, 1024>}, tensor_ext.original_type = #original_type}) -> (tensor<1x!ct> {tensor_ext.original_type = #original_type}) attributes {heir.interface = {func_name = "vecsum", input_types = [tensor<1x1024xf32>, tensor<1x1024xf32>], result_types = [tensor<1x1024xf32>], roles = ["entry", "server.evaluate"]}} {
    %c0 = arith.constant 0 : index
    %0 = tensor.empty() : tensor<1x!ct>
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %extracted_0 = tensor.extract %arg1[%c0] : tensor<1x!ct>
    %ct = openfhe.add_inplace %cc, %extracted, %extracted_0 : (!cc, !ct, !ct) -> !ct
    %inserted = tensor.insert %ct into %0[%c0] : tensor<1x!ct>
    return %inserted : tensor<1x!ct>
  }
  func.func @vecsum__encrypt__arg0(%cc: !cc, %arg0: tensor<1x1024xf32>, %pk: !pk) -> tensor<1x!ct> attributes {heir.interface = {func_name = "vecsum", index = 0 : i64, roles = ["client.encrypt"]}} {
    %c1024_i32 = arith.constant 1024 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0 = arith.constant 0 : index
    %0 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %2 = arith.index_cast %arg1 : i32 to index
      %extracted = tensor.extract %arg0[%c0, %2] : tensor<1x1024xf32>
      %inserted = tensor.insert %extracted into %arg2[%c0, %2] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    %extracted_slice = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %1 = arith.extf %extracted_slice : tensor<1024xf32> to tensor<1024xf64>
    %pt = openfhe.make_ckks_packed_plaintext %cc, %1 : (!cc, tensor<1024xf64>) -> !pt
    %ct = openfhe.encrypt %cc, %pt, %pk : (!cc, !pt, !pk) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @vecsum__encrypt__arg1(%cc: !cc, %arg0: tensor<1x1024xf32>, %pk: !pk) -> tensor<1x!ct> attributes {heir.interface = {func_name = "vecsum", index = 1 : i64, roles = ["client.encrypt"]}} {
    %c1024_i32 = arith.constant 1024 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0 = arith.constant 0 : index
    %0 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %2 = arith.index_cast %arg1 : i32 to index
      %extracted = tensor.extract %arg0[%c0, %2] : tensor<1x1024xf32>
      %inserted = tensor.insert %extracted into %arg2[%c0, %2] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    %extracted_slice = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %1 = arith.extf %extracted_slice : tensor<1024xf32> to tensor<1024xf64>
    %pt = openfhe.make_ckks_packed_plaintext %cc, %1 : (!cc, tensor<1024xf64>) -> !pt
    %ct = openfhe.encrypt %cc, %pt, %pk : (!cc, !pt, !pk) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @vecsum__decrypt__result0(%cc: !cc, %arg0: tensor<1x!ct>, %sk: !sk) -> tensor<1x1024xf32> attributes {heir.interface = {func_name = "vecsum", index = 0 : i64, roles = ["client.decrypt"]}} {
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %c1_i32 = arith.constant 1 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %c0 = arith.constant 0 : index
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %pt = openfhe.decrypt %cc, %extracted, %sk : (!cc, !ct, !sk) -> !pt
    %0 = openfhe.decode_ckks %pt : !pt -> tensor<1x1024xf32>
    %1 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %2 = arith.subi %c1023_i32, %arg1 : i32
      %3 = arith.index_cast %2 : i32 to index
      %extracted_0 = tensor.extract %0[%c0, %3] : tensor<1x1024xf32>
      %inserted = tensor.insert %extracted_0 into %arg2[%c0, %3] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    return %1 : tensor<1x1024xf32>
  }
  func.func @vecsum__generate_crypto_context() -> !cc {
    %params = openfhe.gen_params  <mulDepth = 0, plainMod = 0, firstModSize = 55, scalingModSize = 45> : () -> !params
    %cc = openfhe.gen_context %params <supportFHE = false> : (!params) -> !cc
    return %cc : !cc
  }
  func.func @vecsum__configure_crypto_context(%cc: !cc, %sk: !sk) -> !cc {
    return %cc : !cc
  }
}

