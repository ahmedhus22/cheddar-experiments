
#include <cmath>
#include <complex>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include "core/Context.h"
#include "core/Container.h"
#include "core/Parameter.h"
#include "core/Encode.h"
#include "core/EvkMap.h"
#include "core/EvkRequest.h"
#include "UserInterface.h"


  using namespace cheddar;
  using word = uint64_t;
  using Ct = Ciphertext<word>;
  using Pt = Plaintext<word>;
  using Const = Constant<word>;
  using Evk = EvaluationKey<word>;
  using EvkMapT = EvkMap<word>;
  using CtxPtr = std::shared_ptr<Context<word>>;
  using Param = Parameter<word>;
  using UI = UserInterface<word>;
  using Enc = Encoder<word>;
  using Complex = std::complex<double>;

std::vector<double> _assign_layout_10297891714507134769() {
  int32_t v0 = 1024;
  int32_t v1 = 8;
  std::vector<double> v2(8192, 0);
  int32_t v3 = 0;
  int32_t v4 = 1;
  std::vector<double> v5 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  std::vector<double> v8 = std::move(v2);
  for (int64_t v7 = 0; v7 < 8; v7 += 1) {
    std::vector<double> v11 = std::move(v8);
    for (int64_t v10 = 0; v10 < 1024; v10 += 1) {
      int32_t v12 = v10 % v1;
      int32_t v13 = v7 + v10;
      int32_t v14 = v13 % v1;
      int64_t v15 = static_cast<int64_t>(v12);
      int64_t v16 = static_cast<int64_t>(v14);
      double v17 = v5[v16 + 8 * (v15)];
      int64_t v18 = static_cast<int64_t>(v7);
      int64_t v19 = static_cast<int64_t>(v10);
      auto v20 = std::move(v11);
      v20[v19 + 1024 * (v18)] = v17;
      v11 = std::move(v20);
    }
    std::vector<double> v9 = std::move(v11);
    v8 = std::move(v9);
  }
  std::vector<double> v6 = std::move(v8);
  return v6;
}

