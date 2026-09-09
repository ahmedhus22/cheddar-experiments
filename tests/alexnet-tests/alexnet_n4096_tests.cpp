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


void alexnet_tiny(Context<word>* v1, const Encoder<word>& v2, const EvaluationKey<word>& v3, const EvkMap<word>& v4, 
                    const std::array<Ciphertext<word>, 1>& v5, std::array<Ciphertext<word>, 1>& v6);
void alexnet_tiny__encrypt__arg0(Context<word>* v1, const Encoder<word>& v2, const EvaluationKey<word>& v3, float* v4,
                                   UserInterface<word>* v5, std::array<Ciphertext<word>, 1>& v6);
void alexnet_tiny__decrypt__result0(Context<word>* v1, const Encoder<word>& v2, const EvaluationKey<word>& v3,
                                     const std::array<Ciphertext<word>, 1>& v4, UserInterface<word>* v5, float* v6);
void alexnet_tiny__setup(std::shared_ptr<Context<word>>& v1);
void alexnet_tiny__keygen(const std::shared_ptr<Context<word>>& v1, std::unique_ptr<UserInterface<word>>& v2);
void alexnet_tiny__configure(std::shared_ptr<Context<word>>& v1, std::unique_ptr<UserInterface<word>>& v2);

void run_alexnet(std::vector<double> &test_input, std::vector<float> &result, std::vector<double> &torch_output) {
  std::shared_ptr<cheddar::Context<word>> ctx;
  std::unique_ptr<UI> ui;
  alexnet_tiny__configure(ctx, ui);

  ASSERT_NE(ctx, nullptr);
  ASSERT_NE(ui, nullptr);

  const Evk& evk = ui->GetMultiplicationKey();
  const EvkMapT& evk_map = ui->GetEvkMap();

  std::filesystem::path inPath =
    std::filesystem::path(TEST_DATA_DIR) / "input.bin";
  std::ifstream in(inPath, std::ios::binary);
  in.read(reinterpret_cast<char*>(test_input.data()), test_input.size() * sizeof(double));
  std::vector<float> test_input_float(test_input.begin(), test_input.end());

  // encrypt input
  std::array<Ct, 1> encrypted_input;
  alexnet_tiny__encrypt__arg0(ctx.get(), ctx->encoder_, evk, &test_input_float[0], ui.get(),
                       encrypted_input);
  // alexnet_tiny on encrypted input
   std::array<Ciphertext<word>, 1> encrypted_result;
  alexnet_tiny(ctx.get(), ctx->encoder_, evk, evk_map, encrypted_input, encrypted_result);
  // decrypt result
  alexnet_tiny__decrypt__result0(ctx.get(), ctx->encoder_, evk, encrypted_result, ui.get(),
                          &result[0]);

  std::filesystem::path torchPath =
    std::filesystem::path(TEST_DATA_DIR) / "torch_output.bin";
  std::ifstream torch_in(torchPath, std::ios::binary);
  torch_in.read(reinterpret_cast<char*>(torch_output.data()), torch_output.size() * sizeof(double));
}

std::vector<double> test_input(1 * 3 * 16 * 16);
std::vector<float> result(1 * 10);
std::vector<double> torch_output(1 * 10);

TEST(AlexnetTiny4096, OutputMatchesTorch) {
  run_alexnet(test_input, result, torch_output);
  // Compare the result with pytorch implementation
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], torch_output[i], 1e-3);
    std::cout << "result[" << i << "] = " << result[i] << ", torch_output[" << i << "] = " << torch_output[i] << std::endl;
  }
}

TEST(AlexnetTiny4096, OutputShape) {
  EXPECT_EQ(result.size(), 10);
  EXPECT_EQ(result.size(), torch_output.size());
}

TEST(AlexnetTiny4096, FiniteandNonZero) {
  bool has_nonzero = false;
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_TRUE(std::isfinite(result[i])) << "result[" << i << "] is not finite";
    if (result[i] != 0.0) {
      has_nonzero = true;
    }
  }
  EXPECT_TRUE(has_nonzero) << "All elements in the result are zero";
}

TEST(AlexnetTiny4096, MaxAbsoluteError) {
  double max_abs_error = 0.0;
  for (size_t i = 0; i < result.size(); ++i) {
    double abs_error = std::abs(result[i] - torch_output[i]);
    if (abs_error > max_abs_error) {
      max_abs_error = abs_error;
    }
  }
  std::cout << "Max absolute error: " << max_abs_error << std::endl;
  EXPECT_LT(max_abs_error, 1e-3) << "Max absolute error is too large: " << max_abs_error;
}

TEST(AlexnetTiny4096, MaxRelativeError) {
  double max_rel_error = 0.0;
  for (size_t i = 0; i < result.size(); ++i) {
    double rel_error = std::abs(result[i] - torch_output[i]) / (std::abs(torch_output[i]) + 1e-12);
    if (rel_error > max_rel_error) {
      max_rel_error = rel_error;
    }
  }
  std::cout << "Max relative error: " << max_rel_error << std::endl;
  EXPECT_LT(max_rel_error, 1e-3) << "Max relative error is too large: " << max_rel_error;
}

TEST(AlexnetTiny4096, ArgmaxMatch) {
  size_t argmax_result = std::distance(result.begin(), std::max_element(result.begin(), result.end()));
  size_t argmax_torch = std::distance(torch_output.begin(), std::max_element(torch_output.begin(), torch_output.end()));
  std::cout << "Argmax index: " << argmax_result << std::endl;
  EXPECT_EQ(argmax_result, argmax_torch) << "Argmax indices do not match: result argmax = " << argmax_result << ", torch argmax = " << argmax_torch;
}