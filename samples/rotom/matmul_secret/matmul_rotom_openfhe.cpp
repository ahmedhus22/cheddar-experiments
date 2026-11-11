
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

std::vector<Plaintext> matmul_secret__preprocessing(CryptoContextT cc) {
  [[maybe_unused]] size_t v0 = 0;
  [[maybe_unused]] size_t v1 = 1;
  [[maybe_unused]] size_t v2 = 2;
  [[maybe_unused]] size_t v3 = 3;
  std::vector<double> v4 = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<double> v5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<double> v6(2048, 1);
  std::vector<double> v7 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<Plaintext> v8(4);
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v4;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v4[i % v4.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  v8[0] = pt;
  auto pt1_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt1_filled = v5;
  pt1_filled.clear();
  pt1_filled.reserve(pt1_filled_n);
  for (auto i = 0; i < pt1_filled_n; ++i) {
    pt1_filled.push_back(v5[i % v5.size()]);
  }
  auto pt1 = cc->MakeCKKSPackedPlaintext(pt1_filled);
  v8[1] = pt1;
  auto pt2_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt2_filled = v6;
  pt2_filled.clear();
  pt2_filled.reserve(pt2_filled_n);
  for (auto i = 0; i < pt2_filled_n; ++i) {
    pt2_filled.push_back(v6[i % v6.size()]);
  }
  auto pt2 = cc->MakeCKKSPackedPlaintext(pt2_filled);
  v8[2] = pt2;
  auto pt3_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt3_filled = v7;
  pt3_filled.clear();
  pt3_filled.reserve(pt3_filled_n);
  for (auto i = 0; i < pt3_filled_n; ++i) {
    pt3_filled.push_back(v7[i % v7.size()]);
  }
  auto pt3 = cc->MakeCKKSPackedPlaintext(pt3_filled);
  v8[3] = pt3;
  return v8;
}
std::vector<CiphertextT> matmul_secret__preprocessed(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<CiphertextT> v1, const std::vector<Plaintext>& v2) {
  std::vector<int32_t> v3 = {-20, 8, -18, 10, -26, -28, 28, 32, 34, -4, -2, 2, 58, -10, 12, 26, 22, 56, -12, 20, 6, 14, 40, 4, 24, 42, 50, 48, 16, 18, 30};
  [[maybe_unused]] size_t v4 = 29;
  [[maybe_unused]] size_t v5 = 27;
  [[maybe_unused]] size_t v6 = 25;
  [[maybe_unused]] size_t v7 = 23;
  [[maybe_unused]] size_t v8 = 21;
  [[maybe_unused]] size_t v9 = 19;
  [[maybe_unused]] size_t v10 = 17;
  [[maybe_unused]] size_t v11 = 15;
  [[maybe_unused]] size_t v12 = 13;
  [[maybe_unused]] size_t v13 = 11;
  [[maybe_unused]] size_t v14 = 9;
  [[maybe_unused]] size_t v15 = 7;
  [[maybe_unused]] size_t v16 = 5;
  [[maybe_unused]] size_t v17 = 0;
  [[maybe_unused]] size_t v18 = 30;
  [[maybe_unused]] size_t v19 = 28;
  [[maybe_unused]] size_t v20 = 22;
  [[maybe_unused]] size_t v21 = 20;
  [[maybe_unused]] size_t v22 = 14;
  [[maybe_unused]] size_t v23 = 12;
  [[maybe_unused]] size_t v24 = 6;
  [[maybe_unused]] size_t v25 = 4;
  [[maybe_unused]] size_t v26 = -192;
  [[maybe_unused]] size_t v27 = -16;
  [[maybe_unused]] size_t v28 = -32;
  [[maybe_unused]] size_t v29 = -1;
  [[maybe_unused]] size_t v30 = 2;
  [[maybe_unused]] size_t v31 = -8;
  [[maybe_unused]] size_t v32 = -4;
  [[maybe_unused]] size_t v33 = -2;
  [[maybe_unused]] size_t v34 = 1024;
  [[maybe_unused]] size_t v35 = 512;
  [[maybe_unused]] size_t v36 = 256;
  [[maybe_unused]] size_t v37 = 128;
  [[maybe_unused]] size_t v38 = 64;
  [[maybe_unused]] size_t v39 = 8;
  [[maybe_unused]] size_t v40 = 10;
  [[maybe_unused]] size_t v41 = -64;
  [[maybe_unused]] size_t v42 = 16;
  [[maybe_unused]] size_t v43 = 18;
  [[maybe_unused]] size_t v44 = 24;
  [[maybe_unused]] size_t v45 = 26;
  [[maybe_unused]] size_t v46 = -128;
  [[maybe_unused]] size_t v47 = -256;
  [[maybe_unused]] size_t v48 = 1;
  [[maybe_unused]] size_t v49 = 3;
  const auto& ct = v0[0];
  auto ct1 = cc->EvalRotate(ct, -16);
  cc->EvalAddInPlace(ct1, ct);
  auto ct3 = cc->EvalRotate(ct1, -32);
  cc->EvalAddInPlace(ct3, ct1);
  const auto& ct5 = v1[0];
  auto ct6 = cc->EvalRotate(ct5, -1);
  cc->EvalAddInPlace(ct6, ct5);
  const auto& digit_decomp = cc->EvalFastRotationPrecompute(ct6);
  Plaintext pt = v2[0];
  auto ct8 = cc->EvalMult(ct6, pt);
  Plaintext pt1 = v2[1];
  Plaintext pt2 = v2[2];
  auto ct9 = cc->EvalMult(ct3, pt2);
  cc->ModReduceInPlace(ct9);
  Plaintext pt3 = v2[3];
  std::vector<CiphertextT> v50(31);
  #pragma omp parallel for
  for (auto v52 = 0; v52 < 31; ++v52) {
    size_t v54 = v3[v52];
    const auto& ct11 = cc->EvalFastRotation(ct6, v54, 2 * cc->GetRingDimension(), digit_decomp);
    const std::vector<CiphertextT> v55 = {ct11};
    v50[v52] = v55[0];
  }
  const auto& ct12 = v50[0];
  const auto& ct13 = v50[1];
  const auto& ct14 = v50[2];
  const auto& ct15 = v50[3];
  const auto& ct16 = v50[4];
  const auto& ct17 = v50[5];
  const auto& ct18 = v50[6];
  const auto& ct19 = v50[7];
  const auto& ct20 = v50[8];
  const auto& ct21 = v50[9];
  const auto& ct22 = v50[10];
  const auto& ct23 = v50[11];
  const auto& ct24 = v50[12];
  const auto& ct25 = v50[13];
  const auto& ct26 = v50[14];
  const auto& ct27 = v50[15];
  const auto& ct28 = v50[16];
  const auto& ct29 = v50[17];
  const auto& ct30 = v50[18];
  const auto& ct31 = v50[19];
  const auto& ct32 = v50[20];
  const auto& ct33 = v50[21];
  const auto& ct34 = v50[22];
  const auto& ct35 = v50[23];
  const auto& ct36 = v50[24];
  const auto& ct37 = v50[25];
  const auto& ct38 = v50[26];
  const auto& ct39 = v50[27];
  const auto& ct40 = v50[28];
  const auto& ct41 = v50[29];
  const auto& ct42 = v50[30];
  const auto& ct43 = cc->EvalMult(ct42, pt1);
  std::vector<CiphertextT> v56(1);
  const auto& ct44 = cc->EvalMult(ct17, pt1);
  auto ct45 = cc->EvalMult(ct23, pt);
  const auto& ct46 = cc->EvalMult(ct16, pt1);
  cc->EvalAddInPlace(ct45, ct46);
  const auto& ct48 = cc->EvalRotate(ct45, -16);
  cc->EvalAddInPlace(ct8, ct44);
  cc->EvalAddInPlace(ct8, ct48);
  auto ct51 = cc->EvalRotate(ct8, -8);
  cc->EvalAddInPlace(ct51, ct8);
  auto ct53 = cc->EvalRotate(ct51, -4);
  cc->EvalAddInPlace(ct53, ct51);
  auto ct55 = cc->EvalRotate(ct53, -2);
  cc->EvalAddInPlace(ct55, ct53);
  cc->ModReduceInPlace(ct55);
  auto ct58 = cc->EvalMultNoRelin(ct9, ct55);
  cc->RelinearizeInPlace(ct58);
  auto ct60 = cc->EvalRotate(ct58, 1024);
  cc->EvalAddInPlace(ct60, ct58);
  auto ct62 = cc->EvalRotate(ct60, 512);
  cc->EvalAddInPlace(ct62, ct60);
  auto ct64 = cc->EvalRotate(ct62, 256);
  cc->EvalAddInPlace(ct64, ct62);
  auto ct66 = cc->EvalRotate(ct64, 128);
  cc->EvalAddInPlace(ct66, ct64);
  auto ct68 = cc->EvalRotate(ct66, 64);
  cc->EvalAddInPlace(ct68, ct66);
  cc->ModReduceInPlace(ct68);
  auto ct71 = cc->EvalMult(ct68, pt3);
  auto ct72 = cc->EvalMult(ct13, pt);
  const auto& ct73 = cc->EvalMult(ct12, pt1);
  auto ct74 = cc->EvalMult(ct15, pt);
  const auto& ct75 = cc->EvalMult(ct14, pt1);
  cc->EvalAddInPlace(ct74, ct75);
  const auto& ct77 = cc->EvalRotate(ct74, -16);
  cc->EvalAddInPlace(ct72, ct73);
  cc->EvalAddInPlace(ct72, ct77);
  auto ct80 = cc->EvalRotate(ct72, -8);
  cc->EvalAddInPlace(ct80, ct72);
  auto ct82 = cc->EvalRotate(ct80, -4);
  cc->EvalAddInPlace(ct82, ct80);
  auto ct84 = cc->EvalRotate(ct82, -2);
  cc->EvalAddInPlace(ct84, ct82);
  cc->ModReduceInPlace(ct84);
  auto ct87 = cc->EvalMultNoRelin(ct9, ct84);
  cc->RelinearizeInPlace(ct87);
  auto ct89 = cc->EvalRotate(ct87, 1024);
  cc->EvalAddInPlace(ct89, ct87);
  auto ct91 = cc->EvalRotate(ct89, 512);
  cc->EvalAddInPlace(ct91, ct89);
  auto ct93 = cc->EvalRotate(ct91, 256);
  cc->EvalAddInPlace(ct93, ct91);
  auto ct95 = cc->EvalRotate(ct93, 128);
  cc->EvalAddInPlace(ct95, ct93);
  auto ct97 = cc->EvalRotate(ct95, 64);
  cc->EvalAddInPlace(ct97, ct95);
  cc->ModReduceInPlace(ct97);
  const auto& ct100 = cc->EvalMult(ct97, pt3);
  const auto& ct101 = cc->EvalRotate(ct100, -64);
  auto ct102 = cc->EvalMult(ct40, pt);
  const auto& ct103 = cc->EvalMult(ct30, pt1);
  auto ct104 = cc->EvalMult(ct41, pt);
  const auto& ct105 = cc->EvalMult(ct25, pt1);
  cc->EvalAddInPlace(ct104, ct105);
  const auto& ct107 = cc->EvalRotate(ct104, -16);
  cc->EvalAddInPlace(ct102, ct103);
  cc->EvalAddInPlace(ct102, ct107);
  auto ct110 = cc->EvalRotate(ct102, -8);
  cc->EvalAddInPlace(ct110, ct102);
  auto ct112 = cc->EvalRotate(ct110, -4);
  cc->EvalAddInPlace(ct112, ct110);
  auto ct114 = cc->EvalRotate(ct112, -2);
  cc->EvalAddInPlace(ct114, ct112);
  cc->ModReduceInPlace(ct114);
  auto ct117 = cc->EvalMultNoRelin(ct9, ct114);
  cc->RelinearizeInPlace(ct117);
  auto ct119 = cc->EvalRotate(ct117, 1024);
  cc->EvalAddInPlace(ct119, ct117);
  auto ct121 = cc->EvalRotate(ct119, 512);
  cc->EvalAddInPlace(ct121, ct119);
  auto ct123 = cc->EvalRotate(ct121, 256);
  cc->EvalAddInPlace(ct123, ct121);
  auto ct125 = cc->EvalRotate(ct123, 128);
  cc->EvalAddInPlace(ct125, ct123);
  auto ct127 = cc->EvalRotate(ct125, 64);
  cc->EvalAddInPlace(ct127, ct125);
  cc->ModReduceInPlace(ct127);
  const auto& ct130 = cc->EvalMult(ct127, pt3);
  auto ct131 = cc->EvalMult(ct36, pt);
  const auto& ct132 = cc->EvalMult(ct21, pt1);
  auto ct133 = cc->EvalMult(ct27, pt);
  const auto& ct134 = cc->EvalMult(ct22, pt1);
  cc->EvalAddInPlace(ct133, ct134);
  const auto& ct136 = cc->EvalRotate(ct133, -16);
  cc->EvalAddInPlace(ct131, ct132);
  cc->EvalAddInPlace(ct131, ct136);
  auto ct139 = cc->EvalRotate(ct131, -8);
  cc->EvalAddInPlace(ct139, ct131);
  auto ct141 = cc->EvalRotate(ct139, -4);
  cc->EvalAddInPlace(ct141, ct139);
  auto ct143 = cc->EvalRotate(ct141, -2);
  cc->EvalAddInPlace(ct143, ct141);
  cc->ModReduceInPlace(ct143);
  auto ct146 = cc->EvalMultNoRelin(ct9, ct143);
  cc->RelinearizeInPlace(ct146);
  auto ct148 = cc->EvalRotate(ct146, 1024);
  cc->EvalAddInPlace(ct148, ct146);
  auto ct150 = cc->EvalRotate(ct148, 512);
  cc->EvalAddInPlace(ct150, ct148);
  auto ct152 = cc->EvalRotate(ct150, 256);
  cc->EvalAddInPlace(ct152, ct150);
  auto ct154 = cc->EvalRotate(ct152, 128);
  cc->EvalAddInPlace(ct154, ct152);
  auto ct156 = cc->EvalRotate(ct154, 64);
  cc->EvalAddInPlace(ct156, ct154);
  cc->ModReduceInPlace(ct156);
  const auto& ct159 = cc->EvalMult(ct156, pt3);
  auto ct160 = cc->EvalRotate(ct130, -128);
  const auto& ct161 = cc->EvalRotate(ct159, -192);
  auto ct162 = cc->EvalMult(ct19, pt);
  const auto& ct163 = cc->EvalMult(ct35, pt1);
  auto ct164 = cc->EvalMult(ct20, pt);
  const auto& ct165 = cc->EvalMult(ct32, pt1);
  cc->EvalAddInPlace(ct164, ct165);
  const auto& ct167 = cc->EvalRotate(ct164, -16);
  cc->EvalAddInPlace(ct162, ct163);
  cc->EvalAddInPlace(ct162, ct167);
  auto ct170 = cc->EvalRotate(ct162, -8);
  cc->EvalAddInPlace(ct170, ct162);
  auto ct172 = cc->EvalRotate(ct170, -4);
  cc->EvalAddInPlace(ct172, ct170);
  auto ct174 = cc->EvalRotate(ct172, -2);
  cc->EvalAddInPlace(ct174, ct172);
  cc->ModReduceInPlace(ct174);
  auto ct177 = cc->EvalMultNoRelin(ct9, ct174);
  cc->RelinearizeInPlace(ct177);
  auto ct179 = cc->EvalRotate(ct177, 1024);
  cc->EvalAddInPlace(ct179, ct177);
  auto ct181 = cc->EvalRotate(ct179, 512);
  cc->EvalAddInPlace(ct181, ct179);
  auto ct183 = cc->EvalRotate(ct181, 256);
  cc->EvalAddInPlace(ct183, ct181);
  auto ct185 = cc->EvalRotate(ct183, 128);
  cc->EvalAddInPlace(ct185, ct183);
  auto ct187 = cc->EvalRotate(ct185, 64);
  cc->EvalAddInPlace(ct187, ct185);
  cc->ModReduceInPlace(ct187);
  auto ct190 = cc->EvalMult(ct187, pt3);
  auto ct191 = cc->EvalMult(ct34, pt);
  const auto& ct192 = cc->EvalMult(ct26, pt1);
  auto ct193 = cc->EvalMult(ct37, pt);
  const auto& ct194 = cc->EvalMult(ct33, pt1);
  cc->EvalAddInPlace(ct193, ct194);
  const auto& ct196 = cc->EvalRotate(ct193, -16);
  cc->EvalAddInPlace(ct191, ct192);
  cc->EvalAddInPlace(ct191, ct196);
  auto ct199 = cc->EvalRotate(ct191, -8);
  cc->EvalAddInPlace(ct199, ct191);
  auto ct201 = cc->EvalRotate(ct199, -4);
  cc->EvalAddInPlace(ct201, ct199);
  auto ct203 = cc->EvalRotate(ct201, -2);
  cc->EvalAddInPlace(ct203, ct201);
  cc->ModReduceInPlace(ct203);
  auto ct206 = cc->EvalMultNoRelin(ct9, ct203);
  cc->RelinearizeInPlace(ct206);
  auto ct208 = cc->EvalRotate(ct206, 1024);
  cc->EvalAddInPlace(ct208, ct206);
  auto ct210 = cc->EvalRotate(ct208, 512);
  cc->EvalAddInPlace(ct210, ct208);
  auto ct212 = cc->EvalRotate(ct210, 256);
  cc->EvalAddInPlace(ct212, ct210);
  auto ct214 = cc->EvalRotate(ct212, 128);
  cc->EvalAddInPlace(ct214, ct212);
  auto ct216 = cc->EvalRotate(ct214, 64);
  cc->EvalAddInPlace(ct216, ct214);
  cc->ModReduceInPlace(ct216);
  const auto& ct219 = cc->EvalMult(ct216, pt3);
  const auto& ct220 = cc->EvalRotate(ct219, -64);
  auto ct221 = cc->EvalMult(ct39, pt);
  const auto& ct222 = cc->EvalMult(ct31, pt1);
  auto ct223 = cc->EvalMult(ct38, pt);
  const auto& ct224 = cc->EvalMult(ct28, pt1);
  cc->EvalAddInPlace(ct223, ct224);
  const auto& ct226 = cc->EvalRotate(ct223, -16);
  cc->EvalAddInPlace(ct221, ct222);
  cc->EvalAddInPlace(ct221, ct226);
  auto ct229 = cc->EvalRotate(ct221, -8);
  cc->EvalAddInPlace(ct229, ct221);
  auto ct231 = cc->EvalRotate(ct229, -4);
  cc->EvalAddInPlace(ct231, ct229);
  auto ct233 = cc->EvalRotate(ct231, -2);
  cc->EvalAddInPlace(ct233, ct231);
  cc->ModReduceInPlace(ct233);
  auto ct236 = cc->EvalMultNoRelin(ct9, ct233);
  cc->RelinearizeInPlace(ct236);
  auto ct238 = cc->EvalRotate(ct236, 1024);
  cc->EvalAddInPlace(ct238, ct236);
  auto ct240 = cc->EvalRotate(ct238, 512);
  cc->EvalAddInPlace(ct240, ct238);
  auto ct242 = cc->EvalRotate(ct240, 256);
  cc->EvalAddInPlace(ct242, ct240);
  auto ct244 = cc->EvalRotate(ct242, 128);
  cc->EvalAddInPlace(ct244, ct242);
  auto ct246 = cc->EvalRotate(ct244, 64);
  cc->EvalAddInPlace(ct246, ct244);
  cc->ModReduceInPlace(ct246);
  const auto& ct249 = cc->EvalMult(ct246, pt3);
  auto ct250 = cc->EvalMult(ct29, pt);
  const auto& ct251 = cc->EvalMult(ct18, pt1);
  auto ct252 = cc->EvalMult(ct24, pt);
  cc->EvalAddInPlace(ct252, ct43);
  const auto& ct254 = cc->EvalRotate(ct252, -16);
  cc->EvalAddInPlace(ct250, ct251);
  cc->EvalAddInPlace(ct250, ct254);
  auto ct257 = cc->EvalRotate(ct250, -8);
  cc->EvalAddInPlace(ct257, ct250);
  auto ct259 = cc->EvalRotate(ct257, -4);
  cc->EvalAddInPlace(ct259, ct257);
  auto ct261 = cc->EvalRotate(ct259, -2);
  cc->EvalAddInPlace(ct261, ct259);
  cc->ModReduceInPlace(ct261);
  auto ct264 = cc->EvalMultNoRelin(ct9, ct261);
  cc->RelinearizeInPlace(ct264);
  auto ct266 = cc->EvalRotate(ct264, 1024);
  cc->EvalAddInPlace(ct266, ct264);
  auto ct268 = cc->EvalRotate(ct266, 512);
  cc->EvalAddInPlace(ct268, ct266);
  auto ct270 = cc->EvalRotate(ct268, 256);
  cc->EvalAddInPlace(ct270, ct268);
  auto ct272 = cc->EvalRotate(ct270, 128);
  cc->EvalAddInPlace(ct272, ct270);
  auto ct274 = cc->EvalRotate(ct272, 64);
  cc->EvalAddInPlace(ct274, ct272);
  cc->ModReduceInPlace(ct274);
  const auto& ct277 = cc->EvalMult(ct274, pt3);
  auto ct278 = cc->EvalRotate(ct249, -128);
  const auto& ct279 = cc->EvalRotate(ct277, -192);
  cc->EvalAddInPlace(ct190, ct220);
  cc->EvalAddInPlace(ct278, ct279);
  cc->EvalAddInPlace(ct190, ct278);
  const auto& ct283 = cc->EvalRotate(ct190, -256);
  cc->EvalAddInPlace(ct71, ct101);
  cc->EvalAddInPlace(ct160, ct161);
  cc->EvalAddInPlace(ct160, ct283);
  cc->EvalAddInPlace(ct71, ct160);
  cc->ModReduceInPlace(ct71);
  v56[0] = ct71;
  return v56;
}
std::vector<CiphertextT> matmul_secret(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<CiphertextT> v1) {
  const auto& v2 = matmul_secret__preprocessing(cc);
  const auto& v3 = matmul_secret__preprocessed(cc, v0, v1, v2);
  return v3;
}
std::vector<CiphertextT> matmul_secret__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] int32_t v1 = 2048;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(2048, 0);
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v4;
  for (auto v7 = 0; v7 < 2048; v7 += 1) {
    size_t v9 = static_cast<size_t>(v7);
    float v10 = v0[v9 + 2048 * (0)];
    v6[v9 + 2048 * (0)] = v10;
  }
  std::vector<float> v12(1 * 2048);
  for (int64_t v12_i0 = 0; v12_i0 < 1; ++v12_i0) {
    for (int64_t v12_i1 = 0; v12_i1 < 2048; ++v12_i1) {
      v12[v12_i1 + 2048 * (v12_i0)] = v6[0 + v12_i1 * 1 + 2048 * (0 + v12_i0 * 1)];
    }
  }
  std::vector<double> v13(std::begin(v12), std::end(v12));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v13;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v13[i % v13.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  const auto& ct = cc->Encrypt(pk, pt);
  const std::vector<CiphertextT> v14 = {ct};
  return v14;
}
std::vector<CiphertextT> matmul_secret__encrypt__arg1(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] int32_t v1 = 2048;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(2048, 0);
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v4;
  for (auto v7 = 0; v7 < 2048; v7 += 1) {
    size_t v9 = static_cast<size_t>(v7);
    float v10 = v0[v9 + 2048 * (0)];
    v6[v9 + 2048 * (0)] = v10;
  }
  std::vector<float> v12(1 * 2048);
  for (int64_t v12_i0 = 0; v12_i0 < 1; ++v12_i0) {
    for (int64_t v12_i1 = 0; v12_i1 < 2048; ++v12_i1) {
      v12[v12_i1 + 2048 * (v12_i0)] = v6[0 + v12_i1 * 1 + 2048 * (0 + v12_i0 * 1)];
    }
  }
  std::vector<double> v13(std::begin(v12), std::end(v12));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v13;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v13[i % v13.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  const auto& ct = cc->Encrypt(pk, pt);
  const std::vector<CiphertextT> v14 = {ct};
  return v14;
}
std::vector<float> matmul_secret__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk) {
  std::vector<float> v1(2048, 0);
  [[maybe_unused]] int32_t v2 = 0;
  [[maybe_unused]] int32_t v3 = 2047;
  [[maybe_unused]] int32_t v4 = 1;
  [[maybe_unused]] int32_t v5 = 2048;
  [[maybe_unused]] size_t v6 = 0;
  const auto& ct = v0[0];
  PlaintextT pt;
  cc->Decrypt(sk, ct, &pt);
  pt->SetLength(2048);
  const auto& v7_cast = pt->GetCKKSPackedValue();
  std::vector<float> v7(v7_cast.size());
  std::transform(std::begin(v7_cast), std::end(v7_cast), std::begin(v7), [](const std::complex<double>& c) { return c.real(); });
  std::vector<float> v8 = v1;
  for (auto v9 = 0; v9 < 2048; v9 += 1) {
    int32_t v11 = v3 - v9;
    size_t v12 = static_cast<size_t>(v11);
    float v13 = v7[v12 + 2048 * (0)];
    v8[v12 + 2048 * (0)] = v13;
  }
  return v8;
}
CryptoContextT matmul_secret__generate_crypto_context() {
  CCParamsT params;
  params.SetMultiplicativeDepth(3);
  params.SetFirstModSize(55);
  params.SetScalingModSize(45);
  params.SetKeySwitchTechnique(HYBRID);
  CryptoContextT cc = GenCryptoContext(params);
  cc->Enable(PKE);
  cc->Enable(KEYSWITCH);
  cc->Enable(LEVELEDSHE);
  return cc;
}
CryptoContextT matmul_secret__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk) {
  cc->EvalMultKeyGen(sk);
  cc->EvalRotateKeyGen(sk, {1024, 512, 256, 128, 64, -64, -12, 26, -128, -192, 2, 40, 14, 28, -10, -256, 16, 42, 4, 30, -8, 56, 18, -1, -20, 6, -32, 32, 58, 20, -18, 8, 34, -4, 22, -16, 48, 10, -28, -2, 24, 50, 12, -26});
  return cc;
}
