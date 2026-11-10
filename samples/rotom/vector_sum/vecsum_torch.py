import torch
import torch.nn as nn
import torch_mlir
from torch_mlir import fx


class VecSum(nn.Module):
  def forward(self, A, x):
    return torch.add(A, x)

def main():
  model = VecSum().eval()

  # Input tensors
  A = torch.randn(1024)
  x = torch.randn(1024)

  # Export and import into Torch dialect
  module = fx.export_and_import(
    model,
    A,
    x,
    output_type="linalg-on-tensors"
  )

  print(module)
  with open("samples/rotom/vector_sum/vecsum_linalg.mlir", "w") as f:
    f.write(str(module))

  with torch.no_grad():
    y = model(A, x)
  
  print("Output shape:", y.shape)

if __name__ == "__main__":
  main()