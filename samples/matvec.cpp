
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

std::vector<double> _assign_layout_16910372757803757633() {
  int64_t v0 = 0;
  int32_t v1 = 16;
  std::vector<double> v2(1024, 0);
  int32_t v3 = 0;
  int32_t v4 = 1;
  int32_t v5 = 1024;
  std::vector<double> v6 = {-0.451415330171585, -0.0277900472283363, 0.311195373535156, 0.182548940181732, -0.25880953669548, 0.497506737709045, 0.00115649134386331, -0.194445714354515, 0.158549472689629, 0, 0.310650676488876, -0.214976981282234, -0.0236619990319014, -0.392960965633392, 0.647287011146545, 0.831665277481079};
  std::vector<double> v9 = std::move(v2);
  for (int64_t v8 = 0; v8 < 1024; v8 += 1) {
    int32_t v10 = v8 % v1;
    int64_t v11 = static_cast<int64_t>(v10);
    double v12 = v6[v11];
    int64_t v13 = static_cast<int64_t>(v8);
    auto v14 = std::move(v9);
    v14[v13 + 1024 * (v0)] = v12;
    v9 = std::move(v14);
  }
  std::vector<double> v7 = std::move(v9);
  return v7;
}

std::vector<double> _assign_layout_1535064765322952764() {
  int32_t v0 = 1024;
  int32_t v1 = 16;
  std::vector<double> v2(16384, 0);
  int32_t v3 = 0;
  int32_t v4 = 1;
  std::vector<double> v5 = {0.0992246866226196, 0.186927512288094, 1.11323213577271, -0.661866903305054, 1.14751410484314, -0.211862608790398, -1.26457107067108, 0.0226964186877012, -2.8995475769043, 0.256206631660461, 0.588923454284668, -0.667416632175445, 0.607778370380401, 0.260872364044189, -0.137271597981453, -0.794038355350494, -0.381407767534256, -0.946523189544677, 0.0578776858747005, 0.718836426734924, -1.24268174171448, 0.938824236392974, -0.431416898965836, 0.191955298185349, 1.13260626792908, -0.986824989318847, 0.574271678924561, 0.454489141702652, 0.563138723373413, 0.539456129074097, -1.05352544784546, 0.0650914758443832, 0.181312143802643, 0.454538226127625, 0.122071698307991, -0.47020760178566, 0.601066172122955, 0.527348399162292, -0.141457214951515, -0.0720636546611785, -0.543793797492981, -0.123041018843651, -0.369369655847549, 0.555918574333191, -1.1289473772049, 0.553164839744568, -0.955740272998809, -0.208183318376541, -0.157960042357445, 0.275503069162369, 0.394202142953873, 1.58992755413055, -0.716345906257629, 0.868726789951324, -0.0778019726276397, -0.732523918151855, -2.48991799354553, 0.131586417555809, -0.818917512893677, 0.545576333999634, -0.162624537944794, -0.189138919115067, 0.480629742145538, 0.530687093734741, -0.964649200439453, -0.370172888040543, 0.313313752412796, 0.0647574439644814, 1.96434772014618, -0.51371169090271, -0.166721880435944, -0.385623902082443, 0.922843158245086, 0.427547335624695, 1.51181399822235, 0.142105132341385, 0.598540484905243, 0.0274777915328741, 0.490155249834061, -0.392955243587494, 0.275448828935623, -0.72272264957428, -0.327790230512619, 1.29883456230164, -1.24775183200836, -0.056285310536623, -0.948979198932647, 0.330862075090408, 1.7444931268692, -0.114400379359722, -0.964258134365081, 0.24027144908905, -0.563671886920929, -0.89652681350708, -0.334315627813339, -0.384786665439606, 0.114905454218388, -0.333166062831879, -0.0738262832164764, -0.249753788113594, 0.486313760280609, 1.07196342945099, 0.315511167049408, -0.0841916725039482, -2.70876336097717, 0.848621785640716, -0.645231425762176, -0.101779691874981, -0.23064124584198, -0.0716918483376503, -1.12681853352115E-4, -0.207001850008965, 0.197146743535995, -0.284750372171402, -0.50972318649292, 0.032491646707058, 1.42427027225494, 0.141853332519531, 0.607029676437378, 0.50927346944809, 1.10566747188568, -0.0362475253641605, 1.33680927753448, -0.160905048251152, 0.546912789344788, 0.326243549585342, -0.300572067499161, 0.428382337093353, -0.738234460353851, 0.330806046724319, 0.286297976970673, 1.58761894702911, -0.71573382616043, -0.772574305534362, 0.255487352609634, 0.584364652633667, 1.22524285316467, 0.109442748129368, 0.0473451875150204, 0.261543840169907, -0.317237883806229, 0.233622893691063, -0.226570799946785, 0.220496818423271, -0.195044487714767, -0.287197321653366, 0.396501183509827, -0.189009755849838, -0.831791877746582, 0.34788578748703, 0.156113848090172, -0.0788015499711036, -2.33800339698792, -0.104814141988754, -0.494833648204803, 0.513059079647064, 0.480570584535599, -0.547497034072876, -0.458309590816498, -0.148206532001495, -0.00554171437397599, -0.626607358455657, 0.139947563409805, -0.362113356590271, 1.86286163330078, 0.12404315918684, 0.246206611394882, -0.033918734639883, -1.24023795127869, 0.161590248346329, 1.26691663265228, -0.209617927670479, 0.0366545654833317, -0.258321821689606, 0.123686246573925, -0.320211201906204, 0.282270938158035, 0.533514142036438, -0.500115215778351, 0.635144770145416, -1.26488256454468, 0.0139037305489182, 0.0958119630813598, -0.612099587917327, 0.60860002040863, -0.185381308197975, -0.819893181324005, -0.187680512666702, 0.0450635366141796, -0.246530383825302, -0.600519955158234, 0.934989273548126, -0.151964589953423, 0.0554278343915939, 0.185905829071999, -0.0506787896156311, -1.22751820087433, 0.946358561515808, -0.712347388267517, 0.598950266838074, -2.40225839614868, 0.354834914207458, 0.214426159858704, -0.321492224931717, -0.458649456501007, 0.511211693286896, 1.56523978710175, 0.721896588802337, -0.035896223038435, -0.0970092639327049, -0.55540144443512, -0.0191589146852493, 1.52065753936768, 0.806710064411163, 0.085726074874401, -0.243274495005608, 1.17313587665558, -0.842383623123169, 0.0923027768731117, 0.292922526597977, -0.00216138293035328, -0.360774785280228, 0.420725166797638, 0.0427541136741638, -0.596498668193817, 0.643704891204833, -0.148111045360565, 1.04437649250031, 0.972919225692749, -0.488904893398285, -0.205765828490257, 0.240273147821426, -1.48157644271851, -0.181547075510025, 1.52375555038452, 0.0426931940019131, -0.0227817241102457, -0.6388920545578, -0.713748395442962, -0.17439877986908, 0.230908960103989, -0.18939845263958, 0.261706441640854, 1.00754237174988, -0.666052341461181, 0.562415778636932, 0.271623253822327, -0.834818065166473, 0.152525588870049, 0.684201002120972, -0.59854382276535, -0.424889355897903, -0.552195012569427, -0.0453558638691902, -0.441321521997452, -0.154636800289154};
  std::vector<double> v8 = std::move(v2);
  for (int64_t v7 = 0; v7 < 16; v7 += 1) {
    std::vector<double> v11 = std::move(v8);
    for (int64_t v10 = 0; v10 < 1024; v10 += 1) {
      int32_t v12 = v10 % v1;
      int32_t v13 = v7 + v10;
      int32_t v14 = v13 % v1;
      int64_t v15 = static_cast<int64_t>(v12);
      int64_t v16 = static_cast<int64_t>(v14);
      double v17 = v5[v16 + 16 * (v15)];
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

std::vector<Ct> matvec(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0) {
  int64_t v1 = 12;
  int64_t v2 = 8;
  int64_t v3 = 4;
  int64_t v4 = 3;
  int64_t v5 = 2;
  int64_t v6 = 1;
  int64_t v7 = 0;
  std::vector<double> v8 = _assign_layout_1535064765322952764();
  std::vector<double> v9 = _assign_layout_16910372757803757633();
  std::vector<double> v10(v8.begin() + 4 * 1024 + 0, v8.begin() + 4 * 1024 + 0 + 1020);
  std::vector<double> v11(v8.begin() + 4 * 1024 + 1020, v8.begin() + 4 * 1024 + 1020 + 4);
  std::vector<double> v12(1024);
  std::vector<double> v13(1024);
  std::copy(v10.begin(), v10.end(), v13.begin() + 0 * 1024 + 4);
  auto v14 = std::move(v13);
  std::copy(v11.begin(), v11.end(), v14.begin() + 0 * 1024 + 0);
  std::vector<double> v15(v8.begin() + 5 * 1024 + 0, v8.begin() + 5 * 1024 + 0 + 1020);
  std::vector<double> v16(v8.begin() + 5 * 1024 + 1020, v8.begin() + 5 * 1024 + 1020 + 4);
  std::vector<double> v17(1024);
  std::copy(v15.begin(), v15.end(), v17.begin() + 0 * 1024 + 4);
  auto v18 = std::move(v17);
  std::copy(v16.begin(), v16.end(), v18.begin() + 0 * 1024 + 0);
  std::vector<double> v19(v8.begin() + 6 * 1024 + 0, v8.begin() + 6 * 1024 + 0 + 1020);
  std::vector<double> v20(v8.begin() + 6 * 1024 + 1020, v8.begin() + 6 * 1024 + 1020 + 4);
  std::vector<double> v21(1024);
  std::copy(v19.begin(), v19.end(), v21.begin() + 0 * 1024 + 4);
  auto v22 = std::move(v21);
  std::copy(v20.begin(), v20.end(), v22.begin() + 0 * 1024 + 0);
  std::vector<double> v23(v8.begin() + 7 * 1024 + 0, v8.begin() + 7 * 1024 + 0 + 1020);
  std::vector<double> v24(v8.begin() + 7 * 1024 + 1020, v8.begin() + 7 * 1024 + 1020 + 4);
  std::vector<double> v25(1024);
  std::copy(v23.begin(), v23.end(), v25.begin() + 0 * 1024 + 4);
  auto v26 = std::move(v25);
  std::copy(v24.begin(), v24.end(), v26.begin() + 0 * 1024 + 0);
  std::vector<double> v27(v8.begin() + 8 * 1024 + 0, v8.begin() + 8 * 1024 + 0 + 1016);
  std::vector<double> v28(v8.begin() + 8 * 1024 + 1016, v8.begin() + 8 * 1024 + 1016 + 8);
  std::vector<double> v29(1024);
  std::copy(v27.begin(), v27.end(), v29.begin() + 0 * 1024 + 8);
  auto v30 = std::move(v29);
  std::copy(v28.begin(), v28.end(), v30.begin() + 0 * 1024 + 0);
  std::vector<double> v31(v8.begin() + 9 * 1024 + 0, v8.begin() + 9 * 1024 + 0 + 1016);
  std::vector<double> v32(v8.begin() + 9 * 1024 + 1016, v8.begin() + 9 * 1024 + 1016 + 8);
  std::vector<double> v33(1024);
  std::copy(v31.begin(), v31.end(), v33.begin() + 0 * 1024 + 8);
  auto v34 = std::move(v33);
  std::copy(v32.begin(), v32.end(), v34.begin() + 0 * 1024 + 0);
  std::vector<double> v35(v8.begin() + 10 * 1024 + 0, v8.begin() + 10 * 1024 + 0 + 1016);
  std::vector<double> v36(v8.begin() + 10 * 1024 + 1016, v8.begin() + 10 * 1024 + 1016 + 8);
  std::vector<double> v37(1024);
  std::copy(v35.begin(), v35.end(), v37.begin() + 0 * 1024 + 8);
  auto v38 = std::move(v37);
  std::copy(v36.begin(), v36.end(), v38.begin() + 0 * 1024 + 0);
  std::vector<double> v39(v8.begin() + 11 * 1024 + 0, v8.begin() + 11 * 1024 + 0 + 1016);
  std::vector<double> v40(v8.begin() + 11 * 1024 + 1016, v8.begin() + 11 * 1024 + 1016 + 8);
  std::vector<double> v41(1024);
  std::copy(v39.begin(), v39.end(), v41.begin() + 0 * 1024 + 8);
  auto v42 = std::move(v41);
  std::copy(v40.begin(), v40.end(), v42.begin() + 0 * 1024 + 0);
  std::vector<double> v43(v8.begin() + 12 * 1024 + 0, v8.begin() + 12 * 1024 + 0 + 1012);
  std::vector<double> v44(v8.begin() + 12 * 1024 + 1012, v8.begin() + 12 * 1024 + 1012 + 12);
  std::vector<double> v45(1024);
  std::copy(v43.begin(), v43.end(), v45.begin() + 0 * 1024 + 12);
  auto v46 = std::move(v45);
  std::copy(v44.begin(), v44.end(), v46.begin() + 0 * 1024 + 0);
  std::vector<double> v47(v8.begin() + 13 * 1024 + 0, v8.begin() + 13 * 1024 + 0 + 1012);
  std::vector<double> v48(v8.begin() + 13 * 1024 + 1012, v8.begin() + 13 * 1024 + 1012 + 12);
  std::vector<double> v49(1024);
  std::copy(v47.begin(), v47.end(), v49.begin() + 0 * 1024 + 12);
  auto v50 = std::move(v49);
  std::copy(v48.begin(), v48.end(), v50.begin() + 0 * 1024 + 0);
  std::vector<double> v51(v8.begin() + 14 * 1024 + 0, v8.begin() + 14 * 1024 + 0 + 1012);
  std::vector<double> v52(v8.begin() + 14 * 1024 + 1012, v8.begin() + 14 * 1024 + 1012 + 12);
  std::vector<double> v53(1024);
  std::copy(v51.begin(), v51.end(), v53.begin() + 0 * 1024 + 12);
  auto v54 = std::move(v53);
  std::copy(v52.begin(), v52.end(), v54.begin() + 0 * 1024 + 0);
  std::vector<double> v55(v8.begin() + 15 * 1024 + 0, v8.begin() + 15 * 1024 + 0 + 1012);
  std::vector<double> v56(v8.begin() + 15 * 1024 + 1012, v8.begin() + 15 * 1024 + 1012 + 12);
  std::vector<double> v57(1024);
  std::copy(v55.begin(), v55.end(), v57.begin() + 0 * 1024 + 12);
  auto v58 = std::move(v57);
  std::copy(v56.begin(), v56.end(), v58.begin() + 0 * 1024 + 0);
  std::vector<double> v59(v8.begin() + 0 * 1024 + 0, v8.begin() + 0 * 1024 + 0 + 1024);
  Pt pt;
  std::vector<Complex> pt_complex(v59.begin(), v59.end());
  encoder.Encode(pt, 0, ctx->param_.GetScale(0), pt_complex);
  auto& ct = v0[v7];
  Ct ct1;
  ctx->Mult(ct1, ct, pt);
  Ct ct2;
  ctx->HRot(ct2, ct, ui.GetRotationKey(v6), v6);
  std::vector<double> v60(v8.begin() + 1 * 1024 + 0, v8.begin() + 1 * 1024 + 0 + 1024);
  Pt pt1;
  std::vector<Complex> pt1_complex(v60.begin(), v60.end());
  encoder.Encode(pt1, 0, ctx->param_.GetScale(0), pt1_complex);
  Ct ct3;
  ctx->Mult(ct3, ct2, pt1);
  Ct ct4;
  ctx->HRot(ct4, ct, ui.GetRotationKey(v5), v5);
  std::vector<double> v61(v8.begin() + 2 * 1024 + 0, v8.begin() + 2 * 1024 + 0 + 1024);
  Pt pt2;
  std::vector<Complex> pt2_complex(v61.begin(), v61.end());
  encoder.Encode(pt2, 0, ctx->param_.GetScale(0), pt2_complex);
  Ct ct5;
  ctx->Mult(ct5, ct4, pt2);
  Ct ct6;
  ctx->HRot(ct6, ct, ui.GetRotationKey(v4), v4);
  std::vector<double> v62(v8.begin() + 3 * 1024 + 0, v8.begin() + 3 * 1024 + 0 + 1024);
  Pt pt3;
  std::vector<Complex> pt3_complex(v62.begin(), v62.end());
  encoder.Encode(pt3, 0, ctx->param_.GetScale(0), pt3_complex);
  Ct ct7;
  ctx->Mult(ct7, ct6, pt3);
  std::vector<double> v63(v14.begin() + 0 * 1024 + 0, v14.begin() + 0 * 1024 + 0 + 1024);
  Pt pt4;
  std::vector<Complex> pt4_complex(v63.begin(), v63.end());
  encoder.Encode(pt4, 0, ctx->param_.GetScale(0), pt4_complex);
  Ct ct8;
  ctx->Mult(ct8, ct, pt4);
  std::vector<double> v64(v18.begin() + 0 * 1024 + 0, v18.begin() + 0 * 1024 + 0 + 1024);
  Pt pt5;
  std::vector<Complex> pt5_complex(v64.begin(), v64.end());
  encoder.Encode(pt5, 0, ctx->param_.GetScale(0), pt5_complex);
  Ct ct9;
  ctx->Mult(ct9, ct2, pt5);
  std::vector<double> v65(v22.begin() + 0 * 1024 + 0, v22.begin() + 0 * 1024 + 0 + 1024);
  Pt pt6;
  std::vector<Complex> pt6_complex(v65.begin(), v65.end());
  encoder.Encode(pt6, 0, ctx->param_.GetScale(0), pt6_complex);
  Ct ct10;
  ctx->Mult(ct10, ct4, pt6);
  std::vector<double> v66(v26.begin() + 0 * 1024 + 0, v26.begin() + 0 * 1024 + 0 + 1024);
  Pt pt7;
  std::vector<Complex> pt7_complex(v66.begin(), v66.end());
  encoder.Encode(pt7, 0, ctx->param_.GetScale(0), pt7_complex);
  Ct ct11;
  ctx->Mult(ct11, ct6, pt7);
  Ct ct12;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct8.GetScale();
    double rhs_scale = ct9.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct12 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct12, ct8, ct9);
  Ct ct13;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct10.GetScale();
    double rhs_scale = ct11.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct13 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct13, ct10, ct11);
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
  ctx->HRot(ct15, ct14, ui.GetRotationKey(v3), v3);
  std::vector<double> v67(v30.begin() + 0 * 1024 + 0, v30.begin() + 0 * 1024 + 0 + 1024);
  Pt pt8;
  std::vector<Complex> pt8_complex(v67.begin(), v67.end());
  encoder.Encode(pt8, 0, ctx->param_.GetScale(0), pt8_complex);
  Ct ct16;
  ctx->Mult(ct16, ct, pt8);
  std::vector<double> v68(v34.begin() + 0 * 1024 + 0, v34.begin() + 0 * 1024 + 0 + 1024);
  Pt pt9;
  std::vector<Complex> pt9_complex(v68.begin(), v68.end());
  encoder.Encode(pt9, 0, ctx->param_.GetScale(0), pt9_complex);
  Ct ct17;
  ctx->Mult(ct17, ct2, pt9);
  std::vector<double> v69(v38.begin() + 0 * 1024 + 0, v38.begin() + 0 * 1024 + 0 + 1024);
  Pt pt10;
  std::vector<Complex> pt10_complex(v69.begin(), v69.end());
  encoder.Encode(pt10, 0, ctx->param_.GetScale(0), pt10_complex);
  Ct ct18;
  ctx->Mult(ct18, ct4, pt10);
  std::vector<double> v70(v42.begin() + 0 * 1024 + 0, v42.begin() + 0 * 1024 + 0 + 1024);
  Pt pt11;
  std::vector<Complex> pt11_complex(v70.begin(), v70.end());
  encoder.Encode(pt11, 0, ctx->param_.GetScale(0), pt11_complex);
  Ct ct19;
  ctx->Mult(ct19, ct6, pt11);
  Ct ct20;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct16.GetScale();
    double rhs_scale = ct17.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct20 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct20, ct16, ct17);
  Ct ct21;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct18.GetScale();
    double rhs_scale = ct19.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct21 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct21, ct18, ct19);
  Ct ct22;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct20.GetScale();
    double rhs_scale = ct21.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct22 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct22, ct20, ct21);
  Ct ct23;
  ctx->HRot(ct23, ct22, ui.GetRotationKey(v2), v2);
  std::vector<double> v71(v46.begin() + 0 * 1024 + 0, v46.begin() + 0 * 1024 + 0 + 1024);
  Pt pt12;
  std::vector<Complex> pt12_complex(v71.begin(), v71.end());
  encoder.Encode(pt12, 0, ctx->param_.GetScale(0), pt12_complex);
  Ct ct24;
  ctx->Mult(ct24, ct, pt12);
  std::vector<double> v72(v50.begin() + 0 * 1024 + 0, v50.begin() + 0 * 1024 + 0 + 1024);
  Pt pt13;
  std::vector<Complex> pt13_complex(v72.begin(), v72.end());
  encoder.Encode(pt13, 0, ctx->param_.GetScale(0), pt13_complex);
  Ct ct25;
  ctx->Mult(ct25, ct2, pt13);
  std::vector<double> v73(v54.begin() + 0 * 1024 + 0, v54.begin() + 0 * 1024 + 0 + 1024);
  Pt pt14;
  std::vector<Complex> pt14_complex(v73.begin(), v73.end());
  encoder.Encode(pt14, 0, ctx->param_.GetScale(0), pt14_complex);
  Ct ct26;
  ctx->Mult(ct26, ct4, pt14);
  std::vector<double> v74(v58.begin() + 0 * 1024 + 0, v58.begin() + 0 * 1024 + 0 + 1024);
  Pt pt15;
  std::vector<Complex> pt15_complex(v74.begin(), v74.end());
  encoder.Encode(pt15, 0, ctx->param_.GetScale(0), pt15_complex);
  Ct ct27;
  ctx->Mult(ct27, ct6, pt15);
  Ct ct28;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct24.GetScale();
    double rhs_scale = ct25.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct28 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct28, ct24, ct25);
  Ct ct29;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct26.GetScale();
    double rhs_scale = ct27.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct29 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct29, ct26, ct27);
  Ct ct30;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct28.GetScale();
    double rhs_scale = ct29.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct30 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct30, ct28, ct29);
  Ct ct31;
  ctx->HRot(ct31, ct30, ui.GetRotationKey(v1), v1);
  Ct ct32;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct1.GetScale();
    double rhs_scale = ct3.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct32 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct32, ct1, ct3);
  Ct ct33;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct5.GetScale();
    double rhs_scale = ct7.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct33 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct33, ct5, ct7);
  Ct ct34;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct32.GetScale();
    double rhs_scale = ct33.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct34 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct34, ct32, ct33);
  Ct ct35;
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct15.GetScale();
    double rhs_scale = ct23.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct35 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct35, ct15, ct23);
  std::vector<double> v75(v9.begin() + 0 * 1024 + 0, v9.begin() + 0 * 1024 + 0 + 1024);
  Pt pt16;
  std::vector<Complex> pt16_complex(v75.begin(), v75.end());
  encoder.Encode(pt16, 0, ctx->param_.GetScale(0) * ctx->param_.GetScale(0), pt16_complex);
  Ct ct36;
  pt16.SetScale(ct31.GetScale());
  ctx->Add(ct36, ct31, pt16);
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
  if (std::getenv("HEIR_CHEDDAR_DEBUG_SCALES")) {
    double lhs_scale = ct34.GetScale();
    double rhs_scale = ct37.GetScale();
    if (std::abs(lhs_scale - rhs_scale) >= 1e-12 * lhs_scale) {
      std::cerr << "[heir-cheddar] add ct38 scale mismatch lhs=" << lhs_scale << " rhs=" << rhs_scale << std::endl;
    }
  }
  ctx->Add(ct38, ct34, ct37);
  std::vector<Ct> v76;
  v76.resize(1);
  Ct ct39;
  ctx->Rescale(ct39, ct38);
  std::vector<Ct> v77;
  v77.resize(1);
  Ct ct39_c0;
  ctx->Copy(ct39_c0, ct39);
  v77[v7] = std::move(ct39_c0);
  return v77;
}

