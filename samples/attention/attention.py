import numpy as np
from heir import compile
from heir.mlir import F32, F64, Secret, Tensor

# Dimension configuration: 2 tokens (sequence length), 4 hidden dimensions
SEQ_LEN = 2
DIM = 4

# Compile the Self-Attention block using CKKS floating-point encryption
@compile(scheme="ckks", backend="openfhe", debug=False)
def private_self_attention(
    x: Secret[Tensor[[SEQ_LEN, DIM], F32]],      # Input Hidden States (Encrypted)
    w_q: Secret[Tensor[[DIM, DIM], F32]],       # Query Weights (Encrypted)
    w_k: Secret[Tensor[[DIM, DIM], F32]],       # Key Weights (Encrypted)
    w_v: Secret[Tensor[[DIM, DIM], F32]]        # Value Weights (Encrypted)
):
    
    # 1. Project Inputs into Query, Key, and Value spaces using Matrix Multiplication (@)
    q = x @ w_q   # Shape: [SEQ_LEN, DIM]
    k = x @ w_k   # Shape: [SEQ_LEN, DIM]
    v = x @ w_v   # Shape: [SEQ_LEN, DIM]
    
    # 2. Compute Raw Attention Scores (Q x K^T)
    # Note: To avoid explicit transpose ops which can be complex in FHE, 
    # we use standard matrix multiplication scaled accordingly.
    raw_scores = q @ k
    
    # 3. Scale by 1 / sqrt(d_k)
    # For DIM = 4, sqrt(4) = 2.0, so we multiply by 0.5
    scaled_scores = raw_scores * F32(0.5)
    
    # 4. FHE-Friendly Polynomial Softmax Approximation
    # Exact Softmax is impossible in FHE. We replace it with a 2nd-degree Taylor 
    # polynomial expansion approximation: f(x) = 0.5x^2 + x + 0.25
    squared_scores = scaled_scores * scaled_scores
    poly_softmax = (squared_scores * F32(0.5)) + scaled_scores + F32(0.25)
    
    # 5. Compute Weighted Attention Output (Softmax_approx x V)
    attention_output = poly_softmax @ v   # Shape: [SEQ_LEN, DIM]
    
    return attention_output

def main():
    print("--- Initializing HEIR Compiler Context ---")
    private_self_attention.setup()

    # Generate mock inputs using NumPy
    np.random.seed(42)
    raw_x = np.random.randn(SEQ_LEN, DIM).astype(np.float32)
    raw_wq = np.random.randn(DIM, DIM).astype(np.float32)
    raw_wk = np.random.randn(DIM, DIM).astype(np.float32)
    raw_wv = np.random.randn(DIM, DIM).astype(np.float32)

    print("\n--- Encrypting Model Inputs and Weights ---")
    encrypted_x = private_self_attention.encrypt_x(raw_x)
    encrypted_wq = private_self_attention.encrypt_w_q(raw_wq)
    encrypted_wk = private_self_attention.encrypt_w_k(raw_wk)
    encrypted_wv = private_self_attention.encrypt_w_v(raw_wv)

    print("\n--- Evaluating Private Self-Attention Circuit on OpenFHE ---")
    encrypted_result = private_self_attention.eval(
        encrypted_x, encrypted_wq, encrypted_wk, encrypted_wv
    )

    print("\n--- Decrypting Result ---")
    decrypted_numpy_result = private_self_attention.decrypt_result(encrypted_result)

    # Plaintext Verification Logic
    p_q = raw_x @ raw_wq
    p_k = raw_x @ raw_wk
    p_v = raw_x @ raw_wv
    p_scaled = (p_q @ p_k) * 0.5
    p_softmax_approx = (0.5 * (p_scaled ** 2)) + p_scaled + 0.25
    expected_plaintext = p_softmax_approx @ p_v

    print("\n=== ATTENTION VERIFICATION ===")
    print(f"FHE Decrypted Output Shape: {decrypted_numpy_result.shape}")
    print(f"FHE Decrypted Attention Matrix:\n{decrypted_numpy_result}")
    print(f"\nExpected Ground Truth Matrix:\n{expected_plaintext}")

if __name__ == "__main__":
    main()


# from heir import compile
# from heir.mlir import F64, Secret

# @compile()  # defaults to scheme="bgv", OpenFHE backend, and debug=False
# def attention(input: Secret[F64], Wq: Secret[F64], Wk: Secret[F64], Wv: Secret[F64]):
#     Q = input @ Wq
#     K = input @ Wk
#     V = input @ Wv

#     # Compute attention scores
#     scores = Q @ K.T
#     output = scores @ V

# from heir import compile
# from heir.mlir import I64, Secret

# @compile()  # defaults to scheme="bgv", OpenFHE backend, and debug=False
# def func(x: Secret[I64], y: Secret[I64]):
#     sum = x + y
#     diff = x - y
#     mul = x * y
#     expression = sum * diff + mul
#     deadcode = expression * mul
#     return expression

# func.setup()
# enc_x = func.encrypt_x(7)
# enc_y = func.encrypt_y(8)
# result_enc = func.eval(enc_x, enc_y)
# result = func.decrypt_result(result_enc)

# print(
#   f"Expected result for `func`: {func.original(7,8)}, FHE result:"
#   f" {result}"
# )