
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

std::vector<float> _assign_layout_16269634747298775998(std::vector<float> v0) {
  [[maybe_unused]] int32_t v1 = 1;
  [[maybe_unused]] int32_t v2 = 0;
  std::vector<float> v3(4096, 0);
  [[maybe_unused]] int32_t v4 = 64;
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v3;
  for (auto v7 = 0; v7 < 64; v7 += 1) {
    for (auto v10 = 0; v10 < 64; v10 += 1) {
      int32_t v12 = v7 * v4;
      int32_t v13 = v12 + v10;
      size_t v14 = static_cast<size_t>(v7);
      size_t v15 = static_cast<size_t>(v10);
      float v16 = v0[v15 + 64 * (v14)];
      size_t v17 = static_cast<size_t>(v13);
      v6[v17 + 4096 * (0)] = v16;
    }
  }
  return v6;
}
std::vector<Plaintext> matvec_64__preprocessing(CryptoContextT cc, std::vector<float> v0) {
  [[maybe_unused]] size_t v1 = 0;
  std::vector<Plaintext> v2(1);
  std::vector<float> v3(4096);
  std::vector<float> v4 = v3;
  for (auto v5 = 0; v5 < 64; ++v5) {
    for (auto v8 = 0; v8 < 64; ++v8) {
      float v10 = v0[v8];
      v4[v8 + 64 * (v5)] = v10;
      v4 = v4;
    }
    v4 = v4;
  }
  const auto& v12 = _assign_layout_16269634747298775998(v4);
  std::vector<float> v13(1 * 4096);
  for (int64_t v13_i0 = 0; v13_i0 < 1; ++v13_i0) {
    for (int64_t v13_i1 = 0; v13_i1 < 4096; ++v13_i1) {
      v13[v13_i1 + 4096 * (v13_i0)] = v12[0 + v13_i1 * 1 + 4096 * (0 + v13_i0 * 1)];
    }
  }
  std::vector<double> v14(std::begin(v13), std::end(v13));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v14;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v14[i % v14.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  v2[0] = pt;
  return v2;
}
std::vector<CiphertextT> matvec_64__preprocessed(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1, const std::vector<Plaintext>& v2) {
  [[maybe_unused]] size_t v3 = 0;
  [[maybe_unused]] size_t v4 = 1;
  [[maybe_unused]] size_t v5 = 2;
  [[maybe_unused]] size_t v6 = 4;
  [[maybe_unused]] size_t v7 = 8;
  [[maybe_unused]] size_t v8 = 16;
  [[maybe_unused]] size_t v9 = 32;
  Plaintext pt = v2[0];
  const auto& ct = v0[0];
  auto ct1 = cc->EvalMult(ct, pt);
  const auto& ct2 = cc->EvalRotate(ct1, 1);
  cc->EvalAddInPlace(ct1, ct2);
  const auto& ct4 = cc->EvalRotate(ct1, 2);
  cc->EvalAddInPlace(ct1, ct4);
  const auto& ct6 = cc->EvalRotate(ct1, 4);
  cc->EvalAddInPlace(ct1, ct6);
  const auto& ct8 = cc->EvalRotate(ct1, 8);
  cc->EvalAddInPlace(ct1, ct8);
  const auto& ct10 = cc->EvalRotate(ct1, 16);
  cc->EvalAddInPlace(ct1, ct10);
  const auto& ct12 = cc->EvalRotate(ct1, 32);
  cc->EvalAddInPlace(ct1, ct12);
  std::vector<CiphertextT> v10(1);
  cc->ModReduceInPlace(ct1);
  v10[0] = ct1;
  return v10;
}
std::vector<CiphertextT> matvec_64(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1) {
  const auto& v2 = matvec_64__preprocessing(cc, v1);
  const auto& v3 = matvec_64__preprocessed(cc, v0, v1, v2);
  return v3;
}
std::vector<CiphertextT> matvec_64__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] int32_t v1 = 1;
  [[maybe_unused]] int32_t v2 = 0;
  std::vector<float> v3(4096, 0);
  [[maybe_unused]] int32_t v4 = 64;
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v3;
  for (auto v7 = 0; v7 < 64; v7 += 1) {
    for (auto v10 = 0; v10 < 64; v10 += 1) {
      int32_t v12 = v7 * v4;
      int32_t v13 = v12 + v10;
      size_t v14 = static_cast<size_t>(v7);
      size_t v15 = static_cast<size_t>(v10);
      float v16 = v0[v15 + 64 * (v14)];
      size_t v17 = static_cast<size_t>(v13);
      v6[v17 + 4096 * (0)] = v16;
    }
  }
  std::vector<float> v19(1 * 4096);
  for (int64_t v19_i0 = 0; v19_i0 < 1; ++v19_i0) {
    for (int64_t v19_i1 = 0; v19_i1 < 4096; ++v19_i1) {
      v19[v19_i1 + 4096 * (v19_i0)] = v6[0 + v19_i1 * 1 + 4096 * (0 + v19_i0 * 1)];
    }
  }
  std::vector<double> v20(std::begin(v19), std::end(v19));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v20;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v20[i % v20.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  const auto& ct = cc->Encrypt(pk, pt);
  const std::vector<CiphertextT> v21 = {ct};
  return v21;
}
std::vector<float> matvec_64__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk) {
  std::vector<float> v1(64, 0);
  [[maybe_unused]] int32_t v2 = 0;
  [[maybe_unused]] int32_t v3 = 63;
  [[maybe_unused]] int32_t v4 = 1;
  [[maybe_unused]] int32_t v5 = 64;
  [[maybe_unused]] size_t v6 = 0;
  const auto& ct = v0[0];
  PlaintextT pt;
  cc->Decrypt(sk, ct, &pt);
  pt->SetLength(4096);
  const auto& v7_cast = pt->GetCKKSPackedValue();
  std::vector<float> v7(v7_cast.size());
  std::transform(std::begin(v7_cast), std::end(v7_cast), std::begin(v7), [](const std::complex<double>& c) { return c.real(); });
  std::vector<float> v8 = v1;
  for (auto v9 = 0; v9 < 64; v9 += 1) {
    int32_t v11 = v3 - v9;
    int32_t v12 = v11 * v5;
    int32_t v13 = v12 + v3;
    int32_t v14 = v12 + v5;
    for (auto v16 = v12; v16 < v14; v16 += 1) {
      int32_t v18 = v16 - v12;
      int32_t v19 = v13 - v18;
      size_t v20 = static_cast<size_t>(v19);
      float v21 = v7[v20 + 4096 * (0)];
      size_t v22 = static_cast<size_t>(v11);
      v8[v22] = v21;
    }
  }
  return v8;
}
CryptoContextT matvec_64__generate_crypto_context() {
  CCParamsT params;
  params.SetMultiplicativeDepth(1);
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
