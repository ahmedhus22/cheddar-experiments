import numpy as np
import sys

if len(sys.argv) != 2:
    print(f"Usage: python {sys.argv[0]} <binary_file>")
    sys.exit(1)

file_path = sys.argv[1]

data = np.fromfile(file_path, dtype=np.float32)

print(f"File: {file_path}")
print(f"Total elements: {data.size}")
print(f"Shape: {data.shape}")