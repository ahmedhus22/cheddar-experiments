!ct = !cheddar.ciphertext
!ctx = !cheddar.context
!encoder = !cheddar.encoder
!evk = !cheddar.eval_key
!pt = !cheddar.plaintext
!ui = !cheddar.user_interface
#layout = #tensor_ext.layout<"{ [i0] -> [ct, slot] : ct = 0 and (-i0 + slot) mod 8 = 0 and 0 <= i0 <= 7 and 0 <= slot <= 1023 }">
#original_type = #tensor_ext.original_type<originalType = tensor<8xf32>, layout = #layout>
module attributes {cheddar.P = array<i64: 1073740609, 1073739937, 1073739649>, cheddar.Q = array<i64: 1073742881, 1073742721, 1073741441, 1073741857, 524353>, cheddar.logDefaultScale = 45 : i64, cheddar.logN = 4 : i64} {
  func.func private @_assign_layout_12040075739753753025(%arg0: tensor<8x8xf32>) -> tensor<8x1024xf32> attributes {client.pack_func = {func_name = "matvec_identity"}} {
    %c1024_i32 = arith.constant 1024 : i32
    %c8_i32 = arith.constant 8 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<8x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %0 = scf.for %arg1 = %c0_i32 to %c8_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<8x1024xf32>)  : i32 {
      %1 = scf.for %arg3 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg4 = %arg2) -> (tensor<8x1024xf32>)  : i32 {
        %2 = arith.remsi %arg3, %c8_i32 : i32
        %3 = arith.addi %arg1, %arg3 : i32
        %4 = arith.remsi %3, %c8_i32 : i32
        %5 = arith.index_cast %2 : i32 to index
        %6 = arith.index_cast %4 : i32 to index
        %extracted = tensor.extract %arg0[%5, %6] : tensor<8x8xf32>
        %7 = arith.index_cast %arg1 : i32 to index
        %8 = arith.index_cast %arg3 : i32 to index
        %inserted = tensor.insert %extracted into %arg4[%7, %8] : tensor<8x1024xf32>
        scf.yield %inserted : tensor<8x1024xf32>
      }
      scf.yield %1 : tensor<8x1024xf32>
    }
    return %0 : tensor<8x1024xf32>
  }
  func.func @matvec_identity(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct> {tensor_ext.original_type = #original_type}) -> (tensor<1x!ct> {tensor_ext.original_type = #original_type}) {
    %c6 = arith.constant 6 : index
    %c3 = arith.constant 3 : index
    %c2 = arith.constant 2 : index
    %c1 = arith.constant 1 : index
    %cst = arith.constant dense<[[1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00]]> : tensor<8x8xf32>
    %c0 = arith.constant 0 : index
    %0 = call @_assign_layout_12040075739753753025(%cst) : (tensor<8x8xf32>) -> tensor<8x1024xf32>
    %extracted_slice = tensor.extract_slice %0[3, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_0 = tensor.extract_slice %0[3, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %1 = tensor.empty() : tensor<1x1024xf32>
    %inserted_slice = tensor.insert_slice %extracted_slice into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_1 = tensor.insert_slice %extracted_slice_0 into %inserted_slice[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_2 = tensor.extract_slice %0[4, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_3 = tensor.extract_slice %0[4, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_4 = tensor.insert_slice %extracted_slice_2 into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_5 = tensor.insert_slice %extracted_slice_3 into %inserted_slice_4[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_6 = tensor.extract_slice %0[5, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_7 = tensor.extract_slice %0[5, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_8 = tensor.insert_slice %extracted_slice_6 into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_9 = tensor.insert_slice %extracted_slice_7 into %inserted_slice_8[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_10 = tensor.extract_slice %0[6, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_11 = tensor.extract_slice %0[6, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_12 = tensor.insert_slice %extracted_slice_10 into %1[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_13 = tensor.insert_slice %extracted_slice_11 into %inserted_slice_12[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_14 = tensor.extract_slice %0[7, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_15 = tensor.extract_slice %0[7, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_16 = tensor.insert_slice %extracted_slice_14 into %1[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_17 = tensor.insert_slice %extracted_slice_15 into %inserted_slice_16[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_18 = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice_18 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %ct = cheddar.mult_plain %ctx, %extracted, %pt : (!ctx, !ct, !pt) -> !ct
    %evk = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_19 = cheddar.hrot %ctx, %extracted, %evk, %c1 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_20 = tensor.extract_slice %0[1, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_21 = cheddar.encode %encoder, %extracted_slice_20 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_22 = cheddar.mult_plain %ctx, %ct_19, %pt_21 : (!ctx, !ct, !pt) -> !ct
    %evk_23 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_24 = cheddar.hrot %ctx, %extracted, %evk_23, %c2 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_25 = tensor.extract_slice %0[2, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_26 = cheddar.encode %encoder, %extracted_slice_25 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_27 = cheddar.mult_plain %ctx, %ct_24, %pt_26 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_28 = tensor.extract_slice %inserted_slice_1[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_29 = cheddar.encode %encoder, %extracted_slice_28 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_30 = cheddar.mult_plain %ctx, %extracted, %pt_29 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_31 = tensor.extract_slice %inserted_slice_5[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_32 = cheddar.encode %encoder, %extracted_slice_31 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_33 = cheddar.mult_plain %ctx, %ct_19, %pt_32 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_34 = tensor.extract_slice %inserted_slice_9[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_35 = cheddar.encode %encoder, %extracted_slice_34 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_36 = cheddar.mult_plain %ctx, %ct_24, %pt_35 : (!ctx, !ct, !pt) -> !ct
    %ct_37 = cheddar.add %ctx, %ct_30, %ct_33 : (!ctx, !ct, !ct) -> !ct
    %ct_38 = cheddar.add %ctx, %ct_37, %ct_36 : (!ctx, !ct, !ct) -> !ct
    %evk_39 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_40 = cheddar.hrot %ctx, %ct_38, %evk_39, %c3 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_41 = tensor.extract_slice %inserted_slice_13[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_42 = cheddar.encode %encoder, %extracted_slice_41 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_43 = cheddar.mult_plain %ctx, %extracted, %pt_42 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_44 = tensor.extract_slice %inserted_slice_17[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_45 = cheddar.encode %encoder, %extracted_slice_44 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_46 = cheddar.mult_plain %ctx, %ct_19, %pt_45 : (!ctx, !ct, !pt) -> !ct
    %ct_47 = cheddar.add %ctx, %ct_43, %ct_46 : (!ctx, !ct, !ct) -> !ct
    %evk_48 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_49 = cheddar.hrot %ctx, %ct_47, %evk_48, %c6 : (!ctx, !ct, !evk, index) -> !ct
    %ct_50 = cheddar.add %ctx, %ct, %ct_22 : (!ctx, !ct, !ct) -> !ct
    %ct_51 = cheddar.add %ctx, %ct_27, %ct_40 : (!ctx, !ct, !ct) -> !ct
    %ct_52 = cheddar.add %ctx, %ct_51, %ct_49 : (!ctx, !ct, !ct) -> !ct
    %ct_53 = cheddar.add %ctx, %ct_50, %ct_52 : (!ctx, !ct, !ct) -> !ct
    %2 = tensor.empty() : tensor<1x!ct>
    %ct_54 = cheddar.rescale %ctx, %ct_53 : (!ctx, !ct) -> !ct
    %inserted = tensor.insert %ct_54 into %2[%c0] : tensor<1x!ct>
    return %inserted : tensor<1x!ct>
  }
  func.func @matvec_identity__encrypt__arg0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<8xf32>, %ui_0: !ui) -> tensor<1x!ct> attributes {client.enc_func = {func_name = "matvec_identity", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c8_i32 = arith.constant 8 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %0 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %1 = arith.remsi %arg1, %c8_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %extracted = tensor.extract %arg0[%2] : tensor<8xf32>
      %3 = arith.index_cast %arg1 : i32 to index
      %inserted = tensor.insert %extracted into %arg2[%c0, %3] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    %extracted_slice = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct = cheddar.encrypt %ui, %pt : (!ui, !pt) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @matvec_identity__decrypt__result0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct>, %ui_0: !ui) -> tensor<8xf32> attributes {client.dec_func = {func_name = "matvec_identity", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c1024_i32 = arith.constant 1024 : i32
    %c8_i32 = arith.constant 8 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<8xf32>
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %pt = cheddar.decrypt %ui, %extracted : (!ui, !ct) -> !pt
    %0 = cheddar.decode %encoder, %pt : (!encoder, !pt) -> tensor<1x1024xf32>
    %1 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<8xf32>)  : i32 {
      %2 = arith.remsi %arg1, %c8_i32 : i32
      %3 = arith.index_cast %arg1 : i32 to index
      %extracted_1 = tensor.extract %0[%c0, %3] : tensor<1x1024xf32>
      %4 = arith.index_cast %2 : i32 to index
      %inserted = tensor.insert %extracted_1 into %arg2[%4] : tensor<8xf32>
      scf.yield %inserted : tensor<8xf32>
    }
    return %1 : tensor<8xf32>
  }
  func.func @matvec_shift(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct> {tensor_ext.original_type = #original_type}) -> (tensor<1x!ct> {tensor_ext.original_type = #original_type}) {
    %c6 = arith.constant 6 : index
    %c3 = arith.constant 3 : index
    %c2 = arith.constant 2 : index
    %c1 = arith.constant 1 : index
    %cst = arith.constant dense<[[0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00], [1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00]]> : tensor<8x8xf32>
    %c0 = arith.constant 0 : index
    %0 = call @_assign_layout_12040075739753753025(%cst) : (tensor<8x8xf32>) -> tensor<8x1024xf32>
    %extracted_slice = tensor.extract_slice %0[3, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_0 = tensor.extract_slice %0[3, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %1 = tensor.empty() : tensor<1x1024xf32>
    %inserted_slice = tensor.insert_slice %extracted_slice into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_1 = tensor.insert_slice %extracted_slice_0 into %inserted_slice[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_2 = tensor.extract_slice %0[4, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_3 = tensor.extract_slice %0[4, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_4 = tensor.insert_slice %extracted_slice_2 into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_5 = tensor.insert_slice %extracted_slice_3 into %inserted_slice_4[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_6 = tensor.extract_slice %0[5, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_7 = tensor.extract_slice %0[5, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_8 = tensor.insert_slice %extracted_slice_6 into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_9 = tensor.insert_slice %extracted_slice_7 into %inserted_slice_8[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_10 = tensor.extract_slice %0[6, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_11 = tensor.extract_slice %0[6, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_12 = tensor.insert_slice %extracted_slice_10 into %1[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_13 = tensor.insert_slice %extracted_slice_11 into %inserted_slice_12[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_14 = tensor.extract_slice %0[7, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_15 = tensor.extract_slice %0[7, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_16 = tensor.insert_slice %extracted_slice_14 into %1[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_17 = tensor.insert_slice %extracted_slice_15 into %inserted_slice_16[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_18 = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice_18 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %ct = cheddar.mult_plain %ctx, %extracted, %pt : (!ctx, !ct, !pt) -> !ct
    %evk = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_19 = cheddar.hrot %ctx, %extracted, %evk, %c1 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_20 = tensor.extract_slice %0[1, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_21 = cheddar.encode %encoder, %extracted_slice_20 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_22 = cheddar.mult_plain %ctx, %ct_19, %pt_21 : (!ctx, !ct, !pt) -> !ct
    %evk_23 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_24 = cheddar.hrot %ctx, %extracted, %evk_23, %c2 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_25 = tensor.extract_slice %0[2, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_26 = cheddar.encode %encoder, %extracted_slice_25 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_27 = cheddar.mult_plain %ctx, %ct_24, %pt_26 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_28 = tensor.extract_slice %inserted_slice_1[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_29 = cheddar.encode %encoder, %extracted_slice_28 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_30 = cheddar.mult_plain %ctx, %extracted, %pt_29 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_31 = tensor.extract_slice %inserted_slice_5[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_32 = cheddar.encode %encoder, %extracted_slice_31 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_33 = cheddar.mult_plain %ctx, %ct_19, %pt_32 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_34 = tensor.extract_slice %inserted_slice_9[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_35 = cheddar.encode %encoder, %extracted_slice_34 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_36 = cheddar.mult_plain %ctx, %ct_24, %pt_35 : (!ctx, !ct, !pt) -> !ct
    %ct_37 = cheddar.add %ctx, %ct_30, %ct_33 : (!ctx, !ct, !ct) -> !ct
    %ct_38 = cheddar.add %ctx, %ct_37, %ct_36 : (!ctx, !ct, !ct) -> !ct
    %evk_39 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_40 = cheddar.hrot %ctx, %ct_38, %evk_39, %c3 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_41 = tensor.extract_slice %inserted_slice_13[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_42 = cheddar.encode %encoder, %extracted_slice_41 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_43 = cheddar.mult_plain %ctx, %extracted, %pt_42 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_44 = tensor.extract_slice %inserted_slice_17[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_45 = cheddar.encode %encoder, %extracted_slice_44 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_46 = cheddar.mult_plain %ctx, %ct_19, %pt_45 : (!ctx, !ct, !pt) -> !ct
    %ct_47 = cheddar.add %ctx, %ct_43, %ct_46 : (!ctx, !ct, !ct) -> !ct
    %evk_48 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_49 = cheddar.hrot %ctx, %ct_47, %evk_48, %c6 : (!ctx, !ct, !evk, index) -> !ct
    %ct_50 = cheddar.add %ctx, %ct, %ct_22 : (!ctx, !ct, !ct) -> !ct
    %ct_51 = cheddar.add %ctx, %ct_27, %ct_40 : (!ctx, !ct, !ct) -> !ct
    %ct_52 = cheddar.add %ctx, %ct_51, %ct_49 : (!ctx, !ct, !ct) -> !ct
    %ct_53 = cheddar.add %ctx, %ct_50, %ct_52 : (!ctx, !ct, !ct) -> !ct
    %2 = tensor.empty() : tensor<1x!ct>
    %ct_54 = cheddar.rescale %ctx, %ct_53 : (!ctx, !ct) -> !ct
    %inserted = tensor.insert %ct_54 into %2[%c0] : tensor<1x!ct>
    return %inserted : tensor<1x!ct>
  }
  func.func @matvec_shift__encrypt__arg0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<8xf32>, %ui_0: !ui) -> tensor<1x!ct> attributes {client.enc_func = {func_name = "matvec_shift", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c8_i32 = arith.constant 8 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %0 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %1 = arith.remsi %arg1, %c8_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %extracted = tensor.extract %arg0[%2] : tensor<8xf32>
      %3 = arith.index_cast %arg1 : i32 to index
      %inserted = tensor.insert %extracted into %arg2[%c0, %3] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    %extracted_slice = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct = cheddar.encrypt %ui, %pt : (!ui, !pt) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @matvec_shift__decrypt__result0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct>, %ui_0: !ui) -> tensor<8xf32> attributes {client.dec_func = {func_name = "matvec_shift", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c1024_i32 = arith.constant 1024 : i32
    %c8_i32 = arith.constant 8 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<8xf32>
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %pt = cheddar.decrypt %ui, %extracted : (!ui, !ct) -> !pt
    %0 = cheddar.decode %encoder, %pt : (!encoder, !pt) -> tensor<1x1024xf32>
    %1 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<8xf32>)  : i32 {
      %2 = arith.remsi %arg1, %c8_i32 : i32
      %3 = arith.index_cast %arg1 : i32 to index
      %extracted_1 = tensor.extract %0[%c0, %3] : tensor<1x1024xf32>
      %4 = arith.index_cast %2 : i32 to index
      %inserted = tensor.insert %extracted_1 into %arg2[%4] : tensor<8xf32>
      scf.yield %inserted : tensor<8xf32>
    }
    return %1 : tensor<8xf32>
  }
  func.func @matvec_random(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct> {tensor_ext.original_type = #original_type}) -> (tensor<1x!ct> {tensor_ext.original_type = #original_type}) {
    %c6 = arith.constant 6 : index
    %c3 = arith.constant 3 : index
    %c2 = arith.constant 2 : index
    %c1 = arith.constant 1 : index
    %cst = arith.constant dense<[[0.811626255, 1.90635717, 1.49078846, 1.23745108, 0.39643541, 0.396389604, 0.210358858, 1.74573469], [1.24211848, 1.44533789, 0.139110535, 1.94282877, 1.68164098, 0.503444314, 0.445467442, 0.448468566], [0.678060233, 1.0970372, 0.920695543, 0.653335392, 1.26252055, 0.365038335, 0.655074835, 0.796087503], [0.966532945, 1.59183431, 0.47938019, 1.07704544, 1.22558773, 0.188255787, 1.25433517, 0.423995823], [0.223598033, 1.90288258, 1.93470085, 1.63595498, 0.678766131, 0.285577029, 1.40004277, 0.936289727], [0.331872642, 1.0408361, 0.165338188, 1.82770872, 0.591681957, 1.3587923, 6.922510e-01, 1.08812928], [1.13874948, 0.451223463, 1.94221079, 1.57275236, 1.88504803, 1.80017197, 1.236010e+00, 1.85156107], [0.268135756, 0.472367436, 0.185931846, 0.718127608, 0.83848685, 0.615563154, 1.67460132, 0.777831316]]> : tensor<8x8xf32>
    %c0 = arith.constant 0 : index
    %0 = call @_assign_layout_12040075739753753025(%cst) : (tensor<8x8xf32>) -> tensor<8x1024xf32>
    %extracted_slice = tensor.extract_slice %0[3, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_0 = tensor.extract_slice %0[3, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %1 = tensor.empty() : tensor<1x1024xf32>
    %inserted_slice = tensor.insert_slice %extracted_slice into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_1 = tensor.insert_slice %extracted_slice_0 into %inserted_slice[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_2 = tensor.extract_slice %0[4, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_3 = tensor.extract_slice %0[4, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_4 = tensor.insert_slice %extracted_slice_2 into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_5 = tensor.insert_slice %extracted_slice_3 into %inserted_slice_4[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_6 = tensor.extract_slice %0[5, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_7 = tensor.extract_slice %0[5, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_8 = tensor.insert_slice %extracted_slice_6 into %1[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_9 = tensor.insert_slice %extracted_slice_7 into %inserted_slice_8[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_10 = tensor.extract_slice %0[6, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_11 = tensor.extract_slice %0[6, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_12 = tensor.insert_slice %extracted_slice_10 into %1[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_13 = tensor.insert_slice %extracted_slice_11 into %inserted_slice_12[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_14 = tensor.extract_slice %0[7, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_15 = tensor.extract_slice %0[7, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_16 = tensor.insert_slice %extracted_slice_14 into %1[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_17 = tensor.insert_slice %extracted_slice_15 into %inserted_slice_16[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_18 = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice_18 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %ct = cheddar.mult_plain %ctx, %extracted, %pt : (!ctx, !ct, !pt) -> !ct
    %evk = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_19 = cheddar.hrot %ctx, %extracted, %evk, %c1 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_20 = tensor.extract_slice %0[1, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_21 = cheddar.encode %encoder, %extracted_slice_20 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_22 = cheddar.mult_plain %ctx, %ct_19, %pt_21 : (!ctx, !ct, !pt) -> !ct
    %evk_23 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_24 = cheddar.hrot %ctx, %extracted, %evk_23, %c2 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_25 = tensor.extract_slice %0[2, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_26 = cheddar.encode %encoder, %extracted_slice_25 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_27 = cheddar.mult_plain %ctx, %ct_24, %pt_26 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_28 = tensor.extract_slice %inserted_slice_1[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_29 = cheddar.encode %encoder, %extracted_slice_28 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_30 = cheddar.mult_plain %ctx, %extracted, %pt_29 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_31 = tensor.extract_slice %inserted_slice_5[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_32 = cheddar.encode %encoder, %extracted_slice_31 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_33 = cheddar.mult_plain %ctx, %ct_19, %pt_32 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_34 = tensor.extract_slice %inserted_slice_9[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_35 = cheddar.encode %encoder, %extracted_slice_34 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_36 = cheddar.mult_plain %ctx, %ct_24, %pt_35 : (!ctx, !ct, !pt) -> !ct
    %ct_37 = cheddar.add %ctx, %ct_30, %ct_33 : (!ctx, !ct, !ct) -> !ct
    %ct_38 = cheddar.add %ctx, %ct_37, %ct_36 : (!ctx, !ct, !ct) -> !ct
    %evk_39 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_40 = cheddar.hrot %ctx, %ct_38, %evk_39, %c3 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_41 = tensor.extract_slice %inserted_slice_13[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_42 = cheddar.encode %encoder, %extracted_slice_41 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_43 = cheddar.mult_plain %ctx, %extracted, %pt_42 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_44 = tensor.extract_slice %inserted_slice_17[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_45 = cheddar.encode %encoder, %extracted_slice_44 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_46 = cheddar.mult_plain %ctx, %ct_19, %pt_45 : (!ctx, !ct, !pt) -> !ct
    %ct_47 = cheddar.add %ctx, %ct_43, %ct_46 : (!ctx, !ct, !ct) -> !ct
    %evk_48 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_49 = cheddar.hrot %ctx, %ct_47, %evk_48, %c6 : (!ctx, !ct, !evk, index) -> !ct
    %ct_50 = cheddar.add %ctx, %ct, %ct_22 : (!ctx, !ct, !ct) -> !ct
    %ct_51 = cheddar.add %ctx, %ct_27, %ct_40 : (!ctx, !ct, !ct) -> !ct
    %ct_52 = cheddar.add %ctx, %ct_51, %ct_49 : (!ctx, !ct, !ct) -> !ct
    %ct_53 = cheddar.add %ctx, %ct_50, %ct_52 : (!ctx, !ct, !ct) -> !ct
    %2 = tensor.empty() : tensor<1x!ct>
    %ct_54 = cheddar.rescale %ctx, %ct_53 : (!ctx, !ct) -> !ct
    %inserted = tensor.insert %ct_54 into %2[%c0] : tensor<1x!ct>
    return %inserted : tensor<1x!ct>
  }
  func.func @matvec_random__encrypt__arg0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<8xf32>, %ui_0: !ui) -> tensor<1x!ct> attributes {client.enc_func = {func_name = "matvec_random", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c8_i32 = arith.constant 8 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %0 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %1 = arith.remsi %arg1, %c8_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %extracted = tensor.extract %arg0[%2] : tensor<8xf32>
      %3 = arith.index_cast %arg1 : i32 to index
      %inserted = tensor.insert %extracted into %arg2[%c0, %3] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    %extracted_slice = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct = cheddar.encrypt %ui, %pt : (!ui, !pt) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @matvec_random__decrypt__result0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct>, %ui_0: !ui) -> tensor<8xf32> attributes {client.dec_func = {func_name = "matvec_random", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c1024_i32 = arith.constant 1024 : i32
    %c8_i32 = arith.constant 8 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<8xf32>
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %pt = cheddar.decrypt %ui, %extracted : (!ui, !ct) -> !pt
    %0 = cheddar.decode %encoder, %pt : (!encoder, !pt) -> tensor<1x1024xf32>
    %1 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<8xf32>)  : i32 {
      %2 = arith.remsi %arg1, %c8_i32 : i32
      %3 = arith.index_cast %arg1 : i32 to index
      %extracted_1 = tensor.extract %0[%c0, %3] : tensor<1x1024xf32>
      %4 = arith.index_cast %2 : i32 to index
      %inserted = tensor.insert %extracted_1 into %arg2[%4] : tensor<8xf32>
      scf.yield %inserted : tensor<8xf32>
    }
    return %1 : tensor<8xf32>
  }
  func.func @matvec_chain(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct> {tensor_ext.original_type = #original_type}) -> (tensor<1x!ct> {tensor_ext.original_type = #original_type}) {
    %c6 = arith.constant 6 : index
    %c3 = arith.constant 3 : index
    %c2 = arith.constant 2 : index
    %c1 = arith.constant 1 : index
    %cst = arith.constant dense<[[1.200000e+00, 7.900000e-01, 7.300000e-01, 1.050000e+00, 1.220000e+00, 9.200000e-01, 1.480000e+00, 1.180000e+00], [9.800000e-01, 0.889999985, 0.839999973, 1.230000e+00, 0.939999997, 5.600000e-01, 0.899999976, 1.240000e+00], [6.800000e-01, 6.800000e-01, 1.030000e+00, 1.030000e+00, 1.130000e+00, 1.350000e+00, 1.220000e+00, 1.110000e+00], [1.220000e+00, 0.819999992, 8.600000e-01, 7.300000e-01, 7.900000e-01, 1.130000e+00, 5.900000e-01, 9.300000e-01], [9.300000e-01, 9.900000e-01, 9.300000e-01, 8.100000e-01, 9.300000e-01, 1.390000e+00, 1.440000e+00, 1.000000e+00], [1.120000e+00, 6.200000e-01, 0.819999992, 9.100000e-01, 1.370000e+00, 7.500000e-01, 9.800000e-01, 1.490000e+00], [1.020000e+00, 1.110000e+00, 6.200000e-01, 1.330000e+00, 1.100000e+00, 1.050000e+00, 0.839999973, 8.000000e-01], [9.200000e-01, 1.180000e+00, 1.380000e+00, 1.010000e+00, 1.170000e+00, 1.090000e+00, 1.120000e+00, 1.170000e+00]]> : tensor<8x8xf32>
    %cst_0 = arith.constant dense<[[1.340000e+00, 5.800000e-01, 1.260000e+00, 7.400000e-01, 0.689999997, 1.070000e+00, 6.000000e-01, 1.390000e+00], [1.130000e+00, 1.220000e+00, 5.200000e-01, 1.090000e+00, 1.060000e+00, 6.600000e-01, 6.500000e-01, 1.200000e+00], [0.819999992, 1.190000e+00, 1.050000e+00, 0.889999985, 1.430000e+00, 1.340000e+00, 8.600000e-01, 5.400000e-01], [8.000000e-01, 0.899999976, 1.200000e+00, 1.500000e+00, 8.600000e-01, 1.260000e+00, 1.090000e+00, 1.190000e+00], [6.500000e-01, 0.899999976, 7.400000e-01, 0.839999973, 1.010000e+00, 1.170000e+00, 6.100000e-01, 6.300000e-01], [0.819999992, 1.160000e+00, 1.350000e+00, 1.050000e+00, 1.350000e+00, 0.879999995, 0.819999992, 8.500000e-01], [6.700000e-01, 1.330000e+00, 0.839999973, 1.050000e+00, 1.080000e+00, 1.020000e+00, 5.000000e-01, 1.490000e+00], [1.410000e+00, 0.709999978, 7.900000e-01, 1.020000e+00, 1.400000e+00, 1.480000e+00, 7.600000e-01, 1.060000e+00]]> : tensor<8x8xf32>
    %c0 = arith.constant 0 : index
    %0 = call @_assign_layout_12040075739753753025(%cst_0) : (tensor<8x8xf32>) -> tensor<8x1024xf32>
    %1 = call @_assign_layout_12040075739753753025(%cst) : (tensor<8x8xf32>) -> tensor<8x1024xf32>
    %extracted_slice = tensor.extract_slice %1[3, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_1 = tensor.extract_slice %1[3, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %2 = tensor.empty() : tensor<1x1024xf32>
    %inserted_slice = tensor.insert_slice %extracted_slice into %2[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_2 = tensor.insert_slice %extracted_slice_1 into %inserted_slice[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_3 = tensor.extract_slice %1[4, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_4 = tensor.extract_slice %1[4, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_5 = tensor.insert_slice %extracted_slice_3 into %2[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_6 = tensor.insert_slice %extracted_slice_4 into %inserted_slice_5[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_7 = tensor.extract_slice %1[5, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_8 = tensor.extract_slice %1[5, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_9 = tensor.insert_slice %extracted_slice_7 into %2[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_10 = tensor.insert_slice %extracted_slice_8 into %inserted_slice_9[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_11 = tensor.extract_slice %1[6, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_12 = tensor.extract_slice %1[6, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_13 = tensor.insert_slice %extracted_slice_11 into %2[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_14 = tensor.insert_slice %extracted_slice_12 into %inserted_slice_13[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_15 = tensor.extract_slice %1[7, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_16 = tensor.extract_slice %1[7, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_17 = tensor.insert_slice %extracted_slice_15 into %2[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_18 = tensor.insert_slice %extracted_slice_16 into %inserted_slice_17[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_19 = tensor.extract_slice %0[3, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_20 = tensor.extract_slice %0[3, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_21 = tensor.insert_slice %extracted_slice_19 into %2[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_22 = tensor.insert_slice %extracted_slice_20 into %inserted_slice_21[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_23 = tensor.extract_slice %0[4, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_24 = tensor.extract_slice %0[4, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_25 = tensor.insert_slice %extracted_slice_23 into %2[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_26 = tensor.insert_slice %extracted_slice_24 into %inserted_slice_25[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_27 = tensor.extract_slice %0[5, 0] [1, 1021] [1, 1] : tensor<8x1024xf32> to tensor<1x1021xf32>
    %extracted_slice_28 = tensor.extract_slice %0[5, 1021] [1, 3] [1, 1] : tensor<8x1024xf32> to tensor<1x3xf32>
    %inserted_slice_29 = tensor.insert_slice %extracted_slice_27 into %2[0, 3] [1, 1021] [1, 1] : tensor<1x1021xf32> into tensor<1x1024xf32>
    %inserted_slice_30 = tensor.insert_slice %extracted_slice_28 into %inserted_slice_29[0, 0] [1, 3] [1, 1] : tensor<1x3xf32> into tensor<1x1024xf32>
    %extracted_slice_31 = tensor.extract_slice %0[6, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_32 = tensor.extract_slice %0[6, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_33 = tensor.insert_slice %extracted_slice_31 into %2[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_34 = tensor.insert_slice %extracted_slice_32 into %inserted_slice_33[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_35 = tensor.extract_slice %0[7, 0] [1, 1018] [1, 1] : tensor<8x1024xf32> to tensor<1x1018xf32>
    %extracted_slice_36 = tensor.extract_slice %0[7, 1018] [1, 6] [1, 1] : tensor<8x1024xf32> to tensor<1x6xf32>
    %inserted_slice_37 = tensor.insert_slice %extracted_slice_35 into %2[0, 6] [1, 1018] [1, 1] : tensor<1x1018xf32> into tensor<1x1024xf32>
    %inserted_slice_38 = tensor.insert_slice %extracted_slice_36 into %inserted_slice_37[0, 0] [1, 6] [1, 1] : tensor<1x6xf32> into tensor<1x1024xf32>
    %extracted_slice_39 = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice_39 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %ct = cheddar.mult_plain %ctx, %extracted, %pt : (!ctx, !ct, !pt) -> !ct
    %evk = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_40 = cheddar.hrot %ctx, %extracted, %evk, %c1 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_41 = tensor.extract_slice %0[1, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_42 = cheddar.encode %encoder, %extracted_slice_41 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_43 = cheddar.mult_plain %ctx, %ct_40, %pt_42 : (!ctx, !ct, !pt) -> !ct
    %evk_44 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_45 = cheddar.hrot %ctx, %extracted, %evk_44, %c2 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_46 = tensor.extract_slice %0[2, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_47 = cheddar.encode %encoder, %extracted_slice_46 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_48 = cheddar.mult_plain %ctx, %ct_45, %pt_47 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_49 = tensor.extract_slice %inserted_slice_22[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_50 = cheddar.encode %encoder, %extracted_slice_49 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_51 = cheddar.mult_plain %ctx, %extracted, %pt_50 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_52 = tensor.extract_slice %inserted_slice_26[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_53 = cheddar.encode %encoder, %extracted_slice_52 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_54 = cheddar.mult_plain %ctx, %ct_40, %pt_53 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_55 = tensor.extract_slice %inserted_slice_30[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_56 = cheddar.encode %encoder, %extracted_slice_55 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_57 = cheddar.mult_plain %ctx, %ct_45, %pt_56 : (!ctx, !ct, !pt) -> !ct
    %ct_58 = cheddar.add %ctx, %ct_51, %ct_54 : (!ctx, !ct, !ct) -> !ct
    %ct_59 = cheddar.add %ctx, %ct_58, %ct_57 : (!ctx, !ct, !ct) -> !ct
    %evk_60 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_61 = cheddar.hrot %ctx, %ct_59, %evk_60, %c3 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_62 = tensor.extract_slice %inserted_slice_34[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_63 = cheddar.encode %encoder, %extracted_slice_62 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_64 = cheddar.mult_plain %ctx, %extracted, %pt_63 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_65 = tensor.extract_slice %inserted_slice_38[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_66 = cheddar.encode %encoder, %extracted_slice_65 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_67 = cheddar.mult_plain %ctx, %ct_40, %pt_66 : (!ctx, !ct, !pt) -> !ct
    %ct_68 = cheddar.add %ctx, %ct_64, %ct_67 : (!ctx, !ct, !ct) -> !ct
    %evk_69 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_70 = cheddar.hrot %ctx, %ct_68, %evk_69, %c6 : (!ctx, !ct, !evk, index) -> !ct
    %ct_71 = cheddar.add %ctx, %ct, %ct_43 : (!ctx, !ct, !ct) -> !ct
    %ct_72 = cheddar.add %ctx, %ct_48, %ct_61 : (!ctx, !ct, !ct) -> !ct
    %ct_73 = cheddar.add %ctx, %ct_72, %ct_70 : (!ctx, !ct, !ct) -> !ct
    %ct_74 = cheddar.add %ctx, %ct_71, %ct_73 : (!ctx, !ct, !ct) -> !ct
    %ct_75 = cheddar.rescale %ctx, %ct_74 : (!ctx, !ct) -> !ct
    %extracted_slice_76 = tensor.extract_slice %1[0, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_77 = cheddar.encode %encoder, %extracted_slice_76 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_78 = cheddar.mult_plain %ctx, %ct_75, %pt_77 : (!ctx, !ct, !pt) -> !ct
    %evk_79 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_80 = cheddar.hrot %ctx, %ct_74, %evk_79, %c1 : (!ctx, !ct, !evk, index) -> !ct
    %ct_81 = cheddar.rescale %ctx, %ct_80 : (!ctx, !ct) -> !ct
    %extracted_slice_82 = tensor.extract_slice %1[1, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_83 = cheddar.encode %encoder, %extracted_slice_82 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_84 = cheddar.mult_plain %ctx, %ct_81, %pt_83 : (!ctx, !ct, !pt) -> !ct
    %evk_85 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_86 = cheddar.hrot %ctx, %ct_74, %evk_85, %c2 : (!ctx, !ct, !evk, index) -> !ct
    %ct_87 = cheddar.rescale %ctx, %ct_86 : (!ctx, !ct) -> !ct
    %extracted_slice_88 = tensor.extract_slice %1[2, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_89 = cheddar.encode %encoder, %extracted_slice_88 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_90 = cheddar.mult_plain %ctx, %ct_87, %pt_89 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_91 = tensor.extract_slice %inserted_slice_2[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_92 = cheddar.encode %encoder, %extracted_slice_91 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_93 = cheddar.mult_plain %ctx, %ct_75, %pt_92 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_94 = tensor.extract_slice %inserted_slice_6[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_95 = cheddar.encode %encoder, %extracted_slice_94 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_96 = cheddar.mult_plain %ctx, %ct_81, %pt_95 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_97 = tensor.extract_slice %inserted_slice_10[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_98 = cheddar.encode %encoder, %extracted_slice_97 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_99 = cheddar.mult_plain %ctx, %ct_87, %pt_98 : (!ctx, !ct, !pt) -> !ct
    %ct_100 = cheddar.add %ctx, %ct_93, %ct_96 : (!ctx, !ct, !ct) -> !ct
    %ct_101 = cheddar.add %ctx, %ct_100, %ct_99 : (!ctx, !ct, !ct) -> !ct
    %evk_102 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_103 = cheddar.hrot %ctx, %ct_101, %evk_102, %c3 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_104 = tensor.extract_slice %inserted_slice_14[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_105 = cheddar.encode %encoder, %extracted_slice_104 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_106 = cheddar.mult_plain %ctx, %ct_75, %pt_105 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_107 = tensor.extract_slice %inserted_slice_18[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_108 = cheddar.encode %encoder, %extracted_slice_107 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_109 = cheddar.mult_plain %ctx, %ct_81, %pt_108 : (!ctx, !ct, !pt) -> !ct
    %ct_110 = cheddar.add %ctx, %ct_106, %ct_109 : (!ctx, !ct, !ct) -> !ct
    %evk_111 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_112 = cheddar.hrot %ctx, %ct_110, %evk_111, %c6 : (!ctx, !ct, !evk, index) -> !ct
    %ct_113 = cheddar.add %ctx, %ct_78, %ct_84 : (!ctx, !ct, !ct) -> !ct
    %ct_114 = cheddar.add %ctx, %ct_90, %ct_103 : (!ctx, !ct, !ct) -> !ct
    %ct_115 = cheddar.add %ctx, %ct_114, %ct_112 : (!ctx, !ct, !ct) -> !ct
    %ct_116 = cheddar.add %ctx, %ct_113, %ct_115 : (!ctx, !ct, !ct) -> !ct
    %3 = tensor.empty() : tensor<1x!ct>
    %ct_117 = cheddar.rescale %ctx, %ct_116 : (!ctx, !ct) -> !ct
    %inserted = tensor.insert %ct_117 into %3[%c0] : tensor<1x!ct>
    return %inserted : tensor<1x!ct>
  }
  func.func @matvec_chain__encrypt__arg0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<8xf32>, %ui_0: !ui) -> tensor<1x!ct> attributes {client.enc_func = {func_name = "matvec_chain", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c8_i32 = arith.constant 8 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %0 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %1 = arith.remsi %arg1, %c8_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %extracted = tensor.extract %arg0[%2] : tensor<8xf32>
      %3 = arith.index_cast %arg1 : i32 to index
      %inserted = tensor.insert %extracted into %arg2[%c0, %3] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    %extracted_slice = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct = cheddar.encrypt %ui, %pt : (!ui, !pt) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @matvec_chain__decrypt__result0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct>, %ui_0: !ui) -> tensor<8xf32> attributes {client.dec_func = {func_name = "matvec_chain", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c1024_i32 = arith.constant 1024 : i32
    %c8_i32 = arith.constant 8 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<8xf32>
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %pt = cheddar.decrypt %ui, %extracted : (!ui, !ct) -> !pt
    %0 = cheddar.decode %encoder, %pt : (!encoder, !pt) -> tensor<1x1024xf32>
    %1 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<8xf32>)  : i32 {
      %2 = arith.remsi %arg1, %c8_i32 : i32
      %3 = arith.index_cast %arg1 : i32 to index
      %extracted_1 = tensor.extract %0[%c0, %3] : tensor<1x1024xf32>
      %4 = arith.index_cast %2 : i32 to index
      %inserted = tensor.insert %extracted_1 into %arg2[%4] : tensor<8xf32>
      scf.yield %inserted : tensor<8xf32>
    }
    return %1 : tensor<8xf32>
  }
}

