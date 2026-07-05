!ct = !cheddar.ciphertext
!ctx = !cheddar.context
!encoder = !cheddar.encoder
!evk = !cheddar.eval_key
!pt = !cheddar.plaintext
!ui = !cheddar.user_interface
#layout = #tensor_ext.layout<"{ [i0] -> [ct, slot] : ct = 0 and (-i0 + slot) mod 8 = 0 and 0 <= i0 <= 7 and 0 <= slot <= 1023 }">
#original_type = #tensor_ext.original_type<originalType = tensor<8xf32>, layout = #layout>
module attributes {cheddar.P = array<i64: 1073740609, 1073739937, 1073739649>, cheddar.Q = array<i64: 1073742881, 1073742721, 1073741441, 1073741857, 524353>, cheddar.logDefaultScale = 45 : i64, cheddar.logN = 4 : i64} {
  func.func private @_assign_layout_10297891714507134769() -> tensor<8x1024xf32> attributes {client.pack_func = {func_name = "matvec_identity"}} {
    %c1024_i32 = arith.constant 1024 : i32
    %c8_i32 = arith.constant 8 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<8x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %cst_0 = arith.constant dense<[[1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00]]> : tensor<8x8xf32>
    %0 = scf.for %arg0 = %c0_i32 to %c8_i32 step %c1_i32 iter_args(%arg1 = %cst) -> (tensor<8x1024xf32>)  : i32 {
      %1 = scf.for %arg2 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg3 = %arg1) -> (tensor<8x1024xf32>)  : i32 {
        %2 = arith.remsi %arg2, %c8_i32 : i32
        %3 = arith.addi %arg0, %arg2 : i32
        %4 = arith.remsi %3, %c8_i32 : i32
        %5 = arith.index_cast %2 : i32 to index
        %6 = arith.index_cast %4 : i32 to index
        %extracted = tensor.extract %cst_0[%5, %6] : tensor<8x8xf32>
        %7 = arith.index_cast %arg0 : i32 to index
        %8 = arith.index_cast %arg2 : i32 to index
        %inserted = tensor.insert %extracted into %arg3[%7, %8] : tensor<8x1024xf32>
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
    %c0 = arith.constant 0 : index
    %0 = call @_assign_layout_10297891714507134769() : () -> tensor<8x1024xf32>
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
    %pt = cheddar.encode %encoder, %extracted_slice_18 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %ct = cheddar.mult_plain %ctx, %extracted, %pt : (!ctx, !ct, !pt) -> !ct
    %evk = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_19 = cheddar.hrot %ctx, %extracted, %evk, %c1 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_20 = tensor.extract_slice %0[1, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_21 = cheddar.encode %encoder, %extracted_slice_20 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_22 = cheddar.mult_plain %ctx, %ct_19, %pt_21 : (!ctx, !ct, !pt) -> !ct
    %evk_23 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_24 = cheddar.hrot %ctx, %extracted, %evk_23, %c2 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_25 = tensor.extract_slice %0[2, 0] [1, 1024] [1, 1] : tensor<8x1024xf32> to tensor<1024xf32>
    %pt_26 = cheddar.encode %encoder, %extracted_slice_25 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_27 = cheddar.mult_plain %ctx, %ct_24, %pt_26 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_28 = tensor.extract_slice %inserted_slice_1[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_29 = cheddar.encode %encoder, %extracted_slice_28 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_30 = cheddar.mult_plain %ctx, %extracted, %pt_29 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_31 = tensor.extract_slice %inserted_slice_5[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_32 = cheddar.encode %encoder, %extracted_slice_31 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_33 = cheddar.mult_plain %ctx, %ct_19, %pt_32 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_34 = tensor.extract_slice %inserted_slice_9[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_35 = cheddar.encode %encoder, %extracted_slice_34 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_36 = cheddar.mult_plain %ctx, %ct_24, %pt_35 : (!ctx, !ct, !pt) -> !ct
    %ct_37 = cheddar.add %ctx, %ct_30, %ct_33 : (!ctx, !ct, !ct) -> !ct
    %ct_38 = cheddar.add %ctx, %ct_37, %ct_36 : (!ctx, !ct, !ct) -> !ct
    %evk_39 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_40 = cheddar.hrot %ctx, %ct_38, %evk_39, %c3 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_41 = tensor.extract_slice %inserted_slice_13[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_42 = cheddar.encode %encoder, %extracted_slice_41 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_43 = cheddar.mult_plain %ctx, %extracted, %pt_42 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_44 = tensor.extract_slice %inserted_slice_17[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_45 = cheddar.encode %encoder, %extracted_slice_44 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
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
    %pt = cheddar.encode %encoder, %extracted_slice {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
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
}

