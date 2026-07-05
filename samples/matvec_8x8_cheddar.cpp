
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

std::vector<double> _assign_layout_12040075739753753025(const std::vector<double>& v0) {
  int32_t v1 = 1024;
  int32_t v2 = 8;
  std::vector<double> v3(8192, 0);
  int32_t v4 = 0;
  int32_t v5 = 1;
  std::vector<double> v8 = std::move(v3);
  for (int64_t v7 = 0; v7 < 8; v7 += 1) {
    std::vector<double> v11 = std::move(v8);
    for (int64_t v10 = 0; v10 < 1024; v10 += 1) {
      int32_t v12 = v10 % v2;
      int32_t v13 = v7 + v10;
      int32_t v14 = v13 % v2;
      int64_t v15 = static_cast<int64_t>(v12);
      int64_t v16 = static_cast<int64_t>(v14);
      double v17 = v0[v16 + 8 * (v15)];
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
  std::vector<double> v5 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  int64_t v6 = 0;
  std::vector<double> v7 = _assign_layout_12040075739753753025(v5);
  std::vector<double> v8(v7.begin() + 3 * 1024 + 0, v7.begin() + 3 * 1024 + 0 + 1021);
  std::vector<double> v9(v7.begin() + 3 * 1024 + 1021, v7.begin() + 3 * 1024 + 1021 + 3);
  std::vector<double> v10(1024);
  std::vector<double> v11(1024);
  std::copy(v8.begin(), v8.end(), v11.begin() + 0 * 1024 + 3);
  auto v12 = std::move(v11);
  std::copy(v9.begin(), v9.end(), v12.begin() + 0 * 1024 + 0);
  std::vector<double> v13(v7.begin() + 4 * 1024 + 0, v7.begin() + 4 * 1024 + 0 + 1021);
  std::vector<double> v14(v7.begin() + 4 * 1024 + 1021, v7.begin() + 4 * 1024 + 1021 + 3);
  std::vector<double> v15(1024);
  std::copy(v13.begin(), v13.end(), v15.begin() + 0 * 1024 + 3);
  auto v16 = std::move(v15);
  std::copy(v14.begin(), v14.end(), v16.begin() + 0 * 1024 + 0);
  std::vector<double> v17(v7.begin() + 5 * 1024 + 0, v7.begin() + 5 * 1024 + 0 + 1021);
  std::vector<double> v18(v7.begin() + 5 * 1024 + 1021, v7.begin() + 5 * 1024 + 1021 + 3);
  std::vector<double> v19(1024);
  std::copy(v17.begin(), v17.end(), v19.begin() + 0 * 1024 + 3);
  auto v20 = std::move(v19);
  std::copy(v18.begin(), v18.end(), v20.begin() + 0 * 1024 + 0);
  std::vector<double> v21(v7.begin() + 6 * 1024 + 0, v7.begin() + 6 * 1024 + 0 + 1018);
  std::vector<double> v22(v7.begin() + 6 * 1024 + 1018, v7.begin() + 6 * 1024 + 1018 + 6);
  std::vector<double> v23(1024);
  std::copy(v21.begin(), v21.end(), v23.begin() + 0 * 1024 + 6);
  auto v24 = std::move(v23);
  std::copy(v22.begin(), v22.end(), v24.begin() + 0 * 1024 + 0);
  std::vector<double> v25(v7.begin() + 7 * 1024 + 0, v7.begin() + 7 * 1024 + 0 + 1018);
  std::vector<double> v26(v7.begin() + 7 * 1024 + 1018, v7.begin() + 7 * 1024 + 1018 + 6);
  std::vector<double> v27(1024);
  std::copy(v25.begin(), v25.end(), v27.begin() + 0 * 1024 + 6);
  auto v28 = std::move(v27);
  std::copy(v26.begin(), v26.end(), v28.begin() + 0 * 1024 + 0);
  std::vector<double> v29(v7.begin() + 0 * 1024 + 0, v7.begin() + 0 * 1024 + 0 + 1024);
  Pt pt;
  std::vector<Complex> pt_complex(v29.begin(), v29.end());
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  auto& ct = v0[v6];
  Ct ct1;
  ctx->Mult(ct1, ct, pt);
  Ct ct2;
  ctx->HRot(ct2, ct, ui.GetRotationKey(v4), v4);
  std::vector<double> v30(v7.begin() + 1 * 1024 + 0, v7.begin() + 1 * 1024 + 0 + 1024);
  Pt pt1;
  std::vector<Complex> pt1_complex(v30.begin(), v30.end());
  encoder.Encode(pt1, 2, ctx->param_.GetScale(2), pt1_complex);
  Ct ct3;
  ctx->Mult(ct3, ct2, pt1);
  Ct ct4;
  ctx->HRot(ct4, ct, ui.GetRotationKey(v3), v3);
  std::vector<double> v31(v7.begin() + 2 * 1024 + 0, v7.begin() + 2 * 1024 + 0 + 1024);
  Pt pt2;
  std::vector<Complex> pt2_complex(v31.begin(), v31.end());
  encoder.Encode(pt2, 2, ctx->param_.GetScale(2), pt2_complex);
  Ct ct5;
  ctx->Mult(ct5, ct4, pt2);
  std::vector<double> v32(v12.begin() + 0 * 1024 + 0, v12.begin() + 0 * 1024 + 0 + 1024);
  Pt pt3;
  std::vector<Complex> pt3_complex(v32.begin(), v32.end());
  encoder.Encode(pt3, 2, ctx->param_.GetScale(2), pt3_complex);
  Ct ct6;
  ctx->Mult(ct6, ct, pt3);
  std::vector<double> v33(v16.begin() + 0 * 1024 + 0, v16.begin() + 0 * 1024 + 0 + 1024);
  Pt pt4;
  std::vector<Complex> pt4_complex(v33.begin(), v33.end());
  encoder.Encode(pt4, 2, ctx->param_.GetScale(2), pt4_complex);
  Ct ct7;
  ctx->Mult(ct7, ct2, pt4);
  std::vector<double> v34(v20.begin() + 0 * 1024 + 0, v20.begin() + 0 * 1024 + 0 + 1024);
  Pt pt5;
  std::vector<Complex> pt5_complex(v34.begin(), v34.end());
  encoder.Encode(pt5, 2, ctx->param_.GetScale(2), pt5_complex);
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
  std::vector<double> v35(v24.begin() + 0 * 1024 + 0, v24.begin() + 0 * 1024 + 0 + 1024);
  Pt pt6;
  std::vector<Complex> pt6_complex(v35.begin(), v35.end());
  encoder.Encode(pt6, 2, ctx->param_.GetScale(2), pt6_complex);
  Ct ct12;
  ctx->Mult(ct12, ct, pt6);
  std::vector<double> v36(v28.begin() + 0 * 1024 + 0, v28.begin() + 0 * 1024 + 0 + 1024);
  Pt pt7;
  std::vector<Complex> pt7_complex(v36.begin(), v36.end());
  encoder.Encode(pt7, 2, ctx->param_.GetScale(2), pt7_complex);
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
  std::vector<Ct> v37;
  v37.resize(1);
  Ct ct20;
  ctx->Rescale(ct20, ct19);
  std::vector<Ct> v38;
  v38.resize(1);
  Ct ct20_c0;
  ctx->Copy(ct20_c0, ct20);
  v38[v6] = std::move(ct20_c0);
  return v38;
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
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
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

std::vector<Ct> matvec_shift(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0) {
  int64_t v1 = 6;
  int64_t v2 = 3;
  int64_t v3 = 2;
  int64_t v4 = 1;
  std::vector<double> v5 = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0};
  int64_t v6 = 0;
  std::vector<double> v7 = _assign_layout_12040075739753753025(v5);
  std::vector<double> v8(v7.begin() + 3 * 1024 + 0, v7.begin() + 3 * 1024 + 0 + 1021);
  std::vector<double> v9(v7.begin() + 3 * 1024 + 1021, v7.begin() + 3 * 1024 + 1021 + 3);
  std::vector<double> v10(1024);
  std::vector<double> v11(1024);
  std::copy(v8.begin(), v8.end(), v11.begin() + 0 * 1024 + 3);
  auto v12 = std::move(v11);
  std::copy(v9.begin(), v9.end(), v12.begin() + 0 * 1024 + 0);
  std::vector<double> v13(v7.begin() + 4 * 1024 + 0, v7.begin() + 4 * 1024 + 0 + 1021);
  std::vector<double> v14(v7.begin() + 4 * 1024 + 1021, v7.begin() + 4 * 1024 + 1021 + 3);
  std::vector<double> v15(1024);
  std::copy(v13.begin(), v13.end(), v15.begin() + 0 * 1024 + 3);
  auto v16 = std::move(v15);
  std::copy(v14.begin(), v14.end(), v16.begin() + 0 * 1024 + 0);
  std::vector<double> v17(v7.begin() + 5 * 1024 + 0, v7.begin() + 5 * 1024 + 0 + 1021);
  std::vector<double> v18(v7.begin() + 5 * 1024 + 1021, v7.begin() + 5 * 1024 + 1021 + 3);
  std::vector<double> v19(1024);
  std::copy(v17.begin(), v17.end(), v19.begin() + 0 * 1024 + 3);
  auto v20 = std::move(v19);
  std::copy(v18.begin(), v18.end(), v20.begin() + 0 * 1024 + 0);
  std::vector<double> v21(v7.begin() + 6 * 1024 + 0, v7.begin() + 6 * 1024 + 0 + 1018);
  std::vector<double> v22(v7.begin() + 6 * 1024 + 1018, v7.begin() + 6 * 1024 + 1018 + 6);
  std::vector<double> v23(1024);
  std::copy(v21.begin(), v21.end(), v23.begin() + 0 * 1024 + 6);
  auto v24 = std::move(v23);
  std::copy(v22.begin(), v22.end(), v24.begin() + 0 * 1024 + 0);
  std::vector<double> v25(v7.begin() + 7 * 1024 + 0, v7.begin() + 7 * 1024 + 0 + 1018);
  std::vector<double> v26(v7.begin() + 7 * 1024 + 1018, v7.begin() + 7 * 1024 + 1018 + 6);
  std::vector<double> v27(1024);
  std::copy(v25.begin(), v25.end(), v27.begin() + 0 * 1024 + 6);
  auto v28 = std::move(v27);
  std::copy(v26.begin(), v26.end(), v28.begin() + 0 * 1024 + 0);
  std::vector<double> v29(v7.begin() + 0 * 1024 + 0, v7.begin() + 0 * 1024 + 0 + 1024);
  Pt pt;
  std::vector<Complex> pt_complex(v29.begin(), v29.end());
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  auto& ct = v0[v6];
  Ct ct1;
  ctx->Mult(ct1, ct, pt);
  Ct ct2;
  ctx->HRot(ct2, ct, ui.GetRotationKey(v4), v4);
  std::vector<double> v30(v7.begin() + 1 * 1024 + 0, v7.begin() + 1 * 1024 + 0 + 1024);
  Pt pt1;
  std::vector<Complex> pt1_complex(v30.begin(), v30.end());
  encoder.Encode(pt1, 2, ctx->param_.GetScale(2), pt1_complex);
  Ct ct3;
  ctx->Mult(ct3, ct2, pt1);
  Ct ct4;
  ctx->HRot(ct4, ct, ui.GetRotationKey(v3), v3);
  std::vector<double> v31(v7.begin() + 2 * 1024 + 0, v7.begin() + 2 * 1024 + 0 + 1024);
  Pt pt2;
  std::vector<Complex> pt2_complex(v31.begin(), v31.end());
  encoder.Encode(pt2, 2, ctx->param_.GetScale(2), pt2_complex);
  Ct ct5;
  ctx->Mult(ct5, ct4, pt2);
  std::vector<double> v32(v12.begin() + 0 * 1024 + 0, v12.begin() + 0 * 1024 + 0 + 1024);
  Pt pt3;
  std::vector<Complex> pt3_complex(v32.begin(), v32.end());
  encoder.Encode(pt3, 2, ctx->param_.GetScale(2), pt3_complex);
  Ct ct6;
  ctx->Mult(ct6, ct, pt3);
  std::vector<double> v33(v16.begin() + 0 * 1024 + 0, v16.begin() + 0 * 1024 + 0 + 1024);
  Pt pt4;
  std::vector<Complex> pt4_complex(v33.begin(), v33.end());
  encoder.Encode(pt4, 2, ctx->param_.GetScale(2), pt4_complex);
  Ct ct7;
  ctx->Mult(ct7, ct2, pt4);
  std::vector<double> v34(v20.begin() + 0 * 1024 + 0, v20.begin() + 0 * 1024 + 0 + 1024);
  Pt pt5;
  std::vector<Complex> pt5_complex(v34.begin(), v34.end());
  encoder.Encode(pt5, 2, ctx->param_.GetScale(2), pt5_complex);
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
  std::vector<double> v35(v24.begin() + 0 * 1024 + 0, v24.begin() + 0 * 1024 + 0 + 1024);
  Pt pt6;
  std::vector<Complex> pt6_complex(v35.begin(), v35.end());
  encoder.Encode(pt6, 2, ctx->param_.GetScale(2), pt6_complex);
  Ct ct12;
  ctx->Mult(ct12, ct, pt6);
  std::vector<double> v36(v28.begin() + 0 * 1024 + 0, v28.begin() + 0 * 1024 + 0 + 1024);
  Pt pt7;
  std::vector<Complex> pt7_complex(v36.begin(), v36.end());
  encoder.Encode(pt7, 2, ctx->param_.GetScale(2), pt7_complex);
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
  std::vector<Ct> v37;
  v37.resize(1);
  Ct ct20;
  ctx->Rescale(ct20, ct19);
  std::vector<Ct> v38;
  v38.resize(1);
  Ct ct20_c2;
  ctx->Copy(ct20_c2, ct20);
  v38[v6] = std::move(ct20_c2);
  return v38;
}

std::vector<Ct> matvec_shift__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1) {
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
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  Ct ct;
  ui.Encrypt(ct, pt);
  std::vector<Ct> v16;
  v16.reserve(1);
  Ct ct_c3;
  ctx->Copy(ct_c3, ct);
  v16.emplace_back(std::move(ct_c3));
  return v16;
}

std::vector<double> matvec_shift__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1) {
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

std::vector<Ct> matvec_random(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0) {
  int64_t v1 = 6;
  int64_t v2 = 3;
  int64_t v3 = 2;
  int64_t v4 = 1;
  std::vector<double> v5 = {0.811626255512237, 1.90635716915131, 1.49078845977783, 1.23745107650757, 0.396435409784317, 0.396389603614807, 0.210358858108521, 1.74573469161987, 1.24211847782135, 1.44533789157867, 0.139110535383224, 1.94282877445221, 1.68164098262787, 0.503444314002991, 0.445467442274094, 0.448468565940857, 0.678060233592987, 1.09703719615936, 0.920695543289185, 0.653335392475128, 1.26252055168152, 0.365038335323334, 0.655074834823608, 0.796087503433228, 0.966532945632934, 1.59183430671692, 0.479380190372467, 1.07704544067383, 1.22558772563934, 0.188255786895752, 1.2543351650238, 0.423995822668076, 0.223598033189774, 1.90288257598877, 1.93470084667206, 1.63595497608185, 0.678766131401062, 0.285577028989792, 1.40004277229309, 0.936289727687835, 0.331872642040253, 1.04083609580994, 0.165338188409805, 1.82770872116089, 0.591681957244873, 1.35879230499268, 0.692251026630401, 1.08812928199768, 1.1387494802475, 0.451223462820053, 1.94221079349518, 1.57275235652924, 1.88504803180695, 1.80017197132111, 1.23600995540619, 1.85156106948853, 0.268135756254196, 0.472367435693741, 0.185931846499443, 0.718127608299255, 0.838486850261688, 0.615563154220581, 1.67460131645203, 0.777831315994263};
  int64_t v6 = 0;
  std::vector<double> v7 = _assign_layout_12040075739753753025(v5);
  std::vector<double> v8(v7.begin() + 3 * 1024 + 0, v7.begin() + 3 * 1024 + 0 + 1021);
  std::vector<double> v9(v7.begin() + 3 * 1024 + 1021, v7.begin() + 3 * 1024 + 1021 + 3);
  std::vector<double> v10(1024);
  std::vector<double> v11(1024);
  std::copy(v8.begin(), v8.end(), v11.begin() + 0 * 1024 + 3);
  auto v12 = std::move(v11);
  std::copy(v9.begin(), v9.end(), v12.begin() + 0 * 1024 + 0);
  std::vector<double> v13(v7.begin() + 4 * 1024 + 0, v7.begin() + 4 * 1024 + 0 + 1021);
  std::vector<double> v14(v7.begin() + 4 * 1024 + 1021, v7.begin() + 4 * 1024 + 1021 + 3);
  std::vector<double> v15(1024);
  std::copy(v13.begin(), v13.end(), v15.begin() + 0 * 1024 + 3);
  auto v16 = std::move(v15);
  std::copy(v14.begin(), v14.end(), v16.begin() + 0 * 1024 + 0);
  std::vector<double> v17(v7.begin() + 5 * 1024 + 0, v7.begin() + 5 * 1024 + 0 + 1021);
  std::vector<double> v18(v7.begin() + 5 * 1024 + 1021, v7.begin() + 5 * 1024 + 1021 + 3);
  std::vector<double> v19(1024);
  std::copy(v17.begin(), v17.end(), v19.begin() + 0 * 1024 + 3);
  auto v20 = std::move(v19);
  std::copy(v18.begin(), v18.end(), v20.begin() + 0 * 1024 + 0);
  std::vector<double> v21(v7.begin() + 6 * 1024 + 0, v7.begin() + 6 * 1024 + 0 + 1018);
  std::vector<double> v22(v7.begin() + 6 * 1024 + 1018, v7.begin() + 6 * 1024 + 1018 + 6);
  std::vector<double> v23(1024);
  std::copy(v21.begin(), v21.end(), v23.begin() + 0 * 1024 + 6);
  auto v24 = std::move(v23);
  std::copy(v22.begin(), v22.end(), v24.begin() + 0 * 1024 + 0);
  std::vector<double> v25(v7.begin() + 7 * 1024 + 0, v7.begin() + 7 * 1024 + 0 + 1018);
  std::vector<double> v26(v7.begin() + 7 * 1024 + 1018, v7.begin() + 7 * 1024 + 1018 + 6);
  std::vector<double> v27(1024);
  std::copy(v25.begin(), v25.end(), v27.begin() + 0 * 1024 + 6);
  auto v28 = std::move(v27);
  std::copy(v26.begin(), v26.end(), v28.begin() + 0 * 1024 + 0);
  std::vector<double> v29(v7.begin() + 0 * 1024 + 0, v7.begin() + 0 * 1024 + 0 + 1024);
  Pt pt;
  std::vector<Complex> pt_complex(v29.begin(), v29.end());
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  auto& ct = v0[v6];
  Ct ct1;
  ctx->Mult(ct1, ct, pt);
  Ct ct2;
  ctx->HRot(ct2, ct, ui.GetRotationKey(v4), v4);
  std::vector<double> v30(v7.begin() + 1 * 1024 + 0, v7.begin() + 1 * 1024 + 0 + 1024);
  Pt pt1;
  std::vector<Complex> pt1_complex(v30.begin(), v30.end());
  encoder.Encode(pt1, 2, ctx->param_.GetScale(2), pt1_complex);
  Ct ct3;
  ctx->Mult(ct3, ct2, pt1);
  Ct ct4;
  ctx->HRot(ct4, ct, ui.GetRotationKey(v3), v3);
  std::vector<double> v31(v7.begin() + 2 * 1024 + 0, v7.begin() + 2 * 1024 + 0 + 1024);
  Pt pt2;
  std::vector<Complex> pt2_complex(v31.begin(), v31.end());
  encoder.Encode(pt2, 2, ctx->param_.GetScale(2), pt2_complex);
  Ct ct5;
  ctx->Mult(ct5, ct4, pt2);
  std::vector<double> v32(v12.begin() + 0 * 1024 + 0, v12.begin() + 0 * 1024 + 0 + 1024);
  Pt pt3;
  std::vector<Complex> pt3_complex(v32.begin(), v32.end());
  encoder.Encode(pt3, 2, ctx->param_.GetScale(2), pt3_complex);
  Ct ct6;
  ctx->Mult(ct6, ct, pt3);
  std::vector<double> v33(v16.begin() + 0 * 1024 + 0, v16.begin() + 0 * 1024 + 0 + 1024);
  Pt pt4;
  std::vector<Complex> pt4_complex(v33.begin(), v33.end());
  encoder.Encode(pt4, 2, ctx->param_.GetScale(2), pt4_complex);
  Ct ct7;
  ctx->Mult(ct7, ct2, pt4);
  std::vector<double> v34(v20.begin() + 0 * 1024 + 0, v20.begin() + 0 * 1024 + 0 + 1024);
  Pt pt5;
  std::vector<Complex> pt5_complex(v34.begin(), v34.end());
  encoder.Encode(pt5, 2, ctx->param_.GetScale(2), pt5_complex);
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
  std::vector<double> v35(v24.begin() + 0 * 1024 + 0, v24.begin() + 0 * 1024 + 0 + 1024);
  Pt pt6;
  std::vector<Complex> pt6_complex(v35.begin(), v35.end());
  encoder.Encode(pt6, 2, ctx->param_.GetScale(2), pt6_complex);
  Ct ct12;
  ctx->Mult(ct12, ct, pt6);
  std::vector<double> v36(v28.begin() + 0 * 1024 + 0, v28.begin() + 0 * 1024 + 0 + 1024);
  Pt pt7;
  std::vector<Complex> pt7_complex(v36.begin(), v36.end());
  encoder.Encode(pt7, 2, ctx->param_.GetScale(2), pt7_complex);
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
  std::vector<Ct> v37;
  v37.resize(1);
  Ct ct20;
  ctx->Rescale(ct20, ct19);
  std::vector<Ct> v38;
  v38.resize(1);
  Ct ct20_c4;
  ctx->Copy(ct20_c4, ct20);
  v38[v6] = std::move(ct20_c4);
  return v38;
}

std::vector<Ct> matvec_random__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1) {
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
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  Ct ct;
  ui.Encrypt(ct, pt);
  std::vector<Ct> v16;
  v16.reserve(1);
  Ct ct_c5;
  ctx->Copy(ct_c5, ct);
  v16.emplace_back(std::move(ct_c5));
  return v16;
}

