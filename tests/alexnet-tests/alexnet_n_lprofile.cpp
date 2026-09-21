#include "benchmark.h"

#include <algorithm>
#include <array>
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

std::vector<Ct> alexnet_tiny(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> alexnet_tiny__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
std::vector<double> alexnet_tiny__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
std::tuple<CtxPtr, UI> __configure();


// ============================================================================
// Global benchmark configuration
// ============================================================================

static constexpr int kwarmups = 1;
static constexpr int kiterations = 3;


// ============================================================================
// AlexNet benchmark fixture
// ============================================================================

class AlexnetTinyProfile
    : public ::testing::Test {

protected:

  using Context = cheddar::Context<word>;

  using Ct = cheddar::Ciphertext<word>;

  using Pt = cheddar::Plaintext<word>;

  using LinearTransform =
      cheddar::LinearTransform<word>;


  // --------------------------------------------------------------------------
  // Shared benchmark state
  // --------------------------------------------------------------------------

  static inline BenchmarkConfig config{
      .warmups = kwarmups,
      .iterations = kiterations
  };

  static inline BenchmarkSpecification benchmark;

  static inline bool initialized = false;


  // --------------------------------------------------------------------------
  // Shared model state
  // --------------------------------------------------------------------------

  static inline std::shared_ptr<Context> ctx;

  static inline std::unique_ptr<UI> ui;

  static inline std::vector<float> test_input_float;

//   static inline Evk* evk = nullptr;

//   static inline EvkMap* evk_map = nullptr;


  // --------------------------------------------------------------------------
  // Initialize common model state
  // --------------------------------------------------------------------------

  static void SetUpTestSuite() {

    // ------------------------------------------------------------------------
    // Configure context
    // ------------------------------------------------------------------------

    ctx.reset();
    ui.reset();

    auto[new_ctx, new_ui] = __configure();

    ctx = std::move(new_ctx);
    ui = std::move(new_ui);

    ASSERT_NE(ctx, nullptr);
    ASSERT_NE(ui, nullptr);


    // ------------------------------------------------------------------------
    // Evaluation keys
    // ------------------------------------------------------------------------

    // evk = &ui->GetMultiplicationKey();

    // evk_map = &ui->GetEvkMap();


    // ------------------------------------------------------------------------
    // Input
    // ------------------------------------------------------------------------

    std::vector<double> test_input(
        1 * 3 * 16 * 16);

    const std::filesystem::path input_path =
        std::filesystem::path(TEST_DATA_DIR) /
        "input.bin";

    std::ifstream in(
        input_path,
        std::ios::binary);

    ASSERT_TRUE(in.good());

    in.read(
        reinterpret_cast<char*>(
            test_input.data()),
        test_input.size() * sizeof(double));

    ASSERT_EQ(
        in.gcount(),
        static_cast<std::streamsize>(
            test_input.size() * sizeof(double)));


    test_input_float.assign(
        test_input.begin(),
        test_input.end());


    initialized = true;
  }


  // --------------------------------------------------------------------------
  // Cleanup
  // --------------------------------------------------------------------------

  static void TearDownTestSuite() {

    // evk = nullptr;
    // evk_map = nullptr;

    ui.reset();
    ctx.reset();

    initialized = false;
  }
};


// ============================================================================
// Configuration
// ============================================================================
//
// This test measures:
//
//   Context Generation
//   Key Generation
//   Evaluation Key Generation
//   Configuration
//
// IMPORTANT:
// Configuration is benchmarked independently for each measured iteration.
// Each iteration should construct its own fresh state if the generated
// configuration function creates/replaces the context and UI.
//

TEST_F(
    AlexnetTinyProfile,
    Configuration) {

  ASSERT_TRUE(initialized);


  BenchmarkSpecification setup_benchmark;


  // --------------------------------------------------------------------------
  // Context Generation
  // --------------------------------------------------------------------------

  setup_benchmark.setup.context_generation = [&] {

    // Replace this with the actual context-generation function if your
    // generated code exposes one.

    ctx.reset();
    ui.reset();

    auto[new_ctx, new_ui] = __configure();

    ctx = std::move(new_ctx);
    ui = std::move(new_ui);
  };


  // --------------------------------------------------------------------------
  // Key Generation
  // --------------------------------------------------------------------------

  setup_benchmark.setup.key_generation = [&] {

    // Put the generated key-generation call here.
    //
    // Example:
    //
    // alexnet_tiny__generate_keys(
    //     ctx,
    //     ui);
  };


  // --------------------------------------------------------------------------
  // Evaluation Key Generation
  // --------------------------------------------------------------------------

  setup_benchmark.setup.eval_key_generation = [&] {

    // Put the generated evaluation-key generation call here.
    //
    // Example:
    //
    // alexnet_tiny__generate_eval_keys(
    //     ctx,
    //     ui);
  };


  // --------------------------------------------------------------------------
  // Configuration
  // --------------------------------------------------------------------------

  setup_benchmark.setup.configuration = [&] {

    ctx.reset();
    ui.reset();

    alexnet_tiny__configure(
        ctx,
        ui);

    ASSERT_NE(ctx, nullptr);
    ASSERT_NE(ui, nullptr);
  };


  // --------------------------------------------------------------------------
  // Run setup benchmark
  // --------------------------------------------------------------------------

  run_setup(
      setup_benchmark.setup,
      config);


  // --------------------------------------------------------------------------
  // Copy results into the suite benchmark object
  // --------------------------------------------------------------------------

  benchmark.setup =
      setup_benchmark.setup;


  // --------------------------------------------------------------------------
  // Restore configured state for inference
  // --------------------------------------------------------------------------

  ctx.reset();
  ui.reset();

  alexnet_tiny__configure(
      ctx,
      ui);

  ASSERT_NE(ctx, nullptr);
  ASSERT_NE(ui, nullptr);

  // evk = &ui->GetMultiplicationKey();
  //evk_map = &ui->GetEvkMap();
}


// ============================================================================
// Inference
// ============================================================================
//
// Execution order for EACH iteration:
//
//   Encryption
//       ↓
//   Plaintext preprocessing
//       ↓
//   Encrypted computation
//       ↓
//   Decryption
//
// Warmup iterations are not included in statistics.
//

TEST_F(
    AlexnetTinyProfile,
    Inference) {

  ASSERT_TRUE(initialized);
  ASSERT_NE(ctx, nullptr);
  ASSERT_NE(ui, nullptr);


  // --------------------------------------------------------------------------
  // Build inference specification
  // --------------------------------------------------------------------------

  benchmark.inference.inference =
      [&]() -> InferenceTiming {

    std::array<Ct, 1> encrypted;

    std::array<Pt, 4> plaintexts;

    std::array<
        std::shared_ptr<LinearTransform>,
        4> transforms;

    std::array<Ct, 1> evaluated;

    float result[10];


    InferenceTiming timing;


    // ------------------------------------------------------------------------
    // Encryption
    // ------------------------------------------------------------------------

    timing.encryption_ms =
        time_phase(
            "Encryption",
            [&] {

              alexnet_tiny__encrypt__arg0(
                  ctx.get(),
                  ctx->encoder_,
                  *evk,
                  test_input_float.data(),
                  ui.get(),
                  encrypted);
            });


    // ------------------------------------------------------------------------
    // Plaintext preprocessing
    // ------------------------------------------------------------------------

    timing.preprocessing_ms =
        time_phase(
            "Plaintext Preprocessing",
            [&] {

              alexnet_tiny__preprocessing(
                  ctx.get(),
                  ctx->encoder_,
                  transforms,
                  plaintexts);
            });


    // ------------------------------------------------------------------------
    // Encrypted computation
    // ------------------------------------------------------------------------

    timing.evaluation_ms =
        time_phase(
            "Encrypted Computation",
            [&] {

              alexnet_tiny__preprocessed(
                  ctx.get(),
                  ctx->encoder_,
                  *evk,
                  *evk_map,
                  encrypted,
                  transforms,
                  plaintexts,
                  evaluated);
            });


    // ------------------------------------------------------------------------
    // Decryption
    // ------------------------------------------------------------------------

    timing.decryption_ms =
        time_phase(
            "Decryption",
            [&] {

              alexnet_tiny__decrypt__result0(
                  ctx.get(),
                  ctx->encoder_,
                  *evk,
                  evaluated,
                  ui.get(),
                  result);
            });


    // ------------------------------------------------------------------------
    // Correctness check
    // ------------------------------------------------------------------------

    const std::filesystem::path output_path =
        std::filesystem::path(TEST_DATA_DIR) /
        "torch_output.bin";

    std::ifstream torch_in(
        output_path,
        std::ios::binary);

    ASSERT_TRUE(torch_in.good());

    std::vector<double> torch_output(10);

    torch_in.read(
        reinterpret_cast<char*>(
            torch_output.data()),
        torch_output.size() * sizeof(double));

    ASSERT_EQ(
        torch_in.gcount(),
        static_cast<std::streamsize>(
            torch_output.size() * sizeof(double)));


    for (std::size_t i = 0; i < 10; ++i) {

      EXPECT_NEAR(
          result[i],
          torch_output[i],
          1e-3);
    }


    return timing;
  };


  // --------------------------------------------------------------------------
  // Run benchmark
  // --------------------------------------------------------------------------

  run_inference_benchmark(
      benchmark.inference,
      config);
}


// ============================================================================
// Reporting
// ============================================================================
//
// This test only reports the results collected by Configuration and
// Inference.
//

TEST_F(
    AlexnetTinyProfile,
    Reporting) {

  // --------------------------------------------------------------------------
  // Configuration results
  // --------------------------------------------------------------------------

  ASSERT_EQ(
      benchmark.setup.context_generation_stats.size(),
      static_cast<std::size_t>(kiterations));

  ASSERT_EQ(
      benchmark.setup.key_generation_stats.size(),
      static_cast<std::size_t>(kiterations));

  ASSERT_EQ(
      benchmark.setup.eval_key_generation_stats.size(),
      static_cast<std::size_t>(kiterations));

  ASSERT_EQ(
      benchmark.setup.configuration_stats.size(),
      static_cast<std::size_t>(kiterations));


  // --------------------------------------------------------------------------
  // Inference results
  // --------------------------------------------------------------------------

  ASSERT_EQ(
      benchmark.inference.encryption_stats.size(),
      static_cast<std::size_t>(kiterations));

  ASSERT_EQ(
      benchmark.inference.preprocessing_stats.size(),
      static_cast<std::size_t>(kiterations));

  ASSERT_EQ(
      benchmark.inference.evaluation_stats.size(),
      static_cast<std::size_t>(kiterations));

  ASSERT_EQ(
      benchmark.inference.decryption_stats.size(),
      static_cast<std::size_t>(kiterations));

  ASSERT_EQ(
      benchmark.inference.online_total_stats.size(),
      static_cast<std::size_t>(kiterations));


  // --------------------------------------------------------------------------
  // Report
  // --------------------------------------------------------------------------

  report_setup(
      benchmark.setup);

  report_inference(
      benchmark.inference);
}

