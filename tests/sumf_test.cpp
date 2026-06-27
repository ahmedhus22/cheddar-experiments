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

// sumf.cpp function declarations
std::vector<Ct> simple_sum(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> simple_sum__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
double simple_sum__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
std::tuple<CtxPtr, UI> __configure();

TEST(CheddarSamples, SimpleSum) {
  auto[ctx, ui] = __configure();
  //Enc encoder;

  std::vector<double> test_input(32,1.0); // All ones for easy verification
  // encrypt input
  auto encrypted_input = simple_sum__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
  // simple_sum on encrypted input
  auto encrypted_result = simple_sum(ctx, ctx->encoder_, ui, encrypted_input);
  // decrypt result
  double result = simple_sum__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);

  EXPECT_DOUBLE_EQ(result, 32.0);
}


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
