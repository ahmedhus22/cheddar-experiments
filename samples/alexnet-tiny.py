import ast
import re
from pathlib import Path
import torch
import torch.nn as nn


def extract_dense_tensor(text, name):
  """
  Extracts an MLIR dense tensor like

  %w1_fused = arith.constant dense<[[...]]> : tensor<256x768xf32>

  and returns a torch.Tensor.
  """

  pattern = (
    rf"%{name}\s*=\s*arith\.constant\s+dense<"
    r"(.*?)"
    r">\s*:\s*tensor<"
  )

  m = re.search(pattern, text, flags=re.S)
  if m is None:
    raise ValueError(f"Couldn't find constant {name}")

  literal = m.group(1)

  # MLIR's dense literal syntax is valid Python list syntax.
  data = ast.literal_eval(literal)

  return torch.tensor(data, dtype=torch.float32)


class Square(nn.Module):
  def forward(self, x):
    return x * x


class AlexNetTiny(nn.Module):
  def __init__(self):
    super().__init__()

    self.flatten = nn.Flatten()

    self.fc1 = nn.Linear(768, 256)
    self.sq1 = Square()

    self.fc2 = nn.Linear(256, 128)
    self.sq2 = Square()

    self.fc3 = nn.Linear(128, 64)
    self.sq3 = Square()

    self.fc4 = nn.Linear(64, 10)

  def forward(self, x):
    x = self.flatten(x)

    x = self.fc1(x)
    x = self.sq1(x)

    x = self.fc2(x)
    x = self.sq2(x)

    x = self.fc3(x)
    x = self.sq3(x)

    x = self.fc4(x)

    return x


if __name__ == "__main__":
  model = AlexNetTiny()
  alexnet_tiny_path = Path(__file__).parent / "alexnet-tiny.mlir"
  with open(alexnet_tiny_path) as f:
    mlir = f.read()

  w1 = extract_dense_tensor(mlir, "w1_fused")
  b1 = extract_dense_tensor(mlir, "b1_fused")

  w2 = extract_dense_tensor(mlir, "w2_fused")
  b2 = extract_dense_tensor(mlir, "b2_fused")

  w3 = extract_dense_tensor(mlir, "w3_fused")
  b3 = extract_dense_tensor(mlir, "b3_fused")

  wf = extract_dense_tensor(mlir, "wf")
  bf = extract_dense_tensor(mlir, "bf")

  assert w1.shape == torch.Size([256, 768])
  assert b1.shape == torch.Size([256])

  assert w2.shape == torch.Size([128, 256])
  assert w3.shape == torch.Size([64, 128])
  assert wf.shape == torch.Size([10, 64])

  with torch.no_grad():
    model.fc1.weight.copy_(w1)
    model.fc1.bias.copy_(b1)

    model.fc2.weight.copy_(w2)
    model.fc2.bias.copy_(b2)

    model.fc3.weight.copy_(w3)
    model.fc3.bias.copy_(b3)

    model.fc4.weight.copy_(wf)
    model.fc4.bias.copy_(bf)
  
  torch.manual_seed(42)
  x = torch.randn(1, 3, 16, 16, dtype=torch.float32)

  with torch.no_grad():
    y = model(x)
  print(y)

  # write raw floats for C++
  testdata_dir = Path(__file__).parent.parent / "tests" / "testdata"
  testdata_dir.mkdir(exist_ok=True)

  x = x.double()  # convert to double for C++ test
  x.numpy().astype("float64").tofile(testdata_dir / "input.bin")

  y = y.double()  # convert to double for C++ test
  y.numpy().astype("float64").tofile(testdata_dir / "torch_output.bin")
