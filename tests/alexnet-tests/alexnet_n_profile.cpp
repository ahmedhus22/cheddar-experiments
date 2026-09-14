#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <memory>
#include <numeric>
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


// void alexnet_tiny__setup(std::shared_ptr<cheddar::Context<word>>& v1) {
//   static cheddar::Parameter<word> cheddar_param(15, static_cast<double>(static_cast<word>(1) << 45), 7, std::vector<std::pair<int, int>>{{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}}, std::vector<word>{36028797017456641ULL, 35184376545281ULL, 35184367828993ULL, 35184373989377ULL, 35184368025601ULL, 35184373006337ULL, 35184368877569ULL, 35184372744193ULL}, std::vector<word>{1152921504608747521ULL, 1152921504614055937ULL, 1152921504615628801ULL});
//   v1 = cheddar::Context<word>::Create(cheddar_param);
//   return;
// }
// void alexnet_tiny__keygen(const std::shared_ptr<cheddar::Context<word>>& v1, std::unique_ptr<cheddar::UserInterface<word>>& v2) {
//   v2 = std::make_unique<cheddar::UserInterface<word>>(v1);
//   v2->PrepareRotationKey(1, 7);
//   v2->PrepareRotationKey(8, 7);
//   v2->PrepareRotationKey(16, 7);
//   v2->PrepareRotationKey(22, 7);
//   v2->PrepareRotationKey(32, 7);
//   v2->PrepareRotationKey(64, 7);
//   v2->PrepareRotationKey(128, 7);
//   v2->PrepareRotationKey(256, 7);
//   v2->PrepareRotationKey(512, 7);
//   return;
// }
// void alexnet_tiny__configure(std::shared_ptr<cheddar::Context<word>>& v1, std::unique_ptr<cheddar::UserInterface<word>>& v2) {
//   bool v3 = true;
//   std::shared_ptr<cheddar::Context<word>> v4;
//   alexnet_tiny__setup(v4);
//   alexnet_tiny__keygen(v4, v2);
//   v1 = v4;
//   if (v3) {
//     v4 = std::shared_ptr<cheddar::Context<word>>();
//   }
//   return;
// }

TimingStats context_generation;
TimingStats key_generation;
TimingStats eval_key_generation;
TimingStats configuration;
int kwarmups = 1;
int kiterations = 3;
double configuration_warmup_ms = 0.0;

