module {
  func.func @vecsum(%4 : tensor<1x1024xf32> {secret.secret}, %6 : tensor<1x1024xf32> {secret.secret}) -> tensor<1x1024xf32> {
    %5 = tensor.extract_slice %4 [0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1x1024xf32>
    %7 = tensor.extract_slice %6 [0, 0] [1, 1024] [1, 1] : tensor<1x1024xf32> to tensor<1x1024xf32>
    %3 = arith.addf %5, %7 : tensor<1x1024xf32>
    return %3 : tensor<1x1024xf32>
  }
}
