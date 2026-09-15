from argparse import ArgumentParser
import ast
import re
from pathlib import Path
import torch
import torch.nn as nn


def extract_dense_tensor(text, name):
  """
  Extracts an MLIR dense tensor like

  %w1 = arith.constant dense<[[...]]> : tensor<784x784xf32>

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

class LeNet(nn.Module):
  def __init__(self):
    super().__init__()

    self.fc1 = nn.Linear(784, 784)
    self.fc2 = nn.Linear(784, 392)
    self.fc3 = nn.Linear(392, 32)
    self.fc4 = nn.Linear(32, 10)

  def forward(self, x):
    x = x.reshape(784)

    x = self.fc1(x)
    x = x * x

    x = self.fc2(x)
    x = x * x

    x = self.fc3(x)
    x = x * x

    x = self.fc4(x)

    return x

if __name__ == "__main__":
  parser = ArgumentParser()
  # Add an argument for the input MLIR file, within the "MLIR/" directory.
  parser.add_argument("--input", type=Path, default=Path("lenet") / "lenet-n2048.mlir")
  args = parser.parse_args()

  model = LeNet()
  lenet_tiny_path = Path(__file__).parent / "MLIR" / args.input
  with open(lenet_tiny_path) as f:
    mlir = f.read()

  w1 = extract_dense_tensor(mlir, "w1")
  b1 = extract_dense_tensor(mlir, "b1")

  w2 = extract_dense_tensor(mlir, "w2")
  b2 = extract_dense_tensor(mlir, "b2")

  w3 = extract_dense_tensor(mlir, "w3")
  b3 = extract_dense_tensor(mlir, "b3")

  w4 = extract_dense_tensor(mlir, "w4")
  b4 = extract_dense_tensor(mlir, "b4")

  assert w1.shape == torch.Size([784, 784])
  assert b1.shape == torch.Size([784])

  assert w2.shape == torch.Size([392, 784])
  assert b2.shape == torch.Size([392])

  assert w3.shape == torch.Size([32, 392])
  assert b3.shape == torch.Size([32])

  assert w4.shape == torch.Size([10, 32])
  assert b4.shape == torch.Size([10])

  with torch.no_grad():
    model.fc1.weight.copy_(w1)
    model.fc1.bias.copy_(b1)

    model.fc2.weight.copy_(w2)
    model.fc2.bias.copy_(b2)

    model.fc3.weight.copy_(w3)
    model.fc3.bias.copy_(b3)

    model.fc4.weight.copy_(w4)
    model.fc4.bias.copy_(b4)
  
  torch.manual_seed(42)
  x = torch.randn(1, 1, 28, 28, dtype=torch.float32)

  with torch.no_grad():
    y = model(x)
  print(y)

  # write raw floats for C++
  testdata_dir = Path(__file__).parents[2] / "tests" / "testdata" / args.input.stem
  testdata_dir.mkdir(exist_ok=True)

  #x = x.double()  # swap comment to save floats as doubles for the C++ test
  #x.numpy().astype("float64").tofile(testdata_dir / "input.bin")
  x.numpy().astype("float32").tofile(testdata_dir / "input.bin")

  # swap comment to save reference data as doubles for the C++ test
  #y = y.double()
  #y.numpy().astype("float64").tofile(testdata_dir / "torch_output.bin")
  y.numpy().astype("float32").tofile(testdata_dir / "torch_output.bin")