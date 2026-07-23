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


def main():
  torch.manual_seed(0)

  seq_len = 8
  d_model = 16
  d_k = 16

  model = AttentionNoSoftmax(d_model, d_k)
  model.eval()

  x = torch.randn(seq_len, d_model)
  exported = torch.export.export(model, (x,))

  module = fx.export_and_import(
    model,
    x,
    output_type="linalg-on-tensors",
  )
  with open("attention.mlir", "w") as f:
    f.write(str(module))

  # with torch.no_grad():
  #   y = model(x)

  # print(y)


if __name__ == "__main__":
  main()