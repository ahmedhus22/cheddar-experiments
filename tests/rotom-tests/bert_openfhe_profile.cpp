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


#include "openfhe.h"  // from @openfhe

using Clock = std::chrono::high_resolution_clock;

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

#include "load_rotom_bin.h"

int main(int argc, char** argv) {
  auto t0 = Clock::now();
  auto cryptoContext = bert_attention__generate_crypto_context();
  auto t1 = Clock::now();

  auto keyPair = cryptoContext->KeyGen();
  auto t2 = Clock::now();

  auto publicKey = keyPair.publicKey;
  auto secretKey = keyPair.secretKey;

  cryptoContext =
    bert_attention__configure_crypto_context(cryptoContext, secretKey);
  auto t3 = Clock::now();

  std::filesystem::path Path3 =
    std::filesystem::path("bert_attention/inputs/3.bin");
  std::filesystem::path Path5 =
    std::filesystem::path("bert_attention/inputs/5.bin");
  std::filesystem::path Path239 =
    std::filesystem::path("bert_attention/inputs/239.bin");
  std::vector<float> in_3 = loadBinaryInput_f(Path3, 4096);
  std::vector<float> in_5 = loadBinaryInput_f(Path5, 64 * 4096);
  std::vector<float> in_239 = loadBinaryInput_f(Path239, 64 * 4096);

  auto t4 = Clock::now();
  auto encrypted_input =
    bert_attention__encrypt__arg0(cryptoContext, in_3, publicKey);
  auto t5 = Clock::now();

  auto encrypted_result =
    bert_attention(cryptoContext, encrypted_input, in_5, in_239);
  auto t6 = Clock::now();

  std::vector<float> result =
    bert_attention__decrypt__result0(
      cryptoContext,
      encrypted_result,
      secretKey);
  auto t7 = Clock::now();

  auto ms = [](auto a, auto b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
  };

  std::cout << "Context generation : " << ms(t0, t1) << " ms\n";
  std::cout << "Key generation     : " << ms(t1, t2) << " ms\n";
  std::cout << "Eval key setup     : " << ms(t2, t3) << " ms\n";
  std::cout << "Encryption         : " << ms(t4, t5) << " ms\n";
  std::cout << "Homomorphic eval   : " << ms(t5, t6) << " ms\n";
  std::cout << "Decryption         : " << ms(t6, t7) << " ms\n";
  std::cout << "End-to-end         : " << ms(t0, t7) << " ms\n";

  std::cout << "Calculating average evaluation time over multiple iterations...\n";
  const int iterations = 20;

  double total_ms = 0.0;
  for (int i = 0; i < iterations; ++i) {
    auto start = Clock::now();

    auto encrypted_result =
      bert_attention(cryptoContext, encrypted_input, in_5, in_239);

    auto end = Clock::now();
    total_ms += ms(start, end);
  }

  std::cout << "Average evaluation: "
            << total_ms / iterations
            << " ms\n";
}