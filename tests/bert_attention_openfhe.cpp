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

#include "openfhe.h"  // from @openfhe

using namespace lbcrypto;
using CiphertextT = Ciphertext<DCRTPoly>;
using ConstCiphertextT = ConstCiphertext<DCRTPoly>;
using CCParamsT = CCParams<CryptoContextCKKSRNS>;
using CryptoContextT = CryptoContext<DCRTPoly>;
using EvalKeyT = EvalKey<DCRTPoly>;
using PlaintextT = Plaintext;
using PrivateKeyT = PrivateKey<DCRTPoly>;
using PublicKeyT = PublicKey<DCRTPoly>;

std::vector<CiphertextT> bert_attention(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1, std::vector<float> v2);
std::vector<CiphertextT> bert_attention__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<float> bert_attention__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk);
CryptoContextT bert_attention__generate_crypto_context();
CryptoContextT bert_attention__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk);


std::vector<float> loadBinaryInput(const std::filesystem::path& relativePath,
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

  return std::vector<float>(temp.begin(), temp.end());
}

TEST(OpenFHESamples, BertAttentionFull) {
  auto cryptoContext = bert_attention__generate_crypto_context();
  auto keyPair = cryptoContext->KeyGen();
  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;
  cryptoContext =
    bert_attention__configure_crypto_context(cryptoContext, secretKey);

  std::filesystem::path Path3 =
    std::filesystem::path("bert_attention/inputs/3.bin");
  std::filesystem::path Path5 =
    std::filesystem::path("bert_attention/inputs/5.bin");
  std::filesystem::path Path239 =
    std::filesystem::path("bert_attention/inputs/239.bin");
  std::vector<float> in_3 = loadBinaryInput(Path3, 4096);
  std::vector<float> in_5 = loadBinaryInput(Path5, 64*4096);
  std::vector<float> in_239 = loadBinaryInput(Path239, 64*4096);

  // encrypt input
  auto encrypted_input = bert_attention__encrypt__arg0(cryptoContext, in_3, publicKey);
  // bert_attention on encrypted input
  auto encrypted_result = bert_attention(cryptoContext, encrypted_input, in_5, in_239);
  // decrypt result
  std::vector<float> result = bert_attention__decrypt__result0(cryptoContext, encrypted_result, secretKey);

  std::filesystem::path outPath =
    std::filesystem::path("bert_attention/results/result.bin");
  std::vector<float> actual_result = loadBinaryInput(outPath, 4096);

  
  // Compare the result with Rotoms testdata
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], actual_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), actual_result.size());
}