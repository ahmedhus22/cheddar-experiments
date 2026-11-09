
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

std::vector<float> _assign_layout_15368556053367397286(std::vector<float> v0) {
  [[maybe_unused]] int32_t v1 = 4096;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(4096, 0);
  [[maybe_unused]] int32_t v5 = 2048;
  [[maybe_unused]] size_t v6 = 0;
  std::vector<float> v7 = v4;
  for (auto v8 = 0; v8 < 4096; v8 += 1) {
    int32_t v10 = (v8 / v5) - ((v8 % v5 != 0) && ((v8 < 0) != (v5 < 0)));
    int32_t v11 = v10 * v5;
    int32_t v12 = v8 - v11;
    size_t v13 = static_cast<size_t>(v8);
    float v14 = v0[v13 + 4096 * (0)];
    size_t v15 = static_cast<size_t>(v10);
    size_t v16 = static_cast<size_t>(v12);
    v7[v16 + 2048 * (v15)] = v14;
  }
  return v7;
}
std::vector<Plaintext> matvec_64__preprocessing(CryptoContextT cc, std::vector<float> v0) {
  std::vector<float> v1 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  [[maybe_unused]] size_t v2 = 0;
  [[maybe_unused]] size_t v3 = 1;
  [[maybe_unused]] size_t v4 = 2;
  [[maybe_unused]] size_t v5 = 3;
  std::vector<Plaintext> v6(4);
  const auto& v7 = _assign_layout_15368556053367397286(v0);
  const auto& v8 = _assign_layout_15368556053367397286(v1);
  std::vector<float> v9(1 * 2048);
  for (int64_t v9_i0 = 0; v9_i0 < 1; ++v9_i0) {
    for (int64_t v9_i1 = 0; v9_i1 < 2048; ++v9_i1) {
      v9[v9_i1 + 2048 * (v9_i0)] = v7[0 + v9_i1 * 1 + 2048 * (0 + v9_i0 * 1)];
    }
  }
  std::vector<double> v10(std::begin(v9), std::end(v9));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v10;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v10[i % v10.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  v6[0] = pt;
  std::vector<float> v11(1 * 2048);
  for (int64_t v11_i0 = 0; v11_i0 < 1; ++v11_i0) {
    for (int64_t v11_i1 = 0; v11_i1 < 2048; ++v11_i1) {
      v11[v11_i1 + 2048 * (v11_i0)] = v7[0 + v11_i1 * 1 + 2048 * (1 + v11_i0 * 1)];
    }
  }
  std::vector<double> v12(std::begin(v11), std::end(v11));
  auto pt1_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt1_filled = v12;
  pt1_filled.clear();
  pt1_filled.reserve(pt1_filled_n);
  for (auto i = 0; i < pt1_filled_n; ++i) {
    pt1_filled.push_back(v12[i % v12.size()]);
  }
  auto pt1 = cc->MakeCKKSPackedPlaintext(pt1_filled);
  v6[1] = pt1;
  std::vector<float> v13(1 * 2048);
  for (int64_t v13_i0 = 0; v13_i0 < 1; ++v13_i0) {
    for (int64_t v13_i1 = 0; v13_i1 < 2048; ++v13_i1) {
      v13[v13_i1 + 2048 * (v13_i0)] = v8[0 + v13_i1 * 1 + 2048 * (0 + v13_i0 * 1)];
    }
  }
  std::vector<double> v14(std::begin(v13), std::end(v13));
  auto pt2_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt2_filled = v14;
  pt2_filled.clear();
  pt2_filled.reserve(pt2_filled_n);
  for (auto i = 0; i < pt2_filled_n; ++i) {
    pt2_filled.push_back(v14[i % v14.size()]);
  }
  auto pt2 = cc->MakeCKKSPackedPlaintext(pt2_filled);
  v6[2] = pt2;
  std::vector<float> v15(1 * 2048);
  for (int64_t v15_i0 = 0; v15_i0 < 1; ++v15_i0) {
    for (int64_t v15_i1 = 0; v15_i1 < 2048; ++v15_i1) {
      v15[v15_i1 + 2048 * (v15_i0)] = v8[0 + v15_i1 * 1 + 2048 * (1 + v15_i0 * 1)];
    }
  }
  std::vector<double> v16(std::begin(v15), std::end(v15));
  auto pt3_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt3_filled = v16;
  pt3_filled.clear();
  pt3_filled.reserve(pt3_filled_n);
  for (auto i = 0; i < pt3_filled_n; ++i) {
    pt3_filled.push_back(v16[i % v16.size()]);
  }
  auto pt3 = cc->MakeCKKSPackedPlaintext(pt3_filled);
  v6[3] = pt3;
  return v6;
}
std::vector<CiphertextT> matvec_64__preprocessed(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1, const std::vector<Plaintext>& v2) {
  [[maybe_unused]] size_t v3 = 1;
  [[maybe_unused]] size_t v4 = 2;
  [[maybe_unused]] size_t v5 = 4;
  [[maybe_unused]] size_t v6 = 8;
  [[maybe_unused]] size_t v7 = 16;
  [[maybe_unused]] size_t v8 = 32;
  [[maybe_unused]] size_t v9 = 0;
  [[maybe_unused]] size_t v10 = 3;
  Plaintext pt = v2[0];
  Plaintext pt1 = v2[1];
  const std::vector<Plaintext> v11 = {pt, pt1};
  std::vector<CiphertextT> v12(2);
  std::vector<CiphertextT> v13 = v12;
  for (auto v14 = 0; v14 < 2; ++v14) {
    const auto& ct = v0[v14];
    Plaintext pt2 = v11[v14];
    const auto& ct1 = cc->EvalMult(ct, pt2);
    v13[v14] = ct1;
    v13 = v13;
  }
  std::vector<CiphertextT> v17 = v12;
  for (auto v18 = 0; v18 < 2; ++v18) {
    const auto& ct2 = v13[v18];
    const auto& ct3 = cc->EvalRotate(ct2, 1);
    v17[v18] = ct3;
    v17 = v17;
  }
  std::vector<CiphertextT> v21 = v12;
  for (auto v22 = 0; v22 < 2; ++v22) {
    auto ct4 = v17[v22];
    const auto& ct5 = v13[v22];
    cc->EvalAddInPlace(ct4, ct5);
    v21[v22] = ct4;
    v21 = v21;
  }
  std::vector<CiphertextT> v25 = v12;
  for (auto v26 = 0; v26 < 2; ++v26) {
    const auto& ct7 = v21[v26];
    const auto& ct8 = cc->EvalRotate(ct7, 2);
    v25[v26] = ct8;
    v25 = v25;
  }
  std::vector<CiphertextT> v29 = v12;
  for (auto v30 = 0; v30 < 2; ++v30) {
    auto ct9 = v25[v30];
    const auto& ct10 = v21[v30];
    cc->EvalAddInPlace(ct9, ct10);
    v29[v30] = ct9;
    v29 = v29;
  }
  std::vector<CiphertextT> v33 = v12;
  for (auto v34 = 0; v34 < 2; ++v34) {
    const auto& ct12 = v29[v34];
    const auto& ct13 = cc->EvalRotate(ct12, 4);
    v33[v34] = ct13;
    v33 = v33;
  }
  std::vector<CiphertextT> v37 = v12;
  for (auto v38 = 0; v38 < 2; ++v38) {
    auto ct14 = v33[v38];
    const auto& ct15 = v29[v38];
    cc->EvalAddInPlace(ct14, ct15);
    v37[v38] = ct14;
    v37 = v37;
  }
  std::vector<CiphertextT> v41 = v12;
  for (auto v42 = 0; v42 < 2; ++v42) {
    const auto& ct17 = v37[v42];
    const auto& ct18 = cc->EvalRotate(ct17, 8);
    v41[v42] = ct18;
    v41 = v41;
  }
  std::vector<CiphertextT> v45 = v12;
  for (auto v46 = 0; v46 < 2; ++v46) {
    auto ct19 = v41[v46];
    const auto& ct20 = v37[v46];
    cc->EvalAddInPlace(ct19, ct20);
    v45[v46] = ct19;
    v45 = v45;
  }
  std::vector<CiphertextT> v49 = v12;
  for (auto v50 = 0; v50 < 2; ++v50) {
    const auto& ct22 = v45[v50];
    const auto& ct23 = cc->EvalRotate(ct22, 16);
    v49[v50] = ct23;
    v49 = v49;
  }
  std::vector<CiphertextT> v53 = v12;
  for (auto v54 = 0; v54 < 2; ++v54) {
    auto ct24 = v49[v54];
    const auto& ct25 = v45[v54];
    cc->EvalAddInPlace(ct24, ct25);
    v53[v54] = ct24;
    v53 = v53;
  }
  std::vector<CiphertextT> v57 = v12;
  for (auto v58 = 0; v58 < 2; ++v58) {
    const auto& ct27 = v53[v58];
    const auto& ct28 = cc->EvalRotate(ct27, 32);
    v57[v58] = ct28;
    v57 = v57;
  }
  std::vector<CiphertextT> v61 = v12;
  for (auto v62 = 0; v62 < 2; ++v62) {
    auto ct29 = v57[v62];
    const auto& ct30 = v53[v62];
    cc->EvalAddInPlace(ct29, ct30);
    v61[v62] = ct29;
    v61 = v61;
  }
  std::vector<CiphertextT> v65 = v12;
  for (auto v66 = 0; v66 < 2; ++v66) {
    auto ct32 = v61[v66];
    cc->ModReduceInPlace(ct32);
    v65[v66] = ct32;
    v65 = v65;
  }
  Plaintext pt3 = v2[2];
  Plaintext pt4 = v2[3];
  const std::vector<Plaintext> v69 = {pt3, pt4};
  std::vector<CiphertextT> v70 = v12;
  for (auto v71 = 0; v71 < 2; ++v71) {
    const auto& ct34 = v65[v71];
    Plaintext pt5 = v69[v71];
    const auto& ct35 = cc->EvalMult(ct34, pt5);
    v70[v71] = ct35;
    v70 = v70;
  }
  std::vector<CiphertextT> v74 = v12;
  for (auto v75 = 0; v75 < 2; ++v75) {
    auto ct36 = v70[v75];
    cc->ModReduceInPlace(ct36);
    v74[v75] = ct36;
    v74 = v74;
  }
  return v74;
}
std::vector<CiphertextT> matvec_64(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1) {
  const auto& v2 = matvec_64__preprocessing(cc, v1);
  const auto& v3 = matvec_64__preprocessed(cc, v0, v1, v2);
  return v3;
}
std::vector<CiphertextT> matvec_64__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] int32_t v1 = 4096;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(4096, 0);
  [[maybe_unused]] int32_t v5 = 2048;
  [[maybe_unused]] size_t v6 = 0;
  std::vector<float> v7 = v4;
  for (auto v8 = 0; v8 < 4096; v8 += 1) {
    int32_t v10 = (v8 / v5) - ((v8 % v5 != 0) && ((v8 < 0) != (v5 < 0)));
    int32_t v11 = v10 * v5;
    int32_t v12 = v8 - v11;
    size_t v13 = static_cast<size_t>(v8);
    float v14 = v0[v13 + 4096 * (0)];
    size_t v15 = static_cast<size_t>(v10);
    size_t v16 = static_cast<size_t>(v12);
    v7[v16 + 2048 * (v15)] = v14;
  }
  std::vector<float> v18(1 * 2048);
  for (int64_t v18_i0 = 0; v18_i0 < 1; ++v18_i0) {
    for (int64_t v18_i1 = 0; v18_i1 < 2048; ++v18_i1) {
      v18[v18_i1 + 2048 * (v18_i0)] = v7[0 + v18_i1 * 1 + 2048 * (0 + v18_i0 * 1)];
    }
  }
  std::vector<double> v19(std::begin(v18), std::end(v18));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v19;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v19[i % v19.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  const auto& ct = cc->Encrypt(pk, pt);
  std::vector<float> v20(1 * 2048);
  for (int64_t v20_i0 = 0; v20_i0 < 1; ++v20_i0) {
    for (int64_t v20_i1 = 0; v20_i1 < 2048; ++v20_i1) {
      v20[v20_i1 + 2048 * (v20_i0)] = v7[0 + v20_i1 * 1 + 2048 * (1 + v20_i0 * 1)];
    }
  }
  std::vector<double> v21(std::begin(v20), std::end(v20));
  auto pt1_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt1_filled = v21;
  pt1_filled.clear();
  pt1_filled.reserve(pt1_filled_n);
  for (auto i = 0; i < pt1_filled_n; ++i) {
    pt1_filled.push_back(v21[i % v21.size()]);
  }
  auto pt1 = cc->MakeCKKSPackedPlaintext(pt1_filled);
  const auto& ct1 = cc->Encrypt(pk, pt1);
  const std::vector<CiphertextT> v22 = {ct, ct1};
  return v22;
}
std::vector<float> matvec_64__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk) {
  [[maybe_unused]] size_t v1 = 1;
  std::vector<float> v2(4096, 0);
  [[maybe_unused]] int32_t v3 = 0;
  [[maybe_unused]] int32_t v4 = 4095;
  [[maybe_unused]] int32_t v5 = 1;
  [[maybe_unused]] int32_t v6 = 2048;
  [[maybe_unused]] int32_t v7 = 4096;
  [[maybe_unused]] size_t v8 = 0;
  const auto& ct = v0[0];
  PlaintextT pt;
  cc->Decrypt(sk, ct, &pt);
  pt->SetLength(2048);
  const auto& v9_cast = pt->GetCKKSPackedValue();
  std::vector<float> v9(v9_cast.size());
  std::transform(std::begin(v9_cast), std::end(v9_cast), std::begin(v9), [](const std::complex<double>& c) { return c.real(); });
  const auto& ct1 = v0[1];
  PlaintextT pt1;
  cc->Decrypt(sk, ct1, &pt1);
  pt1->SetLength(2048);
  const auto& v10_cast = pt1->GetCKKSPackedValue();
  std::vector<float> v10(v10_cast.size());
  std::transform(std::begin(v10_cast), std::end(v10_cast), std::begin(v10), [](const std::complex<double>& c) { return c.real(); });
  std::vector<float> v11(4096);
  std::vector<float> v12(v11);
  int64_t v9_0 = 0;
  for (int64_t v11_0 = 0; v11_0 < 0 + 1 * 1; v11_0 += 1) {
    int64_t v9_1 = 0;
    for (int64_t v11_1 = 0; v11_1 < 0 + 2048 * 1; v11_1 += 1) {
      v12[v11_1 + 2048 * (v11_0)] = v9[v9_1 + 2048 * (v9_0)];
      v9_1 += 1;
    }
    v9_0 += 1;
  }
  std::vector<float> v13(v12);
  int64_t v10_0 = 0;
  for (int64_t v12_0 = 1; v12_0 < 1 + 1 * 1; v12_0 += 1) {
    int64_t v10_1 = 0;
    for (int64_t v12_1 = 0; v12_1 < 0 + 2048 * 1; v12_1 += 1) {
      v13[v12_1 + 2048 * (v12_0)] = v10[v10_1 + 2048 * (v10_0)];
      v10_1 += 1;
    }
    v10_0 += 1;
  }
  std::vector<float> v14 = v2;
  for (auto v15 = 0; v15 < 4096; v15 += 1) {
    int32_t v17 = v4 - v15;
    int32_t v18 = (v17 / v6) - ((v17 % v6 != 0) && ((v17 < 0) != (v6 < 0)));
    int32_t v19 = v18 * v6;
    int32_t v20 = v17 - v19;
    size_t v21 = static_cast<size_t>(v18);
    size_t v22 = static_cast<size_t>(v20);
    float v23 = v13[v22 + 2048 * (v21)];
    size_t v24 = static_cast<size_t>(v17);
    v14[v24 + 4096 * (0)] = v23;
  }
  return v14;
}
CryptoContextT matvec_64__generate_crypto_context() {
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
CryptoContextT matvec_64__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk) {
  cc->EvalRotateKeyGen(sk, {2, 16, 4, 32, 1, 8});
  return cc;
}