std::vector<double> matvec_random__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1) {
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

std::vector<Ct> matvec_chain(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0) {
  int64_t v1 = 6;
  int64_t v2 = 3;
  int64_t v3 = 2;
  int64_t v4 = 1;
  std::vector<double> v5 = {1.20000004768372, 0.790000021457672, 0.730000019073486, 1.04999995231628, 1.22000002861023, 0.9200000166893, 1.48000001907349, 1.17999994754791, 0.980000019073486, 0.889999985694885, 0.839999973773956, 1.23000001907349, 0.939999997615814, 0.560000002384186, 0.899999976158142, 1.24000000953674, 0.680000007152557, 0.680000007152557, 1.02999997138977, 1.02999997138977, 1.12999999523163, 1.35000002384186, 1.22000002861023, 1.11000001430511, 1.22000002861023, 0.819999992847442, 0.860000014305114, 0.730000019073486, 0.790000021457672, 1.12999999523163, 0.589999973773956, 0.930000007152557, 0.930000007152557, 0.990000009536743, 0.930000007152557, 0.810000002384185, 0.930000007152557, 1.38999998569489, 1.44000005722046, 1, 1.12000000476837, 0.620000004768372, 0.819999992847442, 0.910000026226043, 1.37000000476837, 0.75, 0.980000019073486, 1.49000000953674, 1.01999998092651, 1.11000001430511, 0.620000004768372, 1.33000004291534, 1.10000002384186, 1.04999995231628, 0.839999973773956, 0.800000011920928, 0.9200000166893, 1.17999994754791, 1.37999999523163, 1.00999999046326, 1.16999995708466, 1.0900000333786, 1.12000000476837, 1.16999995708466};
  std::vector<double> v6 = {1.3400000333786, 0.579999983310699, 1.25999999046326, 0.740000009536743, 0.689999997615814, 1.07000005245209, 0.600000023841858, 1.38999998569489, 1.12999999523163, 1.22000002861023, 0.519999980926514, 1.0900000333786, 1.05999994277954, 0.660000026226043, 0.649999976158142, 1.20000004768372, 0.819999992847442, 1.19000005722046, 1.04999995231628, 0.889999985694885, 1.42999994754791, 1.3400000333786, 0.860000014305114, 0.540000021457672, 0.800000011920928, 0.899999976158142, 1.20000004768372, 1.5, 0.860000014305114, 1.25999999046326, 1.0900000333786, 1.19000005722046, 0.649999976158142, 0.899999976158142, 0.740000009536743, 0.839999973773956, 1.00999999046326, 1.16999995708466, 0.610000014305115, 0.629999995231628, 0.819999992847442, 1.1599999666214, 1.35000002384186, 1.04999995231628, 1.35000002384186, 0.879999995231628, 0.819999992847442, 0.850000023841857, 0.6700000166893, 1.33000004291534, 0.839999973773956, 1.04999995231628, 1.08000004291534, 1.01999998092651, 0.5, 1.49000000953674, 1.4099999666214, 0.709999978542327, 0.790000021457672, 1.01999998092651, 1.39999997615814, 1.48000001907349, 0.759999990463257, 1.05999994277954};
  int64_t v7 = 0;
  std::vector<double> v8 = _assign_layout_12040075739753753025(v6);
  std::vector<double> v9 = _assign_layout_12040075739753753025(v5);
  std::vector<double> v10(v9.begin() + 3 * 1024 + 0, v9.begin() + 3 * 1024 + 0 + 1021);
  std::vector<double> v11(v9.begin() + 3 * 1024 + 1021, v9.begin() + 3 * 1024 + 1021 + 3);
  std::vector<double> v12(1024);
  std::vector<double> v13(1024);
  std::copy(v10.begin(), v10.end(), v13.begin() + 0 * 1024 + 3);
  auto v14 = std::move(v13);
  std::copy(v11.begin(), v11.end(), v14.begin() + 0 * 1024 + 0);
  std::vector<double> v15(v9.begin() + 4 * 1024 + 0, v9.begin() + 4 * 1024 + 0 + 1021);
  std::vector<double> v16(v9.begin() + 4 * 1024 + 1021, v9.begin() + 4 * 1024 + 1021 + 3);
  std::vector<double> v17(1024);
  std::copy(v15.begin(), v15.end(), v17.begin() + 0 * 1024 + 3);
  auto v18 = std::move(v17);
  std::copy(v16.begin(), v16.end(), v18.begin() + 0 * 1024 + 0);
  std::vector<double> v19(v9.begin() + 5 * 1024 + 0, v9.begin() + 5 * 1024 + 0 + 1021);
  std::vector<double> v20(v9.begin() + 5 * 1024 + 1021, v9.begin() + 5 * 1024 + 1021 + 3);
  std::vector<double> v21(1024);
  std::copy(v19.begin(), v19.end(), v21.begin() + 0 * 1024 + 3);
  auto v22 = std::move(v21);
  std::copy(v20.begin(), v20.end(), v22.begin() + 0 * 1024 + 0);
  std::vector<double> v23(v9.begin() + 6 * 1024 + 0, v9.begin() + 6 * 1024 + 0 + 1018);
  std::vector<double> v24(v9.begin() + 6 * 1024 + 1018, v9.begin() + 6 * 1024 + 1018 + 6);
  std::vector<double> v25(1024);
  std::copy(v23.begin(), v23.end(), v25.begin() + 0 * 1024 + 6);
  auto v26 = std::move(v25);
  std::copy(v24.begin(), v24.end(), v26.begin() + 0 * 1024 + 0);
  std::vector<double> v27(v9.begin() + 7 * 1024 + 0, v9.begin() + 7 * 1024 + 0 + 1018);
  std::vector<double> v28(v9.begin() + 7 * 1024 + 1018, v9.begin() + 7 * 1024 + 1018 + 6);
  std::vector<double> v29(1024);
  std::copy(v27.begin(), v27.end(), v29.begin() + 0 * 1024 + 6);
  auto v30 = std::move(v29);
  std::copy(v28.begin(), v28.end(), v30.begin() + 0 * 1024 + 0);
  std::vector<double> v31(v8.begin() + 3 * 1024 + 0, v8.begin() + 3 * 1024 + 0 + 1021);
  std::vector<double> v32(v8.begin() + 3 * 1024 + 1021, v8.begin() + 3 * 1024 + 1021 + 3);
  std::vector<double> v33(1024);
  std::copy(v31.begin(), v31.end(), v33.begin() + 0 * 1024 + 3);
  auto v34 = std::move(v33);
  std::copy(v32.begin(), v32.end(), v34.begin() + 0 * 1024 + 0);
  std::vector<double> v35(v8.begin() + 4 * 1024 + 0, v8.begin() + 4 * 1024 + 0 + 1021);
  std::vector<double> v36(v8.begin() + 4 * 1024 + 1021, v8.begin() + 4 * 1024 + 1021 + 3);
  std::vector<double> v37(1024);
  std::copy(v35.begin(), v35.end(), v37.begin() + 0 * 1024 + 3);
  auto v38 = std::move(v37);
  std::copy(v36.begin(), v36.end(), v38.begin() + 0 * 1024 + 0);
  std::vector<double> v39(v8.begin() + 5 * 1024 + 0, v8.begin() + 5 * 1024 + 0 + 1021);
  std::vector<double> v40(v8.begin() + 5 * 1024 + 1021, v8.begin() + 5 * 1024 + 1021 + 3);
  std::vector<double> v41(1024);
  std::copy(v39.begin(), v39.end(), v41.begin() + 0 * 1024 + 3);
  auto v42 = std::move(v41);
  std::copy(v40.begin(), v40.end(), v42.begin() + 0 * 1024 + 0);
  std::vector<double> v43(v8.begin() + 6 * 1024 + 0, v8.begin() + 6 * 1024 + 0 + 1018);
  std::vector<double> v44(v8.begin() + 6 * 1024 + 1018, v8.begin() + 6 * 1024 + 1018 + 6);
  std::vector<double> v45(1024);
  std::copy(v43.begin(), v43.end(), v45.begin() + 0 * 1024 + 6);
  auto v46 = std::move(v45);
  std::copy(v44.begin(), v44.end(), v46.begin() + 0 * 1024 + 0);
  std::vector<double> v47(v8.begin() + 7 * 1024 + 0, v8.begin() + 7 * 1024 + 0 + 1018);
  std::vector<double> v48(v8.begin() + 7 * 1024 + 1018, v8.begin() + 7 * 1024 + 1018 + 6);
  std::vector<double> v49(1024);
  std::copy(v47.begin(), v47.end(), v49.begin() + 0 * 1024 + 6);
  auto v50 = std::move(v49);
  std::copy(v48.begin(), v48.end(), v50.begin() + 0 * 1024 + 0);
  std::vector<double> v51(v8.begin() + 0 * 1024 + 0, v8.begin() + 0 * 1024 + 0 + 1024);
  Pt pt;
  std::vector<Complex> pt_complex(v51.begin(), v51.end());
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  auto& ct = v0[v7];
  Ct ct1;
  ctx->Mult(ct1, ct, pt);
  Ct ct2;
  ctx->HRot(ct2, ct, ui.GetRotationKey(v4), v4);
  std::vector<double> v52(v8.begin() + 1 * 1024 + 0, v8.begin() + 1 * 1024 + 0 + 1024);
  Pt pt1;
  std::vector<Complex> pt1_complex(v52.begin(), v52.end());
  encoder.Encode(pt1, 2, ctx->param_.GetScale(2), pt1_complex);
  Ct ct3;
  ctx->Mult(ct3, ct2, pt1);
  Ct ct4;
  ctx->HRot(ct4, ct, ui.GetRotationKey(v3), v3);
  std::vector<double> v53(v8.begin() + 2 * 1024 + 0, v8.begin() + 2 * 1024 + 0 + 1024);
  Pt pt2;
  std::vector<Complex> pt2_complex(v53.begin(), v53.end());
  encoder.Encode(pt2, 2, ctx->param_.GetScale(2), pt2_complex);
  Ct ct5;
  ctx->Mult(ct5, ct4, pt2);
  std::vector<double> v54(v34.begin() + 0 * 1024 + 0, v34.begin() + 0 * 1024 + 0 + 1024);
  Pt pt3;
  std::vector<Complex> pt3_complex(v54.begin(), v54.end());
  encoder.Encode(pt3, 2, ctx->param_.GetScale(2), pt3_complex);
  Ct ct6;
  ctx->Mult(ct6, ct, pt3);
  std::vector<double> v55(v38.begin() + 0 * 1024 + 0, v38.begin() + 0 * 1024 + 0 + 1024);
  Pt pt4;
  std::vector<Complex> pt4_complex(v55.begin(), v55.end());
  encoder.Encode(pt4, 2, ctx->param_.GetScale(2), pt4_complex);
  Ct ct7;
  ctx->Mult(ct7, ct2, pt4);
  std::vector<double> v56(v42.begin() + 0 * 1024 + 0, v42.begin() + 0 * 1024 + 0 + 1024);
  Pt pt5;
  std::vector<Complex> pt5_complex(v56.begin(), v56.end());
  encoder.Encode(pt5, 2, ctx->param_.GetScale(2), pt5_complex);
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
  std::vector<double> v57(v46.begin() + 0 * 1024 + 0, v46.begin() + 0 * 1024 + 0 + 1024);
  Pt pt6;
  std::vector<Complex> pt6_complex(v57.begin(), v57.end());
  encoder.Encode(pt6, 2, ctx->param_.GetScale(2), pt6_complex);
  Ct ct12;
  ctx->Mult(ct12, ct, pt6);
  std::vector<double> v58(v50.begin() + 0 * 1024 + 0, v50.begin() + 0 * 1024 + 0 + 1024);
  Pt pt7;
  std::vector<Complex> pt7_complex(v58.begin(), v58.end());
  encoder.Encode(pt7, 2, ctx->param_.GetScale(2), pt7_complex);
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
  Ct ct20;
  ctx->Rescale(ct20, ct19);
  std::vector<double> v59(v9.begin() + 0 * 1024 + 0, v9.begin() + 0 * 1024 + 0 + 1024);
  Pt pt8;
  std::vector<Complex> pt8_complex(v59.begin(), v59.end());
  encoder.Encode(pt8, 1, ctx->param_.GetScale(1), pt8_complex);
  Ct ct21;
  ctx->Mult(ct21, ct20, pt8);
  Ct ct22;
  ctx->HRot(ct22, ct19, ui.GetRotationKey(v4), v4);
  Ct ct23;
  ctx->Rescale(ct23, ct22);
  std::vector<double> v60(v9.begin() + 1 * 1024 + 0, v9.begin() + 1 * 1024 + 0 + 1024);
  Pt pt9;
  std::vector<Complex> pt9_complex(v60.begin(), v60.end());
  encoder.Encode(pt9, 1, ctx->param_.GetScale(1), pt9_complex);
  Ct ct24;
  ctx->Mult(ct24, ct23, pt9);
  Ct ct25;
  ctx->HRot(ct25, ct19, ui.GetRotationKey(v3), v3);
  Ct ct26;
  ctx->Rescale(ct26, ct25);
  std::vector<double> v61(v9.begin() + 2 * 1024 + 0, v9.begin() + 2 * 1024 + 0 + 1024);
  Pt pt10;
  std::vector<Complex> pt10_complex(v61.begin(), v61.end());
  encoder.Encode(pt10, 1, ctx->param_.GetScale(1), pt10_complex);
  Ct ct27;
  ctx->Mult(ct27, ct26, pt10);
  std::vector<double> v62(v14.begin() + 0 * 1024 + 0, v14.begin() + 0 * 1024 + 0 + 1024);
  Pt pt11;
  std::vector<Complex> pt11_complex(v62.begin(), v62.end());
  encoder.Encode(pt11, 1, ctx->param_.GetScale(1), pt11_complex);
  Ct ct28;
  ctx->Mult(ct28, ct20, pt11);
  std::vector<double> v63(v18.begin() + 0 * 1024 + 0, v18.begin() + 0 * 1024 + 0 + 1024);
  Pt pt12;
  std::vector<Complex> pt12_complex(v63.begin(), v63.end());
  encoder.Encode(pt12, 1, ctx->param_.GetScale(1), pt12_complex);
  Ct ct29;
  ctx->Mult(ct29, ct23, pt12);
  std::vector<double> v64(v22.begin() + 0 * 1024 + 0, v22.begin() + 0 * 1024 + 0 + 1024);
  Pt pt13;
  std::vector<Complex> pt13_complex(v64.begin(), v64.end());
  encoder.Encode(pt13, 1, ctx->param_.GetScale(1), pt13_complex);
  Ct ct30;
  ctx->Mult(ct30, ct26, pt13);
  Ct ct31;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct28.GetScale();
    double rhs_scale = ct29.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct31 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct31, ct28, ct29);
  Ct ct32;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct31.GetScale();
    double rhs_scale = ct30.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct32 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct32, ct31, ct30);
  Ct ct33;
  ctx->HRot(ct33, ct32, ui.GetRotationKey(v2), v2);
  std::vector<double> v65(v26.begin() + 0 * 1024 + 0, v26.begin() + 0 * 1024 + 0 + 1024);
  Pt pt14;
  std::vector<Complex> pt14_complex(v65.begin(), v65.end());
  encoder.Encode(pt14, 1, ctx->param_.GetScale(1), pt14_complex);
  Ct ct34;
  ctx->Mult(ct34, ct20, pt14);
  std::vector<double> v66(v30.begin() + 0 * 1024 + 0, v30.begin() + 0 * 1024 + 0 + 1024);
  Pt pt15;
  std::vector<Complex> pt15_complex(v66.begin(), v66.end());
  encoder.Encode(pt15, 1, ctx->param_.GetScale(1), pt15_complex);
  Ct ct35;
  ctx->Mult(ct35, ct23, pt15);
  Ct ct36;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct34.GetScale();
    double rhs_scale = ct35.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct36 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct36, ct34, ct35);
  Ct ct37;
  ctx->HRot(ct37, ct36, ui.GetRotationKey(v1), v1);
  Ct ct38;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct21.GetScale();
    double rhs_scale = ct24.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct38 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct38, ct21, ct24);
  Ct ct39;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct27.GetScale();
    double rhs_scale = ct33.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct39 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct39, ct27, ct33);
  Ct ct40;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct39.GetScale();
    double rhs_scale = ct37.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct40 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct40, ct39, ct37);
  Ct ct41;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct38.GetScale();
    double rhs_scale = ct40.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct41 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct41, ct38, ct40);
  std::vector<Ct> v67;
  v67.resize(1);
  Ct ct42;
  ctx->Rescale(ct42, ct41);
  std::vector<Ct> v68;
  v68.resize(1);
  Ct ct42_c6;
  ctx->Copy(ct42_c6, ct42);
  v68[v7] = std::move(ct42_c6);
  return v68;
}

