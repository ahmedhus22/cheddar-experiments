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


std::vector<CiphertextT> bicyclic_matmul(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<CiphertextT> v1);
std::vector<CiphertextT> bicyclic_matmul__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<CiphertextT> bicyclic_matmul__encrypt__arg1(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<float> bicyclic_matmul__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk);
CryptoContextT bicyclic_matmul__generate_crypto_context();
CryptoContextT bicyclic_matmul__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk);


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
        cryptoContext = bicyclic_matmul__generate_crypto_context();
        auto keyPair = cryptoContext->KeyGen();
        publicKey = keyPair.publicKey;
        secretKey = keyPair.secretKey;
        cryptoContext = 
          bicyclic_matmul__configure_crypto_context(cryptoContext, secretKey);
    })
  };

  benchmark.run_setup({1, 3});
}


TEST_F(MatmulSecretRotomProfile, Inference) {

  // std::vector<float> test_input(4096);

  std::filesystem::path Path5 =
    std::filesystem::path("matmul_secret/bicyclic/a.bin");
  std::filesystem::path Path15 =
    std::filesystem::path("matmul_secret/bicyclic/b.bin");

  std::vector<float> in_5 = loadBinaryInput_ff(Path5, 16*17);
  std::vector<float> in_15 = loadBinaryInput_ff(Path15, 17*19);

  std::vector<CiphertextT> matrix1_encrypted;
  std::vector<CiphertextT> matrix2_encrypted;
  std::vector<CiphertextT> encrypted_result;
  std::vector<float> result;

  // Setup crypto context and keys
  auto cryptoContext = bicyclic_matmul__generate_crypto_context();
  auto keyPair = cryptoContext->KeyGen();
  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;
  cryptoContext = 
    bicyclic_matmul__configure_crypto_context(cryptoContext, secretKey);

  benchmark.inference = {
    phase("Encryption", [&] {
       matrix1_encrypted = bicyclic_matmul__encrypt__arg0(cryptoContext, in_5, publicKey);
       matrix2_encrypted = bicyclic_matmul__encrypt__arg1(cryptoContext, in_15, publicKey);
    }),

    phase("Encrypted Computation", [&] {
      encrypted_result = bicyclic_matmul(cryptoContext, matrix1_encrypted, matrix2_encrypted);
    }),

    phase("Decryption", [&] {
      result = bicyclic_matmul__decrypt__result0(cryptoContext, encrypted_result, secretKey);
    })
  };

  benchmark.run_inference({1, 3});


  std::filesystem::path outPath =
    std::filesystem::path("matmul_secret/bicyclic/result.bin");
  std::vector<float> actual_result = loadBinaryInput_ff(outPath, 16*19);
  // Compare the result with testdata
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], actual_result[i], 1e-4);
  }
  EXPECT_EQ(result.size(), actual_result.size());

}


TEST_F(MatmulSecretRotomProfile, Reporting) {
  benchmark.report();
}