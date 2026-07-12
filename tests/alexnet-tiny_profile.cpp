#include "algorithm"
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

#include <chrono>

using Clock = std::chrono::steady_clock;

constexpr int kWarmup = 5;
constexpr int kIterations = 100;

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

#include <nvtx3/nvToolsExt.h>

int main(int argc, char** argv) {
  // Initialize once
  auto[ctx, ui] = __configure();

  std::vector<double> test_input(1 * 3 * 16 * 16);
  std::generate(test_input.begin(), test_input.end(), 
    []() { return static_cast<double>(rand()) / RAND_MAX; });

  // Warm-up
  for (int i = 0; i < kWarmup; ++i) {
    auto enc = alexnet_tiny__encrypt__arg0(
        ctx, ctx->encoder_, ui, test_input, ui);

    auto out = alexnet_tiny(
        ctx, ctx->encoder_, ui, enc);

    auto dec = alexnet_tiny__decrypt__result0(
        ctx, ctx->encoder_, ui, out, ui);
  }

  cudaDeviceSynchronize();

  double encrypt_ms = 0;
  double inference_ms = 0;
  double decrypt_ms = 0;

  // stage profiling: Synchronize CUDA before and after each stage to get accurate timing. 
  // To profile the entire pipeline, you can remove the synchronizations and measure the total time for all stages combined.
  for (int i = 0; i < kIterations; ++i) {
    // Encrypt
    nvtxRangePushA("Encrypt");
    auto t0 = Clock::now();
    auto encrypted_input =
      alexnet_tiny__encrypt__arg0(ctx, ctx->encoder_, ui, test_input, ui);
    cudaDeviceSynchronize();
    auto t1 = Clock::now();
    nvtxRangePop();

    // Inference
    nvtxRangePushA("Inference");
    auto encrypted_result =
      alexnet_tiny(ctx, ctx->encoder_, ui, encrypted_input);
    cudaDeviceSynchronize();
    auto t2 = Clock::now();
    nvtxRangePop();

    // Decrypt
    nvtxRangePushA("Decrypt");
    auto result =
      alexnet_tiny__decrypt__result0(
        ctx, ctx->encoder_, ui, encrypted_result, ui);
    cudaDeviceSynchronize();
    auto t3 = Clock::now();
    nvtxRangePop();

    std::cout << "Encrypt : "
              << std::chrono::duration<double, std::milli>(t1 - t0).count()
              << " ms\n";

    std::cout << "Inference : "
              << std::chrono::duration<double, std::milli>(t2 - t1).count()
              << " ms\n";

    std::cout << "Decrypt : "
              << std::chrono::duration<double, std::milli>(t3 - t2).count()
              << " ms\n";

    encrypt_ms +=
      std::chrono::duration<double, std::milli>(t1 - t0).count();

    inference_ms +=
      std::chrono::duration<double, std::milli>(t2 - t1).count();

    decrypt_ms +=
      std::chrono::duration<double, std::milli>(t3 - t2).count();
  }

  std::cout << "Average over " << kIterations << " iterations\n";
  std::cout << "Encrypt : " << encrypt_ms / kIterations << " ms\n";
  std::cout << "Inference: " << inference_ms / kIterations << " ms\n";
  std::cout << "Decrypt : " << decrypt_ms / kIterations << " ms\n";
  std::cout << "Total    : "
            << (encrypt_ms + inference_ms + decrypt_ms) / kIterations
            << " ms\n";
}