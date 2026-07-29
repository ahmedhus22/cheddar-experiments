
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

std::vector<Ct> bert_attention(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, const std::vector<double>& v1, const std::vector<double>& v2) {
  int64_t v3 = 64;
  int64_t v4 = 128;
  int64_t v5 = 192;
  int64_t v6 = 256;
  int64_t v7 = 320;
  int64_t v8 = 384;
  int64_t v9 = 448;
  int64_t v10 = 512;
  int64_t v11 = 1024;
  int64_t v12 = 1536;
  int64_t v13 = 2048;
  int64_t v14 = 2560;
  int64_t v15 = 3072;
  int64_t v16 = 3584;
  int64_t v17 = 0;
  std::vector<double> v18(v1.begin() + 0 * 4096 + 0, v1.begin() + 0 * 4096 + 0 + 4096);
  Pt pt;
  std::vector<Complex> pt_complex(v18.begin(), v18.end());
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  auto& ct = v0[v17];
  Ct ct1;
  ctx->Mult(ct1, ct, pt);
  Ct ct2;
  ctx->HRot(ct2, ct, ui.GetRotationKey(v3), v3);
  std::vector<double> v19(v1.begin() + 1 * 4096 + 0, v1.begin() + 1 * 4096 + 0 + 4096);
  Pt pt1;
  std::vector<Complex> pt1_complex(v19.begin(), v19.end());
  encoder.Encode(pt1, 2, ctx->param_.GetScale(2), pt1_complex);
  Ct ct3;
  ctx->Mult(ct3, ct2, pt1);
  Ct ct4;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct1.GetScale();
    double rhs_scale = ct3.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct4 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct4, ct1, ct3);
  Ct ct5;
  ctx->HRot(ct5, ct, ui.GetRotationKey(v4), v4);
  std::vector<double> v20(v1.begin() + 2 * 4096 + 0, v1.begin() + 2 * 4096 + 0 + 4096);
  Pt pt2;
  std::vector<Complex> pt2_complex(v20.begin(), v20.end());
  encoder.Encode(pt2, 2, ctx->param_.GetScale(2), pt2_complex);
  Ct ct6;
  ctx->Mult(ct6, ct5, pt2);
  Ct ct7;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct4.GetScale();
    double rhs_scale = ct6.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct7 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct7, ct4, ct6);
  Ct ct8;
  ctx->HRot(ct8, ct, ui.GetRotationKey(v5), v5);
  std::vector<double> v21(v1.begin() + 3 * 4096 + 0, v1.begin() + 3 * 4096 + 0 + 4096);
  Pt pt3;
  std::vector<Complex> pt3_complex(v21.begin(), v21.end());
  encoder.Encode(pt3, 2, ctx->param_.GetScale(2), pt3_complex);
  Ct ct9;
  ctx->Mult(ct9, ct8, pt3);
  Ct ct10;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct7.GetScale();
    double rhs_scale = ct9.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct10 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct10, ct7, ct9);
  Ct ct11;
  ctx->HRot(ct11, ct, ui.GetRotationKey(v6), v6);
  std::vector<double> v22(v1.begin() + 4 * 4096 + 0, v1.begin() + 4 * 4096 + 0 + 4096);
  Pt pt4;
  std::vector<Complex> pt4_complex(v22.begin(), v22.end());
  encoder.Encode(pt4, 2, ctx->param_.GetScale(2), pt4_complex);
  Ct ct12;
  ctx->Mult(ct12, ct11, pt4);
  Ct ct13;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct10.GetScale();
    double rhs_scale = ct12.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct13 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct13, ct10, ct12);
  Ct ct14;
  ctx->HRot(ct14, ct, ui.GetRotationKey(v7), v7);
  std::vector<double> v23(v1.begin() + 5 * 4096 + 0, v1.begin() + 5 * 4096 + 0 + 4096);
  Pt pt5;
  std::vector<Complex> pt5_complex(v23.begin(), v23.end());
  encoder.Encode(pt5, 2, ctx->param_.GetScale(2), pt5_complex);
  Ct ct15;
  ctx->Mult(ct15, ct14, pt5);
  Ct ct16;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct13.GetScale();
    double rhs_scale = ct15.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct16 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct16, ct13, ct15);
  Ct ct17;
  ctx->HRot(ct17, ct, ui.GetRotationKey(v8), v8);
  std::vector<double> v24(v1.begin() + 6 * 4096 + 0, v1.begin() + 6 * 4096 + 0 + 4096);
  Pt pt6;
  std::vector<Complex> pt6_complex(v24.begin(), v24.end());
  encoder.Encode(pt6, 2, ctx->param_.GetScale(2), pt6_complex);
  Ct ct18;
  ctx->Mult(ct18, ct17, pt6);
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
  ctx->HRot(ct20, ct, ui.GetRotationKey(v9), v9);
  std::vector<double> v25(v1.begin() + 7 * 4096 + 0, v1.begin() + 7 * 4096 + 0 + 4096);
  Pt pt7;
  std::vector<Complex> pt7_complex(v25.begin(), v25.end());
  encoder.Encode(pt7, 2, ctx->param_.GetScale(2), pt7_complex);
  Ct ct21;
  ctx->Mult(ct21, ct20, pt7);
  Ct ct22;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct19.GetScale();
    double rhs_scale = ct21.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct22 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct22, ct19, ct21);
  std::vector<double> v26(v1.begin() + 8 * 4096 + 0, v1.begin() + 8 * 4096 + 0 + 4096);
  Pt pt8;
  std::vector<Complex> pt8_complex(v26.begin(), v26.end());
  encoder.Encode(pt8, 2, ctx->param_.GetScale(2), pt8_complex);
  Ct ct23;
  ctx->Mult(ct23, ct, pt8);
  std::vector<double> v27(v1.begin() + 9 * 4096 + 0, v1.begin() + 9 * 4096 + 0 + 4096);
  Pt pt9;
  std::vector<Complex> pt9_complex(v27.begin(), v27.end());
  encoder.Encode(pt9, 2, ctx->param_.GetScale(2), pt9_complex);
  Ct ct24;
  ctx->Mult(ct24, ct2, pt9);
  Ct ct25;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct23.GetScale();
    double rhs_scale = ct24.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct25 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct25, ct23, ct24);
  std::vector<double> v28(v1.begin() + 10 * 4096 + 0, v1.begin() + 10 * 4096 + 0 + 4096);
  Pt pt10;
  std::vector<Complex> pt10_complex(v28.begin(), v28.end());
  encoder.Encode(pt10, 2, ctx->param_.GetScale(2), pt10_complex);
  Ct ct26;
  ctx->Mult(ct26, ct5, pt10);
  Ct ct27;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct25.GetScale();
    double rhs_scale = ct26.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct27 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct27, ct25, ct26);
  std::vector<double> v29(v1.begin() + 11 * 4096 + 0, v1.begin() + 11 * 4096 + 0 + 4096);
  Pt pt11;
  std::vector<Complex> pt11_complex(v29.begin(), v29.end());
  encoder.Encode(pt11, 2, ctx->param_.GetScale(2), pt11_complex);
  Ct ct28;
  ctx->Mult(ct28, ct8, pt11);
  Ct ct29;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct27.GetScale();
    double rhs_scale = ct28.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct29 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct29, ct27, ct28);
  std::vector<double> v30(v1.begin() + 12 * 4096 + 0, v1.begin() + 12 * 4096 + 0 + 4096);
  Pt pt12;
  std::vector<Complex> pt12_complex(v30.begin(), v30.end());
  encoder.Encode(pt12, 2, ctx->param_.GetScale(2), pt12_complex);
  Ct ct30;
  ctx->Mult(ct30, ct11, pt12);
  Ct ct31;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct29.GetScale();
    double rhs_scale = ct30.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct31 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct31, ct29, ct30);
  std::vector<double> v31(v1.begin() + 13 * 4096 + 0, v1.begin() + 13 * 4096 + 0 + 4096);
  Pt pt13;
  std::vector<Complex> pt13_complex(v31.begin(), v31.end());
  encoder.Encode(pt13, 2, ctx->param_.GetScale(2), pt13_complex);
  Ct ct32;
  ctx->Mult(ct32, ct14, pt13);
  Ct ct33;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct31.GetScale();
    double rhs_scale = ct32.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct33 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct33, ct31, ct32);
  std::vector<double> v32(v1.begin() + 14 * 4096 + 0, v1.begin() + 14 * 4096 + 0 + 4096);
  Pt pt14;
  std::vector<Complex> pt14_complex(v32.begin(), v32.end());
  encoder.Encode(pt14, 2, ctx->param_.GetScale(2), pt14_complex);
  Ct ct34;
  ctx->Mult(ct34, ct17, pt14);
  Ct ct35;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct33.GetScale();
    double rhs_scale = ct34.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct35 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct35, ct33, ct34);
  std::vector<double> v33(v1.begin() + 15 * 4096 + 0, v1.begin() + 15 * 4096 + 0 + 4096);
  Pt pt15;
  std::vector<Complex> pt15_complex(v33.begin(), v33.end());
  encoder.Encode(pt15, 2, ctx->param_.GetScale(2), pt15_complex);
  Ct ct36;
  ctx->Mult(ct36, ct20, pt15);
  Ct ct37;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct35.GetScale();
    double rhs_scale = ct36.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct37 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct37, ct35, ct36);
  Ct ct38;
  ctx->HRot(ct38, ct37, ui.GetRotationKey(v10), v10);
  Ct ct39;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct22.GetScale();
    double rhs_scale = ct38.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct39 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct39, ct22, ct38);
  std::vector<double> v34(v1.begin() + 16 * 4096 + 0, v1.begin() + 16 * 4096 + 0 + 4096);
  Pt pt16;
  std::vector<Complex> pt16_complex(v34.begin(), v34.end());
  encoder.Encode(pt16, 2, ctx->param_.GetScale(2), pt16_complex);
  Ct ct40;
  ctx->Mult(ct40, ct, pt16);
  std::vector<double> v35(v1.begin() + 17 * 4096 + 0, v1.begin() + 17 * 4096 + 0 + 4096);
  Pt pt17;
  std::vector<Complex> pt17_complex(v35.begin(), v35.end());
  encoder.Encode(pt17, 2, ctx->param_.GetScale(2), pt17_complex);
  Ct ct41;
  ctx->Mult(ct41, ct2, pt17);
  Ct ct42;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct40.GetScale();
    double rhs_scale = ct41.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct42 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct42, ct40, ct41);
  std::vector<double> v36(v1.begin() + 18 * 4096 + 0, v1.begin() + 18 * 4096 + 0 + 4096);
  Pt pt18;
  std::vector<Complex> pt18_complex(v36.begin(), v36.end());
  encoder.Encode(pt18, 2, ctx->param_.GetScale(2), pt18_complex);
  Ct ct43;
  ctx->Mult(ct43, ct5, pt18);
  Ct ct44;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct42.GetScale();
    double rhs_scale = ct43.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct44 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct44, ct42, ct43);
  std::vector<double> v37(v1.begin() + 19 * 4096 + 0, v1.begin() + 19 * 4096 + 0 + 4096);
  Pt pt19;
  std::vector<Complex> pt19_complex(v37.begin(), v37.end());
  encoder.Encode(pt19, 2, ctx->param_.GetScale(2), pt19_complex);
  Ct ct45;
  ctx->Mult(ct45, ct8, pt19);
  Ct ct46;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct44.GetScale();
    double rhs_scale = ct45.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct46 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct46, ct44, ct45);
  std::vector<double> v38(v1.begin() + 20 * 4096 + 0, v1.begin() + 20 * 4096 + 0 + 4096);
  Pt pt20;
  std::vector<Complex> pt20_complex(v38.begin(), v38.end());
  encoder.Encode(pt20, 2, ctx->param_.GetScale(2), pt20_complex);
  Ct ct47;
  ctx->Mult(ct47, ct11, pt20);
  Ct ct48;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct46.GetScale();
    double rhs_scale = ct47.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct48 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct48, ct46, ct47);
  std::vector<double> v39(v1.begin() + 21 * 4096 + 0, v1.begin() + 21 * 4096 + 0 + 4096);
  Pt pt21;
  std::vector<Complex> pt21_complex(v39.begin(), v39.end());
  encoder.Encode(pt21, 2, ctx->param_.GetScale(2), pt21_complex);
  Ct ct49;
  ctx->Mult(ct49, ct14, pt21);
  Ct ct50;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct48.GetScale();
    double rhs_scale = ct49.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct50 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct50, ct48, ct49);
  std::vector<double> v40(v1.begin() + 22 * 4096 + 0, v1.begin() + 22 * 4096 + 0 + 4096);
  Pt pt22;
  std::vector<Complex> pt22_complex(v40.begin(), v40.end());
  encoder.Encode(pt22, 2, ctx->param_.GetScale(2), pt22_complex);
  Ct ct51;
  ctx->Mult(ct51, ct17, pt22);
  Ct ct52;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct50.GetScale();
    double rhs_scale = ct51.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct52 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct52, ct50, ct51);
  std::vector<double> v41(v1.begin() + 23 * 4096 + 0, v1.begin() + 23 * 4096 + 0 + 4096);
  Pt pt23;
  std::vector<Complex> pt23_complex(v41.begin(), v41.end());
  encoder.Encode(pt23, 2, ctx->param_.GetScale(2), pt23_complex);
  Ct ct53;
  ctx->Mult(ct53, ct20, pt23);
  Ct ct54;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct52.GetScale();
    double rhs_scale = ct53.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct54 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct54, ct52, ct53);
  Ct ct55;
  ctx->HRot(ct55, ct54, ui.GetRotationKey(v11), v11);
  Ct ct56;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct39.GetScale();
    double rhs_scale = ct55.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct56 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct56, ct39, ct55);
  std::vector<double> v42(v1.begin() + 24 * 4096 + 0, v1.begin() + 24 * 4096 + 0 + 4096);
  Pt pt24;
  std::vector<Complex> pt24_complex(v42.begin(), v42.end());
  encoder.Encode(pt24, 2, ctx->param_.GetScale(2), pt24_complex);
  Ct ct57;
  ctx->Mult(ct57, ct, pt24);
  std::vector<double> v43(v1.begin() + 25 * 4096 + 0, v1.begin() + 25 * 4096 + 0 + 4096);
  Pt pt25;
  std::vector<Complex> pt25_complex(v43.begin(), v43.end());
  encoder.Encode(pt25, 2, ctx->param_.GetScale(2), pt25_complex);
  Ct ct58;
  ctx->Mult(ct58, ct2, pt25);
  Ct ct59;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct57.GetScale();
    double rhs_scale = ct58.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct59 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct59, ct57, ct58);
  std::vector<double> v44(v1.begin() + 26 * 4096 + 0, v1.begin() + 26 * 4096 + 0 + 4096);
  Pt pt26;
  std::vector<Complex> pt26_complex(v44.begin(), v44.end());
  encoder.Encode(pt26, 2, ctx->param_.GetScale(2), pt26_complex);
  Ct ct60;
  ctx->Mult(ct60, ct5, pt26);
  Ct ct61;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct59.GetScale();
    double rhs_scale = ct60.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct61 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct61, ct59, ct60);
  std::vector<double> v45(v1.begin() + 27 * 4096 + 0, v1.begin() + 27 * 4096 + 0 + 4096);
  Pt pt27;
  std::vector<Complex> pt27_complex(v45.begin(), v45.end());
  encoder.Encode(pt27, 2, ctx->param_.GetScale(2), pt27_complex);
  Ct ct62;
  ctx->Mult(ct62, ct8, pt27);
  Ct ct63;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct61.GetScale();
    double rhs_scale = ct62.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct63 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct63, ct61, ct62);
  std::vector<double> v46(v1.begin() + 28 * 4096 + 0, v1.begin() + 28 * 4096 + 0 + 4096);
  Pt pt28;
  std::vector<Complex> pt28_complex(v46.begin(), v46.end());
  encoder.Encode(pt28, 2, ctx->param_.GetScale(2), pt28_complex);
  Ct ct64;
  ctx->Mult(ct64, ct11, pt28);
  Ct ct65;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct63.GetScale();
    double rhs_scale = ct64.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct65 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct65, ct63, ct64);
  std::vector<double> v47(v1.begin() + 29 * 4096 + 0, v1.begin() + 29 * 4096 + 0 + 4096);
  Pt pt29;
  std::vector<Complex> pt29_complex(v47.begin(), v47.end());
  encoder.Encode(pt29, 2, ctx->param_.GetScale(2), pt29_complex);
  Ct ct66;
  ctx->Mult(ct66, ct14, pt29);
  Ct ct67;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct65.GetScale();
    double rhs_scale = ct66.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct67 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct67, ct65, ct66);
  std::vector<double> v48(v1.begin() + 30 * 4096 + 0, v1.begin() + 30 * 4096 + 0 + 4096);
  Pt pt30;
  std::vector<Complex> pt30_complex(v48.begin(), v48.end());
  encoder.Encode(pt30, 2, ctx->param_.GetScale(2), pt30_complex);
  Ct ct68;
  ctx->Mult(ct68, ct17, pt30);
  Ct ct69;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct67.GetScale();
    double rhs_scale = ct68.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct69 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct69, ct67, ct68);
  std::vector<double> v49(v1.begin() + 31 * 4096 + 0, v1.begin() + 31 * 4096 + 0 + 4096);
  Pt pt31;
  std::vector<Complex> pt31_complex(v49.begin(), v49.end());
  encoder.Encode(pt31, 2, ctx->param_.GetScale(2), pt31_complex);
  Ct ct70;
  ctx->Mult(ct70, ct20, pt31);
  Ct ct71;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct69.GetScale();
    double rhs_scale = ct70.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct71 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct71, ct69, ct70);
  Ct ct72;
  ctx->HRot(ct72, ct71, ui.GetRotationKey(v12), v12);
  Ct ct73;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct56.GetScale();
    double rhs_scale = ct72.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct73 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct73, ct56, ct72);
  std::vector<double> v50(v1.begin() + 32 * 4096 + 0, v1.begin() + 32 * 4096 + 0 + 4096);
  Pt pt32;
  std::vector<Complex> pt32_complex(v50.begin(), v50.end());
  encoder.Encode(pt32, 2, ctx->param_.GetScale(2), pt32_complex);
  Ct ct74;
  ctx->Mult(ct74, ct, pt32);
  std::vector<double> v51(v1.begin() + 33 * 4096 + 0, v1.begin() + 33 * 4096 + 0 + 4096);
  Pt pt33;
  std::vector<Complex> pt33_complex(v51.begin(), v51.end());
  encoder.Encode(pt33, 2, ctx->param_.GetScale(2), pt33_complex);
  Ct ct75;
  ctx->Mult(ct75, ct2, pt33);
  Ct ct76;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct74.GetScale();
    double rhs_scale = ct75.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct76 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct76, ct74, ct75);
  std::vector<double> v52(v1.begin() + 34 * 4096 + 0, v1.begin() + 34 * 4096 + 0 + 4096);
  Pt pt34;
  std::vector<Complex> pt34_complex(v52.begin(), v52.end());
  encoder.Encode(pt34, 2, ctx->param_.GetScale(2), pt34_complex);
  Ct ct77;
  ctx->Mult(ct77, ct5, pt34);
  Ct ct78;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct76.GetScale();
    double rhs_scale = ct77.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct78 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct78, ct76, ct77);
  std::vector<double> v53(v1.begin() + 35 * 4096 + 0, v1.begin() + 35 * 4096 + 0 + 4096);
  Pt pt35;
  std::vector<Complex> pt35_complex(v53.begin(), v53.end());
  encoder.Encode(pt35, 2, ctx->param_.GetScale(2), pt35_complex);
  Ct ct79;
  ctx->Mult(ct79, ct8, pt35);
  Ct ct80;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct78.GetScale();
    double rhs_scale = ct79.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct80 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct80, ct78, ct79);
  std::vector<double> v54(v1.begin() + 36 * 4096 + 0, v1.begin() + 36 * 4096 + 0 + 4096);
  Pt pt36;
  std::vector<Complex> pt36_complex(v54.begin(), v54.end());
  encoder.Encode(pt36, 2, ctx->param_.GetScale(2), pt36_complex);
  Ct ct81;
  ctx->Mult(ct81, ct11, pt36);
  Ct ct82;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct80.GetScale();
    double rhs_scale = ct81.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct82 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct82, ct80, ct81);
  std::vector<double> v55(v1.begin() + 37 * 4096 + 0, v1.begin() + 37 * 4096 + 0 + 4096);
  Pt pt37;
  std::vector<Complex> pt37_complex(v55.begin(), v55.end());
  encoder.Encode(pt37, 2, ctx->param_.GetScale(2), pt37_complex);
  Ct ct83;
  ctx->Mult(ct83, ct14, pt37);
  Ct ct84;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct82.GetScale();
    double rhs_scale = ct83.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct84 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct84, ct82, ct83);
  std::vector<double> v56(v1.begin() + 38 * 4096 + 0, v1.begin() + 38 * 4096 + 0 + 4096);
  Pt pt38;
  std::vector<Complex> pt38_complex(v56.begin(), v56.end());
  encoder.Encode(pt38, 2, ctx->param_.GetScale(2), pt38_complex);
  Ct ct85;
  ctx->Mult(ct85, ct17, pt38);
  Ct ct86;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct84.GetScale();
    double rhs_scale = ct85.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct86 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct86, ct84, ct85);
  std::vector<double> v57(v1.begin() + 39 * 4096 + 0, v1.begin() + 39 * 4096 + 0 + 4096);
  Pt pt39;
  std::vector<Complex> pt39_complex(v57.begin(), v57.end());
  encoder.Encode(pt39, 2, ctx->param_.GetScale(2), pt39_complex);
  Ct ct87;
  ctx->Mult(ct87, ct20, pt39);
  Ct ct88;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct86.GetScale();
    double rhs_scale = ct87.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct88 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct88, ct86, ct87);
  Ct ct89;
  ctx->HRot(ct89, ct88, ui.GetRotationKey(v13), v13);
  Ct ct90;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct73.GetScale();
    double rhs_scale = ct89.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct90 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct90, ct73, ct89);
  std::vector<double> v58(v1.begin() + 40 * 4096 + 0, v1.begin() + 40 * 4096 + 0 + 4096);
  Pt pt40;
  std::vector<Complex> pt40_complex(v58.begin(), v58.end());
  encoder.Encode(pt40, 2, ctx->param_.GetScale(2), pt40_complex);
  Ct ct91;
  ctx->Mult(ct91, ct, pt40);
  std::vector<double> v59(v1.begin() + 41 * 4096 + 0, v1.begin() + 41 * 4096 + 0 + 4096);
  Pt pt41;
  std::vector<Complex> pt41_complex(v59.begin(), v59.end());
  encoder.Encode(pt41, 2, ctx->param_.GetScale(2), pt41_complex);
  Ct ct92;
  ctx->Mult(ct92, ct2, pt41);
  Ct ct93;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct91.GetScale();
    double rhs_scale = ct92.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct93 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct93, ct91, ct92);
  std::vector<double> v60(v1.begin() + 42 * 4096 + 0, v1.begin() + 42 * 4096 + 0 + 4096);
  Pt pt42;
  std::vector<Complex> pt42_complex(v60.begin(), v60.end());
  encoder.Encode(pt42, 2, ctx->param_.GetScale(2), pt42_complex);
  Ct ct94;
  ctx->Mult(ct94, ct5, pt42);
  Ct ct95;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct93.GetScale();
    double rhs_scale = ct94.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct95 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct95, ct93, ct94);
  std::vector<double> v61(v1.begin() + 43 * 4096 + 0, v1.begin() + 43 * 4096 + 0 + 4096);
  Pt pt43;
  std::vector<Complex> pt43_complex(v61.begin(), v61.end());
  encoder.Encode(pt43, 2, ctx->param_.GetScale(2), pt43_complex);
  Ct ct96;
  ctx->Mult(ct96, ct8, pt43);
  Ct ct97;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct95.GetScale();
    double rhs_scale = ct96.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct97 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct97, ct95, ct96);
  std::vector<double> v62(v1.begin() + 44 * 4096 + 0, v1.begin() + 44 * 4096 + 0 + 4096);
  Pt pt44;
  std::vector<Complex> pt44_complex(v62.begin(), v62.end());
  encoder.Encode(pt44, 2, ctx->param_.GetScale(2), pt44_complex);
  Ct ct98;
  ctx->Mult(ct98, ct11, pt44);
  Ct ct99;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct97.GetScale();
    double rhs_scale = ct98.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct99 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct99, ct97, ct98);
  std::vector<double> v63(v1.begin() + 45 * 4096 + 0, v1.begin() + 45 * 4096 + 0 + 4096);
  Pt pt45;
  std::vector<Complex> pt45_complex(v63.begin(), v63.end());
  encoder.Encode(pt45, 2, ctx->param_.GetScale(2), pt45_complex);
  Ct ct100;
  ctx->Mult(ct100, ct14, pt45);
  Ct ct101;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct99.GetScale();
    double rhs_scale = ct100.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct101 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct101, ct99, ct100);
  std::vector<double> v64(v1.begin() + 46 * 4096 + 0, v1.begin() + 46 * 4096 + 0 + 4096);
  Pt pt46;
  std::vector<Complex> pt46_complex(v64.begin(), v64.end());
  encoder.Encode(pt46, 2, ctx->param_.GetScale(2), pt46_complex);
  Ct ct102;
  ctx->Mult(ct102, ct17, pt46);
  Ct ct103;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct101.GetScale();
    double rhs_scale = ct102.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct103 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct103, ct101, ct102);
  std::vector<double> v65(v1.begin() + 47 * 4096 + 0, v1.begin() + 47 * 4096 + 0 + 4096);
  Pt pt47;
  std::vector<Complex> pt47_complex(v65.begin(), v65.end());
  encoder.Encode(pt47, 2, ctx->param_.GetScale(2), pt47_complex);
  Ct ct104;
  ctx->Mult(ct104, ct20, pt47);
  Ct ct105;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct103.GetScale();
    double rhs_scale = ct104.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct105 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct105, ct103, ct104);
  Ct ct106;
  ctx->HRot(ct106, ct105, ui.GetRotationKey(v14), v14);
  Ct ct107;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct90.GetScale();
    double rhs_scale = ct106.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct107 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct107, ct90, ct106);
  std::vector<double> v66(v1.begin() + 48 * 4096 + 0, v1.begin() + 48 * 4096 + 0 + 4096);
  Pt pt48;
  std::vector<Complex> pt48_complex(v66.begin(), v66.end());
  encoder.Encode(pt48, 2, ctx->param_.GetScale(2), pt48_complex);
  Ct ct108;
  ctx->Mult(ct108, ct, pt48);
  std::vector<double> v67(v1.begin() + 49 * 4096 + 0, v1.begin() + 49 * 4096 + 0 + 4096);
  Pt pt49;
  std::vector<Complex> pt49_complex(v67.begin(), v67.end());
  encoder.Encode(pt49, 2, ctx->param_.GetScale(2), pt49_complex);
  Ct ct109;
  ctx->Mult(ct109, ct2, pt49);
  Ct ct110;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct108.GetScale();
    double rhs_scale = ct109.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct110 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct110, ct108, ct109);
  std::vector<double> v68(v1.begin() + 50 * 4096 + 0, v1.begin() + 50 * 4096 + 0 + 4096);
  Pt pt50;
  std::vector<Complex> pt50_complex(v68.begin(), v68.end());
  encoder.Encode(pt50, 2, ctx->param_.GetScale(2), pt50_complex);
  Ct ct111;
  ctx->Mult(ct111, ct5, pt50);
  Ct ct112;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct110.GetScale();
    double rhs_scale = ct111.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct112 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct112, ct110, ct111);
  std::vector<double> v69(v1.begin() + 51 * 4096 + 0, v1.begin() + 51 * 4096 + 0 + 4096);
  Pt pt51;
  std::vector<Complex> pt51_complex(v69.begin(), v69.end());
  encoder.Encode(pt51, 2, ctx->param_.GetScale(2), pt51_complex);
  Ct ct113;
  ctx->Mult(ct113, ct8, pt51);
  Ct ct114;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct112.GetScale();
    double rhs_scale = ct113.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct114 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct114, ct112, ct113);
  std::vector<double> v70(v1.begin() + 52 * 4096 + 0, v1.begin() + 52 * 4096 + 0 + 4096);
  Pt pt52;
  std::vector<Complex> pt52_complex(v70.begin(), v70.end());
  encoder.Encode(pt52, 2, ctx->param_.GetScale(2), pt52_complex);
  Ct ct115;
  ctx->Mult(ct115, ct11, pt52);
  Ct ct116;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct114.GetScale();
    double rhs_scale = ct115.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct116 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct116, ct114, ct115);
  std::vector<double> v71(v1.begin() + 53 * 4096 + 0, v1.begin() + 53 * 4096 + 0 + 4096);
  Pt pt53;
  std::vector<Complex> pt53_complex(v71.begin(), v71.end());
  encoder.Encode(pt53, 2, ctx->param_.GetScale(2), pt53_complex);
  Ct ct117;
  ctx->Mult(ct117, ct14, pt53);
  Ct ct118;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct116.GetScale();
    double rhs_scale = ct117.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct118 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct118, ct116, ct117);
  std::vector<double> v72(v1.begin() + 54 * 4096 + 0, v1.begin() + 54 * 4096 + 0 + 4096);
  Pt pt54;
  std::vector<Complex> pt54_complex(v72.begin(), v72.end());
  encoder.Encode(pt54, 2, ctx->param_.GetScale(2), pt54_complex);
  Ct ct119;
  ctx->Mult(ct119, ct17, pt54);
  Ct ct120;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct118.GetScale();
    double rhs_scale = ct119.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct120 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct120, ct118, ct119);
  std::vector<double> v73(v1.begin() + 55 * 4096 + 0, v1.begin() + 55 * 4096 + 0 + 4096);
  Pt pt55;
  std::vector<Complex> pt55_complex(v73.begin(), v73.end());
  encoder.Encode(pt55, 2, ctx->param_.GetScale(2), pt55_complex);
  Ct ct121;
  ctx->Mult(ct121, ct20, pt55);
  Ct ct122;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct120.GetScale();
    double rhs_scale = ct121.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct122 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct122, ct120, ct121);
  Ct ct123;
  ctx->HRot(ct123, ct122, ui.GetRotationKey(v15), v15);
  Ct ct124;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct107.GetScale();
    double rhs_scale = ct123.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct124 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct124, ct107, ct123);
  std::vector<double> v74(v1.begin() + 56 * 4096 + 0, v1.begin() + 56 * 4096 + 0 + 4096);
  Pt pt56;
  std::vector<Complex> pt56_complex(v74.begin(), v74.end());
  encoder.Encode(pt56, 2, ctx->param_.GetScale(2), pt56_complex);
  Ct ct125;
  ctx->Mult(ct125, ct, pt56);
  std::vector<double> v75(v1.begin() + 57 * 4096 + 0, v1.begin() + 57 * 4096 + 0 + 4096);
  Pt pt57;
  std::vector<Complex> pt57_complex(v75.begin(), v75.end());
  encoder.Encode(pt57, 2, ctx->param_.GetScale(2), pt57_complex);
  Ct ct126;
  ctx->Mult(ct126, ct2, pt57);
  Ct ct127;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct125.GetScale();
    double rhs_scale = ct126.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct127 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct127, ct125, ct126);
  std::vector<double> v76(v1.begin() + 58 * 4096 + 0, v1.begin() + 58 * 4096 + 0 + 4096);
  Pt pt58;
  std::vector<Complex> pt58_complex(v76.begin(), v76.end());
  encoder.Encode(pt58, 2, ctx->param_.GetScale(2), pt58_complex);
  Ct ct128;
  ctx->Mult(ct128, ct5, pt58);
  Ct ct129;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct127.GetScale();
    double rhs_scale = ct128.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct129 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct129, ct127, ct128);
  std::vector<double> v77(v1.begin() + 59 * 4096 + 0, v1.begin() + 59 * 4096 + 0 + 4096);
  Pt pt59;
  std::vector<Complex> pt59_complex(v77.begin(), v77.end());
  encoder.Encode(pt59, 2, ctx->param_.GetScale(2), pt59_complex);
  Ct ct130;
  ctx->Mult(ct130, ct8, pt59);
  Ct ct131;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct129.GetScale();
    double rhs_scale = ct130.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct131 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct131, ct129, ct130);
  std::vector<double> v78(v1.begin() + 60 * 4096 + 0, v1.begin() + 60 * 4096 + 0 + 4096);
  Pt pt60;
  std::vector<Complex> pt60_complex(v78.begin(), v78.end());
  encoder.Encode(pt60, 2, ctx->param_.GetScale(2), pt60_complex);
  Ct ct132;
  ctx->Mult(ct132, ct11, pt60);
  Ct ct133;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct131.GetScale();
    double rhs_scale = ct132.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct133 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct133, ct131, ct132);
  std::vector<double> v79(v1.begin() + 61 * 4096 + 0, v1.begin() + 61 * 4096 + 0 + 4096);
  Pt pt61;
  std::vector<Complex> pt61_complex(v79.begin(), v79.end());
  encoder.Encode(pt61, 2, ctx->param_.GetScale(2), pt61_complex);
  Ct ct134;
  ctx->Mult(ct134, ct14, pt61);
  Ct ct135;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct133.GetScale();
    double rhs_scale = ct134.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct135 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct135, ct133, ct134);
  std::vector<double> v80(v1.begin() + 62 * 4096 + 0, v1.begin() + 62 * 4096 + 0 + 4096);
  Pt pt62;
  std::vector<Complex> pt62_complex(v80.begin(), v80.end());
  encoder.Encode(pt62, 2, ctx->param_.GetScale(2), pt62_complex);
  Ct ct136;
  ctx->Mult(ct136, ct17, pt62);
  Ct ct137;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct135.GetScale();
    double rhs_scale = ct136.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct137 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct137, ct135, ct136);
  std::vector<double> v81(v1.begin() + 63 * 4096 + 0, v1.begin() + 63 * 4096 + 0 + 4096);
  Pt pt63;
  std::vector<Complex> pt63_complex(v81.begin(), v81.end());
  encoder.Encode(pt63, 2, ctx->param_.GetScale(2), pt63_complex);
  Ct ct138;
  ctx->Mult(ct138, ct20, pt63);
  Ct ct139;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct137.GetScale();
    double rhs_scale = ct138.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct139 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct139, ct137, ct138);
  Ct ct140;
  ctx->HRot(ct140, ct139, ui.GetRotationKey(v16), v16);
  Ct ct141;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct124.GetScale();
    double rhs_scale = ct140.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct141 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct141, ct124, ct140);
  Ct ct142;
  ctx->Rescale(ct142, ct141);
  std::vector<double> v82(v2.begin() + 0 * 4096 + 0, v2.begin() + 0 * 4096 + 0 + 4096);
  Pt pt64;
  std::vector<Complex> pt64_complex(v82.begin(), v82.end());
  encoder.Encode(pt64, 1, ctx->param_.GetScale(1), pt64_complex);
  Ct ct143;
  ctx->Mult(ct143, ct142, pt64);
  Ct ct144;
  ctx->HRot(ct144, ct141, ui.GetRotationKey(v3), v3);
  Ct ct145;
  ctx->Rescale(ct145, ct144);
  std::vector<double> v83(v2.begin() + 1 * 4096 + 0, v2.begin() + 1 * 4096 + 0 + 4096);
  Pt pt65;
  std::vector<Complex> pt65_complex(v83.begin(), v83.end());
  encoder.Encode(pt65, 1, ctx->param_.GetScale(1), pt65_complex);
  Ct ct146;
  ctx->Mult(ct146, ct145, pt65);
  Ct ct147;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct143.GetScale();
    double rhs_scale = ct146.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct147 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct147, ct143, ct146);
  Ct ct148;
  ctx->HRot(ct148, ct141, ui.GetRotationKey(v4), v4);
  Ct ct149;
  ctx->Rescale(ct149, ct148);
  std::vector<double> v84(v2.begin() + 2 * 4096 + 0, v2.begin() + 2 * 4096 + 0 + 4096);
  Pt pt66;
  std::vector<Complex> pt66_complex(v84.begin(), v84.end());
  encoder.Encode(pt66, 1, ctx->param_.GetScale(1), pt66_complex);
  Ct ct150;
  ctx->Mult(ct150, ct149, pt66);
  Ct ct151;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct147.GetScale();
    double rhs_scale = ct150.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct151 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct151, ct147, ct150);
  Ct ct152;
  ctx->HRot(ct152, ct141, ui.GetRotationKey(v5), v5);
  Ct ct153;
  ctx->Rescale(ct153, ct152);
  std::vector<double> v85(v2.begin() + 3 * 4096 + 0, v2.begin() + 3 * 4096 + 0 + 4096);
  Pt pt67;
  std::vector<Complex> pt67_complex(v85.begin(), v85.end());
  encoder.Encode(pt67, 1, ctx->param_.GetScale(1), pt67_complex);
  Ct ct154;
  ctx->Mult(ct154, ct153, pt67);
  Ct ct155;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct151.GetScale();
    double rhs_scale = ct154.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct155 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct155, ct151, ct154);
  Ct ct156;
  ctx->HRot(ct156, ct141, ui.GetRotationKey(v6), v6);
  Ct ct157;
  ctx->Rescale(ct157, ct156);
  std::vector<double> v86(v2.begin() + 4 * 4096 + 0, v2.begin() + 4 * 4096 + 0 + 4096);
  Pt pt68;
  std::vector<Complex> pt68_complex(v86.begin(), v86.end());
  encoder.Encode(pt68, 1, ctx->param_.GetScale(1), pt68_complex);
  Ct ct158;
  ctx->Mult(ct158, ct157, pt68);
  Ct ct159;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct155.GetScale();
    double rhs_scale = ct158.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct159 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct159, ct155, ct158);
  Ct ct160;
  ctx->HRot(ct160, ct141, ui.GetRotationKey(v7), v7);
  Ct ct161;
  ctx->Rescale(ct161, ct160);
  std::vector<double> v87(v2.begin() + 5 * 4096 + 0, v2.begin() + 5 * 4096 + 0 + 4096);
  Pt pt69;
  std::vector<Complex> pt69_complex(v87.begin(), v87.end());
  encoder.Encode(pt69, 1, ctx->param_.GetScale(1), pt69_complex);
  Ct ct162;
  ctx->Mult(ct162, ct161, pt69);
  Ct ct163;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct159.GetScale();
    double rhs_scale = ct162.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct163 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct163, ct159, ct162);
  Ct ct164;
  ctx->HRot(ct164, ct141, ui.GetRotationKey(v8), v8);
  Ct ct165;
  ctx->Rescale(ct165, ct164);
  std::vector<double> v88(v2.begin() + 6 * 4096 + 0, v2.begin() + 6 * 4096 + 0 + 4096);
  Pt pt70;
  std::vector<Complex> pt70_complex(v88.begin(), v88.end());
  encoder.Encode(pt70, 1, ctx->param_.GetScale(1), pt70_complex);
  Ct ct166;
  ctx->Mult(ct166, ct165, pt70);
  Ct ct167;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct163.GetScale();
    double rhs_scale = ct166.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct167 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct167, ct163, ct166);
  Ct ct168;
  ctx->HRot(ct168, ct141, ui.GetRotationKey(v9), v9);
  Ct ct169;
  ctx->Rescale(ct169, ct168);
  std::vector<double> v89(v2.begin() + 7 * 4096 + 0, v2.begin() + 7 * 4096 + 0 + 4096);
  Pt pt71;
  std::vector<Complex> pt71_complex(v89.begin(), v89.end());
  encoder.Encode(pt71, 1, ctx->param_.GetScale(1), pt71_complex);
  Ct ct170;
  ctx->Mult(ct170, ct169, pt71);
  Ct ct171;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct167.GetScale();
    double rhs_scale = ct170.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct171 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct171, ct167, ct170);
  std::vector<double> v90(v2.begin() + 8 * 4096 + 0, v2.begin() + 8 * 4096 + 0 + 4096);
  Pt pt72;
  std::vector<Complex> pt72_complex(v90.begin(), v90.end());
  encoder.Encode(pt72, 1, ctx->param_.GetScale(1), pt72_complex);
  Ct ct172;
  ctx->Mult(ct172, ct142, pt72);
  std::vector<double> v91(v2.begin() + 9 * 4096 + 0, v2.begin() + 9 * 4096 + 0 + 4096);
  Pt pt73;
  std::vector<Complex> pt73_complex(v91.begin(), v91.end());
  encoder.Encode(pt73, 1, ctx->param_.GetScale(1), pt73_complex);
  Ct ct173;
  ctx->Mult(ct173, ct145, pt73);
  Ct ct174;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct172.GetScale();
    double rhs_scale = ct173.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct174 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct174, ct172, ct173);
  std::vector<double> v92(v2.begin() + 10 * 4096 + 0, v2.begin() + 10 * 4096 + 0 + 4096);
  Pt pt74;
  std::vector<Complex> pt74_complex(v92.begin(), v92.end());
  encoder.Encode(pt74, 1, ctx->param_.GetScale(1), pt74_complex);
  Ct ct175;
  ctx->Mult(ct175, ct149, pt74);
  Ct ct176;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct174.GetScale();
    double rhs_scale = ct175.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct176 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct176, ct174, ct175);
  std::vector<double> v93(v2.begin() + 11 * 4096 + 0, v2.begin() + 11 * 4096 + 0 + 4096);
  Pt pt75;
  std::vector<Complex> pt75_complex(v93.begin(), v93.end());
  encoder.Encode(pt75, 1, ctx->param_.GetScale(1), pt75_complex);
  Ct ct177;
  ctx->Mult(ct177, ct153, pt75);
  Ct ct178;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct176.GetScale();
    double rhs_scale = ct177.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct178 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct178, ct176, ct177);
  std::vector<double> v94(v2.begin() + 12 * 4096 + 0, v2.begin() + 12 * 4096 + 0 + 4096);
  Pt pt76;
  std::vector<Complex> pt76_complex(v94.begin(), v94.end());
  encoder.Encode(pt76, 1, ctx->param_.GetScale(1), pt76_complex);
  Ct ct179;
  ctx->Mult(ct179, ct157, pt76);
  Ct ct180;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct178.GetScale();
    double rhs_scale = ct179.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct180 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct180, ct178, ct179);
  std::vector<double> v95(v2.begin() + 13 * 4096 + 0, v2.begin() + 13 * 4096 + 0 + 4096);
  Pt pt77;
  std::vector<Complex> pt77_complex(v95.begin(), v95.end());
  encoder.Encode(pt77, 1, ctx->param_.GetScale(1), pt77_complex);
  Ct ct181;
  ctx->Mult(ct181, ct161, pt77);
  Ct ct182;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct180.GetScale();
    double rhs_scale = ct181.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct182 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct182, ct180, ct181);
  std::vector<double> v96(v2.begin() + 14 * 4096 + 0, v2.begin() + 14 * 4096 + 0 + 4096);
  Pt pt78;
  std::vector<Complex> pt78_complex(v96.begin(), v96.end());
  encoder.Encode(pt78, 1, ctx->param_.GetScale(1), pt78_complex);
  Ct ct183;
  ctx->Mult(ct183, ct165, pt78);
  Ct ct184;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct182.GetScale();
    double rhs_scale = ct183.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct184 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct184, ct182, ct183);
  std::vector<double> v97(v2.begin() + 15 * 4096 + 0, v2.begin() + 15 * 4096 + 0 + 4096);
  Pt pt79;
  std::vector<Complex> pt79_complex(v97.begin(), v97.end());
  encoder.Encode(pt79, 1, ctx->param_.GetScale(1), pt79_complex);
  Ct ct185;
  ctx->Mult(ct185, ct169, pt79);
  Ct ct186;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct184.GetScale();
    double rhs_scale = ct185.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct186 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct186, ct184, ct185);
  Ct ct187;
  ctx->HRot(ct187, ct186, ui.GetRotationKey(v10), v10);
  Ct ct188;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct171.GetScale();
    double rhs_scale = ct187.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct188 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct188, ct171, ct187);
  std::vector<double> v98(v2.begin() + 16 * 4096 + 0, v2.begin() + 16 * 4096 + 0 + 4096);
  Pt pt80;
  std::vector<Complex> pt80_complex(v98.begin(), v98.end());
  encoder.Encode(pt80, 1, ctx->param_.GetScale(1), pt80_complex);
  Ct ct189;
  ctx->Mult(ct189, ct142, pt80);
  std::vector<double> v99(v2.begin() + 17 * 4096 + 0, v2.begin() + 17 * 4096 + 0 + 4096);
  Pt pt81;
  std::vector<Complex> pt81_complex(v99.begin(), v99.end());
  encoder.Encode(pt81, 1, ctx->param_.GetScale(1), pt81_complex);
  Ct ct190;
  ctx->Mult(ct190, ct145, pt81);
  Ct ct191;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct189.GetScale();
    double rhs_scale = ct190.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct191 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct191, ct189, ct190);
  std::vector<double> v100(v2.begin() + 18 * 4096 + 0, v2.begin() + 18 * 4096 + 0 + 4096);
  Pt pt82;
  std::vector<Complex> pt82_complex(v100.begin(), v100.end());
  encoder.Encode(pt82, 1, ctx->param_.GetScale(1), pt82_complex);
  Ct ct192;
  ctx->Mult(ct192, ct149, pt82);
  Ct ct193;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct191.GetScale();
    double rhs_scale = ct192.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct193 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct193, ct191, ct192);
  std::vector<double> v101(v2.begin() + 19 * 4096 + 0, v2.begin() + 19 * 4096 + 0 + 4096);
  Pt pt83;
  std::vector<Complex> pt83_complex(v101.begin(), v101.end());
  encoder.Encode(pt83, 1, ctx->param_.GetScale(1), pt83_complex);
  Ct ct194;
  ctx->Mult(ct194, ct153, pt83);
  Ct ct195;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct193.GetScale();
    double rhs_scale = ct194.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct195 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct195, ct193, ct194);
  std::vector<double> v102(v2.begin() + 20 * 4096 + 0, v2.begin() + 20 * 4096 + 0 + 4096);
  Pt pt84;
  std::vector<Complex> pt84_complex(v102.begin(), v102.end());
  encoder.Encode(pt84, 1, ctx->param_.GetScale(1), pt84_complex);
  Ct ct196;
  ctx->Mult(ct196, ct157, pt84);
  Ct ct197;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct195.GetScale();
    double rhs_scale = ct196.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct197 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct197, ct195, ct196);
  std::vector<double> v103(v2.begin() + 21 * 4096 + 0, v2.begin() + 21 * 4096 + 0 + 4096);
  Pt pt85;
  std::vector<Complex> pt85_complex(v103.begin(), v103.end());
  encoder.Encode(pt85, 1, ctx->param_.GetScale(1), pt85_complex);
  Ct ct198;
  ctx->Mult(ct198, ct161, pt85);
  Ct ct199;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct197.GetScale();
    double rhs_scale = ct198.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct199 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct199, ct197, ct198);
  std::vector<double> v104(v2.begin() + 22 * 4096 + 0, v2.begin() + 22 * 4096 + 0 + 4096);
  Pt pt86;
  std::vector<Complex> pt86_complex(v104.begin(), v104.end());
  encoder.Encode(pt86, 1, ctx->param_.GetScale(1), pt86_complex);
  Ct ct200;
  ctx->Mult(ct200, ct165, pt86);
  Ct ct201;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct199.GetScale();
    double rhs_scale = ct200.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct201 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct201, ct199, ct200);
  std::vector<double> v105(v2.begin() + 23 * 4096 + 0, v2.begin() + 23 * 4096 + 0 + 4096);
  Pt pt87;
  std::vector<Complex> pt87_complex(v105.begin(), v105.end());
  encoder.Encode(pt87, 1, ctx->param_.GetScale(1), pt87_complex);
  Ct ct202;
  ctx->Mult(ct202, ct169, pt87);
  Ct ct203;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct201.GetScale();
    double rhs_scale = ct202.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct203 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct203, ct201, ct202);
  Ct ct204;
  ctx->HRot(ct204, ct203, ui.GetRotationKey(v11), v11);
  Ct ct205;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct188.GetScale();
    double rhs_scale = ct204.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct205 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct205, ct188, ct204);
  std::vector<double> v106(v2.begin() + 24 * 4096 + 0, v2.begin() + 24 * 4096 + 0 + 4096);
  Pt pt88;
  std::vector<Complex> pt88_complex(v106.begin(), v106.end());
  encoder.Encode(pt88, 1, ctx->param_.GetScale(1), pt88_complex);
  Ct ct206;
  ctx->Mult(ct206, ct142, pt88);
  std::vector<double> v107(v2.begin() + 25 * 4096 + 0, v2.begin() + 25 * 4096 + 0 + 4096);
  Pt pt89;
  std::vector<Complex> pt89_complex(v107.begin(), v107.end());
  encoder.Encode(pt89, 1, ctx->param_.GetScale(1), pt89_complex);
  Ct ct207;
  ctx->Mult(ct207, ct145, pt89);
  Ct ct208;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct206.GetScale();
    double rhs_scale = ct207.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct208 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct208, ct206, ct207);
  std::vector<double> v108(v2.begin() + 26 * 4096 + 0, v2.begin() + 26 * 4096 + 0 + 4096);
  Pt pt90;
  std::vector<Complex> pt90_complex(v108.begin(), v108.end());
  encoder.Encode(pt90, 1, ctx->param_.GetScale(1), pt90_complex);
  Ct ct209;
  ctx->Mult(ct209, ct149, pt90);
  Ct ct210;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct208.GetScale();
    double rhs_scale = ct209.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct210 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct210, ct208, ct209);
  std::vector<double> v109(v2.begin() + 27 * 4096 + 0, v2.begin() + 27 * 4096 + 0 + 4096);
  Pt pt91;
  std::vector<Complex> pt91_complex(v109.begin(), v109.end());
  encoder.Encode(pt91, 1, ctx->param_.GetScale(1), pt91_complex);
  Ct ct211;
  ctx->Mult(ct211, ct153, pt91);
  Ct ct212;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct210.GetScale();
    double rhs_scale = ct211.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct212 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct212, ct210, ct211);
  std::vector<double> v110(v2.begin() + 28 * 4096 + 0, v2.begin() + 28 * 4096 + 0 + 4096);
  Pt pt92;
  std::vector<Complex> pt92_complex(v110.begin(), v110.end());
  encoder.Encode(pt92, 1, ctx->param_.GetScale(1), pt92_complex);
  Ct ct213;
  ctx->Mult(ct213, ct157, pt92);
  Ct ct214;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct212.GetScale();
    double rhs_scale = ct213.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct214 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct214, ct212, ct213);
  std::vector<double> v111(v2.begin() + 29 * 4096 + 0, v2.begin() + 29 * 4096 + 0 + 4096);
  Pt pt93;
  std::vector<Complex> pt93_complex(v111.begin(), v111.end());
  encoder.Encode(pt93, 1, ctx->param_.GetScale(1), pt93_complex);
  Ct ct215;
  ctx->Mult(ct215, ct161, pt93);
  Ct ct216;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct214.GetScale();
    double rhs_scale = ct215.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct216 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct216, ct214, ct215);
  std::vector<double> v112(v2.begin() + 30 * 4096 + 0, v2.begin() + 30 * 4096 + 0 + 4096);
  Pt pt94;
  std::vector<Complex> pt94_complex(v112.begin(), v112.end());
  encoder.Encode(pt94, 1, ctx->param_.GetScale(1), pt94_complex);
  Ct ct217;
  ctx->Mult(ct217, ct165, pt94);
  Ct ct218;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct216.GetScale();
    double rhs_scale = ct217.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct218 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct218, ct216, ct217);
  std::vector<double> v113(v2.begin() + 31 * 4096 + 0, v2.begin() + 31 * 4096 + 0 + 4096);
  Pt pt95;
  std::vector<Complex> pt95_complex(v113.begin(), v113.end());
  encoder.Encode(pt95, 1, ctx->param_.GetScale(1), pt95_complex);
  Ct ct219;
  ctx->Mult(ct219, ct169, pt95);
  Ct ct220;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct218.GetScale();
    double rhs_scale = ct219.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct220 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct220, ct218, ct219);
  Ct ct221;
  ctx->HRot(ct221, ct220, ui.GetRotationKey(v12), v12);
  Ct ct222;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct205.GetScale();
    double rhs_scale = ct221.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct222 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct222, ct205, ct221);
  std::vector<double> v114(v2.begin() + 32 * 4096 + 0, v2.begin() + 32 * 4096 + 0 + 4096);
  Pt pt96;
  std::vector<Complex> pt96_complex(v114.begin(), v114.end());
  encoder.Encode(pt96, 1, ctx->param_.GetScale(1), pt96_complex);
  Ct ct223;
  ctx->Mult(ct223, ct142, pt96);
  std::vector<double> v115(v2.begin() + 33 * 4096 + 0, v2.begin() + 33 * 4096 + 0 + 4096);
  Pt pt97;
  std::vector<Complex> pt97_complex(v115.begin(), v115.end());
  encoder.Encode(pt97, 1, ctx->param_.GetScale(1), pt97_complex);
  Ct ct224;
  ctx->Mult(ct224, ct145, pt97);
  Ct ct225;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct223.GetScale();
    double rhs_scale = ct224.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct225 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct225, ct223, ct224);
  std::vector<double> v116(v2.begin() + 34 * 4096 + 0, v2.begin() + 34 * 4096 + 0 + 4096);
  Pt pt98;
  std::vector<Complex> pt98_complex(v116.begin(), v116.end());
  encoder.Encode(pt98, 1, ctx->param_.GetScale(1), pt98_complex);
  Ct ct226;
  ctx->Mult(ct226, ct149, pt98);
  Ct ct227;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct225.GetScale();
    double rhs_scale = ct226.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct227 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct227, ct225, ct226);
  std::vector<double> v117(v2.begin() + 35 * 4096 + 0, v2.begin() + 35 * 4096 + 0 + 4096);
  Pt pt99;
  std::vector<Complex> pt99_complex(v117.begin(), v117.end());
  encoder.Encode(pt99, 1, ctx->param_.GetScale(1), pt99_complex);
  Ct ct228;
  ctx->Mult(ct228, ct153, pt99);
  Ct ct229;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct227.GetScale();
    double rhs_scale = ct228.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct229 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct229, ct227, ct228);
  std::vector<double> v118(v2.begin() + 36 * 4096 + 0, v2.begin() + 36 * 4096 + 0 + 4096);
  Pt pt100;
  std::vector<Complex> pt100_complex(v118.begin(), v118.end());
  encoder.Encode(pt100, 1, ctx->param_.GetScale(1), pt100_complex);
  Ct ct230;
  ctx->Mult(ct230, ct157, pt100);
  Ct ct231;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct229.GetScale();
    double rhs_scale = ct230.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct231 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct231, ct229, ct230);
  std::vector<double> v119(v2.begin() + 37 * 4096 + 0, v2.begin() + 37 * 4096 + 0 + 4096);
  Pt pt101;
  std::vector<Complex> pt101_complex(v119.begin(), v119.end());
  encoder.Encode(pt101, 1, ctx->param_.GetScale(1), pt101_complex);
  Ct ct232;
  ctx->Mult(ct232, ct161, pt101);
  Ct ct233;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct231.GetScale();
    double rhs_scale = ct232.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct233 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct233, ct231, ct232);
  std::vector<double> v120(v2.begin() + 38 * 4096 + 0, v2.begin() + 38 * 4096 + 0 + 4096);
  Pt pt102;
  std::vector<Complex> pt102_complex(v120.begin(), v120.end());
  encoder.Encode(pt102, 1, ctx->param_.GetScale(1), pt102_complex);
  Ct ct234;
  ctx->Mult(ct234, ct165, pt102);
  Ct ct235;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct233.GetScale();
    double rhs_scale = ct234.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct235 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct235, ct233, ct234);
  std::vector<double> v121(v2.begin() + 39 * 4096 + 0, v2.begin() + 39 * 4096 + 0 + 4096);
  Pt pt103;
  std::vector<Complex> pt103_complex(v121.begin(), v121.end());
  encoder.Encode(pt103, 1, ctx->param_.GetScale(1), pt103_complex);
  Ct ct236;
  ctx->Mult(ct236, ct169, pt103);
  Ct ct237;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct235.GetScale();
    double rhs_scale = ct236.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct237 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct237, ct235, ct236);
  Ct ct238;
  ctx->HRot(ct238, ct237, ui.GetRotationKey(v13), v13);
  Ct ct239;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct222.GetScale();
    double rhs_scale = ct238.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct239 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct239, ct222, ct238);
  std::vector<double> v122(v2.begin() + 40 * 4096 + 0, v2.begin() + 40 * 4096 + 0 + 4096);
  Pt pt104;
  std::vector<Complex> pt104_complex(v122.begin(), v122.end());
  encoder.Encode(pt104, 1, ctx->param_.GetScale(1), pt104_complex);
  Ct ct240;
  ctx->Mult(ct240, ct142, pt104);
  std::vector<double> v123(v2.begin() + 41 * 4096 + 0, v2.begin() + 41 * 4096 + 0 + 4096);
  Pt pt105;
  std::vector<Complex> pt105_complex(v123.begin(), v123.end());
  encoder.Encode(pt105, 1, ctx->param_.GetScale(1), pt105_complex);
  Ct ct241;
  ctx->Mult(ct241, ct145, pt105);
  Ct ct242;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct240.GetScale();
    double rhs_scale = ct241.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct242 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct242, ct240, ct241);
  std::vector<double> v124(v2.begin() + 42 * 4096 + 0, v2.begin() + 42 * 4096 + 0 + 4096);
  Pt pt106;
  std::vector<Complex> pt106_complex(v124.begin(), v124.end());
  encoder.Encode(pt106, 1, ctx->param_.GetScale(1), pt106_complex);
  Ct ct243;
  ctx->Mult(ct243, ct149, pt106);
  Ct ct244;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct242.GetScale();
    double rhs_scale = ct243.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct244 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct244, ct242, ct243);
  std::vector<double> v125(v2.begin() + 43 * 4096 + 0, v2.begin() + 43 * 4096 + 0 + 4096);
  Pt pt107;
  std::vector<Complex> pt107_complex(v125.begin(), v125.end());
  encoder.Encode(pt107, 1, ctx->param_.GetScale(1), pt107_complex);
  Ct ct245;
  ctx->Mult(ct245, ct153, pt107);
  Ct ct246;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct244.GetScale();
    double rhs_scale = ct245.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct246 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct246, ct244, ct245);
  std::vector<double> v126(v2.begin() + 44 * 4096 + 0, v2.begin() + 44 * 4096 + 0 + 4096);
  Pt pt108;
  std::vector<Complex> pt108_complex(v126.begin(), v126.end());
  encoder.Encode(pt108, 1, ctx->param_.GetScale(1), pt108_complex);
  Ct ct247;
  ctx->Mult(ct247, ct157, pt108);
  Ct ct248;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct246.GetScale();
    double rhs_scale = ct247.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct248 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct248, ct246, ct247);
  std::vector<double> v127(v2.begin() + 45 * 4096 + 0, v2.begin() + 45 * 4096 + 0 + 4096);
  Pt pt109;
  std::vector<Complex> pt109_complex(v127.begin(), v127.end());
  encoder.Encode(pt109, 1, ctx->param_.GetScale(1), pt109_complex);
  Ct ct249;
  ctx->Mult(ct249, ct161, pt109);
  Ct ct250;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct248.GetScale();
    double rhs_scale = ct249.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct250 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct250, ct248, ct249);
  std::vector<double> v128(v2.begin() + 46 * 4096 + 0, v2.begin() + 46 * 4096 + 0 + 4096);
  Pt pt110;
  std::vector<Complex> pt110_complex(v128.begin(), v128.end());
  encoder.Encode(pt110, 1, ctx->param_.GetScale(1), pt110_complex);
  Ct ct251;
  ctx->Mult(ct251, ct165, pt110);
  Ct ct252;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct250.GetScale();
    double rhs_scale = ct251.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct252 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct252, ct250, ct251);
  std::vector<double> v129(v2.begin() + 47 * 4096 + 0, v2.begin() + 47 * 4096 + 0 + 4096);
  Pt pt111;
  std::vector<Complex> pt111_complex(v129.begin(), v129.end());
  encoder.Encode(pt111, 1, ctx->param_.GetScale(1), pt111_complex);
  Ct ct253;
  ctx->Mult(ct253, ct169, pt111);
  Ct ct254;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct252.GetScale();
    double rhs_scale = ct253.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct254 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct254, ct252, ct253);
  Ct ct255;
  ctx->HRot(ct255, ct254, ui.GetRotationKey(v14), v14);
  Ct ct256;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct239.GetScale();
    double rhs_scale = ct255.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct256 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct256, ct239, ct255);
  std::vector<double> v130(v2.begin() + 48 * 4096 + 0, v2.begin() + 48 * 4096 + 0 + 4096);
  Pt pt112;
  std::vector<Complex> pt112_complex(v130.begin(), v130.end());
  encoder.Encode(pt112, 1, ctx->param_.GetScale(1), pt112_complex);
  Ct ct257;
  ctx->Mult(ct257, ct142, pt112);
  std::vector<double> v131(v2.begin() + 49 * 4096 + 0, v2.begin() + 49 * 4096 + 0 + 4096);
  Pt pt113;
  std::vector<Complex> pt113_complex(v131.begin(), v131.end());
  encoder.Encode(pt113, 1, ctx->param_.GetScale(1), pt113_complex);
  Ct ct258;
  ctx->Mult(ct258, ct145, pt113);
  Ct ct259;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct257.GetScale();
    double rhs_scale = ct258.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct259 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct259, ct257, ct258);
  std::vector<double> v132(v2.begin() + 50 * 4096 + 0, v2.begin() + 50 * 4096 + 0 + 4096);
  Pt pt114;
  std::vector<Complex> pt114_complex(v132.begin(), v132.end());
  encoder.Encode(pt114, 1, ctx->param_.GetScale(1), pt114_complex);
  Ct ct260;
  ctx->Mult(ct260, ct149, pt114);
  Ct ct261;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct259.GetScale();
    double rhs_scale = ct260.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct261 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct261, ct259, ct260);
  std::vector<double> v133(v2.begin() + 51 * 4096 + 0, v2.begin() + 51 * 4096 + 0 + 4096);
  Pt pt115;
  std::vector<Complex> pt115_complex(v133.begin(), v133.end());
  encoder.Encode(pt115, 1, ctx->param_.GetScale(1), pt115_complex);
  Ct ct262;
  ctx->Mult(ct262, ct153, pt115);
  Ct ct263;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct261.GetScale();
    double rhs_scale = ct262.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct263 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct263, ct261, ct262);
  std::vector<double> v134(v2.begin() + 52 * 4096 + 0, v2.begin() + 52 * 4096 + 0 + 4096);
  Pt pt116;
  std::vector<Complex> pt116_complex(v134.begin(), v134.end());
  encoder.Encode(pt116, 1, ctx->param_.GetScale(1), pt116_complex);
  Ct ct264;
  ctx->Mult(ct264, ct157, pt116);
  Ct ct265;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct263.GetScale();
    double rhs_scale = ct264.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct265 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct265, ct263, ct264);
  std::vector<double> v135(v2.begin() + 53 * 4096 + 0, v2.begin() + 53 * 4096 + 0 + 4096);
  Pt pt117;
  std::vector<Complex> pt117_complex(v135.begin(), v135.end());
  encoder.Encode(pt117, 1, ctx->param_.GetScale(1), pt117_complex);
  Ct ct266;
  ctx->Mult(ct266, ct161, pt117);
  Ct ct267;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct265.GetScale();
    double rhs_scale = ct266.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct267 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct267, ct265, ct266);
  std::vector<double> v136(v2.begin() + 54 * 4096 + 0, v2.begin() + 54 * 4096 + 0 + 4096);
  Pt pt118;
  std::vector<Complex> pt118_complex(v136.begin(), v136.end());
  encoder.Encode(pt118, 1, ctx->param_.GetScale(1), pt118_complex);
  Ct ct268;
  ctx->Mult(ct268, ct165, pt118);
  Ct ct269;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct267.GetScale();
    double rhs_scale = ct268.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct269 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct269, ct267, ct268);
  std::vector<double> v137(v2.begin() + 55 * 4096 + 0, v2.begin() + 55 * 4096 + 0 + 4096);
  Pt pt119;
  std::vector<Complex> pt119_complex(v137.begin(), v137.end());
  encoder.Encode(pt119, 1, ctx->param_.GetScale(1), pt119_complex);
  Ct ct270;
  ctx->Mult(ct270, ct169, pt119);
  Ct ct271;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct269.GetScale();
    double rhs_scale = ct270.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct271 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct271, ct269, ct270);
  Ct ct272;
  ctx->HRot(ct272, ct271, ui.GetRotationKey(v15), v15);
  Ct ct273;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct256.GetScale();
    double rhs_scale = ct272.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct273 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct273, ct256, ct272);
  std::vector<double> v138(v2.begin() + 56 * 4096 + 0, v2.begin() + 56 * 4096 + 0 + 4096);
  Pt pt120;
  std::vector<Complex> pt120_complex(v138.begin(), v138.end());
  encoder.Encode(pt120, 1, ctx->param_.GetScale(1), pt120_complex);
  Ct ct274;
  ctx->Mult(ct274, ct142, pt120);
  std::vector<double> v139(v2.begin() + 57 * 4096 + 0, v2.begin() + 57 * 4096 + 0 + 4096);
  Pt pt121;
  std::vector<Complex> pt121_complex(v139.begin(), v139.end());
  encoder.Encode(pt121, 1, ctx->param_.GetScale(1), pt121_complex);
  Ct ct275;
  ctx->Mult(ct275, ct145, pt121);
  Ct ct276;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct274.GetScale();
    double rhs_scale = ct275.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct276 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct276, ct274, ct275);
  std::vector<double> v140(v2.begin() + 58 * 4096 + 0, v2.begin() + 58 * 4096 + 0 + 4096);
  Pt pt122;
  std::vector<Complex> pt122_complex(v140.begin(), v140.end());
  encoder.Encode(pt122, 1, ctx->param_.GetScale(1), pt122_complex);
  Ct ct277;
  ctx->Mult(ct277, ct149, pt122);
  Ct ct278;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct276.GetScale();
    double rhs_scale = ct277.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct278 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct278, ct276, ct277);
  std::vector<double> v141(v2.begin() + 59 * 4096 + 0, v2.begin() + 59 * 4096 + 0 + 4096);
  Pt pt123;
  std::vector<Complex> pt123_complex(v141.begin(), v141.end());
  encoder.Encode(pt123, 1, ctx->param_.GetScale(1), pt123_complex);
  Ct ct279;
  ctx->Mult(ct279, ct153, pt123);
  Ct ct280;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct278.GetScale();
    double rhs_scale = ct279.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct280 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct280, ct278, ct279);
  std::vector<double> v142(v2.begin() + 60 * 4096 + 0, v2.begin() + 60 * 4096 + 0 + 4096);
  Pt pt124;
  std::vector<Complex> pt124_complex(v142.begin(), v142.end());
  encoder.Encode(pt124, 1, ctx->param_.GetScale(1), pt124_complex);
  Ct ct281;
  ctx->Mult(ct281, ct157, pt124);
  Ct ct282;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct280.GetScale();
    double rhs_scale = ct281.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct282 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct282, ct280, ct281);
  std::vector<double> v143(v2.begin() + 61 * 4096 + 0, v2.begin() + 61 * 4096 + 0 + 4096);
  Pt pt125;
  std::vector<Complex> pt125_complex(v143.begin(), v143.end());
  encoder.Encode(pt125, 1, ctx->param_.GetScale(1), pt125_complex);
  Ct ct283;
  ctx->Mult(ct283, ct161, pt125);
  Ct ct284;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct282.GetScale();
    double rhs_scale = ct283.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct284 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct284, ct282, ct283);
  std::vector<double> v144(v2.begin() + 62 * 4096 + 0, v2.begin() + 62 * 4096 + 0 + 4096);
  Pt pt126;
  std::vector<Complex> pt126_complex(v144.begin(), v144.end());
  encoder.Encode(pt126, 1, ctx->param_.GetScale(1), pt126_complex);
  Ct ct285;
  ctx->Mult(ct285, ct165, pt126);
  Ct ct286;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct284.GetScale();
    double rhs_scale = ct285.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct286 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct286, ct284, ct285);
  std::vector<double> v145(v2.begin() + 63 * 4096 + 0, v2.begin() + 63 * 4096 + 0 + 4096);
  Pt pt127;
  std::vector<Complex> pt127_complex(v145.begin(), v145.end());
  encoder.Encode(pt127, 1, ctx->param_.GetScale(1), pt127_complex);
  Ct ct287;
  ctx->Mult(ct287, ct169, pt127);
  Ct ct288;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct286.GetScale();
    double rhs_scale = ct287.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct288 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct288, ct286, ct287);
  Ct ct289;
  ctx->HRot(ct289, ct288, ui.GetRotationKey(v16), v16);
  Ct ct290;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct273.GetScale();
    double rhs_scale = ct289.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct290 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct290, ct273, ct289);
  std::vector<Ct> v146;
  v146.resize(1);
  Ct ct291;
  ctx->Rescale(ct291, ct290);
  std::vector<Ct> v147;
  v147.resize(1);
  Ct ct291_c0;
  ctx->Copy(ct291_c0, ct291);
  v147[v17] = std::move(ct291_c0);
  return v147;
}

