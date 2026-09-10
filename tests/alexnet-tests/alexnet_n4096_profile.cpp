#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "UserInterface.h"
#include "core/Context.h"
#include "core/Encode.h"
#include "extension/LinearTransform.h"

using word = uint64_t;
using Ct = cheddar::Ciphertext<word>;
using Evk = cheddar::EvaluationKey<word>;
using EvkMap = cheddar::EvkMap<word>;
using LinearTransform = cheddar::LinearTransform<word>;
using Pt = cheddar::Plaintext<word>;
using UI = cheddar::UserInterface<word>;


void alexnet_tiny__configure(std::shared_ptr<cheddar::Context<word>>& ctx,
                      std::unique_ptr<UI>& ui);
void alexnet_tiny__encrypt__arg0(cheddar::Context<word>* ctx,
                          const cheddar::Encoder<word>& encoder, const Evk& evk,
                          float* input, UI* ui, std::array<Ct, 1>& out);
void alexnet_tiny__preprocessing(cheddar::Context<word>* ctx, const cheddar::Encoder<word>& encoder, 
  std::array<std::shared_ptr<cheddar::LinearTransform<word>>, 4>& transforms, std::array<cheddar::Plaintext<word>, 4>& plaintexts);
void alexnet_tiny__preprocessed(cheddar::Context<word>* ctx, const cheddar::Encoder<word>& encoder, 
                          const Evk& evk, const EvkMap& evk_map, const std::array<cheddar::Ciphertext<word>, 1>& input,
                          const std::array<std::shared_ptr<cheddar::LinearTransform<word>>, 4>& transforms,
                          const std::array<cheddar::Plaintext<word>, 4>& plaintexts, std::array<cheddar::Ciphertext<word>, 1>& output);
void alexnet_tiny__decrypt__result0(cheddar::Context<word>* ctx,
                             const cheddar::Encoder<word>& encoder,
                             const Evk& evk, const std::array<Ct, 1>& input,
                             UI* ui, float* out);

#include <nvtx3/nvToolsExt.h>

int main(int argc, char** argv) {
  std::shared_ptr<cheddar::Context<word>> ctx;
  std::unique_ptr<UI> ui;
  alexnet_tiny__configure(ctx, ui);
  ASSERT_NE(ctx, nullptr);
  ASSERT_NE(ui, nullptr);
  const Evk& evk = ui->GetMultiplicationKey();
  const EvkMap& evk_map = ui->GetEvkMap();
  
  std::vector<float> test_input(1 * 3 * 16 * 16);
  std::generate(test_input.begin(), test_input.end(), 
    []() { return static_cast<float>(rand()) / RAND_MAX; });


  std::array<Ct, 1> encrypted;
  alexnet_tiny__encrypt__arg0(ctx.get(), ctx->encoder_, evk, &test_input[0], ui.get(),
                       encrypted);

  std::array<Pt, 4> plaintexts;
  std::array<std::shared_ptr<LinearTransform>, 4> transforms;
  auto preprocessing_start = std::chrono::steady_clock::now();
  alexnet_tiny__preprocessing(ctx.get(), ctx->encoder_,  transforms, plaintexts);
  std::cerr << "HeirMLP preprocessing took "
            << std::chrono::duration<double>(std::chrono::steady_clock::now() -
                                             preprocessing_start)
                   .count()
            << " seconds\n";
  ASSERT_NE(transforms[0], nullptr);
  ASSERT_NE(transforms[1], nullptr);

  std::array<Ct, 1> evaluated;
  auto evaluation_start = std::chrono::steady_clock::now();
  alexnet_tiny__preprocessed(ctx.get(), ctx->encoder_,  evk, evk_map,
                      encrypted,
                      transforms, plaintexts, evaluated);
  std::cerr << "HeirMLP evaluation took "
            << std::chrono::duration<double>(std::chrono::steady_clock::now() -
                                             evaluation_start)
                   .count()
            << " seconds\n";
  EXPECT_EQ(ctx->param_.NPToLevel(encrypted[0].GetNP()), 6);
  EXPECT_EQ(ctx->param_.NPToLevel(evaluated[0].GetNP()), 0);

  std::array<Ct, 1> evaluated_again;
  alexnet_tiny__preprocessed(ctx.get(), ctx->encoder_,  evk, evk_map,
                      encrypted,
                      transforms, plaintexts, evaluated_again);

  float actual[1][10];
  alexnet_tiny__decrypt__result0(ctx.get(), ctx->encoder_, evk, evaluated, ui.get(),
                          &actual[0][0]);
  int predicted_class = 0;
  for (size_t i = 0; i < 10; ++i) {
    ASSERT_TRUE(std::isfinite(actual[0][i])) << "logit " << i;
    EXPECT_NEAR(actual[0][i], kExpected[i], kTolerance) << "logit " << i;
    if (actual[0][i] > actual[0][predicted_class]) predicted_class = i;
  }
  EXPECT_EQ(predicted_class, kExpectedClass);

  float repeated[1][10];
  alexnet_tiny__decrypt__result0(ctx.get(), ctx->encoder_, evk, evaluated_again,
                          ui.get(), &repeated[0][0]);
  for (size_t i = 0; i < 10; ++i) {
    ASSERT_TRUE(std::isfinite(repeated[0][i])) << "repeated logit " << i;
    EXPECT_NEAR(repeated[0][i], actual[0][i], kTolerance)
        << "repeated logit " << i;
  }
}