
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

std::vector<float> _assign_layout_14017645792964032966(std::vector<float> v0) {
  [[maybe_unused]] int32_t v1 = 1024;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(1024, 0);
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v4;
  for (auto v7 = 0; v7 < 1024; v7 += 1) {
    size_t v9 = static_cast<size_t>(v7);
    float v10 = v0[v9 + 1024 * (0)];
    v6[v9 + 1024 * (0)] = v10;
  }
  return v6;
}
std::vector<Plaintext> matmul_pt__preprocessing(CryptoContextT cc, std::vector<float> v0) {
  std::vector<float> v1 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  [[maybe_unused]] size_t v2 = 0;
  [[maybe_unused]] size_t v3 = 1;
  [[maybe_unused]] size_t v4 = 2;
  [[maybe_unused]] size_t v5 = 3;
  [[maybe_unused]] size_t v6 = 4;
  std::vector<Plaintext> v7(5);
  std::vector<float> v8(1 * 1024);
  for (int64_t v8_i0 = 0; v8_i0 < 1; ++v8_i0) {
    for (int64_t v8_i1 = 0; v8_i1 < 1024; ++v8_i1) {
      v8[v8_i1 + 1024 * (v8_i0)] = v0[0 + v8_i1 * 1 + 1024 * (0 + v8_i0 * 1)];
    }
  }
  std::vector<float> v9(1 * 1024);
  for (int64_t v9_i0 = 0; v9_i0 < 1; ++v9_i0) {
    for (int64_t v9_i1 = 0; v9_i1 < 1024; ++v9_i1) {
      v9[v9_i1 + 1024 * (v9_i0)] = v0[0 + v9_i1 * 1 + 1024 * (1 + v9_i0 * 1)];
    }
  }
  std::vector<float> v10(1 * 1024);
  for (int64_t v10_i0 = 0; v10_i0 < 1; ++v10_i0) {
    for (int64_t v10_i1 = 0; v10_i1 < 1024; ++v10_i1) {
      v10[v10_i1 + 1024 * (v10_i0)] = v0[0 + v10_i1 * 1 + 1024 * (2 + v10_i0 * 1)];
    }
  }
  std::vector<float> v11(1 * 1024);
  for (int64_t v11_i0 = 0; v11_i0 < 1; ++v11_i0) {
    for (int64_t v11_i1 = 0; v11_i1 < 1024; ++v11_i1) {
      v11[v11_i1 + 1024 * (v11_i0)] = v0[0 + v11_i1 * 1 + 1024 * (3 + v11_i0 * 1)];
    }
  }
  const auto& v12 = _assign_layout_14017645792964032966(v8);
  const auto& v13 = _assign_layout_14017645792964032966(v9);
  const auto& v14 = _assign_layout_14017645792964032966(v10);
  const auto& v15 = _assign_layout_14017645792964032966(v11);
  const auto& v16 = _assign_layout_14017645792964032966(v1);
  std::vector<float> v17(1 * 1024);
  for (int64_t v17_i0 = 0; v17_i0 < 1; ++v17_i0) {
    for (int64_t v17_i1 = 0; v17_i1 < 1024; ++v17_i1) {
      v17[v17_i1 + 1024 * (v17_i0)] = v12[0 + v17_i1 * 1 + 1024 * (0 + v17_i0 * 1)];
    }
  }
  std::vector<double> v18(std::begin(v17), std::end(v17));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v18;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v18[i % v18.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  v7[0] = pt;
  std::vector<float> v19(1 * 1024);
  for (int64_t v19_i0 = 0; v19_i0 < 1; ++v19_i0) {
    for (int64_t v19_i1 = 0; v19_i1 < 1024; ++v19_i1) {
      v19[v19_i1 + 1024 * (v19_i0)] = v13[0 + v19_i1 * 1 + 1024 * (0 + v19_i0 * 1)];
    }
  }
  std::vector<double> v20(std::begin(v19), std::end(v19));
  auto pt1_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt1_filled = v20;
  pt1_filled.clear();
  pt1_filled.reserve(pt1_filled_n);
  for (auto i = 0; i < pt1_filled_n; ++i) {
    pt1_filled.push_back(v20[i % v20.size()]);
  }
  auto pt1 = cc->MakeCKKSPackedPlaintext(pt1_filled);
  v7[1] = pt1;
  std::vector<float> v21(1 * 1024);
  for (int64_t v21_i0 = 0; v21_i0 < 1; ++v21_i0) {
    for (int64_t v21_i1 = 0; v21_i1 < 1024; ++v21_i1) {
      v21[v21_i1 + 1024 * (v21_i0)] = v14[0 + v21_i1 * 1 + 1024 * (0 + v21_i0 * 1)];
    }
  }
  std::vector<double> v22(std::begin(v21), std::end(v21));
  auto pt2_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt2_filled = v22;
  pt2_filled.clear();
  pt2_filled.reserve(pt2_filled_n);
  for (auto i = 0; i < pt2_filled_n; ++i) {
    pt2_filled.push_back(v22[i % v22.size()]);
  }
  auto pt2 = cc->MakeCKKSPackedPlaintext(pt2_filled);
  v7[2] = pt2;
  std::vector<float> v23(1 * 1024);
  for (int64_t v23_i0 = 0; v23_i0 < 1; ++v23_i0) {
    for (int64_t v23_i1 = 0; v23_i1 < 1024; ++v23_i1) {
      v23[v23_i1 + 1024 * (v23_i0)] = v15[0 + v23_i1 * 1 + 1024 * (0 + v23_i0 * 1)];
    }
  }
  std::vector<double> v24(std::begin(v23), std::end(v23));
  auto pt3_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt3_filled = v24;
  pt3_filled.clear();
  pt3_filled.reserve(pt3_filled_n);
  for (auto i = 0; i < pt3_filled_n; ++i) {
    pt3_filled.push_back(v24[i % v24.size()]);
  }
  auto pt3 = cc->MakeCKKSPackedPlaintext(pt3_filled);
  v7[3] = pt3;
  std::vector<float> v25(1 * 1024);
  for (int64_t v25_i0 = 0; v25_i0 < 1; ++v25_i0) {
    for (int64_t v25_i1 = 0; v25_i1 < 1024; ++v25_i1) {
      v25[v25_i1 + 1024 * (v25_i0)] = v16[0 + v25_i1 * 1 + 1024 * (0 + v25_i0 * 1)];
    }
  }
  std::vector<double> v26(std::begin(v25), std::end(v25));
  auto pt4_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt4_filled = v26;
  pt4_filled.clear();
  pt4_filled.reserve(pt4_filled_n);
  for (auto i = 0; i < pt4_filled_n; ++i) {
    pt4_filled.push_back(v26[i % v26.size()]);
  }
  auto pt4 = cc->MakeCKKSPackedPlaintext(pt4_filled);
  v7[4] = pt4;
  return v7;
}
std::vector<CiphertextT> matmul_pt__preprocessed(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1, const std::vector<Plaintext>& v2) {
  [[maybe_unused]] size_t v3 = 0;
  [[maybe_unused]] size_t v4 = -1;
  [[maybe_unused]] size_t v5 = -2;
  [[maybe_unused]] size_t v6 = 256;
  [[maybe_unused]] size_t v7 = 512;
  [[maybe_unused]] size_t v8 = 64;
  [[maybe_unused]] size_t v9 = 128;
  [[maybe_unused]] size_t v10 = 1;
  [[maybe_unused]] size_t v11 = 2;
  [[maybe_unused]] size_t v12 = 3;
  [[maybe_unused]] size_t v13 = 4;
  const auto& ct = v0[0];
  auto ct1 = cc->EvalRotate(ct, -1);
  cc->EvalAddInPlace(ct1, ct);
  auto ct3 = cc->EvalRotate(ct1, -2);
  cc->EvalAddInPlace(ct3, ct1);
  Plaintext pt = v2[0];
  auto ct5 = cc->EvalMult(ct3, pt);
  const auto& ct6 = cc->EvalRotate(ct3, 256);
  Plaintext pt1 = v2[1];
  const auto& ct7 = cc->EvalMult(ct6, pt1);
  Plaintext pt2 = v2[2];
  auto ct8 = cc->EvalMult(ct3, pt2);
  Plaintext pt3 = v2[3];
  const auto& ct9 = cc->EvalMult(ct6, pt3);
  cc->EvalAddInPlace(ct8, ct9);
  const auto& ct11 = cc->EvalRotate(ct8, 512);
  cc->EvalAddInPlace(ct5, ct7);
  cc->EvalAddInPlace(ct5, ct11);
  auto ct14 = cc->EvalRotate(ct5, 64);
  cc->EvalAddInPlace(ct14, ct5);
  auto ct16 = cc->EvalRotate(ct14, 128);
  cc->EvalAddInPlace(ct16, ct14);
  cc->ModReduceInPlace(ct16);
  Plaintext pt4 = v2[4];
  auto ct19 = cc->EvalMult(ct16, pt4);
  std::vector<CiphertextT> v14(1);
  cc->ModReduceInPlace(ct19);
  v14[0] = ct19;
  return v14;
}
std::vector<CiphertextT> matmul_pt(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1) {
  const auto& v2 = matmul_pt__preprocessing(cc, v1);
  const auto& v3 = matmul_pt__preprocessed(cc, v0, v1, v2);
  return v3;
}
std::vector<CiphertextT> matmul_pt__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  [[maybe_unused]] int32_t v1 = 1024;
  [[maybe_unused]] int32_t v2 = 1;
  [[maybe_unused]] int32_t v3 = 0;
  std::vector<float> v4(1024, 0);
  [[maybe_unused]] size_t v5 = 0;
  std::vector<float> v6 = v4;
  for (auto v7 = 0; v7 < 1024; v7 += 1) {
    size_t v9 = static_cast<size_t>(v7);
    float v10 = v0[v9 + 1024 * (0)];
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
std::vector<float> matmul_pt__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk) {
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
    v8[v12 + 1024 * (0)] = v13;
  }
  return v8;
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
  cc->EvalRotateKeyGen(sk, {256, 512, 64, 128, -1, -2});
  return cc;
}
