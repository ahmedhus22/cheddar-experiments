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

std::vector<Ct> lenet(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0);
std::vector<Ct> lenet__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1);
std::vector<double> lenet__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
std::tuple<CtxPtr, UI> __configure();

void lenet__setup(std::shared_ptr<Context<word>>& v1) {
  static Parameter<word> cheddar_param(15, static_cast<double>(static_cast<word>(1) << 45), 7, std::vector<std::pair<int, int>>{{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}}, std::vector<word>{36028797017456641ULL, 35184376545281ULL, 35184367828993ULL, 35184373989377ULL, 35184368025601ULL, 35184373006337ULL, 35184368877569ULL, 35184372744193ULL}, std::vector<word>{1152921504608747521ULL, 1152921504614055937ULL, 1152921504615628801ULL});
  v1 = Context<word>::Create(cheddar_param);
  return;
}
void lenet__keygen(const std::shared_ptr<Context<word>>& v1, std::unique_ptr<UserInterface<word>>& v2) {
  v2 = std::make_unique<UserInterface<word>>(v1);
  v2->PrepareRotationKey(1, 7);
  v2->PrepareRotationKey(2, 7);
  v2->PrepareRotationKey(3, 7);
  v2->PrepareRotationKey(4, 7);
  v2->PrepareRotationKey(5, 7);
  v2->PrepareRotationKey(6, 7);
  v2->PrepareRotationKey(7, 7);
  v2->PrepareRotationKey(8, 7);
  v2->PrepareRotationKey(9, 7);
  v2->PrepareRotationKey(10, 7);
  v2->PrepareRotationKey(11, 7);
  v2->PrepareRotationKey(12, 7);
  v2->PrepareRotationKey(13, 7);
  v2->PrepareRotationKey(14, 7);
  v2->PrepareRotationKey(15, 7);
  v2->PrepareRotationKey(16, 7);
  v2->PrepareRotationKey(17, 7);
  v2->PrepareRotationKey(18, 7);
  v2->PrepareRotationKey(19, 7);
  v2->PrepareRotationKey(20, 7);
  v2->PrepareRotationKey(21, 7);
  v2->PrepareRotationKey(22, 7);
  v2->PrepareRotationKey(23, 7);
  v2->PrepareRotationKey(24, 7);
  v2->PrepareRotationKey(25, 7);
  v2->PrepareRotationKey(26, 7);
  v2->PrepareRotationKey(27, 7);
  v2->PrepareRotationKey(28, 7);
  v2->PrepareRotationKey(29, 7);
  v2->PrepareRotationKey(30, 7);
  v2->PrepareRotationKey(31, 7);
  v2->PrepareRotationKey(32, 7);
  v2->PrepareRotationKey(46, 7);
  v2->PrepareRotationKey(64, 7);
  v2->PrepareRotationKey(69, 7);
  v2->PrepareRotationKey(92, 7);
  v2->PrepareRotationKey(96, 7);
  v2->PrepareRotationKey(115, 7);
  v2->PrepareRotationKey(128, 7);
  v2->PrepareRotationKey(138, 7);
  v2->PrepareRotationKey(160, 7);
  v2->PrepareRotationKey(161, 7);
  v2->PrepareRotationKey(184, 7);
  v2->PrepareRotationKey(192, 7);
  v2->PrepareRotationKey(207, 7);
  v2->PrepareRotationKey(224, 7);
  v2->PrepareRotationKey(230, 7);
  v2->PrepareRotationKey(253, 7);
  v2->PrepareRotationKey(256, 7);
  v2->PrepareRotationKey(276, 7);
  v2->PrepareRotationKey(288, 7);
  v2->PrepareRotationKey(299, 7);
  v2->PrepareRotationKey(320, 7);
  v2->PrepareRotationKey(322, 7);
  v2->PrepareRotationKey(345, 7);
  v2->PrepareRotationKey(352, 7);
  v2->PrepareRotationKey(368, 7);
  v2->PrepareRotationKey(384, 7);
  v2->PrepareRotationKey(391, 7);
  v2->PrepareRotationKey(414, 7);
  v2->PrepareRotationKey(416, 7);
  v2->PrepareRotationKey(437, 7);
  v2->PrepareRotationKey(448, 7);
  v2->PrepareRotationKey(460, 7);
  v2->PrepareRotationKey(480, 7);
  v2->PrepareRotationKey(483, 7);
  v2->PrepareRotationKey(506, 7);
  v2->PrepareRotationKey(512, 7);
  v2->PrepareRotationKey(544, 7);
  v2->PrepareRotationKey(576, 7);
  v2->PrepareRotationKey(608, 7);
  v2->PrepareRotationKey(640, 7);
  v2->PrepareRotationKey(672, 7);
  v2->PrepareRotationKey(704, 7);
  v2->PrepareRotationKey(736, 7);
  v2->PrepareRotationKey(768, 7);
  v2->PrepareRotationKey(800, 7);
  v2->PrepareRotationKey(832, 7);
  v2->PrepareRotationKey(864, 7);
  v2->PrepareRotationKey(896, 7);
  v2->PrepareRotationKey(928, 7);
  v2->PrepareRotationKey(960, 7);
  v2->PrepareRotationKey(992, 7);
  return;
}
void lenet__configure(std::shared_ptr<Context<word>>& v1, std::unique_ptr<UserInterface<word>>& v2) {
  bool v3 = true;
  std::shared_ptr<Context<word>> v4;
  lenet__setup(v4);
  lenet__keygen(v4, v2);
  v1 = v4;
  if (v3) {
    v4 = std::shared_ptr<Context<word>>();
  }
  return;
}