std::vector<Ct> matvec__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1) {
  int64_t v1 = 0;
  int32_t v2 = 16;
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
  encoder.Encode(pt, 0, ctx->param_.GetScale(0), pt_complex);
  Ct ct;
  ui.Encrypt(ct, pt);
  std::vector<Ct> v16;
  v16.reserve(1);
  Ct ct_c1;
  ctx->Copy(ct_c1, ct);
  v16.emplace_back(std::move(ct_c1));
  return v16;
}

std::vector<double> matvec__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1) {
  int64_t v1 = 0;
  int32_t v2 = 1024;
  int32_t v3 = 16;
  int32_t v4 = 1;
  int32_t v5 = 0;
  std::vector<double> v6(16, 0);
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
  static std::vector<word> main_primes = {36028797018652673ULL, 35184372121601ULL};
  static std::vector<word> aux_primes = {1152921504606994433ULL};
  static std::vector<std::pair<int, int>> level_config = []() {
    std::vector<std::pair<int, int>> lc;
    for (int i = 1; i <= static_cast<int>(main_primes.size()); ++i)
      lc.push_back({i, 0});
    return lc;
  }();
  static Param param(13, static_cast<double>(1ULL << 45), static_cast<int>(main_primes.size()) - 1, level_config, main_primes, aux_primes);
  auto ctx = Context<word>::Create(param);
  UI ui(ctx);
  ui.PrepareRotationKey(1, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(2, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(3, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(4, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(8, static_cast<int>(main_primes.size()) - 1);
  ui.PrepareRotationKey(12, static_cast<int>(main_primes.size()) - 1);
  return {ctx, std::move(ui)};
}