std::vector<Ct> bert_attention__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1) {
  std::vector<double> v1(v0.begin() + 0 * 4096 + 0, v0.begin() + 0 * 4096 + 0 + 4096);
  Pt pt;
  std::vector<Complex> pt_complex(v1.begin(), v1.end());
  encoder.Encode(pt, 2, ctx->param_.GetScale(2), pt_complex);
  Ct ct;
  ui.Encrypt(ct, pt);
  std::vector<Ct> v2;
  v2.reserve(1);
  Ct ct_c1;
  ctx->Copy(ct_c1, ct);
  v2.emplace_back(std::move(ct_c1));
  return v2;
}

std::vector<double> bert_attention__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1) {
  int64_t v1 = 0;
  auto& ct = v0[v1];
  Pt pt;
  ui.Decrypt(pt, ct);
  std::vector<Complex> v2_complex;
  encoder.Decode(v2_complex, pt);
  std::vector<double> v2(v2_complex.size());
  for (size_t i = 0; i < v2_complex.size(); ++i) v2[i] = v2_complex[i].real();
  return v2;
}

std::tuple<CtxPtr, UI> __configure() {
  static std::vector<word> main_primes = {36028797017456641ULL, 35184371138561ULL, 35184372121601ULL};
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
  ui.PrepareRotationKey(64, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(128, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(192, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(256, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(320, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(384, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(448, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(512, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(1024, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(1536, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(2048, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(2560, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(3072, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(3584, static_cast<int>(main_primes.size()) - 1);
  return {ctx, std::move(ui)};
}

