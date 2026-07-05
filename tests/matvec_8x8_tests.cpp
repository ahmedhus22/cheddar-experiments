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
  std::vector<double> test_input={0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  // encrypt input
  auto encrypted_input = matvec_identity__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
  // matvec_identity on encrypted input
  auto encrypted_result = matvec_identity(ctx, ctx->encoder_, ui, encrypted_input);
  // decrypt result
  auto result = matvec_identity__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);

  for (int i=0; i<result.size(); ++i) {
    EXPECT_NEAR(result[i], test_input[i], 1e-4);
  }
  EXPECT_EQ(result.size(), 8);
}

std::vector<Ct> matvec_shift(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> matvec_shift__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
std::vector<double> matvec_shift__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
TEST(MatVec8x8, MVShift) {
  auto[ctx, ui] = __configure();
  std::vector<double> test_input={0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  // encrypt input
  auto encrypted_input = matvec_shift__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
  // matvec_shift on encrypted input
  auto encrypted_result = matvec_shift(ctx, ctx->encoder_, ui, encrypted_input);
  // decrypt result
  auto result = matvec_shift__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);
  std::vector<double> shifted_input={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 0.0};

  for (int i=0; i<result.size(); ++i) {
    EXPECT_NEAR(result[i], shifted_input[i], 1e-4);
  }
  EXPECT_EQ(result.size(), 8);
}


std::vector<Ct> matvec_random(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> matvec_random__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
std::vector<double> matvec_random__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
TEST(MatVec8x8, MVRandom) {
  auto[ctx, ui] = __configure();
  std::vector<double> test_input={0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  // encrypt input
  auto encrypted_input = matvec_random__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
  // matvec_random on encrypted input
  auto encrypted_result = matvec_random(ctx, ctx->encoder_, ui, encrypted_input);
  // decrypt result
  auto result = matvec_random__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);
  /*
  np.random.seed(42)
  A = np.random.uniform(0.1, 2.0, (8, 8))
  v = np.arange(8, dtype=np.float64)
  result = A @ v

  array([25.65027305, 22.60791536, 21.27676958, 22.1193428 , 29.77738353,
       27.78573931, 45.97194101, 24.92280407])
  */
  auto test_result = std::vector<double>{25.65027305, 22.60791536, 21.27676958, 22.1193428 , 29.77738353, 27.78573931, 45.97194101, 24.92280407};
  for (int i=0; i<result.size(); ++i) {
    EXPECT_NEAR(result[i], test_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), 8);
}

std::vector<Ct> matvec_chain(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> matvec_chain__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
std::vector<double> matvec_chain__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
TEST(MatVec8x8, MVChain) {
  auto[ctx, ui] = __configure();
  std::vector<double> test_input={0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  // encrypt input
  auto encrypted_input = matvec_chain__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
  // matvec_chain on encrypted input
  auto encrypted_result = matvec_chain(ctx, ctx->encoder_, ui, encrypted_input);
  // decrypt result
  auto result = matvec_chain__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);
  /*
  np.random.seed(123)
  A = np.round(np.random.uniform(0.5, 1.5, (8,8)), 2)
  B = np.round(np.random.uniform(0.5, 1.5, (8,8)), 2)
  v = np.arange(8, dtype=np.float64)
  result = A @ (B @ v)
  
  array([238.2074, 212.3246, 229.2286, 195.2657, 233.5022, 223.2958,
       218.342 , 249.8862])
  */
  auto test_result = std::vector<double>{238.2074, 212.3246, 229.2286, 195.2657, 233.5022, 223.2958, 218.342 , 249.8862};
  for (int i=0; i<result.size(); ++i) {
    EXPECT_NEAR(result[i], test_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), 8);
}
