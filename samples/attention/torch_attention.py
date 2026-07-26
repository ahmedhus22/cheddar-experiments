import math
import torch
import torch.nn as nn
from torch_mlir import fx


class AttentionNoSoftmax(nn.Module):
  def __init__(self, d_model, d_k):
    super().__init__()

    self.Wq = nn.Parameter(torch.randn(d_model, d_k))
    self.Wk = nn.Parameter(torch.randn(d_model, d_k))
    self.Wv = nn.Parameter(torch.randn(d_model, d_k))

    self.scale = 1.0 / math.sqrt(d_k)

  def forward(self, x):
    # x: [seq_len, d_model]

    Q = torch.matmul(x, self.Wq)           # [seq_len, d_k]
    K = torch.matmul(x, self.Wk)           # [seq_len, d_k]
    V = torch.matmul(x, self.Wv)           # [seq_len, d_k]

    scores = torch.matmul(Q, K.transpose(0, 1))
    scores = scores * self.scale

    output = torch.matmul(scores, V)

    return output


class SingleHeadAttentionNoSoftmax(nn.Module):
  def __init__(
    self,
    seq_len=7,
    d_model=16,
    d_k=17,
    pad_rows=4,
  ):
    super().__init__()
    self.d_model = d_model
    self.seq_len = seq_len
    self.d_k= d_k
    self.pad_rows = pad_rows

    self.Wq = nn.Parameter(torch.randn(d_model, d_k))
    self.Wk = nn.Parameter(torch.randn(d_model, d_k))
    self.Wv = nn.Parameter(torch.randn(d_model, d_k))

    self.scale = 1.0 / math.sqrt(d_k)


  def forward(self, x):
    # x : [L, d_model]

    Q = torch.matmul(x, self.Wq)
    K = torch.matmul(x, self.Wk)
    V = torch.matmul(x, self.Wv)

    # [L+r, d_k]
    L = self.seq_len
    r = self.pad_rows

    I = torch.eye(L)
    I_prime = torch.cat([I, torch.zeros(r, L)], dim=0)

    K = torch.matmul(I_prime, K)
    V = torch.matmul(I_prime, V)

    # [L, L+r]
    scores = torch.matmul(Q, K.transpose(0, 1))
    scores = scores * self.scale

    # [L, d_k]
    output = torch.matmul(scores, V)

    return output


class BatchedAttentionNoSoftmax(nn.Module):
  def __init__(self, num_heads=3, seq_len=7, head_dim=16):
    super().__init__()

    self.num_heads = num_heads
    self.seq_len = seq_len
    self.head_dim = head_dim

    # One projection matrix per head
    self.Wq = nn.Parameter(torch.randn(num_heads, head_dim, head_dim))
    self.Wk = nn.Parameter(torch.randn(num_heads, head_dim, head_dim))
    self.Wv = nn.Parameter(torch.randn(num_heads, head_dim, head_dim))

    self.scale = 1.0 / math.sqrt(head_dim)

  def forward(self, x):
    # x: [H, S, D]

    # Batched matrix multiplication
    Q = torch.matmul(x, self.Wq)  # [H, S, D]
    K = torch.matmul(x, self.Wk)  # [H, S, D]
    V = torch.matmul(x, self.Wv)  # [H, S, D]

    # Batched attention scores
    scores = torch.matmul(Q, K.transpose(-2, -1))  # [H, S, S]
    scores = scores * self.scale

    # Batched output
    output = torch.matmul(scores, V)  # [H, S, D]

    return output


class TricycleAttentionNoSoftmax(nn.Module):
  def __init__(
    self,
    d_model=16,
    num_heads=3,
    seq_len=7,
    d_k_half=17,
    pad_rows=4,
  ):
    super().__init__()

    self.d_model = d_model
    self.num_heads = num_heads
    self.seq_len = seq_len
    self.d_k_half = d_k_half
    self.pad_rows = pad_rows

    # (H, d_model, d_k/2)
    self.Wq = nn.Parameter(
      torch.randn(num_heads, d_model, d_k_half)
    )
    self.Wk = nn.Parameter(
      torch.randn(num_heads, d_model, d_k_half)
    )
    self.Wv = nn.Parameter(
      torch.randn(num_heads, d_model, d_k_half)
    )

    self.scale = 1.0 / math.sqrt(d_k_half)

    #
    # I' : (1, L+r, L)
    #
    # L = seq_len
    # r = pad_rows

    # I = torch.eye(L)
    # I = torch.cat(
    #   [I, torch.zeros(r, L)],
    #   dim=0,
    # )

    # self.register_buffer(
    #   "I_prime",
    #   I.unsqueeze(0),
    # )

  def forward(self, x):
    #
    # x : (L, d_model)
    #

    #
    # Broadcast input across heads
    #
    # x = x.unsqueeze(0).expand(self.num_heads, -1, -1) # HEIR doesn't support broadcasting 2D to 3D, so we use repeat instead
    #
    # (H, L, d_model)
    #

    #
    # Broadcasted batch matrix multiplication
    #
    Q = torch.matmul(x, self.Wq)
    K = torch.matmul(x, self.Wk)
    V = torch.matmul(x, self.Wv)
    #
    # (H, L, d_k_half)
    #

    #
    # Reshape K and V using the tall identity
    #
    L = self.seq_len
    r = self.pad_rows

    I = torch.eye(
      L,
      dtype=x.dtype,
      device=x.device,
    )

    I = torch.cat(
      [I, torch.zeros(r, L, dtype=x.dtype, device=x.device)],
      dim=0,
    )

    I_prime = I.unsqueeze(0)
    K = torch.matmul(I_prime, K)
    V = torch.matmul(I_prime, V)
    #
    # (H, L+r, d_k_half)
    #

    #
    # Attention scores
    #
    scores = torch.matmul(
      Q,
      K.transpose(-2, -1),
    )
    #
    # (H, L, L+r)
    #

    scores = scores * self.scale

    #
    # Attention output
    #
    output = torch.matmul(scores, V)
    #
    # (H, L, d_k_half)
    #

    return output


def main():
  torch.manual_seed(0)

  model = SingleHeadAttentionNoSoftmax(
    d_model=16,
    seq_len=7,
    d_k=17,
    pad_rows=4,      # L+r = 11
  ).eval()

  x = torch.randn(7, 16)


  module = fx.export_and_import(
    model,
    x,
    output_type="linalg-on-tensors",
  )

  with open("samples/attention/attention.mlir", "w") as f:
    f.write(str(module))

  with torch.no_grad():
    y = model(x)

  print("Output shape:", y.shape)


if __name__ == "__main__":
  main()