
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

std::vector<CiphertextT> vecsum(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<CiphertextT> v1) {
  [[maybe_unused]] size_t v2 = 0;
  std::vector<CiphertextT> v3(1);
  auto ct = v0[0];
  const auto& ct1 = v1[0];
  cc->EvalAddInPlace(ct, ct1);
  v3[0] = ct;
  return v3;
}
std::vector<CiphertextT> vecsum__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] int32_t v1 = 1024;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(1024, 0);
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v4;
  for (auto v7 = 0; v7 < 1024; v7 += 1) {
    size_t v9 = static_cast<size_t>(v7);
    float v10 = v0[v9];
    v6[v9 + 1024 * (0)] = v10;
  }
  std::vector<float> v12(1 * 1024);
  for (int64_t v12_i0 = 0; v12_i0 < 1; ++v12_i0) {
    for (int64_t v12_i1 = 0; v12_i1 < 1024; ++v12_i1) {
      v12[v12_i1 + 1024 * (v12_i0)] = v6[0 + v12_i1 * 1 + 1024 * (0 + v12_i0 * 1)];
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
std::vector<CiphertextT> vecsum__encrypt__arg1(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] int32_t v1 = 1024;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(1024, 0);
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v4;
  for (auto v7 = 0; v7 < 1024; v7 += 1) {
    size_t v9 = static_cast<size_t>(v7);
    float v10 = v0[v9];
    v6[v9 + 1024 * (0)] = v10;
  }
  std::vector<float> v12(1 * 1024);
  for (int64_t v12_i0 = 0; v12_i0 < 1; ++v12_i0) {
    for (int64_t v12_i1 = 0; v12_i1 < 1024; ++v12_i1) {
      v12[v12_i1 + 1024 * (v12_i0)] = v6[0 + v12_i1 * 1 + 1024 * (0 + v12_i0 * 1)];
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
std::vector<float> vecsum__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk) {
  std::vector<float> v1(1024, 0);
  [[maybe_unused]] int32_t v2 = 0;
  [[maybe_unused]] int32_t v3 = 1023;
  [[maybe_unused]] int32_t v4 = 1;
  [[maybe_unused]] int32_t v5 = 1024;
  [[maybe_unused]] size_t v6 = 0;
  const auto& ct = v0[0];
  PlaintextT pt;
  cc->Decrypt(sk, ct, &pt);
  pt->SetLength(1024);
  const auto& v7_cast = pt->GetCKKSPackedValue();
  std::vector<float> v7(v7_cast.size());
  std::transform(std::begin(v7_cast), std::end(v7_cast), std::begin(v7), [](const std::complex<double>& c) { return c.real(); });
  std::vector<float> v8 = v1;
  for (auto v9 = 0; v9 < 1024; v9 += 1) {
    int32_t v11 = v3 - v9;
    size_t v12 = static_cast<size_t>(v11);
    float v13 = v7[v12 + 1024 * (0)];
    v8[v12] = v13;
  }
  return v8;
}
CryptoContextT vecsum__generate_crypto_context() {
  CCParamsT params;
  params.SetMultiplicativeDepth(0);
  params.SetFirstModSize(55);
  params.SetScalingModSize(45);
  params.SetKeySwitchTechnique(HYBRID);
  CryptoContextT cc = GenCryptoContext(params);
  cc->Enable(PKE);
  cc->Enable(KEYSWITCH);
  cc->Enable(LEVELEDSHE);
  return cc;
}
CryptoContextT vecsum__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk) {
  return cc;
}
