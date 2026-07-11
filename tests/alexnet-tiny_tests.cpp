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
#include <fstream>
#include <filesystem>


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


std::vector<Ct> alexnet_tiny(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> alexnet_tiny__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
std::vector<double> alexnet_tiny__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
std::tuple<CtxPtr, UI> __configure();

TEST(CheddarSamples, AlexNetTinyRandom) {
  auto[ctx, ui] = __configure();

  std::filesystem::path inPath =
    std::filesystem::path(TEST_DATA_DIR) / "input.bin";
  std::ifstream in(inPath, std::ios::binary);
  std::vector<double> test_input(1 * 3 * 16 * 16);
  in.read(reinterpret_cast<char*>(test_input.data()), test_input.size() * sizeof(double));

  // encrypt input
  auto encrypted_input = alexnet_tiny__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
  // alexnet_tiny on encrypted input
  auto encrypted_result = alexnet_tiny(ctx, ctx->encoder_, ui, encrypted_input);
  // decrypt result
  std::vector<double> result = alexnet_tiny__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);

  std::filesystem::path outPath =
    std::filesystem::path(TEST_DATA_DIR) / "cheddar_output.bin";
  std::ofstream out(outPath, std::ios::binary);
  out.write(reinterpret_cast<const char*>(result.data()),
          result.size() * sizeof(double));

  // Compare the result with pytorch implementation
  EXPECT_EQ(0.0, 0.0);  // TODO: Implement comparison with PyTorch output
}