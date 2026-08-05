
#include "openfhe.h"  // from @openfhe

using namespace lbcrypto;
using CiphertextT = Ciphertext<DCRTPoly>;
using ConstCiphertextT = ConstCiphertext<DCRTPoly>;
using CCParamsT = CCParams<CryptoContextCKKSRNS>;
using CryptoContextT = CryptoContext<DCRTPoly>;
using EvalKeyT = EvalKey<DCRTPoly>;
using PlaintextT = Plaintext;
using PrivateKeyT = PrivateKey<DCRTPoly>;
using PublicKeyT = PublicKey<DCRTPoly>;

std::vector<CiphertextT> bert_attention(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1, std::vector<float> v2) {
  std::vector<size_t> v3 = {448, 384, 320, 256, 192, 128, 64};
  std::vector<size_t> v4 = {128, 64, 192, 320, 256, 448, 384};
  [[maybe_unused]] size_t v5 = 6;
  [[maybe_unused]] size_t v6 = 5;
  [[maybe_unused]] size_t v7 = 4;
  [[maybe_unused]] size_t v8 = 3;
  [[maybe_unused]] size_t v9 = 2;
  [[maybe_unused]] size_t v10 = 1;
  [[maybe_unused]] size_t v11 = 0;
  [[maybe_unused]] size_t v12 = 3584;
  [[maybe_unused]] size_t v13 = 3072;
  [[maybe_unused]] size_t v14 = 2560;
  [[maybe_unused]] size_t v15 = 2048;
  [[maybe_unused]] size_t v16 = 1536;
  [[maybe_unused]] size_t v17 = 1024;
  [[maybe_unused]] size_t v18 = 512;
  std::vector<float> v19(4096);
  for (int64_t v19_i0 = 0; v19_i0 < 1; ++v19_i0) {
    for (int64_t v19_i1 = 0; v19_i1 < 4096; ++v19_i1) {
      v19[v19_i1 + 4096 * (v19_i0)] = v1[0 + v19_i1 * 1 + 4096 * (0 + v19_i0 * 1)];
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
  const auto& ct = v0[0];
  const auto& digit_decomp = cc->EvalFastRotationPrecompute(ct);
  auto ct1 = cc->EvalMult(ct, pt);
  std::vector<float> v21(4096);
  for (int64_t v21_i0 = 0; v21_i0 < 1; ++v21_i0) {
    for (int64_t v21_i1 = 0; v21_i1 < 4096; ++v21_i1) {
      v21[v21_i1 + 4096 * (v21_i0)] = v1[0 + v21_i1 * 1 + 4096 * (1 + v21_i0 * 1)];
    }
  }
  std::vector<double> v22(std::begin(v21), std::end(v21));
  auto pt1_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt1_filled = v22;
  pt1_filled.clear();
  pt1_filled.reserve(pt1_filled_n);
  for (auto i = 0; i < pt1_filled_n; ++i) {
    pt1_filled.push_back(v22[i % v22.size()]);
  }
  auto pt1 = cc->MakeCKKSPackedPlaintext(pt1_filled);
  std::vector<float> v23(4096);
  for (int64_t v23_i0 = 0; v23_i0 < 1; ++v23_i0) {
    for (int64_t v23_i1 = 0; v23_i1 < 4096; ++v23_i1) {
      v23[v23_i1 + 4096 * (v23_i0)] = v1[0 + v23_i1 * 1 + 4096 * (2 + v23_i0 * 1)];
    }
  }
  std::vector<double> v24(std::begin(v23), std::end(v23));
  auto pt2_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt2_filled = v24;
  pt2_filled.clear();
  pt2_filled.reserve(pt2_filled_n);
  for (auto i = 0; i < pt2_filled_n; ++i) {
    pt2_filled.push_back(v24[i % v24.size()]);
  }
  auto pt2 = cc->MakeCKKSPackedPlaintext(pt2_filled);
  std::vector<float> v25(4096);
  for (int64_t v25_i0 = 0; v25_i0 < 1; ++v25_i0) {
    for (int64_t v25_i1 = 0; v25_i1 < 4096; ++v25_i1) {
      v25[v25_i1 + 4096 * (v25_i0)] = v1[0 + v25_i1 * 1 + 4096 * (3 + v25_i0 * 1)];
    }
  }
  std::vector<double> v26(std::begin(v25), std::end(v25));
  auto pt3_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt3_filled = v26;
  pt3_filled.clear();
  pt3_filled.reserve(pt3_filled_n);
  for (auto i = 0; i < pt3_filled_n; ++i) {
    pt3_filled.push_back(v26[i % v26.size()]);
  }
  auto pt3 = cc->MakeCKKSPackedPlaintext(pt3_filled);
  std::vector<float> v27(4096);
  for (int64_t v27_i0 = 0; v27_i0 < 1; ++v27_i0) {
    for (int64_t v27_i1 = 0; v27_i1 < 4096; ++v27_i1) {
      v27[v27_i1 + 4096 * (v27_i0)] = v1[0 + v27_i1 * 1 + 4096 * (4 + v27_i0 * 1)];
    }
  }
  std::vector<double> v28(std::begin(v27), std::end(v27));
  auto pt4_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt4_filled = v28;
  pt4_filled.clear();
  pt4_filled.reserve(pt4_filled_n);
  for (auto i = 0; i < pt4_filled_n; ++i) {
    pt4_filled.push_back(v28[i % v28.size()]);
  }
  auto pt4 = cc->MakeCKKSPackedPlaintext(pt4_filled);
  std::vector<float> v29(4096);
  for (int64_t v29_i0 = 0; v29_i0 < 1; ++v29_i0) {
    for (int64_t v29_i1 = 0; v29_i1 < 4096; ++v29_i1) {
      v29[v29_i1 + 4096 * (v29_i0)] = v1[0 + v29_i1 * 1 + 4096 * (5 + v29_i0 * 1)];
    }
  }
  std::vector<double> v30(std::begin(v29), std::end(v29));
  auto pt5_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt5_filled = v30;
  pt5_filled.clear();
  pt5_filled.reserve(pt5_filled_n);
  for (auto i = 0; i < pt5_filled_n; ++i) {
    pt5_filled.push_back(v30[i % v30.size()]);
  }
  auto pt5 = cc->MakeCKKSPackedPlaintext(pt5_filled);
  std::vector<CiphertextT> v31(7);
  std::vector<float> v32(4096);
  for (int64_t v32_i0 = 0; v32_i0 < 1; ++v32_i0) {
    for (int64_t v32_i1 = 0; v32_i1 < 4096; ++v32_i1) {
      v32[v32_i1 + 4096 * (v32_i0)] = v1[0 + v32_i1 * 1 + 4096 * (6 + v32_i0 * 1)];
    }
  }
  std::vector<double> v33(std::begin(v32), std::end(v32));
  auto pt6_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt6_filled = v33;
  pt6_filled.clear();
  pt6_filled.reserve(pt6_filled_n);
  for (auto i = 0; i < pt6_filled_n; ++i) {
    pt6_filled.push_back(v33[i % v33.size()]);
  }
  auto pt6 = cc->MakeCKKSPackedPlaintext(pt6_filled);
  std::vector<float> v34(4096);
  for (int64_t v34_i0 = 0; v34_i0 < 1; ++v34_i0) {
    for (int64_t v34_i1 = 0; v34_i1 < 4096; ++v34_i1) {
      v34[v34_i1 + 4096 * (v34_i0)] = v1[0 + v34_i1 * 1 + 4096 * (7 + v34_i0 * 1)];
    }
  }
  std::vector<double> v35(std::begin(v34), std::end(v34));
  auto pt7_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt7_filled = v35;
  pt7_filled.clear();
  pt7_filled.reserve(pt7_filled_n);
  for (auto i = 0; i < pt7_filled_n; ++i) {
    pt7_filled.push_back(v35[i % v35.size()]);
  }
  auto pt7 = cc->MakeCKKSPackedPlaintext(pt7_filled);
  std::vector<float> v36(4096);
  for (int64_t v36_i0 = 0; v36_i0 < 1; ++v36_i0) {
    for (int64_t v36_i1 = 0; v36_i1 < 4096; ++v36_i1) {
      v36[v36_i1 + 4096 * (v36_i0)] = v1[0 + v36_i1 * 1 + 4096 * (8 + v36_i0 * 1)];
    }
  }
  std::vector<double> v37(std::begin(v36), std::end(v36));
  auto pt8_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt8_filled = v37;
  pt8_filled.clear();
  pt8_filled.reserve(pt8_filled_n);
  for (auto i = 0; i < pt8_filled_n; ++i) {
    pt8_filled.push_back(v37[i % v37.size()]);
  }
  auto pt8 = cc->MakeCKKSPackedPlaintext(pt8_filled);
  auto ct2 = cc->EvalMult(ct, pt8);
  std::vector<float> v38(4096);
  for (int64_t v38_i0 = 0; v38_i0 < 1; ++v38_i0) {
    for (int64_t v38_i1 = 0; v38_i1 < 4096; ++v38_i1) {
      v38[v38_i1 + 4096 * (v38_i0)] = v1[0 + v38_i1 * 1 + 4096 * (9 + v38_i0 * 1)];
    }
  }
  std::vector<double> v39(std::begin(v38), std::end(v38));
  auto pt9_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt9_filled = v39;
  pt9_filled.clear();
  pt9_filled.reserve(pt9_filled_n);
  for (auto i = 0; i < pt9_filled_n; ++i) {
    pt9_filled.push_back(v39[i % v39.size()]);
  }
  auto pt9 = cc->MakeCKKSPackedPlaintext(pt9_filled);
  std::vector<float> v40(4096);
  for (int64_t v40_i0 = 0; v40_i0 < 1; ++v40_i0) {
    for (int64_t v40_i1 = 0; v40_i1 < 4096; ++v40_i1) {
      v40[v40_i1 + 4096 * (v40_i0)] = v1[0 + v40_i1 * 1 + 4096 * (10 + v40_i0 * 1)];
    }
  }
  std::vector<double> v41(std::begin(v40), std::end(v40));
  auto pt10_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt10_filled = v41;
  pt10_filled.clear();
  pt10_filled.reserve(pt10_filled_n);
  for (auto i = 0; i < pt10_filled_n; ++i) {
    pt10_filled.push_back(v41[i % v41.size()]);
  }
  auto pt10 = cc->MakeCKKSPackedPlaintext(pt10_filled);
  std::vector<float> v42(4096);
  for (int64_t v42_i0 = 0; v42_i0 < 1; ++v42_i0) {
    for (int64_t v42_i1 = 0; v42_i1 < 4096; ++v42_i1) {
      v42[v42_i1 + 4096 * (v42_i0)] = v1[0 + v42_i1 * 1 + 4096 * (11 + v42_i0 * 1)];
    }
  }
  std::vector<double> v43(std::begin(v42), std::end(v42));
  auto pt11_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt11_filled = v43;
  pt11_filled.clear();
  pt11_filled.reserve(pt11_filled_n);
  for (auto i = 0; i < pt11_filled_n; ++i) {
    pt11_filled.push_back(v43[i % v43.size()]);
  }
  auto pt11 = cc->MakeCKKSPackedPlaintext(pt11_filled);
  std::vector<float> v44(4096);
  for (int64_t v44_i0 = 0; v44_i0 < 1; ++v44_i0) {
    for (int64_t v44_i1 = 0; v44_i1 < 4096; ++v44_i1) {
      v44[v44_i1 + 4096 * (v44_i0)] = v1[0 + v44_i1 * 1 + 4096 * (12 + v44_i0 * 1)];
    }
  }
  std::vector<double> v45(std::begin(v44), std::end(v44));
  auto pt12_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt12_filled = v45;
  pt12_filled.clear();
  pt12_filled.reserve(pt12_filled_n);
  for (auto i = 0; i < pt12_filled_n; ++i) {
    pt12_filled.push_back(v45[i % v45.size()]);
  }
  auto pt12 = cc->MakeCKKSPackedPlaintext(pt12_filled);
  std::vector<float> v46(4096);
  for (int64_t v46_i0 = 0; v46_i0 < 1; ++v46_i0) {
    for (int64_t v46_i1 = 0; v46_i1 < 4096; ++v46_i1) {
      v46[v46_i1 + 4096 * (v46_i0)] = v1[0 + v46_i1 * 1 + 4096 * (13 + v46_i0 * 1)];
    }
  }
  std::vector<double> v47(std::begin(v46), std::end(v46));
  auto pt13_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt13_filled = v47;
  pt13_filled.clear();
  pt13_filled.reserve(pt13_filled_n);
  for (auto i = 0; i < pt13_filled_n; ++i) {
    pt13_filled.push_back(v47[i % v47.size()]);
  }
  auto pt13 = cc->MakeCKKSPackedPlaintext(pt13_filled);
  std::vector<float> v48(4096);
  for (int64_t v48_i0 = 0; v48_i0 < 1; ++v48_i0) {
    for (int64_t v48_i1 = 0; v48_i1 < 4096; ++v48_i1) {
      v48[v48_i1 + 4096 * (v48_i0)] = v1[0 + v48_i1 * 1 + 4096 * (14 + v48_i0 * 1)];
    }
  }
  std::vector<double> v49(std::begin(v48), std::end(v48));
  auto pt14_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt14_filled = v49;
  pt14_filled.clear();
  pt14_filled.reserve(pt14_filled_n);
  for (auto i = 0; i < pt14_filled_n; ++i) {
    pt14_filled.push_back(v49[i % v49.size()]);
  }
  auto pt14 = cc->MakeCKKSPackedPlaintext(pt14_filled);
  std::vector<float> v50(4096);
  for (int64_t v50_i0 = 0; v50_i0 < 1; ++v50_i0) {
    for (int64_t v50_i1 = 0; v50_i1 < 4096; ++v50_i1) {
      v50[v50_i1 + 4096 * (v50_i0)] = v1[0 + v50_i1 * 1 + 4096 * (15 + v50_i0 * 1)];
    }
  }
  std::vector<double> v51(std::begin(v50), std::end(v50));
  auto pt15_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt15_filled = v51;
  pt15_filled.clear();
  pt15_filled.reserve(pt15_filled_n);
  for (auto i = 0; i < pt15_filled_n; ++i) {
    pt15_filled.push_back(v51[i % v51.size()]);
  }
  auto pt15 = cc->MakeCKKSPackedPlaintext(pt15_filled);
  std::vector<float> v52(4096);
  for (int64_t v52_i0 = 0; v52_i0 < 1; ++v52_i0) {
    for (int64_t v52_i1 = 0; v52_i1 < 4096; ++v52_i1) {
      v52[v52_i1 + 4096 * (v52_i0)] = v1[0 + v52_i1 * 1 + 4096 * (16 + v52_i0 * 1)];
    }
  }
  std::vector<double> v53(std::begin(v52), std::end(v52));
  auto pt16_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt16_filled = v53;
  pt16_filled.clear();
  pt16_filled.reserve(pt16_filled_n);
  for (auto i = 0; i < pt16_filled_n; ++i) {
    pt16_filled.push_back(v53[i % v53.size()]);
  }
  auto pt16 = cc->MakeCKKSPackedPlaintext(pt16_filled);
  auto ct3 = cc->EvalMult(ct, pt16);
  std::vector<float> v54(4096);
  for (int64_t v54_i0 = 0; v54_i0 < 1; ++v54_i0) {
    for (int64_t v54_i1 = 0; v54_i1 < 4096; ++v54_i1) {
      v54[v54_i1 + 4096 * (v54_i0)] = v1[0 + v54_i1 * 1 + 4096 * (17 + v54_i0 * 1)];
    }
  }
  std::vector<double> v55(std::begin(v54), std::end(v54));
  auto pt17_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt17_filled = v55;
  pt17_filled.clear();
  pt17_filled.reserve(pt17_filled_n);
  for (auto i = 0; i < pt17_filled_n; ++i) {
    pt17_filled.push_back(v55[i % v55.size()]);
  }
  auto pt17 = cc->MakeCKKSPackedPlaintext(pt17_filled);
  std::vector<float> v56(4096);
  for (int64_t v56_i0 = 0; v56_i0 < 1; ++v56_i0) {
    for (int64_t v56_i1 = 0; v56_i1 < 4096; ++v56_i1) {
      v56[v56_i1 + 4096 * (v56_i0)] = v1[0 + v56_i1 * 1 + 4096 * (18 + v56_i0 * 1)];
    }
  }
  std::vector<double> v57(std::begin(v56), std::end(v56));
  auto pt18_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt18_filled = v57;
  pt18_filled.clear();
  pt18_filled.reserve(pt18_filled_n);
  for (auto i = 0; i < pt18_filled_n; ++i) {
    pt18_filled.push_back(v57[i % v57.size()]);
  }
  auto pt18 = cc->MakeCKKSPackedPlaintext(pt18_filled);
  std::vector<float> v58(4096);
  for (int64_t v58_i0 = 0; v58_i0 < 1; ++v58_i0) {
    for (int64_t v58_i1 = 0; v58_i1 < 4096; ++v58_i1) {
      v58[v58_i1 + 4096 * (v58_i0)] = v1[0 + v58_i1 * 1 + 4096 * (19 + v58_i0 * 1)];
    }
  }
  std::vector<double> v59(std::begin(v58), std::end(v58));
  auto pt19_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt19_filled = v59;
  pt19_filled.clear();
  pt19_filled.reserve(pt19_filled_n);
  for (auto i = 0; i < pt19_filled_n; ++i) {
    pt19_filled.push_back(v59[i % v59.size()]);
  }
  auto pt19 = cc->MakeCKKSPackedPlaintext(pt19_filled);
  std::vector<float> v60(4096);
  for (int64_t v60_i0 = 0; v60_i0 < 1; ++v60_i0) {
    for (int64_t v60_i1 = 0; v60_i1 < 4096; ++v60_i1) {
      v60[v60_i1 + 4096 * (v60_i0)] = v1[0 + v60_i1 * 1 + 4096 * (20 + v60_i0 * 1)];
    }
  }
  std::vector<double> v61(std::begin(v60), std::end(v60));
  auto pt20_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt20_filled = v61;
  pt20_filled.clear();
  pt20_filled.reserve(pt20_filled_n);
  for (auto i = 0; i < pt20_filled_n; ++i) {
    pt20_filled.push_back(v61[i % v61.size()]);
  }
  auto pt20 = cc->MakeCKKSPackedPlaintext(pt20_filled);
  std::vector<float> v62(4096);
  for (int64_t v62_i0 = 0; v62_i0 < 1; ++v62_i0) {
    for (int64_t v62_i1 = 0; v62_i1 < 4096; ++v62_i1) {
      v62[v62_i1 + 4096 * (v62_i0)] = v1[0 + v62_i1 * 1 + 4096 * (21 + v62_i0 * 1)];
    }
  }
  std::vector<double> v63(std::begin(v62), std::end(v62));
  auto pt21_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt21_filled = v63;
  pt21_filled.clear();
  pt21_filled.reserve(pt21_filled_n);
  for (auto i = 0; i < pt21_filled_n; ++i) {
    pt21_filled.push_back(v63[i % v63.size()]);
  }
  auto pt21 = cc->MakeCKKSPackedPlaintext(pt21_filled);
  std::vector<float> v64(4096);
  for (int64_t v64_i0 = 0; v64_i0 < 1; ++v64_i0) {
    for (int64_t v64_i1 = 0; v64_i1 < 4096; ++v64_i1) {
      v64[v64_i1 + 4096 * (v64_i0)] = v1[0 + v64_i1 * 1 + 4096 * (22 + v64_i0 * 1)];
    }
  }
  std::vector<double> v65(std::begin(v64), std::end(v64));
  auto pt22_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt22_filled = v65;
  pt22_filled.clear();
  pt22_filled.reserve(pt22_filled_n);
  for (auto i = 0; i < pt22_filled_n; ++i) {
    pt22_filled.push_back(v65[i % v65.size()]);
  }
  auto pt22 = cc->MakeCKKSPackedPlaintext(pt22_filled);
  std::vector<float> v66(4096);
  for (int64_t v66_i0 = 0; v66_i0 < 1; ++v66_i0) {
    for (int64_t v66_i1 = 0; v66_i1 < 4096; ++v66_i1) {
      v66[v66_i1 + 4096 * (v66_i0)] = v1[0 + v66_i1 * 1 + 4096 * (23 + v66_i0 * 1)];
    }
  }
  std::vector<double> v67(std::begin(v66), std::end(v66));
  auto pt23_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt23_filled = v67;
  pt23_filled.clear();
  pt23_filled.reserve(pt23_filled_n);
  for (auto i = 0; i < pt23_filled_n; ++i) {
    pt23_filled.push_back(v67[i % v67.size()]);
  }
  auto pt23 = cc->MakeCKKSPackedPlaintext(pt23_filled);
  std::vector<float> v68(4096);
  for (int64_t v68_i0 = 0; v68_i0 < 1; ++v68_i0) {
    for (int64_t v68_i1 = 0; v68_i1 < 4096; ++v68_i1) {
      v68[v68_i1 + 4096 * (v68_i0)] = v1[0 + v68_i1 * 1 + 4096 * (24 + v68_i0 * 1)];
    }
  }
  std::vector<double> v69(std::begin(v68), std::end(v68));
  auto pt24_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt24_filled = v69;
  pt24_filled.clear();
  pt24_filled.reserve(pt24_filled_n);
  for (auto i = 0; i < pt24_filled_n; ++i) {
    pt24_filled.push_back(v69[i % v69.size()]);
  }
  auto pt24 = cc->MakeCKKSPackedPlaintext(pt24_filled);
  auto ct4 = cc->EvalMult(ct, pt24);
  std::vector<float> v70(4096);
  for (int64_t v70_i0 = 0; v70_i0 < 1; ++v70_i0) {
    for (int64_t v70_i1 = 0; v70_i1 < 4096; ++v70_i1) {
      v70[v70_i1 + 4096 * (v70_i0)] = v1[0 + v70_i1 * 1 + 4096 * (25 + v70_i0 * 1)];
    }
  }
  std::vector<double> v71(std::begin(v70), std::end(v70));
  auto pt25_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt25_filled = v71;
  pt25_filled.clear();
  pt25_filled.reserve(pt25_filled_n);
  for (auto i = 0; i < pt25_filled_n; ++i) {
    pt25_filled.push_back(v71[i % v71.size()]);
  }
  auto pt25 = cc->MakeCKKSPackedPlaintext(pt25_filled);
  std::vector<float> v72(4096);
  for (int64_t v72_i0 = 0; v72_i0 < 1; ++v72_i0) {
    for (int64_t v72_i1 = 0; v72_i1 < 4096; ++v72_i1) {
      v72[v72_i1 + 4096 * (v72_i0)] = v1[0 + v72_i1 * 1 + 4096 * (26 + v72_i0 * 1)];
    }
  }
  std::vector<double> v73(std::begin(v72), std::end(v72));
  auto pt26_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt26_filled = v73;
  pt26_filled.clear();
  pt26_filled.reserve(pt26_filled_n);
  for (auto i = 0; i < pt26_filled_n; ++i) {
    pt26_filled.push_back(v73[i % v73.size()]);
  }
  auto pt26 = cc->MakeCKKSPackedPlaintext(pt26_filled);
  std::vector<float> v74(4096);
  for (int64_t v74_i0 = 0; v74_i0 < 1; ++v74_i0) {
    for (int64_t v74_i1 = 0; v74_i1 < 4096; ++v74_i1) {
      v74[v74_i1 + 4096 * (v74_i0)] = v1[0 + v74_i1 * 1 + 4096 * (27 + v74_i0 * 1)];
    }
  }
  std::vector<double> v75(std::begin(v74), std::end(v74));
  auto pt27_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt27_filled = v75;
  pt27_filled.clear();
  pt27_filled.reserve(pt27_filled_n);
  for (auto i = 0; i < pt27_filled_n; ++i) {
    pt27_filled.push_back(v75[i % v75.size()]);
  }
  auto pt27 = cc->MakeCKKSPackedPlaintext(pt27_filled);
  std::vector<float> v76(4096);
  for (int64_t v76_i0 = 0; v76_i0 < 1; ++v76_i0) {
    for (int64_t v76_i1 = 0; v76_i1 < 4096; ++v76_i1) {
      v76[v76_i1 + 4096 * (v76_i0)] = v1[0 + v76_i1 * 1 + 4096 * (28 + v76_i0 * 1)];
    }
  }
  std::vector<double> v77(std::begin(v76), std::end(v76));
  auto pt28_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt28_filled = v77;
  pt28_filled.clear();
  pt28_filled.reserve(pt28_filled_n);
  for (auto i = 0; i < pt28_filled_n; ++i) {
    pt28_filled.push_back(v77[i % v77.size()]);
  }
  auto pt28 = cc->MakeCKKSPackedPlaintext(pt28_filled);
  std::vector<float> v78(4096);
  for (int64_t v78_i0 = 0; v78_i0 < 1; ++v78_i0) {
    for (int64_t v78_i1 = 0; v78_i1 < 4096; ++v78_i1) {
      v78[v78_i1 + 4096 * (v78_i0)] = v1[0 + v78_i1 * 1 + 4096 * (29 + v78_i0 * 1)];
    }
  }
  std::vector<double> v79(std::begin(v78), std::end(v78));
  auto pt29_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt29_filled = v79;
  pt29_filled.clear();
  pt29_filled.reserve(pt29_filled_n);
  for (auto i = 0; i < pt29_filled_n; ++i) {
    pt29_filled.push_back(v79[i % v79.size()]);
  }
  auto pt29 = cc->MakeCKKSPackedPlaintext(pt29_filled);
  std::vector<float> v80(4096);
  for (int64_t v80_i0 = 0; v80_i0 < 1; ++v80_i0) {
    for (int64_t v80_i1 = 0; v80_i1 < 4096; ++v80_i1) {
      v80[v80_i1 + 4096 * (v80_i0)] = v1[0 + v80_i1 * 1 + 4096 * (30 + v80_i0 * 1)];
    }
  }
  std::vector<double> v81(std::begin(v80), std::end(v80));
  auto pt30_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt30_filled = v81;
  pt30_filled.clear();
  pt30_filled.reserve(pt30_filled_n);
  for (auto i = 0; i < pt30_filled_n; ++i) {
    pt30_filled.push_back(v81[i % v81.size()]);
  }
  auto pt30 = cc->MakeCKKSPackedPlaintext(pt30_filled);
  std::vector<float> v82(4096);
  for (int64_t v82_i0 = 0; v82_i0 < 1; ++v82_i0) {
    for (int64_t v82_i1 = 0; v82_i1 < 4096; ++v82_i1) {
      v82[v82_i1 + 4096 * (v82_i0)] = v1[0 + v82_i1 * 1 + 4096 * (31 + v82_i0 * 1)];
    }
  }
  std::vector<double> v83(std::begin(v82), std::end(v82));
  auto pt31_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt31_filled = v83;
  pt31_filled.clear();
  pt31_filled.reserve(pt31_filled_n);
  for (auto i = 0; i < pt31_filled_n; ++i) {
    pt31_filled.push_back(v83[i % v83.size()]);
  }
  auto pt31 = cc->MakeCKKSPackedPlaintext(pt31_filled);
  std::vector<float> v84(4096);
  for (int64_t v84_i0 = 0; v84_i0 < 1; ++v84_i0) {
    for (int64_t v84_i1 = 0; v84_i1 < 4096; ++v84_i1) {
      v84[v84_i1 + 4096 * (v84_i0)] = v1[0 + v84_i1 * 1 + 4096 * (32 + v84_i0 * 1)];
    }
  }
  std::vector<double> v85(std::begin(v84), std::end(v84));
  auto pt32_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt32_filled = v85;
  pt32_filled.clear();
  pt32_filled.reserve(pt32_filled_n);
  for (auto i = 0; i < pt32_filled_n; ++i) {
    pt32_filled.push_back(v85[i % v85.size()]);
  }
  auto pt32 = cc->MakeCKKSPackedPlaintext(pt32_filled);
  auto ct5 = cc->EvalMult(ct, pt32);
  std::vector<float> v86(4096);
  for (int64_t v86_i0 = 0; v86_i0 < 1; ++v86_i0) {
    for (int64_t v86_i1 = 0; v86_i1 < 4096; ++v86_i1) {
      v86[v86_i1 + 4096 * (v86_i0)] = v1[0 + v86_i1 * 1 + 4096 * (33 + v86_i0 * 1)];
    }
  }
  std::vector<double> v87(std::begin(v86), std::end(v86));
  auto pt33_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt33_filled = v87;
  pt33_filled.clear();
  pt33_filled.reserve(pt33_filled_n);
  for (auto i = 0; i < pt33_filled_n; ++i) {
    pt33_filled.push_back(v87[i % v87.size()]);
  }
  auto pt33 = cc->MakeCKKSPackedPlaintext(pt33_filled);
  std::vector<float> v88(4096);
  for (int64_t v88_i0 = 0; v88_i0 < 1; ++v88_i0) {
    for (int64_t v88_i1 = 0; v88_i1 < 4096; ++v88_i1) {
      v88[v88_i1 + 4096 * (v88_i0)] = v1[0 + v88_i1 * 1 + 4096 * (34 + v88_i0 * 1)];
    }
  }
  std::vector<double> v89(std::begin(v88), std::end(v88));
  auto pt34_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt34_filled = v89;
  pt34_filled.clear();
  pt34_filled.reserve(pt34_filled_n);
  for (auto i = 0; i < pt34_filled_n; ++i) {
    pt34_filled.push_back(v89[i % v89.size()]);
  }
  auto pt34 = cc->MakeCKKSPackedPlaintext(pt34_filled);
  std::vector<float> v90(4096);
  for (int64_t v90_i0 = 0; v90_i0 < 1; ++v90_i0) {
    for (int64_t v90_i1 = 0; v90_i1 < 4096; ++v90_i1) {
      v90[v90_i1 + 4096 * (v90_i0)] = v1[0 + v90_i1 * 1 + 4096 * (35 + v90_i0 * 1)];
    }
  }
  std::vector<double> v91(std::begin(v90), std::end(v90));
  auto pt35_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt35_filled = v91;
  pt35_filled.clear();
  pt35_filled.reserve(pt35_filled_n);
  for (auto i = 0; i < pt35_filled_n; ++i) {
    pt35_filled.push_back(v91[i % v91.size()]);
  }
  auto pt35 = cc->MakeCKKSPackedPlaintext(pt35_filled);
  std::vector<float> v92(4096);
  for (int64_t v92_i0 = 0; v92_i0 < 1; ++v92_i0) {
    for (int64_t v92_i1 = 0; v92_i1 < 4096; ++v92_i1) {
      v92[v92_i1 + 4096 * (v92_i0)] = v1[0 + v92_i1 * 1 + 4096 * (36 + v92_i0 * 1)];
    }
  }
  std::vector<double> v93(std::begin(v92), std::end(v92));
  auto pt36_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt36_filled = v93;
  pt36_filled.clear();
  pt36_filled.reserve(pt36_filled_n);
  for (auto i = 0; i < pt36_filled_n; ++i) {
    pt36_filled.push_back(v93[i % v93.size()]);
  }
  auto pt36 = cc->MakeCKKSPackedPlaintext(pt36_filled);
  std::vector<float> v94(4096);
  for (int64_t v94_i0 = 0; v94_i0 < 1; ++v94_i0) {
    for (int64_t v94_i1 = 0; v94_i1 < 4096; ++v94_i1) {
      v94[v94_i1 + 4096 * (v94_i0)] = v1[0 + v94_i1 * 1 + 4096 * (37 + v94_i0 * 1)];
    }
  }
  std::vector<double> v95(std::begin(v94), std::end(v94));
  auto pt37_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt37_filled = v95;
  pt37_filled.clear();
  pt37_filled.reserve(pt37_filled_n);
  for (auto i = 0; i < pt37_filled_n; ++i) {
    pt37_filled.push_back(v95[i % v95.size()]);
  }
  auto pt37 = cc->MakeCKKSPackedPlaintext(pt37_filled);
  std::vector<float> v96(4096);
  for (int64_t v96_i0 = 0; v96_i0 < 1; ++v96_i0) {
    for (int64_t v96_i1 = 0; v96_i1 < 4096; ++v96_i1) {
      v96[v96_i1 + 4096 * (v96_i0)] = v1[0 + v96_i1 * 1 + 4096 * (38 + v96_i0 * 1)];
    }
  }
  std::vector<double> v97(std::begin(v96), std::end(v96));
  auto pt38_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt38_filled = v97;
  pt38_filled.clear();
  pt38_filled.reserve(pt38_filled_n);
  for (auto i = 0; i < pt38_filled_n; ++i) {
    pt38_filled.push_back(v97[i % v97.size()]);
  }
  auto pt38 = cc->MakeCKKSPackedPlaintext(pt38_filled);
  std::vector<float> v98(4096);
  for (int64_t v98_i0 = 0; v98_i0 < 1; ++v98_i0) {
    for (int64_t v98_i1 = 0; v98_i1 < 4096; ++v98_i1) {
      v98[v98_i1 + 4096 * (v98_i0)] = v1[0 + v98_i1 * 1 + 4096 * (39 + v98_i0 * 1)];
    }
  }
  std::vector<double> v99(std::begin(v98), std::end(v98));
  auto pt39_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt39_filled = v99;
  pt39_filled.clear();
  pt39_filled.reserve(pt39_filled_n);
  for (auto i = 0; i < pt39_filled_n; ++i) {
    pt39_filled.push_back(v99[i % v99.size()]);
  }
  auto pt39 = cc->MakeCKKSPackedPlaintext(pt39_filled);
  std::vector<float> v100(4096);
  for (int64_t v100_i0 = 0; v100_i0 < 1; ++v100_i0) {
    for (int64_t v100_i1 = 0; v100_i1 < 4096; ++v100_i1) {
      v100[v100_i1 + 4096 * (v100_i0)] = v1[0 + v100_i1 * 1 + 4096 * (40 + v100_i0 * 1)];
    }
  }
  std::vector<double> v101(std::begin(v100), std::end(v100));
  auto pt40_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt40_filled = v101;
  pt40_filled.clear();
  pt40_filled.reserve(pt40_filled_n);
  for (auto i = 0; i < pt40_filled_n; ++i) {
    pt40_filled.push_back(v101[i % v101.size()]);
  }
  auto pt40 = cc->MakeCKKSPackedPlaintext(pt40_filled);
  auto ct6 = cc->EvalMult(ct, pt40);
  std::vector<float> v102(4096);
  for (int64_t v102_i0 = 0; v102_i0 < 1; ++v102_i0) {
    for (int64_t v102_i1 = 0; v102_i1 < 4096; ++v102_i1) {
      v102[v102_i1 + 4096 * (v102_i0)] = v1[0 + v102_i1 * 1 + 4096 * (41 + v102_i0 * 1)];
    }
  }
  std::vector<double> v103(std::begin(v102), std::end(v102));
  auto pt41_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt41_filled = v103;
  pt41_filled.clear();
  pt41_filled.reserve(pt41_filled_n);
  for (auto i = 0; i < pt41_filled_n; ++i) {
    pt41_filled.push_back(v103[i % v103.size()]);
  }
  auto pt41 = cc->MakeCKKSPackedPlaintext(pt41_filled);
  std::vector<float> v104(4096);
  for (int64_t v104_i0 = 0; v104_i0 < 1; ++v104_i0) {
    for (int64_t v104_i1 = 0; v104_i1 < 4096; ++v104_i1) {
      v104[v104_i1 + 4096 * (v104_i0)] = v1[0 + v104_i1 * 1 + 4096 * (42 + v104_i0 * 1)];
    }
  }
  std::vector<double> v105(std::begin(v104), std::end(v104));
  auto pt42_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt42_filled = v105;
  pt42_filled.clear();
  pt42_filled.reserve(pt42_filled_n);
  for (auto i = 0; i < pt42_filled_n; ++i) {
    pt42_filled.push_back(v105[i % v105.size()]);
  }
  auto pt42 = cc->MakeCKKSPackedPlaintext(pt42_filled);
  std::vector<float> v106(4096);
  for (int64_t v106_i0 = 0; v106_i0 < 1; ++v106_i0) {
    for (int64_t v106_i1 = 0; v106_i1 < 4096; ++v106_i1) {
      v106[v106_i1 + 4096 * (v106_i0)] = v1[0 + v106_i1 * 1 + 4096 * (43 + v106_i0 * 1)];
    }
  }
  std::vector<double> v107(std::begin(v106), std::end(v106));
  auto pt43_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt43_filled = v107;
  pt43_filled.clear();
  pt43_filled.reserve(pt43_filled_n);
  for (auto i = 0; i < pt43_filled_n; ++i) {
    pt43_filled.push_back(v107[i % v107.size()]);
  }
  auto pt43 = cc->MakeCKKSPackedPlaintext(pt43_filled);
  std::vector<float> v108(4096);
  for (int64_t v108_i0 = 0; v108_i0 < 1; ++v108_i0) {
    for (int64_t v108_i1 = 0; v108_i1 < 4096; ++v108_i1) {
      v108[v108_i1 + 4096 * (v108_i0)] = v1[0 + v108_i1 * 1 + 4096 * (44 + v108_i0 * 1)];
    }
  }
  std::vector<double> v109(std::begin(v108), std::end(v108));
  auto pt44_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt44_filled = v109;
  pt44_filled.clear();
  pt44_filled.reserve(pt44_filled_n);
  for (auto i = 0; i < pt44_filled_n; ++i) {
    pt44_filled.push_back(v109[i % v109.size()]);
  }
  auto pt44 = cc->MakeCKKSPackedPlaintext(pt44_filled);
  std::vector<float> v110(4096);
  for (int64_t v110_i0 = 0; v110_i0 < 1; ++v110_i0) {
    for (int64_t v110_i1 = 0; v110_i1 < 4096; ++v110_i1) {
      v110[v110_i1 + 4096 * (v110_i0)] = v1[0 + v110_i1 * 1 + 4096 * (45 + v110_i0 * 1)];
    }
  }
  std::vector<double> v111(std::begin(v110), std::end(v110));
  auto pt45_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt45_filled = v111;
  pt45_filled.clear();
  pt45_filled.reserve(pt45_filled_n);
  for (auto i = 0; i < pt45_filled_n; ++i) {
    pt45_filled.push_back(v111[i % v111.size()]);
  }
  auto pt45 = cc->MakeCKKSPackedPlaintext(pt45_filled);
  std::vector<float> v112(4096);
  for (int64_t v112_i0 = 0; v112_i0 < 1; ++v112_i0) {
    for (int64_t v112_i1 = 0; v112_i1 < 4096; ++v112_i1) {
      v112[v112_i1 + 4096 * (v112_i0)] = v1[0 + v112_i1 * 1 + 4096 * (46 + v112_i0 * 1)];
    }
  }
  std::vector<double> v113(std::begin(v112), std::end(v112));
  auto pt46_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt46_filled = v113;
  pt46_filled.clear();
  pt46_filled.reserve(pt46_filled_n);
  for (auto i = 0; i < pt46_filled_n; ++i) {
    pt46_filled.push_back(v113[i % v113.size()]);
  }
  auto pt46 = cc->MakeCKKSPackedPlaintext(pt46_filled);
  std::vector<float> v114(4096);
  for (int64_t v114_i0 = 0; v114_i0 < 1; ++v114_i0) {
    for (int64_t v114_i1 = 0; v114_i1 < 4096; ++v114_i1) {
      v114[v114_i1 + 4096 * (v114_i0)] = v1[0 + v114_i1 * 1 + 4096 * (47 + v114_i0 * 1)];
    }
  }
  std::vector<double> v115(std::begin(v114), std::end(v114));
  auto pt47_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt47_filled = v115;
  pt47_filled.clear();
  pt47_filled.reserve(pt47_filled_n);
  for (auto i = 0; i < pt47_filled_n; ++i) {
    pt47_filled.push_back(v115[i % v115.size()]);
  }
  auto pt47 = cc->MakeCKKSPackedPlaintext(pt47_filled);
  std::vector<float> v116(4096);
  for (int64_t v116_i0 = 0; v116_i0 < 1; ++v116_i0) {
    for (int64_t v116_i1 = 0; v116_i1 < 4096; ++v116_i1) {
      v116[v116_i1 + 4096 * (v116_i0)] = v1[0 + v116_i1 * 1 + 4096 * (48 + v116_i0 * 1)];
    }
  }
  std::vector<double> v117(std::begin(v116), std::end(v116));
  auto pt48_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt48_filled = v117;
  pt48_filled.clear();
  pt48_filled.reserve(pt48_filled_n);
  for (auto i = 0; i < pt48_filled_n; ++i) {
    pt48_filled.push_back(v117[i % v117.size()]);
  }
  auto pt48 = cc->MakeCKKSPackedPlaintext(pt48_filled);
  auto ct7 = cc->EvalMult(ct, pt48);
  std::vector<float> v118(4096);
  for (int64_t v118_i0 = 0; v118_i0 < 1; ++v118_i0) {
    for (int64_t v118_i1 = 0; v118_i1 < 4096; ++v118_i1) {
      v118[v118_i1 + 4096 * (v118_i0)] = v1[0 + v118_i1 * 1 + 4096 * (49 + v118_i0 * 1)];
    }
  }
  std::vector<double> v119(std::begin(v118), std::end(v118));
  auto pt49_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt49_filled = v119;
  pt49_filled.clear();
  pt49_filled.reserve(pt49_filled_n);
  for (auto i = 0; i < pt49_filled_n; ++i) {
    pt49_filled.push_back(v119[i % v119.size()]);
  }
  auto pt49 = cc->MakeCKKSPackedPlaintext(pt49_filled);
  std::vector<float> v120(4096);
  for (int64_t v120_i0 = 0; v120_i0 < 1; ++v120_i0) {
    for (int64_t v120_i1 = 0; v120_i1 < 4096; ++v120_i1) {
      v120[v120_i1 + 4096 * (v120_i0)] = v1[0 + v120_i1 * 1 + 4096 * (50 + v120_i0 * 1)];
    }
  }
  std::vector<double> v121(std::begin(v120), std::end(v120));
  auto pt50_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt50_filled = v121;
  pt50_filled.clear();
  pt50_filled.reserve(pt50_filled_n);
  for (auto i = 0; i < pt50_filled_n; ++i) {
    pt50_filled.push_back(v121[i % v121.size()]);
  }
  auto pt50 = cc->MakeCKKSPackedPlaintext(pt50_filled);
  std::vector<float> v122(4096);
  for (int64_t v122_i0 = 0; v122_i0 < 1; ++v122_i0) {
    for (int64_t v122_i1 = 0; v122_i1 < 4096; ++v122_i1) {
      v122[v122_i1 + 4096 * (v122_i0)] = v1[0 + v122_i1 * 1 + 4096 * (51 + v122_i0 * 1)];
    }
  }
  std::vector<double> v123(std::begin(v122), std::end(v122));
  auto pt51_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt51_filled = v123;
  pt51_filled.clear();
  pt51_filled.reserve(pt51_filled_n);
  for (auto i = 0; i < pt51_filled_n; ++i) {
    pt51_filled.push_back(v123[i % v123.size()]);
  }
  auto pt51 = cc->MakeCKKSPackedPlaintext(pt51_filled);
  std::vector<float> v124(4096);
  for (int64_t v124_i0 = 0; v124_i0 < 1; ++v124_i0) {
    for (int64_t v124_i1 = 0; v124_i1 < 4096; ++v124_i1) {
      v124[v124_i1 + 4096 * (v124_i0)] = v1[0 + v124_i1 * 1 + 4096 * (52 + v124_i0 * 1)];
    }
  }
  std::vector<double> v125(std::begin(v124), std::end(v124));
  auto pt52_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt52_filled = v125;
  pt52_filled.clear();
  pt52_filled.reserve(pt52_filled_n);
  for (auto i = 0; i < pt52_filled_n; ++i) {
    pt52_filled.push_back(v125[i % v125.size()]);
  }
  auto pt52 = cc->MakeCKKSPackedPlaintext(pt52_filled);
  std::vector<float> v126(4096);
  for (int64_t v126_i0 = 0; v126_i0 < 1; ++v126_i0) {
    for (int64_t v126_i1 = 0; v126_i1 < 4096; ++v126_i1) {
      v126[v126_i1 + 4096 * (v126_i0)] = v1[0 + v126_i1 * 1 + 4096 * (53 + v126_i0 * 1)];
    }
  }
  std::vector<double> v127(std::begin(v126), std::end(v126));
  auto pt53_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt53_filled = v127;
  pt53_filled.clear();
  pt53_filled.reserve(pt53_filled_n);
  for (auto i = 0; i < pt53_filled_n; ++i) {
    pt53_filled.push_back(v127[i % v127.size()]);
  }
  auto pt53 = cc->MakeCKKSPackedPlaintext(pt53_filled);
  std::vector<float> v128(4096);
  for (int64_t v128_i0 = 0; v128_i0 < 1; ++v128_i0) {
    for (int64_t v128_i1 = 0; v128_i1 < 4096; ++v128_i1) {
      v128[v128_i1 + 4096 * (v128_i0)] = v1[0 + v128_i1 * 1 + 4096 * (54 + v128_i0 * 1)];
    }
  }
  std::vector<double> v129(std::begin(v128), std::end(v128));
  auto pt54_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt54_filled = v129;
  pt54_filled.clear();
  pt54_filled.reserve(pt54_filled_n);
  for (auto i = 0; i < pt54_filled_n; ++i) {
    pt54_filled.push_back(v129[i % v129.size()]);
  }
  auto pt54 = cc->MakeCKKSPackedPlaintext(pt54_filled);
  std::vector<float> v130(4096);
  for (int64_t v130_i0 = 0; v130_i0 < 1; ++v130_i0) {
    for (int64_t v130_i1 = 0; v130_i1 < 4096; ++v130_i1) {
      v130[v130_i1 + 4096 * (v130_i0)] = v1[0 + v130_i1 * 1 + 4096 * (55 + v130_i0 * 1)];
    }
  }
  std::vector<double> v131(std::begin(v130), std::end(v130));
  auto pt55_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt55_filled = v131;
  pt55_filled.clear();
  pt55_filled.reserve(pt55_filled_n);
  for (auto i = 0; i < pt55_filled_n; ++i) {
    pt55_filled.push_back(v131[i % v131.size()]);
  }
  auto pt55 = cc->MakeCKKSPackedPlaintext(pt55_filled);
  std::vector<float> v132(4096);
  for (int64_t v132_i0 = 0; v132_i0 < 1; ++v132_i0) {
    for (int64_t v132_i1 = 0; v132_i1 < 4096; ++v132_i1) {
      v132[v132_i1 + 4096 * (v132_i0)] = v1[0 + v132_i1 * 1 + 4096 * (56 + v132_i0 * 1)];
    }
  }
  std::vector<double> v133(std::begin(v132), std::end(v132));
  auto pt56_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt56_filled = v133;
  pt56_filled.clear();
  pt56_filled.reserve(pt56_filled_n);
  for (auto i = 0; i < pt56_filled_n; ++i) {
    pt56_filled.push_back(v133[i % v133.size()]);
  }
  auto pt56 = cc->MakeCKKSPackedPlaintext(pt56_filled);
  auto ct8 = cc->EvalMult(ct, pt56);
  std::vector<float> v134(4096);
  for (int64_t v134_i0 = 0; v134_i0 < 1; ++v134_i0) {
    for (int64_t v134_i1 = 0; v134_i1 < 4096; ++v134_i1) {
      v134[v134_i1 + 4096 * (v134_i0)] = v1[0 + v134_i1 * 1 + 4096 * (57 + v134_i0 * 1)];
    }
  }
  std::vector<double> v135(std::begin(v134), std::end(v134));
  auto pt57_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt57_filled = v135;
  pt57_filled.clear();
  pt57_filled.reserve(pt57_filled_n);
  for (auto i = 0; i < pt57_filled_n; ++i) {
    pt57_filled.push_back(v135[i % v135.size()]);
  }
  auto pt57 = cc->MakeCKKSPackedPlaintext(pt57_filled);
  std::vector<float> v136(4096);
  for (int64_t v136_i0 = 0; v136_i0 < 1; ++v136_i0) {
    for (int64_t v136_i1 = 0; v136_i1 < 4096; ++v136_i1) {
      v136[v136_i1 + 4096 * (v136_i0)] = v1[0 + v136_i1 * 1 + 4096 * (58 + v136_i0 * 1)];
    }
  }
  std::vector<double> v137(std::begin(v136), std::end(v136));
  auto pt58_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt58_filled = v137;
  pt58_filled.clear();
  pt58_filled.reserve(pt58_filled_n);
  for (auto i = 0; i < pt58_filled_n; ++i) {
    pt58_filled.push_back(v137[i % v137.size()]);
  }
  auto pt58 = cc->MakeCKKSPackedPlaintext(pt58_filled);
  std::vector<float> v138(4096);
  for (int64_t v138_i0 = 0; v138_i0 < 1; ++v138_i0) {
    for (int64_t v138_i1 = 0; v138_i1 < 4096; ++v138_i1) {
      v138[v138_i1 + 4096 * (v138_i0)] = v1[0 + v138_i1 * 1 + 4096 * (59 + v138_i0 * 1)];
    }
  }
  std::vector<double> v139(std::begin(v138), std::end(v138));
  auto pt59_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt59_filled = v139;
  pt59_filled.clear();
  pt59_filled.reserve(pt59_filled_n);
  for (auto i = 0; i < pt59_filled_n; ++i) {
    pt59_filled.push_back(v139[i % v139.size()]);
  }
  auto pt59 = cc->MakeCKKSPackedPlaintext(pt59_filled);
  std::vector<float> v140(4096);
  for (int64_t v140_i0 = 0; v140_i0 < 1; ++v140_i0) {
    for (int64_t v140_i1 = 0; v140_i1 < 4096; ++v140_i1) {
      v140[v140_i1 + 4096 * (v140_i0)] = v1[0 + v140_i1 * 1 + 4096 * (60 + v140_i0 * 1)];
    }
  }
  std::vector<double> v141(std::begin(v140), std::end(v140));
  auto pt60_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt60_filled = v141;
  pt60_filled.clear();
  pt60_filled.reserve(pt60_filled_n);
  for (auto i = 0; i < pt60_filled_n; ++i) {
    pt60_filled.push_back(v141[i % v141.size()]);
  }
  auto pt60 = cc->MakeCKKSPackedPlaintext(pt60_filled);
  std::vector<float> v142(4096);
  for (int64_t v142_i0 = 0; v142_i0 < 1; ++v142_i0) {
    for (int64_t v142_i1 = 0; v142_i1 < 4096; ++v142_i1) {
      v142[v142_i1 + 4096 * (v142_i0)] = v1[0 + v142_i1 * 1 + 4096 * (61 + v142_i0 * 1)];
    }
  }
  std::vector<double> v143(std::begin(v142), std::end(v142));
  auto pt61_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt61_filled = v143;
  pt61_filled.clear();
  pt61_filled.reserve(pt61_filled_n);
  for (auto i = 0; i < pt61_filled_n; ++i) {
    pt61_filled.push_back(v143[i % v143.size()]);
  }
  auto pt61 = cc->MakeCKKSPackedPlaintext(pt61_filled);
  std::vector<float> v144(4096);
  for (int64_t v144_i0 = 0; v144_i0 < 1; ++v144_i0) {
    for (int64_t v144_i1 = 0; v144_i1 < 4096; ++v144_i1) {
      v144[v144_i1 + 4096 * (v144_i0)] = v1[0 + v144_i1 * 1 + 4096 * (62 + v144_i0 * 1)];
    }
  }
  std::vector<double> v145(std::begin(v144), std::end(v144));
  auto pt62_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt62_filled = v145;
  pt62_filled.clear();
  pt62_filled.reserve(pt62_filled_n);
  for (auto i = 0; i < pt62_filled_n; ++i) {
    pt62_filled.push_back(v145[i % v145.size()]);
  }
  auto pt62 = cc->MakeCKKSPackedPlaintext(pt62_filled);
  std::vector<float> v146(4096);
  for (int64_t v146_i0 = 0; v146_i0 < 1; ++v146_i0) {
    for (int64_t v146_i1 = 0; v146_i1 < 4096; ++v146_i1) {
      v146[v146_i1 + 4096 * (v146_i0)] = v1[0 + v146_i1 * 1 + 4096 * (63 + v146_i0 * 1)];
    }
  }
  std::vector<double> v147(std::begin(v146), std::end(v146));
  auto pt63_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt63_filled = v147;
  pt63_filled.clear();
  pt63_filled.reserve(pt63_filled_n);
  for (auto i = 0; i < pt63_filled_n; ++i) {
    pt63_filled.push_back(v147[i % v147.size()]);
  }
  auto pt63 = cc->MakeCKKSPackedPlaintext(pt63_filled);
  std::vector<float> v148(4096);
  for (int64_t v148_i0 = 0; v148_i0 < 1; ++v148_i0) {
    for (int64_t v148_i1 = 0; v148_i1 < 4096; ++v148_i1) {
      v148[v148_i1 + 4096 * (v148_i0)] = v2[0 + v148_i1 * 1 + 4096 * (0 + v148_i0 * 1)];
    }
  }
  std::vector<double> v149(std::begin(v148), std::end(v148));
  auto pt64_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt64_filled = v149;
  pt64_filled.clear();
  pt64_filled.reserve(pt64_filled_n);
  for (auto i = 0; i < pt64_filled_n; ++i) {
    pt64_filled.push_back(v149[i % v149.size()]);
  }
  auto pt64 = cc->MakeCKKSPackedPlaintext(pt64_filled);
  std::vector<float> v150(4096);
  for (int64_t v150_i0 = 0; v150_i0 < 1; ++v150_i0) {
    for (int64_t v150_i1 = 0; v150_i1 < 4096; ++v150_i1) {
      v150[v150_i1 + 4096 * (v150_i0)] = v2[0 + v150_i1 * 1 + 4096 * (1 + v150_i0 * 1)];
    }
  }
  std::vector<double> v151(std::begin(v150), std::end(v150));
  auto pt65_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt65_filled = v151;
  pt65_filled.clear();
  pt65_filled.reserve(pt65_filled_n);
  for (auto i = 0; i < pt65_filled_n; ++i) {
    pt65_filled.push_back(v151[i % v151.size()]);
  }
  auto pt65 = cc->MakeCKKSPackedPlaintext(pt65_filled);
  std::vector<float> v152(4096);
  for (int64_t v152_i0 = 0; v152_i0 < 1; ++v152_i0) {
    for (int64_t v152_i1 = 0; v152_i1 < 4096; ++v152_i1) {
      v152[v152_i1 + 4096 * (v152_i0)] = v2[0 + v152_i1 * 1 + 4096 * (2 + v152_i0 * 1)];
    }
  }
  std::vector<double> v153(std::begin(v152), std::end(v152));
  auto pt66_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt66_filled = v153;
  pt66_filled.clear();
  pt66_filled.reserve(pt66_filled_n);
  for (auto i = 0; i < pt66_filled_n; ++i) {
    pt66_filled.push_back(v153[i % v153.size()]);
  }
  auto pt66 = cc->MakeCKKSPackedPlaintext(pt66_filled);
  std::vector<float> v154(4096);
  for (int64_t v154_i0 = 0; v154_i0 < 1; ++v154_i0) {
    for (int64_t v154_i1 = 0; v154_i1 < 4096; ++v154_i1) {
      v154[v154_i1 + 4096 * (v154_i0)] = v2[0 + v154_i1 * 1 + 4096 * (3 + v154_i0 * 1)];
    }
  }
  std::vector<double> v155(std::begin(v154), std::end(v154));
  auto pt67_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt67_filled = v155;
  pt67_filled.clear();
  pt67_filled.reserve(pt67_filled_n);
  for (auto i = 0; i < pt67_filled_n; ++i) {
    pt67_filled.push_back(v155[i % v155.size()]);
  }
  auto pt67 = cc->MakeCKKSPackedPlaintext(pt67_filled);
  std::vector<float> v156(4096);
  for (int64_t v156_i0 = 0; v156_i0 < 1; ++v156_i0) {
    for (int64_t v156_i1 = 0; v156_i1 < 4096; ++v156_i1) {
      v156[v156_i1 + 4096 * (v156_i0)] = v2[0 + v156_i1 * 1 + 4096 * (4 + v156_i0 * 1)];
    }
  }
  std::vector<double> v157(std::begin(v156), std::end(v156));
  auto pt68_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt68_filled = v157;
  pt68_filled.clear();
  pt68_filled.reserve(pt68_filled_n);
  for (auto i = 0; i < pt68_filled_n; ++i) {
    pt68_filled.push_back(v157[i % v157.size()]);
  }
  auto pt68 = cc->MakeCKKSPackedPlaintext(pt68_filled);
  std::vector<float> v158(4096);
  for (int64_t v158_i0 = 0; v158_i0 < 1; ++v158_i0) {
    for (int64_t v158_i1 = 0; v158_i1 < 4096; ++v158_i1) {
      v158[v158_i1 + 4096 * (v158_i0)] = v2[0 + v158_i1 * 1 + 4096 * (5 + v158_i0 * 1)];
    }
  }
  std::vector<double> v159(std::begin(v158), std::end(v158));
  auto pt69_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt69_filled = v159;
  pt69_filled.clear();
  pt69_filled.reserve(pt69_filled_n);
  for (auto i = 0; i < pt69_filled_n; ++i) {
    pt69_filled.push_back(v159[i % v159.size()]);
  }
  auto pt69 = cc->MakeCKKSPackedPlaintext(pt69_filled);
  std::vector<float> v160(4096);
  for (int64_t v160_i0 = 0; v160_i0 < 1; ++v160_i0) {
    for (int64_t v160_i1 = 0; v160_i1 < 4096; ++v160_i1) {
      v160[v160_i1 + 4096 * (v160_i0)] = v2[0 + v160_i1 * 1 + 4096 * (6 + v160_i0 * 1)];
    }
  }
  std::vector<double> v161(std::begin(v160), std::end(v160));
  auto pt70_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt70_filled = v161;
  pt70_filled.clear();
  pt70_filled.reserve(pt70_filled_n);
  for (auto i = 0; i < pt70_filled_n; ++i) {
    pt70_filled.push_back(v161[i % v161.size()]);
  }
  auto pt70 = cc->MakeCKKSPackedPlaintext(pt70_filled);
  std::vector<float> v162(4096);
  for (int64_t v162_i0 = 0; v162_i0 < 1; ++v162_i0) {
    for (int64_t v162_i1 = 0; v162_i1 < 4096; ++v162_i1) {
      v162[v162_i1 + 4096 * (v162_i0)] = v2[0 + v162_i1 * 1 + 4096 * (7 + v162_i0 * 1)];
    }
  }
  std::vector<double> v163(std::begin(v162), std::end(v162));
  auto pt71_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt71_filled = v163;
  pt71_filled.clear();
  pt71_filled.reserve(pt71_filled_n);
  for (auto i = 0; i < pt71_filled_n; ++i) {
    pt71_filled.push_back(v163[i % v163.size()]);
  }
  auto pt71 = cc->MakeCKKSPackedPlaintext(pt71_filled);
  std::vector<float> v164(4096);
  for (int64_t v164_i0 = 0; v164_i0 < 1; ++v164_i0) {
    for (int64_t v164_i1 = 0; v164_i1 < 4096; ++v164_i1) {
      v164[v164_i1 + 4096 * (v164_i0)] = v2[0 + v164_i1 * 1 + 4096 * (8 + v164_i0 * 1)];
    }
  }
  std::vector<double> v165(std::begin(v164), std::end(v164));
  auto pt72_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt72_filled = v165;
  pt72_filled.clear();
  pt72_filled.reserve(pt72_filled_n);
  for (auto i = 0; i < pt72_filled_n; ++i) {
    pt72_filled.push_back(v165[i % v165.size()]);
  }
  auto pt72 = cc->MakeCKKSPackedPlaintext(pt72_filled);
  std::vector<float> v166(4096);
  for (int64_t v166_i0 = 0; v166_i0 < 1; ++v166_i0) {
    for (int64_t v166_i1 = 0; v166_i1 < 4096; ++v166_i1) {
      v166[v166_i1 + 4096 * (v166_i0)] = v2[0 + v166_i1 * 1 + 4096 * (9 + v166_i0 * 1)];
    }
  }
  std::vector<double> v167(std::begin(v166), std::end(v166));
  auto pt73_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt73_filled = v167;
  pt73_filled.clear();
  pt73_filled.reserve(pt73_filled_n);
  for (auto i = 0; i < pt73_filled_n; ++i) {
    pt73_filled.push_back(v167[i % v167.size()]);
  }
  auto pt73 = cc->MakeCKKSPackedPlaintext(pt73_filled);
  std::vector<float> v168(4096);
  for (int64_t v168_i0 = 0; v168_i0 < 1; ++v168_i0) {
    for (int64_t v168_i1 = 0; v168_i1 < 4096; ++v168_i1) {
      v168[v168_i1 + 4096 * (v168_i0)] = v2[0 + v168_i1 * 1 + 4096 * (10 + v168_i0 * 1)];
    }
  }
  std::vector<double> v169(std::begin(v168), std::end(v168));
  auto pt74_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt74_filled = v169;
  pt74_filled.clear();
  pt74_filled.reserve(pt74_filled_n);
  for (auto i = 0; i < pt74_filled_n; ++i) {
    pt74_filled.push_back(v169[i % v169.size()]);
  }
  auto pt74 = cc->MakeCKKSPackedPlaintext(pt74_filled);
  std::vector<float> v170(4096);
  for (int64_t v170_i0 = 0; v170_i0 < 1; ++v170_i0) {
    for (int64_t v170_i1 = 0; v170_i1 < 4096; ++v170_i1) {
      v170[v170_i1 + 4096 * (v170_i0)] = v2[0 + v170_i1 * 1 + 4096 * (11 + v170_i0 * 1)];
    }
  }
  std::vector<double> v171(std::begin(v170), std::end(v170));
  auto pt75_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt75_filled = v171;
  pt75_filled.clear();
  pt75_filled.reserve(pt75_filled_n);
  for (auto i = 0; i < pt75_filled_n; ++i) {
    pt75_filled.push_back(v171[i % v171.size()]);
  }
  auto pt75 = cc->MakeCKKSPackedPlaintext(pt75_filled);
  std::vector<float> v172(4096);
  for (int64_t v172_i0 = 0; v172_i0 < 1; ++v172_i0) {
    for (int64_t v172_i1 = 0; v172_i1 < 4096; ++v172_i1) {
      v172[v172_i1 + 4096 * (v172_i0)] = v2[0 + v172_i1 * 1 + 4096 * (12 + v172_i0 * 1)];
    }
  }
  std::vector<double> v173(std::begin(v172), std::end(v172));
  auto pt76_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt76_filled = v173;
  pt76_filled.clear();
  pt76_filled.reserve(pt76_filled_n);
  for (auto i = 0; i < pt76_filled_n; ++i) {
    pt76_filled.push_back(v173[i % v173.size()]);
  }
  auto pt76 = cc->MakeCKKSPackedPlaintext(pt76_filled);
  std::vector<float> v174(4096);
  for (int64_t v174_i0 = 0; v174_i0 < 1; ++v174_i0) {
    for (int64_t v174_i1 = 0; v174_i1 < 4096; ++v174_i1) {
      v174[v174_i1 + 4096 * (v174_i0)] = v2[0 + v174_i1 * 1 + 4096 * (13 + v174_i0 * 1)];
    }
  }
  std::vector<double> v175(std::begin(v174), std::end(v174));
  auto pt77_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt77_filled = v175;
  pt77_filled.clear();
  pt77_filled.reserve(pt77_filled_n);
  for (auto i = 0; i < pt77_filled_n; ++i) {
    pt77_filled.push_back(v175[i % v175.size()]);
  }
  auto pt77 = cc->MakeCKKSPackedPlaintext(pt77_filled);
  std::vector<float> v176(4096);
  for (int64_t v176_i0 = 0; v176_i0 < 1; ++v176_i0) {
    for (int64_t v176_i1 = 0; v176_i1 < 4096; ++v176_i1) {
      v176[v176_i1 + 4096 * (v176_i0)] = v2[0 + v176_i1 * 1 + 4096 * (14 + v176_i0 * 1)];
    }
  }
  std::vector<double> v177(std::begin(v176), std::end(v176));
  auto pt78_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt78_filled = v177;
  pt78_filled.clear();
  pt78_filled.reserve(pt78_filled_n);
  for (auto i = 0; i < pt78_filled_n; ++i) {
    pt78_filled.push_back(v177[i % v177.size()]);
  }
  auto pt78 = cc->MakeCKKSPackedPlaintext(pt78_filled);
  std::vector<float> v178(4096);
  for (int64_t v178_i0 = 0; v178_i0 < 1; ++v178_i0) {
    for (int64_t v178_i1 = 0; v178_i1 < 4096; ++v178_i1) {
      v178[v178_i1 + 4096 * (v178_i0)] = v2[0 + v178_i1 * 1 + 4096 * (15 + v178_i0 * 1)];
    }
  }
  std::vector<double> v179(std::begin(v178), std::end(v178));
  auto pt79_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt79_filled = v179;
  pt79_filled.clear();
  pt79_filled.reserve(pt79_filled_n);
  for (auto i = 0; i < pt79_filled_n; ++i) {
    pt79_filled.push_back(v179[i % v179.size()]);
  }
  auto pt79 = cc->MakeCKKSPackedPlaintext(pt79_filled);
  std::vector<float> v180(4096);
  for (int64_t v180_i0 = 0; v180_i0 < 1; ++v180_i0) {
    for (int64_t v180_i1 = 0; v180_i1 < 4096; ++v180_i1) {
      v180[v180_i1 + 4096 * (v180_i0)] = v2[0 + v180_i1 * 1 + 4096 * (16 + v180_i0 * 1)];
    }
  }
  std::vector<double> v181(std::begin(v180), std::end(v180));
  auto pt80_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt80_filled = v181;
  pt80_filled.clear();
  pt80_filled.reserve(pt80_filled_n);
  for (auto i = 0; i < pt80_filled_n; ++i) {
    pt80_filled.push_back(v181[i % v181.size()]);
  }
  auto pt80 = cc->MakeCKKSPackedPlaintext(pt80_filled);
  std::vector<float> v182(4096);
  for (int64_t v182_i0 = 0; v182_i0 < 1; ++v182_i0) {
    for (int64_t v182_i1 = 0; v182_i1 < 4096; ++v182_i1) {
      v182[v182_i1 + 4096 * (v182_i0)] = v2[0 + v182_i1 * 1 + 4096 * (17 + v182_i0 * 1)];
    }
  }
  std::vector<double> v183(std::begin(v182), std::end(v182));
  auto pt81_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt81_filled = v183;
  pt81_filled.clear();
  pt81_filled.reserve(pt81_filled_n);
  for (auto i = 0; i < pt81_filled_n; ++i) {
    pt81_filled.push_back(v183[i % v183.size()]);
  }
  auto pt81 = cc->MakeCKKSPackedPlaintext(pt81_filled);
  std::vector<float> v184(4096);
  for (int64_t v184_i0 = 0; v184_i0 < 1; ++v184_i0) {
    for (int64_t v184_i1 = 0; v184_i1 < 4096; ++v184_i1) {
      v184[v184_i1 + 4096 * (v184_i0)] = v2[0 + v184_i1 * 1 + 4096 * (18 + v184_i0 * 1)];
    }
  }
  std::vector<double> v185(std::begin(v184), std::end(v184));
  auto pt82_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt82_filled = v185;
  pt82_filled.clear();
  pt82_filled.reserve(pt82_filled_n);
  for (auto i = 0; i < pt82_filled_n; ++i) {
    pt82_filled.push_back(v185[i % v185.size()]);
  }
  auto pt82 = cc->MakeCKKSPackedPlaintext(pt82_filled);
  std::vector<float> v186(4096);
  for (int64_t v186_i0 = 0; v186_i0 < 1; ++v186_i0) {
    for (int64_t v186_i1 = 0; v186_i1 < 4096; ++v186_i1) {
      v186[v186_i1 + 4096 * (v186_i0)] = v2[0 + v186_i1 * 1 + 4096 * (19 + v186_i0 * 1)];
    }
  }
  std::vector<double> v187(std::begin(v186), std::end(v186));
  auto pt83_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt83_filled = v187;
  pt83_filled.clear();
  pt83_filled.reserve(pt83_filled_n);
  for (auto i = 0; i < pt83_filled_n; ++i) {
    pt83_filled.push_back(v187[i % v187.size()]);
  }
  auto pt83 = cc->MakeCKKSPackedPlaintext(pt83_filled);
  std::vector<float> v188(4096);
  for (int64_t v188_i0 = 0; v188_i0 < 1; ++v188_i0) {
    for (int64_t v188_i1 = 0; v188_i1 < 4096; ++v188_i1) {
      v188[v188_i1 + 4096 * (v188_i0)] = v2[0 + v188_i1 * 1 + 4096 * (20 + v188_i0 * 1)];
    }
  }
  std::vector<double> v189(std::begin(v188), std::end(v188));
  auto pt84_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt84_filled = v189;
  pt84_filled.clear();
  pt84_filled.reserve(pt84_filled_n);
  for (auto i = 0; i < pt84_filled_n; ++i) {
    pt84_filled.push_back(v189[i % v189.size()]);
  }
  auto pt84 = cc->MakeCKKSPackedPlaintext(pt84_filled);
  std::vector<float> v190(4096);
  for (int64_t v190_i0 = 0; v190_i0 < 1; ++v190_i0) {
    for (int64_t v190_i1 = 0; v190_i1 < 4096; ++v190_i1) {
      v190[v190_i1 + 4096 * (v190_i0)] = v2[0 + v190_i1 * 1 + 4096 * (21 + v190_i0 * 1)];
    }
  }
  std::vector<double> v191(std::begin(v190), std::end(v190));
  auto pt85_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt85_filled = v191;
  pt85_filled.clear();
  pt85_filled.reserve(pt85_filled_n);
  for (auto i = 0; i < pt85_filled_n; ++i) {
    pt85_filled.push_back(v191[i % v191.size()]);
  }
  auto pt85 = cc->MakeCKKSPackedPlaintext(pt85_filled);
  std::vector<float> v192(4096);
  for (int64_t v192_i0 = 0; v192_i0 < 1; ++v192_i0) {
    for (int64_t v192_i1 = 0; v192_i1 < 4096; ++v192_i1) {
      v192[v192_i1 + 4096 * (v192_i0)] = v2[0 + v192_i1 * 1 + 4096 * (22 + v192_i0 * 1)];
    }
  }
  std::vector<double> v193(std::begin(v192), std::end(v192));
  auto pt86_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt86_filled = v193;
  pt86_filled.clear();
  pt86_filled.reserve(pt86_filled_n);
  for (auto i = 0; i < pt86_filled_n; ++i) {
    pt86_filled.push_back(v193[i % v193.size()]);
  }
  auto pt86 = cc->MakeCKKSPackedPlaintext(pt86_filled);
  std::vector<float> v194(4096);
  for (int64_t v194_i0 = 0; v194_i0 < 1; ++v194_i0) {
    for (int64_t v194_i1 = 0; v194_i1 < 4096; ++v194_i1) {
      v194[v194_i1 + 4096 * (v194_i0)] = v2[0 + v194_i1 * 1 + 4096 * (23 + v194_i0 * 1)];
    }
  }
  std::vector<double> v195(std::begin(v194), std::end(v194));
  auto pt87_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt87_filled = v195;
  pt87_filled.clear();
  pt87_filled.reserve(pt87_filled_n);
  for (auto i = 0; i < pt87_filled_n; ++i) {
    pt87_filled.push_back(v195[i % v195.size()]);
  }
  auto pt87 = cc->MakeCKKSPackedPlaintext(pt87_filled);
  std::vector<float> v196(4096);
  for (int64_t v196_i0 = 0; v196_i0 < 1; ++v196_i0) {
    for (int64_t v196_i1 = 0; v196_i1 < 4096; ++v196_i1) {
      v196[v196_i1 + 4096 * (v196_i0)] = v2[0 + v196_i1 * 1 + 4096 * (24 + v196_i0 * 1)];
    }
  }
  std::vector<double> v197(std::begin(v196), std::end(v196));
  auto pt88_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt88_filled = v197;
  pt88_filled.clear();
  pt88_filled.reserve(pt88_filled_n);
  for (auto i = 0; i < pt88_filled_n; ++i) {
    pt88_filled.push_back(v197[i % v197.size()]);
  }
  auto pt88 = cc->MakeCKKSPackedPlaintext(pt88_filled);
  std::vector<float> v198(4096);
  for (int64_t v198_i0 = 0; v198_i0 < 1; ++v198_i0) {
    for (int64_t v198_i1 = 0; v198_i1 < 4096; ++v198_i1) {
      v198[v198_i1 + 4096 * (v198_i0)] = v2[0 + v198_i1 * 1 + 4096 * (25 + v198_i0 * 1)];
    }
  }
  std::vector<double> v199(std::begin(v198), std::end(v198));
  auto pt89_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt89_filled = v199;
  pt89_filled.clear();
  pt89_filled.reserve(pt89_filled_n);
  for (auto i = 0; i < pt89_filled_n; ++i) {
    pt89_filled.push_back(v199[i % v199.size()]);
  }
  auto pt89 = cc->MakeCKKSPackedPlaintext(pt89_filled);
  std::vector<float> v200(4096);
  for (int64_t v200_i0 = 0; v200_i0 < 1; ++v200_i0) {
    for (int64_t v200_i1 = 0; v200_i1 < 4096; ++v200_i1) {
      v200[v200_i1 + 4096 * (v200_i0)] = v2[0 + v200_i1 * 1 + 4096 * (26 + v200_i0 * 1)];
    }
  }
  std::vector<double> v201(std::begin(v200), std::end(v200));
  auto pt90_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt90_filled = v201;
  pt90_filled.clear();
  pt90_filled.reserve(pt90_filled_n);
  for (auto i = 0; i < pt90_filled_n; ++i) {
    pt90_filled.push_back(v201[i % v201.size()]);
  }
  auto pt90 = cc->MakeCKKSPackedPlaintext(pt90_filled);
  std::vector<float> v202(4096);
  for (int64_t v202_i0 = 0; v202_i0 < 1; ++v202_i0) {
    for (int64_t v202_i1 = 0; v202_i1 < 4096; ++v202_i1) {
      v202[v202_i1 + 4096 * (v202_i0)] = v2[0 + v202_i1 * 1 + 4096 * (27 + v202_i0 * 1)];
    }
  }
  std::vector<double> v203(std::begin(v202), std::end(v202));
  auto pt91_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt91_filled = v203;
  pt91_filled.clear();
  pt91_filled.reserve(pt91_filled_n);
  for (auto i = 0; i < pt91_filled_n; ++i) {
    pt91_filled.push_back(v203[i % v203.size()]);
  }
  auto pt91 = cc->MakeCKKSPackedPlaintext(pt91_filled);
  std::vector<float> v204(4096);
  for (int64_t v204_i0 = 0; v204_i0 < 1; ++v204_i0) {
    for (int64_t v204_i1 = 0; v204_i1 < 4096; ++v204_i1) {
      v204[v204_i1 + 4096 * (v204_i0)] = v2[0 + v204_i1 * 1 + 4096 * (28 + v204_i0 * 1)];
    }
  }
  std::vector<double> v205(std::begin(v204), std::end(v204));
  auto pt92_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt92_filled = v205;
  pt92_filled.clear();
  pt92_filled.reserve(pt92_filled_n);
  for (auto i = 0; i < pt92_filled_n; ++i) {
    pt92_filled.push_back(v205[i % v205.size()]);
  }
  auto pt92 = cc->MakeCKKSPackedPlaintext(pt92_filled);
  std::vector<float> v206(4096);
  for (int64_t v206_i0 = 0; v206_i0 < 1; ++v206_i0) {
    for (int64_t v206_i1 = 0; v206_i1 < 4096; ++v206_i1) {
      v206[v206_i1 + 4096 * (v206_i0)] = v2[0 + v206_i1 * 1 + 4096 * (29 + v206_i0 * 1)];
    }
  }
  std::vector<double> v207(std::begin(v206), std::end(v206));
  auto pt93_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt93_filled = v207;
  pt93_filled.clear();
  pt93_filled.reserve(pt93_filled_n);
  for (auto i = 0; i < pt93_filled_n; ++i) {
    pt93_filled.push_back(v207[i % v207.size()]);
  }
  auto pt93 = cc->MakeCKKSPackedPlaintext(pt93_filled);
  std::vector<float> v208(4096);
  for (int64_t v208_i0 = 0; v208_i0 < 1; ++v208_i0) {
    for (int64_t v208_i1 = 0; v208_i1 < 4096; ++v208_i1) {
      v208[v208_i1 + 4096 * (v208_i0)] = v2[0 + v208_i1 * 1 + 4096 * (30 + v208_i0 * 1)];
    }
  }
  std::vector<double> v209(std::begin(v208), std::end(v208));
  auto pt94_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt94_filled = v209;
  pt94_filled.clear();
  pt94_filled.reserve(pt94_filled_n);
  for (auto i = 0; i < pt94_filled_n; ++i) {
    pt94_filled.push_back(v209[i % v209.size()]);
  }
  auto pt94 = cc->MakeCKKSPackedPlaintext(pt94_filled);
  std::vector<float> v210(4096);
  for (int64_t v210_i0 = 0; v210_i0 < 1; ++v210_i0) {
    for (int64_t v210_i1 = 0; v210_i1 < 4096; ++v210_i1) {
      v210[v210_i1 + 4096 * (v210_i0)] = v2[0 + v210_i1 * 1 + 4096 * (31 + v210_i0 * 1)];
    }
  }
  std::vector<double> v211(std::begin(v210), std::end(v210));
  auto pt95_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt95_filled = v211;
  pt95_filled.clear();
  pt95_filled.reserve(pt95_filled_n);
  for (auto i = 0; i < pt95_filled_n; ++i) {
    pt95_filled.push_back(v211[i % v211.size()]);
  }
  auto pt95 = cc->MakeCKKSPackedPlaintext(pt95_filled);
  std::vector<float> v212(4096);
  for (int64_t v212_i0 = 0; v212_i0 < 1; ++v212_i0) {
    for (int64_t v212_i1 = 0; v212_i1 < 4096; ++v212_i1) {
      v212[v212_i1 + 4096 * (v212_i0)] = v2[0 + v212_i1 * 1 + 4096 * (32 + v212_i0 * 1)];
    }
  }
  std::vector<double> v213(std::begin(v212), std::end(v212));
  auto pt96_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt96_filled = v213;
  pt96_filled.clear();
  pt96_filled.reserve(pt96_filled_n);
  for (auto i = 0; i < pt96_filled_n; ++i) {
    pt96_filled.push_back(v213[i % v213.size()]);
  }
  auto pt96 = cc->MakeCKKSPackedPlaintext(pt96_filled);
  std::vector<float> v214(4096);
  for (int64_t v214_i0 = 0; v214_i0 < 1; ++v214_i0) {
    for (int64_t v214_i1 = 0; v214_i1 < 4096; ++v214_i1) {
      v214[v214_i1 + 4096 * (v214_i0)] = v2[0 + v214_i1 * 1 + 4096 * (33 + v214_i0 * 1)];
    }
  }
  std::vector<double> v215(std::begin(v214), std::end(v214));
  auto pt97_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt97_filled = v215;
  pt97_filled.clear();
  pt97_filled.reserve(pt97_filled_n);
  for (auto i = 0; i < pt97_filled_n; ++i) {
    pt97_filled.push_back(v215[i % v215.size()]);
  }
  auto pt97 = cc->MakeCKKSPackedPlaintext(pt97_filled);
  std::vector<float> v216(4096);
  for (int64_t v216_i0 = 0; v216_i0 < 1; ++v216_i0) {
    for (int64_t v216_i1 = 0; v216_i1 < 4096; ++v216_i1) {
      v216[v216_i1 + 4096 * (v216_i0)] = v2[0 + v216_i1 * 1 + 4096 * (34 + v216_i0 * 1)];
    }
  }
  std::vector<double> v217(std::begin(v216), std::end(v216));
  auto pt98_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt98_filled = v217;
  pt98_filled.clear();
  pt98_filled.reserve(pt98_filled_n);
  for (auto i = 0; i < pt98_filled_n; ++i) {
    pt98_filled.push_back(v217[i % v217.size()]);
  }
  auto pt98 = cc->MakeCKKSPackedPlaintext(pt98_filled);
  std::vector<float> v218(4096);
  for (int64_t v218_i0 = 0; v218_i0 < 1; ++v218_i0) {
    for (int64_t v218_i1 = 0; v218_i1 < 4096; ++v218_i1) {
      v218[v218_i1 + 4096 * (v218_i0)] = v2[0 + v218_i1 * 1 + 4096 * (35 + v218_i0 * 1)];
    }
  }
  std::vector<double> v219(std::begin(v218), std::end(v218));
  auto pt99_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt99_filled = v219;
  pt99_filled.clear();
  pt99_filled.reserve(pt99_filled_n);
  for (auto i = 0; i < pt99_filled_n; ++i) {
    pt99_filled.push_back(v219[i % v219.size()]);
  }
  auto pt99 = cc->MakeCKKSPackedPlaintext(pt99_filled);
  std::vector<float> v220(4096);
  for (int64_t v220_i0 = 0; v220_i0 < 1; ++v220_i0) {
    for (int64_t v220_i1 = 0; v220_i1 < 4096; ++v220_i1) {
      v220[v220_i1 + 4096 * (v220_i0)] = v2[0 + v220_i1 * 1 + 4096 * (36 + v220_i0 * 1)];
    }
  }
  std::vector<double> v221(std::begin(v220), std::end(v220));
  auto pt100_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt100_filled = v221;
  pt100_filled.clear();
  pt100_filled.reserve(pt100_filled_n);
  for (auto i = 0; i < pt100_filled_n; ++i) {
    pt100_filled.push_back(v221[i % v221.size()]);
  }
  auto pt100 = cc->MakeCKKSPackedPlaintext(pt100_filled);
  std::vector<float> v222(4096);
  for (int64_t v222_i0 = 0; v222_i0 < 1; ++v222_i0) {
    for (int64_t v222_i1 = 0; v222_i1 < 4096; ++v222_i1) {
      v222[v222_i1 + 4096 * (v222_i0)] = v2[0 + v222_i1 * 1 + 4096 * (37 + v222_i0 * 1)];
    }
  }
  std::vector<double> v223(std::begin(v222), std::end(v222));
  auto pt101_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt101_filled = v223;
  pt101_filled.clear();
  pt101_filled.reserve(pt101_filled_n);
  for (auto i = 0; i < pt101_filled_n; ++i) {
    pt101_filled.push_back(v223[i % v223.size()]);
  }
  auto pt101 = cc->MakeCKKSPackedPlaintext(pt101_filled);
  std::vector<float> v224(4096);
  for (int64_t v224_i0 = 0; v224_i0 < 1; ++v224_i0) {
    for (int64_t v224_i1 = 0; v224_i1 < 4096; ++v224_i1) {
      v224[v224_i1 + 4096 * (v224_i0)] = v2[0 + v224_i1 * 1 + 4096 * (38 + v224_i0 * 1)];
    }
  }
  std::vector<double> v225(std::begin(v224), std::end(v224));
  auto pt102_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt102_filled = v225;
  pt102_filled.clear();
  pt102_filled.reserve(pt102_filled_n);
  for (auto i = 0; i < pt102_filled_n; ++i) {
    pt102_filled.push_back(v225[i % v225.size()]);
  }
  auto pt102 = cc->MakeCKKSPackedPlaintext(pt102_filled);
  std::vector<float> v226(4096);
  for (int64_t v226_i0 = 0; v226_i0 < 1; ++v226_i0) {
    for (int64_t v226_i1 = 0; v226_i1 < 4096; ++v226_i1) {
      v226[v226_i1 + 4096 * (v226_i0)] = v2[0 + v226_i1 * 1 + 4096 * (39 + v226_i0 * 1)];
    }
  }
  std::vector<double> v227(std::begin(v226), std::end(v226));
  auto pt103_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt103_filled = v227;
  pt103_filled.clear();
  pt103_filled.reserve(pt103_filled_n);
  for (auto i = 0; i < pt103_filled_n; ++i) {
    pt103_filled.push_back(v227[i % v227.size()]);
  }
  auto pt103 = cc->MakeCKKSPackedPlaintext(pt103_filled);
  std::vector<float> v228(4096);
  for (int64_t v228_i0 = 0; v228_i0 < 1; ++v228_i0) {
    for (int64_t v228_i1 = 0; v228_i1 < 4096; ++v228_i1) {
      v228[v228_i1 + 4096 * (v228_i0)] = v2[0 + v228_i1 * 1 + 4096 * (40 + v228_i0 * 1)];
    }
  }
  std::vector<double> v229(std::begin(v228), std::end(v228));
  auto pt104_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt104_filled = v229;
  pt104_filled.clear();
  pt104_filled.reserve(pt104_filled_n);
  for (auto i = 0; i < pt104_filled_n; ++i) {
    pt104_filled.push_back(v229[i % v229.size()]);
  }
  auto pt104 = cc->MakeCKKSPackedPlaintext(pt104_filled);
  std::vector<float> v230(4096);
  for (int64_t v230_i0 = 0; v230_i0 < 1; ++v230_i0) {
    for (int64_t v230_i1 = 0; v230_i1 < 4096; ++v230_i1) {
      v230[v230_i1 + 4096 * (v230_i0)] = v2[0 + v230_i1 * 1 + 4096 * (41 + v230_i0 * 1)];
    }
  }
  std::vector<double> v231(std::begin(v230), std::end(v230));
  auto pt105_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt105_filled = v231;
  pt105_filled.clear();
  pt105_filled.reserve(pt105_filled_n);
  for (auto i = 0; i < pt105_filled_n; ++i) {
    pt105_filled.push_back(v231[i % v231.size()]);
  }
  auto pt105 = cc->MakeCKKSPackedPlaintext(pt105_filled);
  std::vector<float> v232(4096);
  for (int64_t v232_i0 = 0; v232_i0 < 1; ++v232_i0) {
    for (int64_t v232_i1 = 0; v232_i1 < 4096; ++v232_i1) {
      v232[v232_i1 + 4096 * (v232_i0)] = v2[0 + v232_i1 * 1 + 4096 * (42 + v232_i0 * 1)];
    }
  }
  std::vector<double> v233(std::begin(v232), std::end(v232));
  auto pt106_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt106_filled = v233;
  pt106_filled.clear();
  pt106_filled.reserve(pt106_filled_n);
  for (auto i = 0; i < pt106_filled_n; ++i) {
    pt106_filled.push_back(v233[i % v233.size()]);
  }
  auto pt106 = cc->MakeCKKSPackedPlaintext(pt106_filled);
  std::vector<float> v234(4096);
  for (int64_t v234_i0 = 0; v234_i0 < 1; ++v234_i0) {
    for (int64_t v234_i1 = 0; v234_i1 < 4096; ++v234_i1) {
      v234[v234_i1 + 4096 * (v234_i0)] = v2[0 + v234_i1 * 1 + 4096 * (43 + v234_i0 * 1)];
    }
  }
  std::vector<double> v235(std::begin(v234), std::end(v234));
  auto pt107_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt107_filled = v235;
  pt107_filled.clear();
  pt107_filled.reserve(pt107_filled_n);
  for (auto i = 0; i < pt107_filled_n; ++i) {
    pt107_filled.push_back(v235[i % v235.size()]);
  }
  auto pt107 = cc->MakeCKKSPackedPlaintext(pt107_filled);
  std::vector<float> v236(4096);
  for (int64_t v236_i0 = 0; v236_i0 < 1; ++v236_i0) {
    for (int64_t v236_i1 = 0; v236_i1 < 4096; ++v236_i1) {
      v236[v236_i1 + 4096 * (v236_i0)] = v2[0 + v236_i1 * 1 + 4096 * (44 + v236_i0 * 1)];
    }
  }
  std::vector<double> v237(std::begin(v236), std::end(v236));
  auto pt108_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt108_filled = v237;
  pt108_filled.clear();
  pt108_filled.reserve(pt108_filled_n);
  for (auto i = 0; i < pt108_filled_n; ++i) {
    pt108_filled.push_back(v237[i % v237.size()]);
  }
  auto pt108 = cc->MakeCKKSPackedPlaintext(pt108_filled);
  std::vector<float> v238(4096);
  for (int64_t v238_i0 = 0; v238_i0 < 1; ++v238_i0) {
    for (int64_t v238_i1 = 0; v238_i1 < 4096; ++v238_i1) {
      v238[v238_i1 + 4096 * (v238_i0)] = v2[0 + v238_i1 * 1 + 4096 * (45 + v238_i0 * 1)];
    }
  }
  std::vector<double> v239(std::begin(v238), std::end(v238));
  auto pt109_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt109_filled = v239;
  pt109_filled.clear();
  pt109_filled.reserve(pt109_filled_n);
  for (auto i = 0; i < pt109_filled_n; ++i) {
    pt109_filled.push_back(v239[i % v239.size()]);
  }
  auto pt109 = cc->MakeCKKSPackedPlaintext(pt109_filled);
  std::vector<float> v240(4096);
  for (int64_t v240_i0 = 0; v240_i0 < 1; ++v240_i0) {
    for (int64_t v240_i1 = 0; v240_i1 < 4096; ++v240_i1) {
      v240[v240_i1 + 4096 * (v240_i0)] = v2[0 + v240_i1 * 1 + 4096 * (46 + v240_i0 * 1)];
    }
  }
  std::vector<double> v241(std::begin(v240), std::end(v240));
  auto pt110_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt110_filled = v241;
  pt110_filled.clear();
  pt110_filled.reserve(pt110_filled_n);
  for (auto i = 0; i < pt110_filled_n; ++i) {
    pt110_filled.push_back(v241[i % v241.size()]);
  }
  auto pt110 = cc->MakeCKKSPackedPlaintext(pt110_filled);
  std::vector<float> v242(4096);
  for (int64_t v242_i0 = 0; v242_i0 < 1; ++v242_i0) {
    for (int64_t v242_i1 = 0; v242_i1 < 4096; ++v242_i1) {
      v242[v242_i1 + 4096 * (v242_i0)] = v2[0 + v242_i1 * 1 + 4096 * (47 + v242_i0 * 1)];
    }
  }
  std::vector<double> v243(std::begin(v242), std::end(v242));
  auto pt111_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt111_filled = v243;
  pt111_filled.clear();
  pt111_filled.reserve(pt111_filled_n);
  for (auto i = 0; i < pt111_filled_n; ++i) {
    pt111_filled.push_back(v243[i % v243.size()]);
  }
  auto pt111 = cc->MakeCKKSPackedPlaintext(pt111_filled);
  std::vector<float> v244(4096);
  for (int64_t v244_i0 = 0; v244_i0 < 1; ++v244_i0) {
    for (int64_t v244_i1 = 0; v244_i1 < 4096; ++v244_i1) {
      v244[v244_i1 + 4096 * (v244_i0)] = v2[0 + v244_i1 * 1 + 4096 * (48 + v244_i0 * 1)];
    }
  }
  std::vector<double> v245(std::begin(v244), std::end(v244));
  auto pt112_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt112_filled = v245;
  pt112_filled.clear();
  pt112_filled.reserve(pt112_filled_n);
  for (auto i = 0; i < pt112_filled_n; ++i) {
    pt112_filled.push_back(v245[i % v245.size()]);
  }
  auto pt112 = cc->MakeCKKSPackedPlaintext(pt112_filled);
  std::vector<float> v246(4096);
  for (int64_t v246_i0 = 0; v246_i0 < 1; ++v246_i0) {
    for (int64_t v246_i1 = 0; v246_i1 < 4096; ++v246_i1) {
      v246[v246_i1 + 4096 * (v246_i0)] = v2[0 + v246_i1 * 1 + 4096 * (49 + v246_i0 * 1)];
    }
  }
  std::vector<double> v247(std::begin(v246), std::end(v246));
  auto pt113_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt113_filled = v247;
  pt113_filled.clear();
  pt113_filled.reserve(pt113_filled_n);
  for (auto i = 0; i < pt113_filled_n; ++i) {
    pt113_filled.push_back(v247[i % v247.size()]);
  }
  auto pt113 = cc->MakeCKKSPackedPlaintext(pt113_filled);
  std::vector<float> v248(4096);
  for (int64_t v248_i0 = 0; v248_i0 < 1; ++v248_i0) {
    for (int64_t v248_i1 = 0; v248_i1 < 4096; ++v248_i1) {
      v248[v248_i1 + 4096 * (v248_i0)] = v2[0 + v248_i1 * 1 + 4096 * (50 + v248_i0 * 1)];
    }
  }
  std::vector<double> v249(std::begin(v248), std::end(v248));
  auto pt114_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt114_filled = v249;
  pt114_filled.clear();
  pt114_filled.reserve(pt114_filled_n);
  for (auto i = 0; i < pt114_filled_n; ++i) {
    pt114_filled.push_back(v249[i % v249.size()]);
  }
  auto pt114 = cc->MakeCKKSPackedPlaintext(pt114_filled);
  std::vector<float> v250(4096);
  for (int64_t v250_i0 = 0; v250_i0 < 1; ++v250_i0) {
    for (int64_t v250_i1 = 0; v250_i1 < 4096; ++v250_i1) {
      v250[v250_i1 + 4096 * (v250_i0)] = v2[0 + v250_i1 * 1 + 4096 * (51 + v250_i0 * 1)];
    }
  }
  std::vector<double> v251(std::begin(v250), std::end(v250));
  auto pt115_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt115_filled = v251;
  pt115_filled.clear();
  pt115_filled.reserve(pt115_filled_n);
  for (auto i = 0; i < pt115_filled_n; ++i) {
    pt115_filled.push_back(v251[i % v251.size()]);
  }
  auto pt115 = cc->MakeCKKSPackedPlaintext(pt115_filled);
  std::vector<float> v252(4096);
  for (int64_t v252_i0 = 0; v252_i0 < 1; ++v252_i0) {
    for (int64_t v252_i1 = 0; v252_i1 < 4096; ++v252_i1) {
      v252[v252_i1 + 4096 * (v252_i0)] = v2[0 + v252_i1 * 1 + 4096 * (52 + v252_i0 * 1)];
    }
  }
  std::vector<double> v253(std::begin(v252), std::end(v252));
  auto pt116_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt116_filled = v253;
  pt116_filled.clear();
  pt116_filled.reserve(pt116_filled_n);
  for (auto i = 0; i < pt116_filled_n; ++i) {
    pt116_filled.push_back(v253[i % v253.size()]);
  }
  auto pt116 = cc->MakeCKKSPackedPlaintext(pt116_filled);
  std::vector<float> v254(4096);
  for (int64_t v254_i0 = 0; v254_i0 < 1; ++v254_i0) {
    for (int64_t v254_i1 = 0; v254_i1 < 4096; ++v254_i1) {
      v254[v254_i1 + 4096 * (v254_i0)] = v2[0 + v254_i1 * 1 + 4096 * (53 + v254_i0 * 1)];
    }
  }
  std::vector<double> v255(std::begin(v254), std::end(v254));
  auto pt117_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt117_filled = v255;
  pt117_filled.clear();
  pt117_filled.reserve(pt117_filled_n);
  for (auto i = 0; i < pt117_filled_n; ++i) {
    pt117_filled.push_back(v255[i % v255.size()]);
  }
  auto pt117 = cc->MakeCKKSPackedPlaintext(pt117_filled);
  std::vector<float> v256(4096);
  for (int64_t v256_i0 = 0; v256_i0 < 1; ++v256_i0) {
    for (int64_t v256_i1 = 0; v256_i1 < 4096; ++v256_i1) {
      v256[v256_i1 + 4096 * (v256_i0)] = v2[0 + v256_i1 * 1 + 4096 * (54 + v256_i0 * 1)];
    }
  }
  std::vector<double> v257(std::begin(v256), std::end(v256));
  auto pt118_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt118_filled = v257;
  pt118_filled.clear();
  pt118_filled.reserve(pt118_filled_n);
  for (auto i = 0; i < pt118_filled_n; ++i) {
    pt118_filled.push_back(v257[i % v257.size()]);
  }
  auto pt118 = cc->MakeCKKSPackedPlaintext(pt118_filled);
  std::vector<float> v258(4096);
  for (int64_t v258_i0 = 0; v258_i0 < 1; ++v258_i0) {
    for (int64_t v258_i1 = 0; v258_i1 < 4096; ++v258_i1) {
      v258[v258_i1 + 4096 * (v258_i0)] = v2[0 + v258_i1 * 1 + 4096 * (55 + v258_i0 * 1)];
    }
  }
  std::vector<double> v259(std::begin(v258), std::end(v258));
  auto pt119_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt119_filled = v259;
  pt119_filled.clear();
  pt119_filled.reserve(pt119_filled_n);
  for (auto i = 0; i < pt119_filled_n; ++i) {
    pt119_filled.push_back(v259[i % v259.size()]);
  }
  auto pt119 = cc->MakeCKKSPackedPlaintext(pt119_filled);
  std::vector<float> v260(4096);
  for (int64_t v260_i0 = 0; v260_i0 < 1; ++v260_i0) {
    for (int64_t v260_i1 = 0; v260_i1 < 4096; ++v260_i1) {
      v260[v260_i1 + 4096 * (v260_i0)] = v2[0 + v260_i1 * 1 + 4096 * (56 + v260_i0 * 1)];
    }
  }
  std::vector<double> v261(std::begin(v260), std::end(v260));
  auto pt120_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt120_filled = v261;
  pt120_filled.clear();
  pt120_filled.reserve(pt120_filled_n);
  for (auto i = 0; i < pt120_filled_n; ++i) {
    pt120_filled.push_back(v261[i % v261.size()]);
  }
  auto pt120 = cc->MakeCKKSPackedPlaintext(pt120_filled);
  std::vector<float> v262(4096);
  for (int64_t v262_i0 = 0; v262_i0 < 1; ++v262_i0) {
    for (int64_t v262_i1 = 0; v262_i1 < 4096; ++v262_i1) {
      v262[v262_i1 + 4096 * (v262_i0)] = v2[0 + v262_i1 * 1 + 4096 * (57 + v262_i0 * 1)];
    }
  }
  std::vector<double> v263(std::begin(v262), std::end(v262));
  auto pt121_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt121_filled = v263;
  pt121_filled.clear();
  pt121_filled.reserve(pt121_filled_n);
  for (auto i = 0; i < pt121_filled_n; ++i) {
    pt121_filled.push_back(v263[i % v263.size()]);
  }
  auto pt121 = cc->MakeCKKSPackedPlaintext(pt121_filled);
  std::vector<float> v264(4096);
  for (int64_t v264_i0 = 0; v264_i0 < 1; ++v264_i0) {
    for (int64_t v264_i1 = 0; v264_i1 < 4096; ++v264_i1) {
      v264[v264_i1 + 4096 * (v264_i0)] = v2[0 + v264_i1 * 1 + 4096 * (58 + v264_i0 * 1)];
    }
  }
  std::vector<double> v265(std::begin(v264), std::end(v264));
  auto pt122_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt122_filled = v265;
  pt122_filled.clear();
  pt122_filled.reserve(pt122_filled_n);
  for (auto i = 0; i < pt122_filled_n; ++i) {
    pt122_filled.push_back(v265[i % v265.size()]);
  }
  auto pt122 = cc->MakeCKKSPackedPlaintext(pt122_filled);
  std::vector<float> v266(4096);
  for (int64_t v266_i0 = 0; v266_i0 < 1; ++v266_i0) {
    for (int64_t v266_i1 = 0; v266_i1 < 4096; ++v266_i1) {
      v266[v266_i1 + 4096 * (v266_i0)] = v2[0 + v266_i1 * 1 + 4096 * (59 + v266_i0 * 1)];
    }
  }
  std::vector<double> v267(std::begin(v266), std::end(v266));
  auto pt123_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt123_filled = v267;
  pt123_filled.clear();
  pt123_filled.reserve(pt123_filled_n);
  for (auto i = 0; i < pt123_filled_n; ++i) {
    pt123_filled.push_back(v267[i % v267.size()]);
  }
  auto pt123 = cc->MakeCKKSPackedPlaintext(pt123_filled);
  std::vector<float> v268(4096);
  for (int64_t v268_i0 = 0; v268_i0 < 1; ++v268_i0) {
    for (int64_t v268_i1 = 0; v268_i1 < 4096; ++v268_i1) {
      v268[v268_i1 + 4096 * (v268_i0)] = v2[0 + v268_i1 * 1 + 4096 * (60 + v268_i0 * 1)];
    }
  }
  std::vector<double> v269(std::begin(v268), std::end(v268));
  auto pt124_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt124_filled = v269;
  pt124_filled.clear();
  pt124_filled.reserve(pt124_filled_n);
  for (auto i = 0; i < pt124_filled_n; ++i) {
    pt124_filled.push_back(v269[i % v269.size()]);
  }
  auto pt124 = cc->MakeCKKSPackedPlaintext(pt124_filled);
  std::vector<float> v270(4096);
  for (int64_t v270_i0 = 0; v270_i0 < 1; ++v270_i0) {
    for (int64_t v270_i1 = 0; v270_i1 < 4096; ++v270_i1) {
      v270[v270_i1 + 4096 * (v270_i0)] = v2[0 + v270_i1 * 1 + 4096 * (61 + v270_i0 * 1)];
    }
  }
  std::vector<double> v271(std::begin(v270), std::end(v270));
  auto pt125_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt125_filled = v271;
  pt125_filled.clear();
  pt125_filled.reserve(pt125_filled_n);
  for (auto i = 0; i < pt125_filled_n; ++i) {
    pt125_filled.push_back(v271[i % v271.size()]);
  }
  auto pt125 = cc->MakeCKKSPackedPlaintext(pt125_filled);
  std::vector<float> v272(4096);
  for (int64_t v272_i0 = 0; v272_i0 < 1; ++v272_i0) {
    for (int64_t v272_i1 = 0; v272_i1 < 4096; ++v272_i1) {
      v272[v272_i1 + 4096 * (v272_i0)] = v2[0 + v272_i1 * 1 + 4096 * (62 + v272_i0 * 1)];
    }
  }
  std::vector<double> v273(std::begin(v272), std::end(v272));
  auto pt126_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt126_filled = v273;
  pt126_filled.clear();
  pt126_filled.reserve(pt126_filled_n);
  for (auto i = 0; i < pt126_filled_n; ++i) {
    pt126_filled.push_back(v273[i % v273.size()]);
  }
  auto pt126 = cc->MakeCKKSPackedPlaintext(pt126_filled);
  std::vector<float> v274(4096);
  for (int64_t v274_i0 = 0; v274_i0 < 1; ++v274_i0) {
    for (int64_t v274_i1 = 0; v274_i1 < 4096; ++v274_i1) {
      v274[v274_i1 + 4096 * (v274_i0)] = v2[0 + v274_i1 * 1 + 4096 * (63 + v274_i0 * 1)];
    }
  }
  std::vector<double> v275(std::begin(v274), std::end(v274));
  auto pt127_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt127_filled = v275;
  pt127_filled.clear();
  pt127_filled.reserve(pt127_filled_n);
  for (auto i = 0; i < pt127_filled_n; ++i) {
    pt127_filled.push_back(v275[i % v275.size()]);
  }
  auto pt127 = cc->MakeCKKSPackedPlaintext(pt127_filled);
  std::vector<CiphertextT> v276(1);
  #pragma omp parallel for
  for (auto v278 = 0; v278 < 7; ++v278) {
    size_t v280 = v4[v278];
    const auto& ct9 = cc->EvalFastRotation(ct, v280, 2 * cc->GetRingDimension(), digit_decomp);
    const std::vector<CiphertextT> v281 = {ct9};
    v31[v278] = v281[0];
  }
  const auto& ct10 = v31[0];
  const auto& ct11 = v31[1];
  const auto& ct12 = v31[2];
  const auto& ct13 = v31[3];
  const auto& ct14 = v31[4];
  const auto& ct15 = v31[5];
  const auto& ct16 = v31[6];
  const auto& ct17 = cc->EvalMult(ct16, pt6);
  const auto& ct18 = cc->EvalMult(ct15, pt7);
  const auto& ct19 = cc->EvalMult(ct11, pt9);
  cc->EvalAddInPlace(ct2, ct19);
  const auto& ct21 = cc->EvalMult(ct10, pt10);
  cc->EvalAddInPlace(ct2, ct21);
  const auto& ct23 = cc->EvalMult(ct12, pt11);
  cc->EvalAddInPlace(ct2, ct23);
  const auto& ct25 = cc->EvalMult(ct14, pt12);
  cc->EvalAddInPlace(ct2, ct25);
  const auto& ct27 = cc->EvalMult(ct13, pt13);
  cc->EvalAddInPlace(ct2, ct27);
  const auto& ct29 = cc->EvalMult(ct16, pt14);
  cc->EvalAddInPlace(ct2, ct29);
  const auto& ct31 = cc->EvalMult(ct15, pt15);
  cc->EvalAddInPlace(ct2, ct31);
  const auto& ct33 = cc->EvalRotate(ct2, 512);
  const auto& ct34 = cc->EvalMult(ct11, pt17);
  cc->EvalAddInPlace(ct3, ct34);
  const auto& ct36 = cc->EvalMult(ct10, pt18);
  cc->EvalAddInPlace(ct3, ct36);
  const auto& ct38 = cc->EvalMult(ct12, pt19);
  cc->EvalAddInPlace(ct3, ct38);
  const auto& ct40 = cc->EvalMult(ct14, pt20);
  cc->EvalAddInPlace(ct3, ct40);
  const auto& ct42 = cc->EvalMult(ct13, pt21);
  cc->EvalAddInPlace(ct3, ct42);
  const auto& ct44 = cc->EvalMult(ct16, pt22);
  cc->EvalAddInPlace(ct3, ct44);
  const auto& ct46 = cc->EvalMult(ct15, pt23);
  cc->EvalAddInPlace(ct3, ct46);
  const auto& ct48 = cc->EvalRotate(ct3, 1024);
  const auto& ct49 = cc->EvalMult(ct11, pt25);
  cc->EvalAddInPlace(ct4, ct49);
  const auto& ct51 = cc->EvalMult(ct10, pt26);
  cc->EvalAddInPlace(ct4, ct51);
  const auto& ct53 = cc->EvalMult(ct12, pt27);
  cc->EvalAddInPlace(ct4, ct53);
  const auto& ct55 = cc->EvalMult(ct14, pt28);
  cc->EvalAddInPlace(ct4, ct55);
  const auto& ct57 = cc->EvalMult(ct13, pt29);
  cc->EvalAddInPlace(ct4, ct57);
  const auto& ct59 = cc->EvalMult(ct16, pt30);
  cc->EvalAddInPlace(ct4, ct59);
  const auto& ct61 = cc->EvalMult(ct15, pt31);
  cc->EvalAddInPlace(ct4, ct61);
  const auto& ct63 = cc->EvalRotate(ct4, 1536);
  const auto& ct64 = cc->EvalMult(ct11, pt33);
  cc->EvalAddInPlace(ct5, ct64);
  const auto& ct66 = cc->EvalMult(ct10, pt34);
  cc->EvalAddInPlace(ct5, ct66);
  const auto& ct68 = cc->EvalMult(ct12, pt35);
  cc->EvalAddInPlace(ct5, ct68);
  const auto& ct70 = cc->EvalMult(ct14, pt36);
  cc->EvalAddInPlace(ct5, ct70);
  const auto& ct72 = cc->EvalMult(ct13, pt37);
  cc->EvalAddInPlace(ct5, ct72);
  const auto& ct74 = cc->EvalMult(ct16, pt38);
  cc->EvalAddInPlace(ct5, ct74);
  const auto& ct76 = cc->EvalMult(ct15, pt39);
  cc->EvalAddInPlace(ct5, ct76);
  const auto& ct78 = cc->EvalRotate(ct5, 2048);
  const auto& ct79 = cc->EvalMult(ct11, pt41);
  cc->EvalAddInPlace(ct6, ct79);
  const auto& ct81 = cc->EvalMult(ct10, pt42);
  cc->EvalAddInPlace(ct6, ct81);
  const auto& ct83 = cc->EvalMult(ct12, pt43);
  cc->EvalAddInPlace(ct6, ct83);
  const auto& ct85 = cc->EvalMult(ct14, pt44);
  cc->EvalAddInPlace(ct6, ct85);
  const auto& ct87 = cc->EvalMult(ct13, pt45);
  cc->EvalAddInPlace(ct6, ct87);
  const auto& ct89 = cc->EvalMult(ct16, pt46);
  cc->EvalAddInPlace(ct6, ct89);
  const auto& ct91 = cc->EvalMult(ct15, pt47);
  cc->EvalAddInPlace(ct6, ct91);
  const auto& ct93 = cc->EvalRotate(ct6, 2560);
  const auto& ct94 = cc->EvalMult(ct11, pt49);
  cc->EvalAddInPlace(ct7, ct94);
  const auto& ct96 = cc->EvalMult(ct10, pt50);
  cc->EvalAddInPlace(ct7, ct96);
  const auto& ct98 = cc->EvalMult(ct12, pt51);
  cc->EvalAddInPlace(ct7, ct98);
  const auto& ct100 = cc->EvalMult(ct14, pt52);
  cc->EvalAddInPlace(ct7, ct100);
  const auto& ct102 = cc->EvalMult(ct13, pt53);
  cc->EvalAddInPlace(ct7, ct102);
  const auto& ct104 = cc->EvalMult(ct16, pt54);
  cc->EvalAddInPlace(ct7, ct104);
  const auto& ct106 = cc->EvalMult(ct15, pt55);
  cc->EvalAddInPlace(ct7, ct106);
  const auto& ct108 = cc->EvalRotate(ct7, 3072);
  const auto& ct109 = cc->EvalMult(ct11, pt57);
  cc->EvalAddInPlace(ct8, ct109);
  const auto& ct111 = cc->EvalMult(ct10, pt58);
  cc->EvalAddInPlace(ct8, ct111);
  const auto& ct113 = cc->EvalMult(ct12, pt59);
  cc->EvalAddInPlace(ct8, ct113);
  const auto& ct115 = cc->EvalMult(ct14, pt60);
  cc->EvalAddInPlace(ct8, ct115);
  const auto& ct117 = cc->EvalMult(ct13, pt61);
  cc->EvalAddInPlace(ct8, ct117);
  const auto& ct119 = cc->EvalMult(ct16, pt62);
  cc->EvalAddInPlace(ct8, ct119);
  const auto& ct121 = cc->EvalMult(ct15, pt63);
  cc->EvalAddInPlace(ct8, ct121);
  const auto& ct123 = cc->EvalRotate(ct8, 3584);
  const auto& ct124 = cc->EvalMult(ct11, pt1);
  cc->EvalAddInPlace(ct1, ct124);
  const auto& ct126 = cc->EvalMult(ct10, pt2);
  cc->EvalAddInPlace(ct1, ct126);
  const auto& ct128 = cc->EvalMult(ct12, pt3);
  cc->EvalAddInPlace(ct1, ct128);
  const auto& ct130 = cc->EvalMult(ct14, pt4);
  cc->EvalAddInPlace(ct1, ct130);
  const auto& ct132 = cc->EvalMult(ct13, pt5);
  cc->EvalAddInPlace(ct1, ct132);
  cc->EvalAddInPlace(ct1, ct17);
  cc->EvalAddInPlace(ct1, ct18);
  cc->EvalAddInPlace(ct1, ct33);
  cc->EvalAddInPlace(ct1, ct48);
  cc->EvalAddInPlace(ct1, ct63);
  cc->EvalAddInPlace(ct1, ct78);
  cc->EvalAddInPlace(ct1, ct93);
  cc->EvalAddInPlace(ct1, ct108);
  cc->EvalAddInPlace(ct1, ct123);
  const auto& digit_decomp1 = cc->EvalFastRotationPrecompute(ct1);
  const auto& ct143 = cc->ModReduce(ct1);
  auto ct144 = cc->EvalMult(ct143, pt64);
  #pragma omp parallel for
  for (auto v283 = 0; v283 < 7; ++v283) {
    size_t v285 = v3[v283];
    const auto& ct145 = cc->EvalFastRotation(ct1, v285, 2 * cc->GetRingDimension(), digit_decomp1);
    const std::vector<CiphertextT> v286 = {ct145};
    v31[v283] = v286[0];
  }
  auto ct146 = v31[0];
  auto ct147 = v31[1];
  auto ct148 = v31[2];
  auto ct149 = v31[3];
  auto ct150 = v31[4];
  auto ct151 = v31[5];
  auto ct152 = v31[6];
  cc->ModReduceInPlace(ct152);
  const auto& ct154 = cc->EvalMult(ct152, pt65);
  cc->EvalAddInPlace(ct144, ct154);
  cc->ModReduceInPlace(ct151);
  const auto& ct157 = cc->EvalMult(ct151, pt66);
  cc->EvalAddInPlace(ct144, ct157);
  cc->ModReduceInPlace(ct150);
  const auto& ct160 = cc->EvalMult(ct150, pt67);
  cc->EvalAddInPlace(ct144, ct160);
  cc->ModReduceInPlace(ct149);
  const auto& ct163 = cc->EvalMult(ct149, pt68);
  cc->EvalAddInPlace(ct144, ct163);
  cc->ModReduceInPlace(ct148);
  const auto& ct166 = cc->EvalMult(ct148, pt69);
  cc->EvalAddInPlace(ct144, ct166);
  cc->ModReduceInPlace(ct147);
  const auto& ct169 = cc->EvalMult(ct147, pt70);
  cc->EvalAddInPlace(ct144, ct169);
  cc->ModReduceInPlace(ct146);
  const auto& ct172 = cc->EvalMult(ct146, pt71);
  cc->EvalAddInPlace(ct144, ct172);
  auto ct174 = cc->EvalMult(ct143, pt72);
  const auto& ct175 = cc->EvalMult(ct152, pt73);
  cc->EvalAddInPlace(ct174, ct175);
  const auto& ct177 = cc->EvalMult(ct151, pt74);
  cc->EvalAddInPlace(ct174, ct177);
  const auto& ct179 = cc->EvalMult(ct150, pt75);
  cc->EvalAddInPlace(ct174, ct179);
  const auto& ct181 = cc->EvalMult(ct149, pt76);
  cc->EvalAddInPlace(ct174, ct181);
  const auto& ct183 = cc->EvalMult(ct148, pt77);
  cc->EvalAddInPlace(ct174, ct183);
  const auto& ct185 = cc->EvalMult(ct147, pt78);
  cc->EvalAddInPlace(ct174, ct185);
  const auto& ct187 = cc->EvalMult(ct146, pt79);
  cc->EvalAddInPlace(ct174, ct187);
  const auto& ct189 = cc->EvalRotate(ct174, 512);
  cc->EvalAddInPlace(ct144, ct189);
  auto ct191 = cc->EvalMult(ct143, pt80);
  const auto& ct192 = cc->EvalMult(ct152, pt81);
  cc->EvalAddInPlace(ct191, ct192);
  const auto& ct194 = cc->EvalMult(ct151, pt82);
  cc->EvalAddInPlace(ct191, ct194);
  const auto& ct196 = cc->EvalMult(ct150, pt83);
  cc->EvalAddInPlace(ct191, ct196);
  const auto& ct198 = cc->EvalMult(ct149, pt84);
  cc->EvalAddInPlace(ct191, ct198);
  const auto& ct200 = cc->EvalMult(ct148, pt85);
  cc->EvalAddInPlace(ct191, ct200);
  const auto& ct202 = cc->EvalMult(ct147, pt86);
  cc->EvalAddInPlace(ct191, ct202);
  const auto& ct204 = cc->EvalMult(ct146, pt87);
  cc->EvalAddInPlace(ct191, ct204);
  const auto& ct206 = cc->EvalRotate(ct191, 1024);
  cc->EvalAddInPlace(ct144, ct206);
  auto ct208 = cc->EvalMult(ct143, pt88);
  const auto& ct209 = cc->EvalMult(ct152, pt89);
  cc->EvalAddInPlace(ct208, ct209);
  const auto& ct211 = cc->EvalMult(ct151, pt90);
  cc->EvalAddInPlace(ct208, ct211);
  const auto& ct213 = cc->EvalMult(ct150, pt91);
  cc->EvalAddInPlace(ct208, ct213);
  const auto& ct215 = cc->EvalMult(ct149, pt92);
  cc->EvalAddInPlace(ct208, ct215);
  const auto& ct217 = cc->EvalMult(ct148, pt93);
  cc->EvalAddInPlace(ct208, ct217);
  const auto& ct219 = cc->EvalMult(ct147, pt94);
  cc->EvalAddInPlace(ct208, ct219);
  const auto& ct221 = cc->EvalMult(ct146, pt95);
  cc->EvalAddInPlace(ct208, ct221);
  const auto& ct223 = cc->EvalRotate(ct208, 1536);
  cc->EvalAddInPlace(ct144, ct223);
  auto ct225 = cc->EvalMult(ct143, pt96);
  const auto& ct226 = cc->EvalMult(ct152, pt97);
  cc->EvalAddInPlace(ct225, ct226);
  const auto& ct228 = cc->EvalMult(ct151, pt98);
  cc->EvalAddInPlace(ct225, ct228);
  const auto& ct230 = cc->EvalMult(ct150, pt99);
  cc->EvalAddInPlace(ct225, ct230);
  const auto& ct232 = cc->EvalMult(ct149, pt100);
  cc->EvalAddInPlace(ct225, ct232);
  const auto& ct234 = cc->EvalMult(ct148, pt101);
  cc->EvalAddInPlace(ct225, ct234);
  const auto& ct236 = cc->EvalMult(ct147, pt102);
  cc->EvalAddInPlace(ct225, ct236);
  const auto& ct238 = cc->EvalMult(ct146, pt103);
  cc->EvalAddInPlace(ct225, ct238);
  const auto& ct240 = cc->EvalRotate(ct225, 2048);
  cc->EvalAddInPlace(ct144, ct240);
  auto ct242 = cc->EvalMult(ct143, pt104);
  const auto& ct243 = cc->EvalMult(ct152, pt105);
  cc->EvalAddInPlace(ct242, ct243);
  const auto& ct245 = cc->EvalMult(ct151, pt106);
  cc->EvalAddInPlace(ct242, ct245);
  const auto& ct247 = cc->EvalMult(ct150, pt107);
  cc->EvalAddInPlace(ct242, ct247);
  const auto& ct249 = cc->EvalMult(ct149, pt108);
  cc->EvalAddInPlace(ct242, ct249);
  const auto& ct251 = cc->EvalMult(ct148, pt109);
  cc->EvalAddInPlace(ct242, ct251);
  const auto& ct253 = cc->EvalMult(ct147, pt110);
  cc->EvalAddInPlace(ct242, ct253);
  const auto& ct255 = cc->EvalMult(ct146, pt111);
  cc->EvalAddInPlace(ct242, ct255);
  const auto& ct257 = cc->EvalRotate(ct242, 2560);
  cc->EvalAddInPlace(ct144, ct257);
  auto ct259 = cc->EvalMult(ct143, pt112);
  const auto& ct260 = cc->EvalMult(ct152, pt113);
  cc->EvalAddInPlace(ct259, ct260);
  const auto& ct262 = cc->EvalMult(ct151, pt114);
  cc->EvalAddInPlace(ct259, ct262);
  const auto& ct264 = cc->EvalMult(ct150, pt115);
  cc->EvalAddInPlace(ct259, ct264);
  const auto& ct266 = cc->EvalMult(ct149, pt116);
  cc->EvalAddInPlace(ct259, ct266);
  const auto& ct268 = cc->EvalMult(ct148, pt117);
  cc->EvalAddInPlace(ct259, ct268);
  const auto& ct270 = cc->EvalMult(ct147, pt118);
  cc->EvalAddInPlace(ct259, ct270);
  const auto& ct272 = cc->EvalMult(ct146, pt119);
  cc->EvalAddInPlace(ct259, ct272);
  const auto& ct274 = cc->EvalRotate(ct259, 3072);
  cc->EvalAddInPlace(ct144, ct274);
  auto ct276 = cc->EvalMult(ct143, pt120);
  const auto& ct277 = cc->EvalMult(ct152, pt121);
  cc->EvalAddInPlace(ct276, ct277);
  const auto& ct279 = cc->EvalMult(ct151, pt122);
  cc->EvalAddInPlace(ct276, ct279);
  const auto& ct281 = cc->EvalMult(ct150, pt123);
  cc->EvalAddInPlace(ct276, ct281);
  const auto& ct283 = cc->EvalMult(ct149, pt124);
  cc->EvalAddInPlace(ct276, ct283);
  const auto& ct285 = cc->EvalMult(ct148, pt125);
  cc->EvalAddInPlace(ct276, ct285);
  const auto& ct287 = cc->EvalMult(ct147, pt126);
  cc->EvalAddInPlace(ct276, ct287);
  const auto& ct289 = cc->EvalMult(ct146, pt127);
  cc->EvalAddInPlace(ct276, ct289);
  const auto& ct291 = cc->EvalRotate(ct276, 3584);
  cc->EvalAddInPlace(ct144, ct291);
  cc->ModReduceInPlace(ct144);
  v276[0] = ct144;
  return v276;
}
std::vector<CiphertextT> bert_attention__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk) {
  std::vector<float> v1(4096);
  for (int64_t v1_i0 = 0; v1_i0 < 1; ++v1_i0) {
    for (int64_t v1_i1 = 0; v1_i1 < 4096; ++v1_i1) {
      v1[v1_i1 + 4096 * (v1_i0)] = v0[0 + v1_i1 * 1 + 4096 * (0 + v1_i0 * 1)];
    }
  }
  std::vector<double> v2(std::begin(v1), std::end(v1));
  auto pt_filled_n = cc->GetCryptoParameters()->GetElementParams()->GetRingDimension() / 2;
  auto pt_filled = v2;
  pt_filled.clear();
  pt_filled.reserve(pt_filled_n);
  for (auto i = 0; i < pt_filled_n; ++i) {
    pt_filled.push_back(v2[i % v2.size()]);
  }
  auto pt = cc->MakeCKKSPackedPlaintext(pt_filled);
  const auto& ct = cc->Encrypt(pk, pt);
  const std::vector<CiphertextT> v3 = {ct};
  return v3;
}
std::vector<float> bert_attention__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk) {
  [[maybe_unused]] size_t v1 = 0;
  const auto& ct = v0[0];
  PlaintextT pt;
  cc->Decrypt(sk, ct, &pt);
  pt->SetLength(4096);
  const auto& v2_cast = pt->GetCKKSPackedValue();
  std::vector<float> v2(v2_cast.size());
  std::transform(std::begin(v2_cast), std::end(v2_cast), std::begin(v2), [](const std::complex<double>& c) { return c.real(); });
  return v2;
}
CryptoContextT bert_attention__generate_crypto_context() {
  CCParamsT params;
  params.SetMultiplicativeDepth(2);
  params.SetKeySwitchTechnique(HYBRID);
  CryptoContextT cc = GenCryptoContext(params);
  cc->Enable(PKE);
  cc->Enable(KEYSWITCH);
  cc->Enable(LEVELEDSHE);
  return cc;
}
CryptoContextT bert_attention__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk) {
  cc->EvalRotateKeyGen(sk, {64, 128, 2560, 192, 256, 320, 3072, 384, 448, 3584, 512, 1024, 1536, 2048});
  return cc;
}
