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


void alexnet_tiny(Context<word>* v1, const Encoder<word>& v2, UserInterface<word>* v3, const EvaluationKey<word>& v4, const std::array<Ciphertext<word>, 1>& v5, std::array<Ciphertext<word>, 1>& v6);
void alexnet_tiny__encrypt__arg0(Context<word>* v1, const Encoder<word>& v2, UserInterface<word>* v3, const EvaluationKey<word>& v4, float v5[1][3][16][16], UserInterface<word>* v6, std::array<Ciphertext<word>, 1>& v7);
void alexnet_tiny__decrypt__result0(Context<word>* v1, const Encoder<word>& v2, UserInterface<word>* v3, const EvaluationKey<word>& v4, const std::array<Ciphertext<word>, 1>& v5, UserInterface<word>* v6, float* v7);
void alexnet_tiny__configure(std::shared_ptr<Context<word>>& v1, std::unique_ptr<UserInterface<word>>& v2);

TEST(AlexnetTiny, AlexNetN4096) {
  std::shared_ptr<Context<word>> ctx;
  std::unique_ptr<UserInterface<word>> ui;
  alexnet_tiny__configure(ctx, ui);
  const Evk& evk = ui->GetMultiplicationKey();

  std::filesystem::path inPath =
    std::filesystem::path(TEST_DATA_DIR) / "input.bin";
  std::ifstream in(inPath, std::ios::binary);
  std::vector<double> test_input(1 * 3 * 16 * 16);
  in.read(reinterpret_cast<char*>(test_input.data()), test_input.size() * sizeof(double));
  std::vector<float> test_input_float(test_input.begin(), test_input.end());
  float (*input_shaped)[3][16][16] =
    reinterpret_cast<float (*)[3][16][16]>(test_input_float.data());

  // encrypt input
  std::array<Ciphertext<word>, 1> encrypted_input;
  alexnet_tiny__encrypt__arg0(ctx.get(), ctx->encoder_, ui.get(), evk, input_shaped, ui.get(), encrypted_input);
  std::cout << "Encrypted input size: " << encrypted_input.size() << std::endl;
  // alexnet_tiny on encrypted input
  std::array<Ciphertext<word>, 1> encrypted_result;
  alexnet_tiny(ctx.get(), ctx->encoder_, ui.get(), evk, encrypted_input, encrypted_result);
  // decrypt result
  std::vector<float> result(1 * 10);
  alexnet_tiny__decrypt__result0(ctx.get(), ctx->encoder_, ui.get(), evk, encrypted_result, ui.get(), result.data());

  std::cout << "Decrypted result size: " << result.size() << std::endl;
  std::filesystem::path torchPath =
    std::filesystem::path(TEST_DATA_DIR) / "torch_output.bin";
  std::ifstream torch_in(torchPath, std::ios::binary);
  std::vector<double> torch_output(1 * 10);
  torch_in.read(reinterpret_cast<char*>(torch_output.data()), torch_output.size() * sizeof(double));

  // Compare the result with pytorch implementation
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], torch_output[i], 1e-6);
  }
  EXPECT_EQ(result.size(), torch_output.size());
}