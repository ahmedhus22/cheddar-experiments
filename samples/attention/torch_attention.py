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


def main():
  torch.manual_seed(0)

  model = BatchedAttentionNoSoftmax().eval()

  x = torch.randn(3, 7, 16)

  module = fx.export_and_import(
    model,
    x,
    output_type="linalg-on-tensors",
  )

  with open("attention_batch.mlir", "w") as f:
    f.write(str(module))

  # with torch.no_grad():
  #   y = model(x)

  # print(y)


if __name__ == "__main__":
  main()