std::vector<Ct> matvec_chain__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1) {
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
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  Ct ct;
  ui.Encrypt(ct, pt);
  std::vector<Ct> v16;
  v16.reserve(1);
  Ct ct_c7;
  ctx->Copy(ct_c7, ct);
  v16.emplace_back(std::move(ct_c7));
  return v16;
}

std::vector<double> matvec_chain__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1) {
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
  static std::vector<word> main_primes = {36028797017456641ULL, 35184373006337ULL, 35184370941953ULL, 35184372744193ULL, 35184371138561ULL, 35184372121601ULL};
  static std::vector<word> aux_primes = {1152921504607338497ULL, 1152921504608747521ULL};
  static std::vector<std::pair<int, int>> level_config = []() {
    std::vector<std::pair<int, int>> lc;
    for (int i = 1; i <= static_cast<int>(main_primes.size()); ++i)
      lc.push_back({i, 0});
    return lc;
  }();
  static Param param(14, static_cast<double>(1ULL << 45), static_cast<int>(main_primes.size()) - 1, level_config, main_primes, aux_primes);
  auto ctx = Context<word>::Create(param);
  UI ui(ctx);
  ui.PrepareRotationKey(1, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(2, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(3, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(6, static_cast<int>(main_primes.size()) - 1);
  return {ctx, std::move(ui)};
}

