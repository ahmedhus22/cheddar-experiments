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

std::vector<CiphertextT> matvec_64(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1);
std::vector<CiphertextT> matvec_64__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<float> matvec_64__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk);
CryptoContextT matvec_64__generate_crypto_context();
CryptoContextT matvec_64__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk);


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
  // std::cout << filePath.string() << " loaded successfully. First few values:\n";
  // for (size_t i = 0; i < std::min<size_t>(10, temp.size()); ++i)
  //   std::cout << temp[i] << '\n';

  // for (double x : temp) {
  //   if (!std::isfinite(x))
  //     std::cout << "Non-finite value found\n";
  // }

  // auto [mn, mx] = std::minmax_element(temp.begin(), temp.end());
  // std::cout << "min = " << *mn << ", max = " << *mx << '\n';

  return std::vector<float>(temp.begin(), temp.end());
}

TEST(OpenFHESamples, Matvec64) {
  auto cryptoContext = matvec_64__generate_crypto_context();
  auto keyPair = cryptoContext->KeyGen();
  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;
  cryptoContext =
    matvec_64__configure_crypto_context(cryptoContext, secretKey);

  std::filesystem::path Path4 =
    std::filesystem::path("matvec_64/inputs/4.bin");
  std::filesystem::path Path6 =
    std::filesystem::path("matvec_64/inputs/6.bin");
  std::vector<float> in_4 = loadBinaryInput(Path4, 4096);
  std::vector<float> in_6 = loadBinaryInput(Path6, 4096);

  // encrypt input
  auto encrypted_input = matvec_64__encrypt__arg0(cryptoContext, in_4, publicKey);
  // matvec_64 on encrypted input
  auto encrypted_result = matvec_64(cryptoContext, encrypted_input, in_6);
  // decrypt result
  std::vector<float> result = matvec_64__decrypt__result0(cryptoContext, encrypted_result, secretKey);

  std::filesystem::path outPath =
    std::filesystem::path("matvec_64/results/result.bin");
  std::vector<float> actual_result = loadBinaryInput(outPath, 4096);

  
  // Compare the result with Rotoms testdata
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], actual_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), actual_result.size());
}