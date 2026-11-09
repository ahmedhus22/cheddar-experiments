#map = affine_map<(d0, d1) -> (d0, d1)>
#map1 = affine_map<(d0, d1) -> (d1)>
#map2 = affine_map<(d0, d1) -> (d0)>
module {
  func.func @matvec_64(%arg0: tensor<64x64xf32>, %arg1: tensor<64xf32>) -> tensor<64xf32> {
    %cst = arith.constant 0.000000e+00 : f32
    %0 = tensor.empty() : tensor<64x64xf32>
    %1 = linalg.generic {indexing_maps = [#map, #map1, #map], iterator_types = ["parallel", "parallel"]} ins(%arg0, %arg1 : tensor<64x64xf32>, tensor<64xf32>) outs(%0 : tensor<64x64xf32>) {
    ^bb0(%in: f32, %in_0: f32, %out: f32):
      %5 = arith.mulf %in, %in_0 : f32
      linalg.yield %5 : f32
    } -> tensor<64x64xf32>
    %2 = tensor.empty() : tensor<64xf32>
    %3 = linalg.fill ins(%cst : f32) outs(%2 : tensor<64xf32>) -> tensor<64xf32>
    %4 = linalg.generic {indexing_maps = [#map, #map2], iterator_types = ["parallel", "reduction"]} ins(%1 : tensor<64x64xf32>) outs(%3 : tensor<64xf32>) {
    ^bb0(%in: f32, %out: f32):
      %5 = arith.addf %in, %out : f32
      linalg.yield %5 : f32
    } -> tensor<64xf32>
    return %4 : tensor<64xf32>
  }
}
