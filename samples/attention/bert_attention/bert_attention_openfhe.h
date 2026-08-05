
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
