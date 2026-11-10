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

#include "generic_benchmark.h"
#include "load_rotom_bin.h"

using namespace lbcrypto;
using CiphertextT = Ciphertext<DCRTPoly>;
using ConstCiphertextT = ConstCiphertext<DCRTPoly>;
using CCParamsT = CCParams<CryptoContextCKKSRNS>;
using CryptoContextT = CryptoContext<DCRTPoly>;
using EvalKeyT = EvalKey<DCRTPoly>;
using PlaintextT = Plaintext;
using PrivateKeyT = PrivateKey<DCRTPoly>;
using PublicKeyT = PublicKey<DCRTPoly>;


std::vector<CiphertextT> vecsum(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<CiphertextT> v1);
std::vector<CiphertextT> vecsum__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<float> vecsum__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk);
CryptoContextT vecsum__generate_crypto_context();
CryptoContextT vecsum__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk);


class VecSumRotomProfile : public ::testing::Test {
protected:
  static inline Benchmark benchmark;
  static inline BenchmarkConfig config{1, 3};
};


TEST_F(VecSumRotomProfile, Configuration) {

  CryptoContextT cryptoContext;
  PublicKeyT publicKey;
  PrivateKeyT secretKey;

  benchmark.setup = {
    phase("Context Generation", [&] {
        cryptoContext = vecsum__generate_crypto_context();
        auto keyPair = cryptoContext->KeyGen();
        publicKey = keyPair.publicKey;
        secretKey = keyPair.secretKey;
        cryptoContext = 
          vecsum__configure_crypto_context(cryptoContext, secretKey);
    })
  };

  benchmark.run_setup({1, 3});
}


TEST_F(VecSumRotomProfile, Inference) {

  std::vector<float> test_input(1024);

  std::filesystem::path Path4 =
    std::filesystem::path("vecsum/inputs/4.bin");
  std::filesystem::path Path6 =
    std::filesystem::path("vecsum/inputs/6.bin");

  std::vector<float> in_4 = loadBinaryInput_f(Path4, 1024);
  std::vector<float> in_6 = loadBinaryInput_f(Path6, 1024);

  std::vector<CiphertextT> v1_encrypted;
  std::vector<CiphertextT> v2_encrypted;
  std::vector<CiphertextT> encrypted_result;
  std::vector<float> result;

  // Setup crypto context and keys
  auto cryptoContext = vecsum__generate_crypto_context();
  auto keyPair = cryptoContext->KeyGen();
  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;
  cryptoContext = 
    vecsum__configure_crypto_context(cryptoContext, secretKey);

  benchmark.inference = {
    phase("Encryption", [&] {
       v1_encrypted = vecsum__encrypt__arg0(cryptoContext, in_4, publicKey);
       v2_encrypted = vecsum__encrypt__arg0(cryptoContext, in_6, publicKey);
    }),

    phase("Encrypted Computation", [&] {
      encrypted_result = vecsum(cryptoContext, v1_encrypted, v2_encrypted);
    }),

    phase("Decryption", [&] {
      result = vecsum__decrypt__result0(cryptoContext, encrypted_result, secretKey);
    })
  };

  benchmark.run_inference({1, 3});


  std::filesystem::path outPath =
    std::filesystem::path("vecsum/results/result.bin");
  std::vector<float> actual_result = loadBinaryInput_f(outPath, 1024);
  // Compare the result with Rotoms testdata
  for (size_t i = 0; i < result.size(); ++i) {
    if ((i < 10) || (i > 1014)) {
      std::cout << "result[" << i << "] = " << result[i]
                << ", actual_result[" << i << "] = " << actual_result[i] << '\n';
    }
    EXPECT_NEAR(result[i], actual_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), actual_result.size());

}


TEST_F(VecSumRotomProfile, Reporting) {
  benchmark.report();
}