
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "openfhe/pke/openfhe.h"  // from @openfhe

using namespace lbcrypto;
using CiphertextT = Ciphertext<DCRTPoly>;
using ConstCiphertextT = ConstCiphertext<DCRTPoly>;
using CCParamsT = CCParams<CryptoContextCKKSRNS>;
using CryptoContextT = CryptoContext<DCRTPoly>;
using EvalKeyT = EvalKey<DCRTPoly>;
using PlaintextT = Plaintext;
using PrivateKeyT = PrivateKey<DCRTPoly>;
using PublicKeyT = PublicKey<DCRTPoly>;

// Assumes a little-endian target.
template <typename T>
std::vector<T> load_resource(const std::string& path, size_t size) {
  std::ifstream file(path, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    std::abort();
  }
  std::vector<T> data(size);
  file.read(reinterpret_cast<char*>(data.data()), size * sizeof(T));
  if (!file) {
    std::cerr << "Failed to read expected number of bytes from: " << path << std::endl;
    std::abort();
  }
  return data;
}

// Specialization for bool to avoid std::vector<bool>::data() compilation failure.
template <>
inline std::vector<bool> load_resource<bool>(const std::string& path, size_t size) {
  std::ifstream file(path, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    std::abort();
  }
  std::vector<char> temp(size);
  file.read(temp.data(), size);
  if (!file) {
    std::cerr << "Failed to read expected number of bytes from: " << path << std::endl;
    std::abort();
  }
  std::vector<bool> data(size);
  for (size_t i = 0; i < size; ++i) {
    data[i] = temp[i] != 0;
  }
  return data;
}

