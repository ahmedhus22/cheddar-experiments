#map = affine_map<(d0) -> (d0)>
module {
  func.func @vecsum(%arg0: tensor<1024xf32>, %arg1: tensor<1024xf32>) -> tensor<1024xf32> {
    %0 = tensor.empty() : tensor<1024xf32>
    %1 = linalg.generic {indexing_maps = [#map, #map, #map], iterator_types = ["parallel"]} ins(%arg0, %arg1 : tensor<1024xf32>, tensor<1024xf32>) outs(%0 : tensor<1024xf32>) {
    ^bb0(%in: f32, %in_0: f32, %out: f32):
      %2 = arith.addf %in, %in_0 : f32
      linalg.yield %2 : f32
    } -> tensor<1024xf32>
    return %1 : tensor<1024xf32>
  }
}