std::vector<Ct> matvec_identity(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0) {
  int64_t v1 = 6;
  int64_t v2 = 3;
  int64_t v3 = 2;
  int64_t v4 = 1;
  int64_t v5 = 0;
  std::vector<double> v6 = _assign_layout_10297891714507134769();
  std::vector<double> v7(v6.begin() + 3 * 1024 + 0, v6.begin() + 3 * 1024 + 0 + 1021);
  std::vector<double> v8(v6.begin() + 3 * 1024 + 1021, v6.begin() + 3 * 1024 + 1021 + 3);
  std::vector<double> v9(1024);
  std::vector<double> v10(1024);
  std::copy(v7.begin(), v7.end(), v10.begin() + 0 * 1024 + 3);
  auto v11 = std::move(v10);
  std::copy(v8.begin(), v8.end(), v11.begin() + 0 * 1024 + 0);
  std::vector<double> v12(v6.begin() + 4 * 1024 + 0, v6.begin() + 4 * 1024 + 0 + 1021);
  std::vector<double> v13(v6.begin() + 4 * 1024 + 1021, v6.begin() + 4 * 1024 + 1021 + 3);
  std::vector<double> v14(1024);
  std::copy(v12.begin(), v12.end(), v14.begin() + 0 * 1024 + 3);
  auto v15 = std::move(v14);
  std::copy(v13.begin(), v13.end(), v15.begin() + 0 * 1024 + 0);
  std::vector<double> v16(v6.begin() + 5 * 1024 + 0, v6.begin() + 5 * 1024 + 0 + 1021);
  std::vector<double> v17(v6.begin() + 5 * 1024 + 1021, v6.begin() + 5 * 1024 + 1021 + 3);
  std::vector<double> v18(1024);
  std::copy(v16.begin(), v16.end(), v18.begin() + 0 * 1024 + 3);
  auto v19 = std::move(v18);
  std::copy(v17.begin(), v17.end(), v19.begin() + 0 * 1024 + 0);
  std::vector<double> v20(v6.begin() + 6 * 1024 + 0, v6.begin() + 6 * 1024 + 0 + 1018);
  std::vector<double> v21(v6.begin() + 6 * 1024 + 1018, v6.begin() + 6 * 1024 + 1018 + 6);
  std::vector<double> v22(1024);
  std::copy(v20.begin(), v20.end(), v22.begin() + 0 * 1024 + 6);
  auto v23 = std::move(v22);
  std::copy(v21.begin(), v21.end(), v23.begin() + 0 * 1024 + 0);
  std::vector<double> v24(v6.begin() + 7 * 1024 + 0, v6.begin() + 7 * 1024 + 0 + 1018);
  std::vector<double> v25(v6.begin() + 7 * 1024 + 1018, v6.begin() + 7 * 1024 + 1018 + 6);
  std::vector<double> v26(1024);
  std::copy(v24.begin(), v24.end(), v26.begin() + 0 * 1024 + 6);
  auto v27 = std::move(v26);
  std::copy(v25.begin(), v25.end(), v27.begin() + 0 * 1024 + 0);
  std::vector<double> v28(v6.begin() + 0 * 1024 + 0, v6.begin() + 0 * 1024 + 0 + 1024);
  Pt pt;
  std::vector<Complex> pt_complex(v28.begin(), v28.end());
  encoder.Encode(pt, 1, ctx->param_.GetScale(1), pt_complex);
  auto& ct = v0[v5];
  Ct ct1;
  ctx->Mult(ct1, ct, pt);
  Ct ct2;
  ctx->HRot(ct2, ct, ui.GetRotationKey(v4), v4);
  std::vector<double> v29(v6.begin() + 1 * 1024 + 0, v6.begin() + 1 * 1024 + 0 + 1024);
  Pt pt1;
  std::vector<Complex> pt1_complex(v29.begin(), v29.end());
  encoder.Encode(pt1, 1, ctx->param_.GetScale(1), pt1_complex);
  Ct ct3;
  ctx->Mult(ct3, ct2, pt1);
  Ct ct4;
  ctx->HRot(ct4, ct, ui.GetRotationKey(v3), v3);
  std::vector<double> v30(v6.begin() + 2 * 1024 + 0, v6.begin() + 2 * 1024 + 0 + 1024);
  Pt pt2;
  std::vector<Complex> pt2_complex(v30.begin(), v30.end());
  encoder.Encode(pt2, 1, ctx->param_.GetScale(1), pt2_complex);
  Ct ct5;
  ctx->Mult(ct5, ct4, pt2);
  std::vector<double> v31(v11.begin() + 0 * 1024 + 0, v11.begin() + 0 * 1024 + 0 + 1024);
  Pt pt3;
  std::vector<Complex> pt3_complex(v31.begin(), v31.end());
  encoder.Encode(pt3, 1, ctx->param_.GetScale(1), pt3_complex);
  Ct ct6;
  ctx->Mult(ct6, ct, pt3);
  std::vector<double> v32(v15.begin() + 0 * 1024 + 0, v15.begin() + 0 * 1024 + 0 + 1024);
  Pt pt4;
  std::vector<Complex> pt4_complex(v32.begin(), v32.end());
  encoder.Encode(pt4, 1, ctx->param_.GetScale(1), pt4_complex);
  Ct ct7;
  ctx->Mult(ct7, ct2, pt4);
  std::vector<double> v33(v19.begin() + 0 * 1024 + 0, v19.begin() + 0 * 1024 + 0 + 1024);
  Pt pt5;
  std::vector<Complex> pt5_complex(v33.begin(), v33.end());
  encoder.Encode(pt5, 1, ctx->param_.GetScale(1), pt5_complex);
  Ct ct8;
  ctx->Mult(ct8, ct4, pt5);
  Ct ct9;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct6.GetScale();
    double rhs_scale = ct7.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct9 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct9, ct6, ct7);
  Ct ct10;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct9.GetScale();
    double rhs_scale = ct8.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct10 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct10, ct9, ct8);
  Ct ct11;
  ctx->HRot(ct11, ct10, ui.GetRotationKey(v2), v2);
  std::vector<double> v34(v23.begin() + 0 * 1024 + 0, v23.begin() + 0 * 1024 + 0 + 1024);
  Pt pt6;
  std::vector<Complex> pt6_complex(v34.begin(), v34.end());
  encoder.Encode(pt6, 1, ctx->param_.GetScale(1), pt6_complex);
  Ct ct12;
  ctx->Mult(ct12, ct, pt6);
  std::vector<double> v35(v27.begin() + 0 * 1024 + 0, v27.begin() + 0 * 1024 + 0 + 1024);
  Pt pt7;
  std::vector<Complex> pt7_complex(v35.begin(), v35.end());
  encoder.Encode(pt7, 1, ctx->param_.GetScale(1), pt7_complex);
  Ct ct13;
  ctx->Mult(ct13, ct2, pt7);
  Ct ct14;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct12.GetScale();
    double rhs_scale = ct13.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct14 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct14, ct12, ct13);
  Ct ct15;
  ctx->HRot(ct15, ct14, ui.GetRotationKey(v1), v1);
  Ct ct16;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct1.GetScale();
    double rhs_scale = ct3.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct16 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct16, ct1, ct3);
  Ct ct17;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct5.GetScale();
    double rhs_scale = ct11.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct17 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct17, ct5, ct11);
  Ct ct18;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct17.GetScale();
    double rhs_scale = ct15.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct18 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct18, ct17, ct15);
  Ct ct19;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct16.GetScale();
    double rhs_scale = ct18.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct19 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct19, ct16, ct18);
  std::vector<Ct> v36;
  v36.resize(1);
  Ct ct20;
  ctx->Rescale(ct20, ct19);
  std::vector<Ct> v37;
  v37.resize(1);
  Ct ct20_c0;
  ctx->Copy(ct20_c0, ct20);
  v37[v5] = std::move(ct20_c0);
  return v37;
}

