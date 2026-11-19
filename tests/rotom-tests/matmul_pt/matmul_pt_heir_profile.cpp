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


std::vector<CiphertextT> matmul_pt(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1);
std::vector<CiphertextT> matmul_pt__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<float> matmul_pt__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk);
CryptoContextT matmul_pt__generate_crypto_context();
CryptoContextT matmul_pt__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk);


class MatmulPTRotomProfile : public ::testing::Test {
protected:
  static inline Benchmark benchmark;
  static inline BenchmarkConfig config{1, 3};
};


TEST_F(MatmulPTRotomProfile, Configuration) {

  CryptoContextT cryptoContext;
  PublicKeyT publicKey;
  PrivateKeyT secretKey;

  benchmark.setup = {
    phase("Context Generation", [&] {
        cryptoContext = matmul_pt__generate_crypto_context();
        auto keyPair = cryptoContext->KeyGen();
        publicKey = keyPair.publicKey;
        secretKey = keyPair.secretKey;
        cryptoContext = 
          matmul_pt__configure_crypto_context(cryptoContext, secretKey);
    })
  };

  benchmark.run_setup({1, 3});
}


TEST_F(MatmulPTRotomProfile, Inference) {

  std::filesystem::path Patha =
    std::filesystem::path("matmul_pt/bicyclic_pt/a.bin");
  std::filesystem::path Pathb =
    std::filesystem::path("matmul_pt/bicyclic_pt/b.bin");

  std::vector<float> in_a = loadBinaryInput_ff(Patha, 13*14);
  std::vector<float> in_b = loadBinaryInput_ff(Pathb, 14*16);

  std::vector<CiphertextT> matrix1_encrypted;
  std::vector<CiphertextT> encrypted_result;
  std::vector<float> result;

  // Setup crypto context and keys
  auto cryptoContext = matmul_pt__generate_crypto_context();
  auto keyPair = cryptoContext->KeyGen();
  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;
  cryptoContext = 
    matmul_pt__configure_crypto_context(cryptoContext, secretKey);

  benchmark.inference = {
    phase("Encryption", [&] {
       matrix1_encrypted = matmul_pt__encrypt__arg0(cryptoContext, in_a, publicKey);
    }),

    phase("Encrypted Computation", [&] {
      encrypted_result = matmul_pt(cryptoContext, matrix1_encrypted, in_b);
    }),

    phase("Decryption", [&] {
      result = matmul_pt__decrypt__result0(cryptoContext, encrypted_result, secretKey);
    })
  };

  benchmark.run_inference({1, 3});


  std::filesystem::path outPath =
    std::filesystem::path("matmul_pt/bicyclic_pt/result.bin");
  std::vector<float> actual_result = loadBinaryInput_ff(outPath, 13*16);
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


TEST_F(MatmulPTRotomProfile, Reporting) {
  benchmark.report();
}