// ============================================================================
// Global benchmark configuration
// ============================================================================

static constexpr int kwarmups = 1;
static constexpr int kiterations = 3;


// ============================================================================
// LeNet benchmark fixture
// ============================================================================

class LeNetProfile
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

  static inline CtxPtr ctx;

  static inline std::unique_ptr<UserInterface<word>> ui;

  static inline std::vector<float> test_input_float;

  static inline std::vector<double> test_input_double;

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

    lenet__configure(ctx, ui);

    // std::tie(ctx, ui) = __configure();

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

    test_input_float.resize(1 * 1 * 28 * 28);

    const std::filesystem::path input_path =
        std::filesystem::path(TEST_DATA_DIR) /
        "input.bin";

    std::ifstream in(
        input_path,
        std::ios::binary);

    ASSERT_TRUE(in.good());

    in.read(
        reinterpret_cast<char*>(
            test_input_float.data()),
        test_input_float.size() * sizeof(float));

    ASSERT_EQ(
        in.gcount(),
        static_cast<std::streamsize>(
            test_input_float.size() * sizeof(float)));


    test_input_double.assign(
        test_input_float.begin(),
        test_input_float.end());


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

TEST_F(
    LeNetProfile,
    Configuration) {

  ASSERT_TRUE(initialized);


  BenchmarkSpecification setup_benchmark;


  // --------------------------------------------------------------------------
  // Context Generation
  // --------------------------------------------------------------------------

    //   setup_benchmark.setup.specification.context_generation = [&] {


    //     ctx.reset();
    //     ui.reset();

    //     lenet__configure(ctx, ui);
    //   };


  // --------------------------------------------------------------------------
  // Key Generation
  // --------------------------------------------------------------------------

  // --------------------------------------------------------------------------
  // Evaluation Key Generation
  // --------------------------------------------------------------------------

  // Key generation and evaluation key generation are combined in the lenet__configure function


  // --------------------------------------------------------------------------
  // Configuration
  // --------------------------------------------------------------------------

  setup_benchmark.setup.specification.configuration = [&] {

    ctx.reset();
    ui.reset();

    lenet__configure(ctx, ui);

    ASSERT_NE(ctx, nullptr);
    ASSERT_NE(ui, nullptr);
  };

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

  lenet__configure(ctx, ui);

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
    LeNetProfile,
    Inference) {

  ASSERT_TRUE(initialized);
  ASSERT_NE(ctx, nullptr);
  ASSERT_NE(ui, nullptr);


  // --------------------------------------------------------------------------
  // Build inference specification
  // --------------------------------------------------------------------------

  benchmark.inference.inference =
      [&]() -> InferenceTiming {

    std::vector<Ct> encrypted;


    std::vector<Ct> evaluated;

    std::vector<double> result;


    InferenceTiming timing;


    // ------------------------------------------------------------------------
    // Encryption
    // ------------------------------------------------------------------------

    timing.encryption_ms =
        time_phase(
            "Encryption",
            [&] {

              encrypted = lenet__encrypt__arg0(
                  ctx,
                  ctx->encoder_,
                  *ui,
                  test_input_double,
                  *ui
                  );
            });


    // ------------------------------------------------------------------------
    // Plaintext preprocessing
    // ------------------------------------------------------------------------

    // timing.preprocessing_ms =
    //     time_phase(
    //         "Plaintext Preprocessing",
    //         [&] {

    //           lenet__preprocessing(
    //               ctx.get(),
    //               ctx->encoder_,
    //               transforms,
    //               plaintexts);
    //         });


    // ------------------------------------------------------------------------
    // Encrypted computation
    // ------------------------------------------------------------------------

    timing.evaluation_ms =
        time_phase(
            "Encrypted Computation",
            [&] {

              evaluated = lenet(
                  ctx,
                  ctx->encoder_,
                  *ui,
                  encrypted);
            });


    // ------------------------------------------------------------------------
    // Decryption
    // ------------------------------------------------------------------------

    timing.decryption_ms =
        time_phase(
            "Decryption",
            [&] {

              result = lenet__decrypt__result0(
                  ctx,
                  ctx->encoder_,
                  *ui,
                  evaluated,
                  *ui);
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

    EXPECT_TRUE(torch_in.good());

    std::vector<float> torch_output(10);

    torch_in.read(
        reinterpret_cast<char*>(
            torch_output.data()),
        torch_output.size() * sizeof(float));

    EXPECT_EQ(
        torch_in.gcount(),
        static_cast<std::streamsize>(
            torch_output.size() * sizeof(float)));


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
    LeNetProfile,
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