std::vector<Ct> matvec_identity__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1) {
  int64_t v1 = 0;
  int32_t v2 = 8;
  std::vector<double> v3(1024, 0);
  int32_t v4 = 0;
  int32_t v5 = 1;
  int32_t v6 = 1024;
  std::vector<double> v9 = std::move(v3);
  for (int64_t v8 = 0; v8 < 1024; v8 += 1) {
    int32_t v10 = v8 % v2;
    int64_t v11 = static_cast<int64_t>(v10);
    double v12 = v0[v11];
    int64_t v13 = static_cast<int64_t>(v8);
    auto v14 = std::move(v9);
    v14[v13 + 1024 * (v1)] = v12;
    v9 = std::move(v14);
  }
  std::vector<double> v7 = std::move(v9);
  std::vector<double> v15(v7.begin() + 0 * 1024 + 0, v7.begin() + 0 * 1024 + 0 + 1024);
  Pt pt;
  std::vector<Complex> pt_complex(v15.begin(), v15.end());
  encoder.Encode(pt, 1, ctx->param_.GetScale(1), pt_complex);
  Ct ct;
  ui.Encrypt(ct, pt);
  std::vector<Ct> v16;
  v16.reserve(1);
  Ct ct_c1;
  ctx->Copy(ct_c1, ct);
  v16.emplace_back(std::move(ct_c1));
  return v16;
}

std::vector<double> matvec_identity__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1) {
  int64_t v1 = 0;
  int32_t v2 = 1024;
  int32_t v3 = 8;
  int32_t v4 = 1;
  int32_t v5 = 0;
  std::vector<double> v6(8, 0);
  auto& ct = v0[v1];
  Pt pt;
  ui.Decrypt(pt, ct);
  std::vector<Complex> v7_complex;
  encoder.Decode(v7_complex, pt);
  std::vector<double> v7(v7_complex.size());
  for (size_t i = 0; i < v7_complex.size(); ++i) v7[i] = v7_complex[i].real();
  std::vector<double> v10 = std::move(v6);
  for (int64_t v9 = 0; v9 < 1024; v9 += 1) {
    int32_t v11 = v9 % v3;
    int64_t v12 = static_cast<int64_t>(v9);
    double v13 = v7[v12 + 1024 * (v1)];
    int64_t v14 = static_cast<int64_t>(v11);
    auto v15 = std::move(v10);
    v15[v14] = v13;
    v10 = std::move(v15);
  }
  std::vector<double> v8 = std::move(v10);
  return v8;
}

std::tuple<CtxPtr, UI> __configure() {
  static std::vector<word> main_primes = {1073742881ULL, 1073742721ULL, 1073741441ULL, 1073741857ULL, 524353ULL};
  static std::vector<word> aux_primes = {1073740609ULL, 1073739937ULL, 1073739649ULL};
  static std::vector<std::pair<int, int>> level_config = []() {
    std::vector<std::pair<int, int>> lc;
    for (int i = 1; i <= static_cast<int>(main_primes.size()); ++i)
      lc.push_back({i, 0});
    return lc;
  }();
  static Param param(4, static_cast<double>(1ULL << 45), static_cast<int>(main_primes.size()) - 1, level_config, main_primes, aux_primes);
  auto ctx = Context<word>::Create(param);
  UI ui(ctx);
  ui.PrepareRotationKey(1, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(2, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(3, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(6, static_cast<int>(main_primes.size()) - 1);
  return {ctx, std::move(ui)};
}