TEST(AlexnetTinyProfile, Configuration) {
  nvtxRangePushA("Configuration Warmup");
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
    std::cerr
          << "Warmup iteration " << (i + 1)
          << " configuration: "
          << configuration_warmup_ms
          << " ms\n";
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

TimingStats encryption_stats;
TimingStats preprocessing_stats;
TimingStats evaluation_stats;
TimingStats decryption_stats;
TimingStats online_total_stats;

TEST(AlexnetTinyProfile, Inference) {
  std::shared_ptr<cheddar::Context<word>> ctx;
  std::unique_ptr<UI> ui;
  alexnet_tiny__configure(ctx, ui);

  ASSERT_NE(ctx, nullptr);
  ASSERT_NE(ui, nullptr);

  const Evk& evk = ui->GetMultiplicationKey();
  const EvkMap& evk_map = ui->GetEvkMap();

  std::vector<double> test_input(1 * 3 * 16 * 16);

  std::filesystem::path inPath =
    std::filesystem::path(TEST_DATA_DIR) / "input.bin";
  std::ifstream in(inPath, std::ios::binary);
  in.read(reinterpret_cast<char*>(test_input.data()), test_input.size() * sizeof(double));
  std::vector<float> test_input_float(test_input.begin(), test_input.end());

  auto run_iteration = [&](bool record) -> double {
    std::array<Ct, 1> encrypted;
    std::array<Pt, 4> plaintexts;
    std::array<std::shared_ptr<LinearTransform>, 4> transforms;
    std::array<Ct, 1> evaluated;

    float result[10];

    double encryption_ms = 0.0;
    double preprocessing_ms = 0.0;
    double evaluation_ms = 0.0;
    double decryption_ms = 0.0;


    // ------------------------------------------------------------
    // Encryption
    // ------------------------------------------------------------

    nvtxRangePushA("Encryption");
    sync_cuda();
    auto start = Clock::now();
    alexnet_tiny__encrypt__arg0(
      ctx.get(),
      ctx->encoder_,
      evk,
      test_input_float.data(),
      ui.get(),
      encrypted
    );

    sync_cuda();
    auto end = Clock::now();
    encryption_ms = elapsed_ms(start, end);
    nvtxRangePop();


    // ------------------------------------------------------------
    // Plaintext preprocessing
    // ------------------------------------------------------------
    nvtxRangePushA("Plaintext Preprocessing");
    sync_cuda();
    start = Clock::now();
    alexnet_tiny__preprocessing(
      ctx.get(),
      ctx->encoder_,
      transforms,
      plaintexts
    );

    sync_cuda();
    end = Clock::now();
    preprocessing_ms = elapsed_ms(start, end);
    nvtxRangePop();

    // ASSERT_NE(transforms[0], nullptr);
    // ASSERT_NE(transforms[1], nullptr);

    // ------------------------------------------------------------
    // Encrypted computation
    // ------------------------------------------------------------
    nvtxRangePushA("Encrypted Computation");
    sync_cuda();
    start = Clock::now();
    alexnet_tiny__preprocessed(
      ctx.get(),
      ctx->encoder_,
      evk,
      evk_map,
      encrypted,
      transforms,
      plaintexts,
      evaluated
    );

    sync_cuda();
    end = Clock::now();
    evaluation_ms = elapsed_ms(start, end);
    nvtxRangePop();


    // ------------------------------------------------------------
    // Decryption
    // ------------------------------------------------------------
    nvtxRangePushA("Decryption");
    sync_cuda();
    start = Clock::now();
    alexnet_tiny__decrypt__result0(
      ctx.get(),
      ctx->encoder_,
      evk,
      evaluated,
      ui.get(),
      result
    );
    sync_cuda();
    end = Clock::now();
    decryption_ms = elapsed_ms(start, end);
    nvtxRangePop();


    // ------------------------------------------------------------
    // Online total
    // ------------------------------------------------------------
    double online_ms =
      encryption_ms +
      preprocessing_ms +
      evaluation_ms +
      decryption_ms;


    if (record) {
      encryption_stats.add(encryption_ms);
      preprocessing_stats.add(preprocessing_ms);
      evaluation_stats.add(evaluation_ms);
      decryption_stats.add(decryption_ms);
      online_total_stats.add(online_ms);
    } else {
      std::filesystem::path torchPath =
      std::filesystem::path(TEST_DATA_DIR) / "torch_output.bin";
      std::ifstream torch_in(torchPath, std::ios::binary);
      std::vector<double> torch_output(1 * 10);
      torch_in.read(reinterpret_cast<char*>(torch_output.data()), torch_output.size() * sizeof(double));
      for (size_t i = 0; i < 10; ++i) {
        EXPECT_NEAR(result[i], torch_output[i], 1e-3);
        std::cout << "result[" << i << "] = " << result[i] << ", torch_output[" << i << "] = " << torch_output[i] << std::endl;
      }
    }
    return online_ms;
  };

  // ------------------------------------------------------------
  // Warmup
  // ------------------------------------------------------------
  std::cerr << "Running warmup...\n";
  for (int i = 0; i < kwarmups; ++i) {
      double online_ms = run_iteration(false);
      std::cerr
          << "Warmup iteration " << (i + 1)
          << " online total: "
          << online_ms
          << " ms\n";
  }

  // ------------------------------------------------------------
  // Measured repetitions
  // ------------------------------------------------------------
  std::cerr << "Running measured repetitions...\n";
  for (int i = 0; i < kiterations; ++i) {
      double online_ms = run_iteration(true);
      std::cerr
          << "Iteration " << (i + 1)
          << " online total: "
          << online_ms
          << " ms\n";
  }

}


TEST(AlexnetTinyProfile, Report) {
  auto print_stats = [](const char* name,
                      const TimingStats& stats) {

    std::cout << std::fixed << std::setprecision(3);

    std::cout << "\n" << name << "\n";
    std::cout << "  samples: ";

    for (double x : stats.samples) {
        std::cout << x << " ms ";
    }

    std::cout << "\n";
    std::cout << "  median: " << stats.median() << " ms\n";
    std::cout << "  min:    " << stats.min() << " ms\n";
    std::cout << "  max:    " << stats.max() << " ms\n";
    std::cout << "  stddev: " << stats.stddev() << " ms\n";
  };

  ASSERT_EQ(context_generation.samples.size(), kiterations);
  ASSERT_EQ(key_generation.samples.size(), kiterations);
  ASSERT_EQ(eval_key_generation.samples.size(), kiterations);
  ASSERT_EQ(configuration.samples.size(), kiterations);
  ASSERT_EQ(encryption_stats.samples.size(), kiterations);
  ASSERT_EQ(preprocessing_stats.samples.size(), kiterations);
  ASSERT_EQ(evaluation_stats.samples.size(), kiterations);
  ASSERT_EQ(decryption_stats.samples.size(), kiterations);
  ASSERT_EQ(online_total_stats.samples.size(), kiterations);

  print_stats("Context Generation", context_generation);
  print_stats("Key Generation", key_generation);
  print_stats("Evaluation Key Generation", eval_key_generation);
  print_stats("Configuration", configuration);
  print_stats("Encryption", encryption_stats);
  print_stats("Plaintext preprocessing", preprocessing_stats);
  print_stats("Encrypted computation", evaluation_stats);
  print_stats("Decryption", decryption_stats);
  print_stats("Online total", online_total_stats);
}