std::vector<float> _assign_layout_11331293625880117383(std::vector<float> v0) {
  [[maybe_unused]] int32_t v1 = 14;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(14336, 0);
  [[maybe_unused]] int32_t v5 = 2;
  [[maybe_unused]] int32_t v6 = -8;
  [[maybe_unused]] int32_t v7 = 7;
  [[maybe_unused]] int32_t v8 = 8;
  [[maybe_unused]] int32_t v9 = 223;
  [[maybe_unused]] int32_t v10 = 112;
  [[maybe_unused]] int32_t v11 = 16;
  [[maybe_unused]] int32_t v12 = 1024;
  [[maybe_unused]] int32_t v13 = 111;
  std::vector<float> v14 = v4;
  for (auto v15 = 0; v15 < 14; v15 += 1) {
    for (auto v18 = 0; v18 < 16; v18 += 1) {
      int32_t v20 = v15 + v18;
      int32_t v21 = v20 + v2;
      int32_t v22 = (v21 / v5) - ((v21 % v5 != 0) && ((v21 < 0) != (v5 < 0)));
      int32_t v23 = v22 * v5;
      int32_t v24 = v21 - v23;
      int32_t v25 = v2 - v24;
      for (auto v27 = v25; v27 < 14; v27 += 2) {
        int32_t v29 = v15 * v6;
        int32_t v30 = v18 * v7;
        int32_t v31 = v29 + v30;
        int32_t v32 = v27 * v8;
        int32_t v33 = v31 - v32;
        int32_t v34 = v33 + v9;
        int32_t v35 = (v34 / v10) - ((v34 % v10 != 0) && ((v34 < 0) != (v10 < 0)));
        int32_t v36 = v35 * v10;
        int32_t v37 = v34 - v36;
        int32_t v38 = v13 - v37;
        for (auto v40 = v38; v40 < 1024; v40 += 112) {
          size_t v42 = static_cast<size_t>(v15);
          size_t v43 = static_cast<size_t>(v18);
          float v44 = v0[v43 + 16 * (v42)];
          size_t v45 = static_cast<size_t>(v27);
          size_t v46 = static_cast<size_t>(v40);
          v14[v46 + 1024 * (v45)] = v44;
        }
      }
    }
  }
  return v14;
}
std::vector<Plaintext> matmul_pt__preprocessing(CryptoContextT cc, std::vector<float> v0) {
  [[maybe_unused]] size_t v1 = 0;
  [[maybe_unused]] size_t v2 = 1;
  [[maybe_unused]] size_t v3 = 2;
  [[maybe_unused]] size_t v4 = 3;
  [[maybe_unused]] size_t v5 = 4;
  [[maybe_unused]] size_t v6 = 5;
  [[maybe_unused]] size_t v7 = 6;
  [[maybe_unused]] size_t v8 = 7;
  [[maybe_unused]] size_t v9 = 8;
  [[maybe_unused]] size_t v10 = 9;
  [[maybe_unused]] size_t v11 = 10;
  [[maybe_unused]] size_t v12 = 11;
  [[maybe_unused]] size_t v13 = 12;
  [[maybe_unused]] size_t v14 = 13;
  [[maybe_unused]] size_t v15 = 14;
  [[maybe_unused]] size_t v16 = 15;
  std::vector<double> v17 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<double> v18 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::vector<Plaintext> v19(16);
  const auto& v20 = _assign_layout_11331293625880117383(v0);
  std::vector<float> v21(1 * 1024);
  for (int64_t v21_i0 = 0; v21_i0 < 1; ++v21_i0) {
    for (int64_t v21_i1 = 0; v21_i1 < 1024; ++v21_i1) {
      v21[v21_i1 + 1024 * (v21_i0)] = v20[0 + v21_i1 * 1 + 1024 * (4 + v21_i0 * 1)];
    }
  }
  std::vector<float> v22(1 * 1024);
  for (int64_t v22_i0 = 0; v22_i0 < 1; ++v22_i0) {
    for (int64_t v22_i1 = 0; v22_i1 < 1024; ++v22_i1) {
      v22[v22_i1 + 1024 * (v22_i0)] = v20[0 + v22_i1 * 1 + 1024 * (5 + v22_i0 * 1)];
    }
  }
  std::vector<float> v23(1 * 1024);
  for (int64_t v23_i0 = 0; v23_i0 < 1; ++v23_i0) {
    for (int64_t v23_i1 = 0; v23_i1 < 1024; ++v23_i1) {
      v23[v23_i1 + 1024 * (v23_i0)] = v20[0 + v23_i1 * 1 + 1024 * (6 + v23_i0 * 1)];
    }
  }
  std::vector<float> v24(1 * 1024);
  for (int64_t v24_i0 = 0; v24_i0 < 1; ++v24_i0) {
    for (int64_t v24_i1 = 0; v24_i1 < 1024; ++v24_i1) {
      v24[v24_i1 + 1024 * (v24_i0)] = v20[0 + v24_i1 * 1 + 1024 * (7 + v24_i0 * 1)];
    }
  }
  std::vector<float> v25(1 * 1024);
  for (int64_t v25_i0 = 0; v25_i0 < 1; ++v25_i0) {
    for (int64_t v25_i1 = 0; v25_i1 < 1024; ++v25_i1) {
      v25[v25_i1 + 1024 * (v25_i0)] = v20[0 + v25_i1 * 1 + 1024 * (8 + v25_i0 * 1)];
    }
  }
  std::vector<float> v26(1 * 1024);
  for (int64_t v26_i0 = 0; v26_i0 < 1; ++v26_i0) {
    for (int64_t v26_i1 = 0; v26_i1 < 1024; ++v26_i1) {
      v26[v26_i1 + 1024 * (v26_i0)] = v20[0 + v26_i1 * 1 + 1024 * (9 + v26_i0 * 1)];
    }
  }
  std::vector<float> v27(1 * 1024);
  for (int64_t v27_i0 = 0; v27_i0 < 1; ++v27_i0) {
    for (int64_t v27_i1 = 0; v27_i1 < 1024; ++v27_i1) {
      v27[v27_i1 + 1024 * (v27_i0)] = v20[0 + v27_i1 * 1 + 1024 * (10 + v27_i0 * 1)];
    }
  }
  std::vector<float> v28(1 * 1024);
  for (int64_t v28_i0 = 0; v28_i0 < 1; ++v28_i0) {
    for (int64_t v28_i1 = 0; v28_i1 < 1024; ++v28_i1) {
      v28[v28_i1 + 1024 * (v28_i0)] = v20[0 + v28_i1 * 1 + 1024 * (11 + v28_i0 * 1)];
    }
  }
  std::vector<float> v29(1 * 1024);
  for (int64_t v29_i0 = 0; v29_i0 < 1; ++v29_i0) {
    for (int64_t v29_i1 = 0; v29_i1 < 1024; ++v29_i1) {
      v29[v29_i1 + 1024 * (v29_i0)] = v20[0 + v29_i1 * 1 + 1024 * (12 + v29_i0 * 1)];
    }
  }
  std::vector<float> v30(1 * 1024);
  for (int64_t v30_i0 = 0; v30_i0 < 1; ++v30_i0) {
    for (int64_t v30_i1 = 0; v30_i1 < 1024; ++v30_i1) {
      v30[v30_i1 + 1024 * (v30_i0)] = v20[0 + v30_i1 * 1 + 1024 * (13 + v30_i0 * 1)];
    }
  }
  std::vector<float> v31(1 * 972);
  for (int64_t v31_i0 = 0; v31_i0 < 1; ++v31_i0) {
    for (int64_t v31_i1 = 0; v31_i1 < 972; ++v31_i1) {
      v31[v31_i1 + 972 * (v31_i0)] = v20[0 + v31_i1 * 1 + 1024 * (4 + v31_i0 * 1)];
    }
  }
  std::vector<float> v32(1 * 52);
  for (int64_t v32_i0 = 0; v32_i0 < 1; ++v32_i0) {
    for (int64_t v32_i1 = 0; v32_i1 < 52; ++v32_i1) {
      v32[v32_i1 + 52 * (v32_i0)] = v20[972 + v32_i1 * 1 + 1024 * (4 + v32_i0 * 1)];
    }
  }
  std::vector<float> v33(v21);
  int64_t v31_0 = 0;
  for (int64_t v21_0 = 0; v21_0 < 0 + 1 * 1; v21_0 += 1) {
    int64_t v31_1 = 0;
    for (int64_t v21_1 = 52; v21_1 < 52 + 972 * 1; v21_1 += 1) {
      v33[v21_1 + 1024 * (v21_0)] = v31[v31_1 + 972 * (v31_0)];
      v31_1 += 1;
    }
    v31_0 += 1;
  }
  std::vector<float> v34(v33);
  int64_t v32_0 = 0;
  for (int64_t v33_0 = 0; v33_0 < 0 + 1 * 1; v33_0 += 1) {
    int64_t v32_1 = 0;
    for (int64_t v33_1 = 0; v33_1 < 0 + 52 * 1; v33_1 += 1) {
      v34[v33_1 + 1024 * (v33_0)] = v32[v32_1 + 52 * (v32_0)];
      v32_1 += 1;
    }
    v32_0 += 1;
  }
  std::vector<float> v35(1 * 972);
  for (int64_t v35_i0 = 0; v35_i0 < 1; ++v35_i0) {
    for (int64_t v35_i1 = 0; v35_i1 < 972; ++v35_i1) {
      v35[v35_i1 + 972 * (v35_i0)] = v20[0 + v35_i1 * 1 + 1024 * (5 + v35_i0 * 1)];
    }
  }
  std::vector<float> v36(1 * 52);
  for (int64_t v36_i0 = 0; v36_i0 < 1; ++v36_i0) {
    for (int64_t v36_i1 = 0; v36_i1 < 52; ++v36_i1) {
      v36[v36_i1 + 52 * (v36_i0)] = v20[972 + v36_i1 * 1 + 1024 * (5 + v36_i0 * 1)];
    }
  }
  std::vector<float> v37(v22);
  int64_t v35_0 = 0;
  for (int64_t v22_0 = 0; v22_0 < 0 + 1 * 1; v22_0 += 1) {
    int64_t v35_1 = 0;
    for (int64_t v22_1 = 52; v22_1 < 52 + 972 * 1; v22_1 += 1) {
      v37[v22_1 + 1024 * (v22_0)] = v35[v35_1 + 972 * (v35_0)];
      v35_1 += 1;
    }
    v35_0 += 1;
  }
  std::vector<float> v38(v37);
  int64_t v36_0 = 0;
  for (int64_t v37_0 = 0; v37_0 < 0 + 1 * 1; v37_0 += 1) {
    int64_t v36_1 = 0;
    for (int64_t v37_1 = 0; v37_1 < 0 + 52 * 1; v37_1 += 1) {
      v38[v37_1 + 1024 * (v37_0)] = v36[v36_1 + 52 * (v36_0)];
      v36_1 += 1;
    }
    v36_0 += 1;
  }
  std::vector<float> v39(1 * 972);
  for (int64_t v39_i0 = 0; v39_i0 < 1; ++v39_i0) {
    for (int64_t v39_i1 = 0; v39_i1 < 972; ++v39_i1) {
      v39[v39_i1 + 972 * (v39_i0)] = v20[0 + v39_i1 * 1 + 1024 * (6 + v39_i0 * 1)];
    }
  }
  std::vector<float> v40(1 * 52);
  for (int64_t v40_i0 = 0; v40_i0 < 1; ++v40_i0) {
    for (int64_t v40_i1 = 0; v40_i1 < 52; ++v40_i1) {
      v40[v40_i1 + 52 * (v40_i0)] = v20[972 + v40_i1 * 1 + 1024 * (6 + v40_i0 * 1)];
    }
  }
  std::vector<float> v41(v23);
  int64_t v39_0 = 0;
  for (int64_t v23_0 = 0; v23_0 < 0 + 1 * 1; v23_0 += 1) {
    int64_t v39_1 = 0;
    for (int64_t v23_1 = 52; v23_1 < 52 + 972 * 1; v23_1 += 1) {
      v41[v23_1 + 1024 * (v23_0)] = v39[v39_1 + 972 * (v39_0)];
      v39_1 += 1;
    }
    v39_0 += 1;
  }
  std::vector<float> v42(v41);
  int64_t v40_0 = 0;
  for (int64_t v41_0 = 0; v41_0 < 0 + 1 * 1; v41_0 += 1) {
    int64_t v40_1 = 0;
    for (int64_t v41_1 = 0; v41_1 < 0 + 52 * 1; v41_1 += 1) {
      v42[v41_1 + 1024 * (v41_0)] = v40[v40_1 + 52 * (v40_0)];
      v40_1 += 1;
    }
    v40_0 += 1;
  }
  std::vector<float> v43(1 * 972);
  for (int64_t v43_i0 = 0; v43_i0 < 1; ++v43_i0) {
    for (int64_t v43_i1 = 0; v43_i1 < 972; ++v43_i1) {
      v43[v43_i1 + 972 * (v43_i0)] = v20[0 + v43_i1 * 1 + 1024 * (7 + v43_i0 * 1)];
    }
  }
  std::vector<float> v44(1 * 52);
  for (int64_t v44_i0 = 0; v44_i0 < 1; ++v44_i0) {
    for (int64_t v44_i1 = 0; v44_i1 < 52; ++v44_i1) {
      v44[v44_i1 + 52 * (v44_i0)] = v20[972 + v44_i1 * 1 + 1024 * (7 + v44_i0 * 1)];
    }
  }
  std::vector<float> v45(v24);
  int64_t v43_0 = 0;
  for (int64_t v24_0 = 0; v24_0 < 0 + 1 * 1; v24_0 += 1) {
    int64_t v43_1 = 0;
    for (int64_t v24_1 = 52; v24_1 < 52 + 972 * 1; v24_1 += 1) {
      v45[v24_1 + 1024 * (v24_0)] = v43[v43_1 + 972 * (v43_0)];
      v43_1 += 1;
    }
    v43_0 += 1;
  }
  std::vector<float> v46(v45);
  int64_t v44_0 = 0;
  for (int64_t v45_0 = 0; v45_0 < 0 + 1 * 1; v45_0 += 1) {
    int64_t v44_1 = 0;
    for (int64_t v45_1 = 0; v45_1 < 0 + 52 * 1; v45_1 += 1) {
      v46[v45_1 + 1024 * (v45_0)] = v44[v44_1 + 52 * (v44_0)];
      v44_1 += 1;
    }
    v44_0 += 1;
  }
  std::vector<float> v47(1 * 920);
  for (int64_t v47_i0 = 0; v47_i0 < 1; ++v47_i0) {
    for (int64_t v47_i1 = 0; v47_i1 < 920; ++v47_i1) {
      v47[v47_i1 + 920 * (v47_i0)] = v20[0 + v47_i1 * 1 + 1024 * (8 + v47_i0 * 1)];
    }
  }
  std::vector<float> v48(1 * 104);
  for (int64_t v48_i0 = 0; v48_i0 < 1; ++v48_i0) {
    for (int64_t v48_i1 = 0; v48_i1 < 104; ++v48_i1) {
      v48[v48_i1 + 104 * (v48_i0)] = v20[920 + v48_i1 * 1 + 1024 * (8 + v48_i0 * 1)];
    }
  }
  std::vector<float> v49(v25);
  int64_t v47_0 = 0;
  for (int64_t v25_0 = 0; v25_0 < 0 + 1 * 1; v25_0 += 1) {
    int64_t v47_1 = 0;
    for (int64_t v25_1 = 104; v25_1 < 104 + 920 * 1; v25_1 += 1) {
      v49[v25_1 + 1024 * (v25_0)] = v47[v47_1 + 920 * (v47_0)];
      v47_1 += 1;
    }
    v47_0 += 1;
  }
  std::vector<float> v50(v49);
  int64_t v48_0 = 0;
  for (int64_t v49_0 = 0; v49_0 < 0 + 1 * 1; v49_0 += 1) {
    int64_t v48_1 = 0;
    for (int64_t v49_1 = 0; v49_1 < 0 + 104 * 1; v49_1 += 1) {
      v50[v49_1 + 1024 * (v49_0)] = v48[v48_1 + 104 * (v48_0)];
      v48_1 += 1;
    }
    v48_0 += 1;
  }
  std::vector<float> v51(1 * 920);
  for (int64_t v51_i0 = 0; v51_i0 < 1; ++v51_i0) {
    for (int64_t v51_i1 = 0; v51_i1 < 920; ++v51_i1) {
      v51[v51_i1 + 920 * (v51_i0)] = v20[0 + v51_i1 * 1 + 1024 * (9 + v51_i0 * 1)];
    }
  }
  std::vector<float> v52(1 * 104);
  for (int64_t v52_i0 = 0; v52_i0 < 1; ++v52_i0) {
    for (int64_t v52_i1 = 0; v52_i1 < 104; ++v52_i1) {
      v52[v52_i1 + 104 * (v52_i0)] = v20[920 + v52_i1 * 1 + 1024 * (9 + v52_i0 * 1)];
    }
  }
  std::vector<float> v53(v26);
  int64_t v51_0 = 0;
  for (int64_t v26_0 = 0; v26_0 < 0 + 1 * 1; v26_0 += 1) {
    int64_t v51_1 = 0;
    for (int64_t v26_1 = 104; v26_1 < 104 + 920 * 1; v26_1 += 1) {
      v53[v26_1 + 1024 * (v26_0)] = v51[v51_1 + 920 * (v51_0)];
      v51_1 += 1;
    }
    v51_0 += 1;
  }
  std::vector<float> v54(v53);
  int64_t v52_0 = 0;
  for (int64_t v53_0 = 0; v53_0 < 0 + 1 * 1; v53_0 += 1) {
    int64_t v52_1 = 0;
    for (int64_t v53_1 = 0; v53_1 < 0 + 104 * 1; v53_1 += 1) {
      v54[v53_1 + 1024 * (v53_0)] = v52[v52_1 + 104 * (v52_0)];
      v52_1 += 1;
    }
    v52_0 += 1;
  }
  std::vector<float> v55(1 * 920);
  for (int64_t v55_i0 = 0; v55_i0 < 1; ++v55_i0) {
    for (int64_t v55_i1 = 0; v55_i1 < 920; ++v55_i1) {
      v55[v55_i1 + 920 * (v55_i0)] = v20[0 + v55_i1 * 1 + 1024 * (10 + v55_i0 * 1)];
    }
  }
  std::vector<float> v56(1 * 104);
  for (int64_t v56_i0 = 0; v56_i0 < 1; ++v56_i0) {
    for (int64_t v56_i1 = 0; v56_i1 < 104; ++v56_i1) {
      v56[v56_i1 + 104 * (v56_i0)] = v20[920 + v56_i1 * 1 + 1024 * (10 + v56_i0 * 1)];
    }
  }
  std::vector<float> v57(v27);
  int64_t v55_0 = 0;
  for (int64_t v27_0 = 0; v27_0 < 0 + 1 * 1; v27_0 += 1) {
    int64_t v55_1 = 0;
    for (int64_t v27_1 = 104; v27_1 < 104 + 920 * 1; v27_1 += 1) {
      v57[v27_1 + 1024 * (v27_0)] = v55[v55_1 + 920 * (v55_0)];
      v55_1 += 1;
    }
    v55_0 += 1;
  }
  std::vector<float> v58(v57);
  int64_t v56_0 = 0;
  for (int64_t v57_0 = 0; v57_0 < 0 + 1 * 1; v57_0 += 1) {
    int64_t v56_1 = 0;
    for (int64_t v57_1 = 0; v57_1 < 0 + 104 * 1; v57_1 += 1) {
      v58[v57_1 + 1024 * (v57_0)] = v56[v56_1 + 104 * (v56_0)];
      v56_1 += 1;
    }
    v56_0 += 1;
  }
  std::vector<float> v59(1 * 920);
  for (int64_t v59_i0 = 0; v59_i0 < 1; ++v59_i0) {
    for (int64_t v59_i1 = 0; v59_i1 < 920; ++v59_i1) {
      v59[v59_i1 + 920 * (v59_i0)] = v20[0 + v59_i1 * 1 + 1024 * (11 + v59_i0 * 1)];
    }
  }
  std::vector<float> v60(1 * 104);
  for (int64_t v60_i0 = 0; v60_i0 < 1; ++v60_i0) {
    for (int64_t v60_i1 = 0; v60_i1 < 104; ++v60_i1) {
      v60[v60_i1 + 104 * (v60_i0)] = v20[920 + v60_i1 * 1 + 1024 * (11 + v60_i0 * 1)];
    }
  }
  std::vector<float> v61(v28);
  int64_t v59_0 = 0;
  for (int64_t v28_0 = 0; v28_0 < 0 + 1 * 1; v28_0 += 1) {
    int64_t v59_1 = 0;
    for (int64_t v28_1 = 104; v28_1 < 104 + 920 * 1; v28_1 += 1) {
      v61[v28_1 + 1024 * (v28_0)] = v59[v59_1 + 920 * (v59_0)];
      v59_1 += 1;
    }
    v59_0 += 1;
  }
  std::vector<float> v62(v61);
  int64_t v60_0 = 0;
  for (int64_t v61_0 = 0; v61_0 < 0 + 1 * 1; v61_0 += 1) {
    int64_t v60_1 = 0;
    for (int64_t v61_1 = 0; v61_1 < 0 + 104 * 1; v61_1 += 1) {
      v62[v61_1 + 1024 * (v61_0)] = v60[v60_1 + 104 * (v60_0)];
      v60_1 += 1;
    }
    v60_0 += 1;
  }
  std::vector<float> v63(1 * 868);
  for (int64_t v63_i0 = 0; v63_i0 < 1; ++v63_i0) {
    for (int64_t v63_i1 = 0; v63_i1 < 868; ++v63_i1) {
      v63[v63_i1 + 868 * (v63_i0)] = v20[0 + v63_i1 * 1 + 1024 * (12 + v63_i0 * 1)];
    }
  }
  std::vector<float> v64(1 * 156);
  for (int64_t v64_i0 = 0; v64_i0 < 1; ++v64_i0) {
    for (int64_t v64_i1 = 0; v64_i1 < 156; ++v64_i1) {
      v64[v64_i1 + 156 * (v64_i0)] = v20[868 + v64_i1 * 1 + 1024 * (12 + v64_i0 * 1)];
    }
  }
  std::vector<float> v65(v29);
  int64_t v63_0 = 0;
  for (int64_t v29_0 = 0; v29_0 < 0 + 1 * 1; v29_0 += 1) {
    int64_t v63_1 = 0;
    for (int64_t v29_1 = 156; v29_1 < 156 + 868 * 1; v29_1 += 1) {
      v65[v29_1 + 1024 * (v29_0)] = v63[v63_1 + 868 * (v63_0)];
      v63_1 += 1;
    }
    v63_0 += 1;
  }
  std::vector<float> v66(v65);
  int64_t v64_0 = 0;
  for (int64_t v65_0 = 0; v65_0 < 0 + 1 * 1; v65_0 += 1) {
    int64_t v64_1 = 0;
    for (int64_t v65_1 = 0; v65_1 < 0 + 156 * 1; v65_1 += 1) {
      v66[v65_1 + 1024 * (v65_0)] = v64[v64_1 + 156 * (v64_0)];
      v64_1 += 1;
    }
    v64_0 += 1;
  }
  std::vector<float> v67(1 * 868);
  for (int64_t v67_i0 = 0; v67_i0 < 1; ++v67_i0) {
    for (int64_t v67_i1 = 0; v67_i1 < 868; ++v67_i1) {
      v67[v67_i1 + 868 * (v67_i0)] = v20[0 + v67_i1 * 1 + 1024 * (13 + v67_i0 * 1)];
    }
  }
  std::vector<float> v68(1 * 156);
  for (int64_t v68_i0 = 0; v68_i0 < 1; ++v68_i0) {
    for (int64_t v68_i1 = 0; v68_i1 < 156; ++v68_i1) {
      v68[v68_i1 + 156 * (v68_i0)] = v20[868 + v68_i1 * 1 + 1024 * (13 + v68_i0 * 1)];
    }
  }
  std::vector<float> v69(v30);
  int64_t v67_0 = 0;
  for (int64_t v30_0 = 0; v30_0 < 0 + 1 * 1; v30_0 += 1) {
    int64_t v67_1 = 0;
    for (int64_t v30_1 = 156; v30_1 < 156 + 868 * 1; v30_1 += 1) {
      v69[v30_1 + 1024 * (v30_0)] = v67[v67_1 + 868 * (v67_0)];
      v67_1 += 1;
    }
    v67_0 += 1;
  }
  std::vector<float> v70(v69);
  int64_t v68_0 = 0;
  for (int64_t v69_0 = 0; v69_0 < 0 + 1 * 1; v69_0 += 1) {
    int64_t v68_1 = 0;
    for (int64_t v69_1 = 0; v69_1 < 0 + 156 * 1; v69_1 += 1) {
      v70[v69_1 + 1024 * (v69_0)] = v68[v68_1 + 156 * (v68_0)];
      v68_1 += 1;
    }
    v68_0 += 1;
  }
  std::vector<float> v71(1 * 1024);
  for (int64_t v71_i0 = 0; v71_i0 < 1; ++v71_i0) {
    for (int64_t v71_i1 = 0; v71_i1 < 1024; ++v71_i1) {
      v71[v71_i1 + 1024 * (v71_i0)] = v20[0 + v71_i1 * 1 + 1024 * (0 + v71_i0 * 1)];
    }
  }
  std::vector<double> v72(std::begin(v71), std::end(v71));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v72;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v72[i % v72.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  v19[0] = pt;
  std::vector<float> v73(1 * 1024);
  for (int64_t v73_i0 = 0; v73_i0 < 1; ++v73_i0) {
    for (int64_t v73_i1 = 0; v73_i1 < 1024; ++v73_i1) {
      v73[v73_i1 + 1024 * (v73_i0)] = v20[0 + v73_i1 * 1 + 1024 * (1 + v73_i0 * 1)];
    }
  }
  std::vector<double> v74(std::begin(v73), std::end(v73));
  auto pt1_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt1_filled = v74;
  pt1_filled.clear();
  pt1_filled.reserve(pt1_filled_n);
  for (auto i = 0; i < pt1_filled_n; ++i) {
    pt1_filled.push_back(v74[i % v74.size()]);
  }
  auto pt1 = cc->MakeCKKSPackedPlaintext(pt1_filled);
  v19[1] = pt1;
  std::vector<float> v75(1 * 1024);
  for (int64_t v75_i0 = 0; v75_i0 < 1; ++v75_i0) {
    for (int64_t v75_i1 = 0; v75_i1 < 1024; ++v75_i1) {
      v75[v75_i1 + 1024 * (v75_i0)] = v20[0 + v75_i1 * 1 + 1024 * (2 + v75_i0 * 1)];
    }
  }
  std::vector<double> v76(std::begin(v75), std::end(v75));
  auto pt2_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt2_filled = v76;
  pt2_filled.clear();
  pt2_filled.reserve(pt2_filled_n);
  for (auto i = 0; i < pt2_filled_n; ++i) {
    pt2_filled.push_back(v76[i % v76.size()]);
  }
  auto pt2 = cc->MakeCKKSPackedPlaintext(pt2_filled);
  v19[2] = pt2;
  std::vector<float> v77(1 * 1024);
  for (int64_t v77_i0 = 0; v77_i0 < 1; ++v77_i0) {
    for (int64_t v77_i1 = 0; v77_i1 < 1024; ++v77_i1) {
      v77[v77_i1 + 1024 * (v77_i0)] = v20[0 + v77_i1 * 1 + 1024 * (3 + v77_i0 * 1)];
    }
  }
  std::vector<double> v78(std::begin(v77), std::end(v77));
  auto pt3_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt3_filled = v78;
  pt3_filled.clear();
  pt3_filled.reserve(pt3_filled_n);
  for (auto i = 0; i < pt3_filled_n; ++i) {
    pt3_filled.push_back(v78[i % v78.size()]);
  }
  auto pt3 = cc->MakeCKKSPackedPlaintext(pt3_filled);
  v19[3] = pt3;
  std::vector<float> v79(1 * 1024);
  for (int64_t v79_i0 = 0; v79_i0 < 1; ++v79_i0) {
    for (int64_t v79_i1 = 0; v79_i1 < 1024; ++v79_i1) {
      v79[v79_i1 + 1024 * (v79_i0)] = v34[0 + v79_i1 * 1 + 1024 * (0 + v79_i0 * 1)];
    }
  }
  std::vector<double> v80(std::begin(v79), std::end(v79));
  auto pt4_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt4_filled = v80;
  pt4_filled.clear();
  pt4_filled.reserve(pt4_filled_n);
  for (auto i = 0; i < pt4_filled_n; ++i) {
    pt4_filled.push_back(v80[i % v80.size()]);
  }
  auto pt4 = cc->MakeCKKSPackedPlaintext(pt4_filled);
  v19[4] = pt4;
  std::vector<float> v81(1 * 1024);
  for (int64_t v81_i0 = 0; v81_i0 < 1; ++v81_i0) {
    for (int64_t v81_i1 = 0; v81_i1 < 1024; ++v81_i1) {
      v81[v81_i1 + 1024 * (v81_i0)] = v38[0 + v81_i1 * 1 + 1024 * (0 + v81_i0 * 1)];
    }
  }
  std::vector<double> v82(std::begin(v81), std::end(v81));
  auto pt5_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt5_filled = v82;
  pt5_filled.clear();
  pt5_filled.reserve(pt5_filled_n);
  for (auto i = 0; i < pt5_filled_n; ++i) {
    pt5_filled.push_back(v82[i % v82.size()]);
  }
  auto pt5 = cc->MakeCKKSPackedPlaintext(pt5_filled);
  v19[5] = pt5;
  std::vector<float> v83(1 * 1024);
  for (int64_t v83_i0 = 0; v83_i0 < 1; ++v83_i0) {
    for (int64_t v83_i1 = 0; v83_i1 < 1024; ++v83_i1) {
      v83[v83_i1 + 1024 * (v83_i0)] = v42[0 + v83_i1 * 1 + 1024 * (0 + v83_i0 * 1)];
    }
  }
  std::vector<double> v84(std::begin(v83), std::end(v83));
  auto pt6_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt6_filled = v84;
  pt6_filled.clear();
  pt6_filled.reserve(pt6_filled_n);
  for (auto i = 0; i < pt6_filled_n; ++i) {
    pt6_filled.push_back(v84[i % v84.size()]);
  }
  auto pt6 = cc->MakeCKKSPackedPlaintext(pt6_filled);
  v19[6] = pt6;
  std::vector<float> v85(1 * 1024);
  for (int64_t v85_i0 = 0; v85_i0 < 1; ++v85_i0) {
    for (int64_t v85_i1 = 0; v85_i1 < 1024; ++v85_i1) {
      v85[v85_i1 + 1024 * (v85_i0)] = v46[0 + v85_i1 * 1 + 1024 * (0 + v85_i0 * 1)];
    }
  }
  std::vector<double> v86(std::begin(v85), std::end(v85));
  auto pt7_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt7_filled = v86;
  pt7_filled.clear();
  pt7_filled.reserve(pt7_filled_n);
  for (auto i = 0; i < pt7_filled_n; ++i) {
    pt7_filled.push_back(v86[i % v86.size()]);
  }
  auto pt7 = cc->MakeCKKSPackedPlaintext(pt7_filled);
  v19[7] = pt7;
  std::vector<float> v87(1 * 1024);
  for (int64_t v87_i0 = 0; v87_i0 < 1; ++v87_i0) {
    for (int64_t v87_i1 = 0; v87_i1 < 1024; ++v87_i1) {
      v87[v87_i1 + 1024 * (v87_i0)] = v50[0 + v87_i1 * 1 + 1024 * (0 + v87_i0 * 1)];
    }
  }
  std::vector<double> v88(std::begin(v87), std::end(v87));
  auto pt8_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt8_filled = v88;
  pt8_filled.clear();
  pt8_filled.reserve(pt8_filled_n);
  for (auto i = 0; i < pt8_filled_n; ++i) {
    pt8_filled.push_back(v88[i % v88.size()]);
  }
  auto pt8 = cc->MakeCKKSPackedPlaintext(pt8_filled);
  v19[8] = pt8;
  std::vector<float> v89(1 * 1024);
  for (int64_t v89_i0 = 0; v89_i0 < 1; ++v89_i0) {
    for (int64_t v89_i1 = 0; v89_i1 < 1024; ++v89_i1) {
      v89[v89_i1 + 1024 * (v89_i0)] = v54[0 + v89_i1 * 1 + 1024 * (0 + v89_i0 * 1)];
    }
  }
  std::vector<double> v90(std::begin(v89), std::end(v89));
  auto pt9_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt9_filled = v90;
  pt9_filled.clear();
  pt9_filled.reserve(pt9_filled_n);
  for (auto i = 0; i < pt9_filled_n; ++i) {
    pt9_filled.push_back(v90[i % v90.size()]);
  }
  auto pt9 = cc->MakeCKKSPackedPlaintext(pt9_filled);
  v19[9] = pt9;
  std::vector<float> v91(1 * 1024);
  for (int64_t v91_i0 = 0; v91_i0 < 1; ++v91_i0) {
    for (int64_t v91_i1 = 0; v91_i1 < 1024; ++v91_i1) {
      v91[v91_i1 + 1024 * (v91_i0)] = v58[0 + v91_i1 * 1 + 1024 * (0 + v91_i0 * 1)];
    }
  }
  std::vector<double> v92(std::begin(v91), std::end(v91));
  auto pt10_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt10_filled = v92;
  pt10_filled.clear();
  pt10_filled.reserve(pt10_filled_n);
  for (auto i = 0; i < pt10_filled_n; ++i) {
    pt10_filled.push_back(v92[i % v92.size()]);
  }
  auto pt10 = cc->MakeCKKSPackedPlaintext(pt10_filled);
  v19[10] = pt10;
  std::vector<float> v93(1 * 1024);
  for (int64_t v93_i0 = 0; v93_i0 < 1; ++v93_i0) {
    for (int64_t v93_i1 = 0; v93_i1 < 1024; ++v93_i1) {
      v93[v93_i1 + 1024 * (v93_i0)] = v62[0 + v93_i1 * 1 + 1024 * (0 + v93_i0 * 1)];
    }
  }
  std::vector<double> v94(std::begin(v93), std::end(v93));
  auto pt11_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt11_filled = v94;
  pt11_filled.clear();
  pt11_filled.reserve(pt11_filled_n);
  for (auto i = 0; i < pt11_filled_n; ++i) {
    pt11_filled.push_back(v94[i % v94.size()]);
  }
  auto pt11 = cc->MakeCKKSPackedPlaintext(pt11_filled);
  v19[11] = pt11;
  std::vector<float> v95(1 * 1024);
  for (int64_t v95_i0 = 0; v95_i0 < 1; ++v95_i0) {
    for (int64_t v95_i1 = 0; v95_i1 < 1024; ++v95_i1) {
      v95[v95_i1 + 1024 * (v95_i0)] = v66[0 + v95_i1 * 1 + 1024 * (0 + v95_i0 * 1)];
    }
  }
  std::vector<double> v96(std::begin(v95), std::end(v95));
  auto pt12_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt12_filled = v96;
  pt12_filled.clear();
  pt12_filled.reserve(pt12_filled_n);
  for (auto i = 0; i < pt12_filled_n; ++i) {
    pt12_filled.push_back(v96[i % v96.size()]);
  }
  auto pt12 = cc->MakeCKKSPackedPlaintext(pt12_filled);
  v19[12] = pt12;
  std::vector<float> v97(1 * 1024);
  for (int64_t v97_i0 = 0; v97_i0 < 1; ++v97_i0) {
    for (int64_t v97_i1 = 0; v97_i1 < 1024; ++v97_i1) {
      v97[v97_i1 + 1024 * (v97_i0)] = v70[0 + v97_i1 * 1 + 1024 * (0 + v97_i0 * 1)];
    }
  }
  std::vector<double> v98(std::begin(v97), std::end(v97));
  auto pt13_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt13_filled = v98;
  pt13_filled.clear();
  pt13_filled.reserve(pt13_filled_n);
  for (auto i = 0; i < pt13_filled_n; ++i) {
    pt13_filled.push_back(v98[i % v98.size()]);
  }
  auto pt13 = cc->MakeCKKSPackedPlaintext(pt13_filled);
  v19[13] = pt13;
  auto pt14_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt14_filled = v17;
  pt14_filled.clear();
  pt14_filled.reserve(pt14_filled_n);
  for (auto i = 0; i < pt14_filled_n; ++i) {
    pt14_filled.push_back(v17[i % v17.size()]);
  }
  auto pt14 = cc->MakeCKKSPackedPlaintext(pt14_filled);
  v19[14] = pt14;
  auto pt15_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt15_filled = v18;
  pt15_filled.clear();
  pt15_filled.reserve(pt15_filled_n);
  for (auto i = 0; i < pt15_filled_n; ++i) {
    pt15_filled.push_back(v18[i % v18.size()]);
  }
  auto pt15 = cc->MakeCKKSPackedPlaintext(pt15_filled);
  v19[15] = pt15;
  return v19;
}
std::vector<CiphertextT> matmul_pt__preprocessed(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1, const std::vector<Plaintext>& v2) {
  std::vector<size_t> v3 = {39, 26, 13};
  [[maybe_unused]] size_t v4 = 0;
  [[maybe_unused]] size_t v5 = 13;
  [[maybe_unused]] size_t v6 = 52;
  [[maybe_unused]] size_t v7 = 104;
  [[maybe_unused]] size_t v8 = 156;
  [[maybe_unused]] size_t v9 = 192;
  [[maybe_unused]] size_t v10 = 1;
  [[maybe_unused]] size_t v11 = 2;
  [[maybe_unused]] size_t v12 = 3;
  [[maybe_unused]] size_t v13 = 4;
  [[maybe_unused]] size_t v14 = 5;
  [[maybe_unused]] size_t v15 = 6;
  [[maybe_unused]] size_t v16 = 7;
  [[maybe_unused]] size_t v17 = 8;
  [[maybe_unused]] size_t v18 = 9;
  [[maybe_unused]] size_t v19 = 10;
  [[maybe_unused]] size_t v20 = 11;
  [[maybe_unused]] size_t v21 = 12;
  [[maybe_unused]] size_t v22 = 14;
  [[maybe_unused]] size_t v23 = 15;
  Plaintext pt = v2[0];
  const auto& ct = v0[0];
  const auto& digit_decomp = cc->EvalFastRotationPrecompute(ct);
  auto ct1 = cc->EvalMult(ct, pt);
  std::vector<CiphertextT> v24(3);
  Plaintext pt1 = v2[1];
  Plaintext pt2 = v2[2];
  Plaintext pt3 = v2[3];
  Plaintext pt4 = v2[4];
  auto ct2 = cc->EvalMult(ct, pt4);
  Plaintext pt5 = v2[5];
  Plaintext pt6 = v2[6];
  Plaintext pt7 = v2[7];
  Plaintext pt8 = v2[8];
  auto ct3 = cc->EvalMult(ct, pt8);
  Plaintext pt9 = v2[9];
  Plaintext pt10 = v2[10];
  Plaintext pt11 = v2[11];
  Plaintext pt12 = v2[12];
  auto ct4 = cc->EvalMult(ct, pt12);
  Plaintext pt13 = v2[13];
  Plaintext pt14 = v2[14];
  Plaintext pt15 = v2[15];
  std::vector<CiphertextT> v25(1);
  #pragma omp parallel for
  for (auto v27 = 0; v27 < 3; ++v27) {
    size_t v29 = v3[v27];
    const auto& ct5 = cc->EvalFastRotation(ct, v29, 2 * cc->GetRingDimension(), digit_decomp);
    const std::vector<CiphertextT> v30 = {ct5};
    v24[v27] = v30[0];
  }
  const auto& ct6 = v24[0];
  const auto& ct7 = v24[1];
  const auto& ct8 = v24[2];
  const auto& ct9 = cc->EvalMult(ct8, pt1);
  const auto& ct10 = cc->EvalMult(ct7, pt2);
  auto ct11 = cc->EvalMult(ct6, pt3);
  const auto& ct12 = cc->EvalMult(ct8, pt5);
  auto ct13 = cc->EvalMult(ct7, pt6);
  const auto& ct14 = cc->EvalMult(ct6, pt7);
  cc->EvalAddInPlace(ct2, ct12);
  cc->EvalAddInPlace(ct13, ct14);
  cc->EvalAddInPlace(ct2, ct13);
  const auto& ct18 = cc->EvalRotate(ct2, 52);
  const auto& ct19 = cc->EvalMult(ct8, pt9);
  auto ct20 = cc->EvalMult(ct7, pt10);
  const auto& ct21 = cc->EvalMult(ct6, pt11);
  cc->EvalAddInPlace(ct3, ct19);
  cc->EvalAddInPlace(ct20, ct21);
  cc->EvalAddInPlace(ct3, ct20);
  auto ct25 = cc->EvalRotate(ct3, 104);
  const auto& ct26 = cc->EvalMult(ct8, pt13);
  cc->EvalAddInPlace(ct4, ct26);
  const auto& ct28 = cc->EvalRotate(ct4, 156);
  cc->EvalAddInPlace(ct1, ct9);
  cc->EvalAddInPlace(ct1, ct10);
  cc->EvalAddInPlace(ct11, ct18);
  cc->EvalAddInPlace(ct25, ct28);
  cc->EvalAddInPlace(ct11, ct25);
  cc->EvalAddInPlace(ct1, ct11);
  const auto& ct35 = cc->ModReduce(ct1);
  auto ct36 = cc->EvalMult(ct35, pt14);
  auto ct37 = cc->EvalRotate(ct1, 192);
  cc->ModReduceInPlace(ct37);
  const auto& ct39 = cc->EvalMult(ct37, pt15);
  cc->EvalAddInPlace(ct36, ct39);
  cc->ModReduceInPlace(ct36);
  v25[0] = ct36;
  return v25;
}
std::vector<CiphertextT> matmul_pt(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1) {
  const auto& v2 = matmul_pt__preprocessing(cc, v1);
  const auto& v3 = matmul_pt__preprocessed(cc, v0, v1, v2);
  return v3;
}
std::vector<CiphertextT> matmul_pt__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] size_t v1 = 14;
  [[maybe_unused]] size_t v2 = 13;
  [[maybe_unused]] size_t v3 = 1024;
  [[maybe_unused]] size_t v4 = 1;
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6(1024, 0);
  std::vector<float> v7 = v6;
  for (auto v8 = 0; v8 < 1024; v8 += 1) {
    size_t v10 = v8 % v2;
    size_t v11 = v8 % v1;
    float v12 = v0[v11 + 14 * (v10)];
    v7[v8 + 1024 * (0)] = v12;
  }
  std::vector<float> v14(1 * 1024);
  for (int64_t v14_i0 = 0; v14_i0 < 1; ++v14_i0) {
    for (int64_t v14_i1 = 0; v14_i1 < 1024; ++v14_i1) {
      v14[v14_i1 + 1024 * (v14_i0)] = v7[0 + v14_i1 * 1 + 1024 * (0 + v14_i0 * 1)];
    }
  }
  std::vector<double> v15(std::begin(v14), std::end(v14));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v15;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v15[i % v15.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  const auto& ct = cc->Encrypt(pk, pt);
  const std::vector<CiphertextT> v16 = {ct};
  return v16;
}
std::vector<float> matmul_pt__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk) {
  [[maybe_unused]] int32_t v1 = 816;
  [[maybe_unused]] int32_t v2 = 207;
  std::vector<float> v3(208, 0);
  [[maybe_unused]] int32_t v4 = 0;
  [[maybe_unused]] int32_t v5 = 12;
  [[maybe_unused]] int32_t v6 = 1;
  [[maybe_unused]] int32_t v7 = 64;
  [[maybe_unused]] int32_t v8 = 65;
  [[maybe_unused]] int32_t v9 = 1039;
  [[maybe_unused]] int32_t v10 = 208;
  [[maybe_unused]] int32_t v11 = 13;
  [[maybe_unused]] int32_t v12 = 16;
  [[maybe_unused]] int32_t v13 = 15;
  [[maybe_unused]] int32_t v14 = 1024;
  [[maybe_unused]] size_t v15 = 0;
  const auto& ct = v0[0];
  PlaintextT pt;
  cc->Decrypt(sk, ct, &pt);
  pt->SetLength(1024);
  const auto& v16_cast = pt->GetCKKSPackedValue();
  std::vector<float> v16(v16_cast.size());
  std::transform(std::begin(v16_cast), std::end(v16_cast), std::begin(v16), [](const std::complex<double>& c) { return c.real(); });
  std::vector<float> v17 = v3;
  for (auto v18 = 0; v18 < 13; v18 += 1) {
    int32_t v20 = v5 - v18;
    for (auto v22 = 0; v22 < 16; v22 += 1) {
      int32_t v24 = v13 - v22;
      int32_t v25 = v20 * v7;
      int32_t v26 = v24 * v8;
      int32_t v27 = v25 - v26;
      int32_t v28 = v27 + v9;
      int32_t v29 = (v28 / v10) - ((v28 % v10 != 0) && ((v28 < 0) != (v10 < 0)));
      int32_t v30 = v29 * v10;
      int32_t v31 = v28 - v30;
      int32_t v32 = v2 - v31;
      for (auto v34 = v32; v34 < 1024; v34 += 208) {
        int32_t v36 = v31 + v1;
        int32_t v37 = (v36 / v10) - ((v36 % v10 != 0) && ((v36 < 0) != (v10 < 0)));
        int32_t v38 = v37 * v10;
        int32_t v39 = v32 + v38;
        int32_t v40 = v34 - v32;
        int32_t v41 = v39 - v40;
        size_t v42 = static_cast<size_t>(v41);
        float v43 = v16[v42 + 1024 * (0)];
        size_t v44 = static_cast<size_t>(v20);
        size_t v45 = static_cast<size_t>(v24);
        v17[v45 + 16 * (v44)] = v43;
      }
    }
  }
  return v17;
}
CryptoContextT matmul_pt__generate_crypto_context() {
  CCParamsT params;
  params.SetMultiplicativeDepth(2);
  params.SetFirstModSize(55);
  params.SetScalingModSize(45);
  params.SetKeySwitchTechnique(HYBRID);
  CryptoContextT cc = GenCryptoContext(params);
  cc->Enable(PKE);
  cc->Enable(KEYSWITCH);
  cc->Enable(LEVELEDSHE);
  return cc;
}
CryptoContextT matmul_pt__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk) {
  cc->EvalRotateKeyGen(sk, {192, 26, 52, 104, 156, 13, 39});
  return cc;
}
