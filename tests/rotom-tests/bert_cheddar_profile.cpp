#include <chrono>
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
#include <stdexcept>
#include <string>
#include <vector>

#include <cuda_runtime.h>
#include <nvtx3/nvToolsExt.h>

using Clock = std::chrono::high_resolution_clock;

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


std::vector<Ct> bert_attention(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<Ct> bert_attention__encrypt__arg0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<double>& v0, UI& ui1) ;
std::vector<double> bert_attention__decrypt__result0(CtxPtr ctx, Enc& encoder, UI& ui, const std::vector<Ct>& v0, UI& ui1);
std::tuple<CtxPtr, UI> __configure();

#include "load_rotom_bin.h"

int main(int argc, char** argv) {
  auto ms = [](auto a, auto b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
  };

  auto t0 = Clock::now();
  auto [ctx, ui] = __configure();
  // Ensure any initialization kernels complete.
  cudaDeviceSynchronize();
  auto t1 = Clock::now();

  std::filesystem::path Path3("bert_attention/inputs/3.bin");
  std::filesystem::path Path5("bert_attention/inputs/5.bin");
  std::filesystem::path Path239("bert_attention/inputs/239.bin");

  std::vector<double> in_3 = loadBinaryInput_d(Path3, 4096);
  std::vector<double> in_5 = loadBinaryInput_d(Path5, 64 * 4096);
  std::vector<double> in_239 = loadBinaryInput_d(Path239, 64 * 4096);

  nvtxRangePushA("Encryption");
  auto t2 = Clock::now();
  auto encrypted_input = bert_attention__encrypt__arg0(ctx, ctx->encoder_, ui, in_3, ui);
  cudaDeviceSynchronize();
  auto t3 = Clock::now();
  nvtxRangePop();

  nvtxRangePushA("Evaluation");
  auto encrypted_result = bert_attention(ctx, ctx->encoder_, ui, encrypted_input, in_5, in_239);
  cudaDeviceSynchronize();
  auto t4 = Clock::now();
  nvtxRangePop();

  nvtxRangePushA("Decryption");
  std::vector<double> result = bert_attention__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);
  cudaDeviceSynchronize();
  auto t5 = Clock::now();
  nvtxRangePop();

  std::cout << "Configuration      : " << ms(t0, t1) << " ms\n";
  std::cout << "Encryption         : " << ms(t2, t3) << " ms\n";
  std::cout << "Homomorphic eval   : " << ms(t3, t4) << " ms\n";
  std::cout << "Decryption         : " << ms(t4, t5) << " ms\n";
  std::cout << "End-to-end         : " << ms(t0, t5) << " ms\n";
 
  std::cout << "Calculating average evaluation time over multiple iterations...\n";

  const int iterations = 20;
  double total_ms = 0.0;

  for (int i = 0; i < iterations; ++i) {
    auto start = Clock::now();

    auto encrypted_result =
      bert_attention(ctx, ctx->encoder_, ui,
                      encrypted_input, in_5, in_239);

    cudaDeviceSynchronize();

    auto end = Clock::now();
    total_ms += ms(start, end);
  }

  std::cout << "Average evaluation: "
            << total_ms / iterations
            << " ms\n";
}