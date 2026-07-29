!ct = !cheddar.ciphertext
!ctx = !cheddar.context
!encoder = !cheddar.encoder
!evk = !cheddar.eval_key
!pt = !cheddar.plaintext
!ui = !cheddar.user_interface
module attributes {backend.cheddar, cheddar.P = array<i64: 1152921504607338497, 1152921504608747521>, cheddar.Q = array<i64: 36028797017456641, 35184371138561, 35184372121601>, cheddar.logDefaultScale = 45 : i64, cheddar.logN = 14 : i64, scheme.actual_slot_count = 8192 : i64, scheme.requested_slot_count = 4096 : i64} {
  func.func @bert_attention(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct>, %arg1: tensor<64x4096xf32>, %arg2: tensor<64x4096xf32>) -> tensor<1x!ct> {
    %c64 = arith.constant 64 : index
    %c128 = arith.constant 128 : index
    %c192 = arith.constant 192 : index
    %c256 = arith.constant 256 : index
    %c320 = arith.constant 320 : index
    %c384 = arith.constant 384 : index
    %c448 = arith.constant 448 : index
    %c512 = arith.constant 512 : index
    %c1024 = arith.constant 1024 : index
    %c1536 = arith.constant 1536 : index
    %c2048 = arith.constant 2048 : index
    %c2560 = arith.constant 2560 : index
    %c3072 = arith.constant 3072 : index
    %c3584 = arith.constant 3584 : index
    %c0 = arith.constant 0 : index
    %extracted_slice = tensor.extract_slice %arg1[0, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt = cheddar.encode %encoder, %extracted_slice {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %ct = cheddar.mult_plain %ctx, %extracted, %pt : (!ctx, !ct, !pt) -> !ct
    %evk = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_0 = cheddar.hrot %ctx, %extracted, %evk, %c64 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_1 = tensor.extract_slice %arg1[1, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_2 = cheddar.encode %encoder, %extracted_slice_1 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_3 = cheddar.mult_plain %ctx, %ct_0, %pt_2 : (!ctx, !ct, !pt) -> !ct
    %ct_4 = cheddar.add %ctx, %ct, %ct_3 : (!ctx, !ct, !ct) -> !ct
    %evk_5 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_6 = cheddar.hrot %ctx, %extracted, %evk_5, %c128 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_7 = tensor.extract_slice %arg1[2, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_8 = cheddar.encode %encoder, %extracted_slice_7 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_9 = cheddar.mult_plain %ctx, %ct_6, %pt_8 : (!ctx, !ct, !pt) -> !ct
    %ct_10 = cheddar.add %ctx, %ct_4, %ct_9 : (!ctx, !ct, !ct) -> !ct
    %evk_11 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_12 = cheddar.hrot %ctx, %extracted, %evk_11, %c192 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_13 = tensor.extract_slice %arg1[3, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_14 = cheddar.encode %encoder, %extracted_slice_13 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_15 = cheddar.mult_plain %ctx, %ct_12, %pt_14 : (!ctx, !ct, !pt) -> !ct
    %ct_16 = cheddar.add %ctx, %ct_10, %ct_15 : (!ctx, !ct, !ct) -> !ct
    %evk_17 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_18 = cheddar.hrot %ctx, %extracted, %evk_17, %c256 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_19 = tensor.extract_slice %arg1[4, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_20 = cheddar.encode %encoder, %extracted_slice_19 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_21 = cheddar.mult_plain %ctx, %ct_18, %pt_20 : (!ctx, !ct, !pt) -> !ct
    %ct_22 = cheddar.add %ctx, %ct_16, %ct_21 : (!ctx, !ct, !ct) -> !ct
    %evk_23 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_24 = cheddar.hrot %ctx, %extracted, %evk_23, %c320 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_25 = tensor.extract_slice %arg1[5, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_26 = cheddar.encode %encoder, %extracted_slice_25 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_27 = cheddar.mult_plain %ctx, %ct_24, %pt_26 : (!ctx, !ct, !pt) -> !ct
    %ct_28 = cheddar.add %ctx, %ct_22, %ct_27 : (!ctx, !ct, !ct) -> !ct
    %evk_29 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_30 = cheddar.hrot %ctx, %extracted, %evk_29, %c384 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_31 = tensor.extract_slice %arg1[6, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_32 = cheddar.encode %encoder, %extracted_slice_31 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_33 = cheddar.mult_plain %ctx, %ct_30, %pt_32 : (!ctx, !ct, !pt) -> !ct
    %ct_34 = cheddar.add %ctx, %ct_28, %ct_33 : (!ctx, !ct, !ct) -> !ct
    %evk_35 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_36 = cheddar.hrot %ctx, %extracted, %evk_35, %c448 : (!ctx, !ct, !evk, index) -> !ct
    %extracted_slice_37 = tensor.extract_slice %arg1[7, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_38 = cheddar.encode %encoder, %extracted_slice_37 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_39 = cheddar.mult_plain %ctx, %ct_36, %pt_38 : (!ctx, !ct, !pt) -> !ct
    %ct_40 = cheddar.add %ctx, %ct_34, %ct_39 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_41 = tensor.extract_slice %arg1[8, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_42 = cheddar.encode %encoder, %extracted_slice_41 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_43 = cheddar.mult_plain %ctx, %extracted, %pt_42 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_44 = tensor.extract_slice %arg1[9, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_45 = cheddar.encode %encoder, %extracted_slice_44 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_46 = cheddar.mult_plain %ctx, %ct_0, %pt_45 : (!ctx, !ct, !pt) -> !ct
    %ct_47 = cheddar.add %ctx, %ct_43, %ct_46 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_48 = tensor.extract_slice %arg1[10, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_49 = cheddar.encode %encoder, %extracted_slice_48 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_50 = cheddar.mult_plain %ctx, %ct_6, %pt_49 : (!ctx, !ct, !pt) -> !ct
    %ct_51 = cheddar.add %ctx, %ct_47, %ct_50 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_52 = tensor.extract_slice %arg1[11, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_53 = cheddar.encode %encoder, %extracted_slice_52 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_54 = cheddar.mult_plain %ctx, %ct_12, %pt_53 : (!ctx, !ct, !pt) -> !ct
    %ct_55 = cheddar.add %ctx, %ct_51, %ct_54 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_56 = tensor.extract_slice %arg1[12, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_57 = cheddar.encode %encoder, %extracted_slice_56 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_58 = cheddar.mult_plain %ctx, %ct_18, %pt_57 : (!ctx, !ct, !pt) -> !ct
    %ct_59 = cheddar.add %ctx, %ct_55, %ct_58 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_60 = tensor.extract_slice %arg1[13, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_61 = cheddar.encode %encoder, %extracted_slice_60 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_62 = cheddar.mult_plain %ctx, %ct_24, %pt_61 : (!ctx, !ct, !pt) -> !ct
    %ct_63 = cheddar.add %ctx, %ct_59, %ct_62 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_64 = tensor.extract_slice %arg1[14, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_65 = cheddar.encode %encoder, %extracted_slice_64 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_66 = cheddar.mult_plain %ctx, %ct_30, %pt_65 : (!ctx, !ct, !pt) -> !ct
    %ct_67 = cheddar.add %ctx, %ct_63, %ct_66 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_68 = tensor.extract_slice %arg1[15, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_69 = cheddar.encode %encoder, %extracted_slice_68 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_70 = cheddar.mult_plain %ctx, %ct_36, %pt_69 : (!ctx, !ct, !pt) -> !ct
    %ct_71 = cheddar.add %ctx, %ct_67, %ct_70 : (!ctx, !ct, !ct) -> !ct
    %evk_72 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_73 = cheddar.hrot %ctx, %ct_71, %evk_72, %c512 : (!ctx, !ct, !evk, index) -> !ct
    %ct_74 = cheddar.add %ctx, %ct_40, %ct_73 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_75 = tensor.extract_slice %arg1[16, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_76 = cheddar.encode %encoder, %extracted_slice_75 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_77 = cheddar.mult_plain %ctx, %extracted, %pt_76 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_78 = tensor.extract_slice %arg1[17, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_79 = cheddar.encode %encoder, %extracted_slice_78 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_80 = cheddar.mult_plain %ctx, %ct_0, %pt_79 : (!ctx, !ct, !pt) -> !ct
    %ct_81 = cheddar.add %ctx, %ct_77, %ct_80 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_82 = tensor.extract_slice %arg1[18, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_83 = cheddar.encode %encoder, %extracted_slice_82 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_84 = cheddar.mult_plain %ctx, %ct_6, %pt_83 : (!ctx, !ct, !pt) -> !ct
    %ct_85 = cheddar.add %ctx, %ct_81, %ct_84 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_86 = tensor.extract_slice %arg1[19, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_87 = cheddar.encode %encoder, %extracted_slice_86 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_88 = cheddar.mult_plain %ctx, %ct_12, %pt_87 : (!ctx, !ct, !pt) -> !ct
    %ct_89 = cheddar.add %ctx, %ct_85, %ct_88 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_90 = tensor.extract_slice %arg1[20, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_91 = cheddar.encode %encoder, %extracted_slice_90 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_92 = cheddar.mult_plain %ctx, %ct_18, %pt_91 : (!ctx, !ct, !pt) -> !ct
    %ct_93 = cheddar.add %ctx, %ct_89, %ct_92 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_94 = tensor.extract_slice %arg1[21, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_95 = cheddar.encode %encoder, %extracted_slice_94 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_96 = cheddar.mult_plain %ctx, %ct_24, %pt_95 : (!ctx, !ct, !pt) -> !ct
    %ct_97 = cheddar.add %ctx, %ct_93, %ct_96 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_98 = tensor.extract_slice %arg1[22, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_99 = cheddar.encode %encoder, %extracted_slice_98 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_100 = cheddar.mult_plain %ctx, %ct_30, %pt_99 : (!ctx, !ct, !pt) -> !ct
    %ct_101 = cheddar.add %ctx, %ct_97, %ct_100 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_102 = tensor.extract_slice %arg1[23, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_103 = cheddar.encode %encoder, %extracted_slice_102 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_104 = cheddar.mult_plain %ctx, %ct_36, %pt_103 : (!ctx, !ct, !pt) -> !ct
    %ct_105 = cheddar.add %ctx, %ct_101, %ct_104 : (!ctx, !ct, !ct) -> !ct
    %evk_106 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_107 = cheddar.hrot %ctx, %ct_105, %evk_106, %c1024 : (!ctx, !ct, !evk, index) -> !ct
    %ct_108 = cheddar.add %ctx, %ct_74, %ct_107 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_109 = tensor.extract_slice %arg1[24, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_110 = cheddar.encode %encoder, %extracted_slice_109 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_111 = cheddar.mult_plain %ctx, %extracted, %pt_110 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_112 = tensor.extract_slice %arg1[25, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_113 = cheddar.encode %encoder, %extracted_slice_112 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_114 = cheddar.mult_plain %ctx, %ct_0, %pt_113 : (!ctx, !ct, !pt) -> !ct
    %ct_115 = cheddar.add %ctx, %ct_111, %ct_114 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_116 = tensor.extract_slice %arg1[26, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_117 = cheddar.encode %encoder, %extracted_slice_116 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_118 = cheddar.mult_plain %ctx, %ct_6, %pt_117 : (!ctx, !ct, !pt) -> !ct
    %ct_119 = cheddar.add %ctx, %ct_115, %ct_118 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_120 = tensor.extract_slice %arg1[27, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_121 = cheddar.encode %encoder, %extracted_slice_120 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_122 = cheddar.mult_plain %ctx, %ct_12, %pt_121 : (!ctx, !ct, !pt) -> !ct
    %ct_123 = cheddar.add %ctx, %ct_119, %ct_122 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_124 = tensor.extract_slice %arg1[28, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_125 = cheddar.encode %encoder, %extracted_slice_124 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_126 = cheddar.mult_plain %ctx, %ct_18, %pt_125 : (!ctx, !ct, !pt) -> !ct
    %ct_127 = cheddar.add %ctx, %ct_123, %ct_126 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_128 = tensor.extract_slice %arg1[29, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_129 = cheddar.encode %encoder, %extracted_slice_128 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_130 = cheddar.mult_plain %ctx, %ct_24, %pt_129 : (!ctx, !ct, !pt) -> !ct
    %ct_131 = cheddar.add %ctx, %ct_127, %ct_130 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_132 = tensor.extract_slice %arg1[30, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_133 = cheddar.encode %encoder, %extracted_slice_132 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_134 = cheddar.mult_plain %ctx, %ct_30, %pt_133 : (!ctx, !ct, !pt) -> !ct
    %ct_135 = cheddar.add %ctx, %ct_131, %ct_134 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_136 = tensor.extract_slice %arg1[31, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_137 = cheddar.encode %encoder, %extracted_slice_136 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_138 = cheddar.mult_plain %ctx, %ct_36, %pt_137 : (!ctx, !ct, !pt) -> !ct
    %ct_139 = cheddar.add %ctx, %ct_135, %ct_138 : (!ctx, !ct, !ct) -> !ct
    %evk_140 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_141 = cheddar.hrot %ctx, %ct_139, %evk_140, %c1536 : (!ctx, !ct, !evk, index) -> !ct
    %ct_142 = cheddar.add %ctx, %ct_108, %ct_141 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_143 = tensor.extract_slice %arg1[32, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_144 = cheddar.encode %encoder, %extracted_slice_143 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_145 = cheddar.mult_plain %ctx, %extracted, %pt_144 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_146 = tensor.extract_slice %arg1[33, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_147 = cheddar.encode %encoder, %extracted_slice_146 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_148 = cheddar.mult_plain %ctx, %ct_0, %pt_147 : (!ctx, !ct, !pt) -> !ct
    %ct_149 = cheddar.add %ctx, %ct_145, %ct_148 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_150 = tensor.extract_slice %arg1[34, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_151 = cheddar.encode %encoder, %extracted_slice_150 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_152 = cheddar.mult_plain %ctx, %ct_6, %pt_151 : (!ctx, !ct, !pt) -> !ct
    %ct_153 = cheddar.add %ctx, %ct_149, %ct_152 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_154 = tensor.extract_slice %arg1[35, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_155 = cheddar.encode %encoder, %extracted_slice_154 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_156 = cheddar.mult_plain %ctx, %ct_12, %pt_155 : (!ctx, !ct, !pt) -> !ct
    %ct_157 = cheddar.add %ctx, %ct_153, %ct_156 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_158 = tensor.extract_slice %arg1[36, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_159 = cheddar.encode %encoder, %extracted_slice_158 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_160 = cheddar.mult_plain %ctx, %ct_18, %pt_159 : (!ctx, !ct, !pt) -> !ct
    %ct_161 = cheddar.add %ctx, %ct_157, %ct_160 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_162 = tensor.extract_slice %arg1[37, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_163 = cheddar.encode %encoder, %extracted_slice_162 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_164 = cheddar.mult_plain %ctx, %ct_24, %pt_163 : (!ctx, !ct, !pt) -> !ct
    %ct_165 = cheddar.add %ctx, %ct_161, %ct_164 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_166 = tensor.extract_slice %arg1[38, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_167 = cheddar.encode %encoder, %extracted_slice_166 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_168 = cheddar.mult_plain %ctx, %ct_30, %pt_167 : (!ctx, !ct, !pt) -> !ct
    %ct_169 = cheddar.add %ctx, %ct_165, %ct_168 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_170 = tensor.extract_slice %arg1[39, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_171 = cheddar.encode %encoder, %extracted_slice_170 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_172 = cheddar.mult_plain %ctx, %ct_36, %pt_171 : (!ctx, !ct, !pt) -> !ct
    %ct_173 = cheddar.add %ctx, %ct_169, %ct_172 : (!ctx, !ct, !ct) -> !ct
    %evk_174 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_175 = cheddar.hrot %ctx, %ct_173, %evk_174, %c2048 : (!ctx, !ct, !evk, index) -> !ct
    %ct_176 = cheddar.add %ctx, %ct_142, %ct_175 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_177 = tensor.extract_slice %arg1[40, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_178 = cheddar.encode %encoder, %extracted_slice_177 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_179 = cheddar.mult_plain %ctx, %extracted, %pt_178 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_180 = tensor.extract_slice %arg1[41, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_181 = cheddar.encode %encoder, %extracted_slice_180 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_182 = cheddar.mult_plain %ctx, %ct_0, %pt_181 : (!ctx, !ct, !pt) -> !ct
    %ct_183 = cheddar.add %ctx, %ct_179, %ct_182 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_184 = tensor.extract_slice %arg1[42, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_185 = cheddar.encode %encoder, %extracted_slice_184 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_186 = cheddar.mult_plain %ctx, %ct_6, %pt_185 : (!ctx, !ct, !pt) -> !ct
    %ct_187 = cheddar.add %ctx, %ct_183, %ct_186 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_188 = tensor.extract_slice %arg1[43, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_189 = cheddar.encode %encoder, %extracted_slice_188 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_190 = cheddar.mult_plain %ctx, %ct_12, %pt_189 : (!ctx, !ct, !pt) -> !ct
    %ct_191 = cheddar.add %ctx, %ct_187, %ct_190 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_192 = tensor.extract_slice %arg1[44, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_193 = cheddar.encode %encoder, %extracted_slice_192 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_194 = cheddar.mult_plain %ctx, %ct_18, %pt_193 : (!ctx, !ct, !pt) -> !ct
    %ct_195 = cheddar.add %ctx, %ct_191, %ct_194 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_196 = tensor.extract_slice %arg1[45, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_197 = cheddar.encode %encoder, %extracted_slice_196 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_198 = cheddar.mult_plain %ctx, %ct_24, %pt_197 : (!ctx, !ct, !pt) -> !ct
    %ct_199 = cheddar.add %ctx, %ct_195, %ct_198 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_200 = tensor.extract_slice %arg1[46, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_201 = cheddar.encode %encoder, %extracted_slice_200 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_202 = cheddar.mult_plain %ctx, %ct_30, %pt_201 : (!ctx, !ct, !pt) -> !ct
    %ct_203 = cheddar.add %ctx, %ct_199, %ct_202 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_204 = tensor.extract_slice %arg1[47, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_205 = cheddar.encode %encoder, %extracted_slice_204 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_206 = cheddar.mult_plain %ctx, %ct_36, %pt_205 : (!ctx, !ct, !pt) -> !ct
    %ct_207 = cheddar.add %ctx, %ct_203, %ct_206 : (!ctx, !ct, !ct) -> !ct
    %evk_208 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_209 = cheddar.hrot %ctx, %ct_207, %evk_208, %c2560 : (!ctx, !ct, !evk, index) -> !ct
    %ct_210 = cheddar.add %ctx, %ct_176, %ct_209 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_211 = tensor.extract_slice %arg1[48, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_212 = cheddar.encode %encoder, %extracted_slice_211 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_213 = cheddar.mult_plain %ctx, %extracted, %pt_212 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_214 = tensor.extract_slice %arg1[49, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_215 = cheddar.encode %encoder, %extracted_slice_214 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_216 = cheddar.mult_plain %ctx, %ct_0, %pt_215 : (!ctx, !ct, !pt) -> !ct
    %ct_217 = cheddar.add %ctx, %ct_213, %ct_216 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_218 = tensor.extract_slice %arg1[50, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_219 = cheddar.encode %encoder, %extracted_slice_218 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_220 = cheddar.mult_plain %ctx, %ct_6, %pt_219 : (!ctx, !ct, !pt) -> !ct
    %ct_221 = cheddar.add %ctx, %ct_217, %ct_220 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_222 = tensor.extract_slice %arg1[51, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_223 = cheddar.encode %encoder, %extracted_slice_222 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_224 = cheddar.mult_plain %ctx, %ct_12, %pt_223 : (!ctx, !ct, !pt) -> !ct
    %ct_225 = cheddar.add %ctx, %ct_221, %ct_224 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_226 = tensor.extract_slice %arg1[52, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_227 = cheddar.encode %encoder, %extracted_slice_226 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_228 = cheddar.mult_plain %ctx, %ct_18, %pt_227 : (!ctx, !ct, !pt) -> !ct
    %ct_229 = cheddar.add %ctx, %ct_225, %ct_228 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_230 = tensor.extract_slice %arg1[53, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_231 = cheddar.encode %encoder, %extracted_slice_230 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_232 = cheddar.mult_plain %ctx, %ct_24, %pt_231 : (!ctx, !ct, !pt) -> !ct
    %ct_233 = cheddar.add %ctx, %ct_229, %ct_232 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_234 = tensor.extract_slice %arg1[54, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_235 = cheddar.encode %encoder, %extracted_slice_234 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_236 = cheddar.mult_plain %ctx, %ct_30, %pt_235 : (!ctx, !ct, !pt) -> !ct
    %ct_237 = cheddar.add %ctx, %ct_233, %ct_236 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_238 = tensor.extract_slice %arg1[55, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_239 = cheddar.encode %encoder, %extracted_slice_238 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_240 = cheddar.mult_plain %ctx, %ct_36, %pt_239 : (!ctx, !ct, !pt) -> !ct
    %ct_241 = cheddar.add %ctx, %ct_237, %ct_240 : (!ctx, !ct, !ct) -> !ct
    %evk_242 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_243 = cheddar.hrot %ctx, %ct_241, %evk_242, %c3072 : (!ctx, !ct, !evk, index) -> !ct
    %ct_244 = cheddar.add %ctx, %ct_210, %ct_243 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_245 = tensor.extract_slice %arg1[56, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_246 = cheddar.encode %encoder, %extracted_slice_245 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_247 = cheddar.mult_plain %ctx, %extracted, %pt_246 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_248 = tensor.extract_slice %arg1[57, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_249 = cheddar.encode %encoder, %extracted_slice_248 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_250 = cheddar.mult_plain %ctx, %ct_0, %pt_249 : (!ctx, !ct, !pt) -> !ct
    %ct_251 = cheddar.add %ctx, %ct_247, %ct_250 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_252 = tensor.extract_slice %arg1[58, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_253 = cheddar.encode %encoder, %extracted_slice_252 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_254 = cheddar.mult_plain %ctx, %ct_6, %pt_253 : (!ctx, !ct, !pt) -> !ct
    %ct_255 = cheddar.add %ctx, %ct_251, %ct_254 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_256 = tensor.extract_slice %arg1[59, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_257 = cheddar.encode %encoder, %extracted_slice_256 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_258 = cheddar.mult_plain %ctx, %ct_12, %pt_257 : (!ctx, !ct, !pt) -> !ct
    %ct_259 = cheddar.add %ctx, %ct_255, %ct_258 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_260 = tensor.extract_slice %arg1[60, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_261 = cheddar.encode %encoder, %extracted_slice_260 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_262 = cheddar.mult_plain %ctx, %ct_18, %pt_261 : (!ctx, !ct, !pt) -> !ct
    %ct_263 = cheddar.add %ctx, %ct_259, %ct_262 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_264 = tensor.extract_slice %arg1[61, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_265 = cheddar.encode %encoder, %extracted_slice_264 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_266 = cheddar.mult_plain %ctx, %ct_24, %pt_265 : (!ctx, !ct, !pt) -> !ct
    %ct_267 = cheddar.add %ctx, %ct_263, %ct_266 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_268 = tensor.extract_slice %arg1[62, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_269 = cheddar.encode %encoder, %extracted_slice_268 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_270 = cheddar.mult_plain %ctx, %ct_30, %pt_269 : (!ctx, !ct, !pt) -> !ct
    %ct_271 = cheddar.add %ctx, %ct_267, %ct_270 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_272 = tensor.extract_slice %arg1[63, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_273 = cheddar.encode %encoder, %extracted_slice_272 {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_274 = cheddar.mult_plain %ctx, %ct_36, %pt_273 : (!ctx, !ct, !pt) -> !ct
    %ct_275 = cheddar.add %ctx, %ct_271, %ct_274 : (!ctx, !ct, !ct) -> !ct
    %evk_276 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_277 = cheddar.hrot %ctx, %ct_275, %evk_276, %c3584 : (!ctx, !ct, !evk, index) -> !ct
    %ct_278 = cheddar.add %ctx, %ct_244, %ct_277 : (!ctx, !ct, !ct) -> !ct
    %ct_279 = cheddar.rescale %ctx, %ct_278 : (!ctx, !ct) -> !ct
    %extracted_slice_280 = tensor.extract_slice %arg2[0, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_281 = cheddar.encode %encoder, %extracted_slice_280 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_282 = cheddar.mult_plain %ctx, %ct_279, %pt_281 : (!ctx, !ct, !pt) -> !ct
    %evk_283 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_284 = cheddar.hrot %ctx, %ct_278, %evk_283, %c64 : (!ctx, !ct, !evk, index) -> !ct
    %ct_285 = cheddar.rescale %ctx, %ct_284 : (!ctx, !ct) -> !ct
    %extracted_slice_286 = tensor.extract_slice %arg2[1, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_287 = cheddar.encode %encoder, %extracted_slice_286 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_288 = cheddar.mult_plain %ctx, %ct_285, %pt_287 : (!ctx, !ct, !pt) -> !ct
    %ct_289 = cheddar.add %ctx, %ct_282, %ct_288 : (!ctx, !ct, !ct) -> !ct
    %evk_290 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_291 = cheddar.hrot %ctx, %ct_278, %evk_290, %c128 : (!ctx, !ct, !evk, index) -> !ct
    %ct_292 = cheddar.rescale %ctx, %ct_291 : (!ctx, !ct) -> !ct
    %extracted_slice_293 = tensor.extract_slice %arg2[2, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_294 = cheddar.encode %encoder, %extracted_slice_293 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_295 = cheddar.mult_plain %ctx, %ct_292, %pt_294 : (!ctx, !ct, !pt) -> !ct
    %ct_296 = cheddar.add %ctx, %ct_289, %ct_295 : (!ctx, !ct, !ct) -> !ct
    %evk_297 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_298 = cheddar.hrot %ctx, %ct_278, %evk_297, %c192 : (!ctx, !ct, !evk, index) -> !ct
    %ct_299 = cheddar.rescale %ctx, %ct_298 : (!ctx, !ct) -> !ct
    %extracted_slice_300 = tensor.extract_slice %arg2[3, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_301 = cheddar.encode %encoder, %extracted_slice_300 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_302 = cheddar.mult_plain %ctx, %ct_299, %pt_301 : (!ctx, !ct, !pt) -> !ct
    %ct_303 = cheddar.add %ctx, %ct_296, %ct_302 : (!ctx, !ct, !ct) -> !ct
    %evk_304 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_305 = cheddar.hrot %ctx, %ct_278, %evk_304, %c256 : (!ctx, !ct, !evk, index) -> !ct
    %ct_306 = cheddar.rescale %ctx, %ct_305 : (!ctx, !ct) -> !ct
    %extracted_slice_307 = tensor.extract_slice %arg2[4, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_308 = cheddar.encode %encoder, %extracted_slice_307 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_309 = cheddar.mult_plain %ctx, %ct_306, %pt_308 : (!ctx, !ct, !pt) -> !ct
    %ct_310 = cheddar.add %ctx, %ct_303, %ct_309 : (!ctx, !ct, !ct) -> !ct
    %evk_311 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_312 = cheddar.hrot %ctx, %ct_278, %evk_311, %c320 : (!ctx, !ct, !evk, index) -> !ct
    %ct_313 = cheddar.rescale %ctx, %ct_312 : (!ctx, !ct) -> !ct
    %extracted_slice_314 = tensor.extract_slice %arg2[5, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_315 = cheddar.encode %encoder, %extracted_slice_314 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_316 = cheddar.mult_plain %ctx, %ct_313, %pt_315 : (!ctx, !ct, !pt) -> !ct
    %ct_317 = cheddar.add %ctx, %ct_310, %ct_316 : (!ctx, !ct, !ct) -> !ct
    %evk_318 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_319 = cheddar.hrot %ctx, %ct_278, %evk_318, %c384 : (!ctx, !ct, !evk, index) -> !ct
    %ct_320 = cheddar.rescale %ctx, %ct_319 : (!ctx, !ct) -> !ct
    %extracted_slice_321 = tensor.extract_slice %arg2[6, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_322 = cheddar.encode %encoder, %extracted_slice_321 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_323 = cheddar.mult_plain %ctx, %ct_320, %pt_322 : (!ctx, !ct, !pt) -> !ct
    %ct_324 = cheddar.add %ctx, %ct_317, %ct_323 : (!ctx, !ct, !ct) -> !ct
    %evk_325 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_326 = cheddar.hrot %ctx, %ct_278, %evk_325, %c448 : (!ctx, !ct, !evk, index) -> !ct
    %ct_327 = cheddar.rescale %ctx, %ct_326 : (!ctx, !ct) -> !ct
    %extracted_slice_328 = tensor.extract_slice %arg2[7, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_329 = cheddar.encode %encoder, %extracted_slice_328 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_330 = cheddar.mult_plain %ctx, %ct_327, %pt_329 : (!ctx, !ct, !pt) -> !ct
    %ct_331 = cheddar.add %ctx, %ct_324, %ct_330 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_332 = tensor.extract_slice %arg2[8, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_333 = cheddar.encode %encoder, %extracted_slice_332 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_334 = cheddar.mult_plain %ctx, %ct_279, %pt_333 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_335 = tensor.extract_slice %arg2[9, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_336 = cheddar.encode %encoder, %extracted_slice_335 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_337 = cheddar.mult_plain %ctx, %ct_285, %pt_336 : (!ctx, !ct, !pt) -> !ct
    %ct_338 = cheddar.add %ctx, %ct_334, %ct_337 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_339 = tensor.extract_slice %arg2[10, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_340 = cheddar.encode %encoder, %extracted_slice_339 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_341 = cheddar.mult_plain %ctx, %ct_292, %pt_340 : (!ctx, !ct, !pt) -> !ct
    %ct_342 = cheddar.add %ctx, %ct_338, %ct_341 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_343 = tensor.extract_slice %arg2[11, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_344 = cheddar.encode %encoder, %extracted_slice_343 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_345 = cheddar.mult_plain %ctx, %ct_299, %pt_344 : (!ctx, !ct, !pt) -> !ct
    %ct_346 = cheddar.add %ctx, %ct_342, %ct_345 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_347 = tensor.extract_slice %arg2[12, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_348 = cheddar.encode %encoder, %extracted_slice_347 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_349 = cheddar.mult_plain %ctx, %ct_306, %pt_348 : (!ctx, !ct, !pt) -> !ct
    %ct_350 = cheddar.add %ctx, %ct_346, %ct_349 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_351 = tensor.extract_slice %arg2[13, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_352 = cheddar.encode %encoder, %extracted_slice_351 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_353 = cheddar.mult_plain %ctx, %ct_313, %pt_352 : (!ctx, !ct, !pt) -> !ct
    %ct_354 = cheddar.add %ctx, %ct_350, %ct_353 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_355 = tensor.extract_slice %arg2[14, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_356 = cheddar.encode %encoder, %extracted_slice_355 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_357 = cheddar.mult_plain %ctx, %ct_320, %pt_356 : (!ctx, !ct, !pt) -> !ct
    %ct_358 = cheddar.add %ctx, %ct_354, %ct_357 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_359 = tensor.extract_slice %arg2[15, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_360 = cheddar.encode %encoder, %extracted_slice_359 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_361 = cheddar.mult_plain %ctx, %ct_327, %pt_360 : (!ctx, !ct, !pt) -> !ct
    %ct_362 = cheddar.add %ctx, %ct_358, %ct_361 : (!ctx, !ct, !ct) -> !ct
    %evk_363 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_364 = cheddar.hrot %ctx, %ct_362, %evk_363, %c512 : (!ctx, !ct, !evk, index) -> !ct
    %ct_365 = cheddar.add %ctx, %ct_331, %ct_364 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_366 = tensor.extract_slice %arg2[16, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_367 = cheddar.encode %encoder, %extracted_slice_366 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_368 = cheddar.mult_plain %ctx, %ct_279, %pt_367 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_369 = tensor.extract_slice %arg2[17, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_370 = cheddar.encode %encoder, %extracted_slice_369 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_371 = cheddar.mult_plain %ctx, %ct_285, %pt_370 : (!ctx, !ct, !pt) -> !ct
    %ct_372 = cheddar.add %ctx, %ct_368, %ct_371 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_373 = tensor.extract_slice %arg2[18, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_374 = cheddar.encode %encoder, %extracted_slice_373 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_375 = cheddar.mult_plain %ctx, %ct_292, %pt_374 : (!ctx, !ct, !pt) -> !ct
    %ct_376 = cheddar.add %ctx, %ct_372, %ct_375 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_377 = tensor.extract_slice %arg2[19, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_378 = cheddar.encode %encoder, %extracted_slice_377 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_379 = cheddar.mult_plain %ctx, %ct_299, %pt_378 : (!ctx, !ct, !pt) -> !ct
    %ct_380 = cheddar.add %ctx, %ct_376, %ct_379 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_381 = tensor.extract_slice %arg2[20, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_382 = cheddar.encode %encoder, %extracted_slice_381 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_383 = cheddar.mult_plain %ctx, %ct_306, %pt_382 : (!ctx, !ct, !pt) -> !ct
    %ct_384 = cheddar.add %ctx, %ct_380, %ct_383 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_385 = tensor.extract_slice %arg2[21, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_386 = cheddar.encode %encoder, %extracted_slice_385 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_387 = cheddar.mult_plain %ctx, %ct_313, %pt_386 : (!ctx, !ct, !pt) -> !ct
    %ct_388 = cheddar.add %ctx, %ct_384, %ct_387 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_389 = tensor.extract_slice %arg2[22, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_390 = cheddar.encode %encoder, %extracted_slice_389 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_391 = cheddar.mult_plain %ctx, %ct_320, %pt_390 : (!ctx, !ct, !pt) -> !ct
    %ct_392 = cheddar.add %ctx, %ct_388, %ct_391 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_393 = tensor.extract_slice %arg2[23, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_394 = cheddar.encode %encoder, %extracted_slice_393 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_395 = cheddar.mult_plain %ctx, %ct_327, %pt_394 : (!ctx, !ct, !pt) -> !ct
    %ct_396 = cheddar.add %ctx, %ct_392, %ct_395 : (!ctx, !ct, !ct) -> !ct
    %evk_397 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_398 = cheddar.hrot %ctx, %ct_396, %evk_397, %c1024 : (!ctx, !ct, !evk, index) -> !ct
    %ct_399 = cheddar.add %ctx, %ct_365, %ct_398 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_400 = tensor.extract_slice %arg2[24, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_401 = cheddar.encode %encoder, %extracted_slice_400 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_402 = cheddar.mult_plain %ctx, %ct_279, %pt_401 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_403 = tensor.extract_slice %arg2[25, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_404 = cheddar.encode %encoder, %extracted_slice_403 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_405 = cheddar.mult_plain %ctx, %ct_285, %pt_404 : (!ctx, !ct, !pt) -> !ct
    %ct_406 = cheddar.add %ctx, %ct_402, %ct_405 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_407 = tensor.extract_slice %arg2[26, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_408 = cheddar.encode %encoder, %extracted_slice_407 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_409 = cheddar.mult_plain %ctx, %ct_292, %pt_408 : (!ctx, !ct, !pt) -> !ct
    %ct_410 = cheddar.add %ctx, %ct_406, %ct_409 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_411 = tensor.extract_slice %arg2[27, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_412 = cheddar.encode %encoder, %extracted_slice_411 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_413 = cheddar.mult_plain %ctx, %ct_299, %pt_412 : (!ctx, !ct, !pt) -> !ct
    %ct_414 = cheddar.add %ctx, %ct_410, %ct_413 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_415 = tensor.extract_slice %arg2[28, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_416 = cheddar.encode %encoder, %extracted_slice_415 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_417 = cheddar.mult_plain %ctx, %ct_306, %pt_416 : (!ctx, !ct, !pt) -> !ct
    %ct_418 = cheddar.add %ctx, %ct_414, %ct_417 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_419 = tensor.extract_slice %arg2[29, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_420 = cheddar.encode %encoder, %extracted_slice_419 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_421 = cheddar.mult_plain %ctx, %ct_313, %pt_420 : (!ctx, !ct, !pt) -> !ct
    %ct_422 = cheddar.add %ctx, %ct_418, %ct_421 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_423 = tensor.extract_slice %arg2[30, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_424 = cheddar.encode %encoder, %extracted_slice_423 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_425 = cheddar.mult_plain %ctx, %ct_320, %pt_424 : (!ctx, !ct, !pt) -> !ct
    %ct_426 = cheddar.add %ctx, %ct_422, %ct_425 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_427 = tensor.extract_slice %arg2[31, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_428 = cheddar.encode %encoder, %extracted_slice_427 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_429 = cheddar.mult_plain %ctx, %ct_327, %pt_428 : (!ctx, !ct, !pt) -> !ct
    %ct_430 = cheddar.add %ctx, %ct_426, %ct_429 : (!ctx, !ct, !ct) -> !ct
    %evk_431 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_432 = cheddar.hrot %ctx, %ct_430, %evk_431, %c1536 : (!ctx, !ct, !evk, index) -> !ct
    %ct_433 = cheddar.add %ctx, %ct_399, %ct_432 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_434 = tensor.extract_slice %arg2[32, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_435 = cheddar.encode %encoder, %extracted_slice_434 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_436 = cheddar.mult_plain %ctx, %ct_279, %pt_435 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_437 = tensor.extract_slice %arg2[33, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_438 = cheddar.encode %encoder, %extracted_slice_437 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_439 = cheddar.mult_plain %ctx, %ct_285, %pt_438 : (!ctx, !ct, !pt) -> !ct
    %ct_440 = cheddar.add %ctx, %ct_436, %ct_439 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_441 = tensor.extract_slice %arg2[34, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_442 = cheddar.encode %encoder, %extracted_slice_441 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_443 = cheddar.mult_plain %ctx, %ct_292, %pt_442 : (!ctx, !ct, !pt) -> !ct
    %ct_444 = cheddar.add %ctx, %ct_440, %ct_443 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_445 = tensor.extract_slice %arg2[35, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_446 = cheddar.encode %encoder, %extracted_slice_445 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_447 = cheddar.mult_plain %ctx, %ct_299, %pt_446 : (!ctx, !ct, !pt) -> !ct
    %ct_448 = cheddar.add %ctx, %ct_444, %ct_447 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_449 = tensor.extract_slice %arg2[36, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_450 = cheddar.encode %encoder, %extracted_slice_449 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_451 = cheddar.mult_plain %ctx, %ct_306, %pt_450 : (!ctx, !ct, !pt) -> !ct
    %ct_452 = cheddar.add %ctx, %ct_448, %ct_451 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_453 = tensor.extract_slice %arg2[37, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_454 = cheddar.encode %encoder, %extracted_slice_453 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_455 = cheddar.mult_plain %ctx, %ct_313, %pt_454 : (!ctx, !ct, !pt) -> !ct
    %ct_456 = cheddar.add %ctx, %ct_452, %ct_455 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_457 = tensor.extract_slice %arg2[38, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_458 = cheddar.encode %encoder, %extracted_slice_457 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_459 = cheddar.mult_plain %ctx, %ct_320, %pt_458 : (!ctx, !ct, !pt) -> !ct
    %ct_460 = cheddar.add %ctx, %ct_456, %ct_459 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_461 = tensor.extract_slice %arg2[39, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_462 = cheddar.encode %encoder, %extracted_slice_461 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_463 = cheddar.mult_plain %ctx, %ct_327, %pt_462 : (!ctx, !ct, !pt) -> !ct
    %ct_464 = cheddar.add %ctx, %ct_460, %ct_463 : (!ctx, !ct, !ct) -> !ct
    %evk_465 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_466 = cheddar.hrot %ctx, %ct_464, %evk_465, %c2048 : (!ctx, !ct, !evk, index) -> !ct
    %ct_467 = cheddar.add %ctx, %ct_433, %ct_466 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_468 = tensor.extract_slice %arg2[40, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_469 = cheddar.encode %encoder, %extracted_slice_468 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_470 = cheddar.mult_plain %ctx, %ct_279, %pt_469 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_471 = tensor.extract_slice %arg2[41, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_472 = cheddar.encode %encoder, %extracted_slice_471 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_473 = cheddar.mult_plain %ctx, %ct_285, %pt_472 : (!ctx, !ct, !pt) -> !ct
    %ct_474 = cheddar.add %ctx, %ct_470, %ct_473 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_475 = tensor.extract_slice %arg2[42, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_476 = cheddar.encode %encoder, %extracted_slice_475 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_477 = cheddar.mult_plain %ctx, %ct_292, %pt_476 : (!ctx, !ct, !pt) -> !ct
    %ct_478 = cheddar.add %ctx, %ct_474, %ct_477 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_479 = tensor.extract_slice %arg2[43, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_480 = cheddar.encode %encoder, %extracted_slice_479 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_481 = cheddar.mult_plain %ctx, %ct_299, %pt_480 : (!ctx, !ct, !pt) -> !ct
    %ct_482 = cheddar.add %ctx, %ct_478, %ct_481 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_483 = tensor.extract_slice %arg2[44, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_484 = cheddar.encode %encoder, %extracted_slice_483 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_485 = cheddar.mult_plain %ctx, %ct_306, %pt_484 : (!ctx, !ct, !pt) -> !ct
    %ct_486 = cheddar.add %ctx, %ct_482, %ct_485 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_487 = tensor.extract_slice %arg2[45, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_488 = cheddar.encode %encoder, %extracted_slice_487 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_489 = cheddar.mult_plain %ctx, %ct_313, %pt_488 : (!ctx, !ct, !pt) -> !ct
    %ct_490 = cheddar.add %ctx, %ct_486, %ct_489 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_491 = tensor.extract_slice %arg2[46, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_492 = cheddar.encode %encoder, %extracted_slice_491 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_493 = cheddar.mult_plain %ctx, %ct_320, %pt_492 : (!ctx, !ct, !pt) -> !ct
    %ct_494 = cheddar.add %ctx, %ct_490, %ct_493 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_495 = tensor.extract_slice %arg2[47, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_496 = cheddar.encode %encoder, %extracted_slice_495 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_497 = cheddar.mult_plain %ctx, %ct_327, %pt_496 : (!ctx, !ct, !pt) -> !ct
    %ct_498 = cheddar.add %ctx, %ct_494, %ct_497 : (!ctx, !ct, !ct) -> !ct
    %evk_499 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_500 = cheddar.hrot %ctx, %ct_498, %evk_499, %c2560 : (!ctx, !ct, !evk, index) -> !ct
    %ct_501 = cheddar.add %ctx, %ct_467, %ct_500 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_502 = tensor.extract_slice %arg2[48, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_503 = cheddar.encode %encoder, %extracted_slice_502 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_504 = cheddar.mult_plain %ctx, %ct_279, %pt_503 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_505 = tensor.extract_slice %arg2[49, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_506 = cheddar.encode %encoder, %extracted_slice_505 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_507 = cheddar.mult_plain %ctx, %ct_285, %pt_506 : (!ctx, !ct, !pt) -> !ct
    %ct_508 = cheddar.add %ctx, %ct_504, %ct_507 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_509 = tensor.extract_slice %arg2[50, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_510 = cheddar.encode %encoder, %extracted_slice_509 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_511 = cheddar.mult_plain %ctx, %ct_292, %pt_510 : (!ctx, !ct, !pt) -> !ct
    %ct_512 = cheddar.add %ctx, %ct_508, %ct_511 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_513 = tensor.extract_slice %arg2[51, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_514 = cheddar.encode %encoder, %extracted_slice_513 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_515 = cheddar.mult_plain %ctx, %ct_299, %pt_514 : (!ctx, !ct, !pt) -> !ct
    %ct_516 = cheddar.add %ctx, %ct_512, %ct_515 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_517 = tensor.extract_slice %arg2[52, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_518 = cheddar.encode %encoder, %extracted_slice_517 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_519 = cheddar.mult_plain %ctx, %ct_306, %pt_518 : (!ctx, !ct, !pt) -> !ct
    %ct_520 = cheddar.add %ctx, %ct_516, %ct_519 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_521 = tensor.extract_slice %arg2[53, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_522 = cheddar.encode %encoder, %extracted_slice_521 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_523 = cheddar.mult_plain %ctx, %ct_313, %pt_522 : (!ctx, !ct, !pt) -> !ct
    %ct_524 = cheddar.add %ctx, %ct_520, %ct_523 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_525 = tensor.extract_slice %arg2[54, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_526 = cheddar.encode %encoder, %extracted_slice_525 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_527 = cheddar.mult_plain %ctx, %ct_320, %pt_526 : (!ctx, !ct, !pt) -> !ct
    %ct_528 = cheddar.add %ctx, %ct_524, %ct_527 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_529 = tensor.extract_slice %arg2[55, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_530 = cheddar.encode %encoder, %extracted_slice_529 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_531 = cheddar.mult_plain %ctx, %ct_327, %pt_530 : (!ctx, !ct, !pt) -> !ct
    %ct_532 = cheddar.add %ctx, %ct_528, %ct_531 : (!ctx, !ct, !ct) -> !ct
    %evk_533 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_534 = cheddar.hrot %ctx, %ct_532, %evk_533, %c3072 : (!ctx, !ct, !evk, index) -> !ct
    %ct_535 = cheddar.add %ctx, %ct_501, %ct_534 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_536 = tensor.extract_slice %arg2[56, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_537 = cheddar.encode %encoder, %extracted_slice_536 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_538 = cheddar.mult_plain %ctx, %ct_279, %pt_537 : (!ctx, !ct, !pt) -> !ct
    %extracted_slice_539 = tensor.extract_slice %arg2[57, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_540 = cheddar.encode %encoder, %extracted_slice_539 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_541 = cheddar.mult_plain %ctx, %ct_285, %pt_540 : (!ctx, !ct, !pt) -> !ct
    %ct_542 = cheddar.add %ctx, %ct_538, %ct_541 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_543 = tensor.extract_slice %arg2[58, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_544 = cheddar.encode %encoder, %extracted_slice_543 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_545 = cheddar.mult_plain %ctx, %ct_292, %pt_544 : (!ctx, !ct, !pt) -> !ct
    %ct_546 = cheddar.add %ctx, %ct_542, %ct_545 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_547 = tensor.extract_slice %arg2[59, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_548 = cheddar.encode %encoder, %extracted_slice_547 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_549 = cheddar.mult_plain %ctx, %ct_299, %pt_548 : (!ctx, !ct, !pt) -> !ct
    %ct_550 = cheddar.add %ctx, %ct_546, %ct_549 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_551 = tensor.extract_slice %arg2[60, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_552 = cheddar.encode %encoder, %extracted_slice_551 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_553 = cheddar.mult_plain %ctx, %ct_306, %pt_552 : (!ctx, !ct, !pt) -> !ct
    %ct_554 = cheddar.add %ctx, %ct_550, %ct_553 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_555 = tensor.extract_slice %arg2[61, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_556 = cheddar.encode %encoder, %extracted_slice_555 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_557 = cheddar.mult_plain %ctx, %ct_313, %pt_556 : (!ctx, !ct, !pt) -> !ct
    %ct_558 = cheddar.add %ctx, %ct_554, %ct_557 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_559 = tensor.extract_slice %arg2[62, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_560 = cheddar.encode %encoder, %extracted_slice_559 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_561 = cheddar.mult_plain %ctx, %ct_320, %pt_560 : (!ctx, !ct, !pt) -> !ct
    %ct_562 = cheddar.add %ctx, %ct_558, %ct_561 : (!ctx, !ct, !ct) -> !ct
    %extracted_slice_563 = tensor.extract_slice %arg2[63, 0] [1, 4096] [1, 1] : tensor<64x4096xf32> to tensor<4096xf32>
    %pt_564 = cheddar.encode %encoder, %extracted_slice_563 {level = 1 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct_565 = cheddar.mult_plain %ctx, %ct_327, %pt_564 : (!ctx, !ct, !pt) -> !ct
    %ct_566 = cheddar.add %ctx, %ct_562, %ct_565 : (!ctx, !ct, !ct) -> !ct
    %evk_567 = cheddar.get_rot_key %ui {distance = -1 : i64} : (!ui) -> !evk
    %ct_568 = cheddar.hrot %ctx, %ct_566, %evk_567, %c3584 : (!ctx, !ct, !evk, index) -> !ct
    %ct_569 = cheddar.add %ctx, %ct_535, %ct_568 : (!ctx, !ct, !ct) -> !ct
    %0 = tensor.empty() : tensor<1x!ct>
    %ct_570 = cheddar.rescale %ctx, %ct_569 : (!ctx, !ct) -> !ct
    %inserted = tensor.insert %ct_570 into %0[%c0] : tensor<1x!ct>
    return %inserted : tensor<1x!ct>
  }
  func.func @bert_attention__encrypt__arg0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x4096xf32>, %ui_0: !ui) -> tensor<1x!ct> attributes {client.enc_func = {func_name = "bert_attention", index = 0 : i64}} {
    %extracted_slice = tensor.extract_slice %arg0[0, 0] [1, 4096] [1, 1] : tensor<1x4096xf32> to tensor<4096xf32>
    %pt = cheddar.encode %encoder, %extracted_slice {level = 2 : i64, scale = 45 : i64} : (!encoder, tensor<4096xf32>) -> !pt
    %ct = cheddar.encrypt %ui, %pt : (!ui, !pt) -> !ct
    %from_elements = tensor.from_elements %ct : tensor<1x!ct>
    return %from_elements : tensor<1x!ct>
  }
  func.func @bert_attention__decrypt__result0(%ctx: !ctx, %encoder: !encoder, %ui: !ui, %arg0: tensor<1x!ct>, %ui_0: !ui) -> tensor<1x4096xf32> attributes {client.dec_func = {func_name = "bert_attention", index = 0 : i64}} {
    %c0 = arith.constant 0 : index
    %extracted = tensor.extract %arg0[%c0] : tensor<1x!ct>
    %pt = cheddar.decrypt %ui, %extracted : (!ui, !ct) -> !pt
    %0 = cheddar.decode %encoder, %pt : (!encoder, !pt) -> tensor<1x4096xf32>
    return %0 : tensor<1x4096xf32>
  }
}

