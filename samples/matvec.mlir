!ct = !cheddar.ciphertext
!ctx = !cheddar.context
!encoder = !cheddar.encoder
!evk = !cheddar.eval_key
!pt = !cheddar.plaintext
!ui = !cheddar.user_interface
#layout = #tensor_ext.layout<"{ [i0] -> [ct, slot] : ct = 0 and (-i0 + slot) mod 16 = 0 and 0 <= i0 <= 15 and 0 <= slot <= 1023 }">
#original_type = #tensor_ext.original_type<originalType = tensor<16xf32>, layout = #layout>
module attributes {cheddar.P = array<i64: 1152921504606994433>, cheddar.Q = array<i64: 36028797018652673, 35184372121601>, cheddar.logDefaultScale = 45 : i64, cheddar.logN = 13 : i64, scheme.actual_slot_count = 4096 : i64, scheme.requested_slot_count = 1024 : i64} {
  func.func private @_assign_layout_16910372757803757633() -> tensor<1x1024xf32> attributes {client.pack_func = {func_name = "matvec"}} {
    %c0 = arith.constant 0 : index
    %c16_i32 = arith.constant 16 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %cst_0 = arith.constant dense<[-0.45141533, -0.0277900472, 0.311195374, 0.18254894, -0.258809537, 0.497506738, 0.00115649134, -0.194445714, 0.158549473, 0.000000e+00, 0.310650676, -0.214976981, -0.023661999, -0.392960966, 6.472870e-01, 0.831665277]> : tensor<16xf32>
    %0 = scf.for %arg0 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg1 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %1 = arith.remsi %arg0, %c16_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %extracted = tensor.extract %cst_0[%2] : tensor<16xf32>
      %3 = arith.index_cast %arg0 : i32 to index
      %inserted = tensor.insert %extracted into %arg1[%c0, %3] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    return %0 : tensor<1x1024xf32>
  }
  func.func private @_assign_layout_1535064765322952764() -> tensor<16x1024xf32> attributes {client.pack_func = {func_name = "matvec"}} {
    %c1024_i32 = arith.constant 1024 : i32
    %c16_i32 = arith.constant 16 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<16x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %cst_0 = arith.constant dense<"0x5036CB3DED693F3E647E8E3F1C7029BFBEE1923F83F258BE77DDA1BFD7EDB93C309239C0842D833EB0C3163FD1DB2ABF5D971B3F1091853EED900CBE19464BBFE147C3BE584F72BF27116D3DAA05383F32109FBFC956703FADE2DCBEEE8F443E3EF9903F90A07CBF7803133FCDB2E83EDC29103FCC190A3FECD986BFAE4E853DE4A9393E3CB9E83EBA00FA3D0DBFF0BE79DF193F4E00073F29DA10BE1C9693BD12360BBFEEFCFBBD051EBDBEAE500E3F598190BF369C0D3F65AB74BF022E55BE47C021BEBD0E8D3EDDD4C93EBF82CB3F726237BFE1645E3FA4569FBDB0863BBFD15A1FC097BE063E94A451BFE4AA0B3F0C8726BEA2AD41BE1A15F63E1CDB073F40F376BF4D87BDBEA96AA03E8D9F843DBF6FFB3F9C8203BF24B92ABE7F70C5BE733F6C3F7CE7DA3E1F83C13F0284113EF339193F1B19E13CA1F5FA3E6E31C9BEA1078D3E5A0439BF1FD4A7BE3640A63F55B69FBF6D8B66BD4DF072BFC166A93E8D4BDF3FBF4AEABD9FD976BFB809763ECD4C10BFC88265BF6B2BABBEC202C5BE8D53EB3DBE94AABE3C3297BD75BF7FBE1EFEF83E1936893FAE8AA13EAF6CACBD615C2DC0473F593FE32D25BFDF71D0BD382D6CBE2DD392BD9C4FECB84BF853BED6E0493ECDCA91BE387D02BFF615053D7D4EB63F0042113E4C661B3FBF5F023F83868D3F497814BD911CAB3F4BC424BE7A020C3F6509A73E95E499BEEE54DB3EEFFC3CBF695FA93EA695923E1937CB3F553A37BF6EC745BF3DCF823EEC98153FC2D49C3F8523E03D07ED413D13E9853E016DA2BED73A6F3E2D0268BEEBC9613EBEB947BE870B93BE3402CB3EC68B41BE50F054BF161EB23E4FDC1F3EB562A1BDD9A115C0CCA8D6BDD65AFDBED757033F590DF63EC4280CBF8EA7EABE74C317BE4597B5BB576920BF6A4E0F3EEC66B9BE4072EE3F570AFE3D961D7C3E5FEE0ABD1EC09EBFEA77253E532AA23F15A656BE1923163DC24284BE374FFD3DB9F2A3BED185903E6294083F8D0700BFD998223FACE7A1BF79CC633C1039C43D8FB21CBF36CD1B3F99D43DBE85E451BF522F40BE8B94383D76727CBEADBB19BF755B6F3F9B9C1BBE4C08633D195E3E3E90944FBD511F9DBF8E44723F665C36BFCE54193F9ABE19C0ECACB53E88925B3EA19AA4BE1AD4EABEC5DE023FC759C83F37CE383FEB0713BDCBACC6BDCA2E0EBF28F39CBCE8A4C23F8D844E3F2791AF3DF31C79BE5129963F74A657BF3D09BD3DF1F9953EFDA50DBB79B7B8BE4A69D73EF01E2F3D23B418BFD8C9243F6CAA17BE21AE853F3C11793FBE51FABE47B452BE2A0A763E4CA4BDBF7AE739BE6C0AC33F0FDF2E3DBDA0BABC6E8E23BF37B836BF989532BE66736C3EABF141BE63FE853E26F7803F68822ABF7BFA0F3F34128B3EA3B655BFAB2F1C3ECC272F3F2B3A19BF198BD9BEA75C0DBF12C739BDE5F4E1BE1C591EBE"> : tensor<16x16xf32>
    %0 = scf.for %arg0 = %c0_i32 to %c16_i32 step %c1_i32 iter_args(%arg1 = %cst) -> (tensor<16x1024xf32>)  : i32 {
      %1 = scf.for %arg2 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg3 = %arg1) -> (tensor<16x1024xf32>)  : i32 {
        %2 = arith.remsi %arg2, %c16_i32 : i32
        %3 = arith.addi %arg0, %arg2 : i32
        %4 = arith.remsi %3, %c16_i32 : i32
        %5 = arith.index_cast %2 : i32 to index
        %6 = arith.index_cast %4 : i32 to index
        %extracted = tensor.extract %cst_0[%5, %6] : tensor<16x16xf32>
        %7 = arith.index_cast %arg0 : i32 to index
        %8 = arith.index_cast %arg2 : i32 to index
        %inserted = tensor.insert %extracted into %arg3[%7, %8] : tensor<16x1024xf32>
        scf.yield %inserted : tensor<16x1024xf32>
      }
      scf.yield %1 : tensor<16x1024xf32>
    }
    return %0 : tensor<16x1024xf32>
  }
  func.func @matvec(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct> {tensor_ext.original_type = #original_type}) -> (tensor<1x!ct> {tensor_ext.original_type = #original_type}) {
    %c12 = arith.constant 12 : index
    %c8 = arith.constant 8 : index
    %c4 = arith.constant 4 : index
    %c3 = arith.constant 3 : index
    %c2 = arith.constant 2 : index
    %c1 = arith.constant 1 : index
    %c0 = arith.constant 0 : index
    %0 = call @_assign_layout_1535064765322952764() : () -> tensor<16x1024xf32>
    %1 = call @_assign_layout_16910372757803757633() : () -> tensor<1x1024xf32>
    %extracted_slice = tensor.extract_slice %0[4, 0] [1, 1020] [1, 1] : tensor<16x1024xf32> to tensor<1x1020xf32>
    %extracted_slice_0 = tensor.extract_slice %0[4, 1020] [1, 4] [1, 1] : tensor<16x1024xf32> to tensor<1x4xf32>
    %2 = tensor.empty() : tensor<1x1024xf32>
    %inserted_slice = tensor.insert_slice %extracted_slice into %2[0, 4] [1, 1020] [1, 1] : tensor<1x1020xf32> into tensor<1x1024xf32>
    %inserted_slice_1 = tensor.insert_slice %extracted_slice_0 into %inserted_slice[0, 0] [1, 4] [1, 1] : tensor<1x4xf32> into tensor<1x1024xf32>
    %extracted_slice_2 = tensor.extract_slice %0[5, 0] [1, 1020] [1, 1] : tensor<16x1024xf32> to tensor<1x1020xf32>
    %extracted_slice_3 = tensor.extract_slice %0[5, 1020] [1, 4] [1, 1] : tensor<16x1024xf32> to tensor<1x4xf32>
    %inserted_slice_4 = tensor.insert_slice %extracted_slice_2 into %2[0, 4] [1, 1020] [1, 1] : tensor<1x1020xf32> into tensor<1x1024xf32>
    %inserted_slice_5 = tensor.insert_slice %extracted_slice_3 into %inserted_slice_4[0, 0] [1, 4] [1, 1] : tensor<1x4xf32> into tensor<1x1024xf32>
    %extracted_slice_6 = tensor.extract_slice %0[6, 0] [1, 1020] [1, 1] : tensor<16x1024xf32> to tensor<1x1020xf32>
    %extracted_slice_7 = tensor.extract_slice %0[6, 1020] [1, 4] [1, 1] : tensor<16x1024xf32> to tensor<1x4xf32>
    %inserted_slice_8 = tensor.insert_slice %extracted_slice_6 into %2[0, 4] [1, 1020] [1, 1] : tensor<1x1020xf32> into tensor<1x1024xf32>
    %inserted_slice_9 = tensor.insert_slice %extracted_slice_7 into %inserted_slice_8[0, 0] [1, 4] [1, 1] : tensor<1x4xf32> into tensor<1x1024xf32>
    %extracted_slice_10 = tensor.extract_slice %0[7, 0] [1, 1020] [1, 1] : tensor<16x1024xf32> to tensor<1x1020xf32>
    %extracted_slice_11 = tensor.extract_slice %0[7, 1020] [1, 4] [1, 1] : tensor<16x1024xf32> to tensor<1x4xf32>
    %inserted_slice_12 = tensor.insert_slice %extracted_slice_10 into %2[0, 4] [1, 1020] [1, 1] : tensor<1x1020xf32> into tensor<1x1024xf32>
    %inserted_slice_13 = tensor.insert_slice %extracted_slice_11 into %inserted_slice_12[0, 0] [1, 4] [1, 1] : tensor<1x4xf32> into tensor<1x1024xf32>
    %extracted_slice_14 = tensor.extract_slice %0[8, 0] [1, 1016] [1, 1] : tensor<16x1024xf32> to tensor<1x1016xf32>
    %extracted_slice_15 = tensor.extract_slice %0[8, 1016] [1, 8] [1, 1] : tensor<16x1024xf32> to tensor<1x8xf32>
    %inserted_slice_16 = tensor.insert_slice %extracted_slice_14 into %2[0, 8] [1, 1016] [1, 1] : tensor<1x1016xf32> into tensor<1x1024xf32>
    %inserted_slice_17 = tensor.insert_slice %extracted_slice_15 into %inserted_slice_16[0, 0] [1, 8] [1, 1] : tensor<1x8xf32> into tensor<1x1024xf32>
    %extracted_slice_18 = tensor.extract_slice %0[9, 0] [1, 1016] [1, 1] : tensor<16x1024xf32> to tensor<1x1016xf32>
    %extracted_slice_19 = tensor.extract_slice %0[9, 1016] [1, 8] [1, 1] : tensor<16x1024xf32> to tensor<1x8xf32>
    %inserted_slice_20 = tensor.insert_slice %extracted_slice_18 into %2[0, 8] [1, 1016] [1, 1] : tensor<1x1016xf32> into tensor<1x1024xf32>
    %inserted_slice_21 = tensor.insert_slice %extracted_slice_19 into %inserted_slice_20[0, 0] [1, 8] [1, 1] : tensor<1x8xf32> into tensor<1x1024xf32>
    %extracted_slice_22 = tensor.extract_slice %0[10, 0] [1, 1016] [1, 1] : tensor<16x1024xf32> to tensor<1x1016xf32>
    %extracted_slice_23 = tensor.extract_slice %0[10, 1016] [1, 8] [1, 1] : tensor<16x1024xf32> to tensor<1x8xf32>
    %inserted_slice_24 = tensor.insert_slice %extracted_slice_22 into %2[0, 8] [1, 1016] [1, 1] : tensor<1x1016xf32> into tensor<1x1024xf32>
    %inserted_slice_25 = tensor.insert_slice %extracted_slice_23 into %inserted_slice_24[0, 0] [1, 8] [1, 1] : tensor<1x8xf32> into tensor<1x1024xf32>
    %extracted_slice_26 = tensor.extract_slice %0[11, 0] [1, 1016] [1, 1] : tensor<16x1024xf32> to tensor<1x1016xf32>
    %extracted_slice_27 = tensor.extract_slice %0[11, 1016] [1, 8] [1, 1] : tensor<16x1024xf32> to tensor<1x8xf32>
    %inserted_slice_28 = tensor.insert_slice %extracted_slice_26 into %2[0, 8] [1, 1016] [1, 1] : tensor<1x1016xf32> into tensor<1x1024xf32>
    %inserted_slice_29 = tensor.insert_slice %extracted_slice_27 into %inserted_slice_28[0, 0] [1, 8] [1, 1] : tensor<1x8xf32> into tensor<1x1024xf32>
    %extracted_slice_30 = tensor.extract_slice %0[12, 0] [1, 1012] [1, 1] : tensor<16x1024xf32> to tensor<1x1012xf32>
    %extracted_slice_31 = tensor.extract_slice %0[12, 1012] [1, 12] [1, 1] : tensor<16x1024xf32> to tensor<1x12xf32>
    %inserted_slice_32 = tensor.insert_slice %extracted_slice_30 into %2[0, 12] [1, 1012] [1, 1] : tensor<1x1012xf32> into tensor<1x1024xf32>
    %inserted_slice_33 = tensor.insert_slice %extracted_slice_31 into %inserted_slice_32[0, 0] [1, 12] [1, 1] : tensor<1x12xf32> into tensor<1x1024xf32>
    %extracted_slice_34 = tensor.extract_slice %0[13, 0] [1, 1012] [1, 1] : tensor<16x1024xf32> to tensor<1x1012xf32>
    %extracted_slice_35 = tensor.extract_slice %0[13, 1012] [1, 12] [1, 1] : tensor<16x1024xf32> to tensor<1x12xf32>
    %inserted_slice_36 = tensor.insert_slice %extracted_slice_34 into %2[0, 12] [1, 1012] [1, 1] : tensor<1x1012xf32> into tensor<1x1024xf32>
    %inserted_slice_37 = tensor.insert_slice %extracted_slice_35 into %inserted_slice_36[0, 0] [1, 12] [1, 1] : tensor<1x12xf32> into tensor<1x1024xf32>
    %extracted_slice_38 = tensor.extract_slice %0[14, 0] [1, 1012] [1, 1] : tensor<16x1024xf32> to tensor<1x1012xf32>
    %extracted_slice_39 = tensor.extract_slice %0[14, 1012] [1, 12] [1, 1] : tensor<16x1024xf32> to tensor<1x12xf32>
    %inserted_slice_40 = tensor.insert_slice %extracted_slice_38 into %2[0, 12] [1, 1012] [1, 1] : tensor<1x1012xf32> into tensor<1x1024xf32>
    %inserted_slice_41 = tensor.insert_slice %extracted_slice_39 into %inserted_slice_40[0, 0] [1, 12] [1, 1] : tensor<1x12xf32> into tensor<1x1024xf32>
    %extracted_slice_42 = tensor.extract_slice %0[15, 0] [1, 1012] [1, 1] : tensor<16x1024xf32> to tensor<1x1012xf32>
    %extracted_slice_43 = tensor.extract_slice %0[15, 1012] [1, 12] [1, 1] : tensor<16x1024xf32> to tensor<1x12xf32>
    %inserted_slice_44 = tensor.insert_slice %extracted_slice_42 into %2[0, 12] [1, 1012] [1, 1] : tensor<1x1012xf32> into tensor<1x1024xf32>
    %inserted_slice_45 = tensor.insert_slice %extracted_slice_43 into %inserted_slice_44[0, 0] [1, 12] [1, 1] : tensor<1x12xf32> into tensor<1x1024xf32>
    %extracted_slice_46 = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<16x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice_46 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %ct = cheddar.mult_plain %ctx, %extracted, %pt : (!ctx, !ct, !pt) -> !ct
    %evk = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_47 = cheddar.hrot %ctx, %extracted, %evk, %c1 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_48 = tensor.extract_slice %0[1, 0] [1, 1024] [1, 1] : tensor<16x1024xf32> to tensor<1024xf32>
    %pt_49 = cheddar.encode %encoder, %extracted_slice_48 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_50 = cheddar.mult_plain %ctx, %ct_47, %pt_49 : (!ctx, !ct, !pt) -> !ct
    %evk_51 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_52 = cheddar.hrot %ctx, %extracted, %evk_51, %c2 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_53 = tensor.extract_slice %0[2, 0] [1, 1024] [1, 1] : tensor<16x1024xf32> to tensor<1024xf32>
    %pt_54 = cheddar.encode %encoder, %extracted_slice_53 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_55 = cheddar.mult_plain %ctx, %ct_52, %pt_54 : (!ctx, !ct, !pt) -> !ct
    %evk_56 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_57 = cheddar.hrot %ctx, %extracted, %evk_56, %c3 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_58 = tensor.extract_slice %0[3, 0] [1, 1024] [1, 1] : tensor<16x1024xf32> to tensor<1024xf32>
    %pt_59 = cheddar.encode %encoder, %extracted_slice_58 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_60 = cheddar.mult_plain %ctx, %ct_57, %pt_59 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_61 = tensor.extract_slice %inserted_slice_1[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_62 = cheddar.encode %encoder, %extracted_slice_61 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_63 = cheddar.mult_plain %ctx, %extracted, %pt_62 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_64 = tensor.extract_slice %inserted_slice_5[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_65 = cheddar.encode %encoder, %extracted_slice_64 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_66 = cheddar.mult_plain %ctx, %ct_47, %pt_65 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_67 = tensor.extract_slice %inserted_slice_9[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_68 = cheddar.encode %encoder, %extracted_slice_67 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_69 = cheddar.mult_plain %ctx, %ct_52, %pt_68 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_70 = tensor.extract_slice %inserted_slice_13[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_71 = cheddar.encode %encoder, %extracted_slice_70 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_72 = cheddar.mult_plain %ctx, %ct_57, %pt_71 : (!ctx, !ct, !pt) -> !ct
    %ct_73 = cheddar.add %ctx, %ct_63, %ct_66 : (!ctx, !ct, !ct) -> !ct
    %ct_74 = cheddar.add %ctx, %ct_69, %ct_72 : (!ctx, !ct, !ct) -> !ct
    %ct_75 = cheddar.add %ctx, %ct_73, %ct_74 : (!ctx, !ct, !ct) -> !ct
    %evk_76 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_77 = cheddar.hrot %ctx, %ct_75, %evk_76, %c4 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_78 = tensor.extract_slice %inserted_slice_17[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_79 = cheddar.encode %encoder, %extracted_slice_78 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_80 = cheddar.mult_plain %ctx, %extracted, %pt_79 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_81 = tensor.extract_slice %inserted_slice_21[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_82 = cheddar.encode %encoder, %extracted_slice_81 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_83 = cheddar.mult_plain %ctx, %ct_47, %pt_82 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_84 = tensor.extract_slice %inserted_slice_25[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_85 = cheddar.encode %encoder, %extracted_slice_84 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_86 = cheddar.mult_plain %ctx, %ct_52, %pt_85 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_87 = tensor.extract_slice %inserted_slice_29[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_88 = cheddar.encode %encoder, %extracted_slice_87 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_89 = cheddar.mult_plain %ctx, %ct_57, %pt_88 : (!ctx, !ct, !pt) -> !ct
    %ct_90 = cheddar.add %ctx, %ct_80, %ct_83 : (!ctx, !ct, !ct) -> !ct
    %ct_91 = cheddar.add %ctx, %ct_86, %ct_89 : (!ctx, !ct, !ct) -> !ct
    %ct_92 = cheddar.add %ctx, %ct_90, %ct_91 : (!ctx, !ct, !ct) -> !ct
    %evk_93 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_94 = cheddar.hrot %ctx, %ct_92, %evk_93, %c8 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_95 = tensor.extract_slice %inserted_slice_33[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_96 = cheddar.encode %encoder, %extracted_slice_95 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_97 = cheddar.mult_plain %ctx, %extracted, %pt_96 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_98 = tensor.extract_slice %inserted_slice_37[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_99 = cheddar.encode %encoder, %extracted_slice_98 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_100 = cheddar.mult_plain %ctx, %ct_47, %pt_99 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_101 = tensor.extract_slice %inserted_slice_41[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_102 = cheddar.encode %encoder, %extracted_slice_101 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_103 = cheddar.mult_plain %ctx, %ct_52, %pt_102 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_104 = tensor.extract_slice %inserted_slice_45[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_105 = cheddar.encode %encoder, %extracted_slice_104 {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_106 = cheddar.mult_plain %ctx, %ct_57, %pt_105 : (!ctx, !ct, !pt) -> !ct
    %ct_107 = cheddar.add %ctx, %ct_97, %ct_100 : (!ctx, !ct, !ct) -> !ct
    %ct_108 = cheddar.add %ctx, %ct_103, %ct_106 : (!ctx, !ct, !ct) -> !ct
    %ct_109 = cheddar.add %ctx, %ct_107, %ct_108 : (!ctx, !ct, !ct) -> !ct
    %evk_110 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_111 = cheddar.hrot %ctx, %ct_109, %evk_110, %c12 : (!ctx, !ct, !evk, index) -> !ct
    %ct_112 = cheddar.add %ctx, %ct, %ct_50 : (!ctx, !ct, !ct) -> !ct
    %ct_113 = cheddar.add %ctx, %ct_55, %ct_60 : (!ctx, !ct, !ct) -> !ct
    %ct_114 = cheddar.add %ctx, %ct_112, %ct_113 : (!ctx, !ct, !ct) -> !ct
    %ct_115 = cheddar.add %ctx, %ct_77, %ct_94 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_116 = tensor.extract_slice %1[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt_117 = cheddar.encode %encoder, %extracted_slice_116 {level = 0 : i64, scale = 90 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct_118 = cheddar.add_plain %ctx, %ct_111, %pt_117 : (!ctx, !ct, !pt) -> !ct
    %ct_119 = cheddar.add %ctx, %ct_115, %ct_118 : (!ctx, !ct, !ct) -> !ct
    %ct_120 = cheddar.add %ctx, %ct_114, %ct_119 : (!ctx, !ct, !ct) -> !ct
    %3 = tensor.empty() : tensor<1x!ct>
    %ct_121 = cheddar.rescale %ctx, %ct_120 : (!ctx, !ct) -> !ct
    %inserted = tensor.insert %ct_121 into %3[%c0] : tensor<1x!ct>
    return %inserted : tensor<1x!ct>
  }
  func.func @matvec__encrypt__arg0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<16xf32>, %ui_0: !ui) -> tensor<1x!ct> attributes {client.enc_func = {func_name = "matvec", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c16_i32 = arith.constant 16 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<1x1024xf32>
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %0 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<1x1024xf32>)  : i32 {
      %1 = arith.remsi %arg1, %c16_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %extracted = tensor.extract %arg0[%2] : tensor<16xf32>
      %3 = arith.index_cast %arg1 : i32 to index
      %inserted = tensor.insert %extracted into %arg2[%c0, %3] : tensor<1x1024xf32>
      scf.yield %inserted : tensor<1x1024xf32>
    }
    %extracted_slice = tensor.extract_slice %0[0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1024xf32>
    %pt = cheddar.encode %encoder, %extracted_slice {level = 0 : i64, scale = 45 : i64} : (!encoder, tensor<1024xf32>) -> !pt
    %ct = cheddar.encrypt %ui, %pt : (!ui, !pt) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @matvec__decrypt__result0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct>, %ui_0: !ui) -> tensor<16xf32> attributes {client.dec_func = {func_name = "matvec", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %c1024_i32 = arith.constant 1024 : i32
    %c16_i32 = arith.constant 16 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant dense<0.000000e+00> : tensor<16xf32>
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %pt = cheddar.decrypt %ui, %extracted : (!ui, !ct) -> !pt
    %0 = cheddar.decode %encoder, %pt : (!encoder, !pt) -> tensor<1x1024xf32>
    %1 = scf.for %arg1 = %c0_i32 to %c1024_i32 step %c1_i32 iter_args(%arg2 = %cst) -> (tensor<16xf32>)  : i32 {
      %2 = arith.remsi %arg1, %c16_i32 : i32
      %3 = arith.index_cast %arg1 : i32 to index
      %extracted_1 = tensor.extract %0[%c0, %3] : tensor<1x1024xf32>
      %4 = arith.index_cast %2 : i32 to index
      %inserted = tensor.insert %extracted_1 into %arg2[%4] : tensor<16xf32>
      scf.yield %inserted : tensor<16xf32>
    }
    return %1 : tensor<16xf32>
  }
}

