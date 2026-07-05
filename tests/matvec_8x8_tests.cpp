#include <gtest/gtest.h>


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

// matvec function declarations
std::vector<Ct> matvec_identity(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> matvec_identity__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
std::vector<double> matvec_identity__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
std::tuple<CtxPtr, UI> __configure();

TEST(MatVec8x8, MVIdentity) {
  auto[ctx, ui] = __configure();
  std::vector<double> test_input(8,1.0); // All ones for easy verification
  // encrypt input
  auto encrypted_input = matvec_identity__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
  // matvec_identity on encrypted input
  auto encrypted_result = matvec_identity(ctx, ctx->encoder_, ui, encrypted_input);
  // decrypt result
  auto result = matvec_identity__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);

  for (auto &val : result) {
    EXPECT_NEAR(val, 1.0, 1e-6);
  }
  EXPECT_EQ(result.size(), 8);
}
