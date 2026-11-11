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


std::vector<CiphertextT> matmul_secret(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<CiphertextT> v1);
std::vector<CiphertextT> matmul_secret__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<CiphertextT> matmul_secret__encrypt__arg1(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<float> matmul_secret__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk);
CryptoContextT matmul_secret__generate_crypto_context();
CryptoContextT matmul_secret__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk);


class MatmulSecretRotomProfile : public ::testing::Test {
protected:
  static inline Benchmark benchmark;
  static inline BenchmarkConfig config{1, 3};
};


TEST_F(MatmulSecretRotomProfile, Configuration) {

  CryptoContextT cryptoContext;
  PublicKeyT publicKey;
  PrivateKeyT secretKey;

  benchmark.setup = {
    phase("Context Generation", [&] {
        cryptoContext = matmul_secret__generate_crypto_context();
        auto keyPair = cryptoContext->KeyGen();
        publicKey = keyPair.publicKey;
        secretKey = keyPair.secretKey;
        cryptoContext = 
          matmul_secret__configure_crypto_context(cryptoContext, secretKey);
    })
  };

  benchmark.run_setup({1, 3});
}


TEST_F(MatmulSecretRotomProfile, Inference) {

  // std::vector<float> test_input(4096);

  std::filesystem::path Path5 =
    std::filesystem::path("matmul_secret/inputs/5.bin");
  std::filesystem::path Path15 =
    std::filesystem::path("matmul_secret/inputs/15.bin");

  std::vector<float> in_5 = loadBinaryInput_f(Path5, 2048);
  std::vector<float> in_15 = loadBinaryInput_f(Path15, 2048);

  std::vector<CiphertextT> matrix1_encrypted;
  std::vector<CiphertextT> matrix2_encrypted;
  std::vector<CiphertextT> encrypted_result;
  std::vector<float> result;

  // Setup crypto context and keys
  auto cryptoContext = matmul_secret__generate_crypto_context();
  auto keyPair = cryptoContext->KeyGen();
  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;
  cryptoContext = 
    matmul_secret__configure_crypto_context(cryptoContext, secretKey);

  benchmark.inference = {
    phase("Encryption", [&] {
       matrix1_encrypted = matmul_secret__encrypt__arg0(cryptoContext, in_5, publicKey);
       matrix2_encrypted = matmul_secret__encrypt__arg1(cryptoContext, in_15, publicKey);
    }),

    phase("Encrypted Computation", [&] {
      encrypted_result = matmul_secret(cryptoContext, matrix1_encrypted, matrix2_encrypted);
    }),

    phase("Decryption", [&] {
      result = matmul_secret__decrypt__result0(cryptoContext, encrypted_result, secretKey);
    })
  };

  benchmark.run_inference({1, 3});


  std::filesystem::path outPath =
    std::filesystem::path("matmul_secret/results/result.bin");
  std::vector<float> actual_result = loadBinaryInput_f(outPath, 2048);
  // Compare the result with Rotoms testdata
  for (size_t i = 0; i < result.size(); ++i) {
    // if ((i%64 == 0)) {  // Print every 64th value for debugging, Layout: [0:64:1][G:64]
    //   std::cout << "result[" << i << "] = " << result[i]
    //             << ", actual_result[" << i << "] = " << actual_result[i] << '\n';
    // }
    EXPECT_NEAR(result[i], actual_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), actual_result.size());

}


TEST_F(MatmulSecretRotomProfile, Reporting) {
  benchmark.report();
}