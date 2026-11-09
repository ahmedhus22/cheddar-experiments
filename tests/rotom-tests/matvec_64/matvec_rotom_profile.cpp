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


std::vector<CiphertextT> matvec_64(CryptoContextT cc, std::vector<CiphertextT> v0, std::vector<float> v1);
std::vector<CiphertextT> matvec_64__encrypt__arg0(CryptoContextT cc, std::vector<float> v0, PublicKeyT pk);
std::vector<float> matvec_64__decrypt__result0(CryptoContextT cc, std::vector<CiphertextT> v0, PrivateKeyT sk);
CryptoContextT matvec_64__generate_crypto_context();
CryptoContextT matvec_64__configure_crypto_context(CryptoContextT cc, PrivateKeyT sk);

TimingStats context_generation;
TimingStats key_generation;
TimingStats eval_key_generation;
TimingStats configuration;
int kwarmups = 1;
int kiterations = 3;
double configuration_warmup_ms = 0.0;

class Matvec64RotomProfile : public ::testing::Test {
protected:
  static inline Benchmark benchmark;
  static inline BenchmarkConfig config{1, 3};
};


TEST_F(Matvec64RotomProfile, Configuration) {

  Benchmark benchmark;

  CryptoContextT cryptoContext;
  PublicKeyT publicKey;
  PrivateKeyT secretKey;

  benchmark.setup = {
    phase("Context Generation", [&] {
        cryptoContext = matvec_64__generate_crypto_context();
        auto keyPair = cryptoContext->KeyGen();
        publicKey = keyPair.publicKey;
        secretKey = keyPair.secretKey;
        cryptoContext = 
          matvec_64__configure_crypto_context(cryptoContext, secretKey);
    })

    // phase("Key Generation", [&] {
    //   alexnet_tiny__key_generation(...);
    // }),

    // phase("Evaluation Key Generation", [&] {
    //   alexnet_tiny__eval_key_generation(...);
    // }),

    // phase("Configuration", [&] {
    //   alexnet_tiny__configure(ctx, ui);
    // })
  };

  benchmark.run_setup({1, 3});
}

TimingStats encryption_stats;
TimingStats preprocessing_stats;
TimingStats evaluation_stats;
TimingStats decryption_stats;
TimingStats online_total_stats;

TEST_F(Matvec64RotomProfile, Inference) {

  Benchmark benchmark;

  std::vector<float> test_input(4096);

  std::filesystem::path Path4 =
    std::filesystem::path("matvec_64/inputs/4.bin");
  std::filesystem::path Path6 =
    std::filesystem::path("matvec_64/inputs/6.bin");

  std::vector<float> in_4 = loadBinaryInput_f(Path4, 4096);
  std::vector<float> in_6 = loadBinaryInput_f(Path6, 4096);

  std::vector<CiphertextT> encrypted_input;
  std::vector<CiphertextT> encrypted_result;
  std::vector<float> result;

  // Setup crypto context and keys
  auto cryptoContext = matvec_64__generate_crypto_context();
  auto keyPair = cryptoContext->KeyGen();
  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;
  cryptoContext = 
    matvec_64__configure_crypto_context(cryptoContext, secretKey);

  benchmark.inference = {
    phase("Encryption", [&] {
       encrypted_input = matvec_64__encrypt__arg0(cryptoContext, in_4, publicKey);
    }),

    phase("Encrypted Computation", [&] {
      encrypted_result = matvec_64(cryptoContext, encrypted_input, in_6);
    }),

    phase("Decryption", [&] {
      result = matvec_64__decrypt__result0(cryptoContext, encrypted_result, secretKey);
    })
  };

  benchmark.run_inference({1, 3});
}




TEST_F(Matvec64RotomProfile, Reporting) {
  benchmark.report();
}