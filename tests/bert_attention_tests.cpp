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
#include <stdexcept>
#include <string>
#include <vector>


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

std::vector<double> loadBinaryInput(const std::filesystem::path& relativePath,
                                    std::size_t numElements) {
  std::filesystem::path filePath =
      std::filesystem::path(TEST_DATA_DIR) / relativePath;

  std::ifstream in(filePath, std::ios::binary);
  if (!in) {
    throw std::runtime_error("Failed to open file: " + filePath.string());
  }

  std::vector<double> temp(numElements);
  in.read(reinterpret_cast<char*>(temp.data()),
          temp.size() * sizeof(double));

  if (in.gcount() !=
      static_cast<std::streamsize>(temp.size() * sizeof(double))) {
    throw std::runtime_error("Failed to read expected number of bytes from: " +
                             filePath.string());
  }

  // Uncomment the following lines for debugging purposes
  std::cout << filePath.string() << " loaded successfully. First few values:\n";
  for (size_t i = 0; i < std::min<size_t>(10, temp.size()); ++i)
    std::cout << temp[i] << '\n';

  for (double x : temp) {
    if (!std::isfinite(x))
      std::cout << "Non-finite value found\n";
  }

  auto [mn, mx] = std::minmax_element(temp.begin(), temp.end());
  std::cout << "min = " << *mn << ", max = " << *mx << '\n';

  return std::vector<double>(temp.begin(), temp.end());
}

TEST(CheddarSamples, BertAttentionFull) {
  auto[ctx, ui] = __configure();

  std::filesystem::path Path3 =
    std::filesystem::path("bert_attention/inputs/3.bin");
  std::filesystem::path Path5 =
    std::filesystem::path("bert_attention/inputs/5.bin");
  std::filesystem::path Path239 =
    std::filesystem::path("bert_attention/inputs/239.bin");
  std::vector<double> in_3 = loadBinaryInput(Path3, 4096);
  std::vector<double> in_5 = loadBinaryInput(Path5, 64*4096);
  std::vector<double> in_239 = loadBinaryInput(Path239, 64*4096);

  // encrypt input
  auto encrypted_input = bert_attention__encrypt__arg0(ctx, ctx->encoder_, ui, in_3, ui);
  // bert_attention on encrypted input
  auto encrypted_result = bert_attention(ctx, ctx->encoder_, ui, encrypted_input, in_5, in_239);
  // decrypt result
  std::vector<double> result = bert_attention__decrypt__result0(ctx, ctx->encoder_, ui, encrypted_result, ui);

  std::filesystem::path outPath =
    std::filesystem::path("bert_attention/results/result.bin");
  std::vector<double> actual_result = loadBinaryInput(outPath, 4096);

  
  // Compare the result with Rotoms testdata
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], actual_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), actual_result.size());
}