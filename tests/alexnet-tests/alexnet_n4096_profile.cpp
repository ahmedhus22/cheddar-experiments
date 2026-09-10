#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "UserInterface.h"
#include "core/Context.h"
#include "core/Encode.h"
#include "extension/LinearTransform.h"
                             
#include <cuda_runtime.h>
#include <nvtx3/nvToolsExt.h>

using word = uint64_t;
using Ct = cheddar::Ciphertext<word>;
using Evk = cheddar::EvaluationKey<word>;
using EvkMap = cheddar::EvkMap<word>;
using LinearTransform = cheddar::LinearTransform<word>;
using Pt = cheddar::Plaintext<word>;
using UI = cheddar::UserInterface<word>;

using Clock = std::chrono::steady_clock;

struct TimingStats {
  std::vector<double> samples;

  void add(double ms) {
    samples.push_back(ms);
  }

  double median() const {
    auto x = samples;
    std::sort(x.begin(), x.end());

    if (x.size() % 2 == 0) {
      return (x[x.size()/2 - 1] + x[x.size()/2]) / 2.0;
    }

    return x[x.size()/2];
  }

  double min() const {
    return *std::min_element(samples.begin(), samples.end());
  }

  double max() const {
    return *std::max_element(samples.begin(), samples.end());
  }

  double mean() const {
    return std::accumulate(samples.begin(), samples.end(), 0.0)
              / samples.size();
  }

  double stddev() const {
    const double m = mean();

    double sum = 0.0;
    for (double x : samples) {
      double d = x - m;
      sum += d * d;
    }

    // Population standard deviation.
    return std::sqrt(sum / samples.size());
  }
};

static double elapsed_ms(Clock::time_point start,
                         Clock::time_point end) {
  return std::chrono::duration<double, std::milli>(end - start).count();
}

static void sync_cuda() {
  cudaError_t err = cudaDeviceSynchronize();

  if (err != cudaSuccess) {
    std::cerr << "cudaDeviceSynchronize failed: "
              << cudaGetErrorString(err) << "\n";
    std::abort();
  }
}


// void alexnet_tiny__configure(std::shared_ptr<cheddar::Context<word>>& ctx,
//                       std::unique_ptr<UI>& ui);
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


void alexnet_tiny__setup(std::shared_ptr<cheddar::Context<word>>& v1) {
  static cheddar::Parameter<word> cheddar_param(15, static_cast<double>(static_cast<word>(1) << 45), 7, std::vector<std::pair<int, int>>{{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}}, std::vector<word>{36028797017456641ULL, 35184376545281ULL, 35184367828993ULL, 35184373989377ULL, 35184368025601ULL, 35184373006337ULL, 35184368877569ULL, 35184372744193ULL}, std::vector<word>{1152921504608747521ULL, 1152921504614055937ULL, 1152921504615628801ULL});
  v1 = cheddar::Context<word>::Create(cheddar_param);
  return;
}
void alexnet_tiny__keygen(const std::shared_ptr<cheddar::Context<word>>& v1, std::unique_ptr<cheddar::UserInterface<word>>& v2) {
  v2 = std::make_unique<cheddar::UserInterface<word>>(v1);
  v2->PrepareRotationKey(1, 7);
  v2->PrepareRotationKey(8, 7);
  v2->PrepareRotationKey(16, 7);
  v2->PrepareRotationKey(22, 7);
  v2->PrepareRotationKey(32, 7);
  v2->PrepareRotationKey(64, 7);
  v2->PrepareRotationKey(128, 7);
  v2->PrepareRotationKey(256, 7);
  v2->PrepareRotationKey(512, 7);
  return;
}
void alexnet_tiny__configure(std::shared_ptr<cheddar::Context<word>>& v1, std::unique_ptr<cheddar::UserInterface<word>>& v2) {
  bool v3 = true;
  std::shared_ptr<cheddar::Context<word>> v4;
  alexnet_tiny__setup(v4);
  alexnet_tiny__keygen(v4, v2);
  v1 = v4;
  if (v3) {
    v4 = std::shared_ptr<cheddar::Context<word>>();
  }
  return;
}

TimingStats context_generation;
TimingStats key_generation;
TimingStats eval_key_generation;
TimingStats configuration;
int kwarmups = 1;
int kiterations = 3;

TEST(AlexnetTiny4096Profile, Configuration) {
  nvtxRangePushA("Configuration Warmup");
  double configuration_warmup_ms = 0.0;
  for (int i=0; i < kwarmups; ++i) {
    sync_cuda();
    auto warmup_start = Clock::now();
    std::shared_ptr<cheddar::Context<word>> ctx;
    std::unique_ptr<UI> ui;
    alexnet_tiny__configure(ctx, ui);
    sync_cuda();
    auto warmup_end = Clock::now();
    configuration_warmup_ms =
        elapsed_ms(warmup_start, warmup_end);
    ASSERT_NE(ctx, nullptr);
    ASSERT_NE(ui, nullptr);
  }
  nvtxRangePop(); // Configuration Warmup

  for (int i=0; i < kiterations; ++i) {
    nvtxRangePushA("Configuration");
    auto config_start = Clock::now();

    nvtxRangePushA("Crypto Context Generation");
    sync_cuda();
    auto ctx_start = Clock::now();
    std::shared_ptr<cheddar::Context<word>> ctx;
    static cheddar::Parameter<word> cheddar_param(15, 
      static_cast<double>(static_cast<word>(1) << 45), 
      7, 
      std::vector<std::pair<int, int>>{{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}}, 
      std::vector<word>{36028797017456641ULL, 35184376545281ULL, 35184367828993ULL, 35184373989377ULL, 
        35184368025601ULL, 35184373006337ULL, 35184368877569ULL, 35184372744193ULL}, 
      std::vector<word>{1152921504608747521ULL, 1152921504614055937ULL, 1152921504615628801ULL});
    ctx = cheddar::Context<word>::Create(cheddar_param);
    sync_cuda();
    auto ctx_end = Clock::now();
    context_generation.add(elapsed_ms(ctx_start, ctx_end));
    nvtxRangePop(); // Crypto Context Generation

    nvtxRangePushA("Key Generation");
    std::unique_ptr<UI> ui;
    auto key_start = Clock::now();
    ui = std::make_unique<UI>(ctx);
    sync_cuda();
    auto key_end = Clock::now();
    key_generation.add(elapsed_ms(key_start, key_end));
    nvtxRangePop(); // Key Generation

    nvtxRangePushA("Evaluation Key Generation");
    auto evk_start = Clock::now();
    ui->PrepareRotationKey(1, 7);
    ui->PrepareRotationKey(8, 7);
    ui->PrepareRotationKey(16, 7);
    ui->PrepareRotationKey(22, 7);
    ui->PrepareRotationKey(32, 7);
    ui->PrepareRotationKey(64, 7);
    ui->PrepareRotationKey(128, 7);
    ui->PrepareRotationKey(256, 7);
    ui->PrepareRotationKey(512, 7);
    sync_cuda();
    auto evk_end = Clock::now();
    eval_key_generation.add(elapsed_ms(evk_start, evk_end));
    nvtxRangePop(); // Evaluation Key Generation

    auto config_end = Clock::now();
    configuration.add(elapsed_ms(config_start, config_end));
    nvtxRangePop(); // Configuration
  }
}

// int main(int argc, char** argv) {
//   std::shared_ptr<cheddar::Context<word>> ctx;
//   std::unique_ptr<UI> ui;
//   alexnet_tiny__configure(ctx, ui);
//   ASSERT_NE(ctx, nullptr);
//   ASSERT_NE(ui, nullptr);
//   const Evk& evk = ui->GetMultiplicationKey();
//   const EvkMap& evk_map = ui->GetEvkMap();
  
//   std::vector<float> test_input(1 * 3 * 16 * 16);
//   std::generate(test_input.begin(), test_input.end(), 
//     []() { return static_cast<float>(rand()) / RAND_MAX; });


//   std::array<Ct, 1> encrypted;
//   alexnet_tiny__encrypt__arg0(ctx.get(), ctx->encoder_, evk, &test_input[0], ui.get(),
//                        encrypted);

//   std::array<Pt, 4> plaintexts;
//   std::array<std::shared_ptr<LinearTransform>, 4> transforms;
//   auto preprocessing_start = std::chrono::steady_clock::now();
//   alexnet_tiny__preprocessing(ctx.get(), ctx->encoder_,  transforms, plaintexts);
//   std::cerr << "HeirMLP preprocessing took "
//             << std::chrono::duration<double>(std::chrono::steady_clock::now() -
//                                              preprocessing_start)
//                    .count()
//             << " seconds\n";
//   ASSERT_NE(transforms[0], nullptr);
//   ASSERT_NE(transforms[1], nullptr);

//   std::array<Ct, 1> evaluated;
//   auto evaluation_start = std::chrono::steady_clock::now();
//   alexnet_tiny__preprocessed(ctx.get(), ctx->encoder_,  evk, evk_map,
//                       encrypted,
//                       transforms, plaintexts, evaluated);
//   std::cerr << "HeirMLP evaluation took "
//             << std::chrono::duration<double>(std::chrono::steady_clock::now() -
//                                              evaluation_start)
//                    .count()
//             << " seconds\n";
//   EXPECT_EQ(ctx->param_.NPToLevel(encrypted[0].GetNP()), 6);
//   EXPECT_EQ(ctx->param_.NPToLevel(evaluated[0].GetNP()), 0);

//   std::array<Ct, 1> evaluated_again;
//   alexnet_tiny__preprocessed(ctx.get(), ctx->encoder_,  evk, evk_map,
//                       encrypted,
//                       transforms, plaintexts, evaluated_again);

//   float result[10];
//   alexnet_tiny__decrypt__result0(ctx.get(), ctx->encoder_, evk, evaluated, ui.get(),
//                           &result[0]);
  